#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIODevice>
#include <QMessageBox>
#include "ccddatareceiver.h"
#include "ftd2xx.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    csm(new CcdSeriesManager(DataMode::Average,this)),
    setman(new SettingsManager(this)),
    scan(false),
    currentRow(0),
    sernum(0),
    mode(DataMode::Average),
    lightOn(false)
{
    ui->setupUi(this);
    cd = new ccdDevice("FTT5B0N6",this);
    ld = new LedDevice("A501JYU4",this);
    if(cd->open()&&ld->open()){
        qDebug()<<"connect";
    } else {
        qDebug()<<"not connect";
    }
    m_chart = new QChart;
    ui->chartView->setChart(m_chart);
    m_chart->setTitle("Data from ccd");

    averageAxis = csm->getAverageAxis();
    m_chart->setAxisX(averageAxis.x);
    m_chart->setAxisY(averageAxis.y);

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
    connect(currentSeries->series,SIGNAL(clicked(QPointF)),this,SLOT(seriesClicked()));
    currentSeries->series->attachAxis(averageAxis.x);
    currentSeries->series->attachAxis(averageAxis.y);
}

void MainWindow::setRawDataMode(){
    if(scan){
        on_startButton_clicked();
    }
    rawAxis = csm->getRawAxis();
    ui->newTest->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->startButton->setDisabled(true);
    ui->singleTestButton->setDisabled(true);
    ui->testTime->setDisabled(true);
    ui->interval->setDisabled(true);
    CcdDataReceiver* receiver = csm->getRawDevice();
    cd->setDevice(receiver);
    receiver->newSeries(rawAxis.series[0]);
    m_chart->addSeries(rawAxis.series[0]);
    m_chart->setAxisX(rawAxis.x);
    m_chart->setAxisY(rawAxis.y);
    rawAxis.series[0]->attachAxis(rawAxis.x);
    rawAxis.series[0]->attachAxis(rawAxis.y);
    cd->start(0.2,0);
    mode = DataMode::Raw;
}
void MainWindow::setAverageDataMode(){
    cd->stop();
    m_chart->removeSeries(rawAxis.series[0]);
    averageAxis = csm->getAverageAxis();
    m_chart->setAxisX(averageAxis.x);
    m_chart->setAxisY(averageAxis.y);
    ui->newTest->setDisabled(false);
    ui->saveButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    ui->singleTestButton->setDisabled(false);
    ui->testTime->setDisabled(false);
    ui->interval->setDisabled(false);
    CcdDataReceiver* receiver = csm->getCurrentDevice();
    cd->setDevice(receiver);
    mode = DataMode::Average;
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
    switch(QMessageBox::warning(this,
                tr("Warning"),
                tr("Do you want to save?"),
                QMessageBox::Cancel,QMessageBox::Discard,QMessageBox::Save))
    {
    case QMessageBox::Save:
        on_saveButton_clicked();
        break;
    case QMessageBox::Discard:
        qDebug()<<"discard";
        break;
    case QMessageBox::Cancel:
        qDebug()<<"cancel";
        return;
    default:
        break;
    }

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

void MainWindow::on_PumpIn_clicked(){
    ld->setPumpIn();
}

void MainWindow::on_PumpStop_clicked(){
    ld->setPumpStop();
}

void MainWindow::on_PumpOut_clicked(){
    ld->setPumpOut();
}

void MainWindow::on_interval_currentTextChanged(QString s){
    setman->setInterval(s.toFloat());
}

void MainWindow::on_testTime_valueChanged(int value){
    qDebug()<<value;
    setman->setTestTime(value);
    averageAxis.x->setMax(value);
}

void MainWindow::on_singleTestButton_clicked(){
    cd->testOnce();
}

void MainWindow::on_startButton_clicked(){
    if(scan){
        cd->stop();
        ui->startButton->setText("Start");
        ui->singleTestButton->setDisabled(false);
    } else {
        cd->start(setman->getInterval(),setman->getTestTime());
        ui->startButton->setText("Stop");
        ui->singleTestButton->setDisabled(true);
    }
    scan = !scan;
}

void MainWindow::on_newTest_clicked(){
    disconnect(currentSeries->model);
    currentSeries = csm->newTest();
    m_chart->addSeries(currentSeries->series);
    ui->dataTableView->setModel(currentSeries->model);
    currentSeries->series->attachAxis(averageAxis.x);
    currentSeries->series->attachAxis(averageAxis.y);
    connect(currentSeries->series,SIGNAL(clicked(QPointF)),this,SLOT(seriesClicked()));
    connect(currentSeries->model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(tableDataChanged()));
    //cd->setDevice(csm->getCurrentDevice());
}

void MainWindow::tableDataChanged(){
    ui->dataTableView->scrollToBottom();
}

void MainWindow::seriesClicked(){
    SeriesData* ser = csm->getSeriesDataByXYSeries((QXYSeries*)sender());
    if(ser != 0){
        ui->dataTableView->setModel(ser->model);
    }
}

void MainWindow::on_saveButton_clicked(){
    csm->storeData();
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
    if(ui->mode->currentText()=="Average" && mode != DataMode::Average){
        setAverageDataMode();
    }
    else{
        setRawDataMode();
    }
}

void MainWindow::on_lightSwitch_clicked(){
    lightOn = !lightOn;
    ui->lightSwitch->setChecked(lightOn);
    ld->setLightCondition(lightOn);
}

void MainWindow::on_browseButton_clicked(){
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Set Directory"), QDir::fromNativeSeparators(setman->getDefaultDir())));
    if (!directory.isEmpty()) {
        ui->pathLineEdit->setText(directory);
        setman->setDefaultDir(directory);
    }
}
