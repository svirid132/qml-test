#ifndef BASEEMPLOYEECONTROLLER_H
#define BASEEMPLOYEECONTROLLER_H

#include "basecontroller.h"

#include <QJSValue>
#include <QObject>
#include <QSqlError>
#include <sqlitemanager.h>

#include <view/employee.h>

#include <models/countrymodel.h>

class BaseEmployeeController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY(Employee* targetEmp READ targetEmp WRITE setTargetEmp NOTIFY targetEmpChanged)
    Q_PROPERTY(CountryModel* targetCntrModel READ targetCntrModel WRITE setTargetCntrModel NOTIFY targetCntrModelChanged)

public:
    explicit BaseEmployeeController(QObject *parent = nullptr);

    void setTargetEmp(Employee* target) {
        if (m_targetEmp == target) {
            return;
        }
        m_targetEmp = target;
        emit targetEmpChanged();
    }
    void setTargetCntrModel(CountryModel* targetCntrModel) {
        if (m_targetCntrModel == targetCntrModel) {
            return;
        }
        m_targetCntrModel = targetCntrModel;
        emit targetCntrModelChanged();
    }

    Employee* targetEmp() {
        return m_targetEmp;
    }
    CountryModel* targetCntrModel() {
        return m_targetCntrModel;
    }

signals:
    void targetEmpChanged();
    void targetCntrModelChanged();

protected:
    Employee* m_targetEmp;
    CountryModel* m_targetCntrModel;
};

#endif // BASEEMPLOYEECONTROLLER_H
