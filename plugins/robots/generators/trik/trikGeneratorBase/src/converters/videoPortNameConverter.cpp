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

#include "videoPortNameConverter.h"

#include <qrutils/stringUtils.h>

using namespace trik::converters;

namespace {

QString cameraSourceFor(const kitBase::robotModel::PortInfo &port)
{
	// Reserved variable of a video detector port looks like "lineSensor", "colorSensor",
	// "objectSensorX", "objectSensorY", "objectSensorSize". Per-camera aliases put the camera
	// number right after the sensor name ("lineSensor1", "colorSensor3", "objectSensor1" etc).
	// Legacy object sensor names without a number are bound to the default camera (video2).
	const auto &reservedVariable = port.reservedVariable();
	QString number;
	if (reservedVariable.startsWith("lineSensor")) {
		number = reservedVariable.mid(QString("lineSensor").size());
	} else if (reservedVariable.startsWith("colorSensor")) {
		number = reservedVariable.mid(QString("colorSensor").size());
	} else if (reservedVariable.startsWith("objectSensor")) {
		const auto parameter = reservedVariable.mid(QString("objectSensor").size());
		if (parameter != "X" && parameter != "Y" && parameter != "Size") {
			number = parameter;
		}
	} else {
		return {};
	}

	for (auto &&symbol : number) {
		if (!symbol.isDigit()) {
			return {};
		}
	}

	const auto &camera = number == "1" ? "video1"
		: number == "2" ? "video2"
		: number == "3" ? "usb-camera"
		: "video2";
	return utils::StringUtils::wrap(camera);
}

}

VideoPortNameConverter::VideoPortNameConverter(const QList<kitBase::robotModel::PortInfo> &ports,
	generatorBase::simple::Binding::ConverterInterface *genericConverter)
	: mPorts(ports)
	, mGenericConverter(genericConverter)
{
}

VideoPortNameConverter::~VideoPortNameConverter()
{
	delete mGenericConverter;
}

QString VideoPortNameConverter::convert(const QString &portNameOrAlias) const
{
	kitBase::robotModel::PortInfo portInfo;
	for (auto &&port : mPorts) {
		if (port.name() == portNameOrAlias || port.nameAliases().contains(portNameOrAlias)) {
			portInfo = port;
			if (port.name() == portNameOrAlias) {
				break;
			}
		}
	}

	if (portInfo.isValid()) {
		const auto &cameraSource = cameraSourceFor(portInfo);
		if (!cameraSource.isEmpty()) {
			return cameraSource;
		}
	}

	return mGenericConverter->convert(portNameOrAlias);
}
