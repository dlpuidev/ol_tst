#ifndef COUNTRIES_STORAGE_H
#define COUNTRIES_STORAGE_H

#include <QString>
#include <QDebug>
#include <QSqlDatabase>

#include <stdlib.h>
#include <string.h>
#include <iostream>

class CountryStorage
{
public:
    CountryStorage(int mcc, const QString& code, const QString& name, int mnc_length);
    ~CountryStorage();

    //setters
    void  setMcc(int newMcc);
    void  setCode(const QString& newCode);
    void  setName(const QString& newName);
    void  setMncLength(int newLength);

    // getters
    int         getMcc(void) const;
    QString     getCode(void) const;
    QString     getName(void) const;
    int         getMncLength(void) const;

private:
    int mcc;
    QString code;
    QString name;
    int mnc_length;
};

#endif // COUNTRIES_STORAGE_H
