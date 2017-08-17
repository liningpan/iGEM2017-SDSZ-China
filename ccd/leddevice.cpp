#include "leddevice.h"
#include<QString>
#include<QDebug>
#include<string>
LedDevice::LedDevice(const string &serialNumber, QObject *parent) :
    FTIODevice(serialNumber,parent){

}

bool LedDevice::open(OpenMode mode){
    st = FTIODevice::open(mode);
    if(st){
        FT_SetBaudRate(handle,115200);
    }
    return st;
    //return true;
}

void LedDevice::setLightCondition(bool con){
    writeToDevice("4",QString::number(int(con)));
}
void LedDevice::setBoardOneUp(){
    //UP & DOWN: #[1/2]$NO%SPEED&
    writeToDevice("1","0","30");
}
void LedDevice::setBoardOneStop(){
    writeToDevice("3","0");
}
void LedDevice::setBoardOneDown(){
    writeToDevice("2","0","30");
}
void LedDevice::setBoardTwoUp(){
    writeToDevice("1","1","30");
}
void LedDevice::setBoardTwoStop(){
    writeToDevice("3","1");
}
void LedDevice::setBoardTwoDown(){
    writeToDevice("2","1","30");
}
void LedDevice::stop(){
    setBoardOneStop();
    setBoardTwoStop();
    setLightCondition(false);
}

void LedDevice::writeToDevice(const QString &arg1, const QString &arg2, const QString &arg3){
    QString str = "#"+arg1+"$"+arg2+"%"+arg3+"&";
    if(st){
        write(str.toLocal8Bit());
    }
}
