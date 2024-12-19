/* Copyright 2007-2015 QReal Research Group, Dmitry Mordvinov
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

#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <QtCore/QProcess>
#include <QtCore/QPluginLoader>
#include <QtCore/QMetaType>
#include <QtCore/QSignalMapper>
#include <QtGui/QDesktopServices>
#include <QtGui/QKeySequence>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QAction>
#include <QtWidgets/QTreeView>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtSvg/QSvgGenerator>

#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>
#include <qrkernel/logging.h>
#include <qrkernel/platformInfo.h>
#include <qrutils/outFile.h>
#include <qrutils/stringUtils.h>
#include <qrutils/widgets/qRealFileDialog.h>
#include <qrutils/widgets/qRealMessageBox.h>
#include <qrutils/smartDock.h>
#include <qrutils/graphicsUtils/animatedEffects.h>
#include <qrutils/xmlUtils.h>
#include <Qsci/qsciprinter.h>
#include <Qsci/qsciscintillabase.h>

#include <qrgui/controller/controller.h>
#include <qrgui/dialogs/findReplaceDialog.h>
#include <qrgui/editor/propertyEditorView.h>
#include <qrgui/models/propertyEditorModel.h>
#include <qrgui/plugins/pluginManager/toolPluginManager.h>
#include <qrgui/plugins/pluginManager/editorManagerInterface.h>
#include <qrgui/plugins/toolPluginInterface/systemEvents.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/editorInterface.h>
#include <qrgui/systemFacade/systemFacade.h>

#include <dialogs/projectManagement/suggestToCreateProjectDialog.h>
#include <dialogs/progressDialog/progressDialog.h>

#include <models/models.h>
#include <models/commands/createPatternCommand.h>
#include <models/commands/removeElementsCommand.h>

#include <editor/editorView.h>
#include <editor/sceneCustomizer.h>
#include <editor/element.h>

#include <hotKeyManager/hotKeyManager.h>
#include <hotKeyManager/hotKeyManagerPage.h>

#include <brandManager/brandManager.h>

#include <mouseGestures/gesturesWidget.h>

#include <textEditor/textManager.h>
#include <textEditor/codeBlockManager.h>
#include <textEditor/qscintillaTextEdit.h>

#include <QKeySequence>

#include "qrealApplication.h"
#include "errorReporter.h"
#include "shapeEdit/shapeEdit.h"
#include "startWidget/startWidget.h"
#include "referenceList.h"
#include "splashScreen.h"
#include "dotRunner.h"
#include "findManager.h"
#include "projectManager/projectManagerWrapper.h"

#include "scriptAPI/scriptAPI.h"

#include "QsLog.h"

using namespace qReal;
using namespace qReal::gui;
using namespace qReal::commands;
using namespace qReal::gui::editor;

const QString twoDModelId = "TrikStudio.2DModel.Editor";

MainWindow::MainWindow(const QString &fileToOpen)
	: mUi(new Ui::MainWindowUi)
	, mSplashScreen(new SplashScreen(SettingsManager::value("Splashscreen").toBool()))
	, mController(new Controller)
	, mRootIndex(QModelIndex())
	, mPreferencesDialog(new gui::PreferencesDialog(this))
	, mRecentProjectsLimit(SettingsManager::value("recentProjectsLimit").toInt())
	, mSceneCustomizer(new SceneCustomizer())
	, mInitialFileToOpen(fileToOpen)
{
	QLOG_INFO() << "MainWindow: screen DPI is" << logicalDpiX();
	mUi->setupUi(this);
	mUi->paletteTree->initMainWindow(this);
	setWindowTitle("QReal");
	registerMetaTypes();
	mSplashScreen->activateWindow();
	mSplashScreen->setProgress(5);

	QApplication::processEvents();

	mFacade.reset(new SystemFacade());
	mPropertyModel.reset(new PropertyEditorModel(mFacade->editorManager()));
	mTextManager.reset(new text::TextManager(mFacade->events(), *this));
	mProjectManager.reset(new ProjectManagerWrapper(this, &*mTextManager));

	initPalette();
	initRecentProjectsMenu();
	customizeWindow();
	initTabs();

	mSplashScreen->setProgress(20);

	initMiniMap();
	initGridProperties();

	mSplashScreen->setProgress(40);

	initDocks();

	mErrorReporter.reset(new gui::ErrorReporter(mUi->errorListWidget, mUi->errorDock));
	mErrorReporter->updateVisibility(SettingsManager::value("warningWindow").toBool());
	mUi->errorDock->toggleViewAction()->setShortcut(QKeySequence(Qt::ALT + Qt::Key_1));
	addAction(mUi->errorDock->toggleViewAction());

	mPreferencesDialog->init();

	mSplashScreen->setProgress(60);

	loadEditorPlugins();

	mSplashScreen->setProgress(70);

	mDocksVisibility.clear();


	mSplashScreen->setProgress(80);

	initActionsFromSettings();

	mSplashScreen->setProgress(100);
	if (!SettingsManager::value("maximized").toBool()) {
		showNormal();
		restoreGeometry(SettingsManager::value("mainWindowGeometry").toByteArray());
	} else {
		showMaximized();
	}

	mFindReplaceDialog = new FindReplaceDialog(models().logicalRepoApi(), this);
	mFindHelper.reset(new FindManager(models().repoControlApi()
									  , models().mutableLogicalRepoApi(), this, mFindReplaceDialog));
	connectActions();
	connectSystemEvents();
	initExplorers();

	// So now we are going to load plugins. The problem is that if we will do it
	// here then we have some problems with correct main window initialization
	// beacuse of total event loop blocking by plugins. So waiting for main
	// window initialization complete and then loading plugins.
	QTimer::singleShot(50, this, &MainWindow::initPluginsAndStartWidget);
}

void MainWindow::connectActions()
{
	mUi->actionShow_grid->setChecked(SettingsManager::value("ShowGrid").toBool());
	mUi->actionShow_alignment->setChecked(SettingsManager::value("ShowAlignment").toBool());
	mUi->actionSwitch_on_grid->setChecked(SettingsManager::value("ActivateGrid").toBool());
	mUi->actionSwitch_on_alignment->setChecked(SettingsManager::value("ActivateAlignment").toBool());
	connect(mUi->actionQuit, &QAction::triggered, this, &MainWindow::close);
	connect(mUi->actionRestore_default_settings, &QAction::triggered, this, [this](){
		if (utils::QRealMessageBox::question(this, tr("Restore default settings"),
				tr("Do you realy want to restore default settings?"
						"\nWARNING: Settings restoring cannot be undone"
						"\nWARNING: The settings will be restored after application restart")) == QMessageBox::Yes) {
			mRestoreDefaultSettingsOnClose = true;
			close();
		}
	});

	connect(mUi->actionOpen, &QAction::triggered, this, [this]() {
		if (!mProjectManager->suggestToOpenExisting() && !currentTab()) {
			openStartTab();
		}
	});

	connect(mUi->actionSave, &QAction::triggered, this, &MainWindow::tryToSave);
	connect(mUi->actionSave_as, &QAction::triggered, &*mProjectManager, &ProjectManagerWrapper::suggestToSaveAs);
	connect(mUi->actionSave_diagram_as_a_picture, &QAction::triggered, this, &MainWindow::saveDiagramAsAPicture);
	connect(mUi->actionPrint, &QAction::triggered, this, &MainWindow::print);
	connect(mUi->actionMakeSvg, &QAction::triggered, this, &MainWindow::makeSvg);

	connect(mUi->actionNewProject, &QAction::triggered
			, this, static_cast<void (MainWindow::*)()>(&MainWindow::createProject));
	connect(mUi->actionNew_Diagram, &QAction::triggered
			, &*mProjectManager, &ProjectManagerWrapper::suggestToCreateDiagram);

	connect(mUi->logicalModelExplorer, &ModelExplorer::elementRemoved
			, this, &MainWindow::deleteFromLogicalExplorer);
	connect(mUi->graphicalModelExplorer, &ModelExplorer::elementRemoved
			, this, &MainWindow::deleteFromGraphicalExplorer);

	connect(mUi->actionZoom_In, &QAction::triggered, this, [=]() {
		if (mCurrentEditor) {
			mCurrentEditor->zoomIn();
		}
	});
	connect(mUi->actionZoom_Out, &QAction::triggered, this, [=]() {
		if (mCurrentEditor) {
			mCurrentEditor->zoomOut();
		}
	});

	connect(mUi->actionCopy, &QAction::triggered, this, [=]() {
		if (mCurrentEditor) {
			mCurrentEditor->copy();
		}
	});
	connect(mUi->actionPaste, &QAction::triggered, this, [=]() {
		if (mCurrentEditor) {
			mCurrentEditor->paste();
		}
	});
	connect(mUi->actionCut, &QAction::triggered, this, [=]() {
		if (mCurrentEditor) {
			mCurrentEditor->cut();
		}
	});
	connect(mUi->actionReplaceBy, &QAction::triggered, this, [=]() {
		if (mCurrentEditor && mCurrentEditor->supportsReplacingBy()) {
			mCurrentEditor->replaceBy();
		}
	});

	connect(mUi->actionFind, &QAction::triggered, this, [=]() {
		if (mCurrentEditor && mCurrentEditor->supportsSearching()) {
			mCurrentEditor->find();
		}
	});

	connect(mUi->actionFind_and_replace, &QAction::triggered, this, [=]() {
		if (mCurrentEditor && mCurrentEditor->supportsFindAndReplace()) {
			mCurrentEditor->findAndReplace();
		}
	});

	connect(mUi->actionUndo, &QAction::triggered, this, [this](){
		text::QScintillaTextEdit *area = dynamic_cast<text::QScintillaTextEdit *>(currentTab());
		if (area && mCurrentEditor->editorId() != twoDModelId) {
			area->undo();
			mUi->actionUndo->setEnabled(area->isUndoAvailable());
			mUi->actionRedo->setEnabled(area->isRedoAvailable());
		}
		else {
			mController->undo();
		}
	});
	connect(mUi->actionRedo, &QAction::triggered, this, [this](){
		text::QScintillaTextEdit *area = dynamic_cast<text::QScintillaTextEdit *>(currentTab());
		if (area && mCurrentEditor->editorId() != twoDModelId) {
			area->redo();
			mUi->actionUndo->setEnabled(area->isUndoAvailable());
			mUi->actionRedo->setEnabled(area->isRedoAvailable());
		}
		else {
			mController->redo();
		}
	});

	connect(mUi->actionPreferences, &QAction::triggered, this, &MainWindow::showPreferencesDialog);

	connect(mUi->actionShow_grid, &QAction::toggled, this, &MainWindow::showGrid);
	connect(mUi->actionShow_alignment, &QAction::toggled, this, &MainWindow::showAlignment);
	connect(mUi->actionSwitch_on_grid, &QAction::toggled, this, &MainWindow::switchGrid);
	connect(mUi->actionSwitch_on_alignment, &QAction::toggled, this, &MainWindow::switchAlignment);
	SettingsListener::listen("ShowGrid", mUi->actionShow_grid, &QAction::setChecked);
	SettingsListener::listen("ShowAlignment", mUi->actionShow_alignment, &QAction::setChecked);
	SettingsListener::listen("ActivateGrid", mUi->actionSwitch_on_grid, &QAction::setChecked);
	SettingsListener::listen("ActivateAlignment", mUi->actionSwitch_on_alignment, &QAction::setChecked);

	mUi->actionShow_all_text->setChecked(!qReal::SettingsManager::value("hideNonHardLabels").toBool());
	connect(mUi->actionShow_all_text, &QAction::triggered
			, [](bool checked) { SettingsManager::setValue("hideNonHardLabels", !checked); });

	connect(mUi->actionHelp, &QAction::triggered, this, &MainWindow::showHelp);
	mUi->actionAbout->setText(mUi->actionAbout->text()
			+ mProjectManager->toolManager().customizer()->windowTitle().remove(
			mProjectManager->toolManager().customizer()->productVersion()));
	connect(mUi->actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
	connect(mUi->actionOpenLogs, &QAction::triggered, this, &MainWindow::openLogs);

	connect(mUi->actionGesturesShow, &QAction::triggered, this, &MainWindow::showGestures);

	connect(mUi->actionFullscreen, &QAction::triggered, this, &MainWindow::fullscreen);
	connect(mUi->actionFullscreen, &QAction::changed, this, [=]() {
		const int indexOfFullscreen = mUi->viewToolbar->actions().indexOf(mUi->actionFullscreen);
		if (indexOfFullscreen > 0) {
			QAction * const separatorBefore = mUi->viewToolbar->actions()[indexOfFullscreen - 1];
			separatorBefore->setVisible(mUi->actionFullscreen->isVisible());
		}
	});

	connect(mFindReplaceDialog, &FindReplaceDialog::replaceClicked, &*mFindHelper, &FindManager::handleReplaceDialog);
	connect(mFindReplaceDialog, &FindReplaceDialog::findModelByName, &*mFindHelper, &FindManager::handleFindDialog);
	connect(mFindReplaceDialog, &FindReplaceDialog::chosenElement, &*mFindHelper, &FindManager::handleRefsDialog);

	SettingsListener::listen("PaletteRepresentation", this, &MainWindow::changePaletteRepresentation);
	SettingsListener::listen("PaletteIconsInARowCount", this, &MainWindow::changePaletteRepresentation);
	SettingsListener::listen("toolbarSize", this, &MainWindow::resetToolbarSize);
	SettingsListener::listen("pathToImages", this, &MainWindow::updatePaletteIcons);
	connect(mPreferencesDialog, &PreferencesDialog::settingsApplied, this, &qReal::MainWindow::applySettings);

	connect(&*mController, &Controller::canUndoChanged, mUi->actionUndo, &QAction::setEnabled);
	connect(&*mController, &Controller::canRedoChanged, mUi->actionRedo, &QAction::setEnabled);
	connect(&*mController, &Controller::modifiedChanged, &*mProjectManager, &ProjectManagerWrapper::setStackUnsaved);

	connect(mUi->tabs, &QTabWidget::currentChanged, this, &MainWindow::changeWindowTitle);
	connect(mUi->tabs, &QTabWidget::currentChanged, this, &MainWindow::sceneSelectionChanged);
	connect(&*mTextManager, &text::TextManager::textChanged, this, &MainWindow::setTextChanged);
	connect(&*mTextManager, &text::TextManager::textChanged, mUi->actionUndo, &QAction::setEnabled);

	connect(&*mProjectManager, &ProjectManager::afterOpen, mUi->paletteTree, &PaletteTree::refreshUserPalettes);
	connect(&*mProjectManager, &ProjectManager::closed, mUi->paletteTree, &PaletteTree::refreshUserPalettes);
	connect(&*mProjectManager, &ProjectManager::closed, &*mController, &Controller::projectClosed);

	connect(mUi->propertyEditor, &PropertyEditorView::shapeEditorRequested, this, static_cast<void (MainWindow::*)
			(const QPersistentModelIndex &, int, const QString &, bool)>(&MainWindow::openShapeEditor));
	connect(mUi->propertyEditor, &PropertyEditorView::textEditorRequested, this, &MainWindow::openQscintillaTextEditor);
	connect(mUi->propertyEditor, &PropertyEditorView::referenceListRequested, this, &MainWindow::openReferenceList);

	connect(mUi->menuPanels, &QMenu::aboutToShow, this, [=]() {
		mUi->menuPanels->clear();
		mUi->menuPanels->addActions(createPopupMenu()->actions());
	});

	addAction(mUi->actionHideBottomDocks);
	connect(mUi->actionHideBottomDocks, &QAction::triggered, this, &MainWindow::hideBottomDocks);

	setDefaultShortcuts();
}

void MainWindow::connectSystemEvents()
{
	connect(&*mErrorReporter, &ErrorReporter::informationAdded, &mFacade->events(), &SystemEvents::informationAdded);
	connect(&*mErrorReporter, &ErrorReporter::warningAdded, &mFacade->events(), &SystemEvents::warningAdded);
	connect(&*mErrorReporter, &ErrorReporter::errorAdded, &mFacade->events(), &SystemEvents::errorAdded);
	connect(&*mErrorReporter, &ErrorReporter::criticalAdded, &mFacade->events(), &SystemEvents::criticalAdded);

	connect(qobject_cast<QRealApplication *>(qApp), &QRealApplication::lowLevelEvent
			, &mFacade->events(), &SystemEvents::lowLevelEvent);
}

void MainWindow::initActionsFromSettings()
{
}

void MainWindow::registerMetaTypes()
{
	qRegisterMetaType<Id>();
	qRegisterMetaTypeStreamOperators<Id>();
	qRegisterMetaType<IdList>();
	qRegisterMetaTypeStreamOperators<IdList>();
}

void MainWindow::showFindDialog()
{
	mFindReplaceDialog->stateClear();
	mFindReplaceDialog->show();
}

QModelIndex MainWindow::rootIndex() const
{
	return mRootIndex;
}

MainWindow::~MainWindow()
{
	mUi->paletteTree->saveConfiguration();
	SettingsManager::instance()->saveData();
	SettingsListener::disconnectSource(this);
	delete mUi; mUi = nullptr;

	// TODO: This is a workaround for crash on macOS.
	// Seems like this crash is caused by memory corruption somewhere else.
	// If the statusBar with children is deleted before other controls, this helps.
	// delete statusBar();
	// ----------------


	if (mRestoreDefaultSettingsOnClose) {
		SettingsManager::clearSettings();
		SettingsManager::instance()->saveData();
	}
}

EditorManagerInterface &MainWindow::editorManager()
{
	return mFacade->editorManager();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (mScriptAPI) {
		mScriptAPI->abortEvaluation();
	}

	closeAllTabs();

	if (mUi->tabs->count() > 0)	{
		event->ignore();
		return;
	}

	mProjectManager->close();

	SettingsManager::setValue("maximized", isMaximized());
	SettingsManager::setValue("mainWindowGeometry", saveGeometry());

	QLOG_INFO() << "Closing main window...";
	emit mFacade->events().closedMainWindow();
}

void MainWindow::loadEditorPlugins()
{
	mUi->paletteTree->loadPalette(SettingsManager::value("PaletteRepresentation").toBool()
			, SettingsManager::value("PaletteIconsInARowCount").toInt()
			, &editorManager());
	SettingsManager::setValue("EditorsLoadedCount", editorManager().editors().count());
}

void MainWindow::clearSelectionOnTabs()
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		const EditorView * const tab = dynamic_cast<const EditorView *>(mUi->tabs->widget(i));
		if (tab != nullptr) {
			tab->scene()->clearSelection();
		}
	}
}

void MainWindow::adjustMinimapZoom(int zoom)
{
	mUi->minimapView->resetMatrix();
	mUi->minimapView->scale(0.01 * zoom, 0.01 * zoom);
}

void MainWindow::selectItemWithError(const Id &id)
{
	if (id == Id::rootId() || id.isNull()) {
		return;
	}

	Id graphicalId = id;
	if (!models().graphicalModelAssistApi().isGraphicalId(id)) {
		const IdList graphicalIds = models().graphicalModelAssistApi().graphicalIdsByLogicalId(id);
		graphicalId = graphicalIds.isEmpty() ? Id() : graphicalIds.at(0);
	}

	emit mFacade->events().ensureDiagramVisible();
	selectItemOrDiagram(graphicalId);
	setIndexesOfPropertyEditor(graphicalId);
	centerOn(graphicalId);

	Element * const element = getCurrentTab() ? getCurrentTab()->editorViewScene().getElem(graphicalId) : nullptr;
	graphicsUtils::AnimatedEffects::highlight(element);
}

void MainWindow::selectItem(const Id &id)
{
	if (id == Id::rootId()) {
		return;
	}

	setIndexesOfPropertyEditor(id);
	centerOn(id);
}

void MainWindow::selectItemOrDiagram(const Id &graphicalId)
{
	activateItemOrDiagram(graphicalId, true);
}

void MainWindow::activateItemOrDiagram(const QModelIndex &idx, bool setSelected)
{
	const QModelIndex parent = idx.parent();
	const int numTab = getTabIndex(idx);

	if (numTab != -1) {
		mUi->tabs->setCurrentIndex(numTab);
		const Id currentTabId = getCurrentTab()->editorViewScene().rootItemId();
		mProjectManager->toolManager().activeTabChanged(TabInfo(currentTabId, getCurrentTab()));
	} else {
		openNewTab(idx);
	}

	if (mUi->tabs->isEnabled()) {
		if (parent == models().graphicalModelAssistApi().rootIndex()) {
			getCurrentTab()->mutableMvIface().setRootIndex(idx);
		} else {
			getCurrentTab()->mutableMvIface().setRootIndex(parent);
			// select this item on diagram
			getCurrentTab()->scene()->clearSelection();
			const EditorViewScene *scene = static_cast<const EditorViewScene *>(getCurrentTab()->scene());
			Element * const e = scene->getElem(idx.data(roles::idRole).value<Id>());
			if (e) {
				if (setSelected) {
					e->setSelected(true);
				}
			} else {
				Q_ASSERT(false);
			}
		}
	}
}

void MainWindow::activateItemOrDiagram(const Id &id, bool setSelected)
{
	if (id.isNull()) {
		return;
	}

	if (models().graphicalModelAssistApi().isGraphicalId(id)) {
		activateItemOrDiagram(models().graphicalModelAssistApi().indexById(id), setSelected);
		return;
	}

	// id is logical ID
	const IdList graphicalIds = models().graphicalModelAssistApi().graphicalIdsByLogicalId(id);
	if (graphicalIds.count()) {
		activateItemOrDiagram(models().graphicalModelAssistApi().indexById(graphicalIds[0]), setSelected);
	}
}

void MainWindow::sceneSelectionChanged()
{
	if (!getCurrentTab()) {
		return;
	}
	const IdList selectedIds = getCurrentTab()->editorViewScene().selectedIds();

	if (selectedIds.length() != 1) {
		mUi->graphicalModelExplorer->setCurrentIndex(QModelIndex());
		mPropertyModel->clearModelIndexes();
	} else {
		const Id &singleSelected = selectedIds.first();
		setIndexesOfPropertyEditor(singleSelected);

		const QModelIndex index = models().graphicalModelAssistApi().indexById(singleSelected);
		if (index.isValid()) {
			mUi->graphicalModelExplorer->setCurrentIndex(index);
		}
	}
}

void MainWindow::refreshRecentProjectsList(const QString &fileName)
{
	QString previousString = SettingsManager::value("recentProjects").toString();
	QStringList previousList = previousString.split(";", QString::SkipEmptyParts);
	previousList.removeOne(fileName);
	if (!previousList.isEmpty() && (previousList.size() == mRecentProjectsLimit)) {
		previousList.removeLast();
	}

	previousString.clear();
	if (mRecentProjectsLimit > 0) {
		previousList.push_front(fileName);
		QStringListIterator iterator(previousList);
		while (iterator.hasNext()) {
			previousString = previousString + iterator.next() + ";";
		}
	}

	SettingsManager::setValue("recentProjects", previousString);
}

void MainWindow::openRecentProjectsMenu()
{
	mRecentProjectsMenu->clear();
	const QString stringList = SettingsManager::value("recentProjects").toString();
	QStringList recentProjects = stringList.split(";", QString::SkipEmptyParts);

	mRecentProjectsLimit = SettingsManager::value("recentProjectsLimit", mRecentProjectsLimit).toInt();
	while (recentProjects.size() > mRecentProjectsLimit) {
		recentProjects.pop_front();
	}

	for (const QString &projectPath : recentProjects) {
		mRecentProjectsMenu->addAction(projectPath);
		QObject::connect(mRecentProjectsMenu->actions().last(), &QAction::triggered
				, &*mProjectManager, [this, projectPath](){ mProjectManager->openExisting(projectPath);});
	}
}

void MainWindow::tryToSave()
{
	if(!mProjectManager->saveText() && !mProjectManager->saveOrSuggestToSaveAs()) {
		mErrorReporter->addWarning(tr("Could not save file, try to save it to another place"));
	}
}

void MainWindow::closeAllTabs()
{
	const int tabCount = mUi->tabs->count();
	QList<QWidget *> tabs;
	for (int i = 0; i < tabCount; i++) {
		tabs.append(mUi->tabs->widget(i));
	}
	for (auto && tab : tabs)
		closeTab(tab);
}

void MainWindow::setReference(const QStringList &data, const QPersistentModelIndex &index, const int &role)
{
	removeOldBackReference(index, role);
	setData(data.join(','), index, role);
	for (const QString &target : data) {
		if (!target.isEmpty()) {
			setBackReference(index, target);
		}
	}
}

bool MainWindow::windowsDarkThemeAvailiable()
{
	if ( QOperatingSystemVersion::current().majorVersion() == 10 )
	{
		return QOperatingSystemVersion::current().microVersion() >= 17763;
    }
    else if ( QOperatingSystemVersion::current().majorVersion() > 10 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MainWindow::windowsIsInDarkTheme()
{
    QSettings settings( 
		"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize"
		, QSettings::NativeFormat );
    return settings.value( "AppsUseLightTheme", 1 ).toInt() == 0;
}

void MainWindow::initPalette() {
	if (QSysInfo::productType() != "windows") return ;
	if (windowsDarkThemeAvailiable() && windowsIsInDarkTheme()) {
		auto palette = QApplication::palette();
		palette.setColor(QPalette::Window,QColor(53,53,53));
		palette.setColor(QPalette::WindowText,Qt::white);
		palette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
		palette.setColor(QPalette::Base,QColor(42,42,42));
		palette.setColor(QPalette::AlternateBase,QColor(66,66,66));
		palette.setColor(QPalette::ToolTipBase,Qt::white);
		palette.setColor(QPalette::ToolTipText,Qt::white);
		palette.setColor(QPalette::Text,Qt::white);
		palette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
		palette.setColor(QPalette::Dark,QColor(35,35,35));
		palette.setColor(QPalette::Shadow,QColor(20,20,20));
		palette.setColor(QPalette::Button,QColor(53,53,53));
		palette.setColor(QPalette::ButtonText,Qt::white);
		palette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
		palette.setColor(QPalette::BrightText,Qt::red);
		palette.setColor(QPalette::Link,QColor(42,130,218));
		palette.setColor(QPalette::Highlight,QColor(42,130,218));
		palette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
		palette.setColor(QPalette::HighlightedText,Qt::white);
		palette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));
		QApplication::setPalette(palette);
	}
}

void MainWindow::setData(const QString &data, const QPersistentModelIndex &index, const int &role)
{
	// const_cast here is ok, since we need to set data in a correct model, and
	// not going to use this index anymore.
	QAbstractItemModel * const model = const_cast<QAbstractItemModel *>(index.model());
	model->setData(index, data, role);
}

void MainWindow::print()
{
	const bool isEditorTab = getCurrentTab() != nullptr;

	if (isEditorTab) {
		QPrinter printer(QPrinter::ScreenResolution);
		QPrintDialog dialog(&printer, this);
		if (dialog.exec() == QDialog::Accepted) {
			QPainter painter(&printer);
			auto rectScene = getCurrentTab()->scene()->itemsBoundingRect();
			getCurrentTab()->scene()->render(&painter, QRectF(), rectScene);
		}
	} else {
		QsciScintillaBase *textTab = static_cast<QsciScintillaBase *>(currentTab());
		QsciPrinter printer(QPrinter::HighResolution);
		QPrintDialog dialog(&printer, this);
		if (dialog.exec() == QDialog::Accepted) {
			printer.printRange(textTab);
		}
	}
}

void MainWindow::makeSvg()
{
	QSvgGenerator newSvg;

	QString fileName = utils::QRealFileDialog::getSaveFileName("SaveDiagramAsSvg", this);
	if (fileName.isEmpty()) {
		return;
	}

	newSvg.setFileName(fileName);
	newSvg.setSize(QSize(800, 600));

	QPainter painter(&newSvg);
	getCurrentTab()->scene()->render(&painter);
}

void MainWindow::deleteElementFromDiagram(const Id &id)
{
	const bool isLogical = models().logicalModelAssistApi().isLogicalId(id);
	if (isLogical) {
		mUi->logicalModelExplorer->setCurrentIndex(models().logicalModelAssistApi().indexById(id));
		deleteFromLogicalExplorer();
	} else {
		mUi->graphicalModelExplorer->setCurrentIndex(models().graphicalModelAssistApi().indexById(id));
		deleteFromGraphicalExplorer();
	}
}

void MainWindow::reportOperation(const QFuture<void> &operation, const QString &description)
{
	ProgressDialog * const progressDialog = new ProgressDialog(this);
	progressDialog->reportOperation(operation, description);
}

QWidget *MainWindow::currentTab()
{
	return mUi->tabs->currentWidget();
}

QList<QWidget*> MainWindow::allTabs() const
{
	QList<QWidget*> result;
	for (int i = 0; i < mUi->tabs->count(); i++)
		result << mUi->tabs->widget(i);
	return result;
}

void MainWindow::openTab(QWidget *tab, const QString &title)
{
	if (mUi->tabs->indexOf(tab) == -1) {
		mUi->tabs->addTab(tab, title);
	}

	mUi->tabs->setCurrentWidget(tab);
}

void MainWindow::closeTab(QWidget *tab)
{
	mUi->tabs->setCurrentWidget(tab);
	closeTab(mUi->tabs->indexOf(tab));
}

QMap<QString, gui::PreferencesPage *> MainWindow::preferencesPages() const
{
	QMap<QString, PreferencesPage *> result;
	for (auto &&page : mPreferencesDialog->pages()) {
		result[page->objectName()] = page;
	}

	return result;
}

void MainWindow::closeStartTab()
{
	for (int i = 0; i < mUi->tabs->count(); ++i) {
		const StartWidget * widget = dynamic_cast<StartWidget *>(mUi->tabs->widget(i));
		if (widget) {
			mUi->tabs->removeTab(i);
		}
	}
}

void MainWindow::closeDiagramTab(const Id &id)
{
	const IdList graphicalIds = models().graphicalRepoApi().graphicalElements(id.type());
	if (!graphicalIds.isEmpty()) {
		// TODO: Why only for first graphical element?
		const QModelIndex index = models().graphicalModelAssistApi().indexById(graphicalIds[0]);
		for (int i = 0; i < mUi->tabs->count(); i++) {
			const EditorView * const tab = dynamic_cast<const EditorView *>(mUi->tabs->widget(i));
			if (tab != nullptr && tab->mvIface().rootIndex() == index) {
				mUi->tabs->removeTab(i);
			}
		}
	}
}

void MainWindow::deleteFromLogicalExplorer()
{
	const Id id = models().logicalModelAssistApi().idByIndex(mUi->logicalModelExplorer->currentIndex());
	if (!id.isNull()) {
		mController->executeGlobal((new RemoveElementsCommand(models()))->withLogicalItemToDelete({id}));
	}
}

void MainWindow::deleteFromGraphicalExplorer()
{
	const Id id = models().graphicalModelAssistApi().idByIndex(mUi->graphicalModelExplorer->currentIndex());
	if (!id.isNull()) {
		mController->executeGlobal((new RemoveElementsCommand(models()))->withItemsToDelete({id}));
	}
}

void MainWindow::changeWindowTitle()
{
	const QString windowTitle = mProjectManager->toolManager().customizer()->windowTitle();

	text::QScintillaTextEdit *area = dynamic_cast<text::QScintillaTextEdit *>(currentTab());
	if (area) {
		const QString filePath = mTextManager->path(area);
		setWindowTitle(windowTitle + " " + filePath);
	} else if (getCurrentTab()) {
		mProjectManager->refreshWindowTitleAccordingToSaveFile();
	} else {
		setWindowTitle(windowTitle);
	}
}

void MainWindow::registerEditor(EditorInterface &editor)
{
	editor.configure(*mUi->actionZoom_In, *mUi->actionZoom_Out, *mUi->actionUndo, *mUi->actionRedo, *mUi->actionCopy
			, *mUi->actionPaste, *mUi->actionCut, *mUi->actionFind, *mUi->actionFind_and_replace
			, *mUi->actionReplaceBy);
	connect(&editor.focusAction(), &QAction::triggered, this, [this, &editor]() {
		mCurrentEditor = &editor;
		updateUndoRedoState();
		const bool zoomingEnabled = editor.supportsZooming();
		mUi->actionZoom_In->setEnabled(zoomingEnabled);
		mUi->actionZoom_Out->setEnabled(zoomingEnabled);
		mUi->actionCopy->setEnabled(editor.supportsCopying());
		mUi->actionPaste->setEnabled(editor.supportsPasting());
		mUi->actionCut->setEnabled(editor.supportsCutting());
		mUi->actionFind->setEnabled(editor.supportsSearching());
		mUi->actionFind_and_replace->setEnabled(editor.supportsFindAndReplace());
		mUi->actionReplaceBy->setEnabled(editor.supportsReplacingBy());
		mController->setActiveModule(editor.editorId());
	});
}

void MainWindow::setTextChanged(text::QScintillaTextEdit *editor, bool changed)
{
	static QByteArray CHANGED_MARK = "*";
	const QString windowTitle = mProjectManager->toolManager().customizer()->windowTitle();
	const QString chIndicator = changed ? CHANGED_MARK : "";
	const QString filePath = mTextManager->path(editor);
	setWindowTitle(windowTitle + " " + chIndicator + filePath);
	const int index = mUi->tabs->indexOf(editor);
	mUi->tabs->setTabText(index, mUi->tabs->tabText(index).remove(CHANGED_MARK, Qt::CaseInsensitive) + chIndicator);
}

void MainWindow::removeReferences(const Id &id)
{
	models().logicalModelAssistApi().removeReferencesTo(id);
	models().logicalModelAssistApi().removeReferencesFrom(id);
}

void MainWindow::showAbout() const
{
	QDesktopServices::openUrl(QUrl(mProjectManager->toolManager().customizer()->aboutText()));
}

void MainWindow::showHelp()
{
	QDesktopServices::openUrl(QUrl("https://help.trikset.com/"));
}

void MainWindow::openLogs() const
{
	QUrl url("file:///" + qReal::PlatformInfo::invariantSettingsPath("pathToLogs"));
	bool result = QDesktopServices::openUrl(url);
	Q_UNUSED(result);
}

bool MainWindow::unloadPlugin(const QString &pluginName)
{
	if (editorManager().editors().contains(Id(pluginName))) {
		/* Delete and create palette tree for correct unloading plugin
		 * and for correct completion application.*/
		mUi->paletteTree->deletePaletteTree();
		mUi->paletteTree->createPaletteTree();

		const QString error = editorManager().unloadPlugin(pluginName);
		if (!error.isEmpty()) {
			QMessageBox::warning(this, tr("Error"), tr("Plugin unloading failed: ") + error);
			return false;
		}
	}
	return true;
}

