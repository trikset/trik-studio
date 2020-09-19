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

#include "trikKit/blocks/trikV6BlocksFactory.h"

#include "details/trikForwardOneCellBlock.h"
#include "details/trikBackwardOneCellBlock.h"
#include "details/trikTurnRightBlock.h"
#include "details/trikTurnLeftBlock.h"

using namespace trik::blocks;
using namespace trik::blocks::details;

qReal::interpretation::Block *TrikV6BlocksFactory::produceBlock(const qReal::Id &element)
{
	if (elementMetatypeIs(element, "TrikForwardOneCell")) {
		return new ForwardOneCellBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "TrikBackwardOneCell")) {
		return new BackwardOneCellBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "TrikTurnRight")) {
		return new TurnRightBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "TrikTurnLeft")) {
		return new TurnLeftBlock(mRobotModelManager->model());
	}

	return TrikBlocksFactoryBase::produceBlock(element);
}

qReal::IdList TrikV6BlocksFactory::providedBlocks() const
{
	qReal::IdList result;

	if (mRobotModelManager->model().name().contains("TwoD")) {
		result << id("TrikForwardOneCell");
		result << id("TrikBackwardOneCell");
		result << id("TrikTurnRight");
		result << id("TrikTurnLeft");
	}

	// Drawing actions
	result
			<< id("TrikSetPainterColor")
			<< id("TrikSetPainterWidth")
			<< id("TrikDrawPixel")
			<< id("TrikDrawLine")
			<< id("TrikDrawRect")
			<< id("TrikDrawEllipse")
			<< id("TrikDrawArc")
			<< id("TrikSmile")
			<< id("TrikSadSmile")
			<< id("TrikSetBackground")
			;

	// Robots actions
	result
			<< id("TrikSay")
			<< id("TrikLed")
			<< id("GetButtonCode")
			;

	// Wait for button
	result
			<< id("TrikWaitForButton")
			;

	result << id("TrikPrintText");
	return result;
}
