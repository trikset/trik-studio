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

#include "initCameraBlock.h"

using namespace stm32::blocks::details;

InitCameraBlock::InitCameraBlock(kitBase::robotModel::RobotModelInterface &robotModel)
	: kitBase::blocksBase::common::DeviceBlock<stm32::robotModel::parts::Stm32LineSensor>(robotModel)
{
}

void InitCameraBlock::doJob(stm32::robotModel::parts::Stm32LineSensor &camera)
{
	camera.init();
	emit done(mNextBlockId);
}
