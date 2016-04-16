QT += core
QT -= gui

TARGET = a3-huffman
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    archive.cpp \
    node.cpp

HEADERS += \
    archive.h \
    node.h \
    myqueue.h \
    myvector.h \
    mylist.h

DISTFILES += \
    text.txt

