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

#include "sayGenerator.h"

#include <generatorBase/generatorCustomizer.h>
#include <qrutils/stringUtils.h>

using namespace trik::simple;
using namespace generatorBase::simple;

SayGenerator::SayGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const qReal::Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "say.t"
			, { repo.property(id, "Evaluate").toBool()
					? Binding::createConverting("@@TEXT@@", "Text"
								, customizer.factory()->stringPropertyConverter(id, "Text"))
					: Binding::createStatic("@@TEXT@@", utils::StringUtils::wrap(repo.property(id, "Text").toString()))
			} , parent)
{
}
