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

#pragma once

#include <functional>
#include <QtCore/QSet>
#include <QtCore/QList>
#include <QtCore/QString>

#include <generatorBase/gotoControlFlowGenerator.h>

namespace pioneer {
namespace lua {

/// Generator for state machine for Pioneer quadcopter.
///
/// Programs for Pioneer are reactive, reacting on events from autopilot like reaching given point or given altitude.
/// Program can be in some state and by current state and current event can execute an event handler. Handler can send
/// some more commands to autopilot, wait (synchronously) and ultimately move system to a next state.
///
/// Generator requires some advanced logic because control-flow-based program shall be transformed into a set of
/// handlers, differentiating linear fragments that are executed synchronously and creating new states for nodes that
/// execute asynchronously, like "GoToPoint", who continues execution only when quadcopter reaches given point.
class PioneerStateMachineGenerator : public generatorBase::GotoControlFlowGenerator
{
	Q_OBJECT

public:
	PioneerStateMachineGenerator(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, generatorBase::GeneratorCustomizer &customizer
			, generatorBase::PrimaryControlFlowValidator &validator
			, const qReal::Id &diagramId
			, QObject *parent = 0
			, bool isThisDiagramMain = true);

	/// Registers a function that will be called when generator visits a node with given id.
	/// Allows to collect additional information during generation.
	void registerNodeHook(std::function<void(const qReal::Id)> hook);

private:
	void visitRegular(const qReal::Id &id, const QList<generatorBase::LinkInfo> &links) override;

	void visitConditional(const qReal::Id &id, const QList<generatorBase::LinkInfo> &links) override;

	void visit(const qReal::Id &nodeId, QList<utils::DeepFirstSearcher::LinkInfo> &links) override;

	/// Copies a linear fragment starting from semantic node with id @p from and pastes it into semantic tree as a
	/// sibling of @p after node.
	void copySynchronousFragment(generatorBase::semantics::SemanticNode *after, const qReal::Id from, bool withLabel);

	/// Copies right siblings of the @p node until first labeled node, or until end.
	const QLinkedList<generatorBase::semantics::SemanticNode *> copyRightSiblingsUntilAsynchronous(
			generatorBase::semantics::NonZoneNode *node);

	/// Creates node with label for a given id. Does not transfer ownership.
	generatorBase::semantics::NonZoneNode *produceLabeledNode(const qReal::Id block);

	/// Returns true if this node is asynchronous.
	bool isAsynchronous(const generatorBase::semantics::SemanticNode * const node) const;

	/// Returns true if this node is synthetic, i.e. does not have corresponding block on a diagram.
	static bool isLabel(const generatorBase::semantics::SemanticNode * const node);

	/// Returns true if given node is a direct child of a root node.
	static bool isTopLevelNode(const generatorBase::semantics::SemanticNode * const node);

	/// Finds first sibling of a given node that corresponds to asynchronous block. Returns nullptr if there is no
	/// such node.
	generatorBase::semantics::SemanticNode * findAsynchronousSibling(
			generatorBase::semantics::NonZoneNode *node) const;

	/// Returns first non-synthetic right sibling of a given node. Returns nullptr if there is no such sibling.
	static generatorBase::semantics::SemanticNode *findRightSibling(
			generatorBase::semantics::SemanticNode * const node);

	/// Returns parent of a given node.
	static generatorBase::semantics::NonZoneNode *parent(
			generatorBase::semantics::SemanticNode * const node);

	/// Creates synthetic node that denotes end of asynchronous handler.
	generatorBase::semantics::SemanticNode *produceEndOfHandlerNode();

	/// Adds nextNode as a right sibling of thisNode.
	static void addAfter(generatorBase::semantics::SemanticNode * const thisNode
			, generatorBase::semantics::SemanticNode * const nextNode);

	/// Node types that have asynchronous semantics: send a command to autopilot and continue execution when this
	/// command is completed (e.g. "GoToPoint").
	QSet<QString> mAsynchronousNodes;

	/// A set of asynchronous nodes who already have their distinct states and we can directly generate transition
	/// into them. Note that labeled nodes are not nessesarily asynchronous and not all asynchronous nodes are labeled.
	/// Actually, a node *after* asynchronous node shall be labeled, to allow to continue execution when asyncronous
	/// node will do its work.
	QSet<qReal::Id> mLabeledNodes;

	/// A list of functions that shall be called on visiting each node.
	QList<std::function<void(const qReal::Id)>> mNodeHooks;
};

}
}
