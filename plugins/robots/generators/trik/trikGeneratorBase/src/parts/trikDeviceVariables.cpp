/* Copyright 2007-2015 QReal Research Group
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

#include "trikDeviceVariables.h"

#include <QtCore/QMetaClassInfo>

using namespace trik::parts;

namespace {

QString videoSensorTemplatePath(const QString &reservedVariable)
{
	// Video detectors are described by reserved variables like "lineSensor", "colorSensor",
	// "objectSensorX", "objectSensorY", "objectSensorSize". Per-camera aliases put the camera
	// number right after the sensor name ("lineSensor1", "colorSensor3", "objectSensor1" etc).
	// Object sensor also has a vector form "objectSensorN" returning [x, y, size].
	QString detectorKind;
	if (reservedVariable.startsWith("lineSensor")) {
		detectorKind = "lineSensor";
	} else if (reservedVariable.startsWith("colorSensor")) {
		detectorKind = "colorSensor";
	} else if (reservedVariable.startsWith("objectSensor")) {
		const auto parameter = reservedVariable.mid(QString("objectSensor").size());
		if (parameter == "X" || parameter == "Y" || parameter == "Size") {
			detectorKind = "objectSensor" + parameter;
		} else {
			auto isCameraNumber = !parameter.isEmpty();
			for (auto &&symbol : parameter) {
				if (!symbol.isDigit()) {
					isCameraNumber = false;
					break;
				}
			}

			if (isCameraNumber) {
				detectorKind = "objectSensor";
			}
		}
	}

	const auto &templateName = detectorKind == "colorSensor" ? "ColorSensor"
		: detectorKind == "objectSensor" ? "ObjectSensor"
		: detectorKind == "objectSensorX" ? "ObjectSensorX"
		: detectorKind == "objectSensorY" ? "ObjectSensorY"
		: detectorKind == "objectSensorSize" ? "ObjectSensorSize"
		: detectorKind == "lineSensor" ? "LineSensor"
		: QString();

	return templateName.isEmpty() ? QString() : "videosensors/" + templateName + ".t";
}

}

QString TrikDeviceVariables::variableTemplatePath(const kitBase::robotModel::DeviceInfo &device,
	const kitBase::robotModel::PortInfo &port) const
{
	if (device.name() == "trikLineSensor" || device.name() == "trikObjectSensor"
		|| device.name() == "trikColorSensor") {
		auto templatePath = videoSensorTemplatePath(port.reservedVariable());
		if (!templatePath.isEmpty()) {
			return templatePath;
		}
	} else if (device.name() == "gyroscope" || device.name() == "accelerometer") {
		return QString("%1/%2.t").arg(device.name(), port.reservedVariable());
	} else if (device.name().startsWith("gamepad")) {
		return QString("gamepad/%1.t").arg(device.name());
	}

	return generatorBase::parts::DeviceVariables::variableTemplatePath(device, port);
}
