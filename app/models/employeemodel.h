#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include "datasqlite.h"

class EmployeeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EmployeeModel(QObject *parent = nullptr);

signals:

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int columnCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void insertEmp(const Employee& emp);
    void deleteEmp(int row);
    void updateEmp(int rowIndex, const Employee& emp);
    Employee getEmp(int row);

private:
    QList<Employee> empList;
    enum EmployeeRoles {
        idRole = Qt::UserRole,
        firstNameRole = Qt::UserRole + 1,
        lastNameRole = Qt::UserRole + 2,
        idAdditionallyRole = Qt::UserRole + 3
    };

    // QAbstractItemModel interface
public:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    // QAbstractItemModel interface
public:
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    Q_INVOKABLE bool isValid(int row);
};

#endif // EMPLOYEEMODEL_H
