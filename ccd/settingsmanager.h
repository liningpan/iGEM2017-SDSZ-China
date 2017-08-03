#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include<QSettings>
#include<QDir>

struct mySettings{
    int time;
    float interval;
    QString dir;
    mySettings(int t, float i, QString d){
        time = t;
        interval = i;
        dir = d;
    }
};

class SettingsManager:public QObject
{

private:
    QSettings settings;

public:
    SettingsManager();
    void setDefaultDir(QString);
    QString getDefaultDir();
    void setTestTime(int);
    int getTestTime();
    void setInterval(float);
    float getInterval();
    void setAllSettings(mySettings &s);
    mySettings getAllSettings();
};

#endif // SETTINGSMANAGER_H
