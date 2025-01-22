QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += _RasPi

SOURCES += \
    DistanceSensor.cpp \
    chartcontainer.cpp \
    main.cpp \
    noaaweatherfetcher.cpp \
    smartrainharvest.cpp

HEADERS += \
    DistanceSensor.h \
    chartcontainer.h \
    noaaweatherfetcher.h \
    smartrainharvest.h

FORMS += \
    smartrainharvest.ui

LIBS += -lwiringPi

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
