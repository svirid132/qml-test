#include "m_employee.h"

M_Employee::M_Employee(QObject* parent) : QObject(parent)
{

}

M_Employee::~M_Employee()
{

}

QString M_Employee::firstName() {
    return m_firstName;
}

QString M_Employee::lastName() {
    return m_lastName;
}

QString M_Employee::address() {
    return m_address;
}

QString M_Employee::phone() {
    return m_phone;
}

QString M_Employee::maritalStatus() {
    return m_maritalStatus;
}

void M_Employee::setFirstName(const QString &s) {
    m_firstName = s;
}

void M_Employee::setLastName(const QString &s) {
    m_lastName = s;
}

void M_Employee::setAddress(const QString &s) {
    m_address = s;
}

void M_Employee::setPhone(const QString &s) {
    m_phone = s;
}

void M_Employee::setMaritalStatus(const QString &s) {
    m_maritalStatus = s;
}
