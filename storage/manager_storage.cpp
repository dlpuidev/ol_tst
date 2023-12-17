#include "manager_storage.h"

ManagerStorage::ManagerStorage(QObject *parent) : QObject(parent)
    , _countryStorage(0,"","",0)
    , _operatorStorage("","","")
{}

ManagerStorage::~ManagerStorage()
{
    database.close();
}

void ManagerStorage::initialize(const QString& db, const QString& path)
{
    try
    {
        QFile file(path);
        if (!file.exists()) {
            qDebug() << "Database file does not exist!";
        }
        else
        {
            database = QSqlDatabase::addDatabase(db);
            database.setDatabaseName(path);

            bool isOpen = openDatabase();
            if(isOpen)
            {
                select_all_countries_from_lists();
                select_all_operators_from_lists();
            }
        }
    }
    catch (const std::exception& ex)
    {
        qWarning() << "Connect to db" << db << ":" << path << ", exception:" << ex.what();
    }
}

bool ManagerStorage::openDatabase()
{
    if (!database.open()) {
        qDebug() << "Failed to open the database!";
        qDebug() << "Error details:" << database.lastError().text();
        return false;
    }

    qDebug() << "Database opened successfully!";
    return true;
}

bool ManagerStorage::select_all_countries_from_lists()
{
    QSqlQuery query;

    bool result = false;

    query.prepare( "SELECT * FROM countries ORDER BY countries.name ASC");

    result = query.exec();

    if(result == true)
    {
        while(query.next())
        {
            _countryStorage.setName(query.value("name").toString());
            _countryStorage.setMcc(query.value("mcc").toInt());
            _countryStorage.setCode(query.value("code").toString());
            _countryStorage.setMncLength(query.value("mnc_length").toInt());

            listCountryStorage.append(_countryStorage);
        }
        qDebug() << "Query select_all_countries_from_lists is Succses!";
    }
    else
    {
        qCritical() << "Query is Faild!";
    }

    return result;
}

bool ManagerStorage::select_all_operators_from_lists()
{
    QSqlQuery query;

    bool result = false;

    query.prepare( "SELECT * FROM operators ORDER BY operators.name ASC");

    result = query.exec();

    if(result == true)
    {
        while(query.next())
        {
            _operatorStorage.setName(query.value("name").toString());
            _operatorStorage.setMcc(query.value("mcc").toString());
            _operatorStorage.setMnc(query.value("mnc").toString());

            listOperatorStorage.append(_operatorStorage);
        }

        qDebug() << "Query select_all_operators_from_lists is Succses!";

    }
    else
    {
        qCritical() << "Query is Faild!";
    }

    return result;
}

bool ManagerStorage::insert_operator(OperatorStorage& storage)
{
    QSqlQuery query;
    query.prepare("INSERT INTO operators (name, mcc, mnc) VALUES (:name, :mcc, :mnc)");
    query.bindValue(":name", storage.getName());
    query.bindValue(":mcc", storage.getMcc());
    query.bindValue(":mnc", storage.getMnc());

    bool result = query.exec();

    if (result) {
        qDebug() << "Query insert_operator is successful!";
    } else {
        qCritical() << "Query failed!";
    }

    return result;
}

bool ManagerStorage::update_operator(OperatorStorage& storage)
{
    QSqlQuery query;
    query.prepare("UPDATE operators SET name = :name WHERE mcc = :mcc AND mnc = :mnc");
    query.bindValue(":name", storage.getName());
    query.bindValue(":mcc", storage.getMcc());
    query.bindValue(":mnc", storage.getMnc());

    bool result = query.exec();

    if (result) {
        qDebug() << "Query update_operator is successful!";
    } else {
        qCritical() << "Query failed!";
    }

    return result;
}
