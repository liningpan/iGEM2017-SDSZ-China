#include "ccddevice.h"
#include<QDebug>

ccdDevice::ccdDevice(const string &serialNumber, QObject *parent) :
    FTIODevice(serialNumber,parent),
    randomDataForTest(false),
    deviceSet(false),
    isOpen(false)
{
    readTimer = new QTimer();
    readTimer->setTimerType(Qt::PreciseTimer);
    stopTimer = new QTimer();
    stopTimer->setSingleShot(true);
    stopTimer->setTimerType(Qt::CoarseTimer);
    connect(readTimer,SIGNAL(timeout()),this,SLOT(timeToRead()));
    connect(stopTimer,SIGNAL(timeout()),this,SLOT(stopRead()));
}

bool ccdDevice::open(OpenMode mode){
    isOpen = FTIODevice::open(mode);
    return isOpen;
}

void ccdDevice::setDevice(QIODevice *dm){
    ccdDataReceiver = dm;
    deviceSet = true;
}

void ccdDevice::start(float interval,int testTime){
    if(!(isOpen&&deviceSet)) return;
    readTimer->start(interval*1000);
    stopTimer->start(testTime*1000);
}
void ccdDevice::timeToRead(){
    if(!(isOpen&&deviceSet)) return;
    testOnce();
}
void ccdDevice::stopRead(){
    readTimer->stop();
}

void ccdDevice::testOnce(){
    if(!(isOpen&&deviceSet)) return;
    if(!randomDataForTest){
        write("#?data%");
        DWORD RxBytes;
        DWORD TxBytes;
        DWORD EventDWord;
        while(true){
            FT_GetStatus(handle,&RxBytes,&TxBytes,&EventDWord);
            if(RxBytes == 7296){
                qDebug()<<"Can Read";
                ccdDataReceiver->write(read(7296));
                return;
            }
        }
    } else {
        QByteArray da;
        da.resize(7296);
        for(int i = 0; i < 3648; i++){
            da[i * 2] = 0xbd;
            da[i * 2 + 1] = 0x5c;
        }

        ccdDataReceiver->write(da);
    }
}
void ccdDevice::stop(){
    readTimer->stop();
    stopTimer->stop();
}
