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

#include "sequenceStructurizerNode.h"

#include "continuationStructurizerNode.h"
#include "ifStructurizerNode.h"
#include "loopStructurizerNode.h"
#include "switchStructurizerNode.h"
#include "breakStructurizerNode.h"

using namespace generatorBase;

SequenceStructurizerNode::SequenceStructurizerNode(QObject *parent)
	: StructurizerNode(parent)
	, mChildren({})
{
}

StructurizerNode::Type SequenceStructurizerNode::type() const
{
	return sequence;
}

StructurizerNode::Vertex SequenceStructurizerNode::id() const
{
	return Vertex();
}

bool SequenceStructurizerNode::containsContinuation(const Vertex &id) const
{
	for (auto e : mChildren) {
		if (e->containsContinuation(id)) {
			return true;
		}
	}
	return false;
}

void SequenceStructurizerNode::dropContinuations(const Vertex &id)
{
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->type() == StructurizerNode::continuation) {
			if (mChildren[i]->id() == id) {
				mChildren.erase(mChildren.begin() + i--);
			}
		} else {
			mChildren[i]->dropContinuations(id);
		}
	}
}

int SequenceStructurizerNode::numberOfContinuation(const Vertex &id) const
{
	int count = 0;
	for (auto e : mChildren) {
		count = count + e->numberOfContinuation(id);
	}
	return count;
}



void SequenceStructurizerNode::addToTheEnd(StructurizerNode *s) {
	if (s->type() == sequence) {
		for (StructurizerNode *e : static_cast<SequenceStructurizerNode *>(s)->mChildren) {
			mChildren.append(e);
		}
	} else {
		mChildren.append(s);
	}
}



StructurizerNode *SequenceStructurizerNode::clone() const
{
	SequenceStructurizerNode *x = new SequenceStructurizerNode(parent());
	for (auto e : mChildren) {
		x->addToTheEnd(e);
	}
	return x;
}

QVector<StructurizerNode *> SequenceStructurizerNode::children()
{
	return mChildren;
}


bool SequenceStructurizerNode::isEqual(StructurizerNode *other) const
{
	if (other->type() != sequence) {
		return false;
	}
	for (int i = 0; i < mChildren.size(); ++i) {
		if (!mChildren[i]->isEqual(static_cast<SequenceStructurizerNode *>(other)->mChildren[i])) {
			return false;
		}
	}
	return true;
}

StructurizerNode::ConditionTree *SequenceStructurizerNode::findAllContinuations(const Vertex &id) const
{
	ConditionTree *finalTree = nullptr;
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->containsContinuation(id)) {
			ConditionTree *tree = mChildren[i]->findAllContinuations(id);
			if (tree == nullptr) {
				delete finalTree;
				return nullptr;
			}
			if (finalTree == nullptr) {
				finalTree = tree;
			} else {
				finalTree = new ConditionTree(ConditionTree::OR, finalTree, tree);
				if (finalTree->isTrue()) {
					delete finalTree;
					return nullptr;
				}
			}
		}
	}
	return finalTree;
}

void SequenceStructurizerNode::factorize(const Vertex &id, bool force)
{
	if (numberOfContinuation(id) == 0
		|| (!force && (numberOfContinuation(id) == 1))) {
		return;
	}
	ConditionTree *ifCondition = nullptr;
	bool always = false;
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->containsContinuation(id)) {
			if (mChildren[i]->type() == loop) {
				auto loopBody = static_cast<LoopStructurizerNode *>(mChildren[i])->body();
				static_cast<SequenceStructurizerNode *>(loopBody)->addBreaksToLoopFor(id);
				ConditionTree *newIf = loopBody->findAllContinuations(id);
				loopBody->replaceContinuation(id, new BreakStructurizerNode(parent()));
				mChildren.insert(i + 1, new IfStructurizerNode(newIf, parent()));
			} else {
				mChildren[i]->factorize(id, true);
				if (always) {
					continue;
				}
				ConditionTree *newCase = mChildren[i]->findAllContinuations(id);
				if (newCase == nullptr) {
					always = true;
					delete ifCondition;
					ifCondition = nullptr;
				} else {
					if (ifCondition == nullptr) {
						ifCondition = newCase;
					} else {
						ifCondition = new ConditionTree(ConditionTree::OR, newCase, ifCondition);
					}
				}
			}
		}
	}

	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->containsContinuation(id)) {
			if (mChildren[i]->type() == continuation) {
				mChildren.erase(mChildren.begin() + i--);
			} else {
				mChildren[i]->dropContinuations(id);
			}
		}
	}

	if (ifCondition == nullptr || ifCondition->isTrue()) {
		delete ifCondition;
		mChildren.append(new ContinuationStructurizerNode(id, parent()));
	} else {
		StructurizerNode *newIf = new IfStructurizerNode(ifCondition, parent());
		StructurizerNode *thenBranch = static_cast<IfStructurizerNode *>(newIf)->thenBranch();
		static_cast<SequenceStructurizerNode *>(thenBranch)
				->addToTheEnd(new ContinuationStructurizerNode(id, parent()));
		mChildren.append(newIf);
	}
	dropEmptyConditionals();
}

