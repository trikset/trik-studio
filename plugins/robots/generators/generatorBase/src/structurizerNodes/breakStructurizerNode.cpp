#include "breakStructurizerNode.h"

using namespace generatorBase;

BreakStructurizerNode::BreakStructurizerNode(QObject *parent)
	: SimpleStructurizerNode(qReal::Id(), parent)
{
}

StructurizerNode::Type BreakStructurizerNode::type() const
{
	return breakFromLoop;
}

bool BreakStructurizerNode::isEqual(StructurizerNode * other) const
{
	return other->type() == breakFromLoop;
}

StructurizerNode *BreakStructurizerNode::clone() const
{
	return new BreakStructurizerNode(parent());
}

bool BreakStructurizerNode::hasBreakOnUpperLevel() const
{
	return true;
}
