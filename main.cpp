#include "employer.h"
#include <QApplication>
#include <QMessageBox>
#include <connection.h>
#include "mainwindow.h"
#include <QtDebug>
#include <QtSql>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test=c.creaetconnection();
   MainWindow w ;
    if (test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Base de Donnée ouverte"),
        QObject::tr("Connection réussite. \n" "Cliquer annuler pour quitter"),
                                 QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Base de Donnée"),
                              QObject::tr("Connexion échoué.\n"
                                          "Cliquer annuler pour quitter."),
                QMessageBox::Cancel);
    }
    return a.exec();
}
