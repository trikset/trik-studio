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

#include <trikKitInterpreterCommon/trikEmulation/triklinesensoradapter.h>

TrikLineSensorAdapter::TrikLineSensorAdapter(trik::robotModel::parts::TrikLineSensor *sensor)
	: mLineSensor(sensor)
{
}

trikControl::DeviceInterface::Status TrikLineSensorAdapter::status() const
{
	return Status::ready;
}

void TrikLineSensorAdapter::init(bool showOnDisplay)
{
	Q_UNUSED(showOnDisplay);
	mLineSensor->init();
}

void TrikLineSensorAdapter::detect()
{
	mLineSensor->detectLine(); // hopefully the same
}

QVector<int> TrikLineSensorAdapter::read()
{
	/* Sensor values are calculated by timer in the UI Thread
	 * (subscription in plugins/robots/interpreters/trikKitInterpreterCommon/src/TrikBrick)
	 * and are also forced through TrikScriptRunner when calculating sensor values (except for Gyroscope::read).
	 * This heavily loads the UI thread, and in incorrect code like
	 *	while (true) { brick.lineSensor("video1").read(); }
	 * the UI thread gets blocked by sensor reading tasks, making the user interface non-functional.
	 * As a hot-fix, it is proposed to calculate values using Qt::BlockingQueuedConnection,
	 * which will force waiting for the sensor value calculation instead of queuing new tasks
	 * in the UI thread every few milliseconds (this is critical for reading from sensors
	 * whose handlers take a relatively long time, as the queue contains many reading tasks
	 * while returning old (already calculated) sensor values, which forces new tasks to be queued). */
	QMetaObject::invokeMethod(mLineSensor, "read", Qt::BlockingQueuedConnection);
	return mLineSensor->lastData(); // hopefully the same format
}

void TrikLineSensorAdapter::stop()
{
}

QVector<int> TrikLineSensorAdapter::getDetectParameters() const
{
	return mLineSensor->lastData(); // i guess?
}
