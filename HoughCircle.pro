TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    HoughCircle.cpp \
    CreateCirclePointCloud.cpp

HEADERS += \
    HoughCircle.h \
    util.h \
    CreateCirclePointCloud.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += eigen3
