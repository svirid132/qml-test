#ifndef MEDDIATOR_H
#define MEDDIATOR_H

#include <QJSEngine>
#include <QObject>
#include <sqlitemanager.h>
#include <models/countrymodel.h>
#include <models/employeemodel.h>
#include "elements/memployee.h"
#include "dataMeddiator.h"
#include "elements/memployee.h"

class QQmlApplicationEngine;

/**
 * @brief The Meddiator class - связывет модели, sqlite и ui для общего выполненияы.
 */
class Meddiator : public QObject
{
    Q_OBJECT

public:
    explicit Meddiator(QQmlApplicationEngine& app, QObject *parent = nullptr);
    /**
     * @brief updateMEmployee - обновить структуру данных MEmployee
     * @param rowIndex - строка в модели empModel
     * @param memp - данные, которые будут обновлены
     */
    Q_INVOKABLE void updateMEmployee(int rowIndex, MEmployee* memp);
    /**
     * @brief getCountries - вернуть странны в которых был сотрудник
     * @param rowIndex - строка в модели empModel
     * @return коды стран
     */
    Q_INVOKABLE QList<int> getCountries(int rowIndex);
    /**
     * @brief updateEmployee - обновить данные сотрудника в бд
     * @param rowIndex - строка в модели empModel
     * @param memp - новые данные для обновления в бд
     * @return успешность операции
     */
    Q_INVOKABLE bool updateEmployee(int rowIndex, MEmployee* memp);
    /**
     * @brief saveEmployee - сохранить данные сотрудника в бд
     * @param memp - новые данные для сохранения в бд
     * @return успешность операции
     */
    Q_INVOKABLE bool saveEmployee(MEmployee* memp);
    /**
     * @brief deleteEmployee - удалить сотрудника
     * @param rowIndex - строка в модели empModel
     * @return успешность операции
     */
    Q_INVOKABLE bool deleteEmployee(int rowIndex);

private:
    EmployeeModel empModel;
    CountryModel countryModel;
    QMap<int, Additionally> adds;
};

#endif // MEDDIATOR_H