void SequenceStructurizerNode::derecursivate(const Vertex &id)
{
	if (mChildren.size() == 1 && mChildren[0]->type() == ifThenElse) {
		auto onlyIf = static_cast<IfStructurizerNode *>(mChildren[0]);
		auto thenBranch = static_cast<SequenceStructurizerNode *>(onlyIf->thenBranch());
		auto elseBranch = static_cast<SequenceStructurizerNode *>(onlyIf->elseBranch());
		if (thenBranch->containsContinuation(id)
			&& thenBranch->numberOfContinuation(id) == thenBranch->numberOfContinuation()
			&& !elseBranch->containsContinuation(id))
		{
			thenBranch->dropContinuations(id);
			auto ifCondition = onlyIf->condition();
			auto loop = new LoopStructurizerNode(ifCondition->value().first
				, ifCondition->isInverted(), parent());

			for (auto &e : thenBranch->mChildren) {
				loop->addToBody(e);
			}
			for (auto &e : elseBranch->mChildren) {
				mChildren.append(e);
			}
			mChildren.pop_front();
			mChildren.prepend(loop);
			return;
		}

		if (elseBranch->containsContinuation(id)
			&& elseBranch->numberOfContinuation(id) == elseBranch->numberOfContinuation()
			&& !thenBranch->containsContinuation(id))
		{
			elseBranch->dropContinuations(id);
			auto invertedCondition = onlyIf->condition();
			invertedCondition->invert();

			auto loop = new LoopStructurizerNode(invertedCondition->value().first
				, invertedCondition->isInverted(), parent());

			for (auto &e : elseBranch->mChildren) {
				loop->addToBody(e);
			}
			for (auto &e : thenBranch->mChildren) {
				mChildren.append(e);
			}
			mChildren.pop_front();
			mChildren.prepend(loop);
			return;
		}
	}

	dropContinuations(id);
	LoopStructurizerNode *loop = new LoopStructurizerNode(parent());
	for (int i = 0; i <= mChildren.size() - 1; ++i) {
		loop->addToBody(mChildren[i]);
	}
	mChildren.clear();
	mChildren.append(loop);
}

bool SequenceStructurizerNode::mergeConditionalBranches(const QSet<Vertex> &exits
		, const QSet<Vertex> &loopHeads)
{
	bool result = false;
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->mergeConditionalBranches(exits, loopHeads)) {
			result = true;
		}
		if (mChildren[i]->type() == ifThenElse) {
			SequenceStructurizerNode *first = static_cast<SequenceStructurizerNode *>(
					static_cast<IfStructurizerNode *>(mChildren[i])->thenBranch());
			SequenceStructurizerNode *second = static_cast<SequenceStructurizerNode *>(
					static_cast<IfStructurizerNode *>(mChildren[i])->elseBranch());
			if (first->mChildren.size() == 0 || second->mChildren.size() == 0) {
				continue;
			}
			if (!loopHeads.contains(mChildren[i]->id())) {
				if ((first->mChildren.last()->type() == continuation)
					&& (second->mChildren.last()->type() == simple)
					&& exits.contains(second->mChildren.last()->id()))
				{
					second->addToTheEnd(first->mChildren.last()->clone());
				} else if ((second->mChildren.last()->type() == continuation)
					&& (first->mChildren.last()->type() == simple)
					&& exits.contains(first->mChildren.last()->id()))
				{
					first->addToTheEnd(second->mChildren.last()->clone());
				}
			}
			if (first->mChildren.last()->type() == continuation
				&& second->mChildren.last()->type() == continuation
				&& first->mChildren.last()->id() == second->mChildren.last()->id())
			{
				result = true;
				mChildren.insert(i + 1, first->mChildren.last()->clone());
				first->mChildren.pop_back();
				second->mChildren.pop_back();
			}
		} else if (mChildren[i]->type() == switchCase) {
			auto thisSwitch = static_cast<SwitchStructurizerNode *>(mChildren[i]);
			QSet<Vertex> endContinuations;
			int nonExitCount = 0;
			for (auto &e : thisSwitch->branches()) {
				if (static_cast<SequenceStructurizerNode *>(e)->mChildren.size() > 0
					&& static_cast<SequenceStructurizerNode *>(e)
							->mChildren.last()->type() == continuation)
				{
					endContinuations.insert(static_cast<SequenceStructurizerNode *>(e)
							->mChildren.last()->id());
				}
				if (static_cast<SequenceStructurizerNode *>(e)->mChildren.size() > 0
					&& static_cast<SequenceStructurizerNode *>(e)->mChildren.last()->type() == simple
					&& !exits.contains(static_cast<SequenceStructurizerNode *>(e)->mChildren.last()->id())) {
					nonExitCount += 1;
				}
				if (static_cast<SequenceStructurizerNode *>(e)->mChildren.size() == 0) {
					nonExitCount += 1;
				}
			}
			if ((endContinuations.size() == 1) && (nonExitCount == 0)) {
				result = true;
				mChildren.insert(i + 1, new ContinuationStructurizerNode(*endContinuations.begin(), parent()));
				thisSwitch->dropContinuations(*endContinuations.begin());
			}
		}
	}
	return result;
}

