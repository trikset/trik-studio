/* Copyright 2026 CyberTech Labs Ltd.
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

#include "timelineTests.h"

#include <QtCore/QEventLoop>
#include <QtCore/QTimer>

#include <twoDModel/engine/model/timeline.h>
#include <utils/abstractTimer.h>

using namespace qrTest::robotsTests::commonTwoDModelTests;
using namespace twoDModel::model;

void TimelineTests::SetUp()
{
	mTimeline.reset(new Timeline());
}

void TimelineTests::TearDown()
{
	mTimeline->stop(qReal::interpretation::StopReason::finished);
	mTimeline.reset();
}

void TimelineTests::processEventsFor(int ms)
{
	QEventLoop loop;
	QTimer::singleShot(ms, &loop, &QEventLoop::quit);
	loop.exec();
}

TEST_F(TimelineTests, pauseAndResumeDoNothingWhenNotStarted)
{
	// Receiver for the connections below, disconnects them when the test ends
	QObject context;
	int pausedCount = 0;
	int resumedCount = 0;
	QObject::connect(&*mTimeline, &Timeline::paused, &context, [&pausedCount]() { ++pausedCount; });
	QObject::connect(&*mTimeline, &Timeline::resumed, &context, [&resumedCount]() { ++resumedCount; });

	mTimeline->pause();
	EXPECT_FALSE(mTimeline->isPaused());
	mTimeline->resume();
	EXPECT_FALSE(mTimeline->isPaused());

	EXPECT_EQ(pausedCount, 0);
	EXPECT_EQ(resumedCount, 0);
}

TEST_F(TimelineTests, pauseAndResumeChangeStateAndEmitSignalsOnce)
{
	// Receiver for the connections below, disconnects them when the test ends
	QObject context;
	int pausedCount = 0;
	int resumedCount = 0;
	QObject::connect(&*mTimeline, &Timeline::paused, &context, [&pausedCount]() { ++pausedCount; });
	QObject::connect(&*mTimeline, &Timeline::resumed, &context, [&resumedCount]() { ++resumedCount; });

	mTimeline->start();
	EXPECT_TRUE(mTimeline->isStarted());
	EXPECT_FALSE(mTimeline->isPaused());

	mTimeline->pause();
	mTimeline->pause();
	EXPECT_TRUE(mTimeline->isStarted());
	EXPECT_TRUE(mTimeline->isPaused());
	EXPECT_EQ(pausedCount, 1);

	mTimeline->setPaused(false);
	mTimeline->resume();
	EXPECT_TRUE(mTimeline->isStarted());
	EXPECT_FALSE(mTimeline->isPaused());
	EXPECT_EQ(resumedCount, 1);

	mTimeline->setPaused(true);
	EXPECT_TRUE(mTimeline->isPaused());
	EXPECT_EQ(pausedCount, 2);
}

TEST_F(TimelineTests, modelTimeDoesNotFlowWhilePaused)
{
	mTimeline->start();
	processEventsFor(100);
	const auto timestampBeforePause = mTimeline->timestamp();
	EXPECT_GT(timestampBeforePause, 0u);

	mTimeline->pause();
	const auto timestampAtPause = mTimeline->timestamp();
	int ticksWhilePaused = 0;
	auto connection = QObject::connect(&*mTimeline, &Timeline::tick, [&ticksWhilePaused]() { ++ticksWhilePaused; });
	processEventsFor(200);
	QObject::disconnect(connection);

	EXPECT_EQ(ticksWhilePaused, 0);
	EXPECT_EQ(mTimeline->timestamp(), timestampAtPause);

	mTimeline->resume();
	processEventsFor(100);
	EXPECT_GT(mTimeline->timestamp(), timestampAtPause);
}

TEST_F(TimelineTests, modelTimersDoNotFireWhilePaused)
{
	mTimeline->start();
	mTimeline->pause();

	QScopedPointer<utils::AbstractTimer> timer(mTimeline->produceTimer());
	int timeoutsCount = 0;
	QObject::connect(&*timer, &utils::AbstractTimer::timeout, [&timeoutsCount]() { ++timeoutsCount; });
	timer->start(Timeline::timeInterval);

	processEventsFor(200);
	EXPECT_EQ(timeoutsCount, 0);
	EXPECT_TRUE(timer->isActive());

	mTimeline->resume();
	processEventsFor(200);
	EXPECT_EQ(timeoutsCount, 1);
}

TEST_F(TimelineTests, stopWhilePausedResetsPauseAndAllowsRestart)
{
	mTimeline->start();
	mTimeline->pause();

	// Receiver for the connections below, disconnects them when the test ends
	QObject context;
	int stoppedCount = 0;
	QObject::connect(&*mTimeline, &Timeline::stopped, &context, [&stoppedCount]() { ++stoppedCount; });
	mTimeline->stop(qReal::interpretation::StopReason::userStop);

	EXPECT_EQ(stoppedCount, 1);
	EXPECT_FALSE(mTimeline->isStarted());
	EXPECT_FALSE(mTimeline->isPaused());

	mTimeline->start();
	const auto timestampAtRestart = mTimeline->timestamp();
	processEventsFor(100);
	EXPECT_FALSE(mTimeline->isPaused());
	EXPECT_GT(mTimeline->timestamp(), timestampAtRestart);
}
