#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employer.h"
#include "connection.h"
#include <QLineEdit>
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
#include <QToolBox>
#include "arduino.h"
QT_BEGIN_NAMESPACE

namespace Ui {class MainWindow;}

QT_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QString,QString,QMainWindow *parent = nullptr);
    ~MainWindow();

private slots:

    //Les Bouttons de la tache employer dans le menu
    void on_ajouterButton_clicked();

    void on_ButtonEmployer_clicked();

    void on_StatEmp_clicked();
    //----------------------------------------//
    //----------------------------------------//
    //----------------------------------------//
    void on_Home_ajouter_2_clicked();

    void on_ButtonAffEmp_clicked();

    void on_RetourAff_clicked();

    void on_comboBoxId_currentIndexChanged(int index);

    void on_modifierButton_clicked();

    void on_supprimerButton_clicked();

    void on_ExporterButton_clicked();

    void on_pushButton_2_clicked();

    void on_ChercherEditEmp_textChanged(const QString &arg1);

    void on_AZ_clicked();

    void on_ZA_clicked();

    void StatistiqueSexe();

    void connect_RFID();



    void on_Maj_clicked();

    void on_AjoutPat_clicked();

    void on_ModifPat_clicked();

    void on_RetourPat_clicked();

    void on_ButtonPatient_clicked();

    void on_SuppPat_clicked();

    void on_ButtonAffPat_clicked();

    void on_RetourAff_2_clicked();

    void on_EnvoieSms_clicked();

    void on_ExporterPat_clicked();

    void on_envoyer_dialog_2_clicked();

    void on_pushButton_clicked();

    void on_MailPat_clicked();

    void on_pushButton_3_clicked();

    void on_ButtonSms_clicked();

    void on_Crois_clicked();

    void on_Decroi_clicked();

    void on_ChercherPatEdit_textChanged(const QString &arg1);

    //void StatistiquePatient();

    //void on_MajP_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_CheckMdp_stateChanged(int arg1);

    void on_SeConnecterLogin_clicked();

private:
    Ui::MainWindow *ui;
    QString RFID="";
    Arduino A;
    QByteArray data;
    QToolButton *m_eyeButton;
};

#endif // MAINWINDOW_H
