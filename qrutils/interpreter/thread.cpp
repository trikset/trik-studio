/* Copyright 2007-2015 QReal Research Group
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

#include "thread.h"

#include <QtWidgets/QApplication>
#include <QtCore/QTimer>

#include <qrkernel/settingsManager.h>

#include <qrutils/interpreter/blocks/receiveThreadMessageBlock.h>
#include <qrutils/interpreter/blocks/subprogramBlock.h>


using namespace qReal;
using namespace interpretation;

const int blocksCountTillProcessingEvents = 100;

Thread::Thread(const GraphicalModelAssistInterface *graphicalModelApi
		, gui::MainWindowInterpretersInterface &interpretersInterface
		, const Id &initialNodeType
		, BlocksTableInterface &blocksTable
		, const Id &initialNode
		, const QString &threadId)
	: mGraphicalModelApi(graphicalModelApi)
	, mInterpretersInterface(interpretersInterface)
	, mInitialNodeType(initialNodeType)
	, mBlocksTable(blocksTable)
	, mCurrentBlock(mBlocksTable.block(initialNode))
	, mBlocksSincePreviousEventsProcessing(0)
	, mProcessEventsTimer(new QTimer(this))
	, mProcessEventsMapper(new QSignalMapper(this))
	, mId(threadId)
{
	initTimer();
}

Thread::Thread(const GraphicalModelAssistInterface *graphicalModelApi
		, gui::MainWindowInterpretersInterface &interpretersInterface
		, const Id &initialNodeType
		, const Id &diagramToInterpret
		, BlocksTableInterface &blocksTable
		, const QString &threadId)
	: mGraphicalModelApi(graphicalModelApi)
	, mInterpretersInterface(interpretersInterface)
	, mInitialNodeType(initialNodeType)
	, mBlocksTable(blocksTable)
	, mCurrentBlock(nullptr)
	, mInitialDiagram(diagramToInterpret)
	, mBlocksSincePreviousEventsProcessing(0)
	, mProcessEventsTimer(new QTimer(this))
	, mProcessEventsMapper(new QSignalMapper(this))
	, mId(threadId)
{
	initTimer();
}

Thread::~Thread()
{
	for (const StackFrame &frame : mStack) {
		if (frame.block()) {
			mInterpretersInterface.dehighlight(frame.block()->id());
		}
	}
}

void Thread::initTimer()
{
	mProcessEventsTimer->setSingleShot(true);
	mProcessEventsTimer->setInterval(0);
	connect(mProcessEventsTimer, SIGNAL(timeout())
			, mProcessEventsMapper, SLOT(map()));

	connect(mProcessEventsMapper, SIGNAL(mapped(QObject*))
			, this, SLOT(interpretAfterEventsProcessing(QObject*)));
}

void Thread::interpret()
{
	if (mCurrentBlock) {
		turnOn(mCurrentBlock);
	} else {
		stepInto(mInitialDiagram);
	}
}

void Thread::stop(qReal::interpretation::StopReason reason)
{
	emit stopped(reason);
}

void Thread::nextBlock(const Id &blockId)
{
	turnOff(mCurrentBlock);
	BlockInterface *const block = blockId == Id() ? nullptr : mBlocksTable.block(blockId);
	turnOn(block);
}

void Thread::stepInto(const Id &diagram)
{
	const Id initialNode = findStartingElement(diagram);
	BlockInterface * const block = mBlocksTable.block(initialNode);

	if (initialNode.isNull() || !block) {
		error(tr("No entry point found, please add Initial Node to a diagram"), diagram);
		return;
	}

	if (mStack.count() >= SettingsManager::value("interpreterStackSize").toInt()) {
		error(tr("Stack overflow"));
		return;
	}

	turnOn(block);
}

void Thread::finishedSteppingInto()
{
	if (mStack.isEmpty()) {
		emit stopped(qReal::interpretation::StopReason::finished);
		return;
	}

	mCurrentBlock = mStack.top().block();

	// If block already connected then nothing will happen because of Qt::UniquieConnection modifiers.
	// But if it is disconnected (for example, we did it in turnOff() on recursive lifting) we should connect it back.
	connectBlock(mCurrentBlock);

	// Execution must proceed here
	mCurrentBlock->finishedSteppingInto();
}

void Thread::failure()
{
	emit stopped(qReal::interpretation::StopReason::error);
}

void Thread::error(const QString &message, const Id &source)
{
	mInterpretersInterface.errorReporter()->addError(message, source);
	failure();
}

Id Thread::findStartingElement(const Id &diagram) const
{
	const IdList children = mGraphicalModelApi->graphicalRepoApi().children(diagram);

	for (const Id &child : children) {
		if (child.type() == mInitialNodeType) {
			return child;
		}
	}

	return Id();
}

void Thread::turnOn(BlockInterface * const block)
{
	mCurrentBlock = block;
	if (!mCurrentBlock) {
		finishedSteppingInto();
		return;
	}

	if (!mGraphicalModelApi->graphicalRepoApi().exist(block->id())) {
		// If we get non-null block instance, but non-existing id then the block
		// was removed from diagram during the interpretation.
		error(tr("Block has disappeared!"));
		return;
	}

	mInterpretersInterface.highlight(mCurrentBlock->id(), false);
	connectBlock(mCurrentBlock);

	// Check subprogram block
	const blocks::SubprogramBlock * const subprogram = dynamic_cast<blocks::SubprogramBlock *>(mCurrentBlock);
	if (subprogram) {
		QList<QPair<QString, QVariant>> properties;
		const QList<blocks::SubprogramBlock::DynamicParameter> parameters = subprogram->dynamicParameters();
		for (const blocks::SubprogramBlock::DynamicParameter &param : parameters) {
			properties << qMakePair(param.name, subprogram->value<QVariant>(param.name));
		}

		mStack.push(StackFrame(mCurrentBlock, properties));
	} else {
		mStack.push(StackFrame(mCurrentBlock));
	}

	++mBlocksSincePreviousEventsProcessing;
	if (mBlocksSincePreviousEventsProcessing > blocksCountTillProcessingEvents) {
		// Here we want to process all accumulated events and terminate blocks recursion
		mBlocksSincePreviousEventsProcessing = 0;

		// After timer was started control flow returns to event loop and
		// among events there can be the one that destroys this thread instance.
		// There are some suspicions that in QObject destructor children are removed
		// not immediately but with deleteLater() method. So there is a small probability
		// that slot will be triggered after this object is destroyed. Then
		// we can not access fields, but can access alive block instance in mapper.
		// Kind of hack, but quite an easy way not to suspend everything if
		// interpreted program has an infinite loop without timers.
		mProcessEventsMapper->removeMappings(mProcessEventsTimer);
		mProcessEventsMapper->setMapping(mProcessEventsTimer, mCurrentBlock);
		mProcessEventsTimer->start();
	} else {
		mCurrentBlock->interpret(this);
	}
}

void Thread::interpretAfterEventsProcessing(QObject *blockObject)
{
	BlockInterface * const block = dynamic_cast<BlockInterface *>(blockObject);
	if (block) {
		block->interpret(this);
	}
}

void Thread::turnOff(BlockInterface * const block)
{
	// This is a signal not from a current block of this thread.
	// Other thread shall process it, we will just ignore.
	if (sender() && sender() != block) {
		return;
	}

	if (sender()) {
		sender()->disconnect(this);
	}

	// Restoring old properties...
	const QList<QPair<QString, QVariant>> &oldProperties = mStack.top().properties();
	Block * const topBlock = dynamic_cast<Block *>(mStack.top().block());
	for (const QPair<QString, QVariant> &property : oldProperties) {
		const QString propertyName = property.first;
		const QVariant propertyValue = property.second;

		if (propertyValue.type() == QVariant::Int) {
			topBlock->setVariableValue<int>(propertyName, propertyValue.toInt());
		} else if (propertyValue.type() == QVariant::Bool) {
			topBlock->setVariableValue<bool>(propertyName, propertyValue.toBool());
		} else if (propertyValue.type() == QVariant::Double) {
			topBlock->setVariableValue<qreal>(propertyName, propertyValue.toReal());
		} else if (propertyValue.type() == QVariant::StringList) {
			topBlock->setVectorVariableValue(propertyName, propertyValue.toStringList().toVector());
		} else {
			topBlock->setVariableValue<QString>(propertyName, propertyValue.toString());
		}
	}

	mStack.pop();
	mInterpretersInterface.dehighlight(block->id());
}

void Thread::connectBlock(BlockInterface * const block)
{
	connect(block, &BlockInterface::done, this, &Thread::nextBlock, Qt::UniqueConnection);
	connect(block, &BlockInterface::newThread, this, &Thread::newThread, Qt::UniqueConnection);
	connect(block, &BlockInterface::killThread, this, &Thread::killThread, Qt::UniqueConnection);
	connect(block, &BlockInterface::sendMessage, this, &Thread::sendMessage, Qt::UniqueConnection);
	connect(block, &BlockInterface::failure, this, &Thread::failure, Qt::UniqueConnection);
	connect(block, &BlockInterface::stepInto, this, &Thread::stepInto, Qt::UniqueConnection);
}

void Thread::newMessage(const QString &message)
{
	if (mMessages.isEmpty()) {
		blocks::ReceiveThreadMessageBlock *block = dynamic_cast<blocks::ReceiveThreadMessageBlock *>(mCurrentBlock);
		if (block) {
			block->receiveMessage(message);
			return;
		}
	}

	mMessages.enqueue(message);
}

bool Thread::getMessage(QString &message)
{
	if (!mMessages.isEmpty()) {
		message = mMessages.dequeue();
		return true;
	}

	return false;
}

QString Thread::id() const
{
	return mId;
}
