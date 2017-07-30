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
    QJsonDocument toJson(ccdData &cd,QDateTime t){
        QJsonArray jsCCDData;
        for(int i = 0; i < 3648; i ++){
            jsCCDData.append(cd[i]);
        }
        QJsonObject obj
        {
            {"time",t.toString()},
            {"data",jsCCDData}
        };
        QJsonDocument doc(obj);
        return doc;
    }

public:
    dataStore(){
        dir = "";
    }

    void setDir(QString &d){dir = d;}
    QString getDir(){return dir;}
    bool writeData(ccdData &cd,QDateTime t){
        QJsonDocument js = toJson(cd,t);
        //qDebug() << js;
        QFile file("/Users/panlining/test.txt");
        /**
         * should be dynamic file name
         * file exist or not
         * create new file
         * */
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug() << "OK";
            QTextStream out(&file);
            out<< js.toJson();
            file.close();
        }

    }
};

#endif // DATASTORE_H
