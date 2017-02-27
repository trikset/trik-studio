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

#include "stm32GeneratorFactory.h"

#include <generatorBase/converters/regexpMultiConverter.h>
#include <generatorBase/simpleGenerators/waitForButtonGenerator.h>
#include <generatorBase/lua/luaProcessor.h>

#include "simpleGenerators/detectGenerator.h"
#include "simpleGenerators/detectorToVariableGenerator.h"
#include "simpleGenerators/drawLineGenerator.h"
#include "simpleGenerators/drawPixelGenerator.h"
#include "simpleGenerators/drawRectGenerator.h"
#include "simpleGenerators/drawEllipseGenerator.h"
#include "simpleGenerators/drawArcGenerator.h"
#include "simpleGenerators/initCameraGenerator.h"
#include "simpleGenerators/initVideoStreamingGenerator.h"
#include "simpleGenerators/ledGenerator.h"
#include "simpleGenerators/playToneGenerator.h"
#include "simpleGenerators/waitForMessageGenerator.h"
#include "simpleGenerators/sadSmileGenerator.h"
#include "simpleGenerators/sayGenerator.h"
#include "simpleGenerators/sendMessageGenerator.h"
#include "simpleGenerators/setPainterWidthGenerator.h"
#include "simpleGenerators/setPainterColorGenerator.h"
#include "simpleGenerators/setBackgroundGenerator.h"
#include "simpleGenerators/smileGenerator.h"
#include "simpleGenerators/systemGenerator.h"
#include "simpleGenerators/stm32EnginesGenerator.h"
#include "simpleGenerators/waitForInfraredSensorGenerator.h"
#include "simpleGenerators/waitForMotionGenerator.h"
#include "simpleGenerators/waitGamepadButtonGenerator.h"
#include "simpleGenerators/waitGamepadConnectGenerator.h"
#include "simpleGenerators/waitGamepadDisconnectGenerator.h"
#include "simpleGenerators/waitGamepadWheelGenerator.h"
#include "simpleGenerators/waitPadPressGenerator.h"
#include "simpleGenerators/fileWriteGenerator.h"
#include "simpleGenerators/removeFileGenerator.h"
#include "parts/stm32DeviceVariables.h"

using namespace stm32;
using namespace stm32::simple;
using namespace generatorBase;
using namespace generatorBase::simple;

Stm32GeneratorFactory::Stm32GeneratorFactory(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, lua::LuaProcessor &luaProcessor
		, const QStringList &pathsToTemplates)
	: GeneratorFactoryBase(repo, errorReporter, robotModelManager, luaProcessor)
	, mPathsToTemplates(pathsToTemplates)
{
}

Stm32GeneratorFactory::~Stm32GeneratorFactory()
{
}

AbstractSimpleGenerator *Stm32GeneratorFactory::simpleGenerator(const qReal::Id &id
		, GeneratorCustomizer &customizer)
{
	const QString elementType = id.element();
	if (elementType.contains("EnginesForward")
			|| elementType.contains("EnginesBackward")
			|| elementType.contains("AngularServo"))
	{
		return new Stm32EnginesGenerator(mRepo, customizer, id, elementType, this);
	} else if (elementType.contains("Stm32PlayTone")) {
		return new PlayToneGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32DrawLine") {
		return new DrawLineGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32DrawPixel") {
		return new DrawPixelGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32DrawRect") {
		return new DrawRectGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32DrawEllipse") {
		return new DrawEllipseGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32DrawArc") {
		return new DrawArcGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32SetPainterWidth") {
		return new SetPainterWidthGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32SetPainterColor") {
		return new SetPainterColorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32Smile") {
		return new SmileGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32SadSmile") {
		return new SadSmileGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32Say") {
		return new SayGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32SendMessage") {
		return new SendMessageGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitForMessage") {
		return new WaitForMessageGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32SetBackground") {
		return new SetBackgroundGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32System") {
		return new SystemGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32Led") {
		return new LedGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32Detect") {
		return new DetectGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32InitCamera") {
		return new InitCameraGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32DetectorToVariable") {
		return new DetectorToVariableGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32InitVideoStreaming") {
		return new InitVideoStreamingGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitForMotion") {
		return new WaitForMotionGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitForIRDistance") {
		return new WaitForInfraredSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitGamepadButton") {
		return new WaitGamepadButtonGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitPadPress") {
		return new WaitPadPressGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitGamepadWheel") {
		return new WaitGamepadWheelGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitGamepadConnect") {
		return new WaitGamepadConnectGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WaitGamepadDisconnect") {
		return new WaitGamepadDisconnectGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32WriteToFile") {
		return new FileWriteGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Stm32RemoveFile") {
		return new RemoveFileGenerator(mRepo, customizer, id, this);
	}

	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QStringList Stm32GeneratorFactory::pathsToTemplates() const
{
	return mPathsToTemplates; //{":/" + mGeneratorName + "/templates"};
}

generatorBase::parts::DeviceVariables *Stm32GeneratorFactory::deviceVariables() const
{
	return new stm32::parts::Stm32DeviceVariables();
}
