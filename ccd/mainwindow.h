#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ccd.h"
#include "led.h"
#include "datastore.h"
#include <QTimer>
#include "settingsdialog.h"

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
    void timer_timeout();
    void on_new_file_triggered();
    void on_settings_triggered();
public slots:
    void setChanged(mySettings ms);
private:
    QTimer* timer;
    Ui::MainWindow *ui;
    ccd c;
    ccdData* cd;
    led l;
    dataStore ds;
    void draw(ccdData t);
    void getData();
    bool scan;
    int count;
    void writeToFile(bool stop);
};

#endif // MAINWINDOW_H