bool MainWindow::loadPlugin(const QString &fileName, const QString &pluginName)
{
	const QString error = editorManager().loadPlugin(fileName);
	if (!error.isEmpty()) {
		QMessageBox::warning(this, tr("Error"), tr("Plugin loading failed: ") + error);
		return false;
	}

	for (const Id &diagram : editorManager().diagrams(Id(pluginName))) {
		mUi->paletteTree->addEditorElements(editorManager(), Id(pluginName), diagram);
	}

	mUi->paletteTree->initDone();
	return true;
}

bool MainWindow::pluginLoaded(const QString &pluginName)
{
	return editorManager().editors().contains(Id(pluginName));
}

EditorView * MainWindow::getCurrentTab() const
{
	return dynamic_cast<EditorView *>(mUi->tabs->currentWidget());
}

bool MainWindow::isCurrentTabShapeEdit() const
{
	return dynamic_cast<ShapeEdit *>(mUi->tabs->currentWidget()) != nullptr;
}

void MainWindow::closeCurrentTab()
{
	if (mUi->tabs->currentIndex() >= 0) {
		closeTab(mUi->tabs->currentIndex());
	}
}

void MainWindow::closeTab(int index)
{
	QWidget * const widget = mUi->tabs->widget(index);
	bool isClosed = false;

	if (auto const diagram = dynamic_cast<EditorView *>(widget)) {
		const Id diagramId = diagram->editorViewScene().rootItemId();
		if (diagramId.type() == qReal::Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode")) {
			isClosed = mProjectManager->suggestToSaveChangesOrCancel();
		} else if (diagramId.type() == qReal::Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram")) {
			if (mController->isUnsaved(diagramId.toString())) {
				mProjectManager->setUnsavedIndicator(true);
			}
			isClosed = true;
		}

		if (isClosed) {
			mController->moduleClosed(diagramId.toString());
			emit mFacade->events().diagramClosed(diagramId);
		}
	} else if (auto const start = dynamic_cast<StartWidget *>(widget)) {
		isClosed = true;
	} else if (auto const gesture = dynamic_cast<gestures::GesturesWidget *>(widget)) {
		isClosed = true;
	} else if (auto const possibleCodeTab = dynamic_cast<text::QScintillaTextEdit *>(widget)) {
		if (mTextManager->suggestToSaveCode(possibleCodeTab) && mTextManager->unbindCode(possibleCodeTab)) {
			isClosed = true;
			emit mFacade->events().codeTabClosed(QFileInfo(mTextManager->path(possibleCodeTab)));
		}
	} else {
		QLOG_ERROR() << "Unknown type of tab " << widget->objectName();
		// TODO: process other tabs
		// TODO: Are there any other tabs?
	}

	if (isClosed)
	{
		mUi->tabs->removeTab(index);
		delete widget;
	}
}

