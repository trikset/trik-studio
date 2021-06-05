#include "switchStructurizerNode.h"
#include "simpleStructurizerNode.h"
#include "continuationStructurizerNode.h"
#include "sequenceStructurizerNode.h"

using namespace generatorBase;

StructurizerNode::Type SwitchStructurizerNode::type() const
{
	return Type::switchCase;
}

bool SwitchStructurizerNode::isEmpty() const
{
	for (auto *t : mBranches) {
		if (static_cast<SequenceStructurizerNode *>(t)->children().size() > 0) {
			return false;
		}
	}
	if (static_cast<SequenceStructurizerNode *>(mDefaultBranch.second)->children().size() > 0) {
		return false;
	}
	return true;
}

bool SwitchStructurizerNode::containsContinuation(const Vertex &id) const
{
	for (auto *t : mBranches) {
		if (t->containsContinuation(id)) {
			return true;
		}
	}
	if (mDefaultBranch.second->containsContinuation(id)) {
		return true;
	}
	return false;
}

int SwitchStructurizerNode::numberOfContinuation(const Vertex &id) const
{
	int count = 0;
	for (auto *t : mBranches) {
		count += t->numberOfContinuation(id);
	}
	count += mDefaultBranch.second->numberOfContinuation(id);
	return count;
}

SwitchStructurizerNode::SwitchStructurizerNode(const Vertex &id, const QVector<Vertex> &branches, QObject *parent)
	: StructurizerNode(parent)
	, mId(id)
{
	auto defaultBranch = new SequenceStructurizerNode(parent);
	defaultBranch->addToTheEnd(new ContinuationStructurizerNode(branches.last(), parent));
	mDefaultBranch = qMakePair(branches.last(), defaultBranch);
	for (int i = 0; i < branches.size() - 1; ++i) {
		auto branch = new SequenceStructurizerNode(parent);
		branch->addToTheEnd(new ContinuationStructurizerNode(branches[i], parent));
		mBranches[branches[i]] = branch;
	}
}

StructurizerNode *SwitchStructurizerNode::clone() const
{
	QVector<Vertex> branches;
	for (const Vertex &e : mBranches.keys()) {
		branches.append(e);
	}
	branches.append(mDefaultBranch.first);
	SwitchStructurizerNode *newSwitch = new SwitchStructurizerNode(mId, branches, parent());

	for (const Vertex &e : mBranches.keys()) {
		newSwitch->mBranches[e] = mBranches[e]->clone();
	}
	newSwitch->mDefaultBranch.second = mDefaultBranch.second->clone();
	return newSwitch;
}

StructurizerNode::Vertex SwitchStructurizerNode::id() const
{
	return mId;
}


QMap<StructurizerNode::Vertex, StructurizerNode *> SwitchStructurizerNode::branches() const
{
	return mBranches;
}

void SwitchStructurizerNode::dropContinuations(const Vertex &id)
{
	for (auto *&t : mBranches) {
		t->dropContinuations(id);
	}
	mDefaultBranch.second->dropContinuations(id);
}

bool SwitchStructurizerNode::isEqual(StructurizerNode *other) const
{
	if (other->type() != switchCase) {
		return false;
	}
	if (mId != other->id()) {
		return false;
	}
	for (const Vertex &e : mBranches.keys()) {
		if (!static_cast<SwitchStructurizerNode *>(other)->mBranches.keys().contains(e)
			|| !static_cast<SwitchStructurizerNode *>(other)->mBranches[e]->isEqual(mBranches[e]))
		{
			return false;
		}
	}
	if (static_cast<SwitchStructurizerNode *>(other)->mDefaultBranch.first != mDefaultBranch.first
		|| !static_cast<SwitchStructurizerNode *>(other)->mBranches[mDefaultBranch.first]->isEqual(mBranches[mDefaultBranch.first]))
	{
		return false;
	}
	return true;
}

StructurizerNode::ConditionTree *SwitchStructurizerNode::findAllContinuations(const Vertex &id) const
{
	ConditionTree *tree = nullptr;
	for (const Vertex &e : mBranches.keys()) {
		if (mBranches[e]->containsContinuation(id)) {
			ConditionTree *branchCondition = new ConditionTree(qMakePair(mId, e));
			ConditionTree *newCase = mBranches[e]->findAllContinuations(id);
			if (newCase == nullptr) {
				newCase = branchCondition;
			} else {
				newCase = new ConditionTree(ConditionTree::AND, branchCondition, newCase);
			}
			if (tree == nullptr) {
				tree = newCase;
			} else {
				tree = new ConditionTree(ConditionTree::OR, tree, newCase);
			}
		}
	}
	if (mDefaultBranch.second->containsContinuation(id)) {
		ConditionTree *branchCondition = nullptr;
		for (const Vertex &e : mBranches.keys()) {
			if (branchCondition == nullptr) {
				branchCondition = new ConditionTree(qMakePair(mId, e));
			} else {
				branchCondition = new ConditionTree(ConditionTree::OR, branchCondition, new ConditionTree(qMakePair(mId, e)));
			}
		}
		if (branchCondition != nullptr) {
			branchCondition->invert();

			ConditionTree *newCase = mDefaultBranch.second->findAllContinuations(id);
			if (newCase == nullptr) {
				newCase = branchCondition;
			} else {
				newCase = new ConditionTree(ConditionTree::AND, branchCondition, newCase);
			}
			if (tree == nullptr) {
				tree = newCase;
			} else {
				tree = new ConditionTree(ConditionTree::OR, tree, newCase);
			}
		}
	}
	if (tree == nullptr || tree->isTrue()) {
		delete tree;
		return nullptr;
	}
	return tree;
}

void SwitchStructurizerNode::factorize(const Vertex &id, bool force)
{
	Q_UNUSED(id)
	Q_UNUSED(force)
}

void SwitchStructurizerNode::derecursivate(const Vertex &id)
{
	Q_UNUSED(id)
}

bool SwitchStructurizerNode::mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads)
{
	for (auto *&t : mBranches) {
		if (t->mergeConditionalBranches(exits, loopHeads)) {
			return true;
		}
	}
	if (mDefaultBranch.second->mergeConditionalBranches(exits, loopHeads)) {
		return true;
	}
	return false;
}

void SwitchStructurizerNode::transformDoWhile()
{
}

void SwitchStructurizerNode::dropEmptyConditionals()
{
	for (auto *&t : mBranches) {
		t->dropEmptyConditionals();
	}
	mDefaultBranch.second->dropEmptyConditionals();
}

void SwitchStructurizerNode::replaceContinuation(const Vertex &id, StructurizerNode *value)
{
	for (auto *&t : mBranches) {
		t->replaceContinuation(id, value);
	}
	mDefaultBranch.second->replaceContinuation(id, value);
}

int SwitchStructurizerNode::numberOfConditionCalculating(const Vertex &id) const
{
	int count = mId == id ? 1 : 0;
	for (auto *t : mBranches) {
		count += t->numberOfConditionCalculating(id);
	}
	count += mDefaultBranch.second->numberOfConditionCalculating(id);
	return count;
}

void SwitchStructurizerNode::transformBeforeDerecursivation()
{
}
