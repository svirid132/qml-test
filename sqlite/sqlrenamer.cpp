#include "datasqlite.h"
#include "sqlrenamer.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>

SQLRenamer::SQLRenamer()
{
    Q_INIT_RESOURCE(res);
}

QStringList SQLRenamer::updateEmployee(const QPair<Employee, Additionally>& employee)
{
    QFile file(":/update/employee.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open employee.sql!";
    }
    QString execCmd = QString(file.readAll());
    execCmd = execCmd.simplified();

    Employee emp = employee.first;
    Additionally add = employee.second;
    int from;
    from = replace(execCmd, "Михаил", emp.firstName);
    from = replace(execCmd, "Чехов", emp.lastName, from);
    from = replace(execCmd, "1", QString::number(emp.id), from);
    from = replace(execCmd, "Крыленко", add.address, from);
    from = replace(execCmd, "8 965 088 00 00", add.phone, from);
    from = replace(execCmd, "Не женат", add.maritalStatus, from);
    from = replace(execCmd, "1", QString::number(add.id), from);
    from = replace(execCmd, "1", QString::number(add.id), from);

    if (add.codeCountries.size() == 0) {
        QString before = "INSERT INTO additionally_country(country_code, additionally_id) VALUES (31, 133), (40, 133);";
        replace(execCmd, before, "", from);
        execCmd = execCmd.trimmed();
    } else {
        QString strValues = "";
        for (int i = 0; i < add.codeCountries.size(); ++i) {
            strValues += QString("(%1, %2),").arg(add.codeCountries.at(i)).arg(add.id);
        }
        strValues.chop(1);
        QString before = "(31, 133), (40, 133)";
        replace(execCmd, before, strValues);
    }
    qDebug() << "execCmd:";
    QStringList list = execCmd.split(";", Qt::SkipEmptyParts);
    for (QString str: list) {
        qDebug() << "string Update:" << str;
    }
    return list;
}

QStringList SQLRenamer::deleteEmployee(int idEmployee, int idAdditionally)
{
    QFile file(":/delete/employee.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open employee.sql!";
    }
    QString execCmd = QString(file.readAll());
    execCmd = execCmd.simplified();

    int from;
    from = replace(execCmd, "2", QString::number(idEmployee));
    from = replace(execCmd, "133", QString::number(idAdditionally), from);
    replace(execCmd, "133", QString::number(idAdditionally), from);

    QStringList list = execCmd.split(";", Qt::SkipEmptyParts);
    return list;
}

QStringList SQLRenamer::insertEmployee(const QPair<Employee, Additionally> &employee)
{
    QFile file(":/insert/employee.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "dont open employee.sql!";
    }
    QString execCmd = QString(file.readAll());
    execCmd = execCmd.simplified();

    Employee emp = employee.first;
    Additionally add = employee.second;
    int from;
    from = replace(execCmd, "Вязов", add.address);
    from = replace(execCmd, "8 965 088 00 00", add.phone, from);
    from = replace(execCmd, "Не женат", add.maritalStatus, from);
    from = replace(execCmd, "Александр", emp.firstName, from);
    from = replace(execCmd, "Свиридов", emp.lastName, from);
    from = replace(execCmd, "Не женат", add.maritalStatus, from);

    if (add.codeCountries.size() == 0) {
        QString before = "INSERT INTO \"additionally_country\"(country_code, additionally_id) VALUES (643, (SELECT * from _Variables)),(895, (SELECT * from _Variables));";
        replace(execCmd, before, "", from);
    } else {
        QString before = "(643, (SELECT * from _Variables)),(895, (SELECT * from _Variables))";
        QString value = QString("(%1, (SELECT * from _Variables)),");
        QString values = "";
        for (int i = 0; i < add.codeCountries.size(); ++i) {
            int code = add.codeCountries.at(i);
            values += value.arg(code);
        }
        values.chop(1);
        replace(execCmd, before, values, from);
    }

    QStringList list = execCmd.split(";", Qt::SkipEmptyParts);
    return list;
}

int SQLRenamer::replace(QString &origin, const QString &before, const QString &after, int from)
{
    int index = origin.indexOf(before, from);
    if (index == -1) return 0;
    origin.replace(index, before.length(), after);

    return index + after.length();
}
