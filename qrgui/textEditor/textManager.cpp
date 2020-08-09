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

#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <QtCore/QFile>

#include <qrutils/outFile.h>
#include <qrutils/widgets/qRealMessageBox.h>
#include <qrutils/widgets/qRealFileDialog.h>

#include <plugins/toolPluginInterface/systemEvents.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/mainWindowInterpretersInterface.h>

#include "textManager.h"
#include "qscintillaTextEdit.h"

using namespace qReal;
using namespace text;

TextManager::TextManager(SystemEvents &systemEvents, gui::MainWindowInterpretersInterface &mainWindow)
	: mMainWindow(mainWindow)
	, mSystemEvents(systemEvents)
{
	connect(&mSystemEvents, &SystemEvents::codeTabClosed, this, &TextManager::onTabClosed);
}

bool TextManager::openFile(const QString &filePath, const QString &generatorName, const text::LanguageInfo &language)
{
	QFile file(filePath);	

	if (!file.isOpen() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream inStream(&file);
		inStream.setCodec(QTextCodec::codecForName("UTF-8"));
		const auto &area = new QScintillaTextEdit();
		connect(&*area, &QScintillaTextEdit::textWasModified, this
				, [this](QScintillaTextEdit *t) { setModified(t, true); });
		area->setCurrentLanguage(language);
		area->setText(inStream.readAll());
		mText.insert(filePath, area);
		mPath.insert(area, filePath);
		mPathType.insert(filePath, true);
		mModified.insert(filePath, {false, false});
		mGeneratorName.insert(filePath, generatorName);
		mCodeBlockManager.addNewCode(filePath);
		return true;
	}

	return false;
}

bool TextManager::bindCode(const Id &diagram, const QString &filePath)
{
	if (mText.contains(filePath)) {
		mDiagramCodeManager.insert(diagram, filePath);
		return true;
	}
	return false;
}

bool TextManager::unbindCode(const QString &filePath)
{
	if (mDiagramCodeManager.key(filePath) == Id()) {
		// Unbind is successful because this code doesn't bind to any diagram
		return true;
	}
	return mDiagramCodeManager.remove(mDiagramCodeManager.key(filePath), filePath) != 0;
}

bool TextManager::suggestToSaveCode(text::QScintillaTextEdit *code)
{
	if (mModified[mPath.value(code)].second) {
		switch (utils::QRealMessageBox::question(
				mMainWindow.currentTab()
				, tr("Confirmation")
				, tr("Save before closing?")
				, QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel)))
		{
		case QMessageBox::Yes:
			saveText(false);
			return true;
		case QMessageBox::No:
		{
			// very bad way but now I have only this idea
			// need to reset code to last saved state
			setModified(code, false);
			return true;
		}
		default:
			return false;
		}
	}
	return true;
}

bool TextManager::unbindCode(text::QScintillaTextEdit *code)
{
	if (mDiagramCodeManager.key(mPath.value(code)) == Id()) {
		// Unbind is successful because this code doesn't bind to any diagram
		return true;
	}
	return suggestToSaveCode(code) && unbindCode(mPath.value(code));
}

bool TextManager::closeFile(const QString &filePath)
{
	mPath.remove(mText.value(filePath));
	mPathType.remove(filePath);
	mModified.remove(filePath);
	mGeneratorName.remove(filePath);
	unbindCode(filePath);
	mCodeBlockManager.removeCode(filePath);
	return mText.remove(filePath);
}

void TextManager::changeFilePath(const QString &from, const QString &to)
{
	const auto &code = mText.value(from);
	QPair<bool, bool> mod(true, false);
	const QString genName = generatorName(from);
	const Id diagram = mDiagramCodeManager.key(from);

	closeFile(from);

	mText.insert(to, code);
	mPath.insert(code, to);
	mPathType.insert(to, false);
	mModified.insert(to, mod);
	mGeneratorName.insert(to, genName);

	if (!diagram.isNull()) {
		bindCode(diagram, to);
	}
}

QScintillaTextEdit *TextManager::code(const QString &filePath) const
{
	return mText.value(filePath);
}

QList<text::QScintillaTextEdit *> TextManager::code(const Id &diagram) const
{
	QList<text::QScintillaTextEdit *> codeList;

	for (const QString &filePath : mDiagramCodeManager.values(diagram)) {
		codeList << mText.value(filePath);
	}
	return codeList;
}

bool TextManager::contains(const QString &filePath) const
{
	return mText.contains(filePath);
}

bool TextManager::removeDiagram(const Id &diagram)
{
	return mDiagramCodeManager.remove(diagram);
}

