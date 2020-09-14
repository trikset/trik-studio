#force as a shared library
DEFINES += QSLOG_IS_SHARED_LIBRARY

include(qslog/QsLogSharedLibrary.pro)

TARGET=trikQsLog
#do not add a version major number to a name of dll
CONFIG += skip_target_version_ext
include(../../global.pri)
LIBS -= -ltrikQsLog
