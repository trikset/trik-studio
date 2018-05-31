#include "structurizator.h"

#include <QQueue>

using namespace generatorBase;
using namespace myUtils;

Structurizator::Structurizator(QObject *parent)
	: QObject(parent)
	, mVertecesNumber(1)
	, mStartVertex(-1)
	, mMaxPostOrderTime(-1)
{
}

IntermediateNode *Structurizator::performStructurization(const qrRepo::RepoApi *repo, const QSet<qReal::Id> &vertecesIds)
{
	setRepo(repo);
	setVerteces(vertecesIds);

	// constructing graph
	createGraph();

	findStartVertex();

	// post order
	calculatePostOrder();

	calculateDominators();

	createInitialNodesForIds();

	bool somethingChanged = true;
	while (somethingChanged) {
		somethingChanged = false;

		int t = 0;
		while (t <= mMaxPostOrderTime && mVertices.size() > 1) {

			if (!checkAllStructures()) {
				bool flag = checkAllStructures();
			}
			Q_ASSERT(checkAllStructures());
			int v = mPostOrder.key(t);
			if (!v) {
				qDebug() << "Problem! time = " << t;
			}

			QSet<int> reachUnder;
			QSet<QPair<int, int> > edgesToRemove = {};
			QMap<QString, int> verticesRoles;
			if (isBlock(v, edgesToRemove, verticesRoles)) {
				reduceBlock(edgesToRemove, verticesRoles);
				qDebug() << "Block";
			} else if (isSwitch(v, edgesToRemove, verticesRoles)) {
				reduceSwitch(edgesToRemove, verticesRoles);
				qDebug() << "Switch";
			} else if (isIfThenElse(v, edgesToRemove, verticesRoles)) {
				reduceIfThenElse(edgesToRemove, verticesRoles);
				qDebug() << "If then else";
			} else if (isIfThen(v, edgesToRemove, verticesRoles)) {
				reduceIfThen(edgesToRemove, verticesRoles);
				qDebug() << "If then";
			} else if (isInfiniteLoop(v, edgesToRemove, verticesRoles)) {
				reduceInfiniteLoop(edgesToRemove, verticesRoles);
				qDebug() << "Infinite loop";
			} else if (isWhileLoop(v, edgesToRemove, verticesRoles)) {
				reduceWhileLoop(edgesToRemove, verticesRoles);
				qDebug() << "While loop";

			} else if (isHeadOfCycle(v, reachUnder)) {

				int minTime = -1;
				for (const int vertex : reachUnder) {
					if (minTime == -1 || minTime > mPostOrder[vertex]) {
						minTime = mPostOrder[vertex];
					}
				}

				QMap<int, QSet<int> > nodesWithExits;
				int commonExit = -1;
				bool isCycle = isCycleWithBreaks(reachUnder, nodesWithExits, commonExit);
				if (!isCycle) {
					t++;
					continue;
				}

				qDebug() << "Cycle with breaks";
				reduceConditionsWithBreaks(v, nodesWithExits, commonExit);
				t = minTime;
				somethingChanged = true;
				continue;
			}

			if (verticesRoles.size()) {
				t -= (verticesRoles.size() - 1);
				if (t < 0) {
					t = 0;
				}
				somethingChanged = true;
			} else {
				t++;
			}
		}
	}

	if (mVertices.size() == 1) {
		qDebug() << "Structured!";
		qDebug() << " ";
		return mTrees[mStartVertex];
	}

	return nullptr;
}

void Structurizator::setRepo(const qrRepo::RepoApi *repo)
{
	mRepo = repo;
}

void Structurizator::setVerteces(const QSet<qReal::Id> &vertecesIds)
{
	mVertices.clear();
	mMapIdToInt.clear();
	mVertecesNumber = 1;
	mInitialIds.clear();

	for (const qReal::Id &id : vertecesIds) {
		mInitialIds.insert(id);
		mMapIdToInt[id] = mVertecesNumber;
		mVertices.insert(mVertecesNumber);
		mVertecesNumber++;
	}
}

