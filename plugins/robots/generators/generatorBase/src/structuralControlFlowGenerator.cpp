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
	, mVertecesNumber(1)
	, mEdgesNumber(1)
	, isPerformingGeneration(false)
{
}

ControlFlowGeneratorBase *StructuralControlFlowGenerator::cloneFor(const Id &diagramId, bool cloneForNewDiagram)
{
	StructuralControlFlowGenerator * const copy = new StructuralControlFlowGenerator(mRepo
			, mErrorReporter, mCustomizer, (cloneForNewDiagram ? *mValidator.clone() : mValidator)
			, diagramId, parent(), false);

	return copy;
}

void StructuralControlFlowGenerator::beforeSearch()
{
}

void StructuralControlFlowGenerator::visit(const Id &id, QList<LinkInfo> &links)
{
	initVerteces(id, links);
}

void StructuralControlFlowGenerator::visitRegular(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(id)
	Q_UNUSED(links)
}

void StructuralControlFlowGenerator::visitConditional(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(id)
	Q_UNUSED(links)
}

void StructuralControlFlowGenerator::visitLoop(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(id)
	Q_UNUSED(links)
}

void StructuralControlFlowGenerator::visitSwitch(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(id)
	Q_UNUSED(links)
}

void StructuralControlFlowGenerator::visitUnknown(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(id)
	Q_UNUSED(links)
}

void StructuralControlFlowGenerator::afterSearch()
{
}

bool StructuralControlFlowGenerator::cantBeGeneratedIntoStructuredCode() const
{
	return mCantBeGeneratedIntoStructuredCode;
}

SemanticTree *StructuralControlFlowGenerator::generate(const Id &initialNode, const QString &threadId)
{
	ControlFlowGeneratorBase::generate(initialNode, threadId);
	return mSemanticTree;
}

void StructuralControlFlowGenerator::performGeneration()
{
	//isPerformingGeneration = false;
	mCantBeGeneratedIntoStructuredCode = false;
	ControlFlowGeneratorBase::performGeneration();

	buildGraph();
	findStartVertex();
	findDominators();
	createInitialSemanticNodes();
	int currentTime = 0;

	mUsed.clear();
	for (const int v : mVerteces) {
		mUsed[v] = false;
	}

	dfs(mStartVertex, currentTime);
	mMaxPostOrderTime = currentTime - 1;

	mSomethingChanged = true;
	while (mSomethingChanged) {
		mSomethingChanged = false;

		int t = 0;
		while (t <= mMaxPostOrderTime) {
			int v = mPostOrder.key(t);
			QSet<int> edgesToRemove = {};
			QMap<QString, int> vertecesRoles;
			if (isBlock(v, edgesToRemove, vertecesRoles)) {
				reduceBlock(edgesToRemove, vertecesRoles);
				mSomethingChanged = true;
			} else if (isIfThenElse(v, edgesToRemove, vertecesRoles)) {

			}
			else {
				t++;
			}
		}
	}

	//isPerformingGeneration = true;
	//ControlFlowGeneratorBase::performGeneration();

	//isPerformingGeneration = false;

	if (mVerteces.size() == 1) {
		qDebug() << "Success!";
		mSemanticTree->setRoot(new RootNode(mTrees[mStartVertex]));
	} else {
		mCantBeGeneratedIntoStructuredCode = true;
		mSemanticTree = nullptr;
	}

}

bool StructuralControlFlowGenerator::isBlock(int v, QSet<int> &edgesToRemove, QMap<QString, int> &vertecesRoles)
{
	if (numberOfOutgoingEdges(v) != 1)
		return false;

	QMap<int, QVector<int>> outgoingEdges = mFollowers2[v];
	int u = outgoingEdges.keys().first();
	if (numberOfOutgoingEdges(u) <= 1 && numberOfIncomingEdges(u) == 1) {
		vertecesRoles["block1"] = v;
		vertecesRoles["block2"] = u;
		edgesToRemove += { mFollowers2[v][u].first() };
		return true;
	}

	return false;
}

