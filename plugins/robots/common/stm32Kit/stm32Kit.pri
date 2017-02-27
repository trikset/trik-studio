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

includes(plugins/robots/common/stm32Kit \
		plugins/robots/common/kitBase \
		plugins/robots/utils \
		qrtext \
)

links(qrkernel qrutils qrtext qrgui-preferences-dialog qrgui-tool-plugin-interface \
		robots-utils robots-kit-base qextserialport qslog \
)

HEADERS += \
	$$PWD/include/stm32Kit/robotModel/stm32RobotModelBase.h \
	$$PWD/include/stm32Kit/robotModel/stm32RobotModelV6.h \
	$$PWD/include/stm32Kit/robotModel/stm32RobotModelV62.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32ColorSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32Display.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32GamepadButton.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32GamepadConnectionIndicator.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32GamepadPad.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32GamepadPadPressSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32GamepadWheel.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32Speaker.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32PowerMotor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32ServoMotor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32InfraredSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32Led.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32LineSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32MotionSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32SonarSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32ObjectSensor.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32Shell.h \
	$$PWD/include/stm32Kit/robotModel/parts/stm32MotorsAggregator.h \
	$$PWD/include/stm32Kit/blocks/stm32BlocksFactoryBase.h \
	$$PWD/include/stm32Kit/blocks/stm32V6BlocksFactory.h \
	$$PWD/include/stm32Kit/blocks/stm32V62BlocksFactory.h \
	$$PWD/src/blocks/details/setBackgroundBlock.h \
	$$PWD/src/blocks/details/smileBlock.h \
	$$PWD/src/blocks/details/stm32EnginesForwardBlock.h \
	$$PWD/src/blocks/details/stm32EnginesBackwardBlock.h \
	$$PWD/src/blocks/details/waitForMotionBlock.h \
	$$PWD/src/blocks/details/speakerBlock.h \
	$$PWD/src/blocks/details/ledBlock.h \
	$$PWD/src/blocks/details/sayBlock.h \
	$$PWD/src/blocks/details/systemCommandBlock.h \
	$$PWD/src/blocks/details/waitGamepadButtonBlock.h \
	$$PWD/src/blocks/details/waitGamepadConnectBlock.h \
	$$PWD/src/blocks/details/waitGamepadDisconnectBlock.h \
	$$PWD/src/blocks/details/waitGamepadWheelBlock.h \
	$$PWD/src/blocks/details/waitPadPressBlock.h \
	$$PWD/src/blocks/details/drawLineBlock.h \
	$$PWD/src/blocks/details/drawPixelBlock.h \
	$$PWD/src/blocks/details/drawRectBlock.h \
	$$PWD/src/blocks/details/drawEllipseBlock.h \
	$$PWD/src/blocks/details/drawArcBlock.h \
	$$PWD/src/blocks/details/setPainterWidthBlock.h \
	$$PWD/src/blocks/details/setPainterColorBlock.h \
	$$PWD/src/blocks/details/initCameraBlock.h \
	$$PWD/src/blocks/details/detectLineBlock.h \
	$$PWD/src/blocks/details/lineDetectorToVariable.h \
	$$PWD/src/blocks/details/initVideoStreamingBlock.h \
	$$PWD/src/blocks/details/writeToFileBlock.h \
	$$PWD/src/blocks/details/removeFileBlock.h \

SOURCES += \
	$$PWD/src/robotModel/stm32RobotModelBase.cpp \
	$$PWD/src/robotModel/stm32RobotModelV6.cpp \
	$$PWD/src/robotModel/stm32RobotModelV62.cpp \
	$$PWD/src/robotModel/parts/stm32ColorSensor.cpp \
	$$PWD/src/robotModel/parts/stm32Display.cpp \
	$$PWD/src/robotModel/parts/stm32GamepadButton.cpp \
	$$PWD/src/robotModel/parts/stm32GamepadConnectionIndicator.cpp \
	$$PWD/src/robotModel/parts/stm32GamepadPad.cpp \
	$$PWD/src/robotModel/parts/stm32GamepadPadPressSensor.cpp \
	$$PWD/src/robotModel/parts/stm32GamepadWheel.cpp \
	$$PWD/src/robotModel/parts/stm32InfraredSensor.cpp \
	$$PWD/src/robotModel/parts/stm32Led.cpp \
	$$PWD/src/robotModel/parts/stm32LineSensor.cpp \
	$$PWD/src/robotModel/parts/stm32MotionSensor.cpp \
	$$PWD/src/robotModel/parts/stm32ObjectSensor.cpp \
	$$PWD/src/robotModel/parts/stm32PowerMotor.cpp \
	$$PWD/src/robotModel/parts/stm32ServoMotor.cpp \
	$$PWD/src/robotModel/parts/stm32SonarSensor.cpp \
	$$PWD/src/robotModel/parts/stm32Speaker.cpp \
	$$PWD/src/robotModel/parts/stm32Shell.cpp \
	$$PWD/src/robotModel/parts/stm32MotorsAggregator.cpp \
	$$PWD/src/blocks/stm32BlocksFactoryBase.cpp \
	$$PWD/src/blocks/stm32V6BlocksFactory.cpp \
	$$PWD/src/blocks/stm32V62BlocksFactory.cpp \
	$$PWD/src/blocks/details/setBackgroundBlock.cpp \
	$$PWD/src/blocks/details/smileBlock.cpp \
	$$PWD/src/blocks/details/stm32EnginesForwardBlock.cpp \
	$$PWD/src/blocks/details/stm32EnginesBackwardBlock.cpp \
	$$PWD/src/blocks/details/waitForMotionBlock.cpp \
	$$PWD/src/blocks/details/speakerBlock.cpp \
	$$PWD/src/blocks/details/ledBlock.cpp \
	$$PWD/src/blocks/details/sayBlock.cpp \
	$$PWD/src/blocks/details/systemCommandBlock.cpp \
	$$PWD/src/blocks/details/waitGamepadButtonBlock.cpp \
	$$PWD/src/blocks/details/waitGamepadConnectBlock.cpp \
	$$PWD/src/blocks/details/waitGamepadDisconnectBlock.cpp \
	$$PWD/src/blocks/details/waitGamepadWheelBlock.cpp \
	$$PWD/src/blocks/details/waitPadPressBlock.cpp \
	$$PWD/src/blocks/details/drawLineBlock.cpp \
	$$PWD/src/blocks/details/drawPixelBlock.cpp \
	$$PWD/src/blocks/details/drawRectBlock.cpp \
	$$PWD/src/blocks/details/drawEllipseBlock.cpp \
	$$PWD/src/blocks/details/drawArcBlock.cpp \
	$$PWD/src/blocks/details/setPainterWidthBlock.cpp \
	$$PWD/src/blocks/details/setPainterColorBlock.cpp \
	$$PWD/src/blocks/details/initCameraBlock.cpp \
	$$PWD/src/blocks/details/detectLineBlock.cpp \
	$$PWD/src/blocks/details/lineDetectorToVariable.cpp \
	$$PWD/src/blocks/details/initVideoStreamingBlock.cpp \
	$$PWD/src/blocks/details/writeToFileBlock.cpp \
	$$PWD/src/blocks/details/removeFileBlock.cpp \

TRANSLATIONS += \
	$$PWD/../../../../qrtranslations/ru/plugins/robots/stm32Kit_ru.ts \
	$$PWD/../../../../qrtranslations/fr/plugins/robots/stm32Kit_fr.ts \