bool Structurizator::isBlock(int v, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	if (outgoingEdgesNumber(v) != 1) {
		return false;
	}

	int u = mFollowers[v].first();
	if (outgoingEdgesNumber(u) <= 1 && incomingEdgesNumber(u) == 1) {
		verticesRoles["block1"] = v;
		verticesRoles["block2"] = u;

		edgesToRemove.insert(makePair(v, u));
		return true;
	}

	return false;
}

bool Structurizator::isIfThenElse(int v, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	if (outgoingEdgesNumber(v) != 2) {
		return false;
	}

	int u1 = mFollowers[v].first();
	int u2 = mFollowers[v].last();
	if (incomingEdgesNumber(u1) != 1 || incomingEdgesNumber(u2) != 1) {
		return false;
	}

	if ((outgoingEdgesNumber(u1) == 0 && outgoingEdgesNumber(u2) == 0) ||
				(outgoingEdgesNumber(u1) == 1 && outgoingEdgesNumber(u2) == 1 &&
				mFollowers[u1].first() == mFollowers[u2].first())) {

		verticesRoles["condition"] = v;
		verticesRoles["then"] = u1;
		verticesRoles["else"] = u2;
		edgesToRemove += { makePair(v, u1), makePair(v, u2) };
		return true;
	}

	return false;
}

bool Structurizator::isIfThen(int v, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	if (outgoingEdgesNumber(v) != 2) {
		return false;
	}

	int u1 = mFollowers[v].first();
	int u2 = mFollowers[v].last();

	int thenNumber = -1;
	int elseNumber = -1;
	if (checkIfThenHelper(u1, u2)) {
		thenNumber = u1;
		elseNumber = u2;
	} else if (checkIfThenHelper(u2, u1)) {
		thenNumber = u2;
		elseNumber = u1;
	}

	if (thenNumber == -1 || elseNumber == v) {
		return false;
	}

	verticesRoles["condition"] = v;
	verticesRoles["then"] = thenNumber;

	edgesToRemove = { makePair(v, u1), makePair(v, u2) };

	return true;
}

bool Structurizator::isSwitch(int v, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	if (mFollowers[v].size() < 3) {
		return false;
	}

	int exit = -1;
	QSet<int> vertices = {};
	QSet<QPair<int, int> > edges = {};
	for (const int u : mFollowers[v]) {
		if (incomingEdgesNumber(u) != 1 || outgoingEdgesNumber(u) >= 2) {
			return false;
		}

		if (outgoingEdgesNumber(u) == 1) {
			int m = mFollowers[u].first();
			if (exit == -1) {
				exit = m;
				if (exit == v) {
					return false;
				}
			} else if (m != exit) {
				return false;
			}
		}

		vertices.insert(u);
		edges.insert(makePair(v, u));
	}

	verticesRoles["head"] = v;
	edgesToRemove = edges;

	int cnt = 1;
	for (int u : vertices) {
		verticesRoles[QString::number(cnt)] = u;
		cnt++;
	}

	return true;
}

bool Structurizator::isInfiniteLoop(int v, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	if (outgoingEdgesNumber(v) != 1) {
		return false;
	}

	int u = mFollowers[v].first();
	if (u != v) {
		return false;
	}

	verticesRoles["body"] = v;
	edgesToRemove.insert(makePair(v, v));
	return true;
}

bool Structurizator::isWhileLoop(int v, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	if (outgoingEdgesNumber(v) != 2) {
		return false;
	}

	int u1 = mFollowers[v].first();
	int u2 = mFollowers[v].last();

	int bodyNumber = -1;
	if (checkWhileLoopHelper(v, u1)) {
		bodyNumber = u1;
	} else if (checkWhileLoopHelper(v, u2)) {
		bodyNumber = u2;
	}

	if (bodyNumber == -1) {
		return false;
	}

	edgesToRemove = { makePair(v, bodyNumber), makePair(bodyNumber, v) };

	verticesRoles["head"] = v;
	verticesRoles["body"] = bodyNumber;

	return true;
}

bool Structurizator::checkIfThenHelper(int thenNumber, int exitNumber)
{
	if (incomingEdgesNumber(thenNumber) == 1 && outgoingEdgesNumber(thenNumber) == 1) {
		if (mFollowers[thenNumber].contains(exitNumber)) {
			return true;
		}
	}

	return false;
}

