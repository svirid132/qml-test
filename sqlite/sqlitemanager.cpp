#include "datasqlite.h"
#include "sqlitemanager.h"
#include "sqlrenamer.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QResource>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>

SQLiteManager::SQLiteManager()
{
    Q_INIT_RESOURCE(res);
}

bool SQLiteManager::isDriverExit() {
    return QSqlDatabase::drivers().contains("QSQLITE");
}

QSqlError SQLiteManager::initDB() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database");

    if (!db.open()) {
        return db.lastError();
    }

    qDebug() << "isTableExits" << isTableExits(db);
    if (isTableExits(db)) {
        return QSqlError();
    }

    QSqlError error;
    error = execDirQuery(":/create-table");
    if (error.isValid()) {
        return error;
    }
    error = execDirQuery(":/create");
    if (error.isValid()) {
        return error;
    }
    error = execDirQuery(":/default-insert");
    if (error.isValid()) {
        return error;
    }

    return QSqlError();
}

bool SQLiteManager::isTableExits(const QSqlDatabase& db)
{
    QStringList tables = db.tables();
    QDirIterator it(":/create-table", QDir::Files, QDirIterator::FollowSymlinks);
    bool isTableExit = true;
    if (tables.isEmpty()) isTableExit = false;
    while (it.hasNext()) {
        it.next();
        QString file = it.fileName();
        if (isTableExit){
            isTableExit = tables.contains(file.remove(".sql"), Qt::CaseInsensitive);
        }
    }
    return isTableExit;
}

QSqlError SQLiteManager::execInsertEmployee(const QPair<Employee, Additionally>& employee) {
    QSqlQuery q;

    if (!q.exec("BEGIN;")) {
        q.lastError();
    }

    QFile file(":/insert/employee.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open employee.sql!";
    }
    Employee mainEmp = employee.first;
    Additionally additionally = employee.second;
    QList<int> countries = additionally.codeCountries;

    QString execInsertAdditionallyCountry = "INSERT INTO \"additionally_country\"(country_code, additionally_id) VALUES %6;";
    QString strValuesCountry = QString("(%1, (SELECT * from _Variables)),");
    QString resValuesCountry = "";
    for (int i = 0; i < countries.size(); ++i) {
        int code = countries.at(i);
        resValuesCountry += strValuesCountry.arg(code);
    }
    resValuesCountry.chop(1);
    if (resValuesCountry.isEmpty()) {
        execInsertAdditionallyCountry = "";
    } else {
        execInsertAdditionallyCountry = execInsertAdditionallyCountry.arg(resValuesCountry);
    }

    QString strExec = QString(file.readAll()).
            arg(additionally.address).arg(additionally.phone).arg(additionally.maritalStatus).
            arg(mainEmp.firstName).arg(mainEmp.lastName).
            arg(execInsertAdditionallyCountry);
    file.close();

    QSqlError error = execBigQuery(strExec);
    if(error.isValid()) {
        q.exec("ROLLBACK;");
        qDebug() << "this error";
        return error;
    } else {
        q.exec("COMMIT;");
    }

    //test
    QFile resFile("employee");
    resFile.open(QIODevice::WriteOnly);
    resFile.write(strExec.toLocal8Bit());
    resFile.close();

    return QSqlError();
}

QList<QPair<Employee, Additionally> > SQLiteManager::execSelectEmployees()
{
    QFile file(":/select/employees.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open employee.sql!";
    }
    QString execCmd = QString(file.readAll());

    QSqlQuery q;
    if (!q.exec(execCmd)) {
        qDebug() << "execSelectEmployees:" <<q.lastError();
    }
    QList<QPair<Employee, Additionally>> employees;
    while (q.next()) {
        Employee emp;
        Additionally additionally;
        emp.id = q.value(0).toInt();
        emp.firstName = q.value(1).toString();
        emp.lastName = q.value(2).toString();
        additionally.address = q.value(3).toString();
        additionally.phone = q.value(4).toString();
        additionally.maritalStatus = q.value(5).toString();
        QStringList strCodes = q.value(6).toString().split(';');
        QList<int> codes;
        for (int i = 0; i < strCodes.size(); ++i) {
            int code = strCodes.at(i).toInt();
            codes.append(code);
        }
        additionally.codeCountries = codes;
        QPair<Employee, Additionally> employee;
        employee.first = emp;
        employee.second = additionally;
        employees.append(employee);
    }
    return employees;
}

QList<Country> SQLiteManager::execSelectCountries()
{
    QFile file(":/select/countries.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open employee.sql!";
    }
    QString execCmd = QString(file.readAll());

    QSqlQuery q;
    if (!q.exec(execCmd)) {
        qDebug() << "execSelectCountry:" <<q.lastError();
    }
    QList<Country> countries;
    while (q.next()) {
        Country country;
        country.code = q.value(0).toInt();
        country.name = q.value(1).toString();
        countries.append(country);
    }

    return countries;
}

QSqlError SQLiteManager::execUpdateEmployee(const QPair<Employee, Additionally> &employee)
{
    Employee emp = employee.first;
    Additionally add = employee.second;

//    Employee emp;
//    emp.id = 2;
//    emp.firstName = "Александр";
//    emp.lastName = "Свиридов";
//    Additionally additionally;
//    additionally.id = 133;
//    additionally.address = "Вязов";
//    additionally.maritalStatus = "Не женат";
//    additionally.phone = "123-123";
//    additionally.codeCountries.append(643);
//    additionally.codeCountries.append(895);
//    QPair<Employee, Additionally> employee;
//    employee.first = emp;
//    employee.second = additionally;

    QStringList execCmds = renamer.updateEmployee(employee);
    QSqlQuery q;
    for (int i = 0; i < execCmds.length(); ++i) {
        if (!q.exec(execCmds.at(i))) {
            return q.lastError();
        }
    }
    return QSqlError();
}

QSqlError SQLiteManager::execDeleteEmployee(int idEmployee, int idAdditional)
{
    QStringList execCmds = renamer.deleteEmployee(idEmployee, idAdditional);
    QSqlQuery q;
    for (int i = 0; i < execCmds.size(); ++i) {
        //        qDebug() << execCmds.at(i);
        if (!q.exec(execCmds.at(i))) {
            return q.lastError();
        }
    }
    return QSqlError();
}

QSqlError SQLiteManager::execDirQuery(const QString &dir)
{
    QDirIterator it(dir, QDirIterator::FollowSymlinks);
    while (it.hasNext()) {
        QSqlQuery q;
        QFile file(it.next());
        file.open(QIODevice::ReadOnly);
        QString strQuery = file.readAll();
        if (!q.exec(strQuery)) {
            return q.lastError();
        }
    }
    return QSqlError();
}

QSqlError SQLiteManager::execBigQuery(const QString &bigQuery)
{
    QSqlQuery query;
    QStringList list = bigQuery.split(';');
    QStringList cleanList;
    for (const auto& str: qAsConst(list)) {
        QString query = str.simplified();
        int index = str.indexOf("--");
        if (index == -1 && !str.isEmpty()) {
            cleanList.append(query);
        }
    }
    for (const auto& str: qAsConst(cleanList)) {
        qDebug() << str;
        if(!query.exec(str)) {
            return query.lastError();
        }
    }
    return QSqlError();
}
