#include "structurizerNode.h"

using namespace generatorBase;

StructurizerNode::StructurizerNode(QObject *parent)
	: QObject(parent)
{
}

SimpleStructurizerNode::SimpleStructurizerNode(const qReal::Id &id, QObject *parent)
	: StructurizerNode(parent)
	, mId(id)
{
}

ContinuationStructurizerNode::ContinuationStructurizerNode(const qReal::Id &id, QObject *parent)
	: StructurizerNode(parent)
	, mId(id)
{
}

StructurizerNode::Type SimpleStructurizerNode::type() const
{
	return Type::simple;
}

StructurizerNode::Type ContinuationStructurizerNode::type() const
{
	return Type::continuation;
}

StructurizerNode::Type IfStructurizerNode::type() const
{
	return Type::ifThenElse;
}

StructurizerNode::Type LoopStructurizerNode::type() const
{
	return Type::loop;
}

bool SimpleStructurizerNode::containsContinuation(const Vertex &id) {
	Q_UNUSED(id)
	return false;
}

bool ContinuationStructurizerNode::containsContinuation(const Vertex &id) {
	if (id == qReal::Id()) {
		return true;
	}
	return id == mId;
}

bool IfStructurizerNode::containsContinuation(const Vertex &id) {
	for (auto e : *mThenBranch) {
		if (e->containsContinuation(id)) {
			return true;
		}
	}
	for (auto e : *mElseBranch) {
		if (e->containsContinuation(id)) {
			return true;
		}
	}
	return false;
}

bool LoopStructurizerNode::containsContinuation(const Vertex &id) {
	for (auto e : *mBody) {
		if (e->containsContinuation(id)) {
			return true;
		}
	}
	return false;
}

bool SimpleStructurizerNode::containsNonContinuation() {
	return true;
}

bool ContinuationStructurizerNode::containsNonContinuation() {
	return false;
}

bool IfStructurizerNode::containsNonContinuation() {
	for (auto e : *mThenBranch) {
		if (e->containsNonContinuation()) {
			return true;
		}
	}
	for (auto e : *mElseBranch) {
		if (e->containsNonContinuation()) {
			return true;
		}
	}
	return false;
}

bool LoopStructurizerNode::containsNonContinuation() {
	for (auto e : *mBody) {
		if (e->containsNonContinuation()) {
			return true;
		}
	}
	return false;
}

IfStructurizerNode::IfStructurizerNode(const Vertex &id, const Vertex &firstId, const Vertex &secondId, QObject *parent)
	: StructurizerNode(parent)
{
	mThenBranch = new QVector<StructurizerNode *>();
	mThenBranch->append(new ContinuationStructurizerNode(firstId, parent));

	mElseBranch = new QVector<StructurizerNode *>();
	mElseBranch->append(new ContinuationStructurizerNode(secondId, parent));

	mCondition = new ConditionTree({id, firstId});
}

IfStructurizerNode::IfStructurizerNode(QObject *parent)
	: StructurizerNode(parent)
	, mCondition(nullptr)
	, mThenBranch(new QVector<StructurizerNode *>())
	, mElseBranch(new QVector<StructurizerNode *>())
{
}

IfStructurizerNode::IfStructurizerNode(ConditionTree * ifCondition, QObject *parent)
	: StructurizerNode(parent)
	, mCondition(ifCondition)
	, mThenBranch(new QVector<StructurizerNode *>())
	, mElseBranch(new QVector<StructurizerNode *>())
{
}

LoopStructurizerNode::LoopStructurizerNode(QObject *parent)
	: StructurizerNode(parent)
	, mCondition(nullptr)
	, mDoWhileForm(true)
{
}

LoopStructurizerNode::LoopStructurizerNode(ConditionTree *c, QObject *parent)
	: StructurizerNode(parent)
	, mCondition(c)
	, mDoWhileForm(true)
{
}


StructurizerNode::~StructurizerNode()
{
	//qDebug() << "destructor element";
}


StructurizerNode *SimpleStructurizerNode::clone() {
	return new SimpleStructurizerNode(this->id(), this->parent());
}

StructurizerNode *ContinuationStructurizerNode::clone() {
	return new ContinuationStructurizerNode(this->id(), this->parent());
}

StructurizerNode *IfStructurizerNode::clone() {
	IfStructurizerNode *newCondition = new IfStructurizerNode(parent());
	newCondition->mCondition = mCondition->clone();
	for (auto e : *mThenBranch) {
		newCondition->mThenBranch->append(e->clone());
	}
	for (auto e : *mElseBranch) {
		newCondition->mElseBranch->append(e->clone());
	}
	return newCondition;
}

