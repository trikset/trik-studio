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

#include "continuationStructurizerNode.h"

using namespace generatorBase;

ContinuationStructurizerNode::ContinuationStructurizerNode(const Vertex &id, QObject *parent)
	: StructurizerNode(parent)
	, mId(id)
{
}

StructurizerNode::Type ContinuationStructurizerNode::type() const
{
	return Type::continuation;
}

bool ContinuationStructurizerNode::containsContinuation(const Vertex &id) const
{
	if (id == Vertex()) {
		return true;
	}
	return id == mId;
}

int ContinuationStructurizerNode::numberOfContinuation(const Vertex &id) const
{
	if (id == Vertex()) {
		return 1;
	}
	return id == mId ? 1 : 0;
}

StructurizerNode *ContinuationStructurizerNode::clone() const
{
	return new ContinuationStructurizerNode(mId, parent());
}

StructurizerNode::Vertex ContinuationStructurizerNode::id() const
{
	return mId;
}

bool ContinuationStructurizerNode::isEqual(StructurizerNode * other) const
{
	if (other->type() != continuation) {
		return false;
	}
	return mId == other->id();
}

void ContinuationStructurizerNode::dropContinuations(const Vertex &id)
{
	Q_UNUSED(id)
}

void ContinuationStructurizerNode::factorize(const Vertex &id, bool force)
{
	Q_UNUSED(id)
	Q_UNUSED(force)
}

void ContinuationStructurizerNode::derecursivate(const Vertex &id)
{
	Q_UNUSED(id)
}

bool ContinuationStructurizerNode::mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads)
{
	Q_UNUSED(exits)
	Q_UNUSED(loopHeads)
	return false;
}

void ContinuationStructurizerNode::transformDoWhile()
{
}

void ContinuationStructurizerNode::dropEmptyConditionals()
{
}

StructurizerNode::ConditionTree *ContinuationStructurizerNode::findAllContinuations(const Vertex &id) const
{
	Q_UNUSED(id)
	return nullptr;
}

void ContinuationStructurizerNode::replaceContinuation(const Vertex &id, StructurizerNode *value)
{
	Q_UNUSED(id)
	Q_UNUSED(value)
}


int ContinuationStructurizerNode::numberOfConditionCalculating(const Vertex &id) const
{
	Q_UNUSED(id)
	return 0;
}

bool ContinuationStructurizerNode::hasBreakOnUpperLevel() const
{
	return false;
}
