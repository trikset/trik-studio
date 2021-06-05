#pragma once

#include "structurizerNode.h"

#include <qrkernel/ids.h>

namespace generatorBase {

class SimpleStructurizerNode : public StructurizerNode
{
	Q_OBJECT

public:
	explicit SimpleStructurizerNode(const Vertex &id, QObject *parent);

	Vertex id() const;
	Type type() const;

	bool containsContinuation(const Vertex &id = Vertex()) const;
	void dropContinuations(const Vertex &id);
	int numberOfContinuation(const Vertex &id = Vertex()) const;

	void factorize(const Vertex &id, bool force = false);
	void derecursivate(const Vertex &id);
	void replaceContinuation(const Vertex &id, StructurizerNode *value);

	bool mergeConditionalBranches(const QSet<Vertex> &exits, const QSet<Vertex> &loopHeads);
	void transformDoWhile();

	ConditionTree *findAllContinuations(const Vertex &id) const;
	bool isEqual(StructurizerNode *other) const;
	StructurizerNode *clone() const;
	int numberOfConditionCalculating(const Vertex &id) const;
	void dropEmptyConditionals();
	void transformBeforeDerecursivation();

protected:
	const Vertex mId;

};
}
