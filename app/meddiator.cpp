#include "meddiator.h"

#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlError>
#include <datasqlite.h>

Meddiator::Meddiator(QQmlApplicationEngine& app, QObject *parent)
    : QObject{parent}
{
    QSqlError error = manager.initDB();
    qDebug() << "manager:" << !error.isValid();

    //Заполнение модели странами
    QList<Country> listCounties = manager.execSelectCountries();
    QList<CountryData> listCoyntryDatas;
    for (int i = 0; i < listCounties.size(); ++i) {
        CountryData countryData;
        countryData.code = listCounties[i].code;
        countryData.country = listCounties[i].name;
        listCoyntryDatas.append(countryData);
    }
    countryModel.setCountryDatas(listCoyntryDatas);

    //заполнение модели сотрудниками
    QList<QPair<Employee, Additionally>> listPairEmp = manager.execSelectEmployees();
    for (int i = 0; i < listPairEmp.size(); ++i) {
        Employee emp = listPairEmp[i].first;
        Additionally add = listPairEmp[i].second;
        empModel.insertEmp(emp);
        qDebug() << "emp.additionally_id" << emp.additionally_id;
        adds[emp.additionally_id] = add;
    }

    app.rootContext()->setContextProperty("meddiator", this);
    app.rootContext()->setContextProperty("countryModel", &countryModel);
    app.rootContext()->setContextProperty("employeeModel", &empModel);
}

QStringList Meddiator::getEmployee(int rowIndex)
{
    QStringList list;
    Employee emp = empModel.getEmp(rowIndex);
    Additionally add = adds[emp.additionally_id];
    qDebug() << "emp.id_add"<< emp.additionally_id <<"address:" <<add.address;
    list << emp.firstName << emp.lastName << add.address << add.phone << add.maritalStatus;

    return list;
}

QList<int> Meddiator::getCountries(int rowIndex)
{
    Employee emp = empModel.getEmp(rowIndex);
    Additionally add = adds[emp.additionally_id];

    return add.codeCountries;
}

bool Meddiator::updateEmployee(int rowIndex, QStringList empList, QList<int> codeCountries)
{
    Employee emp = empModel.getEmp(rowIndex);
    emp.firstName = empList.at(0);
    emp.lastName = empList.at(1);
    Additionally add = adds[emp.additionally_id];
    add.address = empList.at(2);
    add.phone = empList.at(3);
    add.maritalStatus = empList.at(4);
    add.codeCountries = codeCountries;

    QSqlError error = manager.execUpdateEmployee({emp, add});
    if (error.isValid()) {
        return false;
    }

    empModel.updateEmp(rowIndex, emp);
    adds[emp.additionally_id] = add;

    return true;
}

bool Meddiator::saveEmployee(const QStringList &empList, const QList<int> &codeCountries)
{
    Employee emp;
    emp.firstName = empList.at(0);
    emp.lastName = empList.at(1);
    Additionally add;
    add.address = empList.at(2);
    add.phone = empList.at(3);
    add.maritalStatus = empList.at(4);
    add.codeCountries = codeCountries;

    QSqlError error = manager.execInsertEmployee({emp, add});
    if(error.isValid()) {
        return false;
    }
    QPair<Employee, Additionally> newPairEmp = manager.execSelectLastEmp();
    Employee newEmp = newPairEmp.first;
    Additionally newAdd = newPairEmp.second;
    empModel.insertEmp(newEmp);
    adds[newEmp.additionally_id] = newAdd;

    return true;
}

bool Meddiator::deleteEmployee(int rowIndex)
{
    Employee emp = empModel.getEmp(rowIndex);
    int idEmp = emp.id;
    int idAdd = emp.additionally_id;

    QSqlError error = manager.execDeleteEmployee(idEmp, idAdd);
    if (error.isValid()) {
        return false;
    }
    empModel.deleteEmp(rowIndex);
    adds.remove(emp.additionally_id);

    return true;
}