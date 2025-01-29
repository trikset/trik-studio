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

#include "logging.h"
#include <QsLogDest.h>
using namespace qReal;

void Logger::addLogTarget(const QString &path, int maxSize, int maxOldLogsCount)
{
	auto dest = QsLogging::DestinationFactory::MakeFileDestination(path
							   , QsLogging::LogRotationOption::EnableLogRotation
							   , QsLogging::MaxSizeBytes(maxSize)
							  , QsLogging::MaxOldLogCount(maxOldLogsCount));
	QsLogging::Logger::instance().setLoggingLevel(QsLogging::DebugLevel);
	QsLogging::Logger::instance().addDestination(std::move(dest));
}

void Logger::removeDefaultInitialLogTarget()
{
	QsLogging::Logger::instance().removeDestination(mDefaultInitialLoggerType);
}

Logger::Logger()
{
	auto dest = QsLogging::DestinationFactory::MakeDebugOutputDestination();
	mDefaultInitialLoggerType = dest->type();
	QsLogging::Logger::instance().setLoggingLevel(QsLogging::DebugLevel);
	QsLogging::Logger::instance().addDestination(std::move(dest));
}

Logger::~Logger()
{
#if defined(Q_OS_WIN)
	QsLogging::Logger::instance().shutDownLoggerThread();
#endif
}
