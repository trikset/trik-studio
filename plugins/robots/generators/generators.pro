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
	trikV62QtsGenerator \
	trikPythonGeneratorLibrary \
	trikV62PythonGenerator \
	nxtGeneratorBase \
	nxtOsekCGenerator \
	ev3GeneratorBase \
	ev3RbfGenerator \
	pioneerLuaGenerator \

trikGeneratorBase.subdir = $$PWD/trik/trikGeneratorBase
trikQtsGeneratorLibrary.subdir = $$PWD/trik/trikQtsGeneratorLibrary
trikV62QtsGenerator.subdir = $$PWD/trik/trikV62QtsGenerator
trikPythonGeneratorLibrary.subdir = $$PWD/trik/trikPythonGeneratorLibrary
trikV62PythonGenerator.subdir = $$PWD/trik/trikV62PythonGenerator
nxtGeneratorBase.subdir = $$PWD/nxt/nxtGeneratorBase
nxtOsekCGenerator.subdir = $$PWD/nxt/nxtOsekCGenerator
ev3GeneratorBase.subdir = $$PWD/ev3/ev3GeneratorBase
ev3RbfGenerator.subdir = $$PWD/ev3/ev3RbfGenerator
pioneerLuaGenerator.subdir = $$PWD/pioneer/pioneerLuaGenerator

trikGeneratorBase.depends = generatorBase
trikQtsGeneratorLibrary.depends = trikGeneratorBase
trikV62QtsGenerator.depends = trikQtsGeneratorLibrary
trikPythonGeneratorLibrary.depends = trikGeneratorBase
trikV62PythonGenerator.depends = trikPythonGeneratorLibrary
nxtGeneratorBase.depends = generatorBase
nxtOsekCGenerator.depends = nxtGeneratorBase
ev3GeneratorBase.depends = generatorBase
ev3RbfGenerator.depends = ev3GeneratorBase
pioneerLuaGenerator.depends = generatorBase

CONFIG(trik_retired_features) {
}