bool Structurizator::checkWhileLoopHelper(int head, int body)
{
	if (incomingEdgesNumber(body) == 1 && outgoingEdgesNumber(body) == 1) {
		int w = mFollowers[body].first();
		if (w == head) {
			return true;
		}
	}

	return false;
}

bool Structurizator::isCycleWithBreaks(QSet<int> &reachUnder, QMap<int, QSet<int> > &nodesWithExits, int &commonExit)
{
	bool result = findCommonExit(reachUnder, nodesWithExits, commonExit);
	if (!result) {
		return false;
	}

	return checkCommonExitUniqueness(commonExit, nodesWithExits);
}

bool Structurizator::isHeadOfCycle(int v, QSet<int> &reachUnder)
{
	QQueue<int> queueForReachUnder;

	for (const int u : mPredecessors[v]) {
		if (mDominators[u].contains(v)) {
			queueForReachUnder.push_back(u);
		}
	}

	while (!queueForReachUnder.empty()) {
		int u = queueForReachUnder.front();
		queueForReachUnder.pop_front();
		reachUnder.insert(u);
		for (const int w : mPredecessors[u]) {
			if (mDominators[w].contains(v) && !reachUnder.contains(w)) {
				queueForReachUnder.push_back(w);
			}
		}
	}

	return !reachUnder.isEmpty();
}

bool Structurizator::findCommonExit(QSet<int> &reachUnder, QMap<int, QSet<int> > &nodesWithExits, int &commonExit)
{
	commonExit = -1;
	QSet<int> exits;

	for (const int u : reachUnder) {
		for (const int w : mFollowers[u]) {
			if (!reachUnder.contains(w)) {
				if (exits.contains(w) || incomingEdgesNumber(w) > 1) {
					if (commonExit != -1 && commonExit != w) {
						return false;
					}
					commonExit = w;
				}

				exits.insert(w);
				nodesWithExits[u].insert(w);
			}
		}
	}

	if (commonExit != -1) {
		return true;
	}

	QList<int> regionToFindCommonChild;
	for (const int exitNumber : exits) {
		if (outgoingEdgesNumber(exitNumber) == 1) {
			regionToFindCommonChild.append(exitNumber);
		} else if (outgoingEdgesNumber(exitNumber) > 1) {
			if (commonExit == -1) {
				// we have found post-cycle execution point
				commonExit = exitNumber;
			} else if (commonExit != exitNumber) {
				// each cycle can have at most 1 point to transfer execution
				return false;
			}
		}
	}

	if (commonExit != -1) {
		return true;
	}

	// assume that one exit point is commonChild
	if (regionToFindCommonChild.size() == 1) {
		commonExit = regionToFindCommonChild.first();
		return true;
	}

	for (const int exitNumber : regionToFindCommonChild) {
		for (const int postExit : mFollowers[exitNumber]) {
			if (commonExit == -1) {
				commonExit = postExit;
			} else if (commonExit != postExit) {
				return false;
			}
		}
	}

	return true;
}

bool Structurizator::checkCommonExitUniqueness(int commonExit, const QMap<int, QSet<int> > &nodesWithExits)
{
	for (const int vertexFromCycle : nodesWithExits.keys()) {
		for (const int exit : nodesWithExits[vertexFromCycle]) {
			if (commonExit == exit) {
				continue;
			}

			if (incomingEdgesNumber(exit) != 1 || outgoingEdgesNumber(exit) >= 2) {
				return false;
			}

			if (outgoingEdgesNumber(exit) == 1 && commonExit != mFollowers[exit].first()) {
				return false;
			}
		}
	}

	return true;
}

void Structurizator::reduceBlock(QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	BlockNode *block = new BlockNode(mTrees[verticesRoles["block1"]], mTrees[verticesRoles["block2"]], this);

	replace(appendVertex(block), edgesToRemove, verticesRoles);
}

