/* Copyright 2015 QReal Research Group, Dmitry Mordvinov
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

#include "actionsBox.h"
#include <qrutils/graphicsUtils/abstractItem.h>

using namespace graphicsUtils;
using namespace twoDModel::view;

ActionsBox::ActionsBox(QObject *parent)
	: QObject(parent)
	, mSceneModeActions(this)
	, mScrollHandModeAction(new QAction(AbstractItem::loadTextColorIcon(":/icons/2d_hand.png"), tr("Hand dragging mode"), this))
	, mMultiSelectionModeAction(new QAction(QIcon(":/icons/2d_multiselection.png"), tr("Multiselection mode"), this))
	, mSeparator1(new QAction(this))
	, mSaveWorldModelAction(new QAction(QIcon(":/icons/2d_save.png"), tr("Save world model..."), this))
	, mLoadWorldModelAction(new QAction(QIcon(":/icons/2d_open.png"), tr("Load world model..."), this))
	, mLoadWorldWithoutRobotAction(new QAction(QIcon(":/icons/2d_open.png")
			, tr("Load world model without robot configuration..."), this))
	, mSeparator2(new QAction(this))
	, mDeleteAllAction(new QAction(AbstractItem::loadTextColorIcon(":/icons/2d_clear.png"), tr("Clear items"), this))
	, mClearFloorAction(new QAction(AbstractItem::loadTextColorIcon(":/icons/2d_clear_floor.svg"), tr("Clear floor"), this))
{
	mScrollHandModeAction->setCheckable(true);
	mMultiSelectionModeAction->setCheckable(true);
	mSceneModeActions.addAction(mScrollHandModeAction.data());
	mSceneModeActions.addAction(mMultiSelectionModeAction.data());
	mSeparator1->setSeparator(true);
	mSeparator2->setSeparator(true);
}

ActionsBox::~ActionsBox()
{
}

QAction &ActionsBox::scrollHandModeAction() const
{
	return *mScrollHandModeAction;
}

QAction &ActionsBox::multiSelectionModeAction() const
{
	return *mMultiSelectionModeAction;
}

QAction &ActionsBox::saveModelAction() const
{
	return *mSaveWorldModelAction;
}

QAction &ActionsBox::loadModelAction() const
{
	return *mLoadWorldModelAction;
}

QAction &ActionsBox::loadModelWithoutRobotAction() const
{
	return *mLoadWorldWithoutRobotAction;
}

QAction &ActionsBox::deleteAllAction() const
{
	return *mDeleteAllAction;
}

QAction &ActionsBox::clearFloorAction() const
{
	return *mClearFloorAction;
}

QList<QAction *> ActionsBox::sceneContextMenuActions() const
{
	return {
		&scrollHandModeAction()
		, &multiSelectionModeAction()
		, mSeparator1.data()
		, &saveModelAction()
		, &loadModelAction()
		, &loadModelWithoutRobotAction()
		, mSeparator2.data()
		, &deleteAllAction()
		, &clearFloorAction()
	};
}

void ActionsBox::setWorldModelActionsVisible(bool visible)
{
	saveModelAction().setVisible(visible);
	loadModelAction().setVisible(visible);
	loadModelWithoutRobotAction().setVisible(visible);
	deleteAllAction().setVisible(visible);
	/// @todo: Do we need to hide clearFloorAction() here?
}

void ActionsBox::setSaveLoadActionsShortcutsEnabled(bool enabled)
{
	if (enabled) {
		saveModelAction().setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
		loadModelAction().setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	} else {
		saveModelAction().setShortcut(QKeySequence());
		loadModelAction().setShortcut(QKeySequence());
	}
}
