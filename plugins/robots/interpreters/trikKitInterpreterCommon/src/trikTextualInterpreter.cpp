/* Copyright 2016-2017 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>
#include <QProcessEnvironment>

#include "trikKitInterpreterCommon/trikTextualInterpreter.h"

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>

#include <twoDModel/engine/model/timeline.h>
#include <qrgui/textEditor/languageInfo.h>
#include <trikKernel/fileUtils.h>
#include <trikNetwork/mailboxFactory.h>
#include <qrkernel/settingsManager.h>


Q_DECLARE_METATYPE(utils::AbstractTimer*)

const QString jsOverrides = "Date.now = script.time;";

trik::TrikTextualInterpreter::TrikTextualInterpreter(
	const QSharedPointer<trik::robotModel::twoD::TrikTwoDRobotModel> &model
		, bool enablePython)
	: mBrick(model)
	, mMailbox(qReal::SettingsManager::value("TRIK2DMailbox", "").toBool()
			   ? trikNetwork::MailboxFactory::create(8889): nullptr)
	, mScriptRunner(mBrick, mMailbox, new TwoDExecutionControl(mBrick, model))
{
	connect(&mBrick, &TrikBrick::error, this, &TrikTextualInterpreter::reportError);
	connect(&mBrick, &TrikBrick::warning, this, &TrikTextualInterpreter::reportWarning);

	auto atimerToScriptValue = [](QScriptEngine *engine, utils::AbstractTimer* const &in){
	return engine->newQObject(in);
	};
	auto atimerFromScriptValue = [](const QScriptValue &object, utils::AbstractTimer* &out){
	out = qobject_cast<utils::AbstractTimer*>(object.toQObject());
	};
	mScriptRunner.addCustomEngineInitStep([&atimerToScriptValue, &atimerFromScriptValue](QScriptEngine *engine){
	qScriptRegisterMetaType<utils::AbstractTimer*>(engine, atimerToScriptValue, atimerFromScriptValue);
	});
	connect(&mScriptRunner, &trikScriptRunner::TrikScriptRunner::textInStdOut, &mBrick, &TrikBrick::log);
	connect(&mScriptRunner, &trikScriptRunner::TrikScriptRunner::completed
		, this, &TrikTextualInterpreter::scriptFinished);

	using qReal::text::Languages;
	using trikScriptRunner::ScriptType;
	Languages::registerLanguage(Languages::javaScript(mScriptRunner.knownMethodNamesFor(ScriptType::JAVASCRIPT)));

	if (enablePython) {
		Languages::registerLanguage(Languages::python(mScriptRunner.knownMethodNamesFor(ScriptType::PYTHON)));
	}
}

trik::TrikTextualInterpreter::~TrikTextualInterpreter()
{
	abort();
}

void trik::TrikTextualInterpreter::interpretCommand(const QString &script)
{
	mScriptRunner.runDirectCommand(script);
}

void trik::TrikTextualInterpreter::interpretScript(const QString &script, const QString &languageExtension)
{
	mRunning = true;
	mBrick.processSensors(true);
	if (languageExtension.contains("js")) {
		mScriptRunner.run(jsOverrides + script);
	} else if (languageExtension.contains("py")) {
		mScriptRunner.run(script, "dummyFile.py");
	} else {
		reportError(tr("Unsupported script file type"));
	}
}

void trik::TrikTextualInterpreter::interpretScriptExercise(const QString &script
	, const QString &inputs, const QString &languageExtension)
{
	mRunning = true;
	mBrick.processSensors(true);
	mBrick.setCurrentInputs(inputs);
	if (languageExtension.contains("js")) {
		mScriptRunner.run(jsOverrides + "script.writeToFile = null;\n" + script);
	} else if (languageExtension.contains("py")) {
		auto updatedScript = script;
		mScriptRunner.run(updatedScript.insert(0, "\nscript.writeToFile = None\n"), "dummyFile.py");
	} else {
		reportError(tr("Unsupported script file type"));
	}
}

void trik::TrikTextualInterpreter::abort()
{
	Q_ASSERT(mScriptRunner.thread() == thread());
	// just a wild test
	QMetaObject::invokeMethod(&mScriptRunner, &trikScriptRunner::TrikScriptRunner::abort, Qt::QueuedConnection);
	mRunning = false; // reset brick?
	mBrick.processSensors(false);
}

void trik::TrikTextualInterpreter::init()
{
	mBrick.init(); // very crucial. Maybe move into interpret methods?
}

void trik::TrikTextualInterpreter::setErrorReporter(qReal::ErrorReporterInterface &errorReporter)
{
	mErrorReporter = &errorReporter;
}

bool trik::TrikTextualInterpreter::isRunning() const
{
	return mRunning;
}

void trik::TrikTextualInterpreter::reportError(const QString &msg)
{
	mErrorReporter->addError(msg);
	//	mBrick.abort(); what if there are more errors?
}

void trik::TrikTextualInterpreter::reportWarning(const QString &msg)
{
	mErrorReporter->addWarning(msg);
}

void trik::TrikTextualInterpreter::reportLog(const QString &msg)
{
	mErrorReporter->addInformation("log: " + msg);
}

QString trik::TrikTextualInterpreter::initInputs(const QString &inputs) const
{
	auto jsValToStr = [this](const QJsonValue &val) -> QString {
	switch (val.type()) {
	case QJsonValue::Bool:
		return val.toBool() ? "true" : "false";
	case QJsonValue::Double:
		return QString::number(val.Double);//maybe increase precision
	case QJsonValue::String:
		return QString("\"%1\"").arg(val.toString());
	case QJsonValue::Array:
		return QString(QJsonDocument(val.toArray()).toJson(QJsonDocument::Compact));
	case QJsonValue::Object:
		return QString(QJsonDocument(val.toObject()).toJson(QJsonDocument::Compact));
	default:
		mErrorReporter->addError(QObject::tr("Bogus input values"));
		return "";
	}
	};

	QString result;
	if (!inputs.isEmpty()) {
	QString val;
	QFile file;
	file.setFileName(inputs);
	if (file.open(QIODevice::ReadOnly)) {
		val = file.readAll();
		file.close();
		QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
		QJsonObject object = document.object();
		for (const QString &name : object.keys()) {
		QJsonValue value = object[name];
		QString valueStr = jsValToStr(value);
		QString line("var " + name + " = " + valueStr + ";\n");
		result.append(line);
		}
	} else {
		mErrorReporter->addError(QObject::tr("Error: File %1 couldn't be opened!").arg(inputs));
	}
	}
	return result;
}

void trik::TrikTextualInterpreter::setRunning(bool running)
{
	mRunning = running;
	mBrick.processSensors(running);
}

void trik::TrikTextualInterpreter::setCurrentDir(const QString &dir, const QString &languageExtension)
{
	mBrick.setCurrentDir(dir);
	mScriptRunner.setDefaultRunner(languageExtension);
	mScriptRunner.setWorkingDirectory(trikKernel::FileUtils::normalizePath(dir));
}

QStringList trik::TrikTextualInterpreter::supportedRobotModelNames() const
{
	return {"TwoDRobotModelForTrikV62RealRobotModel", "TwoDRobotModelForTrikV6RealRobotModel"};
}

QStringList trik::TrikTextualInterpreter::knownMethodNames() const
{
	return mScriptRunner.knownMethodNames();
}

void trik::TrikTextualInterpreter::scriptFinished(const QString &error, int scriptId)
{
	Q_UNUSED(scriptId);
	if (!error.isEmpty()) {
	reportError(error);
	}

	if (mRunning) { /// @todo: figure out better place for this check - it should avoid double aborts
	mRunning = false;
	mBrick.processSensors(false);
	emit completed();
	}
}
