#ifndef SQLRENAMER_H
#define SQLRENAMER_H

#include <QPair>

class QStringList;
struct Employee;
struct Additionally;

class SQLRenamer
{
public:
    SQLRenamer();

    QStringList updateEmployee(const QPair<Employee, Additionally>& employee);
    QStringList deleteEmployee(int idEmployee, int idAdditionally);

private:
    int replace(QString& origin, const QString& before, const QString& after, int from = 0);

};

#endif // SQLRENAMER_H
