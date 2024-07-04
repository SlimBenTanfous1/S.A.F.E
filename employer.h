#ifndef EMPLOYER_H
#define EMPLOYER_H
#include <QString>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include "mainwindow.h"

class Employer
{
    QString Nom;
    QString Prenom;
    QString Role;
    QString Adresse;
    QString Sexe;
    QString Mdp;
    QString Rfid;
    int Employer_id,Telephone;

public:
    Employer();
    Employer(int,QString,QString,QString,int,QString,QString,QString,QString);

   QString getnom();
   QString getprenom();
   QString getadresse();
   int getemployer_id();
   int gettelephone();
   QString getrole();
   QString getsexe();
   QString getmdp();
   QString getrfid();

   void setnom(QString);
   void setprenom(QString);
   void setadresse(QString);
   void setemployer_id(int);
   void settelephone(int);
   void setrole(QString);
   void setsexe(QString);
   void setmdp(QString);
   void setrfid(QString);

    bool ajouter();
    QSqlQueryModel * afficherId();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tri_Nom();
    QSqlQueryModel * tri_Nom2();
    void postrequest(QString smsmsg,QString phonenumber);
    bool rfidExists(QString);
    QString rfidName(QString);



};

#endif // EMPLOYER_H
