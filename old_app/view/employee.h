#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <view/additionalemp.h>

#include <QObject>

class Employee : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(AdditionalEmp* additionalEmp READ additionalEmp WRITE setAdditionalEmp NOTIFY additionalEmpChanged)

public:
    explicit Employee(QObject *parent = nullptr);
    void setId(int id) {
        if (m_id == id) {
            return;
        }
        m_id = id;
        emit idChanged();
    }
    void setFirstName(const QString& firstName) {
        if (m_firstName == firstName) {
            return;
        }
        m_firstName = firstName;
        emit firstNameChanged();
    }
    void setLastName(const QString& lastName) {
        if (m_lastName == lastName) {
            return;
        }
        m_lastName = lastName;
        emit lastNameChanged();
    }
    void setAdditionalEmp(AdditionalEmp* additionalEmp) {
        if (m_additionalEmp == additionalEmp) {
            return;
        }
        m_additionalEmp = additionalEmp;
        emit additionalEmpChanged();
    }
    QString firstName() {
        return m_firstName;
    }
    QString lastName() {
        return m_lastName;
    }
    AdditionalEmp* additionalEmp() {
        return m_additionalEmp;
    }

signals:
    void idChanged();
    void firstNameChanged();
    void lastNameChanged();
    void additionalEmpChanged();

private:
    int m_id = -1;
    QString m_firstName;
    QString m_lastName;
    AdditionalEmp* m_additionalEmp;
};

#endif // EMPLOYEE_H
