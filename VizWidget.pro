#-------------------------------------------------
#
# Project created by QtCreator 2013-09-11T17:55:55
#
#-------------------------------------------------

QT       += opengl core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CorrelaViz
TEMPLATE = app

SOURCES  += main.cpp\
            mainwindow.cpp \
    dataobject.cpp \
    util.cpp \
    glwidget.cpp \
    scatterplotviz.cpp

HEADERS  += mainwindow.h \
    dataobject.h \
    util.h \
    glwidget.h \
    scatterplotviz.h

FORMS    += mainwindow.ui
