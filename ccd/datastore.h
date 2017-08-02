#ifndef DATASTORE_H
#define DATASTORE_H
#include<QFile>
#include<QDir>
#include<QDataStream>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<string>
#include<QDateTime>
#include<QDebug>
#include "ccd.h"
using namespace std;
class dataStore
{
    QString dir;
    bool openFile();
    QJsonDocument toJson(ccdData* cd,int len,QString t);
public:
    dataStore();
    void setDir(QString &d){ dir = d; }
    QString getDir(){ return dir; }
    bool writeData(ccdData* cd,int len,QDateTime t);
};

#endif // DATASTORE_H