void MainWindow::showPreferencesDialog()
{
	if (mPreferencesDialog->exec() == QDialog::Accepted) {
		mProjectManager->toolManager().updateSettings();
	}

	mProjectManager->reinitAutosaver();
}

void MainWindow::openSettingsDialog(const QString &tab)
{
	mPreferencesDialog->switchCurrentPage(tab);
	showPreferencesDialog();
}

// TODO: Unify overloads.
void MainWindow::openShapeEditor(
		const QPersistentModelIndex &index
		, int role
		, const QString &propertyValue
		, bool useTypedPorts
		)
{
	ShapeEdit *shapeEdit = new ShapeEdit(dynamic_cast<models::details::LogicalModel *>(models().logicalModel())
			, index, role, useTypedPorts);
	if (!propertyValue.isEmpty()) {
		shapeEdit->load(propertyValue);
	}

	// Here we are going to actually modify model to set a value of a shape.
	QAbstractItemModel *model = const_cast<QAbstractItemModel *>(index.model());
	model->setData(index, propertyValue, role);
	connect(shapeEdit, &ShapeEdit::shapeSaved, this, &MainWindow::setData);

	mUi->tabs->addTab(shapeEdit, tr("Shape Editor"));
	mUi->tabs->setCurrentWidget(shapeEdit);
}

