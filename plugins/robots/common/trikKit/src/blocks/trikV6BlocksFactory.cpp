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

#include <kitBase/blocksBase/common/clearEncoderBlock.h>
#include <kitBase/blocksBase/common/waitForEncoderBlock.h>

#include "details/trikEnginesBackwardBlock.h"
#include "details/trikEnginesForwardBlock.h"

using namespace trik::blocks;
using namespace trik::blocks::details;
using namespace kitBase::blocksBase::common;

qReal::interpretation::Block *TrikV6BlocksFactory::produceBlock(const qReal::Id &element)
{
	if (elementMetatypeIs(element, "TrikAngularServo")) {
		// AngularServo and EnginesForward are synonyms since angular and radial servos are controlled the same way.
		return new details::TrikEnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "TrikV4ClearEncoder")
			|| elementMetatypeIs(element, "TrikV6ClearEncoder"))
	{
		return new ClearEncoderBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "TrikWaitForEncoder")) {
		return new WaitForEncoderBlock(mRobotModelManager->model());
	}

	return TrikBlocksFactoryBase::produceBlock(element);
}

qReal::IdList TrikV6BlocksFactory::providedBlocks() const
{
	qReal::IdList result;

	result << TrikBlocksFactoryBase::providedBlocks();

	result
			<< id("TrikV6ClearEncoder")
			<< id("TrikAngularServo")
			<< id("TrikWaitForEncoder")
	;

    return result;
}

qReal::IdList TrikV6BlocksFactory::blocksToDisable() const
{
    qReal::IdList result;

    result << TrikBlocksFactoryBase::blocksToDisable();
    result
            << id("TrikV6ClearEncoder")
            << id("TrikAngularServo")
            << id("TrikWaitForEncoder")
            << id("TrikV6EnginesBackward")
            << id("TrikAngularServo")
            << id("TrikV6EnginesStop")
            << id("TrikPlayTone")
            << id("TrikV6ClearEncoder")
            << id("TrikSystem")
            << id("TrikWriteToFile")
            << id("TrikRemoveFile")
            << id("TrikInitVideoStreaming")
            << id("TrikInitCamera")
            << id("TrikDetect")
            << id("TrikDetectorToVariable")
            << id("TrikWaitForLight")
            << id("TrikWaitForSonarDistance")
            << id("TrikWaitForIRDistance")
            << id("TrikWaitForTouchSensor")
            << id("TrikWaitForGyroscope")
            << id("TrikWaitForAccelerometer")
            << id("TrikWaitForMotion")
            << id("TrikWaitForEncoder")
            << id("TrikWaitForButton")
            << id("TrikWaitGamepadButton")
            << id("TrikWaitPadPress")
            << id("TrikWaitGamepadWheel")
            << id("TrikWaitGamepadDisconnect")
            << id("TrikWaitGamepadConnect")
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
            << id("TrikSay")
            << id("TrikSendMessage")
            << id("TrikWaitForMessage")

            << id("CommentBlock")
            << id("Subprogram")
            << id("PrintText")
            << id("ClearScreen")
            << id("Function")
            << id("Fork")
            << id("Join")
            << id("KillThread")
            << id("SendMessageThreads")
            << id("ReceiveMessageThreads")
            << id("Timer")

            << id("TrikLed")

	        << id("IfBlock")
	        << id("FiBlock")
	        << id("SwitchBlock")
	        << id("Loop")
	        << id("VariableInit")
	        << id("Randomizer")

//               <element name="InitialNode"/>
//               <element name="FinalNode"/>
//               <element name="Function"/>
//               <element name="IfBlock"/>
//               <element name="FiBlock"/>
//               <element name="SwitchBlock"/>
//               <element name="Loop"/>
//               <element name="Subprogram"/>
//               <element name="Fork"/>
//               <element name="Join"/>
//               <element name="KillThread"/>
//               <element name="VariableInit"/>
//               <element name="Randomizer"/>
//               <element name="CommentBlock"/>
    ;

    return result;
}
