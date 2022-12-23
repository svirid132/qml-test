#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "basecontroller.h"

#include <QObject>
#include <model/employee.h>
#include <QSqlError>
#include <sqlitemanager.h>

class EmployeeController : public BaseController
{
    Q_PROPERTY(Employee* target READ target WRITE setTarget NOTIFY targetChanged)

    Q_OBJECT
public:
    explicit EmployeeController(QObject *parent = nullptr);

    void setTarget(Employee* target) {
        if (m_target == target) {
            return;
        }
        m_target = target;
        emit targetChanged();
    }
    Employee* target() {
        return m_target;
    }

    Q_INVOKABLE void fullDelete() {
        int empId = m_target->id();
        int addEmpId = m_target->additionalEmp()->id();
        QSqlError error = manager.execDeleteEmployee(empId, addEmpId);
        if (error.isValid()) {
            execOnError();
            return;
        }
        execOnAccess();
    }

    Q_INVOKABLE void getAdditionalEmployee() {
        QList<QPair<SQLite::Employee, SQLite::Additionally>> emps = manager.execSelectEmployees();
        int addEmpId = m_target->additionalEmp()->id();
        AdditionalEmp* addEmp = m_target->additionalEmp();
        for (const QPair<SQLite::Employee, SQLite::Additionally>& emp : qAsConst(emps)) {
            if (addEmpId == emp.second.id) {
                addEmp->setId(emp.second.id);
                addEmp->setAddress(emp.second.address);
                addEmp->setPhone(emp.second.phone);
                addEmp->setMaritalStatus(emp.second.maritalStatus);
                addEmp->setCountryCodes(emp.second.codeCountries);
            }
        }
    }

    Q_INVOKABLE void post() {
        SQLite::Employee emp;
        emp.id = m_target->id();
        emp.firstName = m_target->firstName();
        emp.lastName = m_target->lastName();
        AdditionalEmp* ui_additional = m_target->additionalEmp();
        emp.additionally_id = ui_additional->id();
        SQLite::Additionally additional;
        additional.id = ui_additional->id();
        additional.address = ui_additional->address();
        additional.maritalStatus = ui_additional->maritalStatus();
        additional.phone = ui_additional->phone();
        additional.codeCountries = ui_additional->countryCodes();

        QPair<SQLite::Employee, SQLite::Additionally> empPair(emp, additional);
        QSqlError error = manager.execInsertEmployee(empPair);

        if (error.isValid()) {
            execOnError();
            return;
        }
        execOnAccess();
    }

    Q_INVOKABLE void put() {
        SQLite::Employee emp;
        emp.id = m_target->id();
        emp.firstName = m_target->firstName();
        emp.lastName = m_target->lastName();
        AdditionalEmp* ui_additional = m_target->additionalEmp();
        emp.additionally_id = ui_additional->id();
        SQLite::Additionally additional;
        additional.id = ui_additional->id();
        additional.address = ui_additional->address();
        additional.maritalStatus = ui_additional->maritalStatus();
        additional.phone = ui_additional->phone();
        additional.codeCountries = ui_additional->countryCodes();

        QPair<SQLite::Employee, SQLite::Additionally> empPair(emp, additional);
        QSqlError error = manager.execUpdateEmployee(empPair);

        if (error.isValid()) {
            execOnError();
            return;
        }
        execOnAccess();
    }

signals:
    void targetChanged();

private:
    Employee* m_target;
    SQLite::SQLiteManager manager = SQLite::SQLiteManager::getInstance();
};

#endif // EMPLOYEECONTROLLER_H
