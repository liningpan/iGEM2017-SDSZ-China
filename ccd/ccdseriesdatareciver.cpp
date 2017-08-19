#include "ccdseriesdatareciver.h"
#include<QVector>
#include <QtCharts/QXYSeries>
#include <QDebug>
#include <QDateTime>

CcdSeriesDataReciver::CcdSeriesDataReciver(QXYSeries * series, QObject *parent) :
    CcdDataReceiver(series,parent)
{
}

qint64 CcdSeriesDataReciver::writeData(const char *data, qint64 maxSize){
    //qDebug()<<"receive";
    if(maxSize == 7296){
        QVector<int> da;
        for (int i = 0; i < 3648; i++){
            da.append(charToInt(data[i * 2],data[i * 2 + 1]));
        }
        std::sort(da.begin(),da.end());
        float to = 0;
        for (int i = 10; i < 30; i++){
             to += da[3648 - i];
        }
        to /= 20.0;
        qDebug()<<to;
        if(newSer){
            newSer = false;
            startTime = QDateTime::currentDateTime();
            m_series->append(0,to);\
        } else {
            qDebug()<<startTime.msecsTo(QDateTime::currentDateTime());

            m_series->append(startTime.msecsTo(QDateTime::currentDateTime())/1000.0,to);
        }
        return maxSize;
    }
    return -1;
}
