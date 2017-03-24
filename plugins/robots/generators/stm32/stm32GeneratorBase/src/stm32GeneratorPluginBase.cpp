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

#include "stm32GeneratorBase/stm32GeneratorPluginBase.h"

#include <qrutils/inFile.h>

#include <stm32Kit/blocks/stm32BlocksFactory.h>

#include "include/stm32GeneratorBase/robotModel/stm32GeneratorRobotModel.h"

using namespace stm32;

//Stm32GeneratorPluginBase::Stm32GeneratorPluginBase(kitBase::robotModel::RobotModelInterface * const robotModel
//        , kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory)
//    : mRobotModel(robotModel)
//    , mBlocksFactory(blocksFactory)
//{
//}

Stm32GeneratorPluginBase::Stm32GeneratorPluginBase(const QString &robotName, const QString &robotFriendlyName
        , int priority)
    : mRobotModel(new robotModel::Stm32V62GeneratorRobotModel(kitId()
            , "stm32KitRobot", robotName, robotFriendlyName, priority))
    , mBlocksFactory(new blocks::Stm32BlocksFactory)
{
}

Stm32GeneratorPluginBase::~Stm32GeneratorPluginBase()
{
}

QString Stm32GeneratorPluginBase::kitId() const
{
	return "stm32Kit";
}

QList<kitBase::robotModel::RobotModelInterface *> Stm32GeneratorPluginBase::robotModels()
{
	return { mRobotModel.data() };
}

kitBase::blocksBase::BlocksFactoryInterface *Stm32GeneratorPluginBase::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return mBlocksFactory;
}

QList<kitBase::AdditionalPreferences *> Stm32GeneratorPluginBase::settingsWidgets()
{
	return {};
}

void Stm32GeneratorPluginBase::regenerateExtraFiles(const QFileInfo &newFileInfo)
{
	Q_UNUSED(newFileInfo);
}

kitBase::robotModel::RobotModelInterface &Stm32GeneratorPluginBase::robotModel() const
{
	return *mRobotModel.data();
}
