#-------------------------------------------------
#
# Project created by QtCreator 2020-04-17T15:35:01
#
#-------------------------------------------------

QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = data_compare
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        baseinfo.cpp \
        config.cpp \
        dmsdatahandler.cpp \
        enventcontrol.cpp \
        formbalise.cpp \
        formbalisechk.cpp \
        formbaseinfo.cpp \
        formtrackinfo.cpp \
        main.cpp \
        mainwidget.cpp \
        tcpsocketwork.cpp

HEADERS += \
        baseinfo.h \
        config.h \
        dmsdatahandler.h \
        enventcontrol.h \
        formbalise.h \
        formbalisechk.h \
        formbaseinfo.h \
        formtrackinfo.h \
        log.h \
        mainwidget.h \
        tcpsocketwork.h

FORMS += \
        formbalise.ui \
        formbalisechk.ui \
        formbaseinfo.ui \
        formtrackinfo.ui \
        mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
