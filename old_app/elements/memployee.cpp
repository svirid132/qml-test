#include "memployee.h"

MEmployee::MEmployee(QObject* parent) : QObject(parent)
{
}

MEmployee::~MEmployee()
{

}

QString MEmployee::firstName() const {
    return m_firstName;
}

QString MEmployee::lastName() const {
    return m_lastName;
}

QString MEmployee::address() const {
    return m_address;
}

QString MEmployee::phone() const {
    return m_phone;
}

QString MEmployee::maritalStatus() const {
    return m_maritalStatus;
}

QList<int> MEmployee::countryCodes()
{
    return m_countryCodes;
}

void MEmployee::setFirstName(const QString &s) {
    m_firstName = s;
    emit changedFirstName();
}

void MEmployee::setLastName(const QString &s) {
    m_lastName = s;
    emit changedLastName();
}

void MEmployee::setAddress(const QString &s) {
    m_address = s;
    emit changedAddress();
}

void MEmployee::setPhone(const QString &s) {
    m_phone = s;
    emit changedPhone();
}

void MEmployee::setMaritalStatus(const QString &s) {
    m_maritalStatus = s;
    emit changedMaritalStatus();
}

void MEmployee::setCountryCodes(const QList<int> &countryCodes)
{
    m_countryCodes = countryCodes;
}
