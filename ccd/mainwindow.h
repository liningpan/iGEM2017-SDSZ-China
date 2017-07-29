#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ccd.h"
#include "led.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_getData_clicked();
    void on_ledSwitch_clicked();
private:
    Ui::MainWindow *ui;
    ccd c;
    led l;
    void draw(ccdData t);
};

#endif // MAINWINDOW_H
