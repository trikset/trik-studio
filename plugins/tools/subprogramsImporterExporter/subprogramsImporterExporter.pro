# Copyright 2018 CyberTech Labs Ltd.
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

TEMPLATE = lib
CONFIG += plugin

QT += widgets core

include(../../../global.pri)

DESTDIR = $$DESTDIR/plugins/tools/

links(qrkernel qrrepo qrutils qrgui-tool-plugin-interface)

TRANSLATIONS = \
	$$PWD/../../../qrtranslations/ru/plugins/subprogramsImporterExporter_ru.ts \

INCLUDEPATH += \
	$$PWD/../../../qrutils/ \

HEADERS = \
	subprogramsImporterExporterPlugin.h \
	subprogramsCollectionDialog.h

SOURCES = \
	subprogramsImporterExporterPlugin.cpp \
	subprogramsCollectionDialog.cpp

FORMS += \
	subprogramsCollectionDialog.ui
