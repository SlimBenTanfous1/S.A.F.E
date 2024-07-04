#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employer.h"
#include "connection.h"
#include "patient.h"
#include <QLabel>
#include <QCalendarWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>
#include <QPdfWriter>
#include <QPainter>
#include <QTextStream>
#include <QCoreApplication>
#include <QLineEdit>
#include <QPrinter>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "smtp.h"
#include "arduino.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Employer E;
    patient P;

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(4);
    ui->tableView->setModel(E.afficher());
    ui->comboBoxId->setModel(E.afficherId());
    ui->tableView2->setModel(P.AfficherP());
    ui->ComboCinP->setModel(P.AfficherPatient_CIN());
    ui->employer_id_Edit->setValidator(new QIntValidator(0 ,99999999, this));
    ui->TelephoneEdit->setValidator(new QIntValidator(0 ,99999999, this));
    ui->CINedit->setValidator(new QIntValidator(0 ,99999999, this));
    ui->TelephonePatEdit->setValidator(new QIntValidator(0 ,99999999, this));


    int ret=A.connect_arduino();
    switch (ret) {

    case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();
            break;
        case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
            break;
        case(-1):qDebug()<< "arduino is not availble";
        }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(connect_RFID()));
}

MainWindow::MainWindow(QString e,QString n,QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString contenu="Contenu";
    ui->setupUi(this);
    ui->recipient_2->setText(e);
    ui->uname->setText("contact.s.a.f.e23@gmail.com");
    ui->passwd_2->setText("hztzgpkmlmrdigwu");
    ui->passwd_2->setEchoMode(QLineEdit::Password);


}

MainWindow::~MainWindow()
{
    delete ui;
}

// Redirection des Bouttons
//------------------------------//

void MainWindow::on_ButtonEmployer_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_ButtonAffEmp_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_StatEmp_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_ajouter_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_RetourAff_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_RetourPat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ButtonPatient_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ButtonAffPat_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_RetourAff_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_MailPat_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_3_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ButtonSms_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//

//Page De Connexion
void MainWindow::on_SeConnecterLogin_clicked()
{
    QString ADRESSE = ui->MailLogin->text();
        QString MDP = ui->MdpLineEdit->text();
        QSqlQuery query;
        QString gestion;
        QString ROLE;
        if(query.exec("SELECT * from EMPLOYER where ADRESSE='"+ADRESSE+"' and MDP='"+MDP+"'" ))
        {
            if (query.next())
            {
                gestion=query.value(5).toString();

                ui->stackedWidget->setCurrentIndex(1);
                if (gestion.compare("Administrateur")==0){
                    ui->ButtonEmployer->setEnabled(true);
                    ui->ButtonAffEmp->setEnabled(true);
                    ui->StatEmp->setEnabled(true);
                    ui->ButtonSms->setEnabled(true);
                    ui->ButtonAffPat->setEnabled(true);
                    ui->StatPat->setEnabled(true);
                    ui->MailPat->setEnabled(true);
                    ui->Button_gestion_ambu->setEnabled(true);
                    ui->Button_affich_amblance->setEnabled(true);
                    ui->ButtonPatient->setEnabled(true);
                    ui->Button_statisqtique_ambu->setEnabled(false);
                    ui->Button_Map->setEnabled(false);
                }
                if (gestion.compare("Medecin")==0){
                    ui->ButtonEmployer->setEnabled(false);
                    ui->ButtonAffEmp->setEnabled(false);
                    ui->StatEmp->setEnabled(false);
                    ui->ButtonSms->setEnabled(false);
                    ui->ButtonAffPat->setEnabled(true);
                    ui->ButtonPatient->setEnabled(true);
                    ui->StatPat->setEnabled(false);
                    ui->MailPat->setEnabled(false);
                    ui->Button_gestion_ambu->setEnabled(false);
                    ui->Button_affich_amblance->setEnabled(false);
                    ui->Button_statisqtique_ambu->setEnabled(false);
                    ui->Button_Map->setEnabled(false);


                }
                if (gestion.compare("Infirmier")==0){
                    ui->ButtonEmployer->setEnabled(false);
                    ui->ButtonAffEmp->setEnabled(false);
                    ui->StatEmp->setEnabled(false);
                    ui->ButtonSms->setEnabled(false);
                    ui->ButtonAffPat->setEnabled(true);
                    ui->ButtonPatient->setEnabled(true);
                    ui->StatPat->setEnabled(false);
                    ui->MailPat->setEnabled(false);
                   // ui->ButtonGps->setEnabled(false);
                    //ui->ButtonAffGps->setEnabled(false);
                }
                if (gestion.compare("Chauffeur")==0){
                    ui->ButtonEmployer->setEnabled(false);
                    ui->ButtonAffEmp->setEnabled(false);
                    ui->StatEmp->setEnabled(false);
                    ui->ButtonSms->setEnabled(false);
                    ui->ButtonAffPat->setEnabled(false);
                    ui->ButtonPatient->setEnabled(false);
                    ui->StatPat->setEnabled(false);
                    ui->MailPat->setEnabled(false);
                   // ui->ButtonGps->setEnabled(true);
                    //ui->ButtonAffGps->setEnabled(true);
                }/*
                if (gestion.compare("Locaux")==0){
                    ui->Main_push_Personnel->setEnabled(false);
                    ui->Main_push_Evenement->setEnabled(false);
                    ui->Main_push_Fournisseur->setEnabled(false);
                    ui->Main_push_Locaux->setEnabled(true);
                    ui->Main_push_Sponsoring->setEnabled(false);
                }
                if (gestion.compare("Sponsoring")==0){
                    ui->Main_push_Personnel->setEnabled(false);
                    ui->Main_push_Evenement->setEnabled(false);
                    ui->Main_push_Fournisseur->setEnabled(false);
                    ui->Main_push_Locaux->setEnabled(false);
                    ui->Main_push_Sponsoring->setEnabled(true);
                }*/
                QString NOM=query.value(1).toString();
                QString PRENOM=query.value(2).toString();
                QString ROLE=query.value(5).toString();
                ui->Login_label_LoginInfo->setText("Connecté: "+NOM+" "+PRENOM+"");
                ui->Main_label_LoggedAs->setText("Logged in as: "+NOM+" "+PRENOM+"\nRole: "+ROLE+"");
            }
            else
            {
                ui->Login_label_LoginInfo->setText("CIN ou Password sont incorrect");
            }
        }
}

