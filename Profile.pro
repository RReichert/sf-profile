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

INCLUDEPATH += src

SOURCES += src/main.cpp \
    src/models/app_access.cpp \
    src/models/class_access.cpp \
    src/models/field_permission.cpp \
    src/models/object_permission.cpp \
    src/models/page_access.cpp \
    src/models/record_type_access.cpp \
    src/models/tab_access.cpp \
    src/models/common_profile.cpp \
    src/profile.cpp

HEADERS += \
    src/exceptions/profile_exception.h \
    src/models/app_access.h \
    src/models/class_access.h \
    src/models/field_permission.h \
    src/models/object_permission.h \
    src/models/page_access.h \
    src/models/record_type_access.h \
    src/models/tab_access.h \
    src/models/common_profile.h \
    src/profile.h