// This method is for Interpreter.
void MainWindow::openShapeEditor(const Id &id
		, const QString &propertyValue
		, const EditorManagerInterface *editorManagerProxy
		, bool useTypedPorts)
{
	ShapeEdit *shapeEdit = new ShapeEdit(id, *editorManagerProxy, models().graphicalRepoApi(), this, getCurrentTab()
		, useTypedPorts);
	if (!propertyValue.isEmpty()) {
		shapeEdit->load(propertyValue);
	}

	mUi->tabs->addTab(shapeEdit, tr("Shape Editor"));
	mUi->tabs->setCurrentWidget(shapeEdit);
}

void MainWindow::openQscintillaTextEditor(const QPersistentModelIndex &index, const int role
		, const QString &propertyValue)
{
	text::QScintillaTextEdit *textEdit = new text::QScintillaTextEdit(index, role);
	textEdit->setCurrentLanguage(text::Languages::python());

	if (!propertyValue.isEmpty()) {
		textEdit->setText(propertyValue.toUtf8());
	}

	connect(textEdit, &text::QScintillaTextEdit::textSaved, this, &MainWindow::setData);

	mUi->tabs->addTab(textEdit, tr("Text Editor"));
	mUi->tabs->setCurrentWidget(textEdit);
}

void MainWindow::openShapeEditor()
{
	ShapeEdit * const shapeEdit = new ShapeEdit;
	mUi->tabs->addTab(shapeEdit, tr("Shape Editor"));
	mUi->tabs->setCurrentWidget(shapeEdit);
}

void MainWindow::openReferenceList(const QPersistentModelIndex &index
		, const QString &referenceType,	const QString &propertyValue, int role)
{
	ReferenceList referenceList(this, index, referenceType, propertyValue.split(',', QString::SkipEmptyParts), role);
	connect(&referenceList, &ReferenceList::referenceSet, this, &MainWindow::setReference);
	referenceList.exec();
}

void MainWindow::centerOn(const Id &id)
{
	if (id.isNull() || editorManager().isDiagramNode(id)) {
		return;
	}

	EditorView* const view = getCurrentTab();
	if (!view) {
		return;
	}

	EditorViewScene* const scene = dynamic_cast<EditorViewScene*>(view->scene());
	Element* const element = scene->getElem(id);

	scene->clearSelection();
	if (element) {
		element->setSelected(true);
		view->ensureElementVisible(element);
	}
}

void MainWindow::propertyEditorScrollTo(const QModelIndex &index)
{
	mUi->propertyEditor->scrollTo(index);
}

void MainWindow::graphicalModelExplorerClicked(const QModelIndex &index)
{
	const Id id = models().graphicalModelAssistApi().idByIndex(index);
	setIndexesOfPropertyEditor(id);
	openNewTab(index);
	centerOn(id);
}

void MainWindow::logicalModelExplorerClicked(const QModelIndex &index)
{
	const Id logicalId = models().logicalModelAssistApi().idByIndex(index);
	IdList graphicalIds = models().graphicalModelAssistApi().graphicalIdsByLogicalId(logicalId);
	if (!graphicalIds.empty()) {
		// By now we will select first graphical representation of selected element.
		// In the future it may be needed to make this more intellectual, like
		// selecting the representation in current tab.
		const Id graphicalId = graphicalIds.first();
		const QModelIndex graphicalIndex = models().graphicalModelAssistApi().indexById(graphicalId);
		graphicalModelExplorerClicked(graphicalIndex);
	} else {
		setIndexesOfPropertyEditor(logicalId);
		EditorView* const view = getCurrentTab();
		if (view != nullptr) {
			EditorViewScene* const scene = dynamic_cast<EditorViewScene*>(view->scene());
			scene->clearSelection();
		}
	}
}

