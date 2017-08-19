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
    void setLightCondition(bool con);
    void setBoardOneUp();
    void setBoardOneStop();
    void setBoardOneDown();
    void setBoardTwoUp();
    void setBoardTwoStop();
    void setBoardTwoDown();
    void setPumpOut();
    void setPumpStop();
    void setPumpIn();
    void stop();
private:
    bool condition;
    bool st;
    void writeToDevice(const QString &arg1 = "",const QString & arg2 = "",const QString & arg3 = "");
};

#endif // LEDDEVICE_H