//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//


//Tache Employer Slim Ben Tanfous
void MainWindow::on_ajouterButton_clicked()
{
    bool    error_Id=false;

    ui->    employer_id_Edit->setMaxLength(8);
    QRegularExpressionValidator * validator_Id = new QRegularExpressionValidator(QRegularExpression("[0-9]+"),this);
    int     Employer_id=ui->employer_id_Edit->text().toInt();
    QString NOM=ui->NomEdit->text();
    QString PRENOM=ui->Prenom_Edit->text();
    QString ADRESSE=ui->Adresse_Edit->text();
    int     TELEPHONE=ui->TelephoneEdit->text().toInt();
    QString ROLE=ui->RoleCombo->currentText();
    QString SEXE=ui->SexeCombo->currentText();
    QString MDP=ui->MdpEdit->text();
    QString RFID=ui->RFIDEdit->text();
    Employer E (Employer_id, NOM, PRENOM, ADRESSE, TELEPHONE, ROLE, SEXE,MDP,RFID);
    bool test=E.ajouter();
    {
         ui->tableView->setModel(E.afficher());
         ui->comboBoxId->setModel(E.afficherId());
    }
    if (test){
        QMessageBox::information(nullptr, QObject::tr("Succée"),
                                 QObject::tr("Ajout effectué\n"
                                             "Cliquer pour quitter."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                               QObject::tr("Ajout non effectué\n"
                                           "Cliquer pour quitter."),QMessageBox::Cancel);
}

//----------------------------------------------------------------------------------//

//Modification
void MainWindow::on_modifierButton_clicked()
{
    int     Employer_id=ui->employer_id_Edit->text().toInt();
    QString NOM=ui->NomEdit->text();
    QString PRENOM=ui->Prenom_Edit->text();
    QString ADRESSE=ui->Adresse_Edit->text();
    int     TELEPHONE=ui->TelephoneEdit->text().toInt();
    QString ROLE=ui->RoleCombo->currentText();
    QString SEXE=ui->SexeCombo->currentText();
     QString MDP=ui->MdpEdit->text();
     QString RFID=ui->RFIDEdit->text();
    Employer E (Employer_id, NOM, PRENOM, ADRESSE, TELEPHONE, ROLE, SEXE, MDP,RFID);
    bool test=E.modifier();{
         ui->tableView->setModel(E.afficher());
         ui->comboBoxId->setModel(E.afficherId());
    }
}
//---------------------------------------------------------------------------------//

// Suppression
void MainWindow::on_supprimerButton_clicked()
{
   Employer E;
        E.setemployer_id(ui->comboBoxId->currentText().toInt());
        bool test=E.supprimer(E.getemployer_id());
        if(test)
        {
            ui->tableView->setModel(E.afficher());
            ui->comboBoxId->setModel(E.afficherId());

        }
}
//-----------------------------------------------------------------//

void MainWindow::on_comboBoxId_currentIndexChanged(int index)
{
    int id=ui->comboBoxId->currentText().toInt();
        QString id_1=QString::number(id);
        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYER where EMPLOYER_ID='"+id_1+"'");
        if(query.exec())
        {
            while (query.next())
            {
                ui->employer_id_Edit->setText(query.value(0).toString()) ;
                ui->NomEdit->setText(query.value(1).toString()) ;
                ui->Prenom_Edit->setText(query.value(2).toString()) ;
                ui->Adresse_Edit->setText(query.value(3).toString()) ;
                ui->TelephoneEdit->setText(query.value(4).toString()) ;
                ui->RoleCombo->setCurrentText(query.value(5).toString()) ;
                ui->SexeCombo->setCurrentText(query.value(6).toString()) ;
                ui->RFIDEdit->setText(query.value(7).toString()) ;

            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Error "),
                                  QObject::tr("ECHEC DE chargement"), QMessageBox::Cancel);
        }
}
//-----------------------------------------------------------------//

//Exportation PDF
void MainWindow::on_ExporterButton_clicked(){

    QPdfWriter pdf("C:/safe/ListeEmployers.pdf");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 30));
        //painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/safe/ListeEmployers.pdf"));
        painter.drawText(3000,1500,"LISTE DES EMPLOYERS");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 50));
        //painter.drawRect(2700,200,6300,2600);
        //painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(300,3300,"EMPLOYER_ID:");
        painter.drawText(1800,3300,"NOM");
        painter.drawText(2800,3300,"PRENOM");
        painter.drawText(3800,3300,"ADRESSE");
        painter.drawText(4800,3300,"TELEPHONE");
        painter.drawText(6700,3300,"ROLE");
        painter.drawText(7700,3300,"SEXE");
        QSqlQuery query;
        query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
        time_t tt;
        struct tm* ti;
        time(&tt);
        ti=localtime(&tt);
        asctime(ti);
        painter.drawText(500,300, asctime(ti));
        query.prepare("select EMPLOYER_ID,NOM,PRENOM,ADRESSE,TELEPHONE,ROLE,SEXE from EMPLOYER");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(1800,i,query.value(1).toString());
            painter.drawText(2800,i,query.value(2).toString());
            painter.drawText(3800,i,query.value(3).toString());
            painter.drawText(4800,i,query.value(4).toString());
            painter.drawText(6700,i,query.value(5).toString());
            painter.drawText(7700,i,query.value(6).toString());
            i = i +500;
        }
        int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/safe/ListeEmployers.pdf"));
            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }


}

