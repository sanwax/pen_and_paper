QT       += core websockets
QT       -= gui

TARGET = sslSocketTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp
    Socket.cpp

HEADERS += \
    Socket.h
