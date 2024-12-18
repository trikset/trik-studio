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

#include <time.h>

#include <QtCore/QtPlugin>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include <QtCore/QDirIterator>
#include <QtWidgets/QApplication>
#include <QStyleFactory>

#include <qrkernel/logging.h>
#include <qrkernel/platformInfo.h>

#include "mainWindow/mainWindow.h"
#include "thirdparty/windowsmodernstyle.h"

#include "qrealApplication.h"

using namespace qReal;

const int maxLogSize = 10 * 1024 * 1024;  // 10 MB

static void clearConfig()
{
	SettingsManager::clearSettings();
	SettingsManager::instance()->saveData();
}

static void loadTranslators(QLocale &locale)
{
	/// Load Qt's system translations before application translations
	static const QStringList qtModules {"qtbase", "qtmultimedia", "qtserialport", "qtxmlpatterns", "qtscript" };
	static const auto qtAppsTranslationsDir = QLibraryInfo::location(QLibraryInfo::LibraryLocation::TranslationsPath);

	for (auto &&module: qtModules) {
		auto *t = new QTranslator(qApp);
		if (t->load(locale, module, "_", qtAppsTranslationsDir)) {
			QCoreApplication::installTranslator(t);
		} else {
			QLOG_ERROR() << QString(R"(Failed to load translation file for "%1" (%2) from %3)")
							.arg(module, locale.bcp47Name(), qtAppsTranslationsDir);
			delete t;
		}
	}

	auto const &language = locale.bcp47Name().left(2);
	QDir translationsDirectory(PlatformInfo::invariantSettingsPath("pathToTranslations") + "/" + language);
	QDirIterator directories(translationsDirectory, QDirIterator::Subdirectories);
	while (directories.hasNext()) {
		for (const QFileInfo &translatorFile : QDir(directories.next()).entryInfoList(QDir::Files)) {
			QTranslator *translator = new QTranslator(qApp);
			translator->load(translatorFile.absoluteFilePath());
			QCoreApplication::installTranslator(translator);
		}
	}
}

static void setDefaultLocale(bool localizationDisabled)
{
	if (localizationDisabled) {
		QLocale::setDefault(QLocale::English);
		return;
	}

	auto const &languageName = SettingsManager::value("systemLocale").toString();
	QLocale locale = languageName.isEmpty()? QLocale() : QLocale(languageName); // Empty string results to "C" locale
	QLocale::setDefault(locale);
	QLocale dfltLocale;
	if (locale != dfltLocale) {
		QLOG_ERROR() << "Requested locale was" << locale.bcp47Name() << ", but" << dfltLocale.bcp47Name() << "is set";
	}
	auto language = locale.language();
	if (language != QLocale::Language::C && language != QLocale::Language::English) {
		loadTranslators(locale);
	}
}

static QString versionInfo()
{
	return  "TRIK Studio (" + QSysInfo::buildAbi() + ") " + TRIK_STUDIO_VERSION;
}

int main(int argc, char *argv[])
{
	qReal::Logger logger; // uses initial temporary log target

	const auto &dpiInfo = PlatformInfo::enableHiDPISupport();
	QScopedPointer<QRealApplication> app(new QRealApplication(argc, argv));

	if (app->arguments().contains("--clear-conf")) {
		clearConfig();
		return 0;
	}

	if (app->arguments().contains("--version"))
	{
		QTextStream(stdout) << versionInfo() << endl;
		return 0;
	}

	qsrand(time(0));
	setDefaultLocale(app->arguments().contains("--no-locale"));

	const QString defaultPlatformConfigPath = PlatformInfo::defaultPlatformConfigPath();
	if (!defaultPlatformConfigPath.isEmpty()) {
		// Loading default settings for concrete platform if such exist.
		SettingsManager::instance()->loadSettings(defaultPlatformConfigPath);
	}

	QString fileToOpen;
	if (app->arguments().count() > 1) {
		const int setIndex = app->arguments().indexOf("--config");
		if (setIndex > -1) {
			const QString settingsFileName = app->arguments().at(setIndex + 1);
			SettingsManager::instance()->loadSettings(settingsFileName);
		}

		for (const QString &argument : app->arguments()) {
			if (argument.endsWith(".qrs") || argument.endsWith(".qrs'") || argument.endsWith(".qrs\"")) {
				fileToOpen = argument;
				break;
			}
		}
	}

	const QDir logsDir(PlatformInfo::invariantSettingsPath("pathToLogs"));
	if (logsDir.mkpath(logsDir.absolutePath())) {
		logger.addLogTarget(logsDir.filePath("qreal.log"), maxLogSize, 2);
		logger.removeDefaultInitialLogTarget();
	}

	QLOG_INFO() << "------------------- APPLICATION STARTED --------------------";
	QLOG_INFO() << "Version:" << versionInfo();
	QLOG_INFO() << "Running on" << QSysInfo::prettyProductName() << QSysInfo::currentCpuArchitecture()
				<< "/ Kernel: " << QSysInfo::kernelType() << QSysInfo::kernelVersion();
	QLOG_INFO() << "Arguments:" << app->arguments();
	for (auto &&i: dpiInfo) { QLOG_INFO() << i ; }

	QApplication::setStyle(QStyleFactory::create("Fusion"));

	QScopedPointer<MainWindow> window(new MainWindow(fileToOpen));
	int exitCode = 0; // The window decided to not show itself, exiting now.

	if (window->isVisible()) {
		exitCode = app->exec();
	}

	window.reset();
	app.reset();
	QLOG_INFO() << "------------------- APPLICATION FINISHED -------------------";
	return exitCode;
}
