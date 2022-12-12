#ifndef SELECTEDUSERCONTROLLER_H
#define SELECTEDUSERCONTROLLER_H

#include <QObject>

#include <models/employeemodel.h>
#include <QtQml/qqml.h>
#include <elements/memployee.h>

class SelectedUserController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(EmployeeModel* model READ employeeModel WRITE setEmployeeModel NOTIFY employeeModelChanged)
    Q_PROPERTY(MEmployee* employee READ employee WRITE setEmployee NOTIFY employeeChanged)

public:
    explicit SelectedUserController(QObject *parent = nullptr);
    void setEmployeeModel(EmployeeModel* model) {
        empModel = model;
        emit employeeModelChanged();
    };
    EmployeeModel* employeeModel() {
        return empModel;
    }
    MEmployee* employee() { return emp; }
    void setEmployee(MEmployee* emp) {
        this->emp = emp;
        emit employeeChanged();
    }

signals:
    void employeeModelChanged();
    void employeeChanged();

private:
    EmployeeModel* empModel = nullptr;
    MEmployee* emp = new MEmployee();
};

#endif // SELECTEDUSERCONTROLLER_H
