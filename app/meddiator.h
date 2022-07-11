#ifndef MEDDIATOR_H
#define MEDDIATOR_H

#include <QJSEngine>
#include <QObject>
#include <sqlitemanager.h>
#include <models/countrymodel.h>
#include <models/employeemodel.h>
#include "elements/m_employee.h"
#include "dataMeddiator.h"

class QQmlApplicationEngine;

class Meddiator : public QObject
{
    Q_OBJECT
public:
    explicit Meddiator(QQmlApplicationEngine& app, QObject *parent = nullptr);
    Q_INVOKABLE QStringList getEmployee(int rowIndex);
    Q_INVOKABLE QList<int> getCountries(int rowIndex);
    Q_INVOKABLE bool updateEmployee(int rowIndex, QStringList empList, QList<int> codeCountries);
    Q_INVOKABLE bool saveEmployee(const QStringList& listEmp, const QList<int>& codeCountries);
    Q_INVOKABLE bool deleteEmployee(int rowIndex);

private:
    SQLiteManager manager;
    EmployeeModel empModel;
    CountryModel countryModel;
    QMap<int, Additionally> adds;
};

#endif // MEDDIATOR_H
