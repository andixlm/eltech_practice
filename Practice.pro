QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = Practice
TEMPLATE = app

SOURCES += main.cpp \
        src/initialswitch.cpp

HEADERS += \
        src/initialswitch.hpp
