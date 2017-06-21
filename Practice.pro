QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = Practice
TEMPLATE = app

SOURCES += main.cpp \
        src/ih1widget.cpp \
        src/initialswitch.cpp \
        src/tools.cpp

HEADERS += \
        src/ih1widget.hpp \
        src/initialswitch.hpp \
        src/tools.hpp
