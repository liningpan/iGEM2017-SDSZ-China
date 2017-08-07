#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include "ftd2xx.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->getData->setDisabled(true);
    cd = new ccdDevice("12345678",this);
    ld = new LedDevice("A501JYU4",this);
    if(cd->open()&&ld->open()){
        ui->connectButton->setDisabled(true);
        ui->setDirButton->setDisabled(false);
    }else{
        ui->connectButton->setDisabled(false);
        ui->setDirButton->setDisabled(true);
    }
    m_chart = new QChart;
    ui->customPlot->setChart(m_chart);
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 2000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,65535);
    axisY->setTitleText("Intensity level");
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->legend()->hide();
    m_chart->setTitle("Data from ccd");

    cdr = new CcdDataReceiver(m_series,this);
    cdr->open(QIODevice::WriteOnly);

    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(on_new_file_triggered()));
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(on_settings_triggered()));
    scan = false;
    //count = 0;
}
void MainWindow::on_connectButton_clicked(){
    if(cd->open()&&ld->open()){
        ui->connectButton->setDisabled(true);
        ui->setDirButton->setDisabled(false);
    }else{
        ui->connectButton->setDisabled(false);
        ui->setDirButton->setDisabled(true);
    }
}
void MainWindow::on_new_file_triggered(){
    qDebug()<<"new";
}
void MainWindow::on_settings_triggered(){
    qDebug()<<"Setting";
    SettingsDialog* sd = new SettingsDialog(this);
    sd->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    cd->stop();
    cdr->close();
}


void MainWindow::on_getData_clicked()
{
    if(isScan()){
        cd->stop();
        scan = false;
    }
    else{
        cd->start(cdr,0.5);
        ui->getData->setText("Stop");
        scan = true;
    }
}

void MainWindow::on_ledSwitch_clicked(){
    bool condition = ld->trigger();
    if(condition){
        ui->ledSwitch->setText("Turn Off");
    }else{
        ui->ledSwitch->setText("Turn On");
    }
}

void MainWindow::on_setDirButton_clicked(){
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Set Directory"), QDir::fromNativeSeparators(ds.getDir())));
    if (!directory.isEmpty()) {
        ui->getData->setDisabled(false);
        ds.setDir(directory);
        qDebug() <<ds.getDir();
    }
}
