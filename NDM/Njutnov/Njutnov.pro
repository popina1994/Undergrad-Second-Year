#-------------------------------------------------
#
# Project created by QtCreator 2014-12-30T11:05:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Njutnov
TEMPLATE = app
QMAKE_CXXFLAGS +=-std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    Greska.cpp \
    Njutnov.cpp

HEADERS  += mainwindow.h \
    Greska.h \
    Njutnov.h

FORMS    += mainwindow.ui