bool StructuralControlFlowGenerator::isIfThenElse(int v, QSet<int> &edgesToRemove, QMap<QString, int> &vertecesRoles)
{
	if (numberOfOutgoingEdges(v) == 2) {
		QList<int> followers = mFollowers2[v].keys();
		int u1 = followers.first();
		int u2 = followers.last();
		if (numberOfIncomingEdges(u1) != 1 || numberOfIncomingEdges(u2) != 1) {
			return false;
		}

		if (numberOfOutgoingEdges(u1) == 0 && numberOfOutgoingEdges(u2) == 0) {
			int trueEdgeNumber = getTrueLink(v);
			QString condition = getCondition(mMapId[v], mEdges[trueEdgeNumber].mLinkName);
			IfNode *ifNode = new IfNode(condition);
			if (mFollowers2[v][u1].first() == trueEdgeNumber) {
				int temp = u1;
				u1 = u2;
				u2 = temp;
			}

			ifNode->thenZone()->appendChild(mTrees[u2]);
			ifNode->elseZone()->appendChild(mTrees[u1]);

			vertecesRoles["condition"] = v;
			vertecesRoles["then"] = u2;
			vertecesRoles["else"] = u1;
			edgesToRemove += {mFollowers2[v][u2].first(), mFollowers2[v][u1].first()};

			return true;
		}

	}

	return false;
}

/*
bool StructuralControlFlowGenerator::isBlock(const Id &id, Region &region)
{
	int node = mMapIdToVertexLabel[id];
	QVector<int> outgoingList = mFollowers[node];
	if (outgoingList.size() == 1) {
		int next = outgoingList.first();
		if (mPredecessors[next].size() == 1) {
			region["head"] = node;
			region["tail"] = next;
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isIfThenElse(const Id &id, Region &region)
{
	// it is assumed that semantics of id is If
	QPair<LinkInfo, LinkInfo> branches(ifBranchesFor(id));
	qReal::Id thenNode = branches.first.target;
	qReal::Id elseNode = branches.second.target;

	int thenNodeNumber = mMapIdToVertexLabel[thenNode];
	int elseNodeNumber = mMapIdToVertexLabel[elseNode];

	if (mFollowers[thenNodeNumber].size() == 1 && mPredecessors[thenNodeNumber].size() == 1 &&
				mFollowers[elseNodeNumber].size() == 1 && mPredecessors[elseNodeNumber].size() == 1) {

		int v = mFollowers[thenNodeNumber].first();
		int u = mFollowers[elseNodeNumber].first();
		if (v == u) {
			region["guard"] = mMapIdToVertexLabel[id];
			region["then"] = thenNodeNumber;
			region["else"] = elseNodeNumber;
			return true;
		}
	}

	if (mFollowers[thenNodeNumber].size() == 1 && mPredecessors[thenNodeNumber].size() == 1) {
		int v = mFollowers[thenNodeNumber].first();
		if (v == elseNodeNumber) {
			region["guard"] = mMapIdToVertexLabel[id];
			region["then"] = thenNodeNumber;
			return true;
		}
	}

	if (mFollowers[elseNodeNumber].size() == 1 && mPredecessors[elseNodeNumber].size() == 1) {
		int v = mFollowers[elseNodeNumber].first();
		if (v == thenNodeNumber) {
			region["guard"] = mMapIdToVertexLabel[id];
			region["else"] = elseNodeNumber;
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isSwitch(const qReal::Id &id, Region &region)
{
	bool wasTargetSet = false;
	int targetNode = -1;
	int node = mMapIdToVertexLabel[id];
	region["switch"] = node;
	bool isSwitch = true;
	for (const int u : mFollowers[node]) {
		region["case" + QString::number(u)] = u;
		if (mFollowers[u].size() > 1 || mPredecessors[u].size() != 1) {
			isSwitch = false;
		} else if (mFollowers[node].size() == 1) {
			if (!wasTargetSet) {
				wasTargetSet = true;
				targetNode = mFollowers[node].first();
			} else if (mFollowers[node].first() != targetNode) {
				isSwitch = false;
			}
		}
	}

	if (!isSwitch) {
		region.clear();
	}

	return isSwitch;
}

bool StructuralControlFlowGenerator::isSelfLoop(const Id &id, Region &region)
{
	int node = mMapIdToVertexLabel[id];
	if (mFollowers[node].size() == 1) {
		int next = mFollowers[node].first();
		if (next == node) {
			region["selfloop"] = node;
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isWhileLoop(const Id &id, Region &region)
{
	int node = mMapIdToVertexLabel[id];
	if (mFollowers[node].size() == 2) {
		int v = mFollowers[node].at(0);
		int u = mFollowers[node].at(1);

		if (mFollowers[v].size() == 1 && mPredecessors[v].size() == 1
					&& mFollowers[v].first() == node) {
			region["condition"] = node;
			region["body"] = v;
			return true;
		} else if (mFollowers[u].size() == 1 && mPredecessors[u].size() == 1
						&& mFollowers[u].first() == node) {
			region["condition"] = node;
			region["body"] = u;
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isDoWhileLoop(const Id &id, StructuralControlFlowGenerator::Region &region)
{
	int node = mMapIdToVertexLabel[id];
	if (mFollowers[node].size() == 2) {
		int v = mFollowers[node].at(0);
		int u = mFollowers[node].at(1);

		if (mFollowers[v].size() == 1 && mPredecessors[v].size() == 2
					&& mFollowers[v].contains(node)) {
			region["condition"] = node;
			region["body"] = v;
			return true;
		} else if (mFollowers[u].size() == 1 && mPredecessors[u].size() == 2
						&& mFollowers[u].contains(node)) {
			region["condition"] = node;
			region["body"] = u;
			return true;
		}
	}

	return false;
}
*/

