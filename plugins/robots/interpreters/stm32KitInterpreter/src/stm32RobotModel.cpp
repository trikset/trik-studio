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

#include "stm32RobotModel.h"

using namespace stm32KitInterpreter;

Stm32RobotModel::Stm32RobotModel(const QString &kitId)
    : kitBase::robotModel::CommonRobotModel(kitId, "")
{
}

QString Stm32RobotModel::name() const
{
	return "Stm32Model";
}

QString Stm32RobotModel::friendlyName() const
{
	return tr("STM32 model");
}

bool Stm32RobotModel::needsConnection() const
{
	return false;
}

int Stm32RobotModel::priority() const
{
	return 0;
}
