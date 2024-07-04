#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ambulance.h"
#include "connexion.h"
#include "QTableView"
#include"QRegularExpressionValidator"
#include <QMessageBox>
#include <QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
#include <QQuickItem>
#include "webaxwidget.h"
#include <QQuickView>
#include <QQmlContext>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QSettings>
//QR code

#include "qrcode.hpp"

//arduino
#include"gps_arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ambulance A;
    Arduino B;
    ui->setupUi(this);
    ui->ambu_TableView->setModel(A.afficher());
    ui->ambu_label_Stats->setText("Medicaliser: " + QString::number(0) + "\nNon Medicaliser: " + QString::number(0));
    //ui->ambu_combo_immatriculation->setModel(A.afficher_immatriculation());
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
    ui->ambu_WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ambu_push_Ajouter_clicked() //ajoute
{
    bool error_immatriculation= false;
    bool error_altitude=false;
    bool error_longitude=false;


    QRegularExpressionValidator *validator_immatriculation = new QRegularExpressionValidator(QRegularExpression("[0-9]+"),this);

    QString immatriculation=ui->ambu_line_immatriculation->text(); //immat
    ui->ambu_line_immatriculation->setMaxLength(9);
    ui->ambu_line_immatriculation->setValidator(validator_immatriculation);
    //controle de saisie de immatriculation
    if (!ui->ambu_line_immatriculation->hasAcceptableInput())
                  error_immatriculation= true;
                        if (error_immatriculation == true)
                             {
                                  QMessageBox::critical(nullptr, QObject::tr("immatriculation not valid"),
                                        QObject::tr("immatriculation non valid \n"
                                                  "click sur ok ."), QMessageBox::Ok);
                               }
        else{
            error_immatriculation= false;


    QRegularExpressionValidator *validator_altitude = new QRegularExpressionValidator(QRegularExpression("[0.0-9.0]+"),this);
    QString altitude=ui->ambu_line_altitude->text(); //altitude
    ui->ambu_line_altitude->setMaxLength(12);

    ui->ambu_line_altitude->setValidator(validator_altitude);
    //controle de saisie de altitude
    if (!ui->ambu_line_altitude->hasAcceptableInput())
                  error_altitude= true;
                        if (error_altitude == true)
                             {
                                  QMessageBox::critical(nullptr, QObject::tr("altitude not valid "),
                                        QObject::tr("altitude non valid \n"
                                                  "click sur ok ."), QMessageBox::Ok);
                               }
        else{
            error_altitude=false ;

         QRegularExpressionValidator *validator_longitude = new QRegularExpressionValidator(QRegularExpression("[0.0-9.0]+"),this);
         QString longitude=ui->ambu_line_longitude->text(); // longitude
         ui->ambu_line_longitude->setMaxLength(12);

         ui->ambu_line_longitude->setValidator(validator_longitude);
          //controle de saisie de longitude
          if (!ui->ambu_line_longitude->hasAcceptableInput())
                          error_longitude= true;
                                if (error_longitude == true)
                                     {
                                          QMessageBox::critical(nullptr, QObject::tr("longitude not valid "),
                                                QObject::tr("longitude non valid \n"
                                                          "click sur ok ."), QMessageBox::Ok);
                                       }
                else{
                   error_longitude=false;


        QString etat=ui->ambu_combo_etat->currentText();
        QString type=ui->ambu_combo_type->currentText();


   ambulance A(immatriculation,altitude,longitude,etat,type);
    bool test=A.ajouter();
    ui->ambu_TableView->setModel(A.afficher());
    if(test)
    {
        ui->ambu_Label_GestionInfo->setText("Ajout Effectué");
        ui->ambu_TableView->setModel(A.afficher());
        ui->ambu_combo_immatriculation->setModel(A.afficher_immatriculation());

    }
    else
    {
        ui->ambu_Label_GestionInfo->setText("Ajout non effectué");
    }
}
}
}
}