void MainWindow::openNewTab(const QModelIndex &arg)
{
	QModelIndex index = arg;
	while (index.parent() != QModelIndex()) {
		index = index.parent();
	}

	int tabNumber = -1;
	for (int i = 0; i < mUi->tabs->count(); ++i) {
		EditorView *tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab != nullptr && tab->mvIface().rootIndex() == index) {
			tabNumber = i;
			break;
		}
	}

	if (tabNumber != -1) {
		mUi->tabs->setCurrentIndex(tabNumber);
	} else {
		const Id diagramId = models().graphicalModelAssistApi().idByIndex(index);
		EditorView * const view = new EditorView(models(), *controller(), *mSceneCustomizer, diagramId, this);
		view->mutableScene().enableMouseGestures(qReal::SettingsManager::value("gesturesEnabled").toBool());
		SettingsListener::listen("gesturesEnabled", &(view->mutableScene()), &EditorViewScene::enableMouseGestures);
		SettingsListener::listen("gesturesEnabled", mUi->actionGesturesShow ,&QAction::setEnabled);
		mController->moduleOpened(diagramId.toString());
		initCurrentTab(view, index);
		mUi->tabs->addTab(view, index.data().toString());
		mUi->tabs->setCurrentWidget(view);

		// Focusing on scene top left corner
		view->centerOn(view->scene()->sceneRect().topLeft());
	}

	// changing of palette active editor
	if (SettingsManager::value("PaletteTabSwitching").toBool()) {
		int i = 0;
		for (const QString &name : mUi->paletteTree->editorsNames()) {
			const Id id = models().graphicalModelAssistApi().idByIndex(index);
			const Id diagramId = Id(id.editor(), id.diagram());
			const QString diagramName = editorManager().friendlyName(diagramId);
			if (diagramName == name) {
				mUi->paletteTree->setComboBoxIndex(i);
				break;
			}

			++i;
		}
	}
}

void MainWindow::openFirstDiagram()
{
	const Id rootId = models().graphicalModelAssistApi().rootId();
	const IdList rootIds = models().graphicalModelAssistApi().children(rootId);
	if (rootIds.count() == 0) {
		return;
	}

	for (const Id &id : rootIds) {
		if (models().graphicalRepoApi().isGraphicalElement(id)) {
			openNewTab(models().graphicalModelAssistApi().indexById(id));
			break;
		}
	}
}

void MainWindow::initCurrentTab(EditorView *const tab, const QModelIndex &rootIndex)
{
	if (!tab) {
		return;
	}

	const QModelIndex index = rootIndex;

	tab->mutableMvIface().configure(models().graphicalModelAssistApi()
			, models().logicalModelAssistApi(), models().exploser());

	tab->mutableMvIface().setModel(models().graphicalModel());
	if (tab->sceneRect() == QRectF(0, 0, 0, 0)) {
		tab->setSceneRect(0, 0, 1, 1);
	}

	tab->mutableMvIface().setLogicalModel(models().logicalModel());
	tab->mutableMvIface().setRootIndex(index);

	// Connect after setModel etc. because of signal selectionChanged was sent when there were old indexes
	connect(&tab->editorViewScene(), &EditorViewScene::selectionChanged, this, &MainWindow::sceneSelectionChanged);
	connect(mUi->actionAntialiasing, &QAction::toggled, tab, &EditorView::toggleAntialiasing);
	connect(models().graphicalModel(), &QAbstractItemModel::rowsAboutToBeMoved
			, &tab->mvIface(), &EditorViewMViface::rowsAboutToBeMoved);
	connect(models().graphicalModel(), &QAbstractItemModel::rowsMoved, &tab->mvIface(), &EditorViewMViface::rowsMoved);
	connect(tab, &EditorView::rootElementRemoved, this
			, static_cast<bool (MainWindow::*)(const QModelIndex &)>(&MainWindow::closeTab));
	connect(&tab->editorViewScene(), &EditorViewScene::goTo, this, [=](const Id &id) { activateItemOrDiagram(id); });
	connect(&tab->editorViewScene(), &EditorViewScene::refreshPalette, this, &MainWindow::loadEditorPlugins);
	connect(&tab->editorViewScene(), &EditorViewScene::openShapeEditor, this, static_cast<void (MainWindow::*)
			(const Id &, const QString &, const EditorManagerInterface *, bool)>(&MainWindow::openShapeEditor));

	setShortcuts(tab);

	tab->mutableScene().initNodes();
}

void MainWindow::setShortcuts(EditorView * const tab)
{
	EditorViewScene *scene = dynamic_cast<EditorViewScene *>(tab->scene());
	if (!scene) {
		return;
	}

	// Add shortcut - select all
	QAction *selectAction = new QAction(tab);
	selectAction->setShortcut(QKeySequence(QKeySequence::SelectAll));
	connect(selectAction, &QAction::triggered, scene, &EditorViewScene::selectAll);
	tab->addAction(selectAction);
}

void MainWindow::setDefaultShortcuts()
{
	QAction *closeCurrentTabAction = new QAction(this);
	QAction *closeAllTabsAction = new QAction(this);
	connect(closeCurrentTabAction, &QAction::triggered, this, &MainWindow::closeCurrentTab);
	connect(closeAllTabsAction, &QAction::triggered, this, &MainWindow::closeAllTabs);
	addAction(closeCurrentTabAction);
	addAction(closeAllTabsAction);

	closeCurrentTabAction->setShortcuts(QList<QKeySequence>()
			<< QKeySequence(Qt::CTRL + Qt::Key_W)
			<< QKeySequence(Qt::CTRL + Qt::Key_F4));
	closeAllTabsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_W));

	mUi->actionUndo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
	mUi->actionRedo->setShortcuts(QList<QKeySequence>()
			<< QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z)
			<< QKeySequence(Qt::CTRL + Qt::Key_Y));

	mUi->actionZoom_In->setShortcuts(QList<QKeySequence>()
			<< QKeySequence(Qt::CTRL + Qt::Key_Equal)
			<< QKeySequence(Qt::CTRL + Qt::Key_Plus));
	mUi->actionZoom_Out->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));

	mUi->actionFind->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
	mUi->actionFind_and_replace->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));

	mUi->actionNewProject->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	mUi->actionNew_Diagram->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
	HotKeyManager::setCommand("File.NewDiagram", tr("New diagram"), mUi->actionNew_Diagram);

	// TODO: bind Ctrl+P to print when it will be repaired

	HotKeyManager::setCommand("File.Open", tr("Open project"), mUi->actionOpen);
	HotKeyManager::setCommand("File.Save", tr("Save project"), mUi->actionSave);
	HotKeyManager::setCommand("File.SaveAs", tr("Save project as"), mUi->actionSave_as);
	HotKeyManager::setCommand("File.NewProject", tr("New project"), mUi->actionNewProject);
	HotKeyManager::setCommand("Editor.Undo", tr("Undo"), mUi->actionUndo);
	HotKeyManager::setCommand("Editor.Redo", tr("Redo"), mUi->actionRedo);
	HotKeyManager::setCommand("Editor.ZoomIn", tr("Zoom In"), mUi->actionZoom_In);
	HotKeyManager::setCommand("Editor.ZoomOut", tr("Zoom Out"), mUi->actionZoom_Out);
	HotKeyManager::setCommand("Editor.CloseCurrentTab", tr("Close current tab"), closeCurrentTabAction);
	HotKeyManager::setCommand("Editor.CloseAllTabs", tr("Close all tabs"), closeAllTabsAction);
	HotKeyManager::setCommand("Editor.Print", tr("Print"), mUi->actionPrint);
	HotKeyManager::setCommand("Editor.Find", tr("Find"), mUi->actionFind);
	HotKeyManager::setCommand("Editor.FindAndReplace", tr("Find and replace"), mUi->actionFind_and_replace);
	HotKeyManager::setCommand("Editor.ToggleTitles", tr("Show all text"), mUi->actionShow_all_text);
	HotKeyManager::setCommand("View.ToggleErrorReporter", tr("Toggle errors panel")
			, mUi->errorDock->toggleViewAction());
}

void MainWindow::currentTabChanged(int newIndex)
{
	switchToTab(newIndex);
	mUi->minimapView->changeSource(newIndex);

	const bool isEditorTab = getCurrentTab();
	const bool isStartTab = dynamic_cast<StartWidget *>(mUi->tabs->widget(newIndex));
	const bool isGesturesTab = dynamic_cast<gestures::GesturesWidget *>(mUi->tabs->widget(newIndex));
	const bool isDecorativeTab = isStartTab || isGesturesTab;

	mUi->actionSave->setEnabled(!isDecorativeTab);
	mUi->actionSave_as->setEnabled(!isDecorativeTab);
	mUi->actionSave_diagram_as_a_picture->setEnabled(isEditorTab);
	mUi->actionPrint->setEnabled(!isDecorativeTab);
	mUi->actionFind->setEnabled(!isDecorativeTab);
	mUi->actionFind_and_replace->setEnabled(!isDecorativeTab);
	mUi->actionGesturesShow->setEnabled(qReal::SettingsManager::value("gesturesEnabled").toBool());

	updateUndoRedoState();

	if (isEditorTab) {
		const Id currentTabId = getCurrentTab()->mvIface().rootId();
		mProjectManager->toolManager().activeTabChanged(TabInfo(currentTabId, getCurrentTab()));
	} else if (text::QScintillaTextEdit * const text = dynamic_cast<text::QScintillaTextEdit *>(currentTab())) {
		mProjectManager->toolManager().activeTabChanged(TabInfo(mTextManager->path(text), text));
	} else {
		mProjectManager->toolManager().activeTabChanged(TabInfo(currentTab()));
	}

	emit rootDiagramChanged();
}

void MainWindow::switchToTab(int index)
{
	if (index != -1) {
		mUi->tabs->setEnabled(true);
		EditorView *editorView = getCurrentTab();

		if (editorView) {
			getCurrentTab()->mutableMvIface().setModel(models().graphicalModel());
			getCurrentTab()->mutableMvIface().setLogicalModel(models().logicalModel());
			mRootIndex = editorView->mvIface().rootIndex();
		}
	} else {
		mUi->tabs->setEnabled(false);
	}
}

void MainWindow::updateTabName(const Id &id)
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView * const tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab && (tab->mvIface().rootIndex() == models().graphicalModelAssistApi().indexById(id))) {
			mUi->tabs->setTabText(i, models().graphicalModelAssistApi().name(id));
			return;
		}
	}
}

bool MainWindow::closeTab(const QModelIndex &graphicsIndex)
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView * const tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab && tab->mvIface().rootIndex() == graphicsIndex) {
			mUi->tabs->setCurrentWidget(tab);
			closeTab(i);
			return true;
		}
	}

	return false;
}

models::Models &MainWindow::models()
{
	return mFacade->models();
}

Controller *MainWindow::controller() const
{
	return &*mController;
}

PropertyEditorView *MainWindow::propertyEditor() const
{
	return mUi->propertyEditor;
}

QTreeView *MainWindow::graphicalModelExplorer() const
{
	return mUi->graphicalModelExplorer;
}

QTreeView *MainWindow::logicalModelExplorer() const
{
	return mUi->logicalModelExplorer;
}

PropertyEditorModel &MainWindow::propertyModel()
{
	return *mPropertyModel;
}

ToolPluginManager &MainWindow::toolManager()
{
	return mProjectManager->toolManager();
}

void MainWindow::showGrid(bool isChecked)
{
	SettingsManager::setValue("ShowGrid", isChecked);
	setShowGrid(isChecked);
}

void MainWindow::showAlignment(bool isChecked)
{
	SettingsManager::setValue("ShowAlignment", isChecked);
	setShowAlignment(isChecked);
}

void MainWindow::switchGrid(bool isChecked)
{
	SettingsManager::setValue("ActivateGrid", isChecked);
	setSwitchGrid(isChecked);
}

