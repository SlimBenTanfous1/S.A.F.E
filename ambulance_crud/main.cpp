#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test=c.creatconnection();
    MainWindow w;


    if (test==true)
    {
       w.show();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("databas is not open"),
                              QObject::tr("connection failed \n"
                                          "click cancel to exit ."), QMessageBox::Cancel);
    }

    return a.exec();
}
