#force as a shared library
DEFINES += QSLOG_IS_SHARED_LIBRARY

include(qslog/QsLogSharedLibrary.pro)
unset(VERSION)
unset(DESTDIR)
unset(MOC_DIR)
unset(OBJECTS_DIR)

TARGET=trikQsLog
VERSION=
#do not add a version major number to a name of dll
CONFIG += skip_target_version_ext
include(../../global.pri)
LIBS -= -ltrikQsLog
