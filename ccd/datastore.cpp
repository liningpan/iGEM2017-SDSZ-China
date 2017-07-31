#include "datastore.h"

QJsonDocument dataStore::toJson(ccdData &cd,QString t){
    QJsonArray jsCCDData;
    for(int i = 50; i < 1500; i ++){
        jsCCDData.append(cd[i]);
    }
    QJsonObject obj
    {
        {"time",t},
        {"data",jsCCDData}
    };
    QJsonDocument doc(obj);
    return doc;
}

dataStore::dataStore(){
    dir = "";
}
bool writeData(ccdData &cd,QDateTime t){
    QString strtime = t.toString(Qt::DateFormat::ISODateWithMs);
    QJsonDocument js = toJson(cd,strtime);
    //qDebug() << js;
    QString path = dir + "/" + strtime + ".txt";
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug() << "OK";
        QTextStream out(&file);
        out<< js.toJson(QJsonDocument::JsonFormat::Compact);
        file.close();
    }
}