void SequenceStructurizerNode::transformDoWhile()
{
}

void SequenceStructurizerNode::dropEmptyConditionals()
{
	for (int j = 0; j < mChildren.size(); ++j) {
		if (mChildren[j]->type() == ifThenElse && static_cast<IfStructurizerNode *>(mChildren[j])->isEmpty()) {
			mChildren.erase(mChildren.begin() + j--);
		} else if (mChildren[j]->type() == switchCase
				&& static_cast<SwitchStructurizerNode *>(mChildren[j])->isEmpty())
		{
			mChildren.erase(mChildren.begin() + j--);
		} else {
			mChildren[j]->dropEmptyConditionals();
		}
	}
}

void SequenceStructurizerNode::replaceContinuation(const Vertex &id, StructurizerNode *value)
{
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->type() == continuation && mChildren[i]->id() == id) {
			mChildren.erase(mChildren.begin() + i--);
			if (value->type() == sequence) {
				for (StructurizerNode *&e : static_cast<SequenceStructurizerNode *>(value)->mChildren) {
					mChildren.insert(mChildren.begin() + ++i, e->clone());
				}
			} else {
				mChildren.insert(mChildren.begin() + ++i, value->clone());
			}
		} else {
			mChildren[i]->replaceContinuation(id, value);
		}
	}
}

int SequenceStructurizerNode::numberOfConditionCalculating(const Vertex &id) const
{
	int count = 0;
	for (StructurizerNode *e : mChildren) {
		count += e->numberOfConditionCalculating(id);
	}
	return count;
}

void SequenceStructurizerNode::addBreaksToLoopFor(const Vertex &id)
{
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i]->type() == ifThenElse) {
			auto thisIf = static_cast<IfStructurizerNode *>(mChildren[i]);
			static_cast<SequenceStructurizerNode *>(thisIf->thenBranch())->addBreaksToLoopFor(id);
			static_cast<SequenceStructurizerNode *>(thisIf->elseBranch())->addBreaksToLoopFor(id);
		} else if (mChildren[i]->type() == loop) {
			auto thisLoop = static_cast<LoopStructurizerNode *>(mChildren[i]);
			static_cast<SequenceStructurizerNode *>(thisLoop->body())->addBreaksToLoopFor(id);
			ConditionTree *breakCondition = static_cast<SequenceStructurizerNode *>(
					thisLoop->body())->findAllContinuations(id);
			thisLoop->replaceContinuation(id, new BreakStructurizerNode(parent()));
			auto breakIf = new IfStructurizerNode(breakCondition, parent());
			mChildren.insert(++i, breakIf);
			static_cast<SequenceStructurizerNode *>(breakIf->thenBranch())
					->addToTheEnd(new ContinuationStructurizerNode(id, parent()));
		}
	}
}

bool SequenceStructurizerNode::hasBreakOnUpperLevel() const
{
	for (const auto &e : mChildren) {
		if (e->hasBreakOnUpperLevel()) {
			return true;
		}
	}
	return false;
}
