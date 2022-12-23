#ifndef COUNTRYTABLE_H
#define COUNTRYTABLE_H

#include <QAbstractTableModel>
#include <QObject>
#include <sqlitemanager.h>

struct CountryData {
    int code;
    QString country;
    bool isCheck = false;
};

/*
 * Класс предоставляет модель посещенных стран
 * */

class CountryTable : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QList<int> codeCountriesChecked READ codeCountriesChecked WRITE setCodeCountriesChecked NOTIFY codeCountriesCheckedChanged)

public:
    explicit CountryTable(QObject *parent = nullptr);

    //Измение выбора check для страны. Посещал или нет сотрудник страну.
    /**
     * @brief setCheck - выбор страны. Изменение check страны.
     * @param row - строка странны
     * @param check - измениен посещения страны
     */
    Q_INVOKABLE void setCheck(int row, bool check);

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //
    /**
     * @brief setCheckCounties - Вставка всех посещенных стран. Меняется только check.
     * @param codes - коды стран.
     */
    QList<int> codeCountriesChecked() {
        QList<int> checked;
        std::for_each(countryDatas.begin(), countryDatas.end(), [&checked](const CountryData& country) {
            if (country.isCheck) {
                checked.append(country.code);
            }
        });

        return checked;
    }
    void setCodeCountriesChecked(const QList<int>& codes);
signals:
    void codeCountriesCheckedChanged();

private:
    QList<CountryData> countryDatas;
    SQLite::SQLiteManager sqliteManager = SQLite::SQLiteManager::getInstance();
    enum CountryRoles {
        codeRole = Qt::UserRole,
        nameRole = Qt::UserRole + 1,
        isCheckRole = Qt::UserRole + 2
    };
};

#endif // CountryTable_H
