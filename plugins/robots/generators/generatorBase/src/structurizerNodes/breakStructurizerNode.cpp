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
