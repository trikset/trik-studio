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

#include "trikKitInterpreterCommon/twoDExecutionControl.h"

#include <QApplication>
#include <QEventLoop>

#include <kitBase/robotModel/robotParts/random.h>
#include <kitBase/robotModel/robotModelUtils.h>
#include <twoDModel/engine/model/timeline.h>
#include <trikControl/utilities.h>

TwoDExecutionControl::TwoDExecutionControl(
		trik::TrikBrick &brick
		, const QSharedPointer<trik::robotModel::twoD::TrikTwoDRobotModel> &model)
	: mBrick(brick)
	, mTwoDRobotModel(model)
{
	qRegisterMetaType<QVector<int32_t>>("QVector<int32_t>");
}

TwoDExecutionControl::~TwoDExecutionControl()
{
}

int TwoDExecutionControl::random(int from, int to) const
{
	using namespace kitBase::robotModel;
	auto r = RobotModelUtils::findDevice<robotParts::Random>(*mTwoDRobotModel, "RandomPort");
	// maybe store it later, like the others
	if (!r) {
		//emit error(tr("No cofigured random device"));
		return -1;
	}

	return r->random(from, to);
}

void TwoDExecutionControl::wait(const int &milliseconds)
{
	auto timeline = dynamic_cast<twoDModel::model::Timeline *> (&mTwoDRobotModel->timeline());

	if (!timeline->isStarted()) {
		return;
	}

	QEventLoop loop;

	auto t = timeline->produceTimer();
	connect(t, &utils::AbstractTimer::timeout, &loop, &QEventLoop::quit);
	connect(&loop, &QObject::destroyed, t, &QObject::deleteLater);

	connect(timeline, &twoDModel::model::Timeline::beforeStop, &loop, &QEventLoop::quit);
	connect(timeline, &twoDModel::model::Timeline::stopped, &loop, &QEventLoop::quit);

	if (milliseconds == 0) {
		QApplication::processEvents();
	} else if (timeline->isStarted()) {
		t->start(milliseconds);
		loop.exec();
	}
}

qint64 TwoDExecutionControl::time() const
{
	return mTwoDRobotModel->timeline().timestamp();
}

void TwoDExecutionControl::reset()
{
	emit stopWaiting();
	for (auto &&timer : mTimers) {
		QMetaObject::invokeMethod(timer, &utils::AbstractTimer::stop, Qt::BlockingQueuedConnection);
		timer->deleteLater();
	}
	mTimers.clear();
}

utils::AbstractTimer *TwoDExecutionControl::timer(int milliseconds)
{
	auto result = mTwoDRobotModel->timeline().produceTimer();
	mTimers.append(result);
	result->setRepeatable(true);
	result->start(milliseconds);
	return result;
}


bool TwoDExecutionControl::isInEventDrivenMode() const
{
	return mInEventDrivenMode;
}

QVector<int32_t> TwoDExecutionControl::getPhoto()
{
	return trikControl::Utilities::rescalePhoto(mBrick.getStillImage());
}

void TwoDExecutionControl::system(const QString &command, bool synchronously)
{
	Q_UNUSED(command)
	Q_UNUSED(synchronously)
}

void TwoDExecutionControl::writeToFile(const QString &file, const QString &text)
{
	QFile out(mBrick.getCurrentDir().absoluteFilePath(file));
	out.open(QIODevice::WriteOnly | QIODevice::Append);
	out.write(text.toUtf8());
}

void TwoDExecutionControl::writeData(const QString &file, const QVector<uint8_t> &bytes)
{
	QFile out(mBrick.getCurrentDir().absoluteFilePath(file));
	out.open(QIODevice::WriteOnly | QIODevice::Append);
	out.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

QStringList TwoDExecutionControl::readAll(const QString &file) const
{
	return mBrick.readAll(file);
}

void TwoDExecutionControl::removeFile(const QString &file)
{
	QFile out(mBrick.getCurrentDir().absoluteFilePath(file));
	out.remove();
}

void TwoDExecutionControl::run()
{
	mInEventDrivenMode = true;
}

void TwoDExecutionControl::quit()
{
	emit quitSignal();
}
