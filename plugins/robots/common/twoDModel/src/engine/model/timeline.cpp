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

#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>
#include <QThread>

#include "twoDModel/engine/model/timeline.h"
#include "modelTimer.h"

using namespace twoDModel::model;

Timeline::Timeline(QObject *parent)
	: QObject(parent)
	, mSpeedFactor(normalSpeedFactor)
	, mCyclesCount(0)
	, mIsStarted(false)
	, mTimestamp(0)
{
	static volatile auto registered = false;
	if (!registered) {
		// For queued signals with argument of this type
		qRegisterMetaType<qReal::interpretation::StopReason>();
		registered = true;
	}

	connect(&mTimer, &QTimer::timeout, this, &Timeline::onTimer);
	mTimer.setTimerType(Qt::TimerType::PreciseTimer);
	mTimer.setInterval(defaultRealTimeInterval);

	connect(&mFrameTimer, &QTimer::timeout, this, &Timeline::gotoNextFrame);
	mFrameTimer.setTimerType(Qt::TimerType::PreciseTimer);
	mFrameTimer.setSingleShot(true);
}

void Timeline::start()
{
	if (!mIsStarted) {
		mIsStarted = true;
		mIsPaused = false;
		Q_EMIT started();
		gotoNextFrame();
	}
}

void Timeline::stop(qReal::interpretation::StopReason reason)
{
	if (mIsStarted) {
		mIsStarted = false;
		mIsPaused = false;
		QCoreApplication::processEvents();
		Q_EMIT beforeStop(reason);
		mTimer.stop();
		Q_EMIT stopped(reason);
	}
}

void Timeline::pause()
{
	if (mIsStarted && !mIsPaused) {
		mIsPaused = true;
		mTimer.stop();
		mFrameTimer.stop();
		mCyclesCount = 0;
		// Let the scene reflect the ticks that were modeled since the last frame
		Q_EMIT nextFrame();
		Q_EMIT paused();
	}
}

void Timeline::resume()
{
	if (mIsStarted && mIsPaused) {
		mIsPaused = false;
		Q_EMIT resumed();
		gotoNextFrame();
	}
}

void Timeline::setPaused(bool paused)
{
	if (paused) {
		pause();
	} else {
		resume();
	}
}

void Timeline::onTimer()
{
	if (!mIsStarted || mIsPaused) {
		mTimer.stop();
		return;
	}

	for (int i = 0; i < ticksPerCycle; ++i) {
		QCoreApplication::processEvents();
		if (mIsStarted && !mIsPaused) {
			mTimestamp += timeInterval;
			Q_EMIT tick();
			++mCyclesCount;
			if (mCyclesCount >= mSpeedFactor) {
				mTimer.stop();
				mCyclesCount = 0;
				const int msFromFrameStart =
					static_cast<int>(QDateTime::currentMSecsSinceEpoch() - mFrameStartTimestamp);
				const int pauseBeforeFrameEnd = mFrameLength - msFromFrameStart;
				if (pauseBeforeFrameEnd > 0) {
					mFrameTimer.start(pauseBeforeFrameEnd - 1);
				} else {
					gotoNextFrame();
				}

				return;
			}
		}
	}
}

void Timeline::gotoNextFrame()
{
	if (mIsPaused) {
		return;
	}

	Q_EMIT nextFrame();
	mFrameStartTimestamp = QDateTime::currentMSecsSinceEpoch();
	if (!mTimer.isActive()) {
		mTimer.start();
	}
}

utils::AbstractTimer *Timeline::produceTimerImpl()
{
	return new ModelTimer(this);
}

int Timeline::speedFactor() const
{
	return mSpeedFactor;
}

bool Timeline::isStarted() const
{
	return mIsStarted;
}

bool Timeline::isPaused() const
{
	return mIsPaused;
}

quint64 Timeline::timestamp() const
{
	return mTimestamp;
}

utils::AbstractTimer *Timeline::produceTimer()
{
	return produceTimerImpl();
}

void Timeline::setImmediateMode(bool immediateMode)
{
	mTimer.setInterval(immediateMode ? 0 : defaultRealTimeInterval);
	setSpeedFactor(immediateMode ? immediateSpeedFactor : normalSpeedFactor);
	mFrameLength = immediateMode ? 0 : defaultFrameLength;
}

void Timeline::setSpeedFactor(int factor)
{
	if (mSpeedFactor != factor) {
		mSpeedFactor = factor;
		Q_EMIT speedFactorChanged(factor);
	}
}
