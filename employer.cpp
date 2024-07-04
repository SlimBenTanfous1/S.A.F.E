#include "employer.h"
#include <QSqlQuery>
#include "connection.h"
#include<QMainWindow>
#include<QtDebug>
#include "mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QHttpMultiPart>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include "arduino.h"

Employer::Employer(){

    Employer_id=0;
    Prenom ="";
    Nom="";
    Adresse="";
    Telephone=0;
    Role="";
    Sexe="";
    Mdp="";
    Rfid="";

}

Employer::Employer(int Employer_id,QString Prenom, QString Nom, QString Adresse,int Telephone,QString Role,QString Sexe,QString Mdp,QString Rfid)
{
    this->Employer_id=Employer_id;
    this->Prenom=Prenom;
    this->Nom=Nom;
    this->Adresse=Adresse;
    this->Telephone=Telephone;
    this->Role=Role;
    this->Sexe=Sexe;
    this->Mdp=Mdp;
    this->Rfid=Rfid;
}
//------------------------------------------------//
//Getters
QString Employer::getnom(){return Nom;}
QString Employer::getprenom(){return Prenom;}
QString Employer::getadresse(){return Adresse;}
QString Employer::getrole(){return Role;}
QString Employer::getsexe(){return Sexe;}
QString Employer::getmdp(){return Mdp;}
QString Employer::getrfid(){return Rfid;}
int Employer::getemployer_id(){return Employer_id;}
int Employer::gettelephone(){return Telephone;}
//------------------------------------------------//
//Setters
void Employer::setnom(QString N){Nom=N;}
void Employer::setprenom(QString P){Prenom=P;}
void Employer::setadresse(QString A){Adresse=A;}
void Employer::setrole(QString R){Role=R;}
void Employer::setsexe(QString S){Sexe=S;}
void Employer::setmdp(QString M){Mdp=M;}
void Employer::setrfid(QString I){Rfid=I;}
void Employer::setemployer_id(int Employer_id){this->Employer_id = Employer_id;}
void Employer::settelephone(int Telephone){this->Telephone = Telephone;}
//------------------------------------------------//

bool Employer::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYER (EMPLOYER_ID,NOM,PRENOM,ADRESSE,TELEPHONE,ROLE,SEXE,MDP,RFID)" "VALUES (:EMPLOYER_ID,:NOM,:PRENOM,:ADRESSE,:TELEPHONE,:ROLE,:SEXE,:MDP,:RFID)");
    query.bindValue(":EMPLOYER_ID", Employer_id);
    query.bindValue(":NOM", Nom);
    query.bindValue(":PRENOM", Prenom);
    query.bindValue(":ADRESSE", Adresse);
    query.bindValue(":TELEPHONE", Telephone);
    query.bindValue(":ROLE", Role);
    query.bindValue(":SEXE",Sexe);
    query.bindValue(":MDP",Mdp);
    query.bindValue(":RFID",Rfid);
    return query.exec();
}

bool Employer::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYER SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, TELEPHONE=:TELEPHONE, ROLE=:ROLE, SEXE=:SEXE, MDP=:MDP, RFID=:RFID WHERE EMPLOYER_ID=:EMPLOYER_ID ");
    query.bindValue(":EMPLOYER_ID", Employer_id);
    query.bindValue(":NOM", Nom);
    query.bindValue(":PRENOM", Prenom);
    query.bindValue(":ADRESSE", Adresse);
    query.bindValue(":TELEPHONE", Telephone);
    query.bindValue(":ROLE", Role);
    query.bindValue(":SEXE", Sexe);
    query.bindValue(":MDP", Mdp);
    query.bindValue(":RFID",Rfid);
    return query.exec();
}

bool Employer::supprimer(int Employer_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYER where EMPLOYER_ID= :EMPLOYER_ID");
    query.bindValue(0, Employer_id);
    return query.exec();
}

QSqlQueryModel* Employer::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT EMPLOYER_ID,NOM,PRENOM,ADRESSE,TELEPHONE,ROLE,SEXE FROM EMPLOYER ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("EMPLOYER_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ROLE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
    //model->setHeaderData(7, Qt::Horizontal, QObject::tr("MDP"));


    return  model;
}

QSqlQueryModel* Employer ::afficherId()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT EMPLOYER_ID from EMPLOYER");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("EMPLOYER_ID"));
    return model;
}


QSqlQueryModel* Employer ::tri_Nom()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYER ORDER BY NOM ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("EMPLOYER_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ROLE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}

QSqlQueryModel* Employer ::tri_Nom2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYER ORDER BY NOM DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("EMPLOYER_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ROLE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}


void Employer::postrequest(QString smsmsg,QString phonenumber){

    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("https://api.orange.com/smsmessaging/v1/outbound/tel%3A%2B322804/requests") ) );
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("Authorization", "Bearer eyJ2ZXIiOiIxLjAiLCJ0eXAiOiJKV1QiLCJhbGciOiJFUzM4NCIsImtpZCI6ImRzRUN2TDVaTENQbTl1R081RHltUjZCRTdMcnFGak5hX1VKbl9Ody1zdVUifQ.eyJhcHBfbmFtZSI6IlFUIFByb2plY3QiLCJzdWIiOiJwSTc1SlNYeVNZMThRdk9jcWl5MU0xQzB3N1RwVlliVyIsImlzcyI6Imh0dHBzOlwvXC9hcGkub3JhbmdlLmNvbVwvb2F1dGhcL3YzIiwiZXhwIjoxNjgzMDI0MTIzLCJhcHBfaWQiOiJ3QXBZNU05MDBYU21XcVpUIiwiaWF0IjoxNjgzMDIwNTIzLCJjbGllbnRfaWQiOiJwSTc1SlNYeVNZMThRdk9jcWl5MU0xQzB3N1RwVlliVyIsImp0aSI6IjQ1YWI2MjRhLTYwYjktNGQ2NS1hYjk2LTU0MWI2ZWIyODk5MSJ9.opE6W8Ijdl7fxLbt9OJk_5fQIXtrSJw3Ml-PIAeSy4i8_5fSrm2MP3Wc9obIzwcYVglCLbSy1CIpe3fleUn8Ef2CkPaJ8ie3vZZRVhzaihRoRM_ZtvBxNSAbSTlNzyXg");
    QJsonObject msg;
    msg["message"] = smsmsg;
    QJsonObject obj;
    obj["address"] = "tel:+216"+phonenumber;
    obj["senderAddress"] = "tel:+322804";
    obj["outboundSMSTextMessage"] = msg;
    QJsonObject body;
    body["outboundSMSMessageRequest"] = obj;
    QJsonDocument doc(body);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = mgr.post(req,data);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success" <<reply->readAll();
        delete reply;
    }
    else {
        qDebug() << "Failure" <<reply->errorString() << reply->error();
        delete reply;
    }

}

bool Employer::rfidExists(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT RFID FROM EMPLOYER WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            return true;
        }




    return false;
}



    /* QSqlQuery query;
    //QString cin_string= QString::number();


   //requette sql
   query.prepare("SELECT * FROM EMPLOYER WHERE RFID=:uid");

   //saisi des donnee
   query.bindValue(":uid",uid);


   //execution de la requette
   return query.exec();*/

QString Employer::rfidName(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT NOM FROM EMPLOYER WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            return query.value(0).toString();
        }
        return "";
}



