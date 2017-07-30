#include "ccd.h"

#include <QDebug>
#include <string>
using namespace std;

bool ccd::open()
{
    bool st = ftdevice::open();
    if (!st)
    {
        qDebug() << "CCD open failed.";
        return false;
    }
    write("#CCDInt:100%");
    return st;
}

bool ccd::getData(ccdData &dat)
{
    write("#?data%");
    QByteArray data(7296, 0);
    bool st = read(data, 7296, true);
    if (!st)
    {
        qDebug() << "Get data failed.";
        return false;
    }
    for (int i = 0; i < 3648; i++)
        dat[i] = data[i * 2] * 256 + data[i * 2 + 1];
    return true;
}
