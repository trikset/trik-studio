/* Copyright 2016-2017 CyberTech Labs Ltd.
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

#include <QtCore/QtMath>

#include <trikKitInterpreterCommon/trikEmulation/trikGyroscopeAdapter.h>
#include <twoDModel/engine/twoDModelEngineInterface.h>
#include <twoDModel/engine/model/constants.h>


template <typename T>
static T getPitch(const QQuaternion &q)
{
	return qAtan2(2 * q.y()*q.z() + 2 * q.scalar() * q.x()
			, 1 - 2 * q.x() * q.x() - 2 * q.y() * q.y());
}

template <typename T>
static T getRoll(const QQuaternion &q)
{
	return qAsin(2 * q.scalar() * q.y() - 2 * q.x() * q.z());
}

template <typename T>
static T getYaw(const QQuaternion &q)
{
	return qAtan2(2 * q.x() * q.y() + 2 * q.scalar() * q.z()
			, 1 - 2 * q.y() * q.y() - 2 * q.z() * q.z());
}

static quint64 getTimeValue(trik::robotModel::twoD::TrikTwoDRobotModel * const model) {
	return model->timeline().timestamp();
}


TrikGyroscopeAdapter::TrikGyroscopeAdapter(kitBase::robotModel::robotParts::GyroscopeSensor *gyro
		, const QSharedPointer<trik::robotModel::twoD::TrikTwoDRobotModel> &model)
	: mTimeInited(false)
	, mGyro(gyro)
	, mModel(model)
	, mResult(7, 0)
	, mQuaternion(1, 0, 0, 0)
	, mStartTime(getTimeValue(model.data()))
	, mLastUpdateTimeStamp(getTimeValue(model.data()))
{
	connect(gyro, SIGNAL(newData(QVector<int>)), this, SLOT(countTilt(QVector<int>)));
}

QVector<int> TrikGyroscopeAdapter::read() const
{
	return mResult;
}

void TrikGyroscopeAdapter::calibrate(int msec)
{
	Q_UNUSED(msec); // Don't wait for now. 2D model calibrates immedeatly with zero bias (at least I hope so)
	mTimeInited = false;
}

bool TrikGyroscopeAdapter::isCalibrated() const
{
	return !mTimeInited;
}

QVector<int> TrikGyroscopeAdapter::readRawData() const
{
	QVector<int> result = mModel->engine()->readGyroscopeSensor();
	result.append(convertToTrikRuntimeTime(getTimeValue(mModel.data())));
	return result;
}

void TrikGyroscopeAdapter::countTilt(const QVector<int> &oldFormat)
{
	const quint64 timeStamp = getTimeValue(mModel.data());

	if (!mTimeInited) {
		mTimeInited = true;
		mLastUpdateTimeStamp = timeStamp;
		mInitialTilt = oldFormat[3];
	} else {
		mResult[0] = oldFormat[0];
		mResult[1] = oldFormat[1];
		mResult[2] = oldFormat[2];
		mResult[3] = convertToTrikRuntimeTime(timeStamp);
		mResult[4] = 0;
		mResult[5] = 0;
		mResult[6] = oldFormat[3] - mInitialTilt;
	}
}

qreal TrikGyroscopeAdapter::degreeToMilidegree(qreal value)
{
	return value * 1000;
}

int TrikGyroscopeAdapter::convertToTrikRuntimeTime(quint64 time) const
{
	return static_cast<int>(time * 1000 / 256);
}

