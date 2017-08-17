#include "datastore.h"

QJsonDocument dataStore::toJson(QVector<SeriesData*> &v){
    int len = v.size();

    QJsonArray data;
    for(int i = 0; i < len; i ++){
        QJsonArray jsCCDData;
        QVector<QPointF> points = v[i]->series->pointsVector();
        for(int j = 0; j < points.length(); j++)
        {
            QJsonArray now;
            now.append(points[j].x());
            now.append(points[j].y());
            jsCCDData.append(now);
        }
        QJsonObject obj
        {
            {"time", v[i]->timestamp.toString(Qt::DateFormat::ISODateWithMs)},
            {"len", jsCCDData.size()},
            {"ccdData",jsCCDData}
        };
        data.append(obj);
    }
    QJsonObject final{
        {"mode",2},
        {"data", data}
    };
    QJsonDocument doc(final);
    return doc;
}

dataStore::dataStore(){
    dir = setman.getDefaultDir();
}
bool dataStore::writeData(QVector<SeriesData*> &v,QDateTime t){
    dir = setman.getDefaultDir();
    QString strtime = t.toString(Qt::DateFormat::ISODateWithMs);
    QJsonDocument js = toJson(v);
    QString path = dir + "/" + strtime + ".json";
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&file);
        out<< js.toJson(QJsonDocument::JsonFormat::Compact);
        file.close();
    }
}
