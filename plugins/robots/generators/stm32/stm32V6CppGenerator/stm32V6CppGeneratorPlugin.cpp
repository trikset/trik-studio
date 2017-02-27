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

#include "stm32V6CppGeneratorPlugin.h"

#include <stm32Kit/blocks/stm32V6BlocksFactory.h>
#include <stm32GeneratorBase/robotModel/stm32V6GeneratorRobotModel.h>

using namespace stm32;
using namespace stm32::cpp;
using namespace kitBase::robotModel;

Stm32V6CppGeneratorPlugin::Stm32V6CppGeneratorPlugin()
    : Stm32CppGeneratorPluginBase(new robotModel::Stm32V6GeneratorRobotModel(
					"stm32Kit"
					, "stm32KitRobot"
                    , "Stm32CppGeneratorRobotModel"
                    , tr("Generation (C++)")
					, 9 /* After 2D model */)
			, new blocks::Stm32V6BlocksFactory()
            , {":/stm32V6Cpp/templates", ":/stm32Cpp/templates"})
	, mModel(static_cast<robotModel::Stm32V6GeneratorRobotModel *>(robotModels().first()))
{
}

QString Stm32V6CppGeneratorPlugin::kitId() const
{
	return "stm32Kit";
}

void Stm32V6CppGeneratorPlugin::init(const kitBase::KitPluginConfigurator &configurator)
{
	Stm32CppGeneratorPluginBase::init(configurator);
	addShellDevice(*mModel);
}
