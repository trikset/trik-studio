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

#include "syntheticIfGenerator.h"

#include "generatorBase/generatorCustomizer.h"

using namespace generatorBase::simple;

SyntheticIfGenerator::SyntheticIfGenerator(const qrRepo::RepoApi &repo
		, GeneratorCustomizer &customizer
		, const QMap<qReal::Id, bool> &useVariable
		, bool elseIsEmpty
		, const QString syntheticCondition
		, const qReal::Id &id
		, bool needInverting
		, ReadableLabelManager &nameManager
		, QObject *parent)
	: AbstractSimpleGenerator(repo, customizer, id, parent)
	, mUseVariable(useVariable)
	, mSyntheticCondition(syntheticCondition)
	, mElseIsEmpty(elseIsEmpty)
	, mNeedInverting(needInverting)
	, mNameManager(nameManager)
{
}

QString SyntheticIfGenerator::generate()
{
	QString result = mSyntheticCondition;
	for (const qReal::Id &id : mUseVariable.keys()) {
		if (mUseVariable[id]) {
			result.replace(id.id(), mNameManager.labelFor(id, "__temp_"));
		} else {
			result.replace(id.id(), mRepo.property(id, "Condition").toString());
		}
	}
	QString finalResult =  customizer().factory()->boolPropertyConverter(mUseVariable.firstKey()
		, "Condition", mNeedInverting)->convert(result);
	return readTemplate(mElseIsEmpty ? "conditional/if.t" : "conditional/ifElse.t")
		.replace("@@CONDITION@@", finalResult);
}
