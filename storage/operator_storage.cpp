#include "operator_storage.h"

OperatorStorage::OperatorStorage(const QString& mcc, const QString& mnc, const QString& name)
    : mcc(mcc), mnc(mnc), name(name)
{}

OperatorStorage::~OperatorStorage()
{}

//setters

void OperatorStorage::setMcc(const QString& newMcc)
{
    mcc = newMcc;
}

void OperatorStorage::setMnc(const QString& newMnc)
{
    mnc = newMnc;
}

void OperatorStorage::setName(const QString& newName)
{
    name = newName;
}


// getters

QString OperatorStorage::getMcc() const
{
    return mcc;
}

QString OperatorStorage::getMnc() const
{
    return mnc;
}

QString OperatorStorage::getName() const
{
    return name;
}
