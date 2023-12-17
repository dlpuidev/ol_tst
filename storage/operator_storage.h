#ifndef COUNTRIESSTORAGE_H
#define COUNTRIESSTORAGE_H

#include <QString>
#include <QDebug>
#include <QSqlDatabase>

#include <stdlib.h>
#include <string.h>
#include <iostream>


class OperatorStorage
{
public:
    OperatorStorage(const QString& mcc, const QString& mnc, const QString& name);
    ~OperatorStorage();

    //setters
    void        setMcc(const QString& newMcc);
    void        setMnc(const QString& newMnc);
    void        setName(const QString& newName);

    // getters
    QString     getMcc(void) const;
    QString     getMnc(void) const;
    QString     getName(void) const;

private:
    QString     mcc;
    QString     mnc;
    QString     name;

};

#endif // COUNTRIESSTORAGE_H
