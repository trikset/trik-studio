TEMPLATE = lib

include(../../../../global.pri)

unix:QT = core
else:QT = core gui

include(qextserialport/src/qextserialport.pri)
#include(qextserialport/doc/doc.pri)

CONFIG += warn_off

DEFINES += QEXTSERIALPORT_BUILD_SHARED
