/* Copyright 2007-2015 QReal Research Group
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

#include "generatorBase/semanticTree/simpleNode.h"

#include <qrutils/stringUtils.h>
#include "generatorBase/semanticTree/zoneNode.h"

using namespace generatorBase::semantics;
using namespace qReal;

SimpleNode::SimpleNode(const Id &idBinded, QObject *parent)
	: NonZoneNode(idBinded, parent)
	, mSyntheticBinding(noSytheticBinding)
{
}

QString SimpleNode::toStringImpl(GeneratorCustomizer &customizer, int indent, const QString &indentString) const
{
	switch (mSyntheticBinding) {
	case breakNode:
		return utils::StringUtils::addIndent(customizer.factory()->breakGenerator(mId
				, customizer)->generate(), indent, indentString);
	case passNode:
		return utils::StringUtils::addIndent(customizer.factory()->passGenerator(mId
				, customizer)->generate(), indent, indentString);
	case continueNode:
		return utils::StringUtils::addIndent(customizer.factory()->continueGenerator(mId
				, customizer)->generate(), indent, indentString);
	case gotoNode:
		return utils::StringUtils::addIndent(customizer.factory()->gotoSimpleGenerator(mId
				, customizer)->generate(), indent, indentString);
	case tempVariableNode:
		return utils::StringUtils::addIndent(customizer.factory()->syntheticVariableNameGenerator(mId
				, customizer)->generate(), indent, indentString);
	default:
		return utils::StringUtils::addIndent(customizer.factory()->simpleGenerator(mId
				, customizer)->generate(), indent, indentString);
	}
}

void SimpleNode::bindToSyntheticConstruction(SimpleNode::SyntheticBlockType type)
{
	mSyntheticBinding = type;
}

SimpleNode *SimpleNode::createBreakNode(QObject *parent)
{
	SimpleNode *breakNode = new SimpleNode(qReal::Id(), parent);
	breakNode->bindToSyntheticConstruction(SyntheticBlockType::breakNode);
	return breakNode;
}

SimpleNode *SimpleNode::createPassNode(QObject *parent)
{
	SimpleNode *passNode = new SimpleNode(qReal::Id(), parent);
	passNode->bindToSyntheticConstruction(SyntheticBlockType::passNode);
	return passNode;
}

SimpleNode *SimpleNode::createSyntheticVariableNode(const qReal::Id &id, QObject *parent)
{
	SimpleNode *varNode = new SimpleNode(id, parent);
	varNode->bindToSyntheticConstruction(SyntheticBlockType::tempVariableNode);
	return varNode;
}

QLinkedList<SemanticNode *> SimpleNode::children() const
{
	return QLinkedList<SemanticNode *>();
}
