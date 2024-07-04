#ifndef PATIENT_H
#define PATIENT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include "mainwindow.h"

class patient
{

    QString NomP;
    QString PrenomP;
    QString Etat;
    QString MailP;
    int Patient_CIN,TelephoneP;

public:
    patient();
    patient(int,QString,QString,int,QString,QString);

   QString getnomp();
   QString getprenomp();
   QString getmailp();
   QString getetat();
   int getCIN();
   int gettelephoneP();

   void setnomp(QString);
   void setprenomp(QString);
   void setmail(QString);
   void setetat(QString);
   void setCIN(int);
   void settelephoneP(int);


    bool AjouterP();
    QSqlQueryModel * AfficherPatient_CIN();
    QSqlQueryModel * AfficherP();
    bool SupprimerP(int);
    bool ModifierP();
    QSqlQueryModel * tri_NomP();
    QSqlQueryModel * tri_NomP2();
};

#endif // PATIENT_H
