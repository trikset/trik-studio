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

#include <ctime>
#include <QtCore/QDir>
#include <QtCore/QCommandLineParser>
#include <QtCore/QTranslator>
#include <QtCore/QDirIterator>
#include <QtWidgets/QApplication>
#include <qrkernel/logging.h>
#include <qrkernel/platformInfo.h>
#include "runner.h"

constexpr int maxLogSize = 10 * 1024 * 1024;  // 10 MB
constexpr int TWO_D_MODEL_RUNNER_INTERPRET_ERROR = 2;
constexpr int TWO_D_MODEL_RUNNER_GENERATE_ERROR = 3;
constexpr int TWO_D_MODEL_RUNNER_GENERATE_MODE_NOT_EXIST = 4;

const QString description = QObject::tr(
		"Emulates robot`s behaviour on TRIK Studio 2D model separately from programming environment. "\
		"Passed .qrs will be interpreted just like when 'Run' button was pressed in TRIK Studio. \n"\
		"In background mode the session will be terminated just after the execution ended and return code "
		"will then contain binary information about program correctness."
		"Example: \n") +
		"    2D-model -b --platform minimal --report report.json --trajectory trajectory.fifo example.qrs";

bool loadTranslators(const QString &locale)
{
	QDir translationsDirectory(qReal::PlatformInfo::invariantSettingsPath("pathToTranslations") + "/" + locale);
	QDirIterator directories(translationsDirectory, QDirIterator::Subdirectories);
	bool hasTranslations = false;
	while (directories.hasNext()) {
		for (const QFileInfo &translatorFile : QDir(directories.next()).entryInfoList(QDir::Files)) {
			QTranslator *translator = new QTranslator(qApp);
			translator->load(translatorFile.absoluteFilePath());
			QCoreApplication::installTranslator(translator);
			hasTranslations = true;
		}
	}
	return hasTranslations;
}

void setDefaultLocale()
{
	const QString lang = QLocale().name().left(2);
	if (lang.isEmpty()) {
		return;
	}

	// Reset to default country for this language
	QLocale::setDefault(QLocale(lang));
	if (!loadTranslators(lang)) {
		QLOG_INFO() << "Missing translations for language" << lang;
	}
}

