/* Copyright 2019 Iakov Kirilenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

//This file is used to force C compiler instead of C++ one
//until */hid.c files are made compatible with C++
#include <qglobal.h>
#if defined(Q_OS_LINUX)
#include <errno.h>
#include "plugins/robots/thirdparty/hidapi/linux/hid.c"
int hidapi_lasterror() { return errno; }
#elif defined(Q_OS_WIN)
#include <errhandlingapi.h>
int hidapi_lasterror() { return GetLastError(); }
#include "plugins/robots/thirdparty/hidapi/windows/hid.c"
#elif defined(Q_OS_DARWIN)
#include <errno.h>
#include "plugins/robots/thirdparty/hidapi/mac/hid.c"
int hidapi_lasterror() { return errno; }
#endif
