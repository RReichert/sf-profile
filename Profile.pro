#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T21:38:14
#
#-------------------------------------------------

TARGET = profile

LIBS += -L/usr/local/lib
LIBS += -lboost_filesystem
LIBS += -lboost_system
LIBS += -lboost_regex

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    models/app_access.cpp \
    models/class_access.cpp \
    models/field_permission.cpp \
    models/object_permission.cpp \
    models/page_access.cpp \
    models/record_type_access.cpp \
    models/tab_access.cpp \
    models/common_profile.cpp \
    profile.cpp

HEADERS += \
    exceptions/profile_exception.h \
    models/app_access.h \
    models/class_access.h \
    models/field_permission.h \
    models/object_permission.h \
    models/page_access.h \
    models/record_type_access.h \
    models/tab_access.h \
    models/common_profile.h \
    profile.h
