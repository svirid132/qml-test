#ifndef EMPMODEL_H
#define EMPMODEL_H

#include <QSqlTableModel>

class EmpModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit EmpModel(QObject *parent = nullptr);
};

#endif // EMPMODEL_H
