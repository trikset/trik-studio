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

#include "loopStructurizerNode.h"

#include "sequenceStructurizerNode.h"

using namespace generatorBase;

StructurizerNode::Type LoopStructurizerNode::type() const
{
	return Type::loop;
}

bool LoopStructurizerNode::containsContinuation(const Vertex &id) const
{
	return mBody->containsContinuation(id);
}

int LoopStructurizerNode::numberOfContinuation(const Vertex &id) const
{
	return mBody->numberOfContinuation(id);
}

LoopStructurizerNode::LoopStructurizerNode(QObject *parent)
	: StructurizerNode(parent)
	, mId(Vertex())
	, mInvertedCondition(false)
	, mBody(new SequenceStructurizerNode(parent))
{
}

LoopStructurizerNode::LoopStructurizerNode(const Vertex &id, bool invertCondition, QObject *parent)
	: StructurizerNode(parent)
	, mId(id)
	, mInvertedCondition(invertCondition)
	, mBody(new SequenceStructurizerNode(parent))
{
}

StructurizerNode *LoopStructurizerNode::clone() const
{
	LoopStructurizerNode *loop = nullptr;
	if (!mId.isNull()) {
		loop = new LoopStructurizerNode(mId, mInvertedCondition, parent());
	} else {
		loop = new LoopStructurizerNode(parent());
	}
	for (StructurizerNode *&e : static_cast<SequenceStructurizerNode *>(mBody)->children()) {
		loop->addToBody(e->clone());
	}
	return loop;
}

StructurizerNode::Vertex LoopStructurizerNode::id() const
{
	return mId;
}

bool LoopStructurizerNode::isEqual(StructurizerNode *other) const
{
	if (other->type() != loop) {
		return false;
	}
	if (mId != other->id()) {
		return false;
	}
	if (mInvertedCondition != static_cast<LoopStructurizerNode *>(other)->mInvertedCondition) {
		return false;
	}
	if (!mBody->isEqual(static_cast<LoopStructurizerNode *>(other)->mBody)) {
		return false;
	}
	return true;
}

void  LoopStructurizerNode::dropContinuations(const Vertex &id)
{
	mBody->dropContinuations(id);
}

void  LoopStructurizerNode::factorize(const Vertex &id, bool force)
{
	Q_UNUSED(id)
	Q_UNUSED(force)
}

void  LoopStructurizerNode::derecursivate(const Vertex &id)
{
	Q_UNUSED(id)
}

bool  LoopStructurizerNode::mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads)
{
	return mBody->mergeConditionalBranches(exits, loopHeads);
}

void  LoopStructurizerNode::transformDoWhile()
{
	mBody->transformDoWhile();
}

void  LoopStructurizerNode::dropEmptyConditionals()
{
	mBody->dropEmptyConditionals();
}

StructurizerNode::ConditionTree *LoopStructurizerNode::findAllContinuations(const Vertex &id) const
{
	Q_UNUSED(id);
	return nullptr;
}

StructurizerNode *LoopStructurizerNode::body()
{
	return mBody;
}

void  LoopStructurizerNode::addToBody(StructurizerNode *e)
{
	static_cast<SequenceStructurizerNode *>(mBody)->addToTheEnd(e);
}

void LoopStructurizerNode::replaceContinuation(const Vertex &id, StructurizerNode *value)
{
	mBody->replaceContinuation(id, value);
}

int LoopStructurizerNode::numberOfConditionCalculating(const Vertex &id) const
{
	return (mId == id ? 1 : 0) + mBody->numberOfConditionCalculating(id);
}

bool LoopStructurizerNode::isInverted() const
{
	return mInvertedCondition;
}

bool LoopStructurizerNode::hasBreakOnUpperLevel() const
{
	return false;
}
