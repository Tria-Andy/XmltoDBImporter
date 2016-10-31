#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T09:03:53
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XMLtoDBImporter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlparser.cpp

HEADERS  += mainwindow.h \
    xmlparser.h

FORMS    += mainwindow.ui
