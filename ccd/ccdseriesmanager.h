#ifndef CCDSERIESMANAGER_H
#define CCDSERIESMANAGER_H

#include <QObject>
#include <QtCharts/QChartGlobal>
#include <QVector>
#include <QDateTime>
#include <QVXYModelMapper>
#include <QLineSeries>

#include "ccddatatablemodel.h"
#include "ccdrawdatareceiver.h"
#include "ccdseriesdatareciver.h"
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
    QIODevice* getCurrentDevice() const{
        return currentDevice;
    }
    SeriesData* getSeriesDataByXYSeries(QXYSeries*);
    void storeData();
    void deleteOldData();
private:
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
