#include "datastore.h"

QJsonDocument dataStore::toJson(ccdData* cd,int len,QString t){
    QJsonArray final;
    for(int i = 0; i < len; i ++){
        QJsonArray jsCCDData;
        for(int j = 50; j < 1500; j ++){
            jsCCDData.append(cd[i][j]);
        }
        QJsonObject obj
        {
            {"time",t},
            {"data",jsCCDData}
        };
        final.append(obj);
    }
    QJsonDocument doc(final);
    return doc;
}

dataStore::dataStore(){
    dir = "";
}
bool dataStore::writeData(ccdData* cd,int len,QDateTime t){
    QString strtime = t.toString(Qt::DateFormat::ISODateWithMs);
    QJsonDocument js = toJson(cd,len,strtime);
    //qDebug() << js;
    QString path = dir + "/" + strtime + ".json";
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug() << "OK";
        QTextStream out(&file);
        out<< js.toJson(QJsonDocument::JsonFormat::Compact);
        file.close();
    }
}
