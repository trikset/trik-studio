/* Copyright 2015 CyberTech Labs Ltd.
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

#include "stm32KitInterpreterCommon/robotModel/twoD/stm32TwoDRobotModel.h"

#include <QtGui/QColor>

#include <qrkernel/logging.h>

#include <kitBase/robotModel/robotModelUtils.h>
#include <kitBase/robotModel/robotParts/lightSensor.h>
#include <kitBase/robotModel/robotParts/touchSensor.h>

#include <stm32Kit/robotModel/parts/stm32LineSensor.h>
#include <stm32Kit/robotModel/parts/stm32ObjectSensor.h>
#include <stm32Kit/robotModel/parts/stm32ColorSensor.h>
#include <stm32Kit/robotModel/parts/stm32InfraredSensor.h>
#include <stm32Kit/robotModel/parts/stm32SonarSensor.h>
#include <stm32Kit/robotModel/parts/stm32Shell.h>
#include <stm32KitInterpreterCommon/stm32DisplayWidget.h>

#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDDisplay.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDSpeaker.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDShell.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDInfraredSensor.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDLed.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDLineSensor.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDObjectSensor.h"
#include "stm32KitInterpreterCommon/robotModel/twoD/parts/twoDColorSensor.h"

using namespace stm32::robotModel;
using namespace stm32::robotModel::twoD;
using namespace kitBase::robotModel;

Stm32TwoDRobotModel::Stm32TwoDRobotModel(RobotModelInterface &realModel)
	: twoDModel::robotModel::TwoDRobotModel(realModel)
	, mLeftWheelPort("M3")
	, mRightWheelPort("M4")
	, mDisplayWidget(new Stm32DisplayWidget())
{
	/// @todo: One day we will support gamepad in 2D model and there will be piece.
	/// But till that day gamepad ports must be killed cause they spam logs.
	const QList<PortInfo> realRobotPorts = CommonRobotModel::availablePorts();
	for (const PortInfo &port : realRobotPorts) {
		if (port.name().contains("Gamepad", Qt::CaseInsensitive)) {
			removeAllowedConnections(port);
		}
	}
}

robotParts::Device *Stm32TwoDRobotModel::createDevice(const PortInfo &port, const DeviceInfo &deviceInfo)
{
	if (deviceInfo.isA<robotParts::Display>()) {
		return new parts::Display(deviceInfo, port, *engine());
	}

	if (deviceInfo.isA<robotParts::Speaker>()) {
		return new parts::TwoDSpeaker(deviceInfo, port, *engine());
	}

	if (deviceInfo.isA<robotModel::parts::Stm32Shell>()) {
		parts::Shell * const shell = new parts::Shell(deviceInfo, port, *engine());
		// Error reporter will come only after global plugin init() is called. Shell is however
		// configured even later. So setting error reporter only when everything will be ready.
		connect(shell, &parts::Shell::configured, [=]() { shell->setErrorReporter(*mErrorReporter); });
		return shell;
	}

	if (deviceInfo.isA<robotModel::parts::Stm32InfraredSensor>()) {
		return new parts::TwoDInfraredSensor(deviceInfo, port, *engine());
	}

	if (deviceInfo.isA<robotModel::parts::Stm32Led>()) {
		return new parts::TwoDLed(deviceInfo, port, *engine());
	}

	if (deviceInfo.isA<robotModel::parts::Stm32LineSensor>()) {
		return new parts::LineSensor(deviceInfo, port, *engine());
	}

	if (deviceInfo.isA<robotModel::parts::Stm32ObjectSensor>()) {
		return new parts::ObjectSensor(deviceInfo, port);
	}

	if (deviceInfo.isA<robotModel::parts::Stm32ColorSensor>()) {
		return new parts::ColorSensor(deviceInfo, port);
	}

	return twoDModel::robotModel::TwoDRobotModel::createDevice(port, deviceInfo);
}

void Stm32TwoDRobotModel::onInterpretationStarted()
{
	robotModel::parts::Stm32Display * const display =
			RobotModelUtils::findDevice<robotModel::parts::Stm32Display>(*this, "DisplayPort");
	if (display) {
		display->clearScreen();
		display->setBackground(QColor(Qt::gray));
		display->redraw();
	} else {
		QLOG_WARN() << "STM32 display is not configured before intepretation start!";
	}

	parts::Shell * const shell = RobotModelUtils::findDevice<parts::Shell>(*this, "ShellPort");
	if (shell) {
		shell->reset();
	} else {
		QLOG_WARN() << "STM32 shell is not configured before intepretation start!";
	}
}

QString Stm32TwoDRobotModel::robotImage() const
{
	return ":icons/stm32TwoDRobot.svg";
}

PortInfo Stm32TwoDRobotModel::defaultLeftWheelPort() const
{
	return PortInfo(mLeftWheelPort, output);
}

PortInfo Stm32TwoDRobotModel::defaultRightWheelPort() const
{
	return PortInfo(mRightWheelPort, output);
}

twoDModel::engine::TwoDModelDisplayWidget *Stm32TwoDRobotModel::displayWidget() const
{
	return mDisplayWidget;
}

QString Stm32TwoDRobotModel::sensorImagePath(const DeviceInfo &deviceType) const
{
	if (deviceType.isA<kitBase::robotModel::robotParts::LightSensor>()) {
		return ":icons/twoDColorEmpty.svg";
	} else if (deviceType.isA<robotModel::parts::Stm32InfraredSensor>()) {
		return ":icons/twoDIrRangeSensor.svg";
	} else if (deviceType.isA<robotModel::parts::Stm32SonarSensor>()) {
		return ":icons/twoDUsRangeSensor.svg";
	} else if (deviceType.isA<robotModel::parts::Stm32LineSensor>()) {
		return ":icons/twoDVideoModule.svg";
	}

	return QString();
}

void Stm32TwoDRobotModel::setWheelPorts(const QString &leftWheelPort, const QString &rightWheelPort)
{
	mLeftWheelPort = leftWheelPort;
	mRightWheelPort = rightWheelPort;
}

QRect Stm32TwoDRobotModel::sensorImageRect(const kitBase::robotModel::DeviceInfo &deviceType) const
{
	if (deviceType.isA<robotParts::TouchSensor>()) {
			return QRect(-12, -5, 25, 10);
	} else if (deviceType.isA<robotParts::LightSensor>()) {
		return QRect(-6, -6, 12, 12);
	} else if (deviceType.isA<robotModel::parts::Stm32InfraredSensor>()) {
		return QRect(-18, -18, 36, 36);
	} else if (deviceType.isA<robotModel::parts::Stm32SonarSensor>()) {
		return QRect(-18, -18, 36, 36);
	} else if (deviceType.isA<robotModel::parts::Stm32LineSensor>()) {
		return QRect(-9, -9, 18, 18);
	}

	return QRect();
}

QHash<kitBase::robotModel::PortInfo, kitBase::robotModel::DeviceInfo> Stm32TwoDRobotModel::specialDevices() const
{
	QHash<PortInfo, DeviceInfo> result(twoDModel::robotModel::TwoDRobotModel::specialDevices());
	return result;
}

QPair<QPoint, qreal> Stm32TwoDRobotModel::specialDeviceConfiguration(const PortInfo &port) const
{
	if (port == PortInfo("LineSensorPort", input)) {
		return qMakePair(QPoint(1, 0), 0);
	}

	return twoDModel::robotModel::TwoDRobotModel::specialDeviceConfiguration(port);
}

QHash<QString, int> Stm32TwoDRobotModel::buttonCodes() const
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

void Stm32TwoDRobotModel::setErrorReporter(qReal::ErrorReporterInterface &errorReporter)
{
	mErrorReporter = &errorReporter;
}
