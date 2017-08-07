#ifndef CCDDEVICE_H
#define CCDDEVICE_H

#include <QObject>
#include "ftiodevice.h"
#include <QTimer>

class ccdDevice : public FTIODevice
{
    Q_OBJECT
    QTimer* timer;
    QIODevice* ccdDataReceiver;
private slots:
    void timeOut();
public:
    //explicit ccdDevice(QObject * parent = 0);
    explicit ccdDevice(const string &serialNumber = "12345678", QObject* parent = 0);
    bool open(OpenMode mode = ReadWrite);
    void start(QIODevice* dm, float interval = 0.5);
    void stop();
    //QIODevice* start(float interval = 0.5);
};

#endif // CCDDEVICE_H
