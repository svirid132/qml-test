#ifndef INFOEMPLOYEEMODEL_H
#define INFOEMPLOYEEMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <sqlitemanager.h>
#include "datasqlite.h"

class InfoEmployeeModel : public QObject
{
    Q_OBJECT
public:
    explicit InfoEmployeeModel(QObject *parent = nullptr);

public:
    /**
     * @brief insertEmp - Добавить в модель сотрудника
     * @param emp
     */
    void insertEmp(const Employee& emp);
    /**
     * @brief deleteEmp - удалить сотрудника
     * @param row - строка для удаления
     */
    void deleteEmp(int row);
    /**
     * @brief updateEmp - обновить данные сотрудника
     * @param rowIndex - строка для обновления
     * @param emp - новые данные сотрудника
     */
    void updateEmp(int rowIndex, const Employee& emp);
    /**
     * @brief getEmp вернуть сотрудника по индекску строки
     * @param row - индекс строки
     * @return
     */
    Employee getEmp(int row);

private:
    QList<Employee> empList;
    enum EmployeeRoles {
        idRole = Qt::UserRole,
        firstNameRole = Qt::UserRole + 1,
        lastNameRole = Qt::UserRole + 2,
        idAdditionallyRole = Qt::UserRole + 3
    };
    SQLiteManager manager = SQLiteManager::getInstance();
    QMap<int, Additionally> adds;

    // QAbstractItemModel interface
public:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    // QAbstractItemModel interface
public:
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    /**
     * @brief isValid - проверка существования строки
     * @param row - строка для проверки
     * @return
     */
    Q_INVOKABLE bool isValid(int row);
};

#endif // INFOEMPLOYEEMODEL_H