Id TextManager::diagram(text::QScintillaTextEdit *code) const
{
	return mDiagramCodeManager.key(mPath.value(code));
}

QString TextManager::path(text::QScintillaTextEdit *code) const
{
	return mPath.value(code);
}

bool TextManager::isDefaultPath(const QString &path) const
{
	return mPathType.value(path);
}

bool TextManager::isModified(const QString &path) const
{
	return mModified.value(path).second;
}

bool TextManager::isModifiedEver(const QString &path) const
{
	return mModified.value(path).first;
}

void TextManager::setModified(text::QScintillaTextEdit *code, bool modified)
{
	QString const &path = mPath.value(code);
	QPair<bool, bool> mod = mModified.value(path);
	mod.first = !modified || mod.first;
	mod.second = modified && code->isUndoAvailable();
	code->setModified(mod.second);
	mModified.insert(path, mod);

	if (isDefaultPath(path)) {
		mCodeBlockManager.setActive(path, !(modified && code->isUndoAvailable()));
	}

	emit textChanged(code, modified && code->isUndoAvailable());
}

void TextManager::onTabClosed(const QFileInfo &file)
{
	closeFile(file.absoluteFilePath());
}

void TextManager::showInTextEditor(const QFileInfo &fileInfo
		, const QString &genName, const text::LanguageInfo &language)
{
	/// @todo: Uncomment it
	// Q_ASSERT(!fileInfo.baseName().isEmpty());

	if (!mMainWindow.activeDiagram().isNull()) {
		const QString filePath = fileInfo.absoluteFilePath();

		if (contains(filePath)) {
			mMainWindow.closeTab(code(filePath));
		}

		openFile(filePath, genName, language);
		QScintillaTextEdit *area = code(filePath);
		area->show();
		bindCode(mMainWindow.activeDiagram(), filePath);
		emit mSystemEvents.newCodeAppeared(mMainWindow.activeDiagram(), QFileInfo(filePath));

		mMainWindow.openTab(area, fileInfo.fileName());
	}
}

void TextManager::showInTextEditor(const QFileInfo &fileInfo, const text::LanguageInfo &language)
{
	Q_ASSERT(!fileInfo.completeBaseName().isEmpty());

	const QString filePath = fileInfo.absoluteFilePath();

	if (contains(filePath)) {
		mMainWindow.closeTab(code(filePath));
	}

	openFile(filePath, QString(), language);
	QScintillaTextEdit *area = code(filePath);
	if (!area) {
		return;
	}

	area->show();

	// Need to bind diagram and code file only if code is just generated
//	bindCode(mMainWindow.activeDiagram(), filePath);
//	emit mSystemEvents.newCodeAppeared(mMainWindow.activeDiagram(), QFileInfo(filePath));

	mMainWindow.openTab(area, fileInfo.fileName());
}

bool TextManager::saveText(bool saveAs)
{
	QScintillaTextEdit * const area = dynamic_cast<QScintillaTextEdit *>(mMainWindow.currentTab());
	if (!area) {
		return false;
	}

	QFileInfo fileInfo = path(area);

	if (saveAs || fileInfo.fileName().isEmpty()) {
		QString editorExtension = QString("%1 (*.%2)").arg(
				area->currentLanguage().extensionDescription
				, area->currentLanguage().extension);
		const QString extensionDescriptions = editorExtension + ";;" + tr("All files (*)");
		QString *currentExtensionDescription = &editorExtension;
		fileInfo = QFileInfo(utils::QRealFileDialog::getSaveFileName("SaveTextFromTextManager"
				, mMainWindow.windowWidget()
				, tr("Save generated code")
				, QString()
				, extensionDescriptions
				, QString()
				, currentExtensionDescription));
	}

	if (!fileInfo.fileName().isEmpty()) {
		mMainWindow.setTabText(area, fileInfo.fileName());

		utils::OutFile out(fileInfo.absoluteFilePath());

		out() << area->text();

		if (isDefaultPath(path(area)) || saveAs) {
			changeFilePath(path(area), fileInfo.absoluteFilePath());
		}

		setModified(area, false);

		const Id diagram = TextManager::diagram(area);
		if (saveAs && !diagram.isNull()) {
			emit mSystemEvents.codePathChanged(diagram, path(area), fileInfo);
		}
	}

	return true;
}

QString TextManager::generatorName(const QString &filePath) const
{
	return mGeneratorName.value(filePath, "");
}

CodeBlockManager &TextManager::codeBlockManager()
{
	return mCodeBlockManager;
}