void MainWindow::switchAlignment(bool isChecked)
{
	SettingsManager::setValue("ActivateAlignment", isChecked);
	setSwitchAlignment(isChecked);
}

void MainWindow::setShowGrid(bool isChecked)
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView *const tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab != nullptr) {
			tab->setDrawSceneGrid(isChecked);
		}
	}
}

void MainWindow::setShowAlignment(bool isChecked)
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView * const tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab != nullptr) {
			const QList<QGraphicsItem *> list = tab->scene()->items();
			for (QGraphicsItem * const item : list) {
				NodeElement * const nodeItem = dynamic_cast<NodeElement*>(item);
				if (nodeItem != nullptr) {
					nodeItem->showAlignment(isChecked);
				}
			}
		}
	}
}

void MainWindow::setSwitchGrid(bool isChecked)
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView  const *tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab != nullptr) {
			const QList<QGraphicsItem *> list = tab->scene()->items();
			for (QGraphicsItem *const item : list) {
				NodeElement * const nodeItem = dynamic_cast<NodeElement*>(item);
				if (nodeItem != nullptr) {
					nodeItem->switchGrid(isChecked);
				}
			}
		}
	}
}

void MainWindow::setSwitchAlignment(bool isChecked)
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView *const tab = (dynamic_cast<EditorView *>(mUi->tabs->widget(i)));
		if (tab != nullptr) {
			const QList<QGraphicsItem *> list = tab->scene()->items();
			for (QGraphicsItem * const item : list) {
				NodeElement * const nodeItem = dynamic_cast<NodeElement*>(item);
				if (nodeItem != nullptr) {
					nodeItem->switchAlignment(isChecked);
				}
			}
		}
	}
}

void MainWindow::showGestures()
{
	if (!getCurrentTab()) {
		return;
	}

	QWidget * const gesturesPainter = getCurrentTab()->mutableScene().gesturesPainterWidget();
	if (gesturesPainter) {
		mUi->tabs->addTab(gesturesPainter, tr("Gestures Show"));
		mUi->tabs->setCurrentWidget(gesturesPainter);
	}
}

void MainWindow::createDiagram(const QString &idString)
{
	closeStartTab();
	const Id id = Id::loadFromString(idString);
	Id created;
	if (editorManager().isNodeOrEdge(id.type())) {
		created = models().graphicalModelAssistApi().createElement(Id::rootId(), id);
	} else {
		// It is a group
		const ElementInfo toCreate(id, Id(), Id::rootId(), Id::rootId(), {}, {}, Id(), false);
		CreatePatternCommand createGroupCommand(models(), {toCreate});
		createGroupCommand.redo();
		created = createGroupCommand.rootId();
	}

	if (created.isNull()) {
		return;
	}

	const QModelIndex index = models().graphicalModelAssistApi().indexById(created);
	mUi->graphicalModelExplorer->setCurrentIndex(index);
	const Id logicalIdCreated = models().graphicalModelAssistApi().logicalId(created);
	const QModelIndex logicalIndex = models().logicalModelAssistApi().indexById(logicalIdCreated);
	mUi->logicalModelExplorer->setCurrentIndex(logicalIndex);

	openNewTab(index);
}

bool MainWindow::createProject(const QString &diagramIdString)
{
	if (!mProjectManager->openEmptyWithSuggestToSaveChanges()) {
		return false;
	}
	createDiagram(diagramIdString);
	return true;
}

void MainWindow::createProject()
{
	const Id theOnlyDiagram = editorManager().theOnlyDiagram();
	if (theOnlyDiagram.isNull()) {
		SuggestToCreateProjectDialog dialog(editorManager(), this);
		connect(&dialog, &SuggestToCreateProjectDialog::diagramSelected, this
				, static_cast<bool (MainWindow::*)(const QString &)>(&MainWindow::createProject));
		dialog.exec();
	} else {
		const Id editor = editorManager().editors()[0];
		const QString diagramIdString = editorManager().diagramNodeNameString(editor, theOnlyDiagram);
		createProject(diagramIdString);
	}
}

int MainWindow::getTabIndex(const QModelIndex &index)
{
	for (int i = 0; i < mUi->tabs->count(); ++i) {
		EditorView * const editor = dynamic_cast<EditorView *>(mUi->tabs->widget(i));
		if (!editor) {
			continue;
		}
		if (index.parent() == editor->mvIface().rootIndex()) {
			return i;
		}
	}
	return -1;
}

void MainWindow::setIndexesOfPropertyEditor(const Id &id)
{
	if (models().graphicalModelAssistApi().isGraphicalId(id)) {
		const Id logicalId = models().graphicalModelAssistApi().logicalId(id);
		const QModelIndex logicalIndex = models().logicalModelAssistApi().indexById(logicalId);
		const QModelIndex graphicalIndex = models().graphicalModelAssistApi().indexById(id);
		mPropertyModel->setModelIndexes(logicalIndex, graphicalIndex);
	} else if (models().logicalModelAssistApi().isLogicalId(id)) {
		const QModelIndex logicalIndex = models().logicalModelAssistApi().indexById(id);
		mPropertyModel->setModelIndexes(logicalIndex, QModelIndex());
	} else {
		mPropertyModel->clearModelIndexes();
	}
}

void MainWindow::highlight(const Id &graphicalId, bool exclusive, const QColor &color)
{
	highlightCode(models().graphicalModelAssistApi().logicalId(graphicalId), true);

	for (int i = 0; i < mUi->tabs->count(); ++i) {
		EditorView * const view = dynamic_cast<EditorView *>(mUi->tabs->widget(i));
		if (!view) {
			continue;
		}
		EditorViewScene * const scene = dynamic_cast<EditorViewScene *>(view->scene());
		const Element * const element = scene->getElem(graphicalId);
		if (element) {
			scene->highlight(graphicalId, exclusive, color);
			view->ensureElementVisible(element, 0, 0);
		}
	}
}

void MainWindow::highlightCode(Id const &graphicalId, bool highlight)
{
	text::QScintillaTextEdit *area = dynamic_cast<text::QScintillaTextEdit *>(currentTab());

	if (area) {
		if (highlight) {
			QString const filePath = mTextManager->path(area);
			QPair<int, int> const interval = mTextManager->codeBlockManager().intervalById(filePath, graphicalId);
			area->setMarkerBackgroundColor(QColor::fromRgb(0, 255, 0));
			area->markerDefine(text::QScintillaTextEdit::Background, text::QScintillaTextEdit::SC_MARK_BACKGROUND);
			for (int i = interval.first; i <= interval.second; i++) {
				area->markerAdd(i - 1, text::QScintillaTextEdit::SC_MARK_BACKGROUND);
			}
		} else {
			area->markerDeleteAll();
		}
	}
}

void MainWindow::updateUndoRedoState()
{
	text::QScintillaTextEdit * const text = dynamic_cast<text::QScintillaTextEdit *>(currentTab());
	if (mCurrentEditor == nullptr) {
		return;
	}
	if (mCurrentEditor->editorId() != twoDModelId && text != nullptr) {
		mUi->actionRedo->setEnabled(text->isRedoAvailable());
		mUi->actionUndo->setEnabled(text->isUndoAvailable());
	}
	else {
		mUi->actionRedo->setEnabled(mController->canRedo());
		mUi->actionUndo->setEnabled(mController->canUndo());
	}
}

void MainWindow::dehighlight(const Id &graphicalId)
{
	highlightCode(models().graphicalModelAssistApi().logicalId(graphicalId), false);

	for (int i = 0; i < mUi->tabs->count(); ++i) {
		EditorView * const view = dynamic_cast<EditorView *>(mUi->tabs->widget(i));
		if (!view) {
			continue;
		}

		EditorViewScene * const scene = dynamic_cast<EditorViewScene *>(view->scene());

		if (graphicalId.isNull()) {
			scene->dehighlight();
		} else {
			scene->dehighlight(graphicalId);
		}

		for (text::QScintillaTextEdit *area : mTextManager->code(view->mvIface().rootId())) {
			if (mTextManager->isDefaultPath(mTextManager->path(area))) {
				area->markerDeleteAll();
			}
		}
	}
}

void MainWindow::dehighlight()
{
	dehighlight(Id());
}

ErrorReporterInterface *MainWindow::errorReporter()
{
	return &*mErrorReporter;
}

void MainWindow::updatePaletteIcons()
{
	mUi->graphicalModelExplorer->viewport()->update();
	mUi->logicalModelExplorer->viewport()->update();

	const Id currentId = mUi->paletteTree->currentEditor();
	loadEditorPlugins();

	mUi->paletteTree->setActiveEditor(currentId);
	mUi->paletteTree->setComboBox(currentId);
}

void MainWindow::applySettings()
{
	for (int i = 0; i < mUi->tabs->count(); i++) {
		EditorView * const tab = dynamic_cast<EditorView *>(mUi->tabs->widget(i));
		EditorViewScene *scene = tab ? dynamic_cast <EditorViewScene *>(tab->scene()) : nullptr;
		if (scene) {
			scene->updateEdgeElements();
			scene->invalidate();
		}
	}
}

void MainWindow::resetToolbarSize(int size)
{
	for (QToolBar * const bar : toolBars()) {
		bar->setIconSize(QSize(size, size));
	}
}

void MainWindow::setBackReference(const QPersistentModelIndex &index, const QString &data)
{
	Id id = Id::loadFromString(data);
	Id indexId = models().logicalModelAssistApi().idByIndex(index);
	models().logicalRepoApi().setBackReference(id, indexId);
}

void MainWindow::removeOldBackReference(const QPersistentModelIndex &index, const int role)
{
	QStringList data = index.data(role).toString().split(',', QString::SkipEmptyParts);

	for (const QString &reference : data) {
		Id id = Id::loadFromString(reference);
		Id indexId = models().logicalModelAssistApi().idByIndex(index);
		models().logicalRepoApi().removeBackReference(id, indexId);
	}
}

void MainWindow::hideDockWidget(QDockWidget *dockWidget, const QString &name)
{
	mDocksVisibility[name] = !dockWidget->isHidden();
	if (mDocksVisibility[name]) {
		dockWidget->hide();
	}
}

void MainWindow::showDockWidget(QDockWidget *dockWidget, const QString &name)
{
	if (mDocksVisibility[name]) {
		dockWidget->show();
	}
}

