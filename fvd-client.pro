#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T10:12:35
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fvd-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datamanager.cpp \
    database.cpp \
    jsontransform.cpp \
    yuvrender.cpp \
    dialogaddroad.cpp \
    searchdialog.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    datamanager.h \
    database.h \
    common.h \
    jsontransform.h \
    yuvrender.h \
    dialogaddroad.h \
    searchdialog.h \
    client.h

FORMS    += mainwindow.ui \
    dialogaddroad.ui \
    searchdialog.ui
