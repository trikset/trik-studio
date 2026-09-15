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

#pragma once

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>
#include <kitBase/robotModel/commonRobotModel.h>

namespace trik {
namespace robotModel {

class TrikRobotModelBase : public kitBase::robotModel::CommonRobotModel
{
	Q_OBJECT

public:
	TrikRobotModelBase(const QString &kitId, const QString &robotId);

	QList<kitBase::robotModel::PortInfo> configurablePorts() const override;
	QList<kitBase::robotModel::DeviceInfo> convertibleBases() const override;

	QHash<QString, int> buttonCodes() const override;

	/// Registers error reporter in a model.
	virtual void setErrorReporter(qReal::ErrorReporterInterface &errorReporter) = 0;

	/// Returns config file version that shall be on a robot to be able to use this model.
	virtual QString robotConfigFileVersion() const = 0;

protected:
	virtual kitBase::robotModel::DeviceInfo displayInfo() const;
	virtual kitBase::robotModel::DeviceInfo speakerInfo() const;
	virtual kitBase::robotModel::DeviceInfo buttonInfo() const;

	virtual kitBase::robotModel::DeviceInfo powerMotorInfo() const;
	virtual kitBase::robotModel::DeviceInfo powerMotorsAggregatorInfo() const;
	virtual kitBase::robotModel::DeviceInfo servoMotorInfo() const;
	virtual kitBase::robotModel::DeviceInfo encoderInfo() const;

	virtual kitBase::robotModel::DeviceInfo touchSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo lightSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo infraredSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo lidarSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo sonarSensorInfo() const;

	virtual kitBase::robotModel::DeviceInfo motionSensorInfo() const;

	virtual kitBase::robotModel::DeviceInfo gyroscopeInfo() const;
	virtual kitBase::robotModel::DeviceInfo accelerometerInfo() const;

	virtual kitBase::robotModel::DeviceInfo ledInfo() const;
	virtual kitBase::robotModel::DeviceInfo shellInfo() const;

	virtual kitBase::robotModel::DeviceInfo videoCameraInfo() const;
	virtual kitBase::robotModel::DeviceInfo lineSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo colorSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo objectSensorInfo() const;

	virtual kitBase::robotModel::DeviceInfo gamepadButtonInfo() const;
	virtual kitBase::robotModel::DeviceInfo gamepadPadInfo() const;
	virtual kitBase::robotModel::DeviceInfo gamepadPadPressSensorInfo() const;
	virtual kitBase::robotModel::DeviceInfo gamepadWheelInfo() const;
	virtual kitBase::robotModel::DeviceInfo gamepadConnectionIndicatorInfo() const;

	virtual kitBase::robotModel::PortInfo video2Port() const;
	virtual kitBase::robotModel::PortInfo lidarPort() const;
	virtual kitBase::robotModel::DeviceInfo networkInfo() const;

	/// Registers ports for video detectors (line/color/object sensors) on each video camera
	/// (video1, video2, usb-camera). Reserved variables get a camera number suffix ("lineSensor1",
	/// "colorSensor3", "objectSensorX2" etc). Called only by generator robot models, so interpreted
	/// (2D and real-time) models keep the single legacy port set untouched.
	void registerVideoDetectorAliases();
};

}
}
