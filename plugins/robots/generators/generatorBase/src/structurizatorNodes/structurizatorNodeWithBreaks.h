/* Copyright 2018 Konstantin Batoev
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

#pragma once

#include "intermediateStructurizatorNode.h"

namespace generatorBase {

class StructurizatorNodeWithBreaks : public IntermediateStructurizatorNode
{
	Q_OBJECT

public:
	explicit StructurizatorNodeWithBreaks(IntermediateStructurizatorNode *condition
			, const QList<IntermediateStructurizatorNode *> &exitBranches
			, QObject *parent);

	IntermediateStructurizatorNode *condition() const;
	QList<IntermediateStructurizatorNode *> exitBranches() const;
	QList<IntermediateStructurizatorNode *> restBranches() const;

	void setRestBranches(const QList<IntermediateStructurizatorNode *> &restBranches);
	bool analyzeBreak();
	Type type() const;
	qReal::Id firstId() const;
private:
	IntermediateStructurizatorNode *mCondition;
	QList<IntermediateStructurizatorNode *> mExitBranches;
	QList<IntermediateStructurizatorNode *> mRestBranches;
};

}
