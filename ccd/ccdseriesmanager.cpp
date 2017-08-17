#include "ccdseriesmanager.h"
#include <QIODevice>


CcdSeriesManager::CcdSeriesManager(const DataMode mode,QObject * parent) :
    mode(mode),
    QObject(parent),
    count(0)
{
    rawDevice = new CcdRawDataReceiver(0,this);
    rawDevice->open(QIODevice::WriteOnly);
    seriesDevice = new CcdSeriesDataReciver(0,this);
    seriesDevice->open(QIODevice::WriteOnly);
    ds = new dataStore;
}
CcdSeriesManager::~CcdSeriesManager(){
    delete ds;
    series_data.clear();
}

void CcdSeriesManager::deleteOldData(){
    for(int i = 0; i < series_data.size(); i ++){
        delete series_data[i]->mapper;
        delete series_data[i]->model;
    }
    series_data.clear();
    count = 0;
}

SeriesData* CcdSeriesManager::getSeriesDataByXYSeries(QXYSeries* s){
    for(int i = 0; i < series_data.size(); i ++){
        if(series_data[i]->series == s)
            return series_data[i];
    }
    return 0;
}

void CcdSeriesManager::storeData(){
    ds->writeData(series_data,QDateTime::currentDateTime());
}

SeriesData* CcdSeriesManager::newTest(){
    currentSeries = new SeriesData;

    currentSeries->series = new QLineSeries(this);
    currentSeries->mapper = new QVXYModelMapper(this);
    currentSeries->model = new CcdDataTableModel(this);

    currentSeries->model->insertColumn(0);
    currentSeries->model->insertColumn(0);

    currentSeries->mapper->setModel(currentSeries->model);
    currentSeries->mapper->setXColumn(0);
    currentSeries->mapper->setYColumn(1);
    currentSeries->mapper->setSeries(currentSeries->series);

    if (mode == Raw) {
        currentDevice = rawDevice;
    } else if (mode == Average){
        currentDevice = seriesDevice;
    }

    currentDevice->newSeries(currentSeries->series);
    series_data.append(currentSeries);
    count = series_data.size();
    return currentSeries;
}