StructurizerNode *LoopStructurizerNode::clone() {
	LoopStructurizerNode *x = new LoopStructurizerNode(parent());
	auto xBody = new QVector<StructurizerNode *>();
	for (auto e : *mBody) {
		xBody->append(e);
	}
	x->setBody(xBody);
	x->mDoWhileForm = mDoWhileForm;
	x->mCondition = mCondition == nullptr ? nullptr :mCondition->clone();
	return x;
}

QVector<StructurizerNode *> *LoopStructurizerNode::body() {
	return mBody;
}

StructurizerNode::Vertex SimpleStructurizerNode::id() const
{
	return this->mId;
}

StructurizerNode::Vertex ContinuationStructurizerNode::id() const
{
	return this->mId;
}

StructurizerNode::Vertex LoopStructurizerNode::id() const
{
	if (mCondition == nullptr)
		return qReal::Id();
	return mCondition->isValue() ? mCondition->value().first : qReal::Id();
}

StructurizerNode::Vertex IfStructurizerNode::id() const
{
	return mCondition->isValue() ? mCondition->value().first : qReal::Id();
}

void LoopStructurizerNode::setBody(QVector<StructurizerNode *> *body, int to) {
	mBody = new QVector<StructurizerNode *>();
	for (int i = 0; i < (to == -1 ? body->size() : to); ++i) {
		auto z = (*body)[i]->clone();
		mBody->append(z);
	}
}

QVector<StructurizerNode *> *IfStructurizerNode::thenBranch() {
	return mThenBranch;
}

QVector<StructurizerNode *> *IfStructurizerNode::elseBranch() {
	return mElseBranch;
}


void IfStructurizerNode::dropContinuations(const Vertex &id) {
	for (int i = 0; i < mThenBranch->size(); ++i) {
		if ((*mThenBranch)[i]->type() == continuation) {
			if ((id == qReal::Id()) || (id == (*mThenBranch)[i]->id())) {
				mThenBranch->erase(mThenBranch->begin()+i--);
			}
		} else if ((*mThenBranch)[i]->type() == ifThenElse) {
			dynamic_cast<IfStructurizerNode *>((*mThenBranch)[i])->dropContinuations(id);
		}
	}
	for (int i = 0; i < mElseBranch->size(); ++i) {
		if ((*mElseBranch)[i]->type() == continuation) {
			if ((id == qReal::Id()) || (id == (*mElseBranch)[i]->id())) {
				mElseBranch->erase(mElseBranch->begin()+i--);
			}
		} else if ((*mElseBranch)[i]->type() == ifThenElse) {
			dynamic_cast<IfStructurizerNode *>((*mElseBranch)[i])->dropContinuations(id);
		}
	}
}

void IfStructurizerNode::dropNonContinuations() {
	for (int i = 0; i < mThenBranch->size(); ++i) {
		if ((*mThenBranch)[i]->type() == simple || (*mThenBranch)[i]->type() == loop) {
			mThenBranch->erase(mThenBranch->begin()+i--);
		} else if ((*mThenBranch)[i]->type() == ifThenElse) {
			dynamic_cast<IfStructurizerNode *>((*mThenBranch)[i])->dropNonContinuations();
		}
	}
	for (int i = 0; i < mElseBranch->size(); ++i) {
		if ((*mElseBranch)[i]->type() == simple || (*mElseBranch)[i]->type() == loop) {
			mElseBranch->erase(mElseBranch->begin()+i--);
		} else if ((*mElseBranch)[i]->type() == ifThenElse) {
			dynamic_cast<IfStructurizerNode *>((*mElseBranch)[i])->dropNonContinuations();
		}
	}
}

bool IfStructurizerNode::hasSameCondition(IfStructurizerNode *x) {
	if ((mCondition == nullptr) && (x->mCondition == nullptr))
		return true;
	if ((mCondition == nullptr) xor (x->mCondition == nullptr))
		return false;
	return mCondition->isEqual(x->mCondition);
}

bool LoopStructurizerNode::hasSameCondition(LoopStructurizerNode *x) {
	if ((mCondition == nullptr) && (x->mCondition == nullptr))
		return true;
	if ((mCondition == nullptr) xor (x->mCondition == nullptr))
		return false;
	return mCondition->isEqual(x->mCondition);
}

bool SimpleStructurizerNode::isEqual(StructurizerNode * another) {
	if (another->type() != simple) {
		return false;
	}
	return mId == another->id();
}

bool ContinuationStructurizerNode::isEqual(StructurizerNode * another) {
	if (another->type() != continuation) {
		return false;
	}
	return mId == another->id();
}

