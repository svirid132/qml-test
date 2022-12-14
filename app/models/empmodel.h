#ifndef EMPMODEL_H
#define EMPMODEL_H

#include <QSqlTableModel>

class EmpModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit EmpModel(QObject *parent = nullptr);

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

#endif // EMPMODEL_H
