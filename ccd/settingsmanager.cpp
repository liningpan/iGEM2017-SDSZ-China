#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject* parent):
    QObject(parent)
{

}

void SettingsManager::setDefaultDir(QString s){
    settings.setValue("datastore/dir",s);
}

QString SettingsManager::getDefaultDir(){
    if(settings.contains("datastore/dir")){
        return settings.value("datastore/dir").toString();
    }
    return QDir::homePath();
}

void SettingsManager::setTestTime(int t){
    settings.setValue("datastore/time",t);
}

int SettingsManager::getTestTime(){
    if(settings.contains("datastore/time")){
        return settings.value("datastore/time").toInt();
    }
    return 60;
}
void SettingsManager::setInterval(float i){
    settings.setValue("datastore/interval",i);
}

float SettingsManager::getInterval(){
    if(settings.contains("datastore/interval")){
        return settings.value("datastore/interval").toFloat();
    }
    return 5.0;
}
void SettingsManager::setAllSettings(mySettings & s){
    setTestTime(s.time);
    setInterval(s.interval);
    setDefaultDir(s.dir);
}
mySettings SettingsManager::getAllSettings(){
    return mySettings(getTestTime(),getInterval(),getDefaultDir());
}