void MainWindow::fullscreen()
{
	mIsFullscreen = !mIsFullscreen;

	if (mIsFullscreen) {
		hideDockWidget(mUi->minimapDock, "minimap");
		hideDockWidget(mUi->graphicalModelDock, "graphicalModel");
		hideDockWidget(mUi->logicalModelDock, "logicalModel");
		hideDockWidget(mUi->propertyDock, "propertyEditor");
		hideDockWidget(mUi->errorDock, "errorReporter");

		mUi->actionFullscreen->setIcon(QIcon(":/mainWindow/images/unFullScreen.svg"));
	} else {
		showDockWidget(mUi->minimapDock, "minimap");
		showDockWidget(mUi->graphicalModelDock, "graphicalModel");
		showDockWidget(mUi->logicalModelDock, "logicalModel");
		showDockWidget(mUi->propertyDock, "propertyEditor");
		showDockWidget(mUi->errorDock, "errorReporter");

		mUi->actionFullscreen->setIcon(QIcon(":/mainWindow/images/fullScreen.svg"));
	}
	for (QDockWidget * const dock : mAdditionalDocks) {
		if (mIsFullscreen) {
			hideDockWidget(dock, dock->windowTitle());
		} else {
			showDockWidget(dock, dock->windowTitle());
		}
	}

	if (mIsFullscreen) {
		mLastTabBarIndexes.clear();
		for (QTabBar * const bar : findChildren<QTabBar *>()) {
			if (bar->objectName().isEmpty()) {  // Else we can modify the central tab widget`s current index
				mLastTabBarIndexes[bar] = bar->currentIndex();
			}
		}
	} else {
		for (QTabBar * const bar : findChildren<QTabBar *>()) {
			if (mLastTabBarIndexes.contains(bar)) {
				bar->setCurrentIndex(mLastTabBarIndexes[bar]);
			}
		}
	}
}

void MainWindow::hideBottomDocks()
{
	for (QDockWidget *dock : findChildren<QDockWidget *>()) {
		if (dockWidgetArea(dock) == Qt::BottomDockWidgetArea) {
			dock->hide();
		}
	}
}

QString MainWindow::getNextDirName(const QString &name)
{
	QStringList parts = name.split("_");
	bool isInt = false;
	int version = parts.last().toInt(&isInt);

	if (parts.size() < 2 || !isInt) {
		return name + "_2";
	}

	parts.last() = QString::number(++version);
	return parts.join("_");
}

Id MainWindow::activeDiagram() const
{
	return getCurrentTab() ? getCurrentTab()->mvIface().rootId() : Id();
}

IdList MainWindow::openedDiagrams() const
{
	IdList result;
	for (int i = 0; i < mUi->tabs->count(); ++i) {
		if (auto const diagram = dynamic_cast<EditorView *>(mUi->tabs->widget(i))) {
			const Id &diagramId = diagram->editorViewScene().rootItemId();
			if (diagramId.editor() == "RobotsMetamodel"
					&& diagramId.diagram() == "RobotsDiagram"
					&& (diagramId.element() == "RobotsDiagramNode"
						|| diagramId.element() == "SubprogramDiagram")) {
				result << diagram->mvIface().rootId();
			}
		}
	}
	return result;
}

void MainWindow::initPluginsAndStartWidget()
{
	initToolPlugins();
	if (SettingsManager::value("scriptInterpretation").toBool()) {
		initActionWidgetsNames();
		initScriptAPI();
	}

	BrandManager::configure(&mProjectManager->toolManager());
	mPreferencesDialog->setWindowIcon(BrandManager::applicationIcon());
	PreferencesPage *hotKeyManagerPage = new PreferencesHotKeyManagerPage(this);
	mPreferencesDialog->registerPage(tr("Shortcuts"), hotKeyManagerPage);

	if (!mProjectManager->restoreIncorrectlyTerminated() &&
			(mInitialFileToOpen.isEmpty() || !mProjectManager->open(mInitialFileToOpen)))
	{
		openStartTab();
	}

	mSplashScreen->close();
}

void MainWindow::initActionWidgetsNames()
{
	QList<QAction *> const actionList = findChildren<QAction *>();

	for (QAction * const action : actionList) {
		for (QWidget * const widget : action->associatedWidgets()) {
			if (widget->objectName().isEmpty()) {
				widget->setObjectName(action->objectName());
			}
		}
	}
}

void MainWindow::addActionOrSubmenu(QMenu *target, const ActionInfo &actionOrMenu)
{
	if (actionOrMenu.isAction()) {
		target->addAction(actionOrMenu.action());
	} else {
		target->addMenu(actionOrMenu.menu());
	}
}

void MainWindow::traverseListOfActions(const QList<ActionInfo> &actions)
{
	for (const ActionInfo &action : actions) {
		if (action.isAction()) {
			QToolBar * const toolbar = findChild<QToolBar *>(action.toolbarName() + "Toolbar");
			if (toolbar) {
				toolbar->addAction(action.action());
				connect(action.action(), &QAction::changed, this, [toolbar]() {
					for (QAction * const action : toolbar->actions()) {
						if (action->isVisible()) {
							toolbar->setVisible(true);
							return;
						}
					}

					toolbar->hide();
				});
			}
		}
	}

	for (const ActionInfo &action : actions) {
		/// @todo: We should somehow assert that all menus have names in such format.
		const QString capitalizedName = utils::StringUtils::capitalizeFirstLetter(action.menuName());
		QMenu *menu = findChild<QMenu *>("menu" + capitalizedName);
		if (!menu) {
			menu = findChild<QMenu *>("menu_" + capitalizedName);
		}

		if (menu) {
			addActionOrSubmenu(menu, action);
		}
	}
}

void MainWindow::addExternalToolActions()
{
	QMenu *externalToolsMenu = new QMenu(tr("External tools"), this);
	const QString pathToConfigs = PlatformInfo::applicationDirPath() + "/externalToolsConfig";
	const QString osName = PlatformInfo::osType();
	const QStringList configs = QDir(pathToConfigs).entryList().filter(".xml");
	QLOG_INFO() << "Initializing external tools from " << pathToConfigs << "with" << configs;
	for (const QString &configFile : configs) {
		QDomDocument xmlConfig = utils::xmlUtils::loadDocument(pathToConfigs + "/" + configFile);
		for (QDomElement element = xmlConfig.firstChildElement("tools").firstChildElement("platform")
				; !element.isNull()
				; element = element.nextSiblingElement("platform"))
		{
			const QString name = element.attribute("name");
			if (!osName.startsWith(name, Qt::CaseInsensitive)) {
				continue;
			}

			for (QDomElement tool = element.firstChildElement("tool")
					; !tool.isNull()
					; tool = tool.nextSiblingElement("tool"))
			{
				auto toolName = tool.attribute("name");
				auto program = PlatformInfo::invariantPath(tool.attribute("program"));
				auto arguments = tool.attribute("arguments").split(" ");
				auto action = new QAction(toolName, externalToolsMenu);
				const QRegularExpression re("@@([^@]*)@@");
				connect(action, &QAction::triggered, this, [=](){
					auto processedArguments = arguments;
					QRegularExpressionMatch match;
					for (auto &arg : processedArguments) {
						while (arg.contains(re, &match)) {
							auto const &newVal = SettingsManager::value(match.captured(1)).toString();
							arg.replace(match.captured(0), newVal);
						}

						// Avoid relative paths in arguments
						if (arg.startsWith("./")) {
							arg = qReal::PlatformInfo::applicationDirPath() + arg.mid(1);
						}
					}

					bool result;
					if (program == "#url#") {
						QUrl url(processedArguments.first());
						result = QDesktopServices::openUrl(url);
					} else {
						//I have found no simple nice way to check if process/sub-process has started without errors
						result = QProcess::startDetached(program, processedArguments);
					}

					if (!result) {
						mErrorReporter->addError(tr("Failed to open %1").arg(toolName));
					}
				});

				externalToolsMenu->addAction(action);
			}

			break;
		}
	}

	if (!externalToolsMenu->actions().isEmpty()) {
		mUi->menuTools->addMenu(externalToolsMenu);
	} else {
		delete externalToolsMenu;
	}
}

QList<QAction *> MainWindow::optionalMenuActionsForInterpretedPlugins()
{
	return mListOfAdditionalActions;
}

void MainWindow::initToolPlugins()
{
	mProjectManager->toolManager().init(PluginConfigurator(models().repoControlApi()
		, models().graphicalModelAssistApi()
		, models().logicalModelAssistApi()
		, *mController
		, *this
		, *this
		, *mProjectManager
		, *mSceneCustomizer
		, mFacade->events()
		, *mTextManager));

	QList<ActionInfo> const actions = mProjectManager->toolManager().actions();
	traverseListOfActions(actions);
	addExternalToolActions();

	for (const HotKeyActionInfo &actionInfo : mProjectManager->toolManager().hotKeyActions()) {
		HotKeyManager::setCommand(actionInfo.id(), actionInfo.label(), actionInfo.action());
	}

	if (mUi->generatorsToolbar->actions().isEmpty()) {
		mUi->generatorsToolbar->hide();
	}

	if (mUi->interpretersToolbar->actions().isEmpty()) {
		mUi->interpretersToolbar->hide();
	}

	for (auto &&page : mProjectManager->toolManager().preferencesPages()) {
		mPreferencesDialog->registerPage(page.first, page.second);
	}

	const bool allowExplosionsCustomization = toolManager().customizer()->allowSubprogramPropertiesChanging();
	mSceneCustomizer->setAllowSubprogramPropertiesChanging(allowExplosionsCustomization);
	mUi->paletteTree->customizeExplosionTitles(
			toolManager().customizer()->userPaletteTitle()
			, toolManager().customizer()->userPaletteDescription());

	customizeActionsVisibility();
}

void MainWindow::customizeActionsVisibility()
{
	QList<QAction *> actions = findChildren<QAction *>();
	for (const QPair<QString, ActionVisibility> &info : toolManager().customizer()->actionsVisibility()) {
		QAction *action = nullptr;
		for (QAction * const currentAction : actions) {
			if (currentAction->objectName() == info.first) {
				action = currentAction;
				break;
			}
		}

		if (!action) {
			QLOG_ERROR() << "Cannot find" << info.first << "in main window actions";
			continue;
		}

		QList<QToolBar *> toolBars;
		for (QWidget * const associatedWidget : action->associatedWidgets()) {
			if (QToolBar * const toolBar = qobject_cast<QToolBar *>(associatedWidget)) {
				toolBars << toolBar;
			}
		}

		switch (info.second) {
		case ActionVisibility::VisibleEverywhere:
			action->setVisible(true);
			break;
		case ActionVisibility::VisibleOnlyInMenu:
			for (QToolBar * const toolBar : toolBars) {
				toolBar->removeAction(action);
			}
			break;
		case ActionVisibility::Invisible:
			action->setVisible(false);
			break;
		}
	}
}

void MainWindow::showErrors(const gui::ErrorReporter * const errorReporter)
{
	errorReporter->showErrors(mUi->errorListWidget, mUi->errorDock);
}

void MainWindow::reinitModels()
{
	closeAllTabs();

	models().reinit();

	PropertyEditorModel* pModel = dynamic_cast<PropertyEditorModel*>(mUi->propertyEditor->model());
	pModel->clearModelIndexes();
	mUi->propertyEditor->setRootIndex(QModelIndex());
}

QWidget *MainWindow::windowWidget()
{
	return this;
}

