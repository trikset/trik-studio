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

TARGET = robots-stm32-cpp-generator

include(../../../../../global.pri)

QT += widgets network

TEMPLATE = lib
CONFIG += plugin

win32 {
	DESTDIR ~= s,/,\\,g
	system(cmd /C "xcopy .\\libraries\\* $$DESTDIR\\libraries\\ /s /e /y")
}

unix:!macx {
	system(mkdir -p $$DESTDIR/libraries/; find ./libraries/ -name * -exec cp --parents {} $$DESTDIR/libraries \\;)
}

macx {
	system(mkdir -p $$DESTDIR/libraries/; find ./libraries/ -name * -exec rsync -R {} $$DESTDIR/libraries \\;)
}

DESTDIR = $$DESTDIR/plugins/tools/kitPlugins/

includes(plugins/robots/generators/stm32/stm32GeneratorBase \
		plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/common/stm32Kit \
		plugins/robots/utils \
		qrtext \
)

links(qrkernel qslog qrutils qrrepo qscintilla2 robots-generator-base robots-stm32-generator-base \
		robots-kit-base robots-stm32-kit robots-utils \
)

TRANSLATIONS = \
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/stm32CppGenerator_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/stm32CppGenerator_fr.ts \

HEADERS += \
	$$PWD/stm32CppGeneratorPlugin.h \
	$$PWD/stm32CppMasterGenerator.h \
	$$PWD/stm32CppControlFlowValidator.h \
	$$PWD/threadsValidator.h \
	$$PWD/emptyShell.h \

SOURCES += \
	$$PWD/stm32CppGeneratorPlugin.cpp \
	$$PWD/stm32CppMasterGenerator.cpp \
	$$PWD/stm32CppControlFlowValidator.cpp \
	$$PWD/threadsValidator.cpp \
	$$PWD/emptyShell.cpp \

RESOURCES = \
	$$PWD/stm32CppGenerator.qrc \
	$$PWD/templates.qrc \

DISTFILES += \
	templates/wait/gyroscope.t