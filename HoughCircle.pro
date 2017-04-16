TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    createcirclepointcloud.cpp \
    HoughCircle.cpp

HEADERS += \
    createcirclepointcloud.h \
    HoughCircle.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += eigen3
