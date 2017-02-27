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

#include "stm32Kit/blocks/stm32V6BlocksFactory.h"

#include <kitBase/blocksBase/common/clearEncoderBlock.h>
#include <kitBase/blocksBase/common/waitForEncoderBlock.h>

#include "details/stm32EnginesBackwardBlock.h"
#include "details/stm32EnginesForwardBlock.h"

using namespace stm32::blocks;
using namespace stm32::blocks::details;
using namespace kitBase::blocksBase::common;

qReal::interpretation::Block *Stm32V6BlocksFactory::produceBlock(const qReal::Id &element)
{
	if (elementMetatypeIs(element, "Stm32AngularServo")) {
		// AngularServo and EnginesForward are synonyms since angular and radial servos are controlled the same way.
		return new details::Stm32EnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32V4ClearEncoder")
			|| elementMetatypeIs(element, "Stm32V6ClearEncoder"))
	{
		return new ClearEncoderBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitForEncoder")) {
		return new WaitForEncoderBlock(mRobotModelManager->model());
	}

	return Stm32BlocksFactoryBase::produceBlock(element);
}

qReal::IdList Stm32V6BlocksFactory::providedBlocks() const
{
	qReal::IdList result;

	result << Stm32BlocksFactoryBase::providedBlocks();

	result
			<< id("Stm32V6ClearEncoder")
			<< id("Stm32AngularServo")
			<< id("Stm32WaitForEncoder")
	;

	return result;
}
