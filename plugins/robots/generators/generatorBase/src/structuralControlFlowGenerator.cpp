/* Copyright 2017 QReal Research Group
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

#include <QtCore/QQueue>

#include <QtCore/QDebug>

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
	, mNumberOfVerteces(0)
	, mEntry(0)
	, mVerteces(QList<VertexLabel>())
	, mCounter(1)
{
}

ControlFlowGeneratorBase *StructuralControlFlowGenerator::cloneFor(const Id &diagramId, bool cloneForNewDiagram)
{
	Q_UNUSED(diagramId)
	Q_UNUSED(cloneForNewDiagram)
	// to do
	return nullptr;
}

void StructuralControlFlowGenerator::beforeSearch()
{
	// to do
}

void StructuralControlFlowGenerator::visitFinal(const Id &id, const QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitFork(const Id &id, QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitJoin(const Id &id, QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitRegular(const Id &id, const QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitConditional(const Id &id, const QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitLoop(const Id &id, const QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitSwitch(const Id &id, const QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::visitUnknown(const Id &id, const QList<LinkInfo> &links)
{
	buildGraph(id, links);
}

void StructuralControlFlowGenerator::afterSearch()
{
	// to do
}

SemanticTree *StructuralControlFlowGenerator::generate(const Id &initialNode, const QString &threadId)
{

	ControlFlowGeneratorBase::generate(initialNode, threadId);
	delete mSemanticTree;
	mSemanticTree->setRoot(new RootNode(mNodesForest.first()));
	return mSemanticTree;
}

void StructuralControlFlowGenerator::performGeneration()
{
	// to bypass diagram and build graph
	ControlFlowGeneratorBase::performGeneration();
	// to-do check whether diagram was right, maybe ControlFlowGeneratorBase is checking it

	performAnalysis();
}

void StructuralControlFlowGenerator::updateForest(graphUtils::RegionType type, graphUtils::VertexLabel newId, QVector<graphUtils::VertexLabel> &nodesThatComposeRegion)
{
	switch (type) {
	case RegionType::Block:
	{
		semantics::ZoneNode *newNode = new semantics::ZoneNode();
		for (auto it = nodesThatComposeRegion.begin(); it != nodesThatComposeRegion.end(); ++it) {
			auto label = *it;
			newNode->appendChild(mNodesForest[label]);
			mNodesForest[label]->setParent(newNode);
			mNodesForest.remove(label);
		}
		mNodesForest.insert(newId, newNode);
		break;
	}

	case RegionType::IfThen:
	{
		// 0 is hardcoded to be condition
		VertexLabel ifNodeLabel = nodesThatComposeRegion.at(0);
		semantics::IfNode *newNode = new semantics::IfNode(mNodesForest[ifNodeLabel]->id());
		VertexLabel thenNodeLabel = nodesThatComposeRegion.at(1);

		mNodesForest[ifNodeLabel]->setParent(newNode);

		newNode->thenZone()->appendChild(mNodesForest[thenNodeLabel]);
		mNodesForest[thenNodeLabel]->setParent(newNode->thenZone());

		mNodesForest.remove(ifNodeLabel);
		mNodesForest.remove(thenNodeLabel);

		mNodesForest.insert(newId, newNode);
		break;
	}

	case RegionType::IfThenElse:
	{
		// 0 is hardcoded to be condition
		VertexLabel ifNodeLabel = nodesThatComposeRegion.at(0);
		semantics::IfNode *newNode = new semantics::IfNode(mNodesForest[ifNodeLabel]->id());

		VertexLabel thenNodeLabel = nodesThatComposeRegion.at(1);
		VertexLabel elseNodeLabel = nodesThatComposeRegion.at(2);
		mNodesForest[thenNodeLabel]->setParent(newNode->thenZone());
		mNodesForest[elseNodeLabel]->setParent(newNode->elseZone());

		newNode->thenZone()->appendChild(mNodesForest[thenNodeLabel]);
		newNode->elseZone()->appendChild(mNodesForest[elseNodeLabel]);

		mNodesForest.remove(thenNodeLabel);
		mNodesForest.remove(elseNodeLabel);
		mNodesForest.remove(ifNodeLabel);

		mNodesForest.insert(newId, newNode);
		break;
	}

	case RegionType::SelfLoop:
	{
		// 0 is hardcoded to be condition
		VertexLabel selfLoopLabel = nodesThatComposeRegion.at(0);
		semantics::LoopNode *newNode = new semantics::LoopNode(qReal::Id());

		mNodesForest[selfLoopLabel]->setParent(newNode);
		newNode->bodyZone()->appendChild(mNodesForest[selfLoopLabel]);

		mNodesForest.remove(selfLoopLabel);
		mNodesForest.insert(newId, newNode);
		break;
	}

	case RegionType::WhileLoop:
	{
		// 0 is hardcoded to be condition
		VertexLabel conditionLabel = nodesThatComposeRegion.at(0);
		semantics::LoopNode *newNode = new semantics::LoopNode(mNodesForest[conditionLabel]->id());
		VertexLabel bodyLabel = nodesThatComposeRegion.at(1);

		mNodesForest[conditionLabel]->setParent(newNode);
		mNodesForest[bodyLabel]->setParent(newNode);

		newNode->bodyZone()->appendChild(mNodesForest[bodyLabel]);

		mNodesForest.remove(conditionLabel);
		mNodesForest.remove(bodyLabel);
		mNodesForest.insert(newId, newNode);
		break;
	}


	}
}

void StructuralControlFlowGenerator::buildInitialForest()
{
	for (qReal::Id id : mInitialVerteces.keys()) {
		VertexLabel label = mInitialVerteces[id]->id();
		mNodesForest.insert(label, mSemanticTree->produceNodeFor(id));
	}
}

void StructuralControlFlowGenerator::buildGraph(const Id &id, const QList<LinkInfo> &links)
{
	Node *currentVertex = nullptr;
	if (mInitialVerteces.contains(id)) {
		currentVertex = mInitialVerteces[id];
	} else {
		currentVertex = new Node(mCounter++, RegionType::simpleNode);
		allNodes.append(currentVertex);
		mNumberOfVerteces++;
		mInitialVerteces[id] = currentVertex;
		mVerteces.push_back(currentVertex->id());
	}

	if (!mEntry) {
		mEntry = currentVertex->id();
	}

	for (const LinkInfo link : links) {
		Node * targetVertex = nullptr;
		if (mInitialVerteces.contains(link.target)) {
			targetVertex = mInitialVerteces[link.target];
		} else {
			targetVertex = new Node(mCounter++, RegionType::simpleNode);
			allNodes.append(currentVertex);
			mNumberOfVerteces++;
			mInitialVerteces[link.target] = targetVertex;
			mVerteces.push_back(targetVertex->id());
		}
		mFollowers[currentVertex->id()].push_back(targetVertex->id());
		mPredecessors[targetVertex->id()].push_back(currentVertex->id());
	}
}

// to do
// to save invariant that mGraph only has valid nodes and edges,
// so it would be possible not to pass setOfNodes
void StructuralControlFlowGenerator::performAnalysis()
{
	findDominators();

	buildInitialForest();

	for (Node *node : mInitialVerteces.values()) {
		mUsed[node->id()] = false;
		mPostOrder[node->id()] = -1;
	}

	int time = 0;
	VertexLabel entry = mEntry;
	dfs(entry, time);

	mCurrentTime = 0;
	mMaxTime = time - 1;

	// it is supposed that mFollowers.size() == mPredecessors.size() == actual number of
	// verteces in current flowgraph

	while (mFollowers.keys().size() > 1 && mCurrentTime <= mMaxTime) {
		const VertexLabel currentNode = mPostOrder.key(mCurrentTime);

		graphUtils::Region * region = determineAcyclicRegionType(currentNode);

		if (region->type() != RegionType::nil) {
			Node *newNode = reduce(region);
			if (region->nodes().contains(mEntry)) {
				mEntry = newNode->id();
			}
		} else {
			QVector<VertexLabel> reachUnder = countReachUnder(currentNode);
			delete region;
			region = determineCyclicRegionType(currentNode, reachUnder);
			if (region->type() != RegionType::nil) {
				Node *newNode = reduce(region);
				if (reachUnder.contains(mEntry)) {
					mEntry = newNode->id();
				}
			} else {
				mCurrentTime++;
			}
		}
	}

	qDebug() << "Success\n";
}

void StructuralControlFlowGenerator::findDominators()
{
	for (VertexLabel vertexLabel : mVerteces) {
		mDominators[vertexLabel] = mVerteces.toSet();
	}

	VertexLabel entry = mEntry;
	mDominators[entry] = { entry };


	bool somethingChanged = true;
	while (somethingChanged) {
		somethingChanged = false;

		// excluding root
		for (VertexLabel vertexLabel : mVerteces) {
			if (vertexLabel != mEntry) {
				QSet<VertexLabel> newDominators = mVerteces.toSet();
				for (VertexLabel predecessor : mPredecessors[vertexLabel]) {
					newDominators.intersect(mDominators[predecessor]);
				}
				// adding the current number, because reflexivity of dominance relation
				newDominators.insert(vertexLabel);
				if (newDominators != mDominators[vertexLabel]) {
					somethingChanged = true;
					mDominators[vertexLabel] = newDominators;
				}
			}
		}
	}
}

void StructuralControlFlowGenerator::dfs(graphUtils::VertexLabel u, int &postOrderLabel)
{
	mUsed[u] = true;
	for (VertexLabel vertexLabel : mFollowers[u]) {
		if (!mUsed[vertexLabel]) {
			dfs(vertexLabel, postOrderLabel);
		}
	}
	mPostOrder[u] = postOrderLabel;
	postOrderLabel++;
}

Region * StructuralControlFlowGenerator::determineAcyclicRegionType(graphUtils::VertexLabel node)
{
	QVector<VertexLabel> blockNodes;
	VertexLabel currentNode = node;

	bool hasOnlyOneIncomingEdge = true;
	bool hasOnlyOneOutcomingEdge = mFollowers[currentNode].size() == 1;

	while (hasOnlyOneIncomingEdge && hasOnlyOneOutcomingEdge) {
		blockNodes.push_back(currentNode);
		currentNode = mFollowers[currentNode].at(0);
		hasOnlyOneIncomingEdge = mPredecessors[currentNode].size() == 1;
		hasOnlyOneOutcomingEdge = mFollowers[currentNode].size() == 1;
	}

	if (hasOnlyOneIncomingEdge) {
		blockNodes.push_back(currentNode);
	}

	currentNode = node;
	hasOnlyOneIncomingEdge = mPredecessors[currentNode].size() == 1;
	hasOnlyOneOutcomingEdge = true;

	while (hasOnlyOneIncomingEdge && hasOnlyOneOutcomingEdge) {
		if (!blockNodes.contains(currentNode)) {
			blockNodes.push_front(currentNode);
		}
		currentNode = mPredecessors[currentNode].at(0);
		hasOnlyOneIncomingEdge = mPredecessors[currentNode].size() == 1;
		hasOnlyOneOutcomingEdge = mFollowers[currentNode].size() == 1;
	}

	if (hasOnlyOneOutcomingEdge && !blockNodes.contains(currentNode)) {
		blockNodes.push_front(currentNode);
	}

	node = currentNode;

	if (blockNodes.size() >= 2) {
		return new graphUtils::BlockRegion(blockNodes);
	}


	// checking for IfThenElse
	if (mFollowers[node].size() == 2) {
		VertexLabel m = mFollowers[node].at(0);
		VertexLabel n = mFollowers[node].at(1);

		if (mFollowers[m].size() == 1 && mFollowers[n].size() == 1
				&& mFollowers[m].at(0) == mFollowers[n].at(0)
				&& mPredecessors[m].size() == 1 && mPredecessors[n].size() == 1) {

			graphUtils::IfThenElseRegion *ifThenElseRegion = new graphUtils::IfThenElseRegion();
			ifThenElseRegion->addCondition(node);
			ifThenElseRegion->addThen(m);
			ifThenElseRegion->addElse(n);

			return ifThenElseRegion;
		}

	}

	// checking IfThen
	if (mFollowers[node].size() == 2) {
		VertexLabel m = mFollowers[node].at(0);
		VertexLabel n = mFollowers[node].at(1);

		VertexLabel thenNode = -1;
		if (mFollowers[m].size() == 1 && mFollowers[m].at(0) == n && mPredecessors[m].size() == 1) {
			thenNode = m;
		} else if (mFollowers[n].size() == 1 && mFollowers[n].at(0) == m && mPredecessors[n].size() == 1) {
			thenNode = n;
		}

		if (thenNode >= 0) {
			graphUtils::IfThenRegion *ifThenRegion = new graphUtils::IfThenRegion();
			ifThenRegion->addCondition(node);
			ifThenRegion->addThen(thenNode);
			return ifThenRegion;
		}
	}

	return new graphUtils::NilRegion();
}

Region * StructuralControlFlowGenerator::determineCyclicRegionType(graphUtils::VertexLabel node, QVector<graphUtils::VertexLabel> &reachUnder)
{
	if (reachUnder.size() == 1) {
		VertexLabel node = reachUnder.first();
		if (mFollowers[node].contains(node)) {
			return new graphUtils::SelfLoopRegion(node);
		}
	}
	else if (reachUnder.size() == 2) {
		VertexLabel lastNode = reachUnder.last() == node ? reachUnder.first() : reachUnder.last();
		if (mFollowers[node].size() == 2 && mFollowers[lastNode].size() == 1
				&& mPredecessors[lastNode].size() == 1) {
			return new graphUtils::WhileLoopRegion(node, lastNode);
		}
	}
	else {
		return new graphUtils::NilRegion();
	}
}

graphUtils::Node *StructuralControlFlowGenerator::reduce(graphUtils::Region *region)
{
	bool hasBackEdgeForBlock = false;
	QVector<VertexLabel> nodesThatComposeRegion = region->nodes();

	if (region->type() == RegionType::Block) {
		VertexLabel lastNode = nodesThatComposeRegion.last();
		VertexLabel firstNode = nodesThatComposeRegion.first();
		hasBackEdgeForBlock = mFollowers[lastNode].contains(firstNode);
	}

	Node *abstractNode = new Node(mCounter++, region->type());

	updateForest(region->type(), abstractNode->id(), nodesThatComposeRegion);
	replace(abstractNode->id(), nodesThatComposeRegion);

	allNodes.append(abstractNode);
	for (VertexLabel currentLabel : nodesThatComposeRegion) {

		// place for optimization
		for (Node *current : allNodes) {
			if (current->id() == currentLabel) {
				current->setParent(abstractNode->id());
			}
		}

		// saving graph invariant
		mFollowers.remove(currentLabel);
		mPredecessors.remove(currentLabel);
	}

	VertexLabel newLabel = abstractNode->id();
	if (hasBackEdgeForBlock) {
		mFollowers[newLabel].push_back(newLabel);
		mPredecessors[newLabel].push_back(newLabel);
	}

	// updating dominators
	// new function?
	QSet<VertexLabel> setForNewNode = {newLabel};
	for (VertexLabel vertexLabel : nodesThatComposeRegion) {
		setForNewNode = setForNewNode.unite(mDominators[vertexLabel]);
	}
	setForNewNode = setForNewNode.intersect(mVerteces.toSet());
	mDominators.insert(abstractNode->id(), setForNewNode);

	for (VertexLabel vertexLabel : nodesThatComposeRegion) {
		mDominators.remove(vertexLabel);
	}

	for (auto it = mDominators.begin(); it != mDominators.end(); ++it) {
		VertexLabel currentVertex = it.key();
		QSet<VertexLabel> oldSet, newSet = it.value();
		oldSet = newSet;
		bool isNeededNewLabel = false;

		for (VertexLabel v : oldSet) {
			if (nodesThatComposeRegion.contains(v)) {
				isNeededNewLabel = true;
				newSet.remove(v);
			}
		}

		if (isNeededNewLabel) {
			newSet.insert(currentVertex);
		}

		mDominators.insert(currentVertex, newSet);
	}

	abstractNode->appendChildren(nodesThatComposeRegion);

	return abstractNode;
}

void StructuralControlFlowGenerator::replace(VertexLabel node, QVector<graphUtils::VertexLabel> &nodesThatComposeRegion)
{
	compact(node, nodesThatComposeRegion);

	QMap<VertexLabel, QVector<VertexLabel> > followers;

	// set of edges is determined by mFollowers or mPredecessors

	for (auto it = mFollowers.begin(); it != mFollowers.end(); ++it) {
		VertexLabel currentLabel = it.key();

		for (VertexLabel nextLabel : it.value()) {
			if (nodesThatComposeRegion.contains(nextLabel) || nodesThatComposeRegion.contains(currentLabel)) {
				removeFrom(mPredecessors, nextLabel, currentLabel);

				if (mVerteces.contains(currentLabel) && currentLabel != node) {
					if (followers.contains(currentLabel)) {
						if (!followers[currentLabel].contains(node)) {
							addTo(followers, currentLabel, node);
							addTo(mPredecessors, node, currentLabel);
						}
					} else {
						addTo(followers, currentLabel, node);
						addTo(mPredecessors, node, currentLabel);
					}
				} else if (mVerteces.contains(nextLabel) && currentLabel != node) {
					if (followers.contains(node)) {
						if (!followers[node].contains(nextLabel)) {
							addTo(followers, node, nextLabel);
							addTo(mPredecessors, nextLabel, node);
						}
					} else {
						addTo(followers, node, nextLabel);
						addTo(mPredecessors, nextLabel, node);
					}
				}

			} else {
				addTo(followers, currentLabel, nextLabel);
			}

		}
	}

	mFollowers = followers;

	// deal with Tree
	//node->appendChildren(nodesThatComposeRegion);
}

void StructuralControlFlowGenerator::compact(VertexLabel node, QVector<VertexLabel> &nodesThatComposeRegion)
{
	mVerteces.append(node);
	int maxPostOrderNumber = -1;

	for (VertexLabel label : nodesThatComposeRegion) {
		if (mPostOrder[label] > maxPostOrderNumber) {
			maxPostOrderNumber = mPostOrder[label];
		}
	}

	mPostOrder[node] = maxPostOrderNumber;

	for (VertexLabel label : nodesThatComposeRegion) {
		mVerteces.removeOne(label);
		mPostOrder.remove(label);
	}

	int appropriateTime = 0;
	for (int i = 0; i <= mMaxTime; i++) {

		if (mPostOrder.values().contains(i)) {
			VertexLabel labelWithTimeI = mPostOrder.key(i);
			mPostOrder[labelWithTimeI] = appropriateTime;
			appropriateTime++;
		}
	}

	mCurrentTime = mPostOrder[node];
	mMaxTime = appropriateTime - 1;
}

void StructuralControlFlowGenerator::removeFrom(QMap<graphUtils::VertexLabel, QVector<graphUtils::VertexLabel> > &map, graphUtils::VertexLabel element, graphUtils::VertexLabel elementToRemove)
{
	auto labels = map.value(element);
	if (!labels.isEmpty()) {
		labels.removeOne(elementToRemove);
		map.insert(element, labels);
	}
}

void StructuralControlFlowGenerator::addTo(QMap<graphUtils::VertexLabel, QVector<graphUtils::VertexLabel> > &map, graphUtils::VertexLabel element, graphUtils::VertexLabel elementToAdd)
{
	auto labels = map.value(element);
	if (!labels.contains(elementToAdd)) {
		labels.push_back(elementToAdd);
		map.insert(element, labels);
	}
}

QVector<graphUtils::VertexLabel> StructuralControlFlowGenerator::countReachUnder(VertexLabel currentNode)
{
	QVector<VertexLabel> reachUnder = {currentNode};

	QMap<VertexLabel, bool> used;
	QQueue<VertexLabel> nodesThatHavePathAndBackEdgeToCurrentNode;
	// only nodes that are dominated by currentNode can be presented in reachUnder
	for (VertexLabel node : mVerteces) {
		used[node] = false;
		if (mDominators[node].contains(currentNode) && mFollowers[node].contains(currentNode)) {
			nodesThatHavePathAndBackEdgeToCurrentNode.enqueue(node);
		}
	}

	used[currentNode] = true;
	while (!nodesThatHavePathAndBackEdgeToCurrentNode.isEmpty()) {
		VertexLabel node = nodesThatHavePathAndBackEdgeToCurrentNode.dequeue();
		reachUnder.push_back(node);
		used[node] = true;
		for (VertexLabel predecessor : mPredecessors[node]) {
			if (!used[predecessor]) {
				nodesThatHavePathAndBackEdgeToCurrentNode.enqueue(predecessor);
			}
		}
	}

	return reachUnder;
}

