#ifndef LEDDEVICE_H
#define LEDDEVICE_H

#include <QObject>
#include "ftiodevice.h"

class LedDevice : public FTIODevice
{
    Q_OBJECT
public:
    explicit LedDevice(const string &serialNumber = "A501JYU4", QObject* parent = 0);
    bool open(OpenMode mode = ReadWrite);
    bool trigger();
    void turnOn();
    void turnOff();
private:
    bool condition;
};

#endif // LEDDEVICE_H
