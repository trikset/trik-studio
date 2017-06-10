# Copyright 2007-2015 QReal Research Group, CyberTech Labs Ltd.
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

SUBDIRS = \
	generatorBase \
	trikGeneratorBase \
	trikQtsGeneratorLibrary \
	trikV6QtsGenerator \
	trikV62QtsGenerator \
	trikCppGeneratorLibrary \
	trikV6CppGenerator \
	trikV62CppGenerator \
	trikFSharpGeneratorLibrary \
	trikV6FSharpGenerator \
	trikV62FSharpGenerator \
	trikPascalABCGeneratorLibrary \
	trikV6PascalABCGenerator \
	trikV62PascalABCGenerator \
	trikPythonGeneratorLibrary \
	trikV62PythonGenerator \
	trikV6RuntimeUploaderPlugin \
	trikV62RuntimeUploaderPlugin \
	trikSharpBinaries \
	nxtGeneratorBase \
	nxtOsekCGenerator \
	nxtRussianCGenerator \
	ev3GeneratorBase \
	ev3RbfGenerator \
	stm32GeneratorBase \
	stm32CppGenerator \

trikGeneratorBase.subdir = $$PWD/trik/trikGeneratorBase
trikQtsGeneratorLibrary.subdir = $$PWD/trik/trikQtsGeneratorLibrary
trikV6QtsGenerator.subdir = $$PWD/trik/trikV6QtsGenerator
trikV62QtsGenerator.subdir = $$PWD/trik/trikV62QtsGenerator
trikCppGeneratorLibrary.subdir = $$PWD/trik/trikCppGeneratorLibrary
trikV6CppGenerator.subdir = $$PWD/trik/trikV6CppGenerator
trikV62CppGenerator.subdir = $$PWD/trik/trikV62CppGenerator
trikFSharpGeneratorLibrary.subdir = $$PWD/trik/trikFSharpGeneratorLibrary
trikV6FSharpGenerator.subdir = $$PWD/trik/trikV6FSharpGenerator
trikV62FSharpGenerator.subdir = $$PWD/trik/trikV62FSharpGenerator
trikPascalABCGeneratorLibrary.subdir = $$PWD/trik/trikPascalABCGeneratorLibrary
trikV6PascalABCGenerator.subdir = $$PWD/trik/trikV6PascalABCGenerator
trikV62PascalABCGenerator.subdir = $$PWD/trik/trikV62PascalABCGenerator
trikPythonGeneratorLibrary.subdir = $$PWD/trik/trikPythonGeneratorLibrary
trikV62PythonGenerator.subdir = $$PWD/trik/trikV62PythonGenerator
trikV6RuntimeUploaderPlugin.subdir = $$PWD/trik/trikV6RuntimeUploaderPlugin
trikV62RuntimeUploaderPlugin.subdir = $$PWD/trik/trikV62RuntimeUploaderPlugin
trikSharpBinaries.subdir = $$PWD/trik/trikSharpBinaries
nxtGeneratorBase.subdir = $$PWD/nxt/nxtGeneratorBase
nxtOsekCGenerator.subdir = $$PWD/nxt/nxtOsekCGenerator
nxtRussianCGenerator.subdir = $$PWD/nxt/nxtRussianCGenerator
ev3GeneratorBase.subdir = $$PWD/ev3/ev3GeneratorBase
ev3RbfGenerator.subdir = $$PWD/ev3/ev3RbfGenerator
stm32GeneratorBase.subdir = $$PWD/stm32/stm32GeneratorBase
stm32CppGenerator.subdir = $$PWD/stm32/stm32CppGenerator

trikGeneratorBase.depends = generatorBase
trikQtsGeneratorLibrary.depends = trikGeneratorBase
trikV6QtsGenerator.depends = trikQtsGeneratorLibrary
trikV62QtsGenerator.depends = trikQtsGeneratorLibrary
trikCppGeneratorLibrary.depends = trikGeneratorBase
trikV6CppGenerator.depends = trikCppGeneratorLibrary
trikV62CppGenerator.depends = trikCppGeneratorLibrary
trikFSharpGeneratorLibrary.depends = trikGeneratorBase
trikV6FSharpGenerator.depends = trikFSharpGeneratorLibrary
trikV62FSharpGenerator.depends = trikFSharpGeneratorLibrary
trikPascalABCGeneratorLibrary.depends = trikGeneratorBase
trikV6PascalABCGenerator.depends = trikPascalABCGeneratorLibrary
trikV62PascalABCGenerator.depends = trikPascalABCGeneratorLibrary
trikPythonGeneratorLibrary.depends = trikGeneratorBase
trikV62PythonGenerator.depends = trikPythonGeneratorLibrary
nxtGeneratorBase.depends = generatorBase
nxtOsekCGenerator.depends = nxtGeneratorBase
nxtRussianCGenerator.depends = nxtGeneratorBase
ev3GeneratorBase.depends = generatorBase
ev3RbfGenerator.depends = ev3GeneratorBase
stm32GeneratorBase.depends = generatorBase
stm32CppGenerator.depends = stm32GeneratorBase
