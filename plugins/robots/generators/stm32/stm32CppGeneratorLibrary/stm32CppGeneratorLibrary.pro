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

TARGET = robots-stm32-cpp-generator-library

include(../../../../../global.pri)

QT += widgets network

TEMPLATE = lib

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
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/stm32CppGeneratorLibrary_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/stm32CppGeneratorLibrary_fr.ts \

HEADERS += \
	$$PWD/include/stm32CppGeneratorLibrary/stm32CppGeneratorPluginBase.h \
	$$PWD/src/stm32CppMasterGenerator.h \
	$$PWD/src/stm32CppControlFlowValidator.h \
	$$PWD/src/threadsValidator.h \
	$$PWD/src/emptyShell.h \

SOURCES += \
	$$PWD/src/stm32CppGeneratorPluginBase.cpp \
	$$PWD/src/stm32CppMasterGenerator.cpp \
	$$PWD/src/stm32CppControlFlowValidator.cpp \
	$$PWD/src/threadsValidator.cpp \
	$$PWD/src/emptyShell.cpp \

RESOURCES = \
	$$PWD/stm32CppGeneratorLibrary.qrc \
	$$PWD/templates.qrc \

DISTFILES += \
	templates/wait/gyroscope.t