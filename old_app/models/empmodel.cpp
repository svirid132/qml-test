#include "empmodel.h"

EmpModel::EmpModel(QObject *parent)
    : QSqlTableModel{parent}
{
    this->setTable("employees");
    this->select();
}
