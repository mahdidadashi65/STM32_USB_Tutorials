#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T11:42:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PM_Controller
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    fcd.c


mac: SOURCES += hidmac.c
win32: SOURCES += hidwin.c


HEADERS  += mainwindow.h \
    fcd.h \
    hidapi.h
HEADERS  += ftd2xx.h


FORMS    += mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LIBs/FTDI/ -lftd2xx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LIBs/FTDI/ -lftd2xx
else:unix: LIBS += -L$$PWD/../LIBs/FTDI/ -lftd2xx

INCLUDEPATH += $$PWD/../LIBs/FTDI
DEPENDPATH += $$PWD/../LIBs/FTDI


# Might need to be adjusted depending on which SDK is installed
mac:LIBS += /System/Library/Frameworks/CoreFoundation.framework/CoreFoundation \
    /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
win32:LIBS += "C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.1A\\Lib\\setupapi.lib"


# libusb-1.0 on Linux uses pkg-config
linux-g++|linux-g++-64 {
    CONFIG += link_pkgconfig
    PKGCONFIG += libusb-1.0
    SOURCES += hid-libusb.c

#   LIBS += -ludev
#   SOURCES += hidraw.c
}


