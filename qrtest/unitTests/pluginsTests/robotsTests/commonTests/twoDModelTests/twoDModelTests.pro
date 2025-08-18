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

TARGET = robots_twoDModel_unittests

include(../../../../common.pri)
include(../../../../../../plugins/robots/common/twoDModel/twoDModel.pri)
include(mocks.pri)

links(qrgui-preferences-dialog qrgui-text-editor qrgui-controller)

INCLUDEPATH += \
	../../../../mocks/plugins/robots/common/kitBase/include/ \
	../../../../../../plugins/robots/interpreters/trikKitInterpreterCommon/include/ \
	../../../../../../plugins/robots/common/twoDModel/ \
	../../../../../../plugins/robots/common/twoDModel/include/ \
	../../../../mocks/plugins/robots/common/twoDModel/include/  \

# Tests
HEADERS += \
	$$PWD/engineTests/constraintsTests/constraintsParserTests.h \
	$$PWD/engineTests/modelTests/modelParserTests.h \

SOURCES += \
	$$PWD/engineTests/constraintsTests/constraintsParserTests.cpp \
	$$PWD/engineTests/modelTests/modelParserTests.cpp \

# Support classes
HEADERS += \
	$$PWD/support/testTimeline.h \
	$$PWD/support/testObject.h \

SOURCES += \
	$$PWD/support/testTimeline.cpp \
	$$PWD/support/testObject.cpp \

OTHER_FILES += \
	$$PWD/data/pixelWorldModel.xml \
	$$PWD/data/cmWorldModel.xml \

message("JJJJJJJJJJJJJJJJJ: $$PWD/data/")
copyToDestdir($$PWD/data/, now)
