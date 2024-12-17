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
