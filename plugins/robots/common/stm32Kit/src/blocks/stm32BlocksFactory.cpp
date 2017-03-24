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

#include "stm32Kit/blocks/stm32BlocksFactory.h"

#include <kitBase/blocksBase/common/enginesStopBlock.h>

#include <kitBase/blocksBase/common/waitForTouchSensorBlock.h>
#include <kitBase/blocksBase/common/waitForLightSensorBlock.h>
#include <kitBase/blocksBase/common/waitForAccelerometerBlock.h>
#include <kitBase/blocksBase/common/waitForGyroscopeSensorBlock.h>
#include <kitBase/blocksBase/common/waitForSonarDistanceBlock.h>
#include <kitBase/blocksBase/common/waitForButtonBlock.h>
#include <kitBase/blocksBase/common/getButtonCodeBlock.h>
#include <kitBase/blocksBase/common/clearEncoderBlock.h>
#include <kitBase/blocksBase/common/waitForEncoderBlock.h>
#include <kitBase/robotModel/robotParts/rangeSensor.h>

#include <qrutils/interpreter/blocks/emptyBlock.h>

#include "details/stm32EnginesBackwardBlock.h"
#include "details/stm32EnginesForwardBlock.h"

#include "details/smileBlock.h"
#include "details/drawPixelBlock.h"
#include "details/drawLineBlock.h"
#include "details/drawRectBlock.h"
#include "details/drawEllipseBlock.h"
#include "details/drawArcBlock.h"
#include "details/setPainterWidthBlock.h"
#include "details/setPainterColorBlock.h"
#include "details/setBackgroundBlock.h"
#include "details/initCameraBlock.h"
#include "details/detectLineBlock.h"
#include "details/lineDetectorToVariable.h"
#include "details/initVideoStreamingBlock.h"
#include "details/waitForMotionBlock.h"
#include "details/speakerBlock.h"
#include "details/ledBlock.h"
#include "details/sayBlock.h"
#include "details/systemCommandBlock.h"

#include "details/waitGamepadButtonBlock.h"
#include "details/waitGamepadConnectBlock.h"
#include "details/waitGamepadDisconnectBlock.h"
#include "details/waitGamepadWheelBlock.h"
#include "details/waitPadPressBlock.h"

#include "details/writeToFileBlock.h"
#include "details/removeFileBlock.h"

#include "stm32Kit/robotModel/parts/stm32InfraredSensor.h"
#include "stm32Kit/robotModel/parts/stm32SonarSensor.h"

using namespace stm32::blocks;
using namespace stm32::blocks::details;
using namespace kitBase::blocksBase::common;

qReal::interpretation::Block *Stm32BlocksFactory::produceBlock(const qReal::Id &element)
{
	if (elementMetatypeIs(element, "Stm32V62AngularServo")) {
		// AngularServo and EnginesForward are synonyms since angular and radial servos are controlled the same way.
		return new details::Stm32EnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32V62ClearEncoder")) {
		return new ClearEncoderBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32V62WaitForEncoder")) {
		return new WaitForEncoderBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "Stm32V6EnginesBackward")) {
		return new details::Stm32EnginesBackwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32V6EnginesForward")) {
		return new details::Stm32EnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32PlayTone")) {
		return new SpeakerBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32V4EnginesStop")
			|| elementMetatypeIs(element, "Stm32V6EnginesStop"))
	{
		return new EnginesStopBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "Stm32Say")) {
		return new SayBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32System")) {
		return new SystemCommandBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32InitCamera")) {
		return new InitCameraBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32Detect")) {
		return new DetectLineBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32DetectorToVariable")) {
		return new LineDetectorToVariableBlock();
	} else if (elementMetatypeIs(element, "Stm32InitVideoStreaming")) {
		return new InitVideoStreamingBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32SendMessage")) {
		return new qReal::interpretation::blocks::EmptyBlock();
	} else if (elementMetatypeIs(element, "Stm32WaitForMessage")) {
		return new qReal::interpretation::blocks::EmptyBlock();
	} else if (elementMetatypeIs(element, "Stm32Led")) {
		return new LedBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "Stm32WaitForIRDistance")) {
		return new WaitForSonarDistanceBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::Stm32InfraredSensor>());
	} else if (elementMetatypeIs(element, "Stm32WaitForTouchSensor")) {
		return new WaitForTouchSensorBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitForLight")) {
		return new WaitForLightSensorBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitForSonarDistance")) {
		return new WaitForSonarDistanceBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::Stm32SonarSensor>());
	} else if (elementMetatypeIs(element, "Stm32WaitForGyroscope")) {
		return new WaitForGyroscopeSensorBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitForAccelerometer")) {
		return new WaitForAccelerometerSensorBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitForMotion")) {
		return new WaitForMotionBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "Stm32WaitForButton")) {
		return new WaitForButtonBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32SetPainterColor")) {
		return new SetPainterColorBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32SetPainterWidth")) {
		return new SetPainterWidthBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32DrawPixel")) {
		return new DrawPixelBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32DrawLine")) {
		return new DrawLineBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32DrawRect")) {
		return new DrawRectBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32DrawEllipse")) {
		return new DrawEllipseBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32DrawArc")) {
		return new DrawArcBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32Smile")) {
		return new SmileBlock(mRobotModelManager->model(), false);
	} else if (elementMetatypeIs(element, "Stm32SadSmile")) {
		return new SmileBlock(mRobotModelManager->model(), true);
	} else if (elementMetatypeIs(element, "Stm32SetBackground")) {
		return new SetBackgroundBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "Stm32WaitGamepadButton")) {
		return new WaitGamepadButtonBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitPadPress")) {
		return new WaitPadPressBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitGamepadWheel")) {
		return new WaitGamepadWheelBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitGamepadDisconnect")) {
		return new WaitGamepadDisconnectBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32WaitGamepadConnect")) {
		return new WaitGamepadConnectBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "Stm32WriteToFile")) {
		return new WriteToFileBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "Stm32RemoveFile")) {
		return new RemoveFileBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "GetButtonCode")) {
		return new GetButtonCodeBlock(mRobotModelManager->model());
	}

	return nullptr;
}

