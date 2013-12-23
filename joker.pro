#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T20:02:00
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = joker
TEMPLATE = app


SOURCES += main.cpp \
    jokerview.cpp \
    carditem.cpp \
    cardutil.cpp \
    buttonitem.cpp \
    userthread.cpp \
    mycontrol.cpp \
    centrecontrol.cpp \
    timeritem.cpp

HEADERS  += \
    jokerview.h \
    carditem.h \
    cardutil.h \
    buttonitem.h \
    userthread.h \
    mycontrol.h \
    centrecontrol.h \
    timeritem.h

RESOURCES += \
    resources.qrc
