#include "ccddatareceiver.h"
#include <QtCharts/QXYSeries>
#include <QDebug>

CcdDataReceiver::CcdDataReceiver(QXYSeries * series, QObject *parent) :
    QIODevice(parent),
    m_series(series)
{
}

qint64 CcdDataReceiver::readData(char *data, qint64 maxSize){
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 CcdDataReceiver::writeData(const char *data, qint64 maxSize){
    qDebug()<<"receive";
    if(maxSize == 7296){
        QVector<QPointF> points;
        for (int i = 0; i < 3648; i++)
            points.append(QPointF(i,data[i * 2] * 256 + data[i * 2 + 1]));
        m_series->replace(points);
    }
    return maxSize;
}
