#include "employee.h"

Employee::Employee(QObject *parent) :
    QObject(parent),
    m_additionalEmp(new AdditionalEmp(this))
{

}
