/* Copyright 2018 CyberTech Labs Ltd.
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

#include "stopCameraGenerator.h"
#include <qrutils/stringUtils.h>
#include <generatorBase/generatorCustomizer.h>

using namespace trik::simple;
using namespace generatorBase::simple;

namespace  {
	QString convertModeToEnum(const QString &mode) {
		if (mode == "StopNone") {
			return "0";
		}
		if (mode == "StopStream") {
			return "1";
		}
		return "2";
	}
}

StopCameraGenerator::StopCameraGenerator(const qrRepo::RepoApi &repo, generatorBase::GeneratorCustomizer &customizer,
	const qReal::Id &id, QObject *parent)
	: BindingGenerator(repo, customizer, id,
		  "videosensors/stop" + repo.property(id, "Mode").toString() + "Sensor.t", {
			   Binding::createStaticConverting("@@PORT@@",
				utils::StringUtils::wrap(utils::StringUtils::dequote(repo.property(id, "VideoPort").toString())),
				customizer.factory()->stringPropertyConverter(id, "VideoPort"))
			   ,
			   Binding::createStaticConverting("@@STOP_CAMERA_MODE@@",
				 convertModeToEnum(repo.stringProperty(id, "StopCameraMode")),
				 customizer.factory()->stringPropertyConverter(id, "StopCameraMode"))
			   ,
			   }, parent)
{
}
