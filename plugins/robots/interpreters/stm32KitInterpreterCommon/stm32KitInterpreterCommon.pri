# Copyright 2015 CyberTech Labs Ltd.
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

includes(plugins/robots/common/kitBase \
		plugins/robots/common/twoDModel \
		plugins/robots/common/stm32Kit \
		plugins/robots/utils \
		qrtext \
		)

links(qrkernel qrutils qrtext qrgui-preferences-dialog qrgui-tool-plugin-interface \
		robots-utils robots-kit-base robots-2d-model robots-stm32-kit qextserialport qslog \
		)

HEADERS += \
	$$PWD/include/stm32KitInterpreterCommon/declSpec.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/display.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/speaker.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/button.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/powerMotor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/powerMotorsAggregator.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/servoMotor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/encoderSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/touchSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/lightSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/infraredSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/sonarSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/led.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/lineSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/motionSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/objectSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/colorSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/gyroscope.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/accelerometer.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/shell.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/gamepadButton.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/gamepadConnectionIndicator.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/gamepadPad.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/gamepadPadPressSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/real/parts/gamepadWheel.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDDisplay.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDSpeaker.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDInfraredSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDLed.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDLineSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDObjectSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDColorSensor.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/parts/twoDShell.h \
	$$PWD/include/stm32KitInterpreterCommon/robotModel/twoD/stm32TwoDRobotModel.h \
	$$PWD/include/stm32KitInterpreterCommon/stm32AdditionalPreferences.h \
	$$PWD/include/stm32KitInterpreterCommon/stm32DisplayWidget.h \
	$$PWD/include/stm32KitInterpreterCommon/stm32KitInterpreterPluginBase.h \

SOURCES += \
	$$PWD/src/robotModel/real/parts/display.cpp \
	$$PWD/src/robotModel/real/parts/speaker.cpp \
	$$PWD/src/robotModel/real/parts/button.cpp \
	$$PWD/src/robotModel/real/parts/powerMotor.cpp \
	$$PWD/src/robotModel/real/parts/powerMotorsAggregator.cpp \
	$$PWD/src/robotModel/real/parts/servoMotor.cpp \
	$$PWD/src/robotModel/real/parts/encoderSensor.cpp \
	$$PWD/src/robotModel/real/parts/touchSensor.cpp \
	$$PWD/src/robotModel/real/parts/lightSensor.cpp \
	$$PWD/src/robotModel/real/parts/infraredSensor.cpp \
	$$PWD/src/robotModel/real/parts/sonarSensor.cpp \
	$$PWD/src/robotModel/real/parts/led.cpp \
	$$PWD/src/robotModel/real/parts/lineSensor.cpp \
	$$PWD/src/robotModel/real/parts/objectSensor.cpp \
	$$PWD/src/robotModel/real/parts/colorSensor.cpp \
	$$PWD/src/robotModel/real/parts/motionSensor.cpp \
	$$PWD/src/robotModel/real/parts/gyroscope.cpp \
	$$PWD/src/robotModel/real/parts/accelerometer.cpp \
	$$PWD/src/robotModel/real/parts/shell.cpp \
	$$PWD/src/robotModel/real/parts/gamepadButton.cpp \
	$$PWD/src/robotModel/real/parts/gamepadConnectionIndicator.cpp \
	$$PWD/src/robotModel/real/parts/gamepadPad.cpp \
	$$PWD/src/robotModel/real/parts/gamepadPadPressSensor.cpp \
	$$PWD/src/robotModel/real/parts/gamepadWheel.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDDisplay.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDSpeaker.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDInfraredSensor.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDLineSensor.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDObjectSensor.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDColorSensor.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDLed.cpp \
	$$PWD/src/robotModel/twoD/parts/twoDShell.cpp \
	$$PWD/src/robotModel/twoD/stm32TwoDRobotModel.cpp \
	$$PWD/src/stm32AdditionalPreferences.cpp \
	$$PWD/src/stm32DisplayWidget.cpp \
	$$PWD/src/stm32KitInterpreterPluginBase.cpp \

FORMS += \
	$$PWD/src/stm32AdditionalPreferences.ui \
	$$PWD/src/stm32DisplayWidget.ui \

RESOURCES += \
	$$PWD/stm32KitInterpreterCommon.qrc \

TRANSLATIONS += \
	$$PWD/../../../../qrtranslations/ru/plugins/robots/stm32KitInterpreterCommon_ru.ts \
	$$PWD/../../../../qrtranslations/fr/plugins/robots/stm32KitInterpreterCommon_fr.ts \

OTHER_FILES += \
	$$PWD/stm32DefaultSettings.ini \
