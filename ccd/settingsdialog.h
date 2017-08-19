#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include"settingsmanager.h"
#include<QDir>
#include<QFileDialog>
namespace Ui {
class SettingsDialog;
}



class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
signals:
    void settingsChanged(mySettings);
private slots:
    void accept();
    void on_browseButton_clicked();
private:
    Ui::SettingsDialog *ui;
    SettingsManager setman;
};

#endif // SETTINGSDIALOG_H
