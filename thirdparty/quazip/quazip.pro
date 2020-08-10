TARGET = quazip
TEMPLATE = lib

include (../../global.pri)
LIBS -= -ltrikQsLog

QMAKE_CXXFLAGS += -Wno-error=non-virtual-dtor -Wno-error=cast-qual
DEFINES += QUAZIP_BUILD
CONFIG+=staticlib
include (quazip/quazip/quazip.pri)
