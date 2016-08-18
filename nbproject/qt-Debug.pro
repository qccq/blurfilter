# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = blurfilter
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += link_pkgconfig debug 
PKGCONFIG += opencv
QT = core gui widgets
SOURCES += main.cpp source/Blurfilter.cpp source/Pictures.cpp
HEADERS += header/Blurfilter.h header/Pictures.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/local/include/opencv2 /usr/local/lib 
LIBS += -Wl,-rpath,/usr/local/include/opencv2 
