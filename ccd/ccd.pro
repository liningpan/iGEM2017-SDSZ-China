#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T16:06:09
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ccd
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ccd.cpp \
    qcustomplot.cpp \
    led.cpp \
    ftdevice.cpp \
    datastore.cpp \
    settingsmanager.cpp \
    settingsdialog.cpp

HEADERS += \
        mainwindow.h \
    ccd.h \
    qcustomplot.h \
    WinTypes.h \
    led.h \
    ftdevice.h \
    ftd2xx.h \
    datastore.h \
    settingsmanager.h \
    settingsdialog.h

FORMS += \
        mainwindow.ui \
    settingsdialog.ui

#macx: LIBS += -lftd2xx.1.4.4

macx: LIBS += -L$$PWD/./ -lftd2xx

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

macx: PRE_TARGETDEPS += $$PWD/./libftd2xx.a

macx: LIBS += -L$$PWD/./ -lftd2xx

INCLUDEPATH += $$PWD/../../../../usr/local/lib
DEPENDPATH += $$PWD/../../../../usr/local/lib


win32: LIBS += -L$$PWD/./ -lftd2xx

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32: PRE_TARGETDEPS += $$PWD/./ftd2xx.lib
