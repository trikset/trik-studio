# Copyright 2016 CyberTech Labs Ltd.
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

QT += widgets network

includes( \
		plugins/robots/generators/stm32/stm32CppGeneratorLibrary \
		plugins/robots/generators/stm32/stm32GeneratorBase \
		plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/common/stm32Kit \
		plugins/robots/utils \
		qrtext \
)

links(qrkernel qslog qrutils qrrepo qscintilla2 robots-generator-base robots-stm32-generator-base \
		robots-kit-base robots-stm32-kit robots-utils robots-stm32-cpp-generator-library \
)

TRANSLATIONS = \
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/stm32V62CppGenerator_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/stm32V62CppGenerator_fr.ts \

HEADERS += \
	$$PWD/stm32V62CppGeneratorPlugin.h \

SOURCES += \
	$$PWD/stm32V62CppGeneratorPlugin.cpp \
