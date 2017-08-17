#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIODevice>
#include "ftd2xx.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    setman(new SettingsManager(this)),
    csm(new CcdSeriesManager(DataMode::Average,this)),
    scan(false),
    currentRow(0),
    sernum(0)
{
    ui->setupUi(this);
    cd = new ccdDevice("FTT5B0N6",this);
    ld = new LedDevice("AD01V9AS",this);
    if(cd->open()&&ld->open()){
        qDebug()<<"connect";
    } else {
        qDebug()<<"not connect";
    }
    ld->setLightCondition(true);
    m_chart = new QChart;
    ui->chartView->setChart(m_chart);
    m_chart->setTitle("Data from ccd");
    axisX = new QValueAxis(this);
    axisX->setRange(0, setman->getTestTime());
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    axisY = new QValueAxis(this);
    axisY->setRange(0,65535);
    axisY->setTitleText("Intensity level");
    axisY->setLabelFormat("%d");

    ui->testTime->setValue(setman->getTestTime());
    float val = setman->getInterval();
    int len = ui->interval->count();
    for(int i = 0; i < len; i ++){
        if(val == ui->interval->itemText(i).toFloat()){
            ui->interval->setCurrentIndex(i);
        }
    }

    ui->pathLineEdit->setText(setman->getDefaultDir());

    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(newFile()));
    //connect(ui->actionSetting,SIGNAL(triggered(bool)),this,SLOT(settings()));
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(on_saveButton_clicked()));

    currentSeries = csm->newTest();
    m_chart->addSeries(currentSeries->series);
    ui->dataTableView->setModel(currentSeries->model);
    cd->setDevice(csm->getCurrentDevice());
    //connect(currentSeries->series,SIGNAL(clicked(QPointF)),this,SLOT(seriesClicked(currentSeries->series)));

    m_chart->setAxisX(axisX);
    m_chart->setAxisY(axisY);
    currentSeries->series->attachAxis(axisX);
    currentSeries->series->attachAxis(axisY);

}
MainWindow::~MainWindow()
{
    delete ui;
    cd->stop();
    ld->stop();
    cd->close();
    ld->close();
    //csdr->close();
}


void MainWindow::newFile(){
    m_chart->removeAllSeries();
    csm->deleteOldData();
    on_newTest_clicked();
}

/*void MainWindow::settings(){
    SettingsDialog *sd = new SettingsDialog(this);
    connect(sd,SIGNAL(settingsChanged(mySettings)),this,SLOT(settingsChanged(mySettings)));
    sd->show();
}*/

void MainWindow::openFile(){
    qDebug()<<"open";
}

void MainWindow::on_BoardOneUp_clicked(){
    ld->setBoardOneUp();
}

void MainWindow::on_BoardOneStop_clicked(){
    ld->setBoardOneStop();
}

void MainWindow::on_BoardOneDown_clicked(){
    ld->setBoardOneDown();
}

void MainWindow::on_BoardTwoUp_clicked(){
    ld->setBoardTwoUp();
}

void MainWindow::on_BoardTwoStop_clicked(){
    ld->setBoardTwoStop();
}

void MainWindow::on_BoardTwoDown_clicked(){
    ld->setBoardTwoDown();
}

void MainWindow::on_interval_currentTextChanged(QString s){
    setman->setInterval(s.toFloat());
}

void MainWindow::on_testTime_valueChanged(int value){
    qDebug()<<value;
    setman->setTestTime(value);
    axisX->setMax(value);
}

void MainWindow::on_singleTestButton_clicked(){
    cd->testOnce();
}

void MainWindow::on_startButton_clicked(){
    if(scan){
        cd->stop();
        ui->startButton->setText("Start");
    } else {
        cd->start(setman->getInterval(),setman->getTestTime());
        ui->startButton->setText("Stop");
    }
    scan = !scan;
}

void MainWindow::on_newTest_clicked(){
    currentSeries = csm->newTest();
    m_chart->addSeries(currentSeries->series);
    ui->dataTableView->setModel(currentSeries->model);
    currentSeries->series->attachAxis(axisX);
    currentSeries->series->attachAxis(axisY);
    //connect(currentSeries->series,currentSeries->series->clicked,this,seriesClicked);
    //cd->setDevice(csm->getCurrentDevice());
}
void MainWindow::seriesClicked(QXYSeries *s){
    qDebug()<<s;
}

void MainWindow::on_saveButton_clicked(){
    csm->storeData();
    on_newTest_clicked();
}

void MainWindow::on_set0T_clicked(){
    qDebug()<<"0T";
}

void MainWindow::on_set100T_clicked(){
    qDebug()<<"100T";
}

void MainWindow::on_mode_currentIndexChanged(int index){
    Q_UNUSED(index)
    qDebug()<<index;
}

void MainWindow::on_browseButton_clicked(){
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Set Directory"), QDir::fromNativeSeparators(setman->getDefaultDir())));
    if (!directory.isEmpty()) {
        ui->pathLineEdit->setText(directory);
        setman->setDefaultDir(directory);
    }
}