void MainWindow::customizeWindow()
{
	const Customizer * const customizer = mProjectManager->toolManager().customizer();
	if (customizer) {
		setWindowTitle(customizer->windowTitle());
		setWindowIcon(customizer->applicationIcon());
		setVersion(customizer->productVersion());
	}
}

void MainWindow::initMiniMap()
{
	mUi->minimapView->init(this);
}

void MainWindow::initTabs()
{
	mUi->tabs->setTabsClosable(true);
	mUi->tabs->setMovable(true);
	registerEditor(*mUi->tabs);
	connect(mUi->tabs, &TabWidget::currentChanged, this, &MainWindow::currentTabChanged);
	connect(mUi->tabs, &TabWidget::tabCloseRequested
			, this, static_cast<void (MainWindow::*)(int)>(&MainWindow::closeTab));
}

void MainWindow::initDocks()
{
	mUi->paletteDock->setWidget(mUi->paletteTree);
	mUi->errorDock->setWidget(mUi->errorListWidget);
	mUi->errorListWidget->init(this);
	mUi->errorDock->setVisible(false);
	resetToolbarSize(SettingsManager::value("toolbarSize").toInt());
	utils::SmartDock::hideCloseButton(mUi->paletteDock);
	utils::SmartDock::hideCloseButton(mUi->propertyDock);
}

void MainWindow::initGridProperties()
{
	mUi->actionSwitch_on_grid->blockSignals(false);
	mUi->actionSwitch_on_grid->setChecked(SettingsManager::value("ActivateGrid").toBool());

	mUi->actionShow_grid->blockSignals(false);
	mUi->actionShow_grid->setChecked(SettingsManager::value("ShowGrid").toBool());
}

void MainWindow::initExplorers()
{
	mUi->propertyEditor->init(models().logicalModelAssistApi(), *mController);
	mUi->propertyEditor->setModel(mPropertyModel.data());

	registerEditor(*mUi->graphicalModelExplorer);
	registerEditor(*mUi->logicalModelExplorer);

	mUi->graphicalModelExplorer->setModel(models().graphicalModel());
	mUi->graphicalModelExplorer->initialize(*mController, models(), models().graphicalModelAssistApi());

	mUi->logicalModelExplorer->setModel(models().logicalModel());
	mUi->logicalModelExplorer->initialize(*mController, models(), models().logicalModelAssistApi());

	mPropertyModel->setSourceModels(models().logicalModel(), models().graphicalModel());

	connect(&models().graphicalModelAssistApi(), &models::GraphicalModelAssistApi::nameChanged
			, this, &MainWindow::updateTabName);
	connect(mUi->graphicalModelExplorer, &ModelExplorer::clicked, this, &MainWindow::graphicalModelExplorerClicked);
	connect(mUi->logicalModelExplorer, &ModelExplorer::clicked, this, &MainWindow::logicalModelExplorerClicked);
}

void MainWindow::initRecentProjectsMenu()
{
	mRecentProjectsMenu = new QMenu(tr("Recent projects"), mUi->menu_File);
	mUi->menu_File->insertMenu(mUi->menu_File->actions().at(1), mRecentProjectsMenu);
	connect(mRecentProjectsMenu, &QMenu::aboutToShow, this, &MainWindow::openRecentProjectsMenu);
}

void MainWindow::saveDiagramAsAPictureToFile(const QString &fileName)
{
	if (fileName.isEmpty()) {
		return;
	}
	const QRectF sceneRect = getCurrentTab()->scene()->itemsBoundingRect();

	QImage image(sceneRect.size().toSize(), QImage::Format_RGB32);
	QPainter painter(&image);

	QBrush brush(Qt::SolidPattern);
	brush.setColor(Qt::white);
	painter.setBrush(brush);
	painter.setPen(QPen(Qt::white));
	QRectF realBoundingRect = sceneRect;
	realBoundingRect.moveTo(QPointF());
	painter.drawRect(realBoundingRect);

	getCurrentTab()->scene()->render(&painter, realBoundingRect, sceneRect);
	image.save(fileName);
}

void MainWindow::saveDiagramAsAPicture()
{
	if (getCurrentTab()) {
		const QString fileName = utils::QRealFileDialog::getSaveFileName("SaveDiagramAsPicture", this
				, tr("Save File"), "", tr("Images (*.png *.jpg)"));
		saveDiagramAsAPictureToFile(fileName);
	}
}

void MainWindow::changePaletteRepresentation()
{
	if (SettingsManager::value("PaletteRepresentation").toBool() != mUi->paletteTree->iconsView()
			|| SettingsManager::value("PaletteIconsInARowCount").toInt() != mUi->paletteTree->itemsCountInARow())
	{
		loadEditorPlugins();
	}
}

void MainWindow::arrangeElementsByDotRunner(const QString &algorithm, const QString &absolutePathToDotFiles)
{
	const Id diagramId = activeDiagram();
	DotRunner *runner = new DotRunner(
			diagramId
			, models().graphicalModelAssistApi()
			, models().logicalModelAssistApi()
			, editorManager()
			, absolutePathToDotFiles
			);

	if (runner->run(algorithm)) {
		updateActiveDiagram();
	}
}

IdList MainWindow::selectedElementsOnActiveDiagram()
{
	if (!getCurrentTab()) {
		return IdList();
	}
	QList<QGraphicsItem*> items = getCurrentTab()->scene()->items();

	IdList selected;
	for (QGraphicsItem* item : items) {
		Element* element = dynamic_cast<Element*>(item);
		if (element) {
			if (element->isSelected()) {
				selected.append(element->id());
			}
		}
	}
	return selected;
}

void MainWindow::updateActiveDiagram()
{
	const Id diagramId = activeDiagram();
	reinitModels();
	activateItemOrDiagram(diagramId);
	mUi->graphicalModelExplorer->setRootIndex(QModelIndex());
}

QDockWidget *MainWindow::logicalModelDock() const
{
	return mUi->logicalModelDock;
}

QDockWidget *MainWindow::graphicalModelDock() const
{
	return mUi->graphicalModelDock;
}

QDockWidget *MainWindow::propertyEditorDock() const
{
	return mUi->propertyDock;
}

QDockWidget *MainWindow::errorReporterDock() const
{
	return mUi->errorDock;
}

QDockWidget *MainWindow::paletteDock() const
{
	return mUi->paletteDock;
}

QDockWidget *MainWindow::minimapDock() const
{
	return mUi->minimapDock;
}

QStatusBar *MainWindow::statusBar() const
{
	return QMainWindow::statusBar();
}

QList<QToolBar *> MainWindow::toolBars() const
{
	return findChildren<QToolBar *>(QString(), Qt::FindDirectChildrenOnly);
}

void MainWindow::tabifyDockWidget(QDockWidget *first, QDockWidget *second)
{
	QMainWindow::tabifyDockWidget(first, second);
}

void MainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockWidget)
{
	mAdditionalDocks << dockWidget;
	QMainWindow::addDockWidget(area, dockWidget);
}

void MainWindow::addToolBar(Qt::ToolBarArea area, QToolBar * const toolbar)
{
	QMainWindow::addToolBar(area, toolbar);
}

QByteArray MainWindow::saveState(int version) const
{
	return QMainWindow::saveState(version);
}

bool MainWindow::restoreState(const QByteArray &state, int version)
{
	const bool result = QMainWindow::restoreState(state, version);
	if (mUi->errorListWidget->count() == 0) {
		mUi->errorDock->hide();
	} else {
		mUi->errorDock->setVisible(true);
	}

	return result;
}

void MainWindow::setCorner(Qt::Corner corner, Qt::DockWidgetArea area)
{
	QMainWindow::setCorner(corner, area);
}

void MainWindow::setTabText(QWidget *tab, const QString &text)
{
	const int index = mUi->tabs->indexOf(tab);

	if (index != -1) {
		mUi->tabs->setTabText(index, text);
	}
}

void MainWindow::setVersion(const QString &version)
{
	// TODO: update title
	SettingsManager::setValue("version", version);
}

void MainWindow::openStartTab()
{
	for (int i = 0; i < mUi->tabs->count(); ++i) {
		if (dynamic_cast<StartWidget *>(mUi->tabs->widget(i))) {
			mUi->tabs->setCurrentIndex(i);
			return;
		}
	}

	mStartWidget = new StartWidget(this, &*mProjectManager, this);
	const bool hadTabs = mUi->tabs->count() > 0;
	mUi->tabs->insertTab(0, mStartWidget, tr("Getting Started"));
	mUi->tabs->setTabUnclosable(hadTabs);
	mStartWidget->setVisibleForInterpreterButton(
			mProjectManager->toolManager().customizer()->showInterpeterButton());
}

void MainWindow::initScriptAPI()
{
	QThread * const scriptAPIthread = new QThread(this);
	mScriptAPI = new ScriptAPI();
	mScriptAPI->moveToThread(scriptAPIthread);
	connect(&mFacade->events(), &SystemEvents::closedMainWindow, scriptAPIthread, &QThread::quit);
	connect(scriptAPIthread, &QThread::finished, mScriptAPI, &QObject::deleteLater);
	connect(scriptAPIthread, &QThread::started, mScriptAPI, [this](){ mScriptAPI->init(this); });

	QAction *const evalAction = new QAction(this);
	// Setting a secret combination to activate script interpretation.
	evalAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F12));
	connect(evalAction, &QAction::triggered, mScriptAPI, &ScriptAPI::evaluate);
	addAction(evalAction);

	scriptAPIthread->start();
}

void MainWindow::beginPaletteModification()
{
}

void MainWindow::setElementInPaletteVisible(const Id &metatype, bool visible)
{
	mUi->paletteTree->setElementVisible(metatype, visible);
	// Note that if element is visible in palette, it is not necessary that it will be enabled it editor manager. It
	// may be greyed-out and still can't be used on diagrams.
}

void MainWindow::setVisibleForAllElementsInPalette(const Id &diagram, bool visible)
{
	mUi->paletteTree->setVisibleForAllElements(diagram, visible);
	for (const Id &element : editorManager().elements(diagram)) {
		editorManager().setElementEnabled(element, visible);
	}
}

void MainWindow::setElementInPaletteEnabled(const Id &metatype, bool enabled)
{
	mUi->paletteTree->setElementEnabled(metatype, enabled);
	editorManager().setElementEnabled(metatype, enabled);
}

void MainWindow::setEnabledForAllElementsInPalette(const Id &diagram, bool enabled)
{
	mUi->paletteTree->setEnabledForAllElements(diagram, enabled);
	for (const Id &element : editorManager().elements(diagram)) {
		editorManager().setElementEnabled(element, enabled);
	}
}

void MainWindow::endPaletteModification()
{
	// Disabling elements on scene...
	EditorViewScene * const scene = getCurrentTab() ? &getCurrentTab()->mutableScene() : nullptr;
	if (scene) {
		for (QGraphicsItem * const item : scene->items()) {
			if (Element * const element = dynamic_cast<Element *>(item)) {
				element->updateEnabledState();
			}
		}

		scene->update();
	}
}
