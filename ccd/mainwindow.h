#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ccddatatablemodel.h"
#include "ccddevice.h"
#include "ccdrawdatareceiver.h"
#include "ccdseriesdatareciver.h"
#include "ccdseriesmanager.h"
#include "leddevice.h"
#include <QTimer>
#include "settingsdialog.h"

#include "settingsmanager.h"
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QVXYModelMapper>
#include <QTableView>
#include <QDebug>

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
public slots:
    void tableDataChanged();
private slots:
    void newFile();
    //void settings();
    void openFile();
    void seriesClicked();

    void on_BoardOneUp_clicked();
    void on_BoardOneStop_clicked();
    void on_BoardOneDown_clicked();

    void on_BoardTwoUp_clicked();
    void on_BoardTwoStop_clicked();
    void on_BoardTwoDown_clicked();

    void on_PumpIn_clicked();
    void on_PumpStop_clicked();
    void on_PumpOut_clicked();

    void on_interval_currentTextChanged(QString);
    void on_testTime_valueChanged(int);
    void on_singleTestButton_clicked();
    void on_startButton_clicked();
    void on_newTest_clicked();
    void on_saveButton_clicked();

    void on_set0T_clicked();
    void on_set100T_clicked();
    void on_mode_currentIndexChanged(int);
    void on_lightSwitch_clicked();

    void on_browseButton_clicked();

private:
    QTimer* timer;
    Ui::MainWindow *ui;
    ccdDevice *cd;
    CcdSeriesManager* csm;
    SeriesData* currentSeries;
    XYAxis averageAxis;
    XYAxis rawAxis;
    LedDevice *ld;
    QChart *m_chart;
    SettingsManager * setman;
    bool scan;
    bool lightOn;
    int currentRow;
    int sernum;
    DataMode mode;

    void setRawDataMode();
    void setAverageDataMode();
};

#endif // MAINWINDOW_H
