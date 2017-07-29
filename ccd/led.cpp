#include "led.h"

#include <QDebug>

led::led()
{
    condition = false;
}

bool led::open()
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
        FT_SetBaudRate(handle,115200);
    }
    else
        qDebug() << "connect failed";
    return FT_SUCCESS(sta);
}


void led::write(char *str, int size)
{
    DWORD sz;
    FT_Write(handle, str, size, &sz);
}

void led::turnOn(){
    write("1",1);
    condition = true;
}
void led::turnOff(){
    write("0",1);
    condition = false;
}
bool led::trigger(){
    if(condition){
        turnOff();
    }else{
        turnOn();
    }
    return condition;
}