void MainWindow::on_ambu_push_Modifier_clicked() //modifie
{
    QString immatriculation=ui->ambu_line_immatriculation->text();
    QString altitude=ui->ambu_line_altitude->text();
    QString longitude=ui->ambu_line_longitude->text();
    QString etat=ui->ambu_combo_etat->currentText();
    QString type=ui->ambu_combo_type->currentText();
    ambulance A(immatriculation,altitude,longitude,type,etat);
    bool test=A.modifierA();
    ui->ambu_TableView->setModel(A.afficher());

    if(test)
    {
        ui->ambu_Label_GestionInfo->setText("Modification effectué");
        ui->ambu_TableView->setModel(A.afficher());
        ui->ambu_combo_immatriculation->setModel(A.afficher_immatriculation());
}
    else
    {
        ui->ambu_Label_GestionInfo->setText("Modification non effectué");
    }
}

void MainWindow::on_ambu_push_Supprimer_clicked()// supprime
{
    ambulance A;
    A.setimmatriculation(ui->ambu_line_immatriculation->text());
    bool test2=A.supprimer(A.getimmatriculation());
    if(test2)
    {
        ui->ambu_Label_GestionInfo->setText("Suppression effectué");
        ui->ambu_TableView->setModel(A.afficher());
        ui->ambu_combo_immatriculation->setModel(A.afficher_immatriculation());

    }
    else
    {
        ui->ambu_Label_GestionInfo->setText("Suppression non effectué");
    }
}

void MainWindow::on_ambu_push_Tri_type_clicked() // tri ambu
{
    ambulance A;
    ui->Perso_Label_ListeInfo->setText("Tri par type effectué");
    ui->ambu_TableView->setModel(A.tri_type());
}

void MainWindow::on_ambu_line_Recherche_textChanged(const QString &arg1) //recherche
{
    ambulance A;
    A.clearTable(ui->ambu_TableView);
    A.cherche_immatriculation(ui->ambu_TableView,arg1);
}

void MainWindow::on_ambu_push_ExportPDF_clicked() // export pdf
{
    QPdfWriter pdf("C:/Users/ihebb/Desktop/ProjetCpp/ambulance_crud/ListeAmbulances.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/ihebb/Desktop/ProjetCpp/ambulance_crud/ListeAmbulances.pdf"));
    painter.drawText(3000,1500,"LISTE DES AMBULANCES");
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 11));
    painter.drawText(300,3300,"immatriculation");
    painter.drawText(2800,3300,"etat");
    painter.drawText(4800,3300,"latitude");
    painter.drawText(6800,3300,"type");
    painter.drawText(8800,3300,"longitude");
    QSqlQuery query;

    query.prepare("select IMMATRICULATION,ETAT,GPS_LATITUDE,TYPE,GPS_LONGITUDE from AMBULANCE");
    query.exec();
    while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
             painter.drawText(2800,i,query.value(1).toString());
              painter.drawText(4800,i,query.value(2).toString());
               painter.drawText(6800,i,query.value(3).toString());
                painter.drawText(8800,i,query.value(4).toString());
                i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ihebb/Desktop/ProjetCpp/ambulance_crud/ListeAmbulances.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }

}

void MainWindow::on_ambu_combo_immatriculation_currentIndexChanged(int ) //combo bar roule
{
    int immatriculation=ui->ambu_combo_immatriculation->currentText().toInt();
    QString immatricule_1=QString::number(immatriculation);
            QSqlQuery query ;
            query.prepare("SELECT * FROM AMBULANCE where IMMATRICULATION='"+immatricule_1+"'");
            if(query.exec())
            {
                while (query.next())
                {
                    ui->ambu_line_immatriculation->setText(query.value(0).toString());
                    ui->ambu_combo_type->setCurrentText(query.value(1).toString());
                    ui->ambu_line_altitude->setText(query.value(2).toString());
                    ui->ambu_combo_etat->setCurrentText(query.value(3).toString());
                    ui->ambu_line_longitude->setText(query.value(4).toString());
                }}
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Error "),
                                          QObject::tr("ECHEC DE chargement"), QMessageBox::Cancel);
                }
}

