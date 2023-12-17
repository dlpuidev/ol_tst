#ifndef MANAGERSTORAGE_H
#define MANAGERSTORAGE_H

#include "country_storage.h"
#include "operator_storage.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>
#include <QFile>

class ManagerStorage : public QObject
{
    Q_OBJECT
public:
    explicit ManagerStorage(QObject *parent = nullptr);
    ~ManagerStorage();

    CountryStorage _countryStorage;
    OperatorStorage _operatorStorage;

    QList<CountryStorage> listCountryStorage;
    QList<OperatorStorage> listOperatorStorage;

private:
    QSqlDatabase database;

private:
    bool openDatabase();
    bool select_all_countries_from_lists();
    bool select_all_operators_from_lists();

public:
    void initialize(const QString& db, const QString& path);
    bool insert_operator(OperatorStorage& storage);
    bool update_operator(OperatorStorage& storage);
};

#endif // MANAGERSTORAGE_H
