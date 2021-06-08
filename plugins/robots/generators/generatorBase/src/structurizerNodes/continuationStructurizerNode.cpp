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
