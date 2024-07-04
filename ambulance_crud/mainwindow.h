#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QValidator>
#include <QRegExp>
#include <QRegExpValidator>
#include <QVariant>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include "webaxwidget.h"
#include <QMainWindow>
#include "gps_arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connect_GPS();

    void on_ambu_push_Ajouter_clicked();

    void on_ambu_push_Modifier_clicked();

    void on_ambu_push_Supprimer_clicked();


    void on_ambu_push_Tri_type_clicked();



    void on_ambu_line_Recherche_textChanged(const QString &arg1);

    void on_ambu_push_ExportPDF_clicked();

    void on_ambu_combo_immatriculation_currentIndexChanged(int index);


    void on_ambu_push_affiche_imatriculation_clicked();

    void on_aller_gestiondesambulance_clicked();

    void on_aller_listedesambulances_clicked();

    void on_aller_map_clicked();

    void ambu_choix_pie();



    void on_ambu_push_affiche_imatriculation_map_clicked();

    void on_ambu_combo_immatriculation_map_currentIndexChanged(int index);

    void on_ambu_push_UpdateStats_clicked();

    void on_aller_statistique_clicked();


    void on_ambu_TableView_clicked(const QModelIndex &index);

    void on_ambu_Gps_clicked();

    void on_ambu_Gps_2_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray data; // variable contenant les données reçues

       Arduino B; // objet temporaire

signals:

    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
};
#endif // MAINWINDOW_H
