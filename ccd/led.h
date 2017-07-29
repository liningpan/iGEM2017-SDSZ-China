#ifndef LED_H
#define LED_H

#include <ftd2xx.h>
#include <string>
using namespace std;
class led
{
public:
    led();
    bool open();
    bool trigger();
    void turnOn();
    void turnOff();
private:
    FT_HANDLE handle;
    const string serialNumber = "A501JYU4";
    void write(char *str, int size);
    bool condition;
};

#endif // LED_H
