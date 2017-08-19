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
bool dataStore::writeData(QVector<SeriesData*> &v,QDateTime t, bool json,bool csv){
    QString strtime = t.toString(Qt::DateFormat::ISODateWithMs);
    for (int i = 0; i < strtime.size(); i++)
        if (strtime[i] == ':')
            strtime[i] = '_';
    dir = setman.getDefaultDir();
    if(json){

        QJsonDocument js = toJson(v);
        QString path = dir + "/" + strtime + ".json";
        QFile jsfile(path);
        if(jsfile.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream jsout(&jsfile);
            jsout<< js.toJson(QJsonDocument::JsonFormat::Compact);
            jsfile.close();
        }
    }
    if(csv){
        QStringList strlist;
        int maxlen = 0;
        for(int i = 0;i < v.length(); i ++){
            int tmp = v[i]->series->pointsVector().size();
            if(tmp > maxlen){
                maxlen = tmp;
            }
        }
        for(int i = 0; i < maxlen; i ++){
            QString str;
            for(int j = 0; j < v.length(); j++){
                if(i < v[j]->series->pointsVector().size()){
                    QPointF point = v[j]->series->pointsVector()[i];
                    str += QString::number(point.x(),'g',3) + ','
                    + QString::number(point.y(),'g',6) + ',';
                }else{
                    str+= ",,";
                }
            }
            strlist.append(str);
        }
        QString path = dir + "/" + strtime + ".csv";
        QFile csvfile(path);
        if(csvfile.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream csvout(&csvfile);
            csvout<<strlist.join("\n");
            csvfile.close();
        }
    }
    return true;
}
