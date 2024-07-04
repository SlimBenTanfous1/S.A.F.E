#include "ambulance.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>



ambulance::ambulance()
{
immatriculation=" ";
longitude=" ";
altitude=" ";
type=" ";
etat=" ";
}

ambulance::ambulance(QString immatriculation,QString longitude,QString altitude,QString type,QString etat)
{
    this->immatriculation=immatriculation ;
    this->longitude=longitude ;
    this->altitude=altitude ;
    this->type=type;
    this->etat=etat;
}


QString ambulance::getimmatriculation(){return immatriculation ;}
QString ambulance::getaltitude(){return altitude;}
QString ambulance::getlongitude(){return longitude ;}
QString ambulance::gettype(){return type ;}
QString ambulance::getetat(){return etat ;}



void ambulance::setimmatriculation(QString immatriculation) {    this->immatriculation=immatriculation ;}
void ambulance::setaltitude(QString altitude){this->altitude=altitude ;}
void ambulance::setlongitude(QString longitude){    this->longitude=longitude ;}
void ambulance::settype(QString type){  this->type=type;}
void ambulance::Setetat(QString etat) {this->etat=etat;}




bool ambulance::ajouter()
{
     QSqlQuery query;
     query.prepare("INSERT INTO AMBULANCE(IMMATRICULATION,ETAT,GPS_LATITUDE,TYPE,GPS_LONGITUDE)" "VALUES (:immatriculation,:type,:altitude,:etat,:longitude)");
     query.bindValue(":immatriculation", immatriculation);
     query.bindValue(":altitude", altitude);
     query.bindValue(":longitude", longitude);
     query.bindValue(":type", type);
     query.bindValue(":etat", etat);
     return query.exec();
}

bool ambulance::supprimer(QString imm)
{
    QSqlQuery query;
    query.prepare("DELETE FROM AMBULANCE where IMMATRICULATION= :immatriculation");
    query.bindValue(":immatriculation",imm);
    return query.exec();
}
QSqlQueryModel* ambulance::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel ();
    model->setQuery("select * from ambulance");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Immatriculation"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("longitude"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("latitude"));
    return model;
}
bool ambulance::modifierA()
{
    QSqlQuery query;
    query.prepare("UPDATE AMBULANCE SET ETAT=:etat, GPS_LATITUDE=:altitude, TYPE=:type, GPS_LONGITUDE=:longitude where IMMATRICULATION= :immatriculation");
    query.bindValue(":immatriculation", immatriculation);
    query.bindValue(":altitude", altitude);
    query.bindValue(":longitude", longitude);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    return query.exec();
}

QSqlQueryModel* ambulance::afficher_immatriculation()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT IMMATRICULATION from AMBULANCE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("immatriculation"));
    return model;
}


QSqlQueryModel * ambulance::tri_type()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * from AMBULANCE order by TYPE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Immatriculation"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("longitude"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("latitude"));
    return model;

}


void ambulance::cherche_immatriculation(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from AMBULANCE where regexp_like(IMMATRICULATION,:immatriculation);");
    query->bindValue(":immatriculation",x);
    if(x==0)
    {
        query->prepare("select * from AMBULANCE;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}

void ambulance::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);

}
