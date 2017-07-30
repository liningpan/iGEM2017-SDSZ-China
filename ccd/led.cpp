#include "led.h"

#include <QDebug>

bool led::open()
{
    bool st = ftdevice::open();
    if (!st)
    {
        qDebug() << "LED Open failed.";
        return false;
    }
    FT_SetBaudRate(handle,115200);
    return true;
}

void led::turnOn(){
    write("1");
    condition = true;
}
void led::turnOff(){
    write("0");
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
