#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ftd2xx.h"
#include "qcustomplot.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    ui->getData->setDisabled(true);
    c.open();
    //l.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(ccdData t)
{
   QVector<double> x(3648), y(3648);
   double mx = 0;
   for (int i = 50; i < 3600; i++)
       x[i] = i, mx = max(y[i] = t.dat[i], mx);
   mx = max(mx,5000.0);
   ui->customPlot->addGraph();
   ui->customPlot->graph(0)->setData(x, y);
   ui->customPlot->xAxis->setRange(0, 3648);
   ui->customPlot->yAxis->setRange(0, mx);
   ui->customPlot->replot();
}


void MainWindow::on_getData_clicked()
{
    ccdData dat;
    bool st = c.getData(dat);
    if (st){
        draw(dat);
        ds.writeData(dat,QDateTime::currentDateTime());
    }
    //tmp outside if
}

void MainWindow::on_ledSwitch_clicked(){
    bool condition = l.trigger();
    if(condition){
        ui->ledSwitch->setText("Turn Off");
    }else{
        ui->ledSwitch->setText("Turn On");
    }
}

void MainWindow::on_setDirButton_clicked(){
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Set Directory"), QDir::homePath()));
    if (!directory.isEmpty()) {
        ui->getData->setDisabled(false);
        ds.setDir(directory);
        qDebug() <<ds.getDir();
    }
}
