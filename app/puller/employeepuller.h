#ifndef EMPLOYEEPULLER_H
#define EMPLOYEEPULLER_H

#include <QObject>

#include <view/employee.h>

class EmployeePuller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Employee* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(Employee* source READ source WRITE setSource NOTIFY sourceChanged)

public:
    explicit EmployeePuller(QObject *parent = nullptr);
    void setTarget(Employee* target) {
        if (m_target == target) {
            return;
        }
        m_target = target;
        emit targetChanged();
    }
    void setSource(Employee* source) {
        if (m_source == source) {
            return;
        }
        m_source = source;
        emit sourceChanged();
    }
    Employee* target() {
        return m_target;
    }
    Employee* source() {
        return m_source;
    }
    Q_INVOKABLE void pull() {
        m_target->setId(m_source->id());
        m_target->setFirstName(m_source->firstName());
        m_target->setLastName(m_source->lastName());
        AdditionalEmp* addEmpSource = m_source->additionalEmp();
        AdditionalEmp* addEmpTarget = m_target->additionalEmp();
        addEmpTarget->setId(addEmpSource->id());
        addEmpTarget->setAddress(addEmpSource->address());
        addEmpTarget->setPhone(addEmpSource->phone());
        addEmpTarget->setMaritalStatus(addEmpSource->maritalStatus());
        addEmpTarget->setCountryCodes(addEmpSource->countryCodes());
    }


signals:
    void targetChanged();
    void sourceChanged();

private:
    Employee* m_target;
    Employee* m_source;
};

#endif // EMPLOYEEPULLER_H