void StructuralControlFlowGenerator::initVerteces(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(links)

	if (!mMapVertexLabel.contains(id)) {
		mMapVertexLabel[id] = mVertecesNumber;
		mMapId[mVertecesNumber] = id;
		//mTrees[mVerteces] = mSemanticTree->produceNodeFor(id);
		mVerteces.insert(mVertecesNumber);
		mVertecesNumber++;
	}
}

/*
void StructuralControlFlowGenerator::identifyPatterns(const qReal::Id &id)
{
	bool ok = true;
	while (ok) {
		ok = false;
		Region region;
		if (isBlock(id, region)) {
			reduceBlock(id, region);
			ok = true;
		}
		else if (isIfThenElse(id, region)) {
			reduceIfThenElse(id, region);
			ok = true;
		}
		else if (isSelfLoop(id, region)) {
			reduceSelfLoop(id, region);
			ok = true;
		} else if (isWhileLoop(id, region)) {
			reduceWhileLoop(id, region);
			ok = true;
		}
		else if (isDoWhileLoop(id, region)) {
			reduceDoWhileLoop(id, region);
			ok = true;
		} else {
			int vertexWithBackEdge = mMapIdToVertexLabel[id];
			bool hasCycle = false;


			// the highest node with back edge to head
			int head = -1;
			for (const int u : mFollowers[vertexWithBackEdge]) {
				if (mDominators[vertexWithBackEdge].contains(u)) {
					hasCycle = true;
					if (head == -1 || mDominators[u].contains(head)) {
						head = u;
					}
				}
			}

			if (!hasCycle) {
				break;
			}

			LoopNode *loopNode = dynamic_cast<LoopNode *>(mTrees[head]);
			if (loopNode) {
				break;
			}

			QSet<int> reachUnder = {vertexWithBackEdge, head};
			QQueue<int> q;
			q.push_back(vertexWithBackEdge);
			while (!q.empty()) {
				int vertex = q.front();
				q.pop_front();
				for (const int u : mPredecessors[vertex]) {
					if (!reachUnder.contains(u) && mDominators[u].contains(head)) {
						reachUnder.insert(u);
						q.push_back(u);
					}
				}
			}

			int cnt = 0;
			ok = true;
			int breakVertex = -1;
			for (const int u : reachUnder) {
				for (const int z : mFollowers[u]) {
					if (!reachUnder.contains(z) && breakVertex == -1) {
						breakVertex = z;
						cnt++;
					} else if (!reachUnder.contains(z) && breakVertex != z) {
						ok = false;
					} else if (!reachUnder.contains(z)) {
						cnt++;
					}
				}
			}

			if (!ok || cnt == 1) {
				break;
			}

			if (breakVertex == -1) {
				break;
			}

			for (const int u : reachUnder) {
				for (const int z : mFollowers[u]) {
					if (!reachUnder.contains(z)) {
						SemanticNode *node = mTrees[u];
						SemanticNode *externalNode = mTrees[z];
						qReal::Id ifId = node->lastIfId();
						qReal::Id externalId = externalNode->firstId();
						QPair<LinkInfo, LinkInfo> p = ifBranchesFor(ifId);
						SimpleNode *breakNode = new SimpleNode(qReal::Id(), node);
						breakNode->bindToSyntheticConstruction(SimpleNode::SyntheticBlockType::breakNode);
						if (p.first.target == externalId) {
							node->makeBreakForLastIf(true, breakNode);
						} else {
							node->makeBreakForLastIf(false, breakNode);
						}
						node->setHasBreakInside(true);
					}
				}
			}

			// we can safely remove excess edges
			QMap<int, QVector<int> > oldFollowers = mFollowers;
			for (const int u : reachUnder) {
				for (const int z : oldFollowers[u]) {
					if (!reachUnder.contains(z)) {
						mFollowers[u].removeAll(z);
						mPredecessors[z].removeAll(u);
					}
				}
			}

			// adding edge from head
			mFollowers[head].push_back(breakVertex);
			mPredecessors[breakVertex].push_back(head);
			mTrees[head]->setHasBreakInside(true);
		}

	}
}
*/

