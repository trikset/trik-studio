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

#include "hotKeyManagerPage.h"
#include "ui_hotKeyManagerPage.h"

#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtWidgets/QAction>
#include <QtGui/QKeySequence>
#include <QtGui/QWheelEvent>

#include <qrutils/widgets/qRealMessageBox.h>

#include "hotKeyManager/hotKeyManager.h"

using namespace qReal;

const int maxShortcutParts = 3; // Actually, 3 = number of commas in string (= 4 shortcut parts)
								// e.g. "Ctrl+X, Alt+V, Shift+G, Ctrl+Y"
const int maxShortcuts = 3; // Max number of shortcuts which we can set to one command

PreferencesHotKeyManagerPage:: PreferencesHotKeyManagerPage(QWidget *parent)
	: PreferencesPage(parent)
	, mUi(new Ui::hotKeyManagerPage)
	, mCurrentId("")
	, mCurrentItem(nullptr)
	, mCurrentModifiers(Qt::NoModifier)
{
	mUi->setupUi(this);
	setObjectName("preferencesHotKeyManagerPage");
	setWindowIcon(QIcon(":/hotKeyManager/images/hotkeys.png"));

	mUi->hotKeysTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

	// TODO: implement export/import
	mUi->importPushButton->hide();
	mUi->exportPushButton->hide();

	connect(mUi->hotKeysTable, SIGNAL(cellClicked(int,int)), this, SLOT(activateShortcutLineEdit(int,int)));
	connect(mUi->hotKeysTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(doubleClicked(int,int)));
	connect(mUi->shortcutLineEdit, SIGNAL(newModifiers(Qt::KeyboardModifiers))
			, this, SLOT(newModifiers(Qt::KeyboardModifiers)));
	connect(mUi->shortcutLineEdit, SIGNAL(newKey(int)), this, SLOT(newKey(int)));
	connect(mUi->resetShortcutPushButton, SIGNAL(clicked()), this, SLOT(resetShortcuts()));
	connect(mUi->resetAllPushButton, SIGNAL(clicked()), this, SLOT(resetAllShortcuts()));

	restoreSettings();
}

PreferencesHotKeyManagerPage::~PreferencesHotKeyManagerPage()
{
	delete mUi;
}

void PreferencesHotKeyManagerPage::save()
{
}

void PreferencesHotKeyManagerPage::restoreSettings()
{
	mUi->hotKeysTable->clearContents();
	initTable();
	loadHotKeys();
	mUi->hotKeysTable->sortByColumn(0, Qt::AscendingOrder);

	const int tableWidth = mUi->hotKeysTable->horizontalHeader()->width();
	mUi->hotKeysTable->setColumnWidth(0, 0.25 * tableWidth);
	mUi->hotKeysTable->setColumnWidth(1, 0.5 * tableWidth);
	mUi->hotKeysTable->setColumnWidth(2, 0.25 * tableWidth);
}

void PreferencesHotKeyManagerPage::resetShortcuts()
{
	if (!mCurrentId.isEmpty()) {
		if (mCurrentItem->foreground() == Qt::black) {
			HotKeyManager::deleteShortcut(mCurrentId, mCurrentItem->text());
		}

		mCurrentItem->setText("");
		mUi->shortcutLineEdit->setText("");
	}
}

void PreferencesHotKeyManagerPage::resetAllShortcuts()
{
	if (utils::QRealMessageBox::question(this, tr("Question"), tr("This will clear all "\
			"current shortcuts. Are you sure?")) == QMessageBox::Yes) {
		mCurrentItem = nullptr;
		mCurrentId = "";

		HotKeyManager::resetAllShortcuts();
		restoreSettings();
	}
}

void PreferencesHotKeyManagerPage::showEvent(QShowEvent *e)
{
	restoreSettings();
	QWidget::showEvent(e);
}

