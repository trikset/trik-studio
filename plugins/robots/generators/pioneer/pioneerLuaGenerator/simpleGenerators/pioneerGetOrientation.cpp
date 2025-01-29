/* Copyright 2022 CyberTech Labs Ltd.
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

#include "pioneerGetOrientation.h"

#include <generatorBase/generatorCustomizer.h>

using namespace pioneer::lua;
using namespace generatorBase::simple;

PioneerGetOrientation::PioneerGetOrientation(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const qReal::Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "quadcopterCommands/getOrientation.t"
		, {
			Binding::createConverting(
					"@@ROLL@@"
					, "Roll"
					, customizer.factory()->stringPropertyConverter(id, "Roll"))
			, Binding::createConverting(
					"@@PITCH@@"
					, "Pitch"
					, customizer.factory()->stringPropertyConverter(id, "Pitch"))
			, Binding::createConverting(
					"@@AZIMUTH@@"
					, "Azimuth"
					, customizer.factory()->stringPropertyConverter(id, "Azimuth"))
			}
		, parent)
{
	customizer.factory()->functionBlockConverter(id, "")->convert(
			QString("%1 = 0;%2 = 0;%3 = 0;")
					.arg(repo.stringProperty(id, "Roll"))
					.arg(repo.stringProperty(id, "Pitch"))
					.arg(repo.stringProperty(id, "Azimuth")));
}
