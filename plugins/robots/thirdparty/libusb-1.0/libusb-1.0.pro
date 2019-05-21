# Copyright 2015 QReal Research Group
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

TEMPLATE = subdirs

include(../../../../global.pri)

win32 {
	isEmpty(PKG_EXE): error(Please add path to platform dependent pkg-config in PATH)
#	This should work, but it always return success code and never call error
#	!system(pkg-config --exists libusb-1.0): error(Please install libusb-1.0)
	EXIST_LIBUSB = $$system(pkg-config --exists libusb-1.0 && echo true || echo false)
	!equals(EXIST_LIBUSB, "true"): error(Please install libusb-1.0)
	copyToDestdir($$system($$pkgConfigExecutable() libusb-1.0 --variable=prefix)\bin\libusb-1.0.dll, NOW)
}

macx {
	copyToDestdir(libusb-1.0.dylib, NOW)
}

CONFIG(clang) {
	QMAKE_CXXFLAGS += -Wno-error=zero-length-array -Wno-error=vla-extension
}
