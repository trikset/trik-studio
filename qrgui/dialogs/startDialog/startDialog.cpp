#include <QtGui/QTabWidget>
#include <QtGui/QCommandLinkButton>
#include "startDialog.h"
#include "suggestToCreateDiagramWidget.h"
#include "recentProjectsListWidget.h"
#include "../mainwindow/mainWindow.h"

using namespace qReal;

StartDialog::StartDialog(MainWindow *mainWindow, QWidget *parent)
	: QDialog(parent, Qt::WindowMaximizeButtonHint)
	, mMainWindow(mainWindow)
	, mTabWidget(new QTabWidget)
{
	mTabWidget->setFixedSize(380, 300);

	RecentProjectsListWidget *recentProjects = new RecentProjectsListWidget(this);
	mTabWidget->addTab(recentProjects, tr("Recent projects"));
	SuggestToCreateDiagramWidget *diagrams = new SuggestToCreateDiagramWidget(mMainWindow, this);
	mTabWidget->addTab(diagrams, tr("New project with diagram"));

	QCommandLinkButton *quitLink = new QCommandLinkButton(tr("&Quit QReal"));
	QCommandLinkButton *openLink = new QCommandLinkButton(tr("&Open existing project"));

	QHBoxLayout *commandLinksLayout = new QHBoxLayout;
	commandLinksLayout->addWidget(openLink);
	commandLinksLayout->addWidget(quitLink);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mTabWidget);
	mainLayout->addLayout(commandLinksLayout);

	setLayout(mainLayout);

	connect(openLink, SIGNAL(clicked()), this, SLOT(openExistingProject()));
	connect(quitLink, SIGNAL(clicked()), mMainWindow, SLOT(close()));
	connect(quitLink, SIGNAL(clicked()), this, SLOT(close()));
	connect(recentProjects, SIGNAL(userDataSelected(QString)), this, SLOT(openRecentProject(QString)));
	connect(diagrams, SIGNAL(userDataSelected(QString)), this, SLOT(createProjectWithDiagram(QString)));
}

void StartDialog::openRecentProject(QString const &fileName)
{
	mMainWindow->open(fileName);
}

void StartDialog::openExistingProject()
{
	if (mMainWindow->openExistingProject()) {
		close();
	}
}

void StartDialog::createProjectWithDiagram(const QString &idString)
{
	mMainWindow->openEmptyProject();
	mMainWindow->createDiagram(idString);
}
