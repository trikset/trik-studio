TEMPLATE = lib

unix:QT = core
else:QT = core gui

include(../../../../global.pri)

include(qextserialport/src/qextserialport.pri)
#include(qextserialport/doc/doc.pri)

CONFIG += warn_off

DEFINES += QEXTSERIALPORT_BUILD_SHARED
