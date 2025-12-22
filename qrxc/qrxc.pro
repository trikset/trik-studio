# Copyright 2007-2015 QReal Research Group
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

include(../global.pri)

CONFIG *= cmdline

HEADERS += \
	$$PWD/diagram.h \
	$$PWD/edgeType.h \
	$$PWD/editor.h \
	$$PWD/enumType.h \
	$$PWD/graphicType.h \
	$$PWD/label.h \
	$$PWD/linePort.h \
	$$PWD/nameNormalizer.h \
	$$PWD/nodeType.h \
	$$PWD/patternType.h \
	$$PWD/nonGraphicType.h \
	$$PWD/numericType.h \
	$$PWD/pointPort.h \
	$$PWD/port.h \
	$$PWD/property.h \
	$$PWD/sdftocpp.h \
	$$PWD/stringType.h \
	$$PWD/type.h \
	$$PWD/xmlCompiler.h \
	$$PWD/portType.h \
	$$PWD/circularPort.h \
	$$PWD/roleType.h \

SOURCES += \
	$$PWD/diagram.cpp \
	$$PWD/edgeType.cpp \
	$$PWD/editor.cpp \
	$$PWD/enumType.cpp \
	$$PWD/graphicType.cpp \
	$$PWD/label.cpp \
	$$PWD/linePort.cpp \
	$$PWD/main.cpp \
	$$PWD/nameNormalizer.cpp \
	$$PWD/nodeType.cpp \
	$$PWD/patternType.cpp \
	$$PWD/nonGraphicType.cpp \
	$$PWD/numericType.cpp \
	$$PWD/pointPort.cpp \
	$$PWD/port.cpp \
	$$PWD/property.cpp \
	$$PWD/sdftocpp.cpp \
	$$PWD/stringType.cpp \
	$$PWD/type.cpp \
	$$PWD/xmlCompiler.cpp \
	$$PWD/portType.cpp \
	$$PWD/circularPort.cpp \
	$$PWD/roleType.cpp \

TEMPLATE = app
QT += xml gui
CONFIG += console

links(qrutils)
