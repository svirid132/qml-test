#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QList>
#include <QPair>
#include "datasqlite.h"

#include "sqlrenamer.h"

class QSqlError;
class QSqlDatabase;
class QString;

namespace SQLite {
    class SQLiteManager;
}

/**
 * @brief The SQLiteManager class - основной класс для обращение к бд
 */
class SQLite::SQLiteManager
{
public:
    static SQLiteManager& getInstance() {
        static SQLiteManager instance;
        return instance;
    }

    /**
     * @brief isDriverExit - проверяет существование драйвера sqlite
     * @return
     */
    bool isDriverExit();
    /**
     * @brief initDB - подключается к бд или создает ее
     * @param nameDB - имя бд
     * @return
     */
    QSqlError initDB(const QString& nameDB = "database");
    /**
     * @brief execInsertEmployee - добавить нового сотрудника
     * @param employee - сотрудник
     * @return
     */
    QSqlError execInsertEmployee(const QPair<Employee, Additionally>& employee);
    /**
     * @brief execSelectEmployees - выводит всех сотрудников из бд
     * @return сотруники
     */
    QList<QPair<Employee, Additionally>> execSelectEmployees();
    /**
     * @brief execSelectLastEmp - выводит последнего добавленного сотрудника в бд
     * @return сотрудник
     */
    QPair<Employee, Additionally> execSelectLastEmp();
    /**
     * @brief execSelectCountries - выводит все страны которые есть в бд
     * @return страны
     */
    QList<Country> execSelectCountries();
    /**
     * @brief execUpdateEmployee - обновляет сотрудника
     * @param employee - новые данные сотрудника
     * @return ошибку
     */
    QSqlError execUpdateEmployee(const QPair<Employee, Additionally>& employee);
    /**
     * @brief execDeleteEmployee - удаляет сотрудника из бд
     * @param idEmployee - id сотрудника
     * @param idAdditional - id дополнения к сотруднику
     * @return ошибку
     */
    QSqlError execDeleteEmployee(int idEmployee, int idAdditional);

private:
    SQLiteManager();
    SQLRenamer renamer;

    /**
     * @brief isTableExits - проверяет сществования всех таблиц в бд
     * @param db
     * @return
     */
    bool isTableExits(const QSqlDatabase& db);
    /**
     * @brief execDirQuery - выполняент все запросы из папки
     * @param dir - путь к папке
     * @return
     */
    QSqlError execDirQuery(const QString& dir);
    /**
     * @brief beginTransaction - начать транзакцию
     * @return ошибку
     */
    QSqlError beginTransaction();
    /**
     * @brief commitTransaction - успешно завершить транзакцию
     * @return ошибку
     */
    QSqlError commitTransaction();
};

#endif // SQLITEMANAGER_H
