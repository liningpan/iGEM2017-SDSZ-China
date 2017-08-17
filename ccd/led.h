#ifndef LED_H
#define LED_H

#include "ftd2xx.h"
#include <string>
#include "ftdevice.h"
using namespace std;
class led : public ftdevice
{
public:
    led(const string &sn = "AD01V9AS") : ftdevice(sn), condition(false) {}
    bool open();
    bool trigger();
    void turnOn();
    void turnOff();
private:
    bool condition;
};

#endif // LED_H
