#include "employeemodel.h"

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}


int EmployeeModel::rowCount(const QModelIndex &parent) const
{
    return empList.size();
}

int EmployeeModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role >= Qt::UserRole) {
        int column = role - Qt::UserRole;
        return data(this->index(index.row(), column), Qt::DisplayRole);
    }

    int row = index.row();
    switch(role) {
    case Qt::DisplayRole: {
        switch (index.column()) {
        case 0: {
            return empList.at(row).id;
        }
        case 1: {
            return empList.at(row).firstName;
        }
        case 2: {
            return empList.at(row).lastName;
        }
        case 3: {
            return empList.at(row).additionally_id;
        }
        }
    }
    }


    return QVariant();
}

QHash<int, QByteArray> EmployeeModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();

    roles[idRole] = "id";
    roles[firstNameRole] = "firstName";
    roles[lastNameRole] = "lastName";
    roles[idAdditionallyRole] = "idAdditionally";

    return roles;
}

void EmployeeModel::insertEmp(const Employee &emp)
{

    int newRow = rowCount();
    beginInsertRows(QModelIndex(), newRow, newRow);
    insertRows(newRow - 1, 1);
    endInsertRows();
    QModelIndex inx = index(newRow, 0);
    setData(inx, emp.id);
    inx = inx.siblingAtColumn(1);
    setData(inx, emp.firstName);
    inx = inx.siblingAtColumn(2);
    setData(inx, emp.lastName);
    inx = inx.siblingAtColumn(3);
    setData(inx, emp.additionally_id);
}

void EmployeeModel::deleteEmp(int row)
{
    beginRemoveRows(QModelIndex(), row, row);

    removeRows(row, 1);

    int lastRow = empList.size() - 1;
    auto leftTopIndex = this->index(row, 0);
    auto rightBottomIndex = this->index(lastRow, 4);

    endRemoveRows();
}

void EmployeeModel::updateEmp(int rowIndex, const Employee &emp)
{
    QModelIndex inx = index(rowIndex, 0);
    setData(inx, emp.id);
    inx = inx.siblingAtColumn(1);
    setData(inx, emp.firstName);
    inx = inx.siblingAtColumn(2);
    setData(inx, emp.lastName);
    inx = inx.siblingAtColumn(3);
    setData(inx, emp.additionally_id);
}

Employee EmployeeModel::getEmp(int row)
{
    return empList.at(row);
}


bool EmployeeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    for (int i = 0; i < count; ++i) {
        empList.append(Employee());
    }

    return true;
}

bool EmployeeModel::isValid(int row) {
    return index(row, 0).isValid();
}

bool EmployeeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()){
        return false;
    }

    int row = index.row();
    int column = index.column();
    switch (column) {
    case 0: {
        empList[row].id = value.toInt();
    }
    case 1: {
        empList[row].firstName = value.toString();
    }
    case 2: {
        empList[row].lastName = value.toString();
    }
    case 3: {
        empList[row].additionally_id = value.toInt();
    }
    }

    emit this->dataChanged(index, index);

    return true;
}

bool EmployeeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    for (int i = 0; i < count; ++i) {
        empList.removeAt(row);
    }

    return true;
}