void Structurizator::reduceIfThenElse(QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	IfNode *ifNode = new IfNode(mTrees[verticesRoles["condition"]], mTrees[verticesRoles["then"]], mTrees[verticesRoles["else"]], this);

	replace(appendVertex(ifNode), edgesToRemove, verticesRoles);
}

void Structurizator::reduceIfThen(QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	IfNode *ifNode = new IfNode(mTrees[verticesRoles["condition"]], mTrees[verticesRoles["then"]], nullptr, this);

	replace(appendVertex(ifNode), edgesToRemove, verticesRoles);
}

void Structurizator::reduceSwitch(QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	int v = verticesRoles["head"];
	QSet<int> otherVerteces = verticesRoles.values().toSet();
	otherVerteces.remove(v);

	QList<IntermediateNode *> branches;
	for (const int u : otherVerteces) {
		branches.append(mTrees[u]);
	}

	SwitchNode *switchNode = new SwitchNode(mTrees[v], branches);

	replace(appendVertex(switchNode), edgesToRemove, verticesRoles);
}

void Structurizator::reduceInfiniteLoop(QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	SelfLoopNode *loopNode = new SelfLoopNode(mTrees[verticesRoles["body"]], this);

	replace(appendVertex(loopNode), edgesToRemove, verticesRoles);
}

void Structurizator::reduceWhileLoop(QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	WhileNode *whileNode = new WhileNode(mTrees[verticesRoles["head"]], mTrees[verticesRoles["body"]], this);

	replace(appendVertex(whileNode), edgesToRemove, verticesRoles);
}

void Structurizator::reduceConditionsWithBreaks(int v, QMap<int, QSet<int> > &nodesWithExits, int commonExit)
{
	if (nodesWithExits.contains(v)) {
		FakeCycleHeadNode *fakeCycleHeadNode = new FakeCycleHeadNode(mTrees[v]->firstId(), this);
		int newNodeNumber = appendVertex(fakeCycleHeadNode);
		addNewNodeNumberBeforeVertex(newNodeNumber, v);
		v = newNodeNumber;
	}

	for (const int u : nodesWithExits.keys()) {
		QList<IntermediateNode *> exitBranches;
		QSet<QPair<int, int> > edgesToRemove;
		QSet<int> vertices = {u};

		for (const int exit : nodesWithExits[u]) {
			qReal::Id id = mTrees[exit]->firstId();
			IntermediateNode *node;
			if (exit == commonExit) {
				node = new BreakNode(id, this);
			} else {
				node = new BlockNode(mTrees[exit], new BreakNode(id, this), this);

				vertices.insert(exit);

				if (mFollowers[exit].contains(commonExit)) {
					edgesToRemove.insert(makePair(exit, commonExit));
				}
			}
			edgesToRemove.insert(makePair(u, exit));
			exitBranches.append(node);
		}

		NodeWithBreaks *nodeWithBreaks = new NodeWithBreaks(mTrees[u], exitBranches, this);
		replace(appendVertex(nodeWithBreaks), edgesToRemove, vertices);
	}

	// adding edge from head to common exit
	if (commonExit != -1 && !mFollowers[v].contains(commonExit)) {
		mFollowers[v].push_back(commonExit);
		mPredecessors[commonExit].push_back(v);
	}
}

void Structurizator::replace(int newNodeNumber, QSet<QPair<int, int> > &edgesToRemove, QSet<int> &vertices)
{
	updateEdges(newNodeNumber, edgesToRemove, vertices);
	updatePostOrder(newNodeNumber, vertices);
	updateDominators(newNodeNumber, vertices);
	updateVertices(newNodeNumber, vertices);
}

void Structurizator::replace(int newNodeNumber, QSet<QPair<int, int> > &edgesToRemove, QMap<QString, int> &verticesRoles)
{
	QSet<int> vertices = verticesRoles.values().toSet();
	replace(newNodeNumber, edgesToRemove, vertices);
}

