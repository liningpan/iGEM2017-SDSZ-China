#ifndef CCDSERIESDATARECIVER_H
#define CCDSERIESDATARECIVER_H

#include <QObject>
#include <QIODevice>
#include <QtCharts/QChartGlobal>
#include <QVector>
#include <QDateTime>
#include <algorithm>
#include "ccddatareceiver.h"

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class CcdSeriesDataReciver : public CcdDataReceiver
{
    Q_OBJECT
public:
    explicit CcdSeriesDataReciver(QXYSeries * series, QObject *parent = 0);
private:
    qint64 writeData(const char * data, qint64 maxSize);
};

#endif // CCDSERIESDATARECIVER_H
