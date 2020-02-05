/* Copyright 2015 QReal Research Group
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

#include "consoleDock.h"

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>

#include <thirdparty/qslog/QsLog.h>

using namespace qReal::ui;

static const int defaultUpdateInterval = 250; // ms

ConsoleDock::ConsoleDock(const QString &title, QWidget *parent)
	: QDockWidget(title, parent)
	, mOutput(new QPlainTextEdit(this))
{
	QFont font("Monospace");
	font.setStyleHint(QFont::Monospace);
	mOutput->setFont(font);
	if (!QFontInfo(font).fixedPitch()) {
		QLOG_ERROR() << "Not monospaced font was choosen " << font.toString();
	}
	setWidget(mOutput);
	mOutput->setReadOnly(false);
	mOutput->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(mOutput, &QPlainTextEdit::customContextMenuRequested, this, [&](const QPoint &pos){
		QMenu *menu = mOutput->createStandardContextMenu();
		QAction *resetAction = menu->addAction(tr("Reset shell"));
		connect(resetAction, &QAction::triggered, this, [&](bool){
			mTimer.stop(); // same as clear() but doesn't hide
			mMsgQueue.clear();
			mOutput->clear();
		});
		menu->exec(mapToGlobal(pos));
		delete menu;
	});

	setObjectName("consoleDockContents");
	connect(&mTimer, &QTimer::timeout, this, [&](){
		QString res;
		res.reserve(100000);
		while (!mMsgQueue.isEmpty()) {
			res.append(mMsgQueue.dequeue());
		}

		// HACK: Append text without a newline character
		auto const &c = mOutput->textCursor();
		mOutput->moveCursor(QTextCursor::End);
		mOutput->insertPlainText(res);
		mOutput->setTextCursor(c);
		// ----

		mOutput->verticalScrollBar()->setValue(mOutput->verticalScrollBar()->maximum());
		show();
		if (mMsgQueue.isEmpty()) {
			mTimer.stop();
		}
	});
}

bool ConsoleDock::isEmpty() const
{
	return mOutput->toPlainText().isEmpty();
}

void ConsoleDock::print(const QString &text)
{
	mMsgQueue.enqueue(text);
	if (!mTimer.isActive()) {
		// Maybe show text here to reduce latency a bit
		mTimer.start(defaultUpdateInterval);
	}
}

void ConsoleDock::clear()
{
	mTimer.stop();
	mMsgQueue.clear();
	mOutput->clear();
	hide();
}