bool IfStructurizerNode::isEqual(StructurizerNode * another) {
	if (another->type() != ifThenElse) {
		return false;
	}
	if (!hasSameCondition(dynamic_cast<IfStructurizerNode *>(another))) {
		return false;
	}
	if (mThenBranch->size() != dynamic_cast<IfStructurizerNode *>(another)->thenBranch()->size()
	|| mElseBranch->size() != dynamic_cast<IfStructurizerNode *>(another)->elseBranch()->size()) {
		return false;
	}
	for (int i = 0; i < mThenBranch->size(); ++i) {
		if (!(*mThenBranch)[i]->isEqual((*dynamic_cast<IfStructurizerNode *>(another)->thenBranch())[i])) {
			return false;
		}
	}
	for (int i = 0; i < mElseBranch->size(); ++i) {
		if (!(*mElseBranch)[i]->isEqual((*dynamic_cast<IfStructurizerNode *>(another)->elseBranch())[i])) {
			return false;
		}
	}
	return true;
}

bool LoopStructurizerNode::isEqual(StructurizerNode * another) {
	if (another->type() != loop) {
		return false;
	}
	if (!hasSameCondition(dynamic_cast<LoopStructurizerNode *>(another))) {
		return false;
	}
	if (mBody->size() != dynamic_cast<LoopStructurizerNode *>(another)->body()->size()) {
		return false;
	}
	for (int i = 0; i < mBody->size(); ++i) {
		if (!(*mBody)[i]->isEqual((*dynamic_cast<LoopStructurizerNode *>(another)->body())[i])) {
			return false;
		}
	}
	return true;
}

StructurizerNode::ConditionTree *IfStructurizerNode::findAllContinuations(const Vertex &id) {
	ConditionTree *trueCases = nullptr;
	ConditionTree *falseCases = nullptr;
	bool alwaysTrue = false;
	for (auto i : *mThenBranch) {
		if (i->containsContinuation(id)) {
			ConditionTree *found = nullptr;
			if (i->type() == continuation) {
				alwaysTrue = true;
				trueCases = nullptr;
				break;
			} else if (i->type() == ifThenElse) {
				found = dynamic_cast<IfStructurizerNode *>(i)->findAllContinuations(id);
				if (found == nullptr) {
					alwaysTrue = true;
					trueCases = nullptr;
					break;
				}
			}
			if (trueCases == nullptr) {
				trueCases = found;
			} else {
				trueCases = new ConditionTree(OR, trueCases, found);
			}
		}
	}
	bool alwaysFalse = false;
	for (auto i : *mElseBranch) {
		if (i->containsContinuation(id)) {
			ConditionTree *found = nullptr;
			if (i->type() == continuation) {
				alwaysFalse = true;
				falseCases = nullptr;
				break;
			} else if (i->type() == ifThenElse) {
				found = dynamic_cast<IfStructurizerNode *>(i)->findAllContinuations(id);
				if (found == nullptr) {
					alwaysFalse = true;
					falseCases = nullptr;
					break;
				}
			}
			if (falseCases == nullptr) {
				falseCases = found;
			} else {
				falseCases = new ConditionTree(OR, falseCases, found);
			}
		}
	}
	if (alwaysTrue && alwaysFalse) {
		return nullptr;
	}
	if (trueCases != nullptr && falseCases != nullptr) {
		if (trueCases->isNegativeTo(falseCases))
			return nullptr;
		auto invertedTree = mCondition->clone();
		invertedTree->invert();
		if (falseCases != nullptr)
		return new ConditionTree(OR, new ConditionTree(AND, mCondition->clone(), trueCases), new ConditionTree(AND, invertedTree, falseCases));
	}
	if (alwaysTrue) {
		if (falseCases != nullptr) {
			auto invertedTree = mCondition->clone();
			invertedTree->invert();
			return new ConditionTree(OR, mCondition->clone(), new ConditionTree(AND, invertedTree, falseCases));
		}
		return mCondition->clone();
	}
	if (alwaysFalse) {
		auto invertedTree = mCondition->clone();
		invertedTree->invert();
		if (trueCases != nullptr) {
			return new ConditionTree(OR, new ConditionTree(AND, mCondition->clone(), trueCases), invertedTree);
		}
		return invertedTree;
	}
	if ((trueCases == nullptr) && (falseCases != nullptr)) {
			auto invertedTree = mCondition->clone();
			invertedTree->invert();
			return new ConditionTree(AND, invertedTree, falseCases);
	}
	if ((trueCases != nullptr) && (falseCases == nullptr)) {
		return new ConditionTree(AND, mCondition->clone(), trueCases);
	}
	qDebug() << "INAPROPRITE CONDITIONNODE";
	return nullptr;
}

StructurizerNode::ConditionTree *IfStructurizerNode::condition() {
	return mCondition;
}

StructurizerNode::ConditionTree *LoopStructurizerNode::condition() {
	return mCondition;
}