void Structurizator::updateEdges(int newNodeNumber, QSet<QPair<int, int> > &edgesToRemove, QSet<int> &vertices)
{
	for (const QPair<int, int> p : edgesToRemove) {
		mFollowers[p.first].removeAll(p.second);
		mPredecessors[p.second].removeAll(p.first);
	}

	// this code cab be optimized.
	const QMap<int, QVector<int> > followers = mFollowers;
	for (const int v : mVertices) {
		for (const int u : followers[v]) {

			int newV = vertices.contains(v) ? newNodeNumber : v;
			int newU = vertices.contains(u) ? newNodeNumber : u;

			if (newU == newNodeNumber || newV == newNodeNumber) {
				// removing old information
				mFollowers[v].removeAll(u);
				mPredecessors[u].removeAll(v);

				// inserting new information
				if (!mFollowers[newV].contains(newU)) {
					mFollowers[newV].push_back(newU);
					mPredecessors[newU].push_back(newV);
				}
			}
		}
	}

	for (const int v : vertices) {
		mFollowers.remove(v);
		mPredecessors.remove(v);
	}
}

void Structurizator::updatePostOrder(int newNodeNumber, QSet<int> &verteces)
{
	int maximum = -1;
	for (int v : verteces) {
		if (maximum == -1 || maximum < mPostOrder[v]) {
			maximum = mPostOrder[v];
		}
	}

	mPostOrder[newNodeNumber] = maximum;

	for (int v : verteces) {
		mPostOrder.remove(v);
	}

	mMaxPostOrderTime = mMaxPostOrderTime - verteces.size() + 1;

	QVector<int> times = mPostOrder.values().toVector();
	std::sort(times.begin(), times.end());

	for (int i = 0; i <= mMaxPostOrderTime; i++) {
		int v = mPostOrder.key(times[i]);
		mPostOrder[v] = i;
	}
}

void Structurizator::updateDominators(int newNodeNumber, QSet<int> &verteces)
{
	// others
	for (int v : mPostOrder.keys()) {
		if (mDominators[v].intersects(verteces)) {
			mDominators[v].subtract(verteces);
			mDominators[v].insert(newNodeNumber);
		}
	}

	// new
	QSet<int> doms = mVertices;
	for (int v : verteces) {
		doms.intersect(mDominators[v]);
	}

	doms.subtract(verteces);
	doms.insert(newNodeNumber);

	mDominators[newNodeNumber] = doms;

	// old
	for (int v : verteces) {
		mDominators.remove(v);
	}
}

void Structurizator::updateVertices(int newNodeNumber, QSet<int> &vertices)
{
	mStartVertex = vertices.contains(mStartVertex) ? newNodeNumber : mStartVertex;
	mVertices.subtract(vertices);
	mVertices.insert(newNodeNumber);
}

void Structurizator::addNewNodeNumberBeforeVertex(int newNodeNumber, int vertex)
{
	QMap<VertexNumber, QVector<VertexNumber> > predecessors = mPredecessors;
	for (const int u : predecessors[vertex]) {
		mFollowers[u].removeAll(vertex);
		mPredecessors[vertex].removeAll(u);

		mFollowers[u].push_back(newNodeNumber);
		mPredecessors[newNodeNumber].push_back(u);
	}

	mFollowers[newNodeNumber].push_back(vertex);
	mPredecessors[vertex].push_back(newNodeNumber);


	// dominators
	mDominators[newNodeNumber] = mDominators[vertex];
	mDominators[newNodeNumber].subtract({vertex});
	for (const int u : mVertices) {
		if (mDominators[u].contains(vertex)) {
			mDominators[u].insert(newNodeNumber);
		}
	}

	calculatePostOrder();
}

void Structurizator::removeVertex(int vertex)
{
	for (const int u : mFollowers[vertex]) {
		mPredecessors[u].removeAll(vertex);
	}

	for (const int u : mPredecessors[vertex]) {
		mFollowers[u].removeAll(vertex);
	}

	mPredecessors.remove(vertex);
	mFollowers.remove(vertex);

	mDominators.remove(vertex);
	mVertices.remove(vertex);
}

void Structurizator::createGraph()
{
	for (const qReal::Id &vertex : mInitialIds) {
		for (const qReal::Id &link : mRepo->outgoingLinks(vertex)) {
			int v = mMapIdToInt[vertex];
			int u = mMapIdToInt[mRepo->otherEntityFromLink(link, vertex)];

			if (!mFollowers[v].contains(u)) {
				mFollowers[v].push_back(u);
				mPredecessors[u].push_back(v);
			}
		}
	}
}

