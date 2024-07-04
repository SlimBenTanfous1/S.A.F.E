#include "connection.h"
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QtSql>
#include <QSqlDatabase>



connection::connection(){}

bool connection::creaetconnection()
{

    bool test=false;
    QSqlDatabase  db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("SLIM");
    db.setPassword("slim23");

    if (db.open())
        test=true;
    return test;

}


void connection::closeconnection()
    {db.close();}

bool connection::Ouvrirconnection(){
    if (db.open())
        return true ;
    else
        return false;
}


