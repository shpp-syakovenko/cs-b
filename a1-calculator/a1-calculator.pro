QT += core
QT -= gui

TARGET = a1-Calculator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Calculator.cpp \
    Checkfunction.cpp

HEADERS += \
    Calculator.h \
    Checkfunction.h

