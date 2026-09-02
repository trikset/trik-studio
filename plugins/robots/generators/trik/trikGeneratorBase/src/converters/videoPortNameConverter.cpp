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
	// "objectSensorX", "objectSensorY", "objectSensorSize" with an optional camera number suffix
	// ("lineSensor1" etc). Legacy names without a suffix are bound to the default camera (video2).
	const auto &reservedVariable = port.reservedVariable();
	if (!reservedVariable.startsWith("lineSensor") && !reservedVariable.startsWith("colorSensor")
		&& !reservedVariable.startsWith("objectSensorX")
		&& !reservedVariable.startsWith("objectSensorY")
		&& !reservedVariable.startsWith("objectSensorSize")) {
		return {};
	}

	QString suffix;
	for (int i = reservedVariable.size() - 1; i >= 0 && reservedVariable.at(i).isDigit(); --i) {
		suffix.prepend(reservedVariable.at(i));
	}

	const auto &camera = suffix == "1" ? "video1"
		: suffix == "2" ? "video2"
		: suffix == "3" ? "usb-camera"
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
