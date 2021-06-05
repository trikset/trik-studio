#pragma once

#include <QtCore/QSet>
#include <QtCore/QMap>

#include <qrkernel/ids.h>

namespace generatorBase {

class StructurizerNode;
class SimpleStructurizerNode;
class ContinuationStructurizerNode;
class IfStructurizerNode;
class LoopStructurizerNode;

class Structurizer : public QObject
{
	Q_OBJECT

public:
	explicit Structurizer(QObject *parent = nullptr);

	/// main function that performs structurization
	StructurizerNode *performStructurization(const QSet<qReal::Id> &verticesIds, qReal::Id startVertex
			, const QMap<qReal::Id, QList<qReal::Id>> &followers);

private:
	typedef qReal::Id Vertex;

	void dfs(Vertex v, int &currentTime, QMap<Vertex, int> &color);

	QSet<Vertex> mVertices;
	QMap<Vertex, QVector<Vertex>> mFollowers;
	QMap<Vertex, QVector<Vertex>> mPredecessors;
	QMap<Vertex, int> mTopologicalOrder;
	QSet<Vertex> mExits;
	QSet<Vertex> mLoopHeads;

	Vertex mStartVertex;
	QVector<QPair<Vertex, Vertex>> mCyclicEdges;

	void reorderLoopHeads(QVector<Vertex> &v);
};

}