qReal::IdList Stm32BlocksFactory::providedBlocks() const
{
	qReal::IdList result;

	result << id("Stm32PlayTone");

	result
			<< id("Stm32V6EnginesBackward")
			<< id("Stm32V6EnginesForward")
			<< id("Stm32V6EnginesStop")
			;

	result
			<< id("Stm32Say")
			<< id("Stm32Led")
			<< id("Stm32System")
			<< id("Stm32InitCamera")
			<< id("Stm32Detect")
			<< id("Stm32DetectorToVariable")
			<< id("Stm32InitVideoStreaming")
			<< id("Stm32SendMessage")
			<< id("Stm32WaitForMessage")
			;

	result
			<< id("Stm32WaitForTouchSensor")
			<< id("Stm32WaitForLight")
			<< id("Stm32WaitForIRDistance")
			<< id("Stm32WaitForSonarDistance")
			<< id("Stm32WaitForGyroscope")
			<< id("Stm32WaitForAccelerometer")
			<< id("Stm32WaitForMotion")
			<< id("Stm32WaitForButton")
			;

	result
			<< id("Stm32SetPainterColor")
			<< id("Stm32SetPainterWidth")
			<< id("Stm32DrawPixel")
			<< id("Stm32DrawLine")
			<< id("Stm32DrawRect")
			<< id("Stm32DrawEllipse")
			<< id("Stm32DrawArc")
			<< id("Stm32Smile")
			<< id("Stm32SadSmile")
			<< id("Stm32SetBackground")
			;

	result
			<< id("Stm32WaitGamepadButton")
			<< id("Stm32WaitPadPress")
			<< id("Stm32WaitGamepadWheel")
			<< id("Stm32WaitGamepadDisconnect")
			<< id("Stm32WaitGamepadConnect")
			;

	result
			<< id("Stm32WriteToFile")
			<< id("Stm32RemoveFile")
			;

	result << id("GetButtonCode");

	result
	        << id("Stm32V62AngularServo")
	        << id("Stm32V62ClearEncoder")
	        << id("Stm32V62WaitForEncoder")
	;

	return result;
}

qReal::IdList Stm32BlocksFactory::blocksToDisable() const
{
	qReal::IdList result;

	// because there is no implementation for it
	if (!mRobotModelManager->model().name().contains("Gen")) {
		result << id("Stm32PlayTone");
	}

	if (mRobotModelManager->model().name().contains("TwoD")) {
		result
				<< id("Stm32WaitForGyroscope")
				<< id("Stm32WaitForAccelerometer")
				<< id("Stm32System")
				<< id("Stm32WaitForMotion")
				<< id("Stm32SendMessage")
				<< id("Stm32WaitForMessage")
				<< id("Stm32WaitGamepadButton")
				<< id("Stm32WaitPadPress")
				<< id("Stm32WaitGamepadWheel")
				<< id("Stm32WaitGamepadDisconnect")
				<< id("Stm32WaitGamepadConnect")
				<< id("Stm32InitVideoStreaming")
				;
	}

	return result;
}
