#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include<QDebug>
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->time->setValue(setman.getTestTime());
    float val = setman.getInterval();
    int len = ui->timeInterval->count();
    for(int i = 0; i < len; i ++){
        if(val == ui->timeInterval->itemText(i).toFloat()){
            ui->timeInterval->setCurrentIndex(i);
        }
    }
    ui->dirName->setText(setman.getDefaultDir());
    connect(this,SIGNAL(settingsChanged(mySettings)),parent,SLOT(setChanged(mySettings)));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
void SettingsDialog::accept(){
    qDebug()<<"ok";
    mySettings ms(ui->time->value(),ui->timeInterval->currentText().toFloat(),ui->dirName->text());
    setman.setAllSettings(ms);
    emit settingsChanged(ms);
    close();
}
void SettingsDialog::on_browseButton_clicked(){
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Set Directory"), QDir::fromNativeSeparators(ui->dirName->text())));
    if (!directory.isEmpty()) {
        ui->dirName->setText(directory);
    }
}
