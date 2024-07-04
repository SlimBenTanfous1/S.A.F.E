#ifndef AMBULANCE_H
#define AMBULANCE_H
#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class ambulance
{
public:
    ambulance();
    ambulance(QString,QString,QString,QString,QString);


    QString getimmatriculation();
    QString getlongitude();
    QString getaltitude();
    QString gettype();
    QString getetat();



    void setimmatriculation(QString);
    void setlongitude(QString);
    void setaltitude(QString);
    void settype(QString);
    void Setetat(QString);





    bool ajouter();
    bool modifierA();
    bool supprimer(QString imm);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_immatriculation();
    QSqlQueryModel* tri_type();



    void clearTable(QTableView * table);
    void cherche_immatriculation(QTableView *table, QString x);

private:
    QString immatriculation;
    QString longitude;
    QString altitude;
    QString type;
    QString etat;

};

#endif // AMBULANCE_H
