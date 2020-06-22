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

#include <trikKitInterpreterCommon/trikEmulation/trikColorSensorAdapter.h>

TrikColorSensorAdapter::TrikColorSensorAdapter(trik::robotModel::parts::TrikColorSensor *sensor)
	: mColorSensor(sensor)
{
}

trikControl::DeviceInterface::Status TrikColorSensorAdapter::status() const
{
	return Status::ready;
}

void TrikColorSensorAdapter::init(bool showOnDisplay)
{
	Q_UNUSED(showOnDisplay)
	mColorSensor->init();
}

QVector<int> TrikColorSensorAdapter::read(int m, int n)
{
	// TODO: TRIK color sensor for 2D model should read with image coordinates
	Q_UNUSED(m)
	Q_UNUSED(n)
	QMetaObject::invokeMethod(mColorSensor, "read");
	return mColorSensor->lastData(); // hopefully the same format
}

void TrikColorSensorAdapter::stop()
{
}
