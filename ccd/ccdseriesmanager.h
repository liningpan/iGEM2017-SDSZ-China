#ifndef CCDSERIESMANAGER_H
#define CCDSERIESMANAGER_H

#include <QObject>
#include <QtCharts/QChartGlobal>
#include <QVector>
#include <QDateTime>
#include <QVXYModelMapper>
#include <QValueAxis>
#include <QLineSeries>

#include "ccddatatablemodel.h"
#include "ccdrawdatareceiver.h"
#include "ccdseriesdatareciver.h"
#include "settingsmanager.h"
#include "datastore.h"

struct SeriesData{
    QXYSeries* series;
    CcdDataTableModel* model;
    QVXYModelMapper* mapper;
    QDateTime timestamp;
    SeriesData(){
        timestamp = QDateTime::currentDateTime();
    }
};
struct XYAxis{
    QValueAxis* x;
    QValueAxis* y;
    QVector<QXYSeries*> series;
};

class dataStore;

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

enum DataMode{
    Raw = 1,
    Average = 2,
};

class CcdSeriesManager : public  QObject
{
    Q_OBJECT
public:
    explicit CcdSeriesManager(const DataMode mode = Average, QObject* parent = 0);
    ~CcdSeriesManager();
    SeriesData* newTest();
    int size() const{ return count; }
    DataMode getMode() const { return mode; }
    void startTest();
    void testOnce();
    CcdDataReceiver* getCurrentDevice() const{
        return currentDevice;
    }
    SeriesData* getCurrentSeries() const{
        return currentSeries;
    }
    CcdDataReceiver* getRawDevice() const{
        return rawDevice;
    }
    SeriesData* getSeriesDataByXYSeries(QXYSeries*);
    XYAxis getRawAxis(){
        XYAxis v;
        v.x = new QValueAxis(this);
        v.x->setRange(0,3648);
        v.x->setLabelFormat("%d");
        v.x->setTitleText("Pixel");

        v.y = new QValueAxis(this);
        v.y->setRange(0,65535);
        v.y->setLabelFormat("%d");
        v.y->setTitleText("Intensity");

        v.series.append(new QLineSeries(this));
        return v;
    }
    XYAxis getAverageAxis(){
        XYAxis v;
        v.x = new QValueAxis(this);
        v.x->setRange(0,setman.getTestTime());
        v.x->setLabelFormat("%d");
        v.x->setTitleText("Time");

        v.y = new QValueAxis(this);
        v.y->setRange(0,65535);
        v.y->setLabelFormat("%d");
        v.y->setTitleText("Intensity");

        for(int i = 0; i < series_data.size();i++){
            v.series.append(series_data[i]->series);
            v.series[i]->attachAxis(v.x);
            v.series[i]->attachAxis(v.y);
        }
        return v;
    }

    void storeData();
    void deleteOldData();
private:
    SettingsManager setman;
    QVector<SeriesData*> series_data;
    SeriesData* currentSeries;
    CcdDataReceiver* rawDevice;
    CcdDataReceiver* seriesDevice;
    CcdDataReceiver* currentDevice;
    dataStore* ds;
    int count;
    DataMode mode;

};

#endif // CCDSERIESMANAGER_H