//---------------------------------------------------------------------------------------//

//Chercher fel Affichage
void MainWindow::on_ChercherEditEmp_textChanged(const QString &arg1)
{
    QString substring = ui->ChercherEditEmp->text();
        if ((substring != "") or !((ui->radioID->isChecked()) and (ui->radioNOM->isChecked())))
        {
                QSqlQueryModel *model = new QSqlQueryModel(this);

                QString queryText;
                if (ui->radioID->isChecked())
                queryText = "SELECT * FROM EMPLOYER WHERE EMPLOYER_ID LIKE '%" + substring + "%'";
                else if (ui->radioNOM->isChecked())
                queryText = "SELECT * FROM EMPLOYER WHERE NOM LIKE '%" + substring + "%'";
                model->setQuery(queryText);
                model->setHeaderData(0, Qt::Horizontal, QObject::tr("EMPLOYER_ID"));
                model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
                model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
                model->setHeaderData(5, Qt::Horizontal, QObject::tr("ROLE"));
                model->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
                model->setHeaderData(7, Qt::Horizontal, QObject::tr("MDP"));

                ui->tableView->setModel(model);
        }
}
//-----------------------------------------------------//

//Filtre croissant
void MainWindow::on_AZ_clicked()
{
    Employer E;
    ui->tableView->setModel(E.tri_Nom());
}
//Filtre décroissant
void MainWindow::on_ZA_clicked()
{
    Employer E;
    ui->tableView->setModel(E.tri_Nom2());
}
//-----------------------------------------------------//


