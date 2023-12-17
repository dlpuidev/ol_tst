#include "country_storage.h"

CountryStorage::CountryStorage(int mcc, const QString& code, const QString& name, int mnc_length)
    : mcc(mcc), code(code), name(name), mnc_length(mnc_length)
{}

CountryStorage::~CountryStorage()
{}

//setters

void CountryStorage::setMcc(int newMcc)
{
    mcc = newMcc;
}

void CountryStorage::setCode(const QString& newCode)
{
    code = newCode;
}

void CountryStorage::setName(const QString& newName)
{
    name = newName;
}

void CountryStorage::setMncLength(int newLength)
{
    mnc_length = newLength;
}

// getters

int CountryStorage::getMcc() const
{
    return mcc;
}

QString CountryStorage::getCode() const
{
    return code;
}

QString CountryStorage::getName() const
{
    return name;
}

int CountryStorage::getMncLength() const
{
    return mnc_length;
}
