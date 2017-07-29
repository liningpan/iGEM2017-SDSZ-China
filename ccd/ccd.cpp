#include "ccd.h"

#include <QDebug>
#include <string>
using namespace std;
ccd::ccd()
{

}

bool ccd::open()
{
    DWORD numDevs;
    FT_STATUS sta = FT_CreateDeviceInfoList(&numDevs);
    int index;
    if(sta == FT_OK){
        //qDebug() << numDevs << "devices";
        FT_DEVICE_LIST_INFO_NODE * node = new FT_DEVICE_LIST_INFO_NODE[numDevs];
        DWORD len;
        sta = FT_GetDeviceInfoList(node,&len);
        if(sta == FT_OK){
            for(int i = 0; i < len; i ++){
                if((string)node[i].SerialNumber == serialNumber){
                    index = i;
                }
            }
        }
        else{
            qDebug() << "Fail to find device";
            return FT_STATUS(sta);
        }
    }else{
        qDebug() << "Fail to get list";
        return FT_STATUS(sta);
    }
    sta = FT_Open(index, &handle);
    if (FT_SUCCESS(sta))
    {
        qDebug() << "connect succeeded";
        write("#CCDInt:100%", 11);
    }
    else
        qDebug() << "connect failed";
    return FT_SUCCESS(sta);
}

ccdData ccd::read()
{
    ccdData ret;
    DWORD sz;
    unsigned char t[7296];
    FT_Read(handle, t, 7296, &sz);
    for (int i = 0; i < 3648; i++)
        ret.dat[i] = t[i * 2] * 256 + t[i * 2 + 1];
    qDebug() << sz;
    return ret;
}

void ccd::write(char *str, int size)
{
    DWORD sz;
    FT_Write(handle, str, size, &sz);
}
ccdData ccd::getData()
{
    char t[] = "#?data%";
    write("#?data%", 7);
    return read();
}
