#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("BearBile");
    QCoreApplication::setOrganizationName("SDSZ-China");
    QCoreApplication::setOrganizationDomain("SDSZ-China.com");

    MainWindow w;
    w.show();

    return a.exec();
}
