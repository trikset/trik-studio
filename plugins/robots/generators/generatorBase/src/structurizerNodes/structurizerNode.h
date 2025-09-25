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

#pragma once

#include <qrkernel/ids.h>

namespace generatorBase {

class StructurizerNode : public QObject
{
public:
	enum Type {
		simple
		, continuation
		, loop
		, ifThenElse
		, switchCase
		, sequence
		, breakFromLoop
	};

	typedef qReal::Id Vertex;

	class ConditionTree {
	public:
		enum Operator {OR, AND};

		ConditionTree(const QPair<Vertex, Vertex> &idPair);
		ConditionTree(Operator o, ConditionTree *left, ConditionTree *right);
		void invert();
		bool isValue() const;
		bool isBoolOperator() const;
		bool isInverted() const;
		QPair<Vertex, Vertex> value() const;
		Operator boolOperator() const;
		ConditionTree *left();
		ConditionTree *right();
		bool isEqual(const ConditionTree *x) const;
		bool isNegativeTo(const ConditionTree *x) const;
		bool isTrue() const;
		ConditionTree *clone() const;

		int numberOfFirstVertex(const Vertex &id) const;
		~ConditionTree();

	private:
		bool calculateValue(const QMap<QPair<Vertex, Vertex>, bool> &values) const;
		void findAllValues(QSet<QPair<Vertex, Vertex>> &values) const;

		bool mInverted;
		const bool mIsOperator;
		const bool mIsValue;
		QPair<Vertex, Vertex> mValue;
		Operator mOperator;
		ConditionTree *mLeft;
		ConditionTree *mRight;
	};

	explicit StructurizerNode(QObject *parent);
	~StructurizerNode();

	virtual Type type() const = 0;
	virtual Vertex id() const = 0;

	virtual bool containsContinuation(const Vertex &id = Vertex()) const = 0;
	virtual void dropContinuations(const Vertex &id) = 0;
	virtual int numberOfContinuation(const Vertex &id = Vertex()) const = 0;

	virtual void factorize(const Vertex &id, bool force = false) = 0;
	virtual void derecursivate(const Vertex &id) = 0;
	virtual void replaceContinuation(const Vertex &id, StructurizerNode *value) = 0;

	virtual bool mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads) = 0;

	virtual void transformDoWhile() = 0;
	virtual ConditionTree *findAllContinuations(const Vertex &id) const = 0;
	virtual bool isEqual(StructurizerNode *other) const = 0;
	virtual StructurizerNode *clone() const = 0;
	virtual int numberOfConditionCalculating(const Vertex &id) const = 0;
	virtual bool hasBreakOnUpperLevel() const = 0;

	virtual void dropEmptyConditionals() = 0;
};
}
