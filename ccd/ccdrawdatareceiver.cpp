#include "ccdrawdatareceiver.h"
#include <QtCharts/QXYSeries>
#include <QDebug>

CcdRawDataReceiver::CcdRawDataReceiver(QXYSeries * series, QObject *parent) :
    CcdDataReceiver(series,parent)
{
}

qint64 CcdRawDataReceiver::writeData(const char *data, qint64 maxSize){
    qDebug()<<"receive";
    if(maxSize == 7296){
        QVector<QPointF> points;
        qDebug()<< charToInt(data[0],data[1]);
        for (int i = 0; i < 3648; i++){
            points.append(QPointF(i,charToInt(data[i * 2],data[i * 2 + 1])));
        }
        //qDebug()<<points[1].ry();
        m_series->replace(points);
        return maxSize;
    }
    return -1;
}
