/* Copyright 2016-2017 CyberTech Labs Ltd.
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

#include "trikKitInterpreterCommon/trikEmulation/triksensoremu.h"

using namespace trik;

TrikSensorEmu::TrikSensorEmu(kitBase::robotModel::robotParts::ScalarSensor *sensor) : mSensor(sensor)
{
//	connect(sensor, &kitBase::robotModel::robotParts::ScalarSensor::newData)
}

int TrikSensorEmu::read()
{
	//mSensor->read(); test crash fixes

	/* Sensor values are calculated by timer in the UI Thread
	 * (subscription in plugins/robots/interpreters/trikKitInterpreterCommon/src/TrikBrick)
	 * and are also forced through TrikScriptRunner when calculating sensor values (except for Gyroscope::read).
	 * This heavily loads the UI thread, and in incorrect code like
	 *	while (true) { brick.sensor("A1").read() }
	 * the UI thread gets blocked by sensor reading tasks, making the user interface non-functional.
	 * As a hot-fix, it is proposed to calculate values using Qt::BlockingQueuedConnection,
	 * which will force waiting for the sensor value calculation instead of queuing new tasks
	 * in the UI thread every few milliseconds (this is critical for reading from sensors
	 * whose handlers take a relatively long time, as the queue contains many reading tasks
	 * while returning old (already calculated) sensor values, which forces new tasks to be queued). */
	QMetaObject::invokeMethod(mSensor, "read", Qt::BlockingQueuedConnection);
	return mSensor->lastData(); // not best, race conditions?
}
