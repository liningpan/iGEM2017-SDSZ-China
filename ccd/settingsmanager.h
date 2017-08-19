#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include<QSettings>
#include<QDir>
#include<QObject>

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
    Q_OBJECT

private:
    QSettings settings;

public:
    SettingsManager(QObject * parent = 0);
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
