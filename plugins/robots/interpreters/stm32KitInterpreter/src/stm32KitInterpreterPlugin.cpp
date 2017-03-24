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

#include "stm32KitInterpreterPlugin.h"

#include <QtWidgets/QApplication>

using namespace stm32KitInterpreter;

Stm32KitInterpreterPlugin::Stm32KitInterpreterPlugin()
    : mRobotModel(kitId())
{
}

QString Stm32KitInterpreterPlugin::kitId() const
{
	return "stm32Kit";
}

QString Stm32KitInterpreterPlugin::friendlyKitName() const
{
	return tr("STM32");
}

QList<kitBase::robotModel::RobotModelInterface *> Stm32KitInterpreterPlugin::robotModels()
{
	return QList<kitBase::robotModel::RobotModelInterface *>() << &mRobotModel;
}

kitBase::blocksBase::BlocksFactoryInterface *Stm32KitInterpreterPlugin::blocksFactoryFor(
        const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return nullptr;
}

QList<kitBase::AdditionalPreferences *> Stm32KitInterpreterPlugin::settingsWidgets()
{
	return {nullptr};
}

QList<qReal::ActionInfo> Stm32KitInterpreterPlugin::customActions()
{
	return {};
}

QList<qReal::HotKeyActionInfo> Stm32KitInterpreterPlugin::hotKeyActions()
{
	return {};
}

QIcon Stm32KitInterpreterPlugin::iconForFastSelector(
        const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon();
}

