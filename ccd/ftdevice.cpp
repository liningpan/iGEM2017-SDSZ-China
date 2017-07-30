#include "ftdevice.h"
#include <string.h>
#include <QDebug>

bool ftdevice::open()
{
    DWORD numDevs;
    FT_STATUS sta = FT_CreateDeviceInfoList(&numDevs);
    int index;
    if(sta == FT_OK){
        qDebug() << numDevs << "devices";
        FT_DEVICE_LIST_INFO_NODE * node = new FT_DEVICE_LIST_INFO_NODE[numDevs];
        DWORD len;
        sta = FT_GetDeviceInfoList(node,&len);
        if(sta == FT_OK){
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
    sta = FT_Open(index, &handle);
    if (FT_SUCCESS(sta))
    {
        qDebug() << "connect succeeded";
    }
    else
        qDebug() << "connect failed";
    return FT_SUCCESS(sta);
}

bool ftdevice::write(char *str, int size)
{
    if (size == -1)
        size = strlen(str);
    DWORD sz;
    FT_STATUS st = FT_Write(handle, str, size, &sz);
    if (!FT_SUCCESS(st))
    {
        qDebug() << "Write failed.";
        return false;
    }
    if (sz != size)
    {
        qDebug() << "Not all data are written.";
        return false;
    }
    return true;
}

bool ftdevice::read(QByteArray &buf, int maxlen, bool precise)
{
    DWORD sz;
    FT_STATUS st = FT_Read(handle, buf.data(), maxlen, &sz);
    if (!FT_SUCCESS(st))
    {
        qDebug() << "Read failed.";
        return false;
    }
    if (precise && sz != maxlen)
    {
        qDebug() << "Not enough data!";
        return false;
    }
    return true;
}
