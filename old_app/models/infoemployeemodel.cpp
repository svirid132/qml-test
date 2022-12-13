#include "infoemployeemodel.h"

InfoEmployeeModel::InfoEmployeeModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    QList<QPair<Employee, Additionally>> listPairEmp = manager.execSelectEmployees();
    for (int i = 0; i < listPairEmp.size(); ++i) {
        Employee emp = listPairEmp[i].first;
        Additionally add = listPairEmp[i].second;
        adds[emp.additionally_id] = add;
    }
}

int InfoEmployeeModel::rowCount(const QModelIndex &parent) const
{
    return adds.size();
}

int InfoEmployeeModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}