void MainWindow::on_ambu_push_affiche_imatriculation_clicked()//affichage les ambu dans combo
{
   ambulance A;
    ui->ambu_combo_immatriculation->setModel(A.afficher_immatriculation());

}

void MainWindow::on_aller_gestiondesambulance_clicked() //depalce a gestion d ambu
{
    ui->Ambulance->setCurrentIndex(1);
}

void MainWindow::on_aller_listedesambulances_clicked() // a liste des ambu
{
    ui->Ambulance->setCurrentIndex(2);

}

void MainWindow::on_aller_map_clicked() // a map
{
    ui->Ambulance->setCurrentIndex(4);

}

void MainWindow::on_ambu_push_affiche_imatriculation_map_clicked() //affiche les immat dans combo
{
    ambulance A;
     ui->ambu_combo_immatriculation_map->setModel(A.afficher_immatriculation());
}

void MainWindow::on_ambu_combo_immatriculation_map_currentIndexChanged(int ) // immat change
{
    QString x,y ;
    int immatriculation=ui->ambu_combo_immatriculation_map->currentText().toInt();
    QString immatricule_1=QString::number(immatriculation);
            QSqlQuery query ;
            query.prepare("SELECT * FROM AMBULANCE where IMMATRICULATION='"+immatricule_1+"'");

            if(query.exec())
            {
                while (query.next())
                { x=(query.value(2).toString());
                    y=query.value(4).toString();

                    ui->ambu_WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/@'"+x+"','"+y+"',13z");

                    ui->ambu_line_immatriculation_2->setText(query.value(0).toString());
                    ui->ambu_combo_type_2->setCurrentText(query.value(1).toString());
                    ui->ambu_line_altitude_2->setText(query.value(2).toString());
                    ui->ambu_combo_etat_2->setCurrentText(query.value(3).toString());
                    ui->ambu_line_longitude_2->setText(query.value(4).toString());
                }}
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Error "),
                                          QObject::tr("ECHEC DE chargement"), QMessageBox::Cancel);
                }





}

void MainWindow::ambu_choix_pie() //statistique
{
    QChartView *chartView;
    QSqlQuery q1, q2 ,q3;
    qreal tot = 0, c1 = 0, c2 = 1, c3 = 0;
    q1.prepare("SELECT * FROM TRANSPORTER");
    q1.exec();
    q2.prepare("SELECT T.IMMATRICULATION FROM TRANSPORTER T JOIN AMBULANCE A ON T.IMMATRICULATION = A.IMMATRICULATION WHERE A.TYPE = 'medicaliser'");
    q2.exec();
    q3.prepare("SELECT T.IMMATRICULATION FROM TRANSPORTER T JOIN AMBULANCE A ON T.IMMATRICULATION = A.IMMATRICULATION WHERE A.TYPE = 'non medicaliser'");
    q3.exec();
    while (q1.next()) {
        tot++;
    }
    while (q2.next()) {
        c1++;
    }
    while (q3.next()) {
        c2++;
    }
    c2 = (tot - c1);
    c3 = (tot - c2) / tot;
    QPieSeries *series = new QPieSeries();
    series->append("Medicaliser", c2);
    series->append("Non Medicaliser", c3);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);

    chartView = new QChartView(chart, ui->ambu_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(550, 350);
    chartView->show();

}

void MainWindow::on_ambu_push_UpdateStats_clicked() // update stat
{
    ambu_choix_pie();
            show();
}

void MainWindow::on_aller_statistique_clicked() // a page stat
{
    ui->Ambulance->setCurrentIndex(3);

}



