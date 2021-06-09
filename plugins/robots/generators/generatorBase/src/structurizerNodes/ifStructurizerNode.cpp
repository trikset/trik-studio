#include "ifStructurizerNode.h"
#include "simpleStructurizerNode.h"
#include "continuationStructurizerNode.h"
#include "sequenceStructurizerNode.h"

using namespace generatorBase;

StructurizerNode::Type IfStructurizerNode::type() const
{
	return ifThenElse;
}

bool IfStructurizerNode::isEmpty() const
{
	return (static_cast<SequenceStructurizerNode *>(mThenBranch)->children().size() == 0)
		&& (static_cast<SequenceStructurizerNode *>(mElseBranch)->children().size() == 0);
}

bool IfStructurizerNode::containsContinuation(const Vertex &id) const
{
	return mThenBranch->containsContinuation(id) || mElseBranch->containsContinuation(id);
}

int IfStructurizerNode::numberOfContinuation(const Vertex &id) const
{
	return mThenBranch->numberOfContinuation(id) + mElseBranch->numberOfContinuation(id);
}

IfStructurizerNode::IfStructurizerNode(const Vertex &id, const Vertex &firstId
		, const Vertex &secondId, QObject *parent)
	: StructurizerNode(parent)
{
	mThenBranch = new SequenceStructurizerNode(parent);
	static_cast<SequenceStructurizerNode *>(mThenBranch)
			->addToTheEnd(new ContinuationStructurizerNode(firstId, parent));

	mElseBranch = new SequenceStructurizerNode(parent);
	static_cast<SequenceStructurizerNode *>(mElseBranch)
			->addToTheEnd(new ContinuationStructurizerNode(secondId, parent));

	mCondition = new ConditionTree({id, firstId});
}

IfStructurizerNode::IfStructurizerNode(const ConditionTree * ifCondition, QObject *parent)
	: StructurizerNode(parent)
	, mCondition(ifCondition)
	, mThenBranch(new SequenceStructurizerNode(parent))
	, mElseBranch(new SequenceStructurizerNode(parent))
{
}

StructurizerNode *IfStructurizerNode::clone() const
{
	IfStructurizerNode *newIf = new IfStructurizerNode(mCondition->clone(), parent());
	for (auto &e : static_cast<SequenceStructurizerNode *>(mThenBranch)->children()) {
		static_cast<SequenceStructurizerNode *>(newIf->mThenBranch)->addToTheEnd(e->clone());
	}
	for (auto &e : static_cast<SequenceStructurizerNode *>(mElseBranch)->children()) {
		static_cast<SequenceStructurizerNode *>(newIf->mElseBranch)->addToTheEnd(e->clone());
	}
	return newIf;
}

StructurizerNode::Vertex IfStructurizerNode::id() const
{
	return mCondition->isValue() ? mCondition->value().first : Vertex();
}


StructurizerNode *IfStructurizerNode::thenBranch()
{
	return mThenBranch;
}

StructurizerNode *IfStructurizerNode::elseBranch()
{
	return mElseBranch;
}

void IfStructurizerNode::dropContinuations(const Vertex &id)
{
	mThenBranch->dropContinuations(id);
	mElseBranch->dropContinuations(id);
}

bool IfStructurizerNode::isEqual(StructurizerNode *other) const
{
	if (other->type() != ifThenElse) {
		return false;
	}
	if (!mCondition->isEqual(static_cast<IfStructurizerNode *>(other)->mCondition)) {
		return false;
	}
	if (!mThenBranch->isEqual(static_cast<IfStructurizerNode *>(other)->mThenBranch)) {
		return false;
	}
	if (!mElseBranch->isEqual(static_cast<IfStructurizerNode *>(other)->mElseBranch)) {
		return false;
	}
	return true;
}

StructurizerNode::ConditionTree *IfStructurizerNode::findAllContinuations(const Vertex &id) const
{
	ConditionTree *tree = nullptr;
	if (mThenBranch->containsContinuation(id)) {
		ConditionTree *thenTree = mThenBranch->findAllContinuations(id);
		if (thenTree == nullptr) {
			tree = mCondition->clone();
		} else {
			tree = new ConditionTree(ConditionTree::AND, mCondition->clone(), thenTree);
		}
	}

	if (mElseBranch->containsContinuation(id)) {
		ConditionTree *invertedCondition = mCondition->clone();
		invertedCondition->invert();
		ConditionTree *elseTree = mElseBranch->findAllContinuations(id);
		if (elseTree == nullptr) {
			elseTree = invertedCondition;
		} else {
			elseTree = new ConditionTree(ConditionTree::AND, invertedCondition, elseTree);
		}
		if (tree == nullptr) {
			tree = elseTree;
		} else {
			tree = new ConditionTree(ConditionTree::OR, tree, elseTree);
		}
	}

	if (tree == nullptr || tree->isTrue()) {
		delete tree;
		return nullptr;
	}
	return tree;
}

void IfStructurizerNode::factorize(const Vertex &id, bool force)
{
	mThenBranch->factorize(id, force);
	mElseBranch->factorize(id, force);
}

void IfStructurizerNode::derecursivate(const Vertex &id)
{
	Q_UNUSED(id)
}

bool IfStructurizerNode::mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads)
{
	if (mThenBranch->mergeConditionalBranches(exits, loopHeads))
		return true;
	if (mElseBranch->mergeConditionalBranches(exits, loopHeads))
		return true;
	return false;
}

void IfStructurizerNode::transformDoWhile()
{
	mThenBranch->transformDoWhile();
	mElseBranch->transformDoWhile();
}

void IfStructurizerNode::dropEmptyConditionals()
{
	mThenBranch->dropEmptyConditionals();
	mElseBranch->dropEmptyConditionals();
}

StructurizerNode::ConditionTree *IfStructurizerNode::condition() const
{
	return mCondition->clone();
}

IfStructurizerNode::~IfStructurizerNode()
{
	delete mCondition;
}

void IfStructurizerNode::replaceContinuation(const Vertex &id, StructurizerNode *value)
{
	mThenBranch->replaceContinuation(id, value);
	mElseBranch->replaceContinuation(id, value);
}

int IfStructurizerNode::numberOfConditionCalculating(const Vertex &id) const
{
	int count = mCondition->numberOfFirstVertex(id);
	count += mThenBranch->numberOfConditionCalculating(id);
	count += mElseBranch->numberOfConditionCalculating(id);
	return count;
}

bool IfStructurizerNode::hasBreakOnUpperLevel() const
{
	return mThenBranch->hasBreakOnUpperLevel() || mElseBranch->hasBreakOnUpperLevel();
}
