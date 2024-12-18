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

#pragma once

#include <QtCore/QList>
#include <QtWidgets/QUndoCommand>

#include "qrgui/controller/controllerDeclSpec.h"

namespace qReal {
namespace commands {

class QRGUI_CONTROLLER_EXPORT AbstractCommand : public QObject, public QUndoCommand
{
	Q_OBJECT

public:
	AbstractCommand();
	virtual ~AbstractCommand();

	virtual void redo();
	virtual void undo();

	void setRedoEnabled(bool enabled);
	void setUndoEnabled(bool enabled);

	/// Adds \a command into a list of commands to be executed before this command.
	void addPreAction(AbstractCommand * const command);

	/// Adds \a command into a specified place of the list of commands to be executed before this command.
	void insertPreAction(AbstractCommand * const command, int index);

	/// Adds \a command into a list of commands to be executed after this command.
	void addPostAction(AbstractCommand * const command);

	/// Adds \a command into a specified place of the list of commands
	/// to be executed after this command.
	void insertPostAction(AbstractCommand * const command, int index);

	virtual bool equals(const AbstractCommand &other) const;

	/// Performs command tree filtering with all duplicates to be removed.
	/// Removes duplicate closer to root, with search only in current subtree.
	/// Root command is never removed.
	void removeDuplicates();

	/// Returns id of the module that produced this command.
	/// @see bindToModule().
	QString moduleBinded() const;

	/// Binds this command to the tab associated with the specified module with \a moduleId.
	/// @see moduleBinded().
	void bindToModule(const QString &moduleId);

	/// Returns time of this command creation in ms since epoch
	uint timestamp() const;

signals:
	void redoComplete(bool success);
	void undoComplete(bool success);

protected:
	/// Returns operation success
	virtual bool execute() = 0;

	/// Implementation must undo all the changes made by this command
	/// and return operation success
	virtual bool restoreState() = 0;

private:
	void executeDirect(QList<AbstractCommand *> const &list);
	void executeReverse(QList<AbstractCommand *> const &list);

	/// Tells if command tree already contains specified command.
	/// The command itself is not considered
	bool hierarchyContains(AbstractCommand * const command) const;

	/// The command itself is not considered
	bool contains(QList<AbstractCommand *> const &list, const AbstractCommand * command) const;

	void removeDuplicatesOn(QList<AbstractCommand *> &list);

	bool mExecuted { false };
	bool mRedoEnabled { true };
	bool mUndoEnabled { true };
	QList<AbstractCommand *> mPreActions; // has ownership
	QList<AbstractCommand *> mPostActions; // has ownership
	QString mModuleBinded;
	uint mTimestamp {};
};

inline bool operator==(const AbstractCommand &c1, const AbstractCommand &c2)
{
	return c1.equals(c2);
}

}
}
