#ifndef CCDRAWDATARECEIVER_H
#define CCDRAWDATARECEIVER_H

#include <QObject>
#include <QIODevice>
#include <QtCharts/QChartGlobal>
#include "ccddatareceiver.h"

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class CcdRawDataReceiver : public CcdDataReceiver
{
    Q_OBJECT
public:
    explicit CcdRawDataReceiver(QXYSeries * series, QObject *parent = 0);
private:
    qint64 writeData(const char * data, qint64 maxSize);
};

#endif // CCDRAWDATARECEIVER_H
