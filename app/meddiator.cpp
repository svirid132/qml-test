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
        adds[emp.additionally_id] = add;
    }

    app.rootContext()->setContextProperty("meddiator", this);
    app.rootContext()->setContextProperty("countryModel", &countryModel);
    app.rootContext()->setContextProperty("employeeModel", &empModel);
}

void Meddiator::updateMEmployee(int rowIndex, MEmployee *memp)
{
    Employee emp = empModel.getEmp(rowIndex);
    Additionally add = adds[emp.additionally_id];

    memp->setFirstName(emp.firstName);
    memp->setLastName(emp.lastName);
    memp->setAddress(add.address);
    memp->setPhone(add.phone);
    memp->setMaritalStatus(add.maritalStatus);
    memp->setCountryCodes(add.codeCountries);
}

QList<int> Meddiator::getCountries(int rowIndex)
{
    Employee emp = empModel.getEmp(rowIndex);
    Additionally add = adds[emp.additionally_id];

    return add.codeCountries;
}

bool Meddiator::updateEmployee(int rowIndex, MEmployee* memp)
{
    Employee emp = empModel.getEmp(rowIndex);
    emp.firstName = memp->firstName();
    emp.lastName = memp->lastName();
    Additionally add = adds[emp.additionally_id];
    add.address = memp->address();
    add.phone = memp->phone();
    add.maritalStatus = memp->maritalStatus();
    add.codeCountries = memp->countryCodes();

    QSqlError error = manager.execUpdateEmployee({emp, add});
    if (error.isValid()) {
        return false;
    }

    empModel.updateEmp(rowIndex, emp);
    adds[emp.additionally_id] = add;

    return true;
}

bool Meddiator::saveEmployee(MEmployee* memp)
{
    Employee emp;
    emp.firstName = memp->firstName();
    emp.lastName = memp->lastName();
    Additionally add;
    add.address = memp->address();
    add.phone = memp->phone();
    add.maritalStatus = memp->maritalStatus();
    add.codeCountries = memp->countryCodes();

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
