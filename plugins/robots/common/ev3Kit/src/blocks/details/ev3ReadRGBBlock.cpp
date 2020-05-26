/* Copyright 2020 CyberTech Labs Ltd.
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

#include "ev3ReadRGBBlock.h"

#include "kitBase/robotModel/robotModelUtils.h"
#include "kitBase/robotModel/robotParts/vectorSensor.h"

using namespace ev3::blocks::details;
using namespace kitBase::robotModel;

Ev3ReadRGBBlock::Ev3ReadRGBBlock(RobotModelInterface &robotModel)
	: mRobotModel(robotModel)
{
}

void Ev3ReadRGBBlock::run()
{
	auto portName = eval<QString>("Port");

	if (errorsOccured()) {
		return;
	}
	auto port = RobotModelUtils::findPort(mRobotModel, portName, input);

	auto const sensor = RobotModelUtils::findDevice<robotParts::VectorSensor>(mRobotModel, port);
	if (sensor) {
		mConnections << connect(sensor, &robotParts::VectorSensor::newData, [this](const QVariant &data){
				disconnectSensor();
				auto color = data.value<QVector<int>>();
				if (color.length() != 3) {
					error(tr("Sensor reading should consist of three components"));
				} else {
					evalCode(stringProperty("RVariable") + " = " + QString::number(color[0]));
					evalCode(stringProperty("GVariable") + " = " + QString::number(color[1]));
					evalCode(stringProperty("BVariable") + " = " + QString::number(color[2]));
					emit done(mNextBlockId);
				}
			});
		mConnections << connect(sensor, &robotParts::VectorSensor::failure, [this](){
				disconnectSensor();
				error(tr("Sensor reading failed"));
			});

		sensor->read();
	} else {
		error(tr("Color raw sensor is not configured on port %2").arg(port.userFriendlyName()));
	}
}

void Ev3ReadRGBBlock::disconnectSensor()
{
	for (auto &&c: mConnections) {
		disconnect(c);
	}
	mConnections.clear();
}
