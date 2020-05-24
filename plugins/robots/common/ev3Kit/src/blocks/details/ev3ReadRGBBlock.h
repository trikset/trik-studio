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

#pragma once

#include <kitBase/blocksBase/robotsBlock.h>

namespace ev3 {
namespace blocks {
namespace details {

class Ev3ReadRGBBlock : public kitBase::blocksBase::RobotsBlock
{
	Q_OBJECT

public:
	explicit Ev3ReadRGBBlock(kitBase::robotModel::RobotModelInterface &robotModel);

	void run() override;

private:
	void disconnectSensor();

	kitBase::robotModel::RobotModelInterface &mRobotModel;
	QList<QMetaObject::Connection> mConnections;

};

}
}
}
