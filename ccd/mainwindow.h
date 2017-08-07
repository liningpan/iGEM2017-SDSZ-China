#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ccddevice.h"
#include "ccddatareceiver.h"
#include "leddevice.h"
#include "datastore.h"
#include <QTimer>
#include "settingsdialog.h"
#include "settingsmanager.h"
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isScan(){ return scan; }
private slots:
    void on_getData_clicked();
    void on_ledSwitch_clicked();
    void on_setDirButton_clicked();
    void on_connectButton_clicked();
    void on_new_file_triggered();
    void on_settings_triggered();
private:
    QTimer* timer;
    Ui::MainWindow *ui;
    ccdDevice *cd;
    CcdDataReceiver *cdr;
    LedDevice *ld;
    QChart *m_chart;
    QLineSeries *m_series;
    SettingsManager * setman;
    dataStore ds;
    //void draw(ccdData t);
    //void getData();
    bool scan;
    //int count;
    //void writeToFile(bool stop);
};

#endif // MAINWINDOW_H
