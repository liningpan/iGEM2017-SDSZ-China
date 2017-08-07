#include "leddevice.h"

LedDevice::LedDevice(const string &serialNumber, QObject *parent) :
    FTIODevice(serialNumber,parent){

}

bool LedDevice::open(OpenMode mode){
    bool st = FTIODevice::open(mode);
    if(st){
        FT_SetBaudRate(handle,115200);
    }
    return st;
}

void LedDevice::turnOn(){
    write("1");
    condition = true;
}
void LedDevice::turnOff(){
    write("0");
    condition = false;
}
bool LedDevice::trigger(){
    if(condition){
        turnOff();
    }else{
        turnOn();
    }
    return condition;
}
