#pragma once

#include "simpleStructurizerNode.h"

namespace generatorBase {

class BreakStructurizerNode : public SimpleStructurizerNode
{
public:
	explicit BreakStructurizerNode(QObject *parent = nullptr);

	Type type() const;
	bool isEqual(StructurizerNode *other) const;
	bool hasBreakOnUpperLevel() const;

	StructurizerNode *clone() const;
};
}
