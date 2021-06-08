#include "structurizer.h"

#include <QtCore/QQueue>

#include "structurizerNodes/structurizerNode.h"
#include "structurizerNodes/simpleStructurizerNode.h"
#include "structurizerNodes/continuationStructurizerNode.h"
#include "structurizerNodes/sequenceStructurizerNode.h"
#include "structurizerNodes/ifStructurizerNode.h"
#include "structurizerNodes/loopStructurizerNode.h"
#include "structurizerNodes/switchStructurizerNode.h"

using namespace generatorBase;

Structurizer::Structurizer(QObject *parent)
	: QObject(parent)
{
}

StructurizerNode *Structurizer::performStructurization(const QSet<qReal::Id> &verticesIds
		, qReal::Id startVertex
		, const QMap<Vertex, QList<Vertex>> &followers)
{
	mStartVertex = startVertex;

	for (const Vertex &v : verticesIds) {
		mVertices.insert(v);
	}

	for (const Vertex &v : mVertices) {
		for (const Vertex &u : followers[v]) {
			mFollowers[v].append(u);
			mPredecessors[u].append(v);
		}
	}

	for (const Vertex &id : mVertices) {
		if (mFollowers[id].size() == 0) {
			mExits.insert(id);
		}
	}

	QMap<Vertex, int> color;
	int time = 0;
	for (const Vertex &v : verticesIds) {
		color[v] = 0;
	}
	dfs(startVertex, time, color);

	QVector<QPair<Vertex, int>> vertices = {};
	for (const Vertex &v : verticesIds) {
		vertices.append(qMakePair(v, mTopologicalOrder[v]));
	}
	qSort(vertices.begin(), vertices.end(),
		[](const QPair<Vertex, int> &l, const QPair<Vertex, int> &r) {
				return l.second < r.second;
	});

	QVector<Vertex> orderOfResolution;
	for (const QPair<Vertex, int> &e : vertices) {
		orderOfResolution.append(e.first);
	}

	reorderLoopHeads(orderOfResolution);

	QMap<Vertex, StructurizerNode *> system = {};

	//system creating
	for (const Vertex &id : orderOfResolution) {
		SequenceStructurizerNode *var = new SequenceStructurizerNode(this);
		if (mFollowers[id].size() <= 1) {
			var->addToTheEnd(new SimpleStructurizerNode(id, this));
			if (mFollowers[id].size() == 1) {
				var->addToTheEnd(new ContinuationStructurizerNode(mFollowers[id].first(), this));
			}
		} else if (mFollowers[id].size() == 2) {
			var->addToTheEnd(new IfStructurizerNode(id, mFollowers[id].first(), mFollowers[id].last(), this));
		} else if (mFollowers[id].size() > 2) {
			var->addToTheEnd(new SwitchStructurizerNode(id, mFollowers[id], this));
		}
		system[id] = var;
	}

	//system solving
	for (int i = 0; i < orderOfResolution.size(); ++i) {
		Vertex v = orderOfResolution[i];

		//if recursive
		if (system[v]->containsContinuation(v)) {
			system[v]->derecursivate(v);
		}

		//elimination
		for (int j = 0; j < orderOfResolution.size(); ++j) {
			if (i == j) {
				continue;
			}
			system[orderOfResolution[j]]->mergeConditionalBranches(mExits, mLoopHeads);

			system[orderOfResolution[j]]->factorize(v);
			system[orderOfResolution[j]]->replaceContinuation(v, system[v]);
		}
	}

	return system[mStartVertex];
}

void Structurizer::dfs(Vertex v, int &currentTime, QMap<Vertex, int> &color)
{
	color[v] = 1;
	for (const Vertex &u : mFollowers[v]) {
		if (color[u] == 0) {
			dfs(u, currentTime, color);
		} else if (color[u] == 1) {
			mCyclicEdges.append(qMakePair(v, u));
		}
	}
	mTopologicalOrder[v] = currentTime--;
	color[v] = 2;
}

void Structurizer::reorderLoopHeads(QVector<Vertex> &vertexOrder)
{
	QMap<Vertex, QSet<Vertex>> loopBody = {};
	for (auto &edge : mCyclicEdges) {
		QQueue<QVector<Vertex>> queue;
		queue.enqueue({edge.first, edge.second});
		while (!queue.empty()) {
			auto currentPath = queue.dequeue();
			for (auto &nextVertex : mFollowers[currentPath.last()]) {
				if (nextVertex == currentPath.first()) {
					auto loopHead = currentPath.first();
					for (auto &i : currentPath) {
						if (mTopologicalOrder[loopHead] > mTopologicalOrder[i]) {
							loopHead = i;
						}
					}
					for (auto &i : currentPath) {
						if (i != loopHead) {
							loopBody[loopHead].insert(i);
						}
					}
					mLoopHeads.insert(loopHead);
				} else if (nextVertex != edge.second && !currentPath.contains(nextVertex)) {
					auto newPath = currentPath;
					newPath.append(nextVertex);
					queue.enqueue(newPath);
				}
			}
		}
	}
	auto topOrder = vertexOrder;

	for (int i = topOrder.size() - 1; i >= 0; --i) {
		Vertex e = topOrder[i];
		bool somethingChanged = true;
		while (somethingChanged) {
			somethingChanged = false;
			for (auto &u : loopBody[e]) {
				for (auto &f : mFollowers[u]) {
					if (loopBody[e].contains(f) || (f == e)) {
						continue;
					}
					bool isInLoop = true;
					for (auto &p : mPredecessors[f]) {
						if (!loopBody[e].contains(p)
							&& !(loopBody.contains(f) && loopBody[f].contains(p))) {
							isInLoop = false;
							break;
						}
					}
					if (isInLoop) {
						somethingChanged = true;
						loopBody[e].insert(f);
						if (loopBody.contains(f)) {
							loopBody[e].unite(loopBody[f]);
						}
					}
				}
			}
		}
	}

	for (int i = topOrder.size() - 1; i >= 0; --i) {
		Vertex v = topOrder[i];
		int maxIndex = -1;
		for (auto &u : loopBody[v]) {
			maxIndex = maxIndex > vertexOrder.lastIndexOf(u) ? maxIndex : vertexOrder.lastIndexOf(u);
		}
		if (maxIndex > vertexOrder.lastIndexOf(v)) {
			vertexOrder.insert(maxIndex + 1, v);
			vertexOrder.erase(vertexOrder.begin() + vertexOrder.indexOf(v));
		}
	}
}
