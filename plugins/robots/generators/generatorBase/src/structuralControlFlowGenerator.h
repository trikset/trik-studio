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

#pragma once

#include "generatorBase/robotsGeneratorDeclSpec.h"
#include "generatorBase/controlFlowGeneratorBase.h"
#include "generatorBase/semanticTree/semanticTree.h"
#include "structurizer.h"
#include "structurizerNodes/structurizerNode.h"
#include "structurizerNodes/ifStructurizerNode.h"
#include "structurizerNodes/loopStructurizerNode.h"
#include "structurizerNodes/simpleStructurizerNode.h"
#include "structurizerNodes/switchStructurizerNode.h"
#include "structurizerNodes/sequenceStructurizerNode.h"


#include <QtCore/QStack>
#include <QtCore/QVector>

namespace generatorBase {

/// Generates semantic tree in control-structured style.
/// First we obtain control flow graph.
/// Then we are trying structurize such a graph with Structurizer.
/// If structurization was successfull then we are trying to transform
/// control flow tree to Semantic Tree used for code generation.
///
/// If control flow can`t be represented with structured code generation process
/// is considered to be unsuccessfull.
class ROBOTS_GENERATOR_EXPORT StructuralControlFlowGenerator : public ControlFlowGeneratorBase
{
	Q_OBJECT

public:
	explicit StructuralControlFlowGenerator(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, GeneratorCustomizer &customizer
			, PrimaryControlFlowValidator &validator
			, const qReal::Id &diagramId
			, QObject *parent = 0
			, bool isThisDiagramMain = true);

	/// Implementation of clone operation for structural generator
	ControlFlowGeneratorBase *cloneFor(const qReal::Id &diagramId, bool cloneForNewDiagram) override;

	void beforeSearch() override;

	/// functions for visiting Ids. While each visit we contruct graph.
	void visitRegular(const qReal::Id &id, const QList<LinkInfo> &links) override;
	void visitConditional(const qReal::Id &id, const QList<LinkInfo> &links) override;
	void visitSwitch(const qReal::Id &id, const QList<LinkInfo> &links) override;
	void visitUnknown(const qReal::Id &id, QList<LinkInfo> const &links) override;
	void visitLoop(const qReal::Id &id, const QList<LinkInfo> &links) override;

	void visitPreconditionalLoop(const qReal::Id &id, const QList<LinkInfo> &links) override;

	/// This method can be used for semantic tree debug printing after all
	/// traversal stages.
	void afterSearch() override;

	/// Returns true if some generation errors occured but the generation process may be proceeded with other
	/// control flow generators (non-fatal errors occured).
	bool cantBeGeneratedIntoStructuredCode() const;

private:
	/// Implementation of generation process for structural generator.
	/// Important: the graph in the model would be traversed two or more times
	/// to build dominators tree and then perform structural analysis
	void performGeneration() override;

	/// Rule is applied only when generation was performed so there's a ForkNode or JoinNode variable.

	/// When forkNode was obtained we register other threads to generate
	void registerOtherThreads(const qReal::Id &id, const QList<LinkInfo> &threads
			, const QHash<qReal::Id, QString> &threadIds, parts::Threads &threadsStorage) override;

	/// When JoinNode was obtained we register other threads to generate
	void registerTerminatingThreads(const qReal::Id &id, parts::Threads &threadsStorage
			, bool fromMain) override;

	void performStructurization();

	void makeSemanticTree(StructurizerNode *nodes, semantics::ZoneNode *zone
			, QMap<qReal::Id, int> &numberOfOccurrences, QSet<qReal::Id> &alreadyCalculated);

	void addSimple(StructurizerNode *node, semantics::ZoneNode *zone
			, QMap<qReal::Id, int> &numberOfOccurrences, QSet<qReal::Id> &alreadyCalculated);

	void addBreak(StructurizerNode *node, semantics::ZoneNode *zone
			, QMap<qReal::Id, int> &numberOfOccurrences, QSet<qReal::Id> &alreadyCalculated);

	void addIf(StructurizerNode *node, semantics::ZoneNode *zone
			, QMap<qReal::Id, int> &numberOfOccurrences, QSet<qReal::Id> &alreadyCalculated);

	void addLoop(StructurizerNode *node, semantics::ZoneNode *zone
			, QMap<qReal::Id, int> &numberOfOccurrences, QSet<qReal::Id> &alreadyCalculated);

	void addSwitch(StructurizerNode *node, semantics::ZoneNode *zone
			, QMap<qReal::Id, int> &numberOfOccurrences, QSet<qReal::Id> &alreadyCalculated);

	/// methods for building graph
	void appendVertex(const qReal::Id &vertex);
	void addEdgeIntoGraph(const qReal::Id &from, const qReal::Id &to);
	void appendEdgesAndVertices(const qReal::Id &vertex, const QList<LinkInfo> &links);

	QString syntheticConditionToString(StructurizerNode::ConditionTree *tree);

	bool mCanBeGeneratedIntoStructuredCode;
	Structurizer *mStructurizer;

	QSet<qReal::Id> mIds;
	qReal::Id mStartVertex;
	QMap<qReal::Id, QList<qReal::Id>> mFollowers;
	bool mIsGraphBeingConstructed;
};

}
