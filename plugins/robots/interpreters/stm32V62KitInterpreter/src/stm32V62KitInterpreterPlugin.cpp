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

#include "stm32V62KitInterpreterPlugin.h"

using namespace stm32;

#include <stm32Kit/blocks/stm32V62BlocksFactory.h>

#include "robotModel/real/stm32V62RealRobotModel.h"
#include "robotModel/twoD/stm32V62TwoDRobotModel.h"

const QString kitIdString = "stm32V62Kit";

Stm32V62KitInterpreterPlugin::Stm32V62KitInterpreterPlugin()
	: Stm32KitInterpreterPluginBase()
{
	const auto realRobotModel = new robotModel::real::RealRobotModel(kitIdString, "stm32V62KitRobot");
	const auto twoDRobotModel = new robotModel::twoD::TwoDRobotModel(*realRobotModel);
	const auto blocksFactory = new blocks::Stm32V62BlocksFactory();
	initKitInterpreterPluginBase(realRobotModel, twoDRobotModel, blocksFactory);
}

QString Stm32V62KitInterpreterPlugin::kitId() const
{
	return kitIdString;
}

QString Stm32V62KitInterpreterPlugin::friendlyKitName() const
{
	return tr("STM32");
}
