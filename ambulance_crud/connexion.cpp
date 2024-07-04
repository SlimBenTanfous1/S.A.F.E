#include "connexion.h"

connection::connection()
{

}
bool connection::creatconnection()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("source_projet");
    db.setUserName("Iheb");
    db.setPassword("houba");

    if (db.open()) test=true;
    return test;
}
void connection::closeconnection()
    {db.close();}
