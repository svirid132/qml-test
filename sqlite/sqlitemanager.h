#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QList>
#include <QPair>
#include "datasqlite.h"

#include "sqlrenamer.h"

class QSqlError;
class QSqlDatabase;
class QString;

//struct Employee;
//struct Additionally;
//struct Country;

class SQLiteManager
{
public:
    SQLiteManager();

    bool isDriverExit();
    QSqlError initDB(const QString& nameDB = "database");
    QSqlError execInsertEmployee(const QPair<Employee, Additionally>& employee);
    QList<QPair<Employee, Additionally>> execSelectEmployees();
    QList<Country> execSelectCountries();
    QSqlError execUpdateEmployee(const QPair<Employee, Additionally>& employee);
    QSqlError execDeleteEmployee(int idEmployee, int idAdditional);

private:
    SQLRenamer renamer;

    bool isTableExits(const QSqlDatabase& db);
    QSqlError execDirQuery(const QString& dir);
    QSqlError beginTransaction();
    QSqlError commitTransaction();
};

#endif // SQLITEMANAGER_H
