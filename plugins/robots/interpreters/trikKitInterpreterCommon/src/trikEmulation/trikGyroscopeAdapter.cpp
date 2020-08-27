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

using namespace twoDModel;

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
	: mGyro(gyro)
	, mModel(model)
	, mResult(7, 0)
	, mQuaternion(1, 0, 0, 0)
	, mStartTime(getTimeValue(model.data()))
{
	using namespace std::placeholders;
	connect(mGyro, &kitBase::robotModel::robotParts::GyroscopeSensor::newData,
			this, std::bind(&TrikGyroscopeAdapter::countTilt, this, std::bind(&QVariant::value<QVector<int>>,_1)));
}

QVector<int> TrikGyroscopeAdapter::read() const
{
	return mResult;
}

void TrikGyroscopeAdapter::calibrate(int msec)
{
	Q_UNUSED(msec); // Don't wait for now. 2D model calibrates immedeatly with zero bias (at least I hope so)
	mModel->engine()->calibrateGyroscopeSensor();
}

bool TrikGyroscopeAdapter::isCalibrated() const
{
	return true;
}

QVector<int> TrikGyroscopeAdapter::readRawData() const
{
	const auto t = convertToTrikRuntimeTime(getTimeValue(mModel.data()));
	return {0, 0, static_cast<int>(mModel->engine()->readGyroscopeSensor()[0] * gyroscopeConstant), t};
}

void TrikGyroscopeAdapter::countTilt(const QVector<int> &oldFormat)
{
	mResult = QVector<int>(oldFormat);
	mResult[3] = convertToTrikRuntimeTime(mResult[3]);
}

qreal TrikGyroscopeAdapter::degreeToMilidegree(qreal value)
{
	return value * 1000;
}

int TrikGyroscopeAdapter::convertToTrikRuntimeTime(quint64 time) const
{
	return static_cast<int>(time * 1000 / 256);
}

