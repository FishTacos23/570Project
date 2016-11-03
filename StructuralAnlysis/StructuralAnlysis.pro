#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T21:11:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StructuralAnlysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analyze.cpp \
    pframe.cpp

HEADERS  += mainwindow.h \
    analyze.h \
    pframe.h

FORMS    += mainwindow.ui
