//This file is used to force C compiler instead of C++ one
//until */hid.c files are made compatible with C++
#if defined(Q_OS_LINUX)
#include <errno.h>
#include "plugins/robots/thirdparty/hidapi/linux/hid.c"
static int hidapi_lasterror() { return errno; }
#elif defined(Q_OS_WIN)
#include <errhandlingapi.h>
static int hidapi_lasterror() { return GetLastError(); }
#include "plugins/robots/thirdparty/hidapi/windows/hid.c"
#elif defined(Q_OS_MAC)
#include <errno.h>
#include "plugins/robots/thirdparty/hidapi/mac/hid.c"
static int hidapi_lasterror() { return errno; }
#endif


