#ifndef CCDDEVICE_H
#define CCDDEVICE_H

#include <QObject>
#include "ftiodevice.h"
#include <QTimer>

class ccdDevice : public FTIODevice
{
    Q_OBJECT
    QTimer* readTimer;
    QTimer* stopTimer;
    QIODevice* ccdDataReceiver;
    bool randomDataForTest;
    bool deviceSet;
    bool isOpen;
private slots:
    void timeToRead();
    void stopRead();
public:
    //explicit ccdDevice(QObject * parent = 0);
    explicit ccdDevice(const string &serialNumber = "12345678", QObject* parent = 0);
    bool open(OpenMode mode = ReadWrite);
    void setDevice(QIODevice* dm);
    void start(float interval,int testTime);
    void testOnce();
    void stop();
};

#endif // CCDDEVICE_H
