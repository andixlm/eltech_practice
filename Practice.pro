QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = Practice
TEMPLATE = app

SOURCES += main.cpp \
        src/clickablelabel.cpp \
        src/hypocycloidprocessor.cpp \
        src/ihwidget.cpp \
        src/ih1widget.cpp \
        src/ih2widget.cpp \
        src/initialswitch.cpp \
        src/kochfractal.cpp \
        src/kochfractalprocessor.cpp \
        src/kochnode.cpp \
        src/kochtree.cpp \
        src/tools.cpp

HEADERS += \
        src/clickablelabel.hpp \
        src/hypocycloidprocessor.hpp \
        src/ihwidget.hpp \
        src/ih2widget.hpp \
        src/ih1widget.hpp \
        src/initialswitch.hpp \
        src/kochfractal.hpp \
        src/kochfractalprocessor.hpp \
        src/kochnode.hpp \
        src/kochtree.hpp \
        src/tools.hpp
