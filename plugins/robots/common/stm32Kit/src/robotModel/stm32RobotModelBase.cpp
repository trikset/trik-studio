/* Copyright 2013-2016 CyberTech Labs Ltd., Grigorii Zimin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "stm32Kit/robotModel/stm32RobotModelBase.h"

#include <kitBase/robotModel/robotParts/display.h>
#include <kitBase/robotModel/robotParts/speaker.h>
#include <kitBase/robotModel/robotParts/button.h>
#include <kitBase/robotModel/robotParts/gyroscopeSensor.h>
#include <kitBase/robotModel/robotParts/accelerometerSensor.h>

#include <kitBase/robotModel/robotParts/encoderSensor.h>

#include <kitBase/robotModel/robotParts/touchSensor.h>
#include <kitBase/robotModel/robotParts/lightSensor.h>

#include "stm32Kit/robotModel/parts/stm32ServoMotor.h"
#include "stm32Kit/robotModel/parts/stm32PowerMotor.h"
#include "stm32Kit/robotModel/parts/stm32MotorsAggregator.h"
#include "stm32Kit/robotModel/parts/stm32InfraredSensor.h"
#include "stm32Kit/robotModel/parts/stm32SonarSensor.h"
#include "stm32Kit/robotModel/parts/stm32MotionSensor.h"
#include "stm32Kit/robotModel/parts/stm32ColorSensor.h"
#include "stm32Kit/robotModel/parts/stm32LineSensor.h"
#include "stm32Kit/robotModel/parts/stm32ObjectSensor.h"
#include "stm32Kit/robotModel/parts/stm32Led.h"
#include "stm32Kit/robotModel/parts/stm32Shell.h"
#include "stm32Kit/robotModel/parts/stm32GamepadButton.h"
#include "stm32Kit/robotModel/parts/stm32GamepadConnectionIndicator.h"
#include "stm32Kit/robotModel/parts/stm32GamepadPad.h"
#include "stm32Kit/robotModel/parts/stm32GamepadPadPressSensor.h"
#include "stm32Kit/robotModel/parts/stm32GamepadWheel.h"

using namespace stm32::robotModel;
using namespace kitBase::robotModel;

Stm32RobotModelBase::Stm32RobotModelBase(const QString &kitId, const QString &robotId)
	: CommonRobotModel(kitId, robotId)
{
	QList<DeviceInfo> const analogPortConnections = {
		lightSensorInfo()
		, infraredSensorInfo()
		, touchSensorInfo()
	};

	addAllowedConnection(PortInfo("DisplayPort", output), { displayInfo() });
	addAllowedConnection(PortInfo("SpeakerPort", output), { speakerInfo() });

	addAllowedConnection(PortInfo("Left", input, {}, "buttonLeft"), { buttonInfo() });
	addAllowedConnection(PortInfo("Right", input, {}, "buttonRight"), { buttonInfo() });
	addAllowedConnection(PortInfo("Up", input, {}, "buttonUp"), { buttonInfo() });
	addAllowedConnection(PortInfo("Down", input, {}, "buttonDown"), { buttonInfo() });
	addAllowedConnection(PortInfo("Enter", input, {}, "buttonEnter"), { buttonInfo() });
	addAllowedConnection(PortInfo("Esc", input, {}, "buttonEsc"), { buttonInfo() });

	addAllowedConnection(PortInfo("M1", output, { "М1" }), { powerMotorInfo() });
	addAllowedConnection(PortInfo("M2", output, { "М2" }), { powerMotorInfo() });
	addAllowedConnection(PortInfo("M3", output, { "М3" }), { powerMotorInfo() });
	addAllowedConnection(PortInfo("M4", output, { "М4" }), { powerMotorInfo() });
	addAllowedConnection(PortInfo("MAll", output, { "MAll" }), { powerMotorsAggregatorInfo() });

	addAllowedConnection(PortInfo("PA0", input, { "PA0" }, "sensorPA0"), analogPortConnections);
	addAllowedConnection(PortInfo("PA1", input, { "PA1" }, "sensorPA1"), analogPortConnections);
	addAllowedConnection(PortInfo("PA2", input, { "PA2" }, "sensorPA2"), analogPortConnections);
	addAllowedConnection(PortInfo("PA3", input, { "PA3" }, "sensorPA3"), analogPortConnections);
	addAllowedConnection(PortInfo("PA4", input, { "PA4" }, "sensorPA4"), analogPortConnections);
	addAllowedConnection(PortInfo("PA5", input, { "PA5" }, "sensorPA5"), analogPortConnections);
	addAllowedConnection(PortInfo("PA6", input, { "PA6" }, "sensorPA6"), analogPortConnections);
	addAllowedConnection(PortInfo("PA7", input, { "PA7" }, "sensorPA7"), analogPortConnections);

//	addAllowedConnection(PortInfo("A1", input, { "А1" }, "sensorA1"), analogPortConnections);
//	addAllowedConnection(PortInfo("A2", input, { "А2" }, "sensorA2"), analogPortConnections);
//	addAllowedConnection(PortInfo("A3", input, { "А3" }, "sensorA3"), analogPortConnections);
//	addAllowedConnection(PortInfo("A4", input, { "А4" }, "sensorA4"), analogPortConnections);
//	addAllowedConnection(PortInfo("A5", input, { "А5" }, "sensorA5"), analogPortConnections);
//	addAllowedConnection(PortInfo("A6", input, { "А6" }, "sensorA6"), analogPortConnections);

//	addAllowedConnection(PortInfo("D1", input, {}, "sensorD1"), { sonarSensorInfo() });
//	addAllowedConnection(PortInfo("D2", input, {}, "sensorD2"), { sonarSensorInfo() });

	addAllowedConnection(PortInfo("GyroscopePort", input, {}, "gyroscope", PortInfo::ReservedVariableType::vector)
			, { gyroscopeInfo() });

	addAllowedConnection(PortInfo("AccelerometerPort", input, {}, "accelerometer"
			, PortInfo::ReservedVariableType::vector), { accelerometerInfo() });

	addAllowedConnection(PortInfo("LedPort", output), { ledInfo() });

	addAllowedConnection(PortInfo("LineSensorPort", tr("Line sensor"), input, { "Stm32LineSensorPort" }, "lineSensor"
			, PortInfo::ReservedVariableType::vector), { lineSensorInfo() });

	addAllowedConnection(PortInfo("ObjectSensorXPort", input, {}, "objectSensorX"), { objectSensorInfo() });
	addAllowedConnection(PortInfo("ObjectSensorYPort", input, {}, "objectSensorY"), { objectSensorInfo() });
	addAllowedConnection(PortInfo("ObjectSensorSizePort", input, {}, "objectSensorSize"), { objectSensorInfo() });

	addAllowedConnection(PortInfo("ColorSensorRPort", input, {}, "colorSensorR"), { colorSensorInfo() });
	addAllowedConnection(PortInfo("ColorSensorGPort", input, {}, "colorSensorG"), { colorSensorInfo() });
	addAllowedConnection(PortInfo("ColorSensorBPort", input, {}, "colorSensorB"), { colorSensorInfo() });

	addAllowedConnection(PortInfo("ShellPort", output), { shellInfo() });

	addAllowedConnection(PortInfo("GamepadPad1PosPort", input, {}, "gamepadPad1"
			, PortInfo::ReservedVariableType::vector), { gamepadPadInfo() });
	addAllowedConnection(PortInfo("GamepadPad2PosPort", input, {}, "gamepadPad2"
			, PortInfo::ReservedVariableType::vector), { gamepadPadInfo() });

	addAllowedConnection(PortInfo("GamepadPad1PressedPort", input, {}, "gamepadPad1Pressed")
			, { gamepadPadPressSensorInfo() });
	addAllowedConnection(PortInfo("GamepadPad2PressedPort", input, {}, "gamepadPad2Pressed")
			, { gamepadPadPressSensorInfo() });

	addAllowedConnection(PortInfo("GamepadWheelPort", input, {}, "gamepadWheel"), { gamepadWheelInfo() });

	addAllowedConnection(PortInfo("GamepadButton1Port", input, {}, "gamepadButton1"), { gamepadButtonInfo() });
	addAllowedConnection(PortInfo("GamepadButton2Port", input, {}, "gamepadButton2"), { gamepadButtonInfo() });
	addAllowedConnection(PortInfo("GamepadButton3Port", input, {}, "gamepadButton3"), { gamepadButtonInfo() });
	addAllowedConnection(PortInfo("GamepadButton4Port", input, {}, "gamepadButton4"), { gamepadButtonInfo() });
	addAllowedConnection(PortInfo("GamepadButton5Port", input, {}, "gamepadButton5"), { gamepadButtonInfo() });

	addAllowedConnection(PortInfo("GamepadConnectionIndicatorPort", input, {}, "gamepadConnected")
			, { gamepadConnectionIndicatorInfo() });

	addAllowedConnection(PortInfo("S1", output, {}), { servoMotorInfo() });
	addAllowedConnection(PortInfo("S2", output, {}), { servoMotorInfo() });
	addAllowedConnection(PortInfo("S3", output, {}), { servoMotorInfo() });
	addAllowedConnection(PortInfo("S4", output, {}), { servoMotorInfo() });
	addAllowedConnection(PortInfo("S5", output, {}), { servoMotorInfo() });
	addAllowedConnection(PortInfo("S6", output, {}), { servoMotorInfo() });

	addAllowedConnection(PortInfo("E1", input, { "M1", "Е1" }, "encoder1"), { encoderInfo() });
	addAllowedConnection(PortInfo("E2", input, { "M2", "Е2" }, "encoder2"), { encoderInfo() });
	addAllowedConnection(PortInfo("E3", input, { "M3", "Е3" }, "encoder3"), { encoderInfo() });
	addAllowedConnection(PortInfo("E4", input, { "M4", "Е4" }, "encoder4"), { encoderInfo() });
}

QList<PortInfo> Stm32RobotModelBase::configurablePorts() const
{
	QList<PortInfo> const digitalPorts = {
			  PortInfo("D1", input, {}, "sensorD1")
			, PortInfo("D2", input, {}, "sensorD2")
			};

	return CommonRobotModel::configurablePorts() + digitalPorts + QList<PortInfo>{PortInfo("LineSensorPort"
			, tr("Line sensor"), input, { "Stm32LineSensorPort" }, "lineSensor"
			, PortInfo::ReservedVariableType::vector)};
}

QList<DeviceInfo> Stm32RobotModelBase::convertibleBases() const
{
	return { DeviceInfo::create<robotParts::TouchSensor>()
		, DeviceInfo::create<robotParts::LightSensor>()
		, DeviceInfo::create<parts::Stm32InfraredSensor>()
		, DeviceInfo::create<parts::Stm32SonarSensor>()
		, DeviceInfo::create<parts::Stm32MotionSensor>()
		, DeviceInfo::create<parts::Stm32LineSensor>()
	};
}

DeviceInfo Stm32RobotModelBase::displayInfo() const
{
	return DeviceInfo::create<robotParts::Display>();
}

DeviceInfo Stm32RobotModelBase::speakerInfo() const
{
	return DeviceInfo::create<robotParts::Speaker>();
}

DeviceInfo Stm32RobotModelBase::buttonInfo() const
{
	return DeviceInfo::create<robotParts::Button>();
}

DeviceInfo Stm32RobotModelBase::powerMotorInfo() const
{
	return DeviceInfo::create<robotParts::Motor>();
}

DeviceInfo Stm32RobotModelBase::powerMotorsAggregatorInfo() const
{
	return DeviceInfo::create<robotParts::MotorsAggregator>();
}

DeviceInfo Stm32RobotModelBase::servoMotorInfo() const
{
	return DeviceInfo::create<robotParts::Motor>();
}

DeviceInfo Stm32RobotModelBase::encoderInfo() const
{
	return DeviceInfo::create<robotParts::EncoderSensor>();
}

DeviceInfo Stm32RobotModelBase::touchSensorInfo() const
{
	return DeviceInfo::create<robotParts::TouchSensor>();
}

DeviceInfo Stm32RobotModelBase::lightSensorInfo() const
{
	return DeviceInfo::create<robotParts::LightSensor>();
}

DeviceInfo Stm32RobotModelBase::infraredSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32InfraredSensor>();
}

DeviceInfo Stm32RobotModelBase::sonarSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32SonarSensor>();
}

DeviceInfo Stm32RobotModelBase::motionSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32MotionSensor>();
}

DeviceInfo Stm32RobotModelBase::gyroscopeInfo() const
{
	return DeviceInfo::create<robotParts::GyroscopeSensor>();
}

DeviceInfo Stm32RobotModelBase::accelerometerInfo() const
{
	return DeviceInfo::create<robotParts::AccelerometerSensor>();
}

DeviceInfo Stm32RobotModelBase::ledInfo() const
{
	return DeviceInfo::create<parts::Stm32Led>();
}

DeviceInfo Stm32RobotModelBase::lineSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32LineSensor>();
}

DeviceInfo Stm32RobotModelBase::colorSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32ColorSensor>();
}

DeviceInfo Stm32RobotModelBase::objectSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32ObjectSensor>();
}

DeviceInfo Stm32RobotModelBase::shellInfo() const
{
	return DeviceInfo::create<parts::Stm32Shell>();
}

DeviceInfo Stm32RobotModelBase::gamepadButtonInfo() const
{
	return DeviceInfo::create<parts::Stm32GamepadButton>();
}

DeviceInfo Stm32RobotModelBase::gamepadPadInfo() const
{
	return DeviceInfo::create<parts::Stm32GamepadPad>();
}

DeviceInfo Stm32RobotModelBase::gamepadPadPressSensorInfo() const
{
	return DeviceInfo::create<parts::Stm32GamepadPadPressSensor>();
}

DeviceInfo Stm32RobotModelBase::gamepadWheelInfo() const
{
	return DeviceInfo::create<parts::Stm32GamepadWheel>();
}

DeviceInfo Stm32RobotModelBase::gamepadConnectionIndicatorInfo() const
{
	return DeviceInfo::create<parts::Stm32GamepadConnectionIndicator>();
}

QHash<QString, int> Stm32RobotModelBase::buttonCodes() const
{
	QHash<QString, int> result;
	result["LeftButton"] = 105;
	result["RightButton"] = 106;
	result["UpButton"] = 103;
	result["DownButton"] = 108;
	result["EnterButton"] = 28;
	result["PowerButton"] = 116;
	result["EscButton"] = 1;
	return result;
}