void StructuralControlFlowGenerator::buildGraph()
{
	for (int v : mVerteces) {
		const qReal::Id vId = mMapId[v];

		for (const qReal::Id link : mRepo.outgoingLinks(vId)) {
			const QString text = mRepo.property(link, "Guard").toString();
			Link edge(text);

			if (mCustomizer.semanticsOf(vId) == enums::semantics::conditionalBlock) {
				edge.mFromIf = true;
			} else if (mCustomizer.semanticsOf(vId) == enums::semantics::switchBlock) {
				edge.mFromSwitch = true;
			}

			const int u = mMapVertexLabel[mRepo.otherEntityFromLink(link, vId)];

			mFollowers2[v][u].push_back(mEdgesNumber);
			mEdges[mEdgesNumber] = edge;
			mEdgesNumber++;
		}

		for (const qReal::Id link : mRepo.incomingLinks(vId)) {
			const QString text = mRepo.property(link, "Guard").toString();
			Link edge(text);
			const qReal::Id uId = mRepo.otherEntityFromLink(link, vId);
			if (mCustomizer.semanticsOf(uId) == enums::semantics::switchBlock) {
				edge.mFromSwitch = true;
			} else if (mCustomizer.semanticsOf(uId) == enums::semantics::conditionalBlock) {
				edge.mFromIf = true;
			}

			const int u = mMapVertexLabel[uId];
			mPredecessors2[v][u].push_back(mEdgesNumber);
			mEdges[mEdgesNumber] = edge;
			mEdgesNumber++;
		}
	}
}

void StructuralControlFlowGenerator::findDominators()
{
	mDominators[mStartVertex] = { mStartVertex };
	bool somethingChanged = true;

	while (somethingChanged) {
		somethingChanged = false;

		for (const int v : mVerteces) {
			if (v == mStartVertex)
				continue;

			QSet<int> doms = mVerteces;
			QList<int> predecessors = mPredecessors2[v].keys();

			for (const int u : predecessors) {
				doms = doms.intersect(mDominators[u]);
			}
			doms.insert(v);
			if (doms != mDominators[v]) {
				mDominators[v] = doms;
				somethingChanged = true;
			}
		}
	}
}

void StructuralControlFlowGenerator::createInitialSemanticNodes()
{
	for (const int u : mVerteces) {
		if (numberOfOutgoingEdges(u) <= 1) {
			mTrees[u] = mSemanticTree->produceNodeFor(mMapId[u]);
		}
	}
}

void StructuralControlFlowGenerator::findStartVertex()
{
	for (int v : mFollowers2.keys()) {
		if (!mPredecessors2[v].size()) {
			mStartVertex = v;
			break;
		}
	}
}

void StructuralControlFlowGenerator::dfs(int v, int &currentTime)
{
	mUsed[v] = true;
	for (const int u : mFollowers2[v].keys().toSet()) {
		if (!mUsed[u]) {
			dfs(u, currentTime);
		}
	}
	mPostOrder[v] = currentTime++;
}

int StructuralControlFlowGenerator::numberOfOutgoingEdges(int v)
{
	int ans = 0;
	for (int u : mFollowers2[v].keys()) {
		ans += mFollowers2[v][u].size();
	}

	return ans;
}

int StructuralControlFlowGenerator::numberOfIncomingEdges(int v)
{
	int ans = 0;
	for (int u : mPredecessors2[v].keys()) {
		ans += mPredecessors2[v][u].size();
	}

	return ans;
}

void StructuralControlFlowGenerator::replace(int newNodeNumber, QSet<int> &edgesToRemove, QSet<int> &verteces)
{
	updateEdges(newNodeNumber, edgesToRemove, verteces);
	updatePostOrder(newNodeNumber, verteces);
	updateDominators(newNodeNumber, verteces);
	updateVerteces(newNodeNumber, verteces);
}

