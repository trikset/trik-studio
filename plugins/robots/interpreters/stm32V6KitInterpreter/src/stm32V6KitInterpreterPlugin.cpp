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

#include "stm32V6KitInterpreterPlugin.h"

using namespace stm32;

#include <stm32Kit/blocks/stm32V6BlocksFactory.h>

#include "robotModel/real/stm32V6RealRobotModel.h"
#include "robotModel/twoD/stm32V6TwoDRobotModel.h"

const QString kitIdString = "stm32Kit";

Stm32V6KitInterpreterPlugin::Stm32V6KitInterpreterPlugin()
	: Stm32KitInterpreterPluginBase()
{
	const auto realRobotModel = new robotModel::real::Stm32V6RealRobotModel(kitIdString, "stm32KitRobot");
	const auto twoDRobotModel = new robotModel::twoD::Stm32V6TwoDRobotModel(*realRobotModel);
	const auto blocksFactory = new blocks::Stm32V6BlocksFactory();
	initKitInterpreterPluginBase(realRobotModel, twoDRobotModel, blocksFactory);
}

QString Stm32V6KitInterpreterPlugin::kitId() const
{
	return kitIdString;
}

QString Stm32V6KitInterpreterPlugin::friendlyKitName() const
{
	return tr("STM32 (model-2014)");
}

int Stm32V6KitInterpreterPlugin::priority() const
{
	return 10;  // Old case is more likely will be met for now.
}
