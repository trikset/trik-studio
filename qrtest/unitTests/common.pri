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

isEmpty(TEMPLATE): TEMPLATE = app

include(../../global.pri)

# after global.pri sets DESTDIR
equals(TEMPLATE, app) {
    CONFIG += testcase testcase_no_bundle no_testcase_installs
}

QT += widgets

#clang complains about GTest headers, but error is produced for macro expansion and -isystem does not help
#probably, this can be fixed if we stop using old-school obsolete MOCK_METHOD{0-9} instead of newer MOCK_METHOD
clang:QMAKE_CXXFLAGS += -Wno-error=gnu-zero-variadic-macro-arguments

SOURCES += $$PWD/mainTest.cpp

INCLUDEPATH += \
	$$PWD/ \
	$$PWD/../../ \
	$$PWD/testUtils/include \

# the line below suppresses warnings generated by google's headers
QMAKE_CXXFLAGS += \
    -isystem $$PWD/../thirdparty/googletest/googletest/googletest/include \
    -isystem $$PWD/../thirdparty/googletest/googletest/googlemock/include \

links(googletest qrkernel)
