#ifndef FTIODEVICE_H
#define FTIODEVICE_H

#include <QObject>
#include <QIODevice>
#include <string>
#include "ftd2xx.h"

using namespace std;

class FTIODevice : public QIODevice
{
    Q_OBJECT
    string serialNumber;
protected:
    FT_HANDLE handle;
public:
    //explicit FTIODevice(QObject* parent = 0);
    explicit FTIODevice(const string &serialNumber, QObject* parent = 0);
    virtual bool open(OpenMode mode);
    void close();
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
};

#endif // FTIODEVICE_H
