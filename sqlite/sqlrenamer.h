#ifndef SQLRENAMER_H
#define SQLRENAMER_H

#include <QPair>
#include <QStringList>

struct Employee;
struct Additionally;

/**
 * @brief The SQLRenamer class - класс, предназначенный для считывания sql файлов.
 * И заполнению считаных данных новыми данными.
 */
class SQLRenamer
{
public:
    SQLRenamer();

    /**
     * @brief updateEmployee - возращает команды для обновления сотрудника
     * @param employee сотрудник
     * @return команды
     */
    QStringList updateEmployee(const QPair<Employee, Additionally>& employee);
    /**
     * @brief deleteEmployee - возращает команды для удаления сотрудника
     * @param idEmployee - id сотурдника
     * @param idAdditionally - id дополнение сотрдника
     * @return команды
     */
    QStringList deleteEmployee(int idEmployee, int idAdditionally);
    /**
     * @brief insertEmployee - возращает команды для добавления сотрудника
     * @param employee - сотрудник
     * @return команды
     */
    QStringList insertEmployee(const QPair<Employee, Additionally>& employee);

private:
    /**
     * @brief replace - заменяет строку новыми данными
     * @param origin - исходная строка
     * @param before - старые данные
     * @param after - новые данные
     * @param from - заменять с какого символа
     * @return возращает число откуда была проведена замена
     */
    int replace(QString& origin, const QString& before, const QString& after, int from = 0);
};

#endif // SQLRENAMER_H
