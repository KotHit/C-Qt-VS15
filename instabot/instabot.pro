#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T11:36:36
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = instabot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    json.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    json.h \
    settings.h

FORMS    += mainwindow.ui
