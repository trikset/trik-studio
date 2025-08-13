/* Copyright 2013-2021 CyberTech Labs Ltd.
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

#include "syntheticVariableNameGenerator.h"

#include "generatorBase/generatorCustomizer.h"

using namespace generatorBase;
using namespace qReal;

simple::SyntheticVariableNameGenerator::SyntheticVariableNameGenerator(const qrRepo::RepoApi &repo
		, GeneratorCustomizer &customizer
		, const Id &id
		, ReadableLabelManager &nameManager
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "function.t"
			, { Binding::createStaticConverting("@@BODY@@"
					, nameManager.labelFor(id, "__temp_") + "=" +
						repo.property(id, repo.hasProperty(id, "Condition") ? "Condition" : "Expression").toString()
					, customizer.factory()->functionBlockConverter(id, "Condition")) }
			, parent)
{
}
