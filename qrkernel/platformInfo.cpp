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

#include "platformInfo.h"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QProcessEnvironment>
#include <QGuiApplication>
#include <QLibrary>
#include <qrkernel/settingsManager.h>
#include <QsLog.h>
#include <QOperatingSystemVersion>

using namespace qReal;

const QString &PlatformInfo::osType()
{
	static const QString type =
#ifdef Q_OS_LINUX
	"linux";
#elif defined(Q_OS_MACOS)
	"macos";
#elif defined(Q_OS_WIN)
	"windows";
#else
	"unknown";
#endif
	return type;
}

QString PlatformInfo::applicationDirPath()
{
#if defined Q_OS_MAC
	if (QFile(QCoreApplication::applicationDirPath() + "/platform.config").exists()) {
		return QCoreApplication::applicationDirPath();
	}

	QDir result(QCoreApplication::applicationDirPath());  // ../bin/debug/qreal-d.app/Contents/MacOS/ or ../bin/debug
	if (result.dirName() == "MacOS") {
		result.cdUp();					      // ../bin/debug/qreal-d.app/Contents/
		result.cdUp();					      // ../bin/debug/qreal-d.app/
		result.cdUp();					      // ../bin/debug/
	}

	return result.absolutePath();
#else
	return QCoreApplication::applicationDirPath();
#endif
}

QString PlatformInfo::defaultPlatformConfigPath()
{
	const QString applicationName = QCoreApplication::applicationName();
	const QStringList paths = SettingsManager::value("platformConfigSearchPaths").toStringList();
	const QStringList names = {"platform.config", applicationName + ".config"};
	for (const QString &rawPath : paths) {
		for (const QString &name : names) {
			const QString path = invariantPath(rawPath + "/" + name);
			if (QFile(path).exists()) {
				return path;
			}
		}
	}

	return QString();
}

QString PlatformInfo::invariantPath(const QString &path)
{
	QRegExp windowsVariablesRegexp("^%([A-Za-z0-9_]+)%.*");
	if (path.startsWith("./")) {
		return qReal::PlatformInfo::applicationDirPath() + path.mid(1);
	} else if (path.startsWith("@DocumentsPath@")) {
		const QStringList documentsPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
		const QString documentsPath = documentsPaths.isEmpty() ? applicationDirPath() : documentsPaths.first();
		return QString(path).replace("@DocumentsPath@", documentsPath);
	} else if (path.startsWith("@AppDataLocation@")) {
		const QStringList appDataLocationPaths = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
		const QString appDataLocationPath = appDataLocationPaths.isEmpty()
				? applicationDirPath() : appDataLocationPaths.first();
		return QString(path).replace("@AppDataLocation@", appDataLocationPath);
	} else if (path.startsWith("@TempLocation@")) {
		const QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
		return QString(path).replace("@TempLocation@", tempPath);
	} else if (windowsVariablesRegexp.exactMatch(path)) {
		const QString variable = windowsVariablesRegexp.cap(1);
		const QString value = QProcessEnvironment::systemEnvironment().value(variable);
		return QString(path).replace("%" + variable + "%", value);
	}

	return path;
}

QString PlatformInfo::invariantSettingsPath(const QString &settingsKey)
{
	return invariantPath(SettingsManager::value(settingsKey).toString());
}

QString PlatformInfo::cpuArchitecture()
{
	return QSysInfo::currentCpuArchitecture();
}

bool PlatformInfo::isX64()
{
	return cpuArchitecture().contains("64");
}

void PlatformInfo::enableHiDPISupport()
{
	if (!qEnvironmentVariableIsSet("QT_DEVICE_PIXEL_RATIO")
			&& !qEnvironmentVariableIsSet("QT_AUTO_SCREEN_SCALE_FACTOR")
			&& !qEnvironmentVariableIsSet("QT_SCALE_FACTOR")
			&& !qEnvironmentVariableIsSet("QT_SCREEN_SCALE_FACTORS")
			&& QOperatingSystemVersion::currentType() != QOperatingSystemVersion::Windows) {
		// Only if there is no attempt to set from the system environment	
			QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	}
}
