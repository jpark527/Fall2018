#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T23:57:42
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eagleRockFireStation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    borderlayout.cpp \
    pathfinder.cpp

HEADERS += \
        mainwindow.h \
    borderlayout.h \
    pathfinder.h

unix {
    Resources.files += "/Users/j/C++/CS08/eagleRockFireStation/map.html"
    Resources.files += "/Users/j/C++/CS08/eagleRockFireStation/styleSheet.qss"
    Resources.files += "/Users/j/C++/CS08/eagleRockFireStation/qwebchannel.js"
    Resources.files += "/Users/j/C++/CS08/eagleRockFireStation/convertedData.json"
    Resources.path = Contents/MacOS
    QMAKE_BUNDLE_DATA += Resources
}
