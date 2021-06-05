#pragma once

#include "structurizerNode.h"

#include <qrkernel/ids.h>

namespace generatorBase {

class IfStructurizerNode : public StructurizerNode
{
	Q_OBJECT

public:
	explicit IfStructurizerNode(const qReal::Id &id, const qReal::Id &firstId, const qReal::Id &secondId, QObject *parent);
	explicit IfStructurizerNode(ConditionTree *ifCondition, QObject *parent);
	explicit IfStructurizerNode(QObject *parent);

	Type type() const;
	Vertex id() const;

	QVector<StructurizerNode *> *thenBranch();
	QVector<StructurizerNode *> *elseBranch();

	ConditionTree *condition();

	bool containsContinuation(const Vertex &id = qReal::Id());
	bool containsNonContinuation();
	bool isEqual(StructurizerNode * another);
	ConditionTree *findAllContinuations(const Vertex &id);

	StructurizerNode *clone();

	bool hasSameCondition(IfStructurizerNode *x);

	//StructurizerNode copy();

	void dropContinuations(const Vertex &id = qReal::Id());
	void dropNonContinuations();


protected:

	ConditionTree *mCondition;

	QVector<StructurizerNode *> *mThenBranch;
	QVector<StructurizerNode *> *mElseBranch;
};

}