void MainWindow::on_ambu_TableView_clicked(const QModelIndex &index) // Qr code gene
{

    QString text =" Immatriculation:"+ ui->ambu_TableView->model()->data(ui->ambu_TableView->model()->index(ui->ambu_TableView->currentIndex().row(),0)).toString()
                  +" \n Latitude: "+ui->ambu_TableView->model()->data(ui->ambu_TableView->model()->index(ui->ambu_TableView->currentIndex().row(),2)).toString()
                  +" \n Longitude: "+ui->ambu_TableView->model()->data(ui->ambu_TableView->model()->index(ui->ambu_TableView->currentIndex().row(),4)).toString()
                  +"\n Etat: "+ui->ambu_TableView->model()->data(ui->ambu_TableView->model()->index(ui->ambu_TableView->currentIndex().row(),3)).toString()
                  +" \n Type: "+ui->ambu_TableView->model()->data(ui->ambu_TableView->model()->index(ui->ambu_TableView->currentIndex().row(),1)).toString();

          //text="user data";
          using namespace qrcodegen;
            // Create the QR Code object
            QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
            qint32 sz = qr.getSize();
            QImage im(sz,sz, QImage::Format_RGB32);
              QRgb black = qRgb(  0,  0,  0);
              QRgb white = qRgb(255,255,255);
            for (int y = 0; y < sz; y++)
              for (int x = 0; x < sz; x++)
                im.setPixel(x,y,qr.getModule(x, y) ? black : white );
            ui->ambu_qr_code->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );


}

void MainWindow::on_ambu_Gps_clicked() //gps ajoute page
{

ambulance A ;
Arduino B ;
QString X,Y;
//----------------------------------------//
//----------------------------------------//
//----------------------------------------//
//----------------------------------------//
//----------------------------------------//
X="36.9";
//----------------------------------------//
Y="10.2";
QSerialPort serial;


serial.setPortName("COM5"); // Replace "COM1" with the name of the port where the Arduino is connected
serial.setBaudRate(QSerialPort::Baud9600);
serial.setDataBits(QSerialPort::Data8);
serial.setParity(QSerialPort::NoParity);
serial.setStopBits(QSerialPort::OneStop);
//----------------------------------------//
//----------------------------------------//
//----------------------------------------//

if (!serial.open(QIODevice::ReadWrite))
{
    qWarning() << "Failed to open port" << serial.portName() << ":" << serial.errorString();
    return;

}
ui->ambu_line_longitude->setText(X);
ui->ambu_line_altitude->setText(Y);
QString data="";
 data =data+ serial.readAll();

    qDebug() << "Received data:" << X <<Y;
 /*while (true)
{
    if (serial.waitForReadyRead(1000))
    {

            ui->latLabel->setText(data);

}

}*/
}


void MainWindow::on_ambu_Gps_2_clicked() // gps update
{
    Arduino B;
    QSerialPort serial;
    QString X,Y;
    X="36.9";
    Y="10.2";
    serial.setPortName("COM5"); // Replace "COM1" with the name of the port where the Arduino is connected
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if (!serial.open(QIODevice::ReadWrite))
    {
        qWarning() << "Failed to open port" << serial.portName() << ":" << serial.errorString();
        return;
    }
    //--------------------------------------------------------------//
    ui->ambu_line_longitude_2->setText(X);
    ui->ambu_line_altitude_2->setText(Y);
    while (true)
    {
        if (serial.waitForReadyRead(10000))
        {
            QString data="";
             data =data+ serial.readAll();
            QString data="";
             data =data+ B.read_from_arduino();
                qDebug() << "Received data:" << data;


        }
    QString immatriculation=ui->ambu_line_immatriculation_2->text();
    QString altitude=ui->ambu_line_altitude_2->text();
    QString longitude=ui->ambu_line_longitude_2->text();
    QString etat=ui->ambu_combo_etat_2->currentText();
    QString type=ui->ambu_combo_type_2->currentText();
    ambulance A(immatriculation,altitude,longitude,type,etat);
    A.modifierA();

    ui->ambu_TableView->setModel(A.afficher());
}
