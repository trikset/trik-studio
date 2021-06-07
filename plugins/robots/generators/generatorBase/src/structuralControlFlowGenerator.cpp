/* Copyright 2018 Konstantin Batoev
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

#include "structuralControlFlowGenerator.h"

#include "generatorBase/parts/subprograms.h"
#include "generatorBase/parts/threads.h"

using namespace qReal;
using namespace generatorBase;
using namespace semantics;

StructuralControlFlowGenerator::StructuralControlFlowGenerator(const qrRepo::RepoApi &repo
		, ErrorReporterInterface &errorReporter
		, GeneratorCustomizer &customizer
		, PrimaryControlFlowValidator &validator
		, const Id &diagramId
		, QObject *parent
		, bool isThisDiagramMain)
	: ControlFlowGeneratorBase(repo, errorReporter, customizer, validator, diagramId, parent, isThisDiagramMain)
	, mCanBeGeneratedIntoStructuredCode(true)
	, mStructurizer(new Structurizer(this))
	, mIsGraphBeingConstructed(true)
{
}

ControlFlowGeneratorBase *StructuralControlFlowGenerator::cloneFor(const Id &diagramId, bool cloneForNewDiagram)
{
	StructuralControlFlowGenerator * const copy = new StructuralControlFlowGenerator(mRepo
			, mErrorReporter, mCustomizer, cloneForNewDiagram ? *mValidator.clone() : mValidator
			, diagramId, parent(), false);

	return copy;
}

void StructuralControlFlowGenerator::beforeSearch()
{
}

void StructuralControlFlowGenerator::visitRegular(const Id &id, const QList<LinkInfo> &links)
{
	if (!mIsGraphBeingConstructed) {
		ControlFlowGeneratorBase::visitRegular(id, links);
		return;
	}

	appendEdgesAndVertices(id, links);
}

void StructuralControlFlowGenerator::visitConditional(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(links)
	const QPair<LinkInfo, LinkInfo> ifBranches = ifBranchesFor(id);

	appendEdgesAndVertices(id, {ifBranches.first});
	appendEdgesAndVertices(id, {ifBranches.second});
}

void StructuralControlFlowGenerator::visitLoop(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(links)
	if (!mIsGraphBeingConstructed) {
		return;
	}

	const QPair<LinkInfo, LinkInfo> loopBranches = loopBranchesFor(id);

	appendEdgesAndVertices(id, {loopBranches.first});
	appendEdgesAndVertices(id, {loopBranches.second});
}

void StructuralControlFlowGenerator::visitPreconditionalLoop(const Id &id, const QList<LinkInfo> &links)
{
	visitLoop(id, links);
}

void StructuralControlFlowGenerator::visitSwitch(const Id &id, const QList<LinkInfo> &links)
{
	LinkInfo defaultLink;
	for (auto &link : links) {
		if (mRepo.property(link.linkId, "Guard").toString() == "") {
			defaultLink = link;
		} else {
			appendEdgesAndVertices(id, {link});
		}
	}
	appendEdgesAndVertices(id, {defaultLink});
}

void StructuralControlFlowGenerator::visitUnknown(const Id &id, const QList<LinkInfo> &links)
{
	appendEdgesAndVertices(id, links);
}

void StructuralControlFlowGenerator::afterSearch()
{
}

bool StructuralControlFlowGenerator::cantBeGeneratedIntoStructuredCode() const
{
	return !mCanBeGeneratedIntoStructuredCode;
}

void StructuralControlFlowGenerator::performGeneration()
{
	mStartVertex = mSemanticTree->initialBlock();
	mIsGraphBeingConstructed = true;
	ControlFlowGeneratorBase::performGeneration();
	StructurizerNode *tree = mStructurizer->performStructurization(mIds
			, mStartVertex, mFollowers);
	QMap<Id, int> numberOfOccurrences;
	for (const auto &e : mIds) {
		if (mFollowers[e].size() > 1) {
			numberOfOccurrences[e] = tree->numberOfConditionCalculating(e);
		}
	}
	QSet<Id> alreadyCalculated;
	auto zone = new ZoneNode(mSemanticTree);
	makeSemanticTree(tree, zone, numberOfOccurrences, alreadyCalculated);
	mSemanticTree->setRoot(zone);
	mIsGraphBeingConstructed = false;
	ControlFlowGeneratorBase::performGeneration();
}

void StructuralControlFlowGenerator::registerOtherThreads(const Id &id, const QList<LinkInfo> &threads
		, const QHash<Id, QString> &threadIds, parts::Threads &threadsStorage)
{
	if (!mIsGraphBeingConstructed) {
		ControlFlowGeneratorBase::registerOtherThreads(id, threads, threadIds, threadsStorage);
	}
}

void StructuralControlFlowGenerator::registerTerminatingThreads(const Id &id, parts::Threads &threadsStorage
		, bool fromMain)
{
	if (!mIsGraphBeingConstructed) {
		ControlFlowGeneratorBase::registerTerminatingThreads(id, threadsStorage, fromMain);
	}
}

void StructuralControlFlowGenerator::makeSemanticTree(StructurizerNode *nodes, semantics::ZoneNode *zone
					, QMap<Id, int> &numberOfOccurrences, QSet<Id> &alreadyCalculated)
{
	if (nodes != nullptr && nodes->type() == StructurizerNode::Type::sequence) {
		for (auto &s : static_cast<SequenceStructurizerNode *>(nodes)->children()) {
			switch (s->type()) {
				case StructurizerNode::Type::simple: {
					addSimple(s, zone, numberOfOccurrences, alreadyCalculated);
					break;
				}
				case StructurizerNode::Type::breakFromLoop: {
					addBreak(s, zone, numberOfOccurrences, alreadyCalculated);
					break;
				}
				case StructurizerNode::Type::loop: {
					addLoop(s, zone, numberOfOccurrences, alreadyCalculated);
					break;
				}
				case StructurizerNode::Type::ifThenElse: {
					addIf(s, zone, numberOfOccurrences, alreadyCalculated);
					break;
				}
			case StructurizerNode::Type::switchCase: {
					addSwitch(s, zone, numberOfOccurrences, alreadyCalculated);
					break;
				}
				default: {qDebug() << "CONTINUATION IN FINAL TREE"; return;}
			}
		}
	} else qDebug() << "that shouldn't happen too";
}


void StructuralControlFlowGenerator::addSimple(StructurizerNode *node, semantics::ZoneNode *zone
					, QMap<Id, int> &numberOfOccurrences, QSet<Id> &alreadyCalculated)
{
	Q_UNUSED(numberOfOccurrences)
	Q_UNUSED(alreadyCalculated)
	zone->appendChild(mSemanticTree->produceNodeFor(node->id()));
}

void StructuralControlFlowGenerator::addBreak(StructurizerNode *node, semantics::ZoneNode *zone
					, QMap<Id, int> &numberOfOccurrences, QSet<Id> &alreadyCalculated)
{
	Q_UNUSED(node)
	Q_UNUSED(numberOfOccurrences)
	Q_UNUSED(alreadyCalculated)
	zone->appendChild(SimpleNode::createBreakNode(mSemanticTree));
}

void StructuralControlFlowGenerator::addSwitch(StructurizerNode *node, semantics::ZoneNode *zone
					, QMap<Id, int> &numberOfOccurrences, QSet<Id> &alreadyCalculated)
{
	auto switchElement = static_cast<SwitchStructurizerNode *>(node);
	if (numberOfOccurrences[switchElement->id()] > 1) {
		zone->appendChild(SimpleNode::createSyntheticVariableNode(switchElement->id(), mSemanticTree));
		alreadyCalculated.insert(switchElement->id());
	}

	auto switchNode = static_cast<SwitchNode *>(mSemanticTree->produceNodeFor(switchElement->id()));
	zone->appendChild(switchNode);

	QMap<Id, ZoneNode *> addedBranches;
	for (const Id &link : mRepo.outgoingLinks(switchElement->id())) {
		const QString value = mRepo.property(link, "Guard").toString();
		const Id targetId = mRepo.otherEntityFromLink(link, switchElement->id());

		if (addedBranches.contains(targetId)) {
			ZoneNode * const targetZone = addedBranches[targetId];
			switchNode->mergeBranch(value, targetZone);
		} else {
			switchNode->addBranch(value);
			ZoneNode *zoneForBranch = switchNode->branchZoneByValue(value);
			addedBranches[targetId] = zoneForBranch;
			StructurizerNode *branchElement = nullptr;
			if (targetId == (switchElement->defaultBranch().first)) {
				branchElement = switchElement->defaultBranch().second;
			} else {
				branchElement = switchElement->branches().value(targetId);
			}
			makeSemanticTree(branchElement, zoneForBranch, numberOfOccurrences, alreadyCalculated);
		}
	}
}

void StructuralControlFlowGenerator::addIf(StructurizerNode *node, semantics::ZoneNode *zone
					, QMap<Id, int> &numberOfOccurrences, QSet<Id> &alreadyCalculated)
{
	auto ifElement = static_cast<IfStructurizerNode *>(node);
	QMap<Id, bool> idWasUsed;
	for (auto &x : numberOfOccurrences.keys()) { //todo in topological order
		if (ifElement->condition()->numberOfFirstVertex(x) > 0) {
			if (!alreadyCalculated.contains(x) && numberOfOccurrences[x] > 1) {
				zone->appendChild(SimpleNode::createSyntheticVariableNode(x, mSemanticTree));
				alreadyCalculated.insert(x);
			}
			idWasUsed[x] = alreadyCalculated.contains(x);
		}
	}
	auto ifNode = mSemanticTree->produceConditional();
	ifNode->setSyntheticCondition(syntheticConditionToString(ifElement->condition()), idWasUsed);
	zone->appendChild(ifNode);
	if (static_cast<SequenceStructurizerNode *>(ifElement->thenBranch())->children().size() == 0) {
		ifNode->invertCondition();
		makeSemanticTree(ifElement->elseBranch(), ifNode->thenZone(), numberOfOccurrences, alreadyCalculated);
	} else {
		makeSemanticTree(ifElement->thenBranch(), ifNode->thenZone(), numberOfOccurrences, alreadyCalculated);
		makeSemanticTree(ifElement->elseBranch(), ifNode->elseZone(), numberOfOccurrences, alreadyCalculated);
	}
}

void StructuralControlFlowGenerator::addLoop(StructurizerNode *node, semantics::ZoneNode *zone
					, QMap<Id, int> &numberOfOccurrences, QSet<Id> &alreadyCalculated)
{
	auto loopElement = static_cast<LoopStructurizerNode *>(node);
	LoopNode *loopNode = nullptr;
	if (loopElement->id() == Id()) {
		loopNode = mSemanticTree->produceLoop();
	} else {
		loopNode = mSemanticTree->produceLoop(node->id());
		if (loopElement->isInverted()) {
			loopNode->invertCondition();
		}
	}
	zone->appendChild(loopNode);
	makeSemanticTree(loopElement->body(), loopNode->bodyZone(), numberOfOccurrences, alreadyCalculated);
}


void StructuralControlFlowGenerator::appendVertex(const Id &vertex)
{
	mIds.insert(vertex);
}

void StructuralControlFlowGenerator::addEdgeIntoGraph(const Id &from, const Id &to)
{
	if (!mFollowers[from].contains(to)) {
		mFollowers[from].append(to);
	}
}

void StructuralControlFlowGenerator::appendEdgesAndVertices(const Id &vertex, const QList<LinkInfo> &links)
{
	if (!mIsGraphBeingConstructed) {
		return;
	}

	if (!mIds.contains(vertex)) {
		appendVertex(vertex);
	}

	for (const LinkInfo &link : links) {
		const Id otherVertex = link.target;
		if (!mIds.contains(otherVertex)) {
			appendVertex(otherVertex);
		}
		addEdgeIntoGraph(vertex, otherVertex);
	}
}

QString StructuralControlFlowGenerator::syntheticConditionToString(StructurizerNode::ConditionTree *tree)
{
	QString result;
	if (tree->isValue()) {
		auto head = tree->value().first;
		auto target = tree->value().second;
		if (mCustomizer.semanticsOf(head) == enums::semantics::conditionalBlock) {
			//it is if
			result = head.id();
		} else if (mCustomizer.semanticsOf(head) == enums::semantics::switchBlock) {
			//it is switch
			QList<QString> cases;
			for (auto &link : mRepo.outgoingLinks(head)) {
				if (mRepo.otherEntityFromLink(link, head) == target) {
					QString guard = mRepo.property(link, "Guard").toString();
					cases << QString("(%1==%2)").arg(head.id(), guard);
				}
			}
			result = cases.join(" or ");
		} else {
			//strange case
			result = head.id();
		}
	} else {
		result = tree->boolOperator() == StructurizerNode::ConditionTree::OR ? "(@@1@@) or (@@2@@)" : "(@@1@@) and (@@2@@)";
		result.replace("@@1@@", syntheticConditionToString(tree->left())).replace("@@2@@", syntheticConditionToString(tree->right()));
	}
	return tree->isInverted() ? QString("not(%1)").arg(result) : result;
}
