#ifndef DATASTORE_H
#define DATASTORE_H
#include<QFile>
#include<QDir>
#include<QDataStream>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<string>
#include<QDateTime>
#include<QDebug>
#include"ccdseriesmanager.h"
#include "settingsmanager.h"

#include <QtCharts/QChartGlobal>
#include <QVXYModelMapper>

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
struct SeriesData;

class dataStore
{
    QString dir;
    bool openFile();
    SettingsManager setman;
    QJsonDocument toJson(QVector<SeriesData*>&);
public:
    dataStore();
    void setDir(QString &d){ dir = d; }
    QString getDir(){ return dir; }
    bool writeData(QVector<SeriesData*>&,QDateTime);
};

#endif // DATASTORE_H