void StructuralControlFlowGenerator::updateEdges(int newNodeNumber, QSet<int> &edgesToRemove, QSet<int> &verteces)
{
	QMap<int, QMap<int, QVector<int>>> followers = mFollowers2;

	for (int v : mVerteces) {
		for (int u : followers[v].keys()) {
			for (int edge : followers[v][u]) {
				if (edgesToRemove.contains(edge)) {
					//mFollowers2[v][u].remove(edge);
					//mPredecessors2[u][v].remove(edge);
					continue;
				}
				int newV = v;
				int newU = u;

				if (verteces.contains(v)) {
					newV = newNodeNumber;
				}

				if (verteces.contains(u)) {
					newU = newNodeNumber;
				}

				if (newU == newNodeNumber || newV == newNodeNumber) {
					if (!mEdges[edge].mLinkName.isEmpty() || !containsEdgeWithoutGuard(newV, newU)) {
						mFollowers2[newV][newU].push_back(edge);
						mPredecessors2[newU][newV].push_back(edge);
					}
				}

			}
		}
	}

	// removing old information
	for (int v : verteces) {
		mFollowers2.remove(v);
		mPredecessors2.remove(v);
	}

	// removing information from actual verteces to old ones
	for (int v : mVerteces) {
		if (verteces.contains(v))
			continue;

		for (int u : verteces) {
			mFollowers2[v].remove(u);
			mPredecessors2[v].remove(u);
		}
	}
}

void StructuralControlFlowGenerator::updatePostOrder(int newNodeNumber, QSet<int> &verteces)
{
	int minimum = -1;
	for (int v : verteces) {
		if (minimum == -1 || minimum > mPostOrder[v]) {
			minimum = mPostOrder[v];
		}
	}

	mPostOrder[newNodeNumber] = minimum;

	for (int v : verteces) {
		mPostOrder.remove(v);
	}

	int offset = verteces.size() - 1;
	for (int v : mPostOrder.keys()) {
		if (mPostOrder[v] > minimum) {
			mPostOrder[v] -= offset;
		}
	}

	mMaxPostOrderTime -= offset;
}

void StructuralControlFlowGenerator::updateDominators(int newNodeNumber, QSet<int> &verteces)
{
	// others
	for (int v : mPostOrder.keys()) {
		if (mDominators[v].intersects(verteces)) {
			mDominators[v].subtract(verteces);
			mDominators[v].insert(newNodeNumber);
		}
	}

	// new
	QSet<int> doms = mVerteces;
	for (int v : verteces) {
		doms.intersect(mDominators[v]);
	}

	mDominators[newNodeNumber] = doms;

	// old
	for (int v : verteces) {
		mDominators.remove(v);
	}
}

void StructuralControlFlowGenerator::updateVerteces(int newNodeNumber, QSet<int> &verteces)
{
	if (mVerteces.contains(mStartVertex)) {
		mStartVertex = newNodeNumber;
	}

	for (int u : verteces) {
		mVerteces.remove(u);
	}

	mVerteces.insert(newNodeNumber);
}

bool StructuralControlFlowGenerator::containsEdgeWithoutGuard(int v, int u)
{
	for (int edge : mFollowers2[v][u]) {
		if (mEdges[edge].mLinkName.isEmpty()) {
			return true;
		}
	}

	return false;
}

void StructuralControlFlowGenerator::reduceBlock(QSet<int> &edgesToRemove, QMap<QString, int> &vertecesRoles)
{
	// it is supposed that v, u are Actions
	int v = vertecesRoles["block1"];
	int u = vertecesRoles["block2"];
	SemanticNode *block1 = mTrees[v];
	SemanticNode *block2 = mTrees[u];

	ZoneNode *block = new ZoneNode(block1->parent());
	block->appendChild(block1);
	block->appendChild(block2);

	mTrees[mVertecesNumber] = block;
	mVerteces.insert(mVertecesNumber);

	QSet<int> verteces = vertecesRoles.values().toSet();
	replace(mVertecesNumber, edgesToRemove, verteces);
	mVertecesNumber++;
}

QString StructuralControlFlowGenerator::getCondition(const Id &id, const QString &edgeText)
{
	if (semanticsOf(id) == enums::semantics::conditionalBlock) {
		QString condition = mRepo.property(id, "Condition").toString();
		if (edgeText == "false") {
			condition = "!(" + condition + ")";
		}
		return condition;
	}

	if (semanticsOf(id) == enums::semantics::switchBlock) {
		QString expression = mRepo.property(id, "Expression").toString();
		return expression + " == " + edgeText;
	}

	return "";
}

int StructuralControlFlowGenerator::getTrueLink(int v)
{
	for (int u : mFollowers2[v].keys()) {
		for (int edge : mFollowers2[v][u]) {
			if (mEdges[edge].mLinkName == "true" || mEdges[edge].mLinkName != "false") {
				return edge;
			}
		}
	}
}

StructuralControlFlowGenerator::Link::Link()
	: mLinkName("")
	, mFromSwitch(false)
	, mFromIf(false)
{
}

StructuralControlFlowGenerator::Link::Link(const QString &text)
	: Link()
{
	mLinkName = text;
}
