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
    if(c.open()&&l.open()){
        ui->connectButton->setDisabled(true);
        ui->setDirButton->setDisabled(false);
    }else{
        ui->connectButton->setDisabled(false);
        ui->setDirButton->setDisabled(true);
    }
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT( timer_timeout()) );
    timer->setInterval(100);
    scan = false;
    count = 0;
    cd= new ccdData[10];
}
void MainWindow::on_connectButton_clicked(){
    if(c.open()&&l.open()){
        ui->connectButton->setDisabled(true);
        ui->setDirButton->setDisabled(false);
    }else{
        ui->connectButton->setDisabled(false);
        ui->setDirButton->setDisabled(true);
    }
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
void MainWindow::getData(){
    bool st = c.getData(cd[count]);
    if (st){
        draw(cd[count]);
        qDebug() << count;
        count+=1;
        if(count == 10){
            ds.writeData(cd,10,QDateTime::currentDateTime());
            count = 0;
        }
    }
}
void MainWindow::timer_timeout(){
    getData();
    timer->start();

}

void MainWindow::on_getData_clicked()
{
    if(isScan()){
        timer->stop();
        ui->getData->setText("Get Data");
        if(count != 0){
            ds.writeData(cd,count,QDateTime::currentDateTime());
            count = 0;
        }
        scan = false;
    }
    else{
        getData();
        timer->start();
        ui->getData->setText("Stop");
        scan = true;
    }
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
