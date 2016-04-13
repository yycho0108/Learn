#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T15:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = First
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

#INCLUDEPATH += /home/jamiecho/ros_catkin_ws/install_isolated/include

RESOURCES += \
    src.qrc

unix:!macx: LIBS += -L$$PWD/../../ORSVisualize/build-CompassWidget-Desktop-Debug/ -lcompasswidgetplugin

INCLUDEPATH += $$PWD/../../ORSVisualize/build-CompassWidget-Desktop-Debug
DEPENDPATH += $$PWD/../../ORSVisualize/build-CompassWidget-Desktop-Debug
