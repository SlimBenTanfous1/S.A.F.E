#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QtSql>
#include <QSqlDatabase>


class connection
{

public:
    connection();
    bool creaetconnection();
    void closeconnection();
    bool Ouvrirconnection();
    void on_ExporterButton_clicked();
    QSqlDatabase db ;
};

#endif // CONNECTION_H