void Structurizator::calculateDominators()
{
	for (const int u : mVertices) {
		mDominators[u] = mVertices;
	}

	mDominators[mStartVertex] = { mStartVertex };

	bool somethingChanged = true;
	while (somethingChanged) {
		somethingChanged = false;

		for (const int v : mVertices) {
			if (v == mStartVertex)
				continue;

			QSet<int> doms = mVertices;
			for (const int u : mPredecessors[v]) {
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

void Structurizator::findStartVertex()
{
	for (const int u : mVertices) {
		if (mPredecessors[u].isEmpty()) {
			mStartVertex = u;
			return;
		}
	}
}

void Structurizator::calculatePostOrder()
{
	mPostOrder.clear();

	QMap<int, bool> used;
	for (const int v : mVertices) {
		used[v] = false;
	}

	int currentTime = 0;
	dfs(mStartVertex, currentTime, used);

	mMaxPostOrderTime = currentTime - 1;
}

void Structurizator::createInitialNodesForIds()
{
	for (const int v : mVertices) {
		mTrees[v] = new SimpleNode(mMapIdToInt.key(v), this);
	}
}

void Structurizator::dfs(int v, int &currentTime, QMap<int, bool> &used)
{
	used[v] = true;
	for (const int u : mFollowers[v]) {
		if (!used[u]) {
			dfs(u, currentTime, used);
		}
	}

	mPostOrder[v] = currentTime;
	currentTime++;
}

int Structurizator::appendVertex(IntermediateNode *node)
{
	mTrees[mVertecesNumber] = node;
	mVertices.insert(mVertecesNumber);
	mVertecesNumber++;
	return mVertecesNumber - 1;
}

int Structurizator::outgoingEdgesNumber(int v) const
{
	return mFollowers[v].size();
}

int Structurizator::incomingEdgesNumber(int v) const
{
	return mPredecessors[v].size();
}

QPair<int, int> Structurizator::makePair(int a, int b)
{
	return QPair<int, int>(a, b);
}

bool Structurizator::checkAllStructures()
{
	return checkFollowers() && checkPostOrder() && checkDominators();
}

bool Structurizator::checkFollowers()
{
	QSet<int> followersKeys = mFollowers.keys().toSet();
	followersKeys = followersKeys.subtract(mVertices);
	if (!followersKeys.isEmpty()) {
		return false;
	}

	QSet<int> predecessorsKeys = mPredecessors.keys().toSet();
	predecessorsKeys = predecessorsKeys.subtract(mVertices);
	if (!predecessorsKeys.isEmpty()) {
		return false;
	}

	for (const int v : mVertices) {
		for (const int u : mFollowers[v]) {
			if (!mVertices.contains(u)) {
				return false;
			}
		}
	}

	for (const int v : mVertices) {
		for (const int u : mPredecessors[v]) {
			if (!mVertices.contains(u)) {
				return false;
			}
		}
	}

	return true;
}

bool Structurizator::checkDominators()
{
	QSet<int> dominators = mDominators.keys().toSet();
	dominators = dominators.subtract(mVertices);
	if (!dominators.isEmpty()) {
		return false;
	}

	QSet<int> verteces = mVertices;
	verteces = verteces.subtract(mDominators.keys().toSet());
	if (!verteces.isEmpty()) {
		return false;
	}

	for (const int v : mVertices) {
		for (const int u : mDominators[v]) {
			if (!mVertices.contains(u)) {
				return false;
			}
		}
	}

	return true;
}

bool Structurizator::checkPostOrder()
{
	QVector<bool> times(mMaxPostOrderTime + 1);
	for (Time i = 0; i <= mMaxPostOrderTime; i++) {
		times[i] = false;
	}

	for (const int u : mVertices) {
		times[mPostOrder[u]] = true;
	}

	for (Time i = 0; i <= mMaxPostOrderTime; i++) {
		if (!times[i]) {
			return false;
		}
	}

	return true;
}
