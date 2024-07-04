#include "patient.h"
#include <QSqlQuery>
#include "connection.h"
#include<QMainWindow>
#include<QtDebug>
#include "mainwindow.h"


patient::patient(){

    Patient_CIN=0;
    PrenomP ="";
    NomP="";
    MailP="";
    TelephoneP=0;
    Etat="";
}

patient::patient(int Patient_CIN,QString NomP, QString PrenomP ,int TelephoneP,QString Etat,QString MailP)

{
    this->Patient_CIN=Patient_CIN;
    this->PrenomP=PrenomP;
    this->NomP=NomP;
    this->MailP=MailP;
    this->TelephoneP=TelephoneP;
    this->Etat=Etat;
}

//------------------------------------------------//
QString patient::getnomp(){return NomP;}
QString patient::getprenomp(){return PrenomP;}
QString patient::getmailp(){return MailP;}
QString patient::getetat(){return Etat;}
int patient::getCIN(){return Patient_CIN;}
int patient::gettelephoneP(){return TelephoneP;}
//------------------------------------------------//
void patient::setnomp(QString N){NomP=N;}
void patient::setprenomp(QString P){PrenomP=P;}
void patient::setmail(QString M){MailP=M;}
void patient::setCIN(int Patient_CIN){this->Patient_CIN = Patient_CIN;}
void patient::settelephoneP(int TelephoneP){this->TelephoneP = TelephoneP;}
//------------------------------------------------//

bool patient::AjouterP()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PATIENT (PATIENT_CIN,NOM,PRENOM,TELEPHONE,ETAT,MAIL)" "VALUES (:PATIENT_CIN,:NOM,:PRENOM,:TELEPHONE,:ETAT,:MAIL)");
    query.bindValue(":PATIENT_CIN", Patient_CIN);
    query.bindValue(":NOM", NomP);
    query.bindValue(":PRENOM", PrenomP);
    query.bindValue(":TELEPHONE", TelephoneP);
    query.bindValue(":ETAT", Etat);
    query.bindValue(":MAIL", MailP);
    return query.exec();
}

bool patient::ModifierP()
{
    QSqlQuery query;
    query.prepare("UPDATE PATIENT SET NOM=:NOM, PRENOM=:PRENOM, TELEPHONE=:TELEPHONE, ETAT=:ETAT, MAIL=:MAIL WHERE PATIENT_CIN=:PATIENT_CIN ");
    query.bindValue(":PATIENT_CIN", Patient_CIN);
    query.bindValue(":NOM", NomP);
    query.bindValue(":PRENOM", PrenomP);
    query.bindValue(":TELEPHONE", TelephoneP);
    query.bindValue(":ETAT", Etat);
    query.bindValue(":MAIL", MailP);
    return query.exec();
}

bool patient::SupprimerP(int Patient_CIN)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PATIENT where PATIENT_CIN=: PATIENT_CIN");
    query.bindValue(0, Patient_CIN);
    return query.exec();
}

QSqlQueryModel* patient::AfficherP()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT PATIENT_CIN,NOM,PRENOM,TELEPHONE,ETAT,MAIL FROM PATIENT ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("PATIENT_CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    return  model;
}

QSqlQueryModel* patient ::AfficherPatient_CIN()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT PATIENT_CIN FROM PATIENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PATIENT_CIN"));
    return model;
}


QSqlQueryModel* patient ::tri_NomP()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT ORDER BY NOM ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("PATIENT_CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));


    return model;
}

QSqlQueryModel* patient ::tri_NomP2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT ORDER BY NOM DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("PATIENT_CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));


    return model;
}





