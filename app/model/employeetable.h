#ifndef EMPLOYEETABLE_H
#define EMPLOYEETABLE_H

#include <QSqlTableModel>

class EmployeeTable : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit EmployeeTable(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE void update();

private:
    enum Roles {
        idRole = Qt::UserRole,
        firstNameRole = Qt::UserRole + 1,
        lastNameRole = Qt::UserRole + 2,
        idAdditionalRole = Qt::UserRole + 3
    };

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // EmployeeTable_H
