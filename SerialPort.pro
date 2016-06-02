#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T15:33:42
#
#-------------------------------------------------


# 添加组件
QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPort
TEMPLATE = app


SOURCES += main.cpp \
    serial.cpp

HEADERS  += \
    serial.h

DISTFILES += \
    Readme.md
RC_FILE += app.rc

RESOURCES +=
