/* Copyright 2021 CyberTech Labs Ltd.
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

#include "trikKitInterpreterCommon/trikEmulation/triklidaremu.h"

using namespace trik;

TrikLidarEmu::TrikLidarEmu(kitBase::robotModel::robotParts::VectorSensor *lidar) : mLidar(lidar)
{
}

QVector<int> TrikLidarEmu::read() const
{
	return mLidar->lastData();
}

QVector<int> TrikLidarEmu::readRaw() const
{
	auto data = mLidar->lastData();
	QVector<int> res;
	for (auto val : data) {
		res.append(QVector<int>(100, val));
	}
	return res;
}
