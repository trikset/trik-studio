/* Copyright 2014-2016 Dmitry Mordvinov
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

#include "removeAndUpdateCommand.h"

#include <models/models.h>
#include <QQueue>

#include "editor/editorViewScene.h"
#include "editor/commands/arrangeLinksCommand.h"
#include "editor/commands/updateElementCommand.h"
#include "editor/commands/reshapeEdgeCommand.h"

using namespace qReal::commands;
using namespace qReal::gui::editor::commands;

RemoveAndUpdateCommand::RemoveAndUpdateCommand(EditorViewScene &scene
		, const models::Models &models)
	: RemoveElementsCommand(models)
	, mScene(scene)
{
}

// Builds an adjacency list for the subgraph induced by nodesSet.
// Only edges connecting two nodes from nodesSet are included;
// connections to nodes outside the set are ignored.
QHash<qReal::Id, QList<qReal::Id>> RemoveAndUpdateCommand::buildAdjacency(const QSet<Id> &nodesSet)
{
	auto &&repo = mGraphicalApi.graphicalRepoApi();
	QHash<Id, QList<Id>> adjacency;

	for (auto &&node : nodesSet) {
		auto &&neighbors = adjacency[node];
		auto &&links = repo.links(node);

		for (auto &&link : links) {
			auto &&other = repo.otherEntityFromLink(link, node);

			if (nodesSet.contains(other)) {
				neighbors.append(other);
			}
		}
	}

	return adjacency;
}

// Finds connected components in the adjacency graph using breadth-first search.
// Each BFS traversal starting from an unvisited node produces one connected
// component.
QList<QList<qReal::Id>> RemoveAndUpdateCommand::findComponents(const QSet<Id> &nodesSet,
									const QHash<Id, QList<Id>> &adjacency)
{
	QList<QList<Id>> components;
	QSet<Id> visited;
	visited.reserve(nodesSet.size());

	for (auto &&start: nodesSet) {
		if (visited.contains(start)) {
			continue;
		}

		QList<Id> component;
		QQueue<Id> queue;

		queue.enqueue(start);
		visited.insert(start);

		while (!queue.isEmpty()) {
			auto &&current = queue.dequeue();
			component.append(current);

			for (auto &&neighbor : adjacency.value(current)) {
				if (!visited.contains(neighbor)) {
					visited.insert(neighbor);
					queue.enqueue(neighbor);
				}
			}
		}

		components.append(std::move(component));
	}

	return components;
}

void RemoveAndUpdateCommand::postprocessCollectedItems(QList<ElementInfo> &nodes, QList<ElementInfo> &edges)
{
	QSet<Id> nodesSet;
	nodesSet.reserve(nodes.size());

	for (auto &&info : nodes) {
		nodesSet.insert(info.id());
	}

	auto &&adjacency = buildAdjacency(nodesSet);
	auto &&components = findComponents(nodesSet, adjacency);

	for (auto &&component: components) {
		processComponent(component, nodesSet, nodes, edges);
	}
}

// Collapses a connected component by removing its outgoing edge and updating
// the incoming edge to bypass the component and point directly to the original
// destination node of the removed edge.
// Before: A ->(1) [ component ] ->(2) B
// After: A ->(1)-> B
void RemoveAndUpdateCommand::reconnectComponent(const Id &incomingEdge, const Id &outgoingEdge,
						QList<ElementInfo> &nodes, QList<ElementInfo> &edges)
{
	auto &&repo = mGraphicalApi.graphicalRepoApi();
	auto &&from = repo.from(incomingEdge);
	auto &&to = repo.to(outgoingEdge);
	appendGraphicalDelete(outgoingEdge, nodes, edges);

	auto &&reshapeCmd = new ReshapeEdgeCommand(&mScene, incomingEdge);
	reshapeCmd->startTracking();

	auto &&edge = mScene.getEdgeById(incomingEdge);
	auto &&startNode = mScene.getNodeById(from);
	auto &&endNode = mScene.getNodeById(to);

	if (edge && startNode && endNode) {
		edge->connectToPort(startNode, endNode);
		edge->layOut();
	}

	reshapeCmd->stopTracking();
	addPreAction(reshapeCmd);
}

/// Processes a connected component of nodes selected for removal.
///
/// The selected nodes may consist of several independent parts, so they are
/// split into connected components beforehand. A component can be collapsed only
/// if it has a single entry point and a single exit point:
///   - exactly one incoming edge from outside the component
///   - exactly one outgoing edge to outside the component
///
/// In this case the component is removed and the incoming edge is reconnected
/// directly to the original destination of the outgoing edge.
///
/// Example:
///
/// Delete {B, C, D, F}
///
/// Before:
///
///          B
///         / \
/// A ---- C   D ---- E
///         \ /
///          F
///
/// After:
///
/// A ----------------> E
///
/// A component with multiple external connections cannot be collapsed safely.
///
/// Example:
///
/// Delete {B, C, D}
///
/// Before:
///
///       A
///       |
///       v
/// X --> B ----> E
///       |
///       v
///       C ----> F
///       |
///       v
///       D
///
/// Incoming edges:
///   A -> B
///   X -> B
///
/// Outgoing edges:
///   B -> E
///   C -> F
///
/// Since the component has multiple entry/exit points, it is skipped.
void RemoveAndUpdateCommand::processComponent(const QList<Id> &component, const QSet<Id> &nodesSet,
							QList<ElementInfo> &nodes, QList<ElementInfo> &edges)
{
	auto &&repo = mGraphicalApi.graphicalRepoApi();

	Id incomingEdge;
	Id outgoingEdge;

	for (auto &&node : component) {
		auto &&links = repo.links(node);
		for (auto &&link: links) {
			auto &&from = repo.from(link);
			auto &&to = repo.to(link);
			// This node cannot be located in another component.
			const auto fromInComponent = nodesSet.contains(from);
			const auto toInComponent = nodesSet.contains(to);

			// Internal edge, nothing to process.
			if (fromInComponent && toInComponent) {
				continue;
			}

			if (!fromInComponent) {
				if (!incomingEdge.isNull()) {
					return;
				}

				incomingEdge = link;
			}

			if (!toInComponent) {
				if (!outgoingEdge.isNull()) {
					return;
				}

				outgoingEdge = link;
			}
		}
	}

	if (incomingEdge.isNull() || outgoingEdge.isNull()) {
		return;
	}

	reconnectComponent(incomingEdge, outgoingEdge, nodes, edges);
}

void RemoveAndUpdateCommand::appendGraphicalDelete(const Id &id
		, QList<ElementInfo> &nodes, QList<ElementInfo> &edges)
{
	RemoveElementsCommand::appendGraphicalDelete(id, nodes, edges);

	// correcting unremoved edges
	ArrangeLinksCommand *arrangeCommand = new ArrangeLinksCommand(&mScene, id, true);
	arrangeCommand->setRedoEnabled(false);
	addPreAction(arrangeCommand);

	UpdateElementCommand *updateCommand = new UpdateElementCommand(&mScene, id);
	updateCommand->setRedoEnabled(false);
	addPreAction(updateCommand);

	const IdList links = mGraphicalApi.graphicalRepoApi().links(id);
	for (const Id &link : links) {
		UpdateElementCommand *updateLinkCommand = new UpdateElementCommand(&mScene, link);
		updateLinkCommand->setRedoEnabled(false);
		addPreAction(updateLinkCommand);
	}
}