//Fonction Statistique

void MainWindow::StatistiqueSexe(){

    QChartView *chartView ;
    QSqlQuery q1,q2;
    qreal tot=0,c1=0,c2=3;
    q1.prepare("SELECT * FROM TRAITER");
    q1.exec(); q2.prepare("SELECT COUNT(*) as count FROM TRAITER INNER JOIN EMPLOYER ON TRAITER.EMPLOYER_ID = EMPLOYER.EMPLOYER_ID WHERE EMPLOYER.ROLE = 'Medecin';");
    q2.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    c1=c1/tot;
    QPieSeries *series = new QPieSeries();
    series->append("Médecin",c2);
    series->append("AUTRES",c1);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart,ui->StatS);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(401,400);
    chartView->show();

}

//-----------------------------------------------------//

//Mise a jour Statistique
void MainWindow::on_Maj_clicked()
{
    StatistiqueSexe();
    show();
}

//Tache SMS
void MainWindow::on_envoyer_dialog_2_clicked()
{
    QString status;
        Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd_2->text(), "smtp.gmail.com", 465); //smtp.gmail.com
        smtp->sendMail(ui->uname->text(), ui->recipient_2->text() , ui->subjectLineEdit_2->text() ,ui->message_2->toPlainText());
        if(status == "Message sent")
            QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
void MainWindow::on_EnvoieSms_clicked()
{
   Employer E;
    QString numtel=ui->lineSms->text();
    QString msg=ui->PlainSms->toPlainText();
    E.postrequest(msg,numtel);
}
//--------------------------------------//

//Intégration ARDUINO RFID SLIM + KSON
void MainWindow::connect_RFID()

{
    ui->RFID_Label->setText("arduino detecte");
    data=A.read_from_arduino();
    QString uid = QTextCodec::codecForMib(106)->toUnicode(data);
    qDebug()<<uid;
    ui->RFID_Label->setText(uid);

    Employer E;

    if(E.rfidExists(uid))
        {
            QByteArray data1;
            data1.append('1');
            A.write_to_arduino(data1);
           //    qDebug()<<"carte existante";

            QString nom = E.rfidName(uid);
            ui->RFID_NOM->setText(nom);
           //qDebug()<<nom;

            //wui->stackedWidget->setCurrentIndex(2);
            QByteArray nomData(nom.toUtf8(), 8);
            A.write_to_arduino(nomData);
        }

    else if (!E.rfidExists(uid))
        {
            //inexistance
            QByteArray data1;

            data1.append('2');
           // QByteArray nomData1(nom.toUtf8(), 8);
            A.write_to_arduino(data1);
           // qDebug()<<"carte inexistante";

        }
}

//------------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//
//-----------------------------------------//

//Intégration Kossentini (Tache Patient)


