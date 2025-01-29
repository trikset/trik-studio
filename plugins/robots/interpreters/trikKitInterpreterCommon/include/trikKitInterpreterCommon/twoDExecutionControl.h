/* Copyright 2020 Andrei Khodko and CyberTech Labs Ltd.
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

#pragma once

#include "trikScriptRunner/trikScriptControlInterface.h"

#include "trikControl/brickInterface.h"
#include "trikbrick.h"

#include <utils/abstractTimer.h>
#include <trikKitInterpreterCommon/robotModel/twoD/trikTwoDRobotModel.h>

class TwoDExecutionControl : public trikScriptRunner::TrikScriptControlInterface
{
	Q_OBJECT
public:
	TwoDExecutionControl(trik::TrikBrick &brick,
			const QSharedPointer<trik::robotModel::twoD::TrikTwoDRobotModel> &model);

	~TwoDExecutionControl() override = default;

	int random(int from, int to) const override;

	void wait(const int &milliseconds) override;

	qint64 time() const override;

	//QStringList readAll(const QString &file) const override;

	/// In trikRuntime returns QTimer, but we need timer with emulated 2D time. Hopefully this is enough
	utils::AbstractTimer *timer(int milliseconds) override;

	void processSensors(bool isRunning = true);

	bool isInEventDrivenMode() const override;

	QVector<int32_t> getPhoto() override;

	void system(const QString &command, bool synchronously) override;

	void writeToFile(const QString &file, const QString &text) override;

	void writeData(const QString &file, const QVector<uint8_t> &bytes) override;

	QStringList readAll(const QString &file) const override;

	void removeFile(const QString &file) override;

	int timeInterval(int packedTimeLeft, int packedTimeRight) override;

public slots:
	void reset() override;
	void run() override;
	void quit() override;

private:
	bool mInEventDrivenMode {false};
	trik::TrikBrick &mBrick;
	QList<utils::AbstractTimer*> mTimers; // Owns, but in safe manner: timers can be from different threads
	QSharedPointer<trik::robotModel::twoD::TrikTwoDRobotModel> mTwoDRobotModel;
};
