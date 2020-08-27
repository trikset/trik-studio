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

QT += widgets

links(qrkernel qrutils qrtext qrgui-preferences-dialog qrgui-tool-plugin-interface \
		robots-utils robots-kit-base robots-2d-model qextserialport \
		)

includes(plugins/robots/common/ev3Kit \
		plugins/robots/common/kitBase \
		plugins/robots/common/twoDModel \
		plugins/robots/utils \
		qrtext \
                plugins/robots/thirdparty/hidapi/hidapi \
)


# libusb headers contain dirty code
gcc:QMAKE_CXXFLAGS += -fpermissive

#HIDAPI windows/hid.c contains bad code (2019, June)
win32: QMAKE_CXXFLAGS += -Wno-error=cast-qual
win32: LIBS += -lsetupapi

macx: LIBS += -framework CoreFoundation

linux {
    CONFIG *= link_pkgconfig
    PKGCONFIG += libudev
}

HEADERS += \
	$$PWD/include/ev3Kit/robotModel/ev3RobotModelBase.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3Display.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3Speaker.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3Motor.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3Led.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3Compass.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3DCIRSeeker.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3ACIRSeeker.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3NXTColorSensorV2Color.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3NXTColorSensorV2RGB.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3NXTColorSensorV2Passive.h \
	$$PWD/include/ev3Kit/robotModel/parts/ev3NXTColorSensorV2Raw.h \
	$$PWD/include/ev3Kit/blocks/ev3BlocksFactory.h \
	$$PWD/include/ev3Kit/communication/commandConstants.h \
	$$PWD/include/ev3Kit/communication/ev3DirectCommand.h \
	$$PWD/include/ev3Kit/communication/ev3RobotCommunicationThread.h \
	$$PWD/include/ev3Kit/communication/bluetoothRobotCommunicationThread.h \
	$$PWD/include/ev3Kit/communication/usbRobotCommunicationThread.h \
	$$PWD/src/blocks/details/speakerBlock.h \
	$$PWD/src/blocks/details/beepBlock.h \
	$$PWD/src/blocks/details/playToneBlock.h \
	$$PWD/src/blocks/details/drawCircleBlock.h \
	$$PWD/src/blocks/details/drawLineBlock.h \
	$$PWD/src/blocks/details/drawPixelBlock.h \
	$$PWD/src/blocks/details/drawRectBlock.h \
	$$PWD/src/blocks/details/ev3EnginesBackwardBlock.h \
	$$PWD/src/blocks/details/ev3EnginesForwardBlock.h \
	$$PWD/src/blocks/details/ledBlock.h \
	$$PWD/src/blocks/details/ev3ReadRGBBlock.h \

SOURCES += \
	$$PWD/src/robotModel/ev3RobotModelBase.cpp \
	$$PWD/src/robotModel/parts/ev3Display.cpp \
	$$PWD/src/robotModel/parts/ev3Speaker.cpp \
	$$PWD/src/robotModel/parts/ev3Motor.cpp \
	$$PWD/src/robotModel/parts/ev3Led.cpp \
	$$PWD/src/robotModel/parts/ev3Compass.cpp \
	$$PWD/src/robotModel/parts/ev3DCIRSeeker.cpp \
	$$PWD/src/robotModel/parts/ev3ACIRSeeker.cpp \
	$$PWD/src/robotModel/parts/ev3NXTColorSensorV2Color.cpp \
	$$PWD/src/robotModel/parts/ev3NXTColorSensorV2RGB.cpp \
	$$PWD/src/robotModel/parts/ev3NXTColorSensorV2Passive.cpp \
	$$PWD/src/robotModel/parts/ev3NXTColorSensorV2Raw.cpp \
	$$PWD/src/blocks/ev3BlocksFactory.cpp \
	$$PWD/src/blocks/details/speakerBlock.cpp \
	$$PWD/src/blocks/details/beepBlock.cpp \
	$$PWD/src/blocks/details/playToneBlock.cpp \
	$$PWD/src/blocks/details/drawCircleBlock.cpp \
	$$PWD/src/blocks/details/drawLineBlock.cpp \
	$$PWD/src/blocks/details/drawPixelBlock.cpp \
	$$PWD/src/blocks/details/drawRectBlock.cpp \
	$$PWD/src/blocks/details/ev3EnginesBackwardBlock.cpp \
	$$PWD/src/blocks/details/ev3EnginesForwardBlock.cpp \
	$$PWD/src/blocks/details/ledBlock.cpp \
	$$PWD/src/blocks/details/ev3ReadRGBBlock.cpp \
	$$PWD/src/communication/ev3DirectCommand.cpp \
	$$PWD/src/communication/ev3RobotCommunicationThread.cpp \
	$$PWD/src/communication/bluetoothRobotCommunicationThread.cpp \
	$$PWD/src/communication/hidapi.c \
	$$PWD/src/communication/usbRobotCommunicationThread.cpp \

TRANSLATIONS = \
	$$PWD/../../../../qrtranslations/ru/plugins/robots/ev3Kit_ru.ts \
	$$PWD/../../../../qrtranslations/fr/plugins/robots/ev3Kit_fr.ts \
