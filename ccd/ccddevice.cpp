#include "ccddevice.h"
#include<QDebug>

ccdDevice::ccdDevice(const string &serialNumber, QObject *parent) : FTIODevice(serialNumber,parent) {
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
}

bool ccdDevice::open(OpenMode mode){
    return FTIODevice::open(mode);
}

void ccdDevice::start(QIODevice *dm, float interval){
    write("#CCDInt:100%");
    ccdDataReceiver = dm;
    timer->start((int)(interval * 1000));
}

void ccdDevice::timeOut(){
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
}
void ccdDevice::stop(){
    timer->stop();
}
