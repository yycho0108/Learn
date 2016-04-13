CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(mywidgetplugin)
TEMPLATE    = lib

HEADERS     = mywidgetplugin.h
SOURCES     = mywidgetplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += widgets uiplugin

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(mywidget.pri)
