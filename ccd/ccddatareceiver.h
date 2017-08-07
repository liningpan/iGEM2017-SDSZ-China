#ifndef CCDDATARECEIVER_H
#define CCDDATARECEIVER_H

#include <QObject>
#include <QIODevice>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class CcdDataReceiver : public QIODevice
{
    Q_OBJECT
     QXYSeries *m_series;
public:
    explicit CcdDataReceiver(QXYSeries * series, QObject *parent = 0);
protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);
};

#endif // CCDDATARECEIVER_H
