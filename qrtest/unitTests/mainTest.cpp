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
#include <QtGlobal>
#include <gtest/gtest.h>

#include <QtWidgets/QApplication>

#include <qrkernel/platformInfo.h>

void handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
	auto const &msgUtf8 = message.toUtf8();
	auto msg = msgUtf8.constData();
	fprintf(stderr, "%s:%d\t", context.file, context.line);
	switch (type)
	{
	case QtDebugMsg:
		fprintf(stderr, "Debug: %s\n", msg);
		break;
	case QtInfoMsg:
		fprintf(stderr, "Info: %s\n", msg);
		break;
	case QtWarningMsg:
		fprintf(stderr, "Warning: %s\n", msg);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "Critical: %s\n", msg);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s\n", msg);
		abort();
	}
}


int main(int argc, char *argv[])
{
	qInstallMessageHandler(handler);
	qReal::PlatformInfo::enableHiDPISupport();
	::testing::InitGoogleTest(&argc, argv);
	// "threadsafe" conflicts with AddressSanitizer for GCC 9.3
	// ::testing::FLAGS_gtest_death_test_style = "threadsafe";
	::testing::FLAGS_gtest_death_test_style = "fast";

	QScopedPointer<QApplication> app(new QApplication(argc, argv));
	auto rc = RUN_ALL_TESTS();
	app.reset();
	return rc;
}
