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

inline void initMyResource() { Q_INIT_RESOURCE(res); }

namespace SQLite {
SQLite::SQLiteManager::SQLiteManager()
{
    initMyResource();
}

bool SQLiteManager::isDriverExit() {
    return QSqlDatabase::drivers().contains("QSQLITE");
}

QSqlError SQLiteManager::initDB(const QString& nameDB) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nameDB);

    if (!db.open()) {
        return db.lastError();
    }

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

    QStringList execCmds = renamer.insertEmployee(employee);
    QSqlError error;
    error = beginTransaction();
    if (error.isValid()) return error;
    QSqlQuery q;
    for (int i = 0; i < execCmds.length(); ++i) {
        if (!q.exec(execCmds.at(i))) {
            return q.lastError();
        }
    }
    error = commitTransaction();
    if (error.isValid()) return error;

    return QSqlError();
}

QList<QPair<SQLite::Employee, SQLite::Additionally>> SQLiteManager::execSelectEmployees()
{
    QFile file(":/select/employees.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open file!";
    }
    QString execCmd = QString(file.readAll());
    QSqlError error;
    error = beginTransaction();
    if (error.isValid()) return QList<QPair<Employee, Additionally>>();
    QSqlQuery q;
    if (!q.exec(execCmd)) {
        qDebug() << "execSelectEmployees:" << q.lastError();
    }
    QList<QPair<Employee, Additionally>> employees;
    while (q.next()) {
        Employee emp;
        Additionally additionally;
        emp.id = q.value(0).toInt();
        emp.firstName = q.value(1).toString();
        emp.lastName = q.value(2).toString();
        emp.additionally_id = q.value(3).toInt();
        additionally.id = q.value(4).toInt();
        additionally.address = q.value(5).toString();
        additionally.phone = q.value(6).toString();
        additionally.maritalStatus = q.value(7).toString();
        QString strCodes = q.value(8).toString();
        QStringList listCodes = {};
        if (!strCodes.isEmpty()) {
            listCodes = strCodes.split(";");
        }

        QList<int> codes;
        for (int i = 0; i < listCodes.size(); ++i) {
            int code = listCodes.at(i).toInt();
            codes.append(code);
        }
        additionally.codeCountries = codes;
        QPair<Employee, Additionally> employee;
        employee.first = emp;
        employee.second = additionally;
        employees.append(employee);
    }
    error = commitTransaction();
    if (error.isValid()) return QList<QPair<Employee, Additionally>>();
    return employees;
}

QPair<SQLite::Employee, SQLite::Additionally> SQLiteManager::execSelectLastEmp()
{
    QFile file(":/select/last_employee.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open file";
    }
    QString execCmd = QString(file.readAll());
    QSqlError error;
    error = beginTransaction();
    if (error.isValid()) return QPair<Employee, Additionally>();
    QSqlQuery q;
    if (!q.exec(execCmd)) {
        qDebug() << "execSelectLastEmp:" << q.lastError();
    }
    q.next();
    Employee emp;
    Additionally additionally;
    emp.id = q.value(0).toInt();
    emp.firstName = q.value(1).toString();
    emp.lastName = q.value(2).toString();
    emp.additionally_id = q.value(3).toInt();
    additionally.id = q.value(4).toInt();
    additionally.address = q.value(5).toString();
    additionally.phone = q.value(6).toString();
    additionally.maritalStatus = q.value(7).toString();
    QString strCodes = q.value(8).toString();
    QStringList listCodes = {};
    if (!strCodes.isEmpty()) {
        listCodes = strCodes.split(";");
    }
    QList<int> codes;
    for (int i = 0; i < listCodes.size(); ++i) {
        int code = listCodes.at(i).toInt();
        codes.append(code);
    }
    additionally.codeCountries = codes;
    QPair<Employee, Additionally> employee;
    employee.first = emp;
    employee.second = additionally;

    error = commitTransaction();
    if (error.isValid()) return QPair<Employee, Additionally>();

    return employee;
}

QList<Country> SQLiteManager::execSelectCountries()
{
    QFile file(":/select/countries.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open file!";
    }
    QString execCmd = QString(file.readAll());
    QSqlError error;
    error = beginTransaction();
    if (error.isValid()) return QList<Country>();
    QSqlQuery q;
    if (!q.exec(execCmd)) {
        qDebug() << "execSelectCountry:" << q.lastError();
    }
    QList<Country> countries;
    while (q.next()) {
        Country country;
        country.code = q.value(0).toInt();
        country.name = q.value(1).toString();
        countries.append(country);
    }
    error = commitTransaction();
    if (error.isValid()) return QList<Country>();

    return countries;
}

QSqlError SQLiteManager::execUpdateEmployee(const QPair<Employee, Additionally> &employee)
{
    Employee emp = employee.first;
    Additionally add = employee.second;

    QStringList execCmds = renamer.updateEmployee(employee);
    QSqlError error;
    error = beginTransaction();
    if (error.isValid()) return error;
    QSqlQuery q;
    for (int i = 0; i < execCmds.size(); ++i) {
        if (!q.exec(execCmds.at(i))) {
            return q.lastError();
        }
    }
    error = commitTransaction();
    if (error.isValid()) return error;
    return QSqlError();
}

QSqlError SQLiteManager::execDeleteEmployee(int idEmployee, int idAdditional)
{
    QStringList execCmds = renamer.deleteEmployee(idEmployee, idAdditional);
    QSqlError error;
    error = beginTransaction();
    if (error.isValid()) return error;
    QSqlQuery q;
    for (int i = 0; i < execCmds.size(); ++i) {
        if (!q.exec(execCmds.at(i))) {
            return q.lastError();
        }
    }
    error = commitTransaction();
    if (error.isValid()) return error;
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

QSqlError SQLiteManager::beginTransaction()
{
    const auto exec = [](const QString& strExec) {
        QSqlQuery q;
        if (!q.exec(strExec)) {
            return q.lastError();
        } else {
            return QSqlError();
        }
    };

    QSqlError error;
    error = exec("BEGIN;");
    if (!error.isValid()) return QSqlError();

    exec("ROLLBACK;");
    error = exec("BEGIN");
    return error;
}

QSqlError SQLiteManager::commitTransaction()
{
    QSqlQuery q;
    q.exec("COMMIT;");
    return q.lastError();
}
}
