#-------------------------------------------------
#
# Project created by QtCreator 2019-05-06T12:23:57
#
#-------------------------------------------------

QT       += core gui

#LIBS     += -lopengl32
#LIBS     += -lglu32
#LIBS     += -lglut

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PtsDisplay
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    objloader.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objloader.h

FORMS    += mainwindow.ui \
    mainwindow.ui

RESOURCES += \
    res.qrc
