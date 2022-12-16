#ifndef PUTEMPLOYEECONTROLLER_H
#define PUTEMPLOYEECONTROLLER_H

#include "baseemployeecontroller.h"

#include <QJSValue>
#include <QObject>
#include <QSqlError>
#include <sqlitemanager.h>

#include <view/employee.h>

#include <models/countrymodel.h>

class PutEmployeeController : public BaseEmployeeController
{
    Q_OBJECT

public:
    explicit PutEmployeeController(BaseEmployeeController *parent = nullptr);

    Q_INVOKABLE void put() {
        SQLite::Employee emp;
        emp.id = m_targetEmp->id();
        emp.firstName = m_targetEmp->firstName();
        emp.lastName = m_targetEmp->lastName();
        AdditionalEmp* ui_additional = m_targetEmp->additionalEmp();
        emp.additionally_id = ui_additional->id();
        SQLite::Additionally additional;
        additional.id = ui_additional->id();
        additional.address = ui_additional->address();
        additional.maritalStatus = ui_additional->maritalStatus();
        additional.phone = ui_additional->phone();
        additional.codeCountries = m_targetCntrModel->codeCountriesChecked();

        QPair<SQLite::Employee, SQLite::Additionally> empPair(emp, additional);
        QSqlError error = sqliteManager.execUpdateEmployee(empPair);

        if (error.isValid()) {
            if (m_onError.isCallable()) {
                m_onError.call();
            }
            return;
        }

        if (m_onAccess.isCallable()) {
            m_onAccess.call();
        }
    }

private:
    SQLite::SQLiteManager sqliteManager = SQLite::SQLiteManager::getInstance();
};

#endif // PUTEMPLOYEECONTROLLER_H