void PreferencesHotKeyManagerPage::loadHotKeys()
{
	QHash<QString, QAction *> cmds = HotKeyManager::commands();
	QHash<QString, QString> shortcuts = HotKeyManager::shortcuts();

	QHash<QString, QAction *>::iterator i;
	int k;

	for (i = cmds.begin(), k = 0; i != cmds.end(); ++i, ++k) {
		const QStringList sequences = shortcuts.keys(i.key());

		mUi->hotKeysTable->item(k, 0)->setText(i.key());
		mUi->hotKeysTable->item(k, 1)->setText(i.value()->whatsThis());

		int j = 0;
		for (const QString &sequence : sequences) {
			mUi->hotKeysTable->item(k, 2 + j)->setText(sequence);
			mUi->hotKeysTable->item(k, 2 + j)->setForeground(QApplication::palette().color(QPalette::Text));

			if (++j >= maxShortcuts) {
				break;
			}
		}
	}
}

void PreferencesHotKeyManagerPage::initTable()
{
	const int rows = HotKeyManager::commands().size();
	mUi->hotKeysTable->setRowCount(rows);

	for (int i = 0; i < mUi->hotKeysTable->rowCount(); ++i) {
		// first column - name of command, second - short description, rest - shortcuts
		for (int j = 0; j < 2 + maxShortcuts; ++j) {
			mUi->hotKeysTable->setItem(i, j, new QTableWidgetItem(""));
		}
	}
}

void PreferencesHotKeyManagerPage::doubleClicked(const int row, const int column)
{
	mUi->shortcutLineEdit->setFocus();
	activateShortcutLineEdit(row, column);
}

void PreferencesHotKeyManagerPage::activateShortcutLineEdit(const int row, const int column)
{
	// Columns with shortcuts start from index 2
	if (column > 1) {
		if (mCurrentItem) {
			mCurrentItem->setBackground(QApplication::palette().color(QPalette::Base));
		}

		mCurrentId = mUi->hotKeysTable->item(row, 0)->text();
		mCurrentItem = mUi->hotKeysTable->item(row, column);
		mCurrentItem->setBackground(QApplication::palette().color(QPalette::Highlight));

		mUi->shortcutLineEdit->setText(mCurrentItem->text());
		mUi->shortcutLineEdit->setEnabled(true);

		if (HotKeyManager::setShortcut(mCurrentId, mCurrentItem->text())) {
			setTextColor(QApplication::palette().color(QPalette::Text));
		}
	} else {
		mCurrentId = "";
		mUi->shortcutLineEdit->clear();
		mUi->shortcutLineEdit->setEnabled(false);
	}
}

void PreferencesHotKeyManagerPage::newModifiers(Qt::KeyboardModifiers modifiers)
{
	mCurrentModifiers = modifiers;
}

void PreferencesHotKeyManagerPage::newKey(const int key)
{
	if (!mCurrentId.isEmpty()) {
		if (mCurrentItem->text().isEmpty()) {
			if (HotKeyManager::setShortcut(mCurrentId, QKeySequence(mCurrentModifiers + key))) {
				setTextColor(QApplication::palette().color(QPalette::Text));
			} else {
				setTextColor(Qt::red);
			}
			mCurrentItem->setText(QKeySequence(mCurrentModifiers + key).toString());
			mUi->shortcutLineEdit->setText(mCurrentItem->text());
		} else {
			const int parts = mCurrentItem->text().count(',');

			if (parts != maxShortcutParts) {
				const QString shortcut = QString("%1, %2").arg(
									mCurrentItem->text()
									, QKeySequence(mCurrentModifiers + key).toString()
								);

				if (mCurrentItem->foreground().color() == Qt::black) {
					HotKeyManager::deleteShortcut(mCurrentId, mCurrentItem->text());
				}

				if (HotKeyManager::setShortcut(mCurrentId, QKeySequence(shortcut))) {
					setTextColor(QApplication::palette().color(QPalette::Text));
					mCurrentItem->setText(shortcut);
					mUi->shortcutLineEdit->setText(mCurrentItem->text());
				} else {
					HotKeyManager::setShortcut(mCurrentId,  mCurrentItem->text());

					if (parts < maxShortcutParts - 1) {
						setTextColor(Qt::red);
						mCurrentItem->setText(shortcut);
						mUi->shortcutLineEdit->setText(mCurrentItem->text());
					}
				}
			}
		}
	}
}

void PreferencesHotKeyManagerPage::setTextColor(const QColor &color)
{
	mCurrentItem->setForeground(color);
	QPalette palette;
	palette.setColor(QPalette::Text, color);
	mUi->shortcutLineEdit->setPalette(palette);
}
