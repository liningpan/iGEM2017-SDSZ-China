#include "ccddatareceiver.h"
#include <QDateTime>


CcdDataReceiver::CcdDataReceiver(QXYSeries * series, QObject *parent) :
    QIODevice(parent),
    m_series(series),
    startTime(QDateTime::currentDateTime())
{
}

qint64 CcdDataReceiver::readData(char *data, qint64 maxSize){
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

int CcdDataReceiver::charToInt(char a, char b){
    return (((int) 0 | (unsigned char)a)<<8)|((int) 0 | (unsigned char)b);
}

void CcdDataReceiver::newSeries(QXYSeries * series){
    m_series = series;
    newSer = true;
}