void MainWindow::on_AjoutPat_clicked()
{
    bool    error_Id=false;

    ui->    CINedit->setMaxLength(8);
    QRegularExpressionValidator * validator_Id = new QRegularExpressionValidator(QRegularExpression("[0-9]+"),this);
    int     PATIENT_CIN=ui->CINedit->text().toInt();
    QString NOM=ui->NomPatientEdit->text();
    QString PRENOM=ui->PrenomPatEdit->text();
    int     TELEPHONE=ui->TelephoneEdit->text().toInt();
    QString MAIL=ui->MailPatEdit->text();
    QString ETAT=ui->EtatPatCombo->currentText();

    patient P (PATIENT_CIN, NOM, PRENOM, TELEPHONE, ETAT, MAIL);
    bool test=P.AjouterP();
    {
         ui->tableView2->setModel(P.AfficherP());
         ui->ComboCinP->setModel(P.AfficherPatient_CIN());
    }
    if (test){
        QMessageBox::information(nullptr, QObject::tr("Succée"),
                                 QObject::tr("Ajout effectué\n"
                                             "Cliquer pour quitter."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                               QObject::tr("Ajout non effectué\n"
                                           "Cliquer pour quitter."),QMessageBox::Cancel);
}

void MainWindow::on_ModifPat_clicked()
{

        int     PATIENT_CIN=ui->CINedit->text().toInt();
        QString NOM=ui->NomPatientEdit->text();
        QString PRENOM=ui->PrenomPatEdit->text();
        int     TELEPHONE=ui->TelephoneEdit->text().toInt();
        QString MAIL=ui->MailPatEdit->text();
        QString ETAT=ui->EtatPatCombo->currentText();

        patient P (PATIENT_CIN, NOM, PRENOM, TELEPHONE, ETAT, MAIL);
        bool test=P.ModifierP();
        {
             ui->tableView2->setModel(P.AfficherP());
             ui->ComboCinP->setModel(P.AfficherPatient_CIN());
        }

 }


void MainWindow::on_SuppPat_clicked()
{
    patient P;
         P.setCIN(ui->ComboCinP->currentText().toInt());
         bool test=P.SupprimerP(P.getCIN());
         if(test)
         {
             ui->tableView2->setModel(P.AfficherP());
             ui->ComboCinP->setModel(P.AfficherPatient_CIN());

         }
}




void MainWindow::on_ExporterPat_clicked()
{
    QPdfWriter pdf("C:/safe/ListePatients.pdf");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 30));
        //painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/safe/ListePatient.pdf"));
        painter.drawText(3000,1500,"LISTE DES EMPLOYERS");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 50));
        //painter.drawRect(2700,200,6300,2600);
        //painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(300,3300,"PATIENT_CIN:");
        painter.drawText(1800,3300,"NOM");
        painter.drawText(2800,3300,"PRENOM");
        painter.drawText(3800,3300,"TELEPHONE");
        painter.drawText(4800,3300,"ETAT");
        painter.drawText(6700,3300,"MAIL");
        QSqlQuery query;
        query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
        time_t tt;
        struct tm* ti;
        time(&tt);
        ti=localtime(&tt);
        asctime(ti);
        painter.drawText(500,300, asctime(ti));
        query.prepare("select PATIENT_CIN,NOM,PRENOM,TELEPHONE,ETAT,MAIL from PATIENT");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(1800,i,query.value(1).toString());
            painter.drawText(2800,i,query.value(2).toString());
            painter.drawText(3800,i,query.value(3).toString());
            painter.drawText(4800,i,query.value(4).toString());
            painter.drawText(6700,i,query.value(5).toString());

            i = i +500;
        }
        int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/safe/ListePatients.pdf"));
            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }
}


void MainWindow::on_Crois_clicked()
{
    patient P;
    ui->tableView2->setModel(P.tri_NomP());
}

void MainWindow::on_Decroi_clicked()
{
    patient P;
    ui->tableView2->setModel(P.tri_NomP2());
}

void MainWindow::on_ChercherPatEdit_textChanged(const QString &arg1)
{

    QString substring = ui->ChercherPatEdit->text();
        if ((substring != "") or !((ui->radioCIN->isChecked()) and (ui->radioNomP->isChecked())))
        {
                QSqlQueryModel *model = new QSqlQueryModel(this);
                QString queryText;
                if (ui->radioCIN->isChecked())
                queryText = "SELECT * FROM PATIENT WHERE PATIENT_CIN LIKE '%" + substring + "%'";
                else if (ui->radioNomP->isChecked())
                queryText = "SELECT * FROM PATIENT WHERE NOM LIKE '%" + substring + "%'";
                model->setQuery(queryText);
                model->setHeaderData(0, Qt::Horizontal, QObject::tr("PATIENT_CIN"));
                model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
                model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
                model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
                ui->tableView2->setModel(model);
        }
}



void MainWindow::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
            ui->MdpEdit->setEchoMode(QLineEdit::Normal);
            ui->ConfirmerEdit->setEchoMode(QLineEdit::Normal);
        } else {
            ui->MdpEdit->setEchoMode(QLineEdit::Password);
            ui->ConfirmerEdit->setEchoMode(QLineEdit::Password);
        }
}

void MainWindow::on_CheckMdp_stateChanged(int etat)
{
    if (etat == Qt::Checked) {
            ui->MdpLineEdit->setEchoMode(QLineEdit::Normal);
            //ui->ConfirmerEdit->setEchoMode(QLineEdit::Normal);
        } else {
            ui->MdpLineEdit->setEchoMode(QLineEdit::Password);
            //ui->ConfirmerEdit->setEchoMode(QLineEdit::Password);
        }
}

