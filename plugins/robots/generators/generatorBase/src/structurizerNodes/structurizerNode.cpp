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

#include "structurizerNode.h"

using namespace generatorBase;

StructurizerNode::StructurizerNode(QObject *parent)
	: QObject(parent)
{
}

StructurizerNode::~StructurizerNode()
{
}

StructurizerNode::ConditionTree::ConditionTree(const QPair<Vertex, Vertex> &idPair)
	: mInverted(false), mIsOperator(false),mIsValue(true), mValue(idPair), mLeft(nullptr), mRight(nullptr)
{
}

StructurizerNode::ConditionTree::ConditionTree(Operator o, ConditionTree *left, ConditionTree *right)
	: mInverted(false), mIsOperator(true), mIsValue(false), mOperator(o), mLeft(left), mRight(right)
{
}

void StructurizerNode::ConditionTree::invert()
{
	mInverted = true;
}

bool StructurizerNode::ConditionTree::isValue() const
{
	return mIsValue;
}

bool StructurizerNode::ConditionTree::isBoolOperator() const
{
	return mIsOperator;
}

bool StructurizerNode::ConditionTree::isInverted() const
{
	return mInverted;
}

bool StructurizerNode::ConditionTree::isEqual(const ConditionTree *x) const
{
	if (x == nullptr) {
		return false;
	}
	if ((mInverted != x->mInverted) || (mIsOperator != x->mIsOperator) || (mIsValue != x->mIsValue)) {
		return false;
	}
	if ((mIsOperator && !(mOperator == x->mOperator)) || (mIsValue && !(mValue == x->mValue))) {
		return false;
	}
	if ((mLeft != nullptr) xor (x->mLeft != nullptr))
		return false;
	if ((mLeft != nullptr) && !mLeft->isEqual(x->mLeft))
		return false;
	if ((mRight != nullptr) xor (x->mRight != nullptr))
		return false;
	if ((mRight != nullptr) && !mRight->isEqual(x->mRight))
		return false;
	return true;
}

bool StructurizerNode::ConditionTree::isNegativeTo(const ConditionTree *x) const
{
	if (x == nullptr) {
		return false;
	}
	if (mInverted == x->mInverted) {
		return false;
	}
	if ((mLeft == nullptr && x->mLeft != nullptr) || (mLeft != nullptr && !mLeft->isEqual(x->mLeft))) {
		return false;
	}
	if ((mRight == nullptr && x->mRight != nullptr) || (mRight != nullptr && !mRight->isEqual(x->mRight))) {
		return false;
	}
	return true;
}

StructurizerNode::ConditionTree *StructurizerNode::ConditionTree::clone() const
{
	ConditionTree *a = nullptr;
	if (mIsOperator) {
		a = new ConditionTree(mOperator
				, (mLeft != nullptr) ? mLeft->clone() : nullptr
				, (mRight != nullptr) ? mRight->clone() : nullptr);
	} else {
		a = new ConditionTree(mValue);
	}
	a->mInverted = mInverted;
	return a;
}

QPair<StructurizerNode::Vertex, StructurizerNode::Vertex> StructurizerNode::ConditionTree::value() const
{
	return mValue;
}

StructurizerNode::ConditionTree::Operator StructurizerNode::ConditionTree::boolOperator() const
{
	return mOperator;
}

StructurizerNode::ConditionTree *StructurizerNode::ConditionTree::left()
{
	return mLeft;
}

StructurizerNode::ConditionTree *StructurizerNode::ConditionTree::right()
{
	return mRight;
}


StructurizerNode::ConditionTree::~ConditionTree()
{
	delete mLeft;
	delete mRight;
}

int StructurizerNode::ConditionTree::numberOfFirstVertex(const Vertex &id) const
{
	if (mIsValue) {
		return (mValue.first == id) ? 1 : 0;
	}
	if (mIsOperator) {
		return mLeft->numberOfFirstVertex(id) + mRight->numberOfFirstVertex(id);
	}
	return false;
}

bool StructurizerNode::ConditionTree::isTrue() const
{
	QSet<QPair<Vertex, Vertex>> allValues;
	findAllValues(allValues);
	QVector<QPair<Vertex, Vertex>> listValues;
	QMap<QPair<Vertex, Vertex>, bool> boolMapValues;
	for (auto &v : allValues) {
		listValues.append(v);
	}
	QVector<int> binSubset = QVector<int>(listValues.size() + 1, 0);
	while (binSubset[0] == 0) {
		for (int i = 0; i < listValues.size(); ++i) {
			boolMapValues[listValues[i]] = binSubset[i + 1];
		}
		if (!calculateValue(boolMapValues)) {
			return false;
		}
		int i = binSubset.size() - 1;
		while (binSubset[i] == 1) {
			binSubset[i] = 0;
			--i;
		}
		binSubset[i] = 1;
	}
	return true;
}

void StructurizerNode::ConditionTree::findAllValues(QSet<QPair<Vertex, Vertex>> &values) const
{
	if (mIsValue) {
		values.insert(mValue);
		return;
	}
	mRight->findAllValues(values);
	mLeft->findAllValues(values);
}

bool StructurizerNode::ConditionTree::calculateValue(const QMap<QPair<Vertex, Vertex>, bool> &values) const
{
	if (mIsValue) {
		return mInverted ? !values[mValue] : values[mValue];
	}

	bool right = mRight->calculateValue(values);
	bool left = mLeft->calculateValue(values);

	bool result = (mOperator == OR) ? (right || left) : (right && left);

	return mInverted ? !result : result;
}