int main(int argc, char *argv[])
{
	qReal::PlatformInfo::enableHiDPISupport();
	qsrand(time(0));
	QScopedPointer<QApplication> app(new QApplication(argc, argv));
	QCoreApplication::setApplicationName("2D-model");
	QCoreApplication::setApplicationVersion(interpreterCore::Customizer::trikStudioVersion());

	const auto &defaultPlatformConfigPath = qReal::PlatformInfo::defaultPlatformConfigPath();
	if (!defaultPlatformConfigPath.isEmpty()) {
		// Loading default settings for concrete platform if such exist.
		qReal::SettingsManager::instance()->loadSettings(defaultPlatformConfigPath);
	}

	qReal::Logger logger;
	const QDir logsDir(qReal::PlatformInfo::invariantSettingsPath("pathToLogs"));
	if (logsDir.mkpath(logsDir.absolutePath())) {
		logger.addLogTarget(logsDir.filePath("2d-model.log"), maxLogSize, 2);
	}
	QLOG_INFO() << "------------------- APPLICATION STARTED --------------------";
	QLOG_INFO() << "Running on" << QSysInfo::prettyProductName() << QSysInfo::currentCpuArchitecture();
	QLOG_INFO() << "Arguments:" << app->arguments();
	QLOG_INFO() << "Setting default locale to" << QLocale().name();
	setDefaultLocale();

	// Hack to switch on default robot model
	for (auto &&kit : {"trikV62", "trikV6", "ev3", "nxt"}) {
		qReal::SettingsManager::setValue(QString("SelectedModelFor%1Kit").arg(kit), QVariant());
	}

	QCommandLineParser parser;
	parser.setApplicationDescription(description);
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("qrs-file", QObject::tr("Save file to be interpreted."));
	QCommandLineOption backgroundOption({"b", "background"}, QObject::tr("Run emulation in background."));
	QCommandLineOption reportOption({"r","report"}
									, QObject::tr("A path to file where checker results will be written (JSON).")
									, "path-to-report", "report.json");
	QCommandLineOption trajectoryOption({"t", "trajectory"}
										, QObject::tr("A path to file where robot`s trajectory will be"\
				" written. The writing will not be performed not immediately, each trajectory point will be written"\
				" just when obtained by checker, so FIFOs are recommended to be targets for this option.")
			, "path-to-trajectory", "trajectory.fifo");
	QCommandLineOption inputOption({"i", "input"}, QObject::tr("Inputs for JavaScript solution.")// probably others too
			, "path-to-input", "inputs.txt");
	QCommandLineOption modeOption({"m", "mode"}, QObject::tr("Set to \"script\" for"\
								" execution of js/py from the project or set to \"diagram\" for block diagram.")
								, "mode", "diagram");
	QCommandLineOption speedOption({"s", "speed"}
								   , QObject::tr("Speed factor, try from 5 to 20, or even 1000 (at your own risk!).")
								   , "speed", "0");
	QCommandLineOption closeOnSuccessOption("close-on-success"
								   , QObject::tr("Close the window and exit if the diagram/script"\
												 " finishes without errors."));
	QCommandLineOption closeOnFinishOption("close"
								   , QObject::tr("Close the window and exit after diagram/script"\
												 " finishes."));
	QCommandLineOption showConsoleOption({"c", "console"}, QObject::tr("Shows robot's console."));
	QCommandLineOption generatePathOption("generate-path"
				, QObject::tr("The complete file path, including the filename"\
					      ", to save the generated JavaScript or Python code.")
				, "path-to-save-code", QString());
	QCommandLineOption generateModeOption("generate-mode", QObject::tr("Select \"python\" or \"javascript\".")
					      , "generate-mode", "javascript");
	QCommandLineOption directScriptExecutionPathOption("script-path"
						, QObject::tr("The path to the Python or JavaScript file that will be used for interpretation.")
						, "script-path", QString());
	QCommandLineOption onlyGenerateOption("only-generate"
						, QObject::tr("Do not run the interpretation in any mode, "\
							      "this is a parameter that is only used to generate a file."));
	QCommandLineOption delayOption("delay-before-exit"
						, QObject::tr("Add a delay in milliseconds after executing "
									"the script before closing the window")
						, "Delay in ms", "0");
	parser.addOption(backgroundOption);
	parser.addOption(reportOption);
	parser.addOption(trajectoryOption);
	parser.addOption(inputOption);
	parser.addOption(modeOption);
	parser.addOption(speedOption);
	parser.addOption(closeOnFinishOption);
	parser.addOption(closeOnSuccessOption);
	parser.addOption(showConsoleOption);
	parser.addOption(generatePathOption);
	parser.addOption(generateModeOption);
	parser.addOption(directScriptExecutionPathOption);
	parser.addOption(onlyGenerateOption);
	parser.addOption(delayOption);
	parser.process(*app);
	const QStringList positionalArgs = parser.positionalArguments();
	if (positionalArgs.size() != 1) {
		parser.showHelp();
	}
	const QString &qrsFile = positionalArgs.first();
	const bool backgroundMode = parser.isSet(backgroundOption);
	const QString report = parser.isSet(reportOption) ? parser.value(reportOption) : QString();
	const QString trajectory = parser.isSet(trajectoryOption) ? parser.value(trajectoryOption) : QString();
	const QString input = parser.isSet(inputOption) ? parser.value(inputOption) : QString();
	const QString mode = parser.isSet(modeOption) ? parser.value(modeOption) : QString("diagram");
	const bool closeOnSuccessMode = parser.isSet(closeOnSuccessOption);
	const bool closeOnFinishMode = backgroundMode || parser.isSet(closeOnFinishOption);
	const bool showConsoleMode = parser.isSet(showConsoleOption);
	const QString generatePath = parser.value(generatePathOption);
	const QString generateMode = parser.value(generateModeOption);
	const QString scriptFilePath = parser.value(directScriptExecutionPathOption);
	const bool onlyGenerate = parser.isSet(onlyGenerateOption);
	const auto &delayStr = parser.value(delayOption);
	auto delayIsCorrect = false;
	auto delay = delayStr.toInt(&delayIsCorrect);
	if (!delayIsCorrect || (delayIsCorrect && delay < 0)) {
		delay = 0;
	}

	QScopedPointer<twoDModel::Runner> runner(
				new twoDModel::Runner(report, trajectory, input, mode, qrsFile, delay));
	auto speedFactor = parser.value(speedOption).toInt();

	if (!generatePath.isEmpty()) {
		if (generateMode != "python" and generateMode != "javascript"
			and generateMode != "nxt") {
			parser.showHelp();
			QLOG_ERROR() << "Problem with generate code to " << generatePath;
			return TWO_D_MODEL_RUNNER_GENERATE_MODE_NOT_EXIST;
		}
		if (!runner->generate(generatePath, generateMode)) {
			QLOG_ERROR() << "Problem with generate code to " << generatePath;
			return TWO_D_MODEL_RUNNER_GENERATE_ERROR;
		}
	}

	if (onlyGenerate || mode == "nxt") {
		return 0;
	}

	if (!runner->interpret(backgroundMode, speedFactor, closeOnFinishMode,
			       closeOnSuccessMode, showConsoleMode, scriptFilePath)) {
		return TWO_D_MODEL_RUNNER_INTERPRET_ERROR;
	}

	const int exitCode = app->exec();
	runner.reset();
	app.reset();
	QLOG_INFO() << "------------------- APPLICATION FINISHED -------------------";
	return exitCode;
}
