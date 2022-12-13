#include "empmodel.h"

#include <QDebug>

EmpModel::EmpModel(QObject *parent)
    : QSqlTableModel{parent}
{
    this->setTable("employees");
    this->select();
    this->setHeaderData(0, Qt::Horizontal, tr("Name"));
    this->setHeaderData(1, Qt::Horizontal, tr("Salary"));

    qDebug() << "this!" << this->rowCount();
}

QHash<int, QByteArray> EmpModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[idRole] = "id";
    roles[firstNameRole] = "firstName";
    roles[lastNameRole] = "lastName";
    roles[idAdditionalRole] = "idAdditional";

    return roles;
}

QVariant EmpModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    // Для qml
    if (role >= Qt::UserRole) {
        int column = role - Qt::UserRole;
        return data(this->index(index.row(), column), Qt::DisplayRole);
    }

    return QSqlTableModel::data(this->index(index.row(), index.column()), role);
}
