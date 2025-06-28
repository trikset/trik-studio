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

#include "simpleStructurizerNode.h"

using namespace generatorBase;

SimpleStructurizerNode::SimpleStructurizerNode(const Vertex &id, QObject *parent)
	: StructurizerNode(parent)
	, mId(id)
{
}

StructurizerNode::Type SimpleStructurizerNode::type() const
{
	return Type::simple;
}

bool SimpleStructurizerNode::containsContinuation(const Vertex &id) const
{
	Q_UNUSED(id)
	return false;
}

int SimpleStructurizerNode::numberOfContinuation(const Vertex &id) const
{
	Q_UNUSED(id)
	return 0;
}

StructurizerNode *SimpleStructurizerNode::clone() const
{
	return new SimpleStructurizerNode(mId, parent());
}

StructurizerNode::Vertex SimpleStructurizerNode::id() const
{
	return mId;
}

bool SimpleStructurizerNode::isEqual(StructurizerNode * other) const
{
	if (other->type() != simple) {
		return false;
	}
	return mId == other->id();
}

void SimpleStructurizerNode::dropContinuations(const Vertex &id)
{
	Q_UNUSED(id)
}

void SimpleStructurizerNode::factorize(const Vertex &id, bool force)
{
	Q_UNUSED(id)
	Q_UNUSED(force)
}

void SimpleStructurizerNode::derecursivate(const Vertex &id)
{
	Q_UNUSED(id)
}

bool SimpleStructurizerNode::mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads)
{
	Q_UNUSED(exits)
	Q_UNUSED(loopHeads)
	return false;
}

void SimpleStructurizerNode::transformDoWhile()
{
}

void SimpleStructurizerNode::dropEmptyConditionals()
{
}

StructurizerNode::ConditionTree *SimpleStructurizerNode::findAllContinuations(const Vertex &id) const
{
	Q_UNUSED(id)
	return nullptr;
}

void SimpleStructurizerNode::replaceContinuation(const Vertex &id, StructurizerNode *value)
{
	Q_UNUSED(id)
	Q_UNUSED(value)
}


int SimpleStructurizerNode::numberOfConditionCalculating(const Vertex &id) const
{
	Q_UNUSED(id)
	return 0;
}

bool SimpleStructurizerNode::hasBreakOnUpperLevel() const
{
	return false;
}
