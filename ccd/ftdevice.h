#ifndef FTDEVICE_H
#define FTDEVICE_H

#include "ftd2xx.h"
#include <string>
#include <QByteArray>
using namespace std;
class ftdevice
{
    string serialNumber;
protected:
    virtual bool open();
    FT_HANDLE handle;
    bool write(char *str, int size = -1);
    bool read(QByteArray &buf, int maxlen, bool precise = false);
public:
    //ftdevice();
    ftdevice(const string &serialNumber) : serialNumber(serialNumber) {}

};

#endif // FTDEVICE_H
