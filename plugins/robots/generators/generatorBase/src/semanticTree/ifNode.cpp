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

#include "generatorBase/semanticTree/ifNode.h"

#include <qrutils/stringUtils.h>

using namespace generatorBase::semantics;
using namespace qReal;

IfNode::IfNode(const Id &idBinded, QObject *parent)
	: ConditionalNode(idBinded, parent)
	, mThenZone(new ZoneNode(this))
	, mElseZone(new ZoneNode(this))
	, mIsSimple(false)
	, mIsSynthetic(false)
{
	mThenZone->setParentNode(this);
	mElseZone->setParentNode(this);
}

IfNode::IfNode(QObject *parent)
	: ConditionalNode(qReal::Id(), parent)
	, mThenZone(new ZoneNode(this))
	, mElseZone(new ZoneNode(this))
	, mIsSimple(false)
	, mIsSynthetic(true)
{
	mThenZone->setParentNode(this);
	mElseZone->setParentNode(this);
}

ZoneNode *IfNode::thenZone()
{
	return mThenZone;
}

ZoneNode *IfNode::elseZone()
{
	return mElseZone;
}

void IfNode::transformToSimple()
{
	mIsSimple = true;
}

void IfNode::setSyntheticCondition(const QString &s, const QMap<qReal::Id, bool> &l)
{
	mIsSynthetic = true;
	mSyntheticCondition = s;
	mIdWasUsedBefore = l;
}

QString IfNode::toStringImpl(GeneratorCustomizer &customizer, int indent, const QString &indentString) const
{
	if (mIsSimple) {
		return mThenZone->toString(customizer, indent, indentString);
	}

	if (mThenZone->isEmpty() && mElseZone->isEmpty()) {
		return QString();
	}

	const bool elseIsEmpty = mElseZone->isEmpty();
	QString result = mIsSynthetic ?
		utils::StringUtils::addIndent(customizer.factory()->
					syntheticIfGenerator(mId, mIdWasUsedBefore, customizer, elseIsEmpty, mSyntheticCondition, mAddNotToCondition)->generate(), indent, indentString)
		: utils::StringUtils::addIndent(customizer.factory()->
			ifGenerator(mId, customizer, elseIsEmpty, mAddNotToCondition)->generate(), indent, indentString);

	const QString thenBlock = mThenZone->toString(customizer, indent + 1, indentString);
	const QString elseBlock = mElseZone->toString(customizer, indent + 1, indentString);

	result.replace("@@THEN_BODY@@", thenBlock);
	result.replace("@@ELSE_BODY@@", elseBlock);
	return result;
}

QLinkedList<SemanticNode *> IfNode::children() const
{
	return QLinkedList<SemanticNode *>() << mThenZone << mElseZone;
}
