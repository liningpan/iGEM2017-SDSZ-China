#include "ftiodevice.h"
#include <QDebug>
/*FTIODevice::FTIODevice(QObject *parent) : QIODevice(parent){

}*/
FTIODevice::FTIODevice(const string &serialNumber, QObject* parent) : QIODevice(parent),
    serialNumber(serialNumber){

}
bool FTIODevice::open(OpenMode mode){
    QIODevice::open(mode);
    DWORD numDevs;
    FT_STATUS st = FT_CreateDeviceInfoList(&numDevs);
    int index;
    if(st == FT_OK){
        qDebug() << numDevs << "devices";
        FT_DEVICE_LIST_INFO_NODE * node = new FT_DEVICE_LIST_INFO_NODE[numDevs];
        DWORD len;
        st = FT_GetDeviceInfoList(node,&len);
        if(st == FT_OK){
            for(int i = 0; i < len; i ++){
                qDebug() << node[i].SerialNumber;
                if((string)node[i].SerialNumber == serialNumber){
                    index = i;
                    break;
                }
            }
        }
        else{
            qDebug() << "Fail to find device";
            return false;
        }
    }else{
        qDebug() << "Fail to get list";
        return false;
    }
    st = FT_Open(index, &handle);
    return FT_SUCCESS(st);
}

void FTIODevice::close(){
    QIODevice::close();
    FT_Close(handle);
}

qint64 FTIODevice::readData(char *data, qint64 maxlen){
    DWORD sz;
    DWORD RxBytes;
    DWORD TxBytes;
    DWORD EventDWord;
    FT_GetStatus(handle,&RxBytes,&TxBytes,&EventDWord);
    FT_STATUS st = FT_Read(handle, data, RxBytes, &sz);
    if(FT_SUCCESS(st)){
        return sz;
    }else{
        return -1;
    }
}

qint64 FTIODevice::writeData(const char *data, qint64 len){
    DWORD sz;
    FT_STATUS st = FT_Write(handle, (void*) data, len, &sz);
    if(FT_SUCCESS(st)){
        return sz;
    }else{
        return -1;
    }
}
