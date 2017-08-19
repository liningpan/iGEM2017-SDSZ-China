#ifndef CCDDATARECEIVER_H
#define CCDDATARECEIVER_H

#include <QObject>
#include <QIODevice>
#include <QtCharts/QChartGlobal>
#include <QVector>
#include <QDateTime>
#include <algorithm>

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class CcdDataReceiver : public QIODevice
{
    Q_OBJECT
protected:
    QXYSeries *m_series;
    bool newSer;
    QDateTime startTime;
    int charToInt(char a, char b);
    qint64 readData(char * data, qint64 maxSize);
    virtual qint64 writeData(const char * data, qint64 maxSize) = 0;
public:
    explicit CcdDataReceiver(QXYSeries * series, QObject *parent = 0);
    void newSeries(QXYSeries * series);
};

#endif // CCDDATARECEIVER_H
