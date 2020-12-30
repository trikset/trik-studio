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

#pragma once

#include <QtCore/QHash>
#include <QtCore/QScopedPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QDir>

#include <trikControl/brickInterface.h>
#include <trikKitInterpreterCommon/robotModel/twoD/trikTwoDRobotModel.h>

#include "trikEmulation/trikdisplayemu.h"
#include "trikEmulation/triksensoremu.h"
#include "trikEmulation/trikencoderadapter.h"
#include "trikEmulation/trikmotoremu.h"
#include "trikEmulation/trikkeysinterfacestub.h"
#include "trikEmulation/triklinesensoradapter.h"
#include "trikEmulation/trikColorSensorAdapter.h"
#include "trikEmulation/trikledadapter.h"
#include "trikEmulation/trikaccelerometeradapter.h"
#include "trikEmulation/trikGyroscopeAdapter.h" /// @todo: replace with forward refs
#include "trikEmulation/trikProxyMarker.h"

namespace utils {
class AbstractTimer;
}

namespace trikControl {
class CameraImplementationInterface;
}

namespace trik {

class TrikBrick final : public trikControl::BrickInterface
{
	Q_OBJECT

	// BrickInterface interface
public:
	TrikBrick(const QSharedPointer<robotModel::twoD::TrikTwoDRobotModel> &model);
	~TrikBrick() override;
	void reset() override;
	QString configVersion() const override {return QString();}
	trikControl::DisplayWidgetInterface *graphicsWidget() override {
		return nullptr;
	}

	void init();

	void setCurrentDir(const QString &dir);
	void setCurrentInputs(const QString &f);

	void reinitImitationCamera();

	QDir getCurrentDir() const;

public slots:
	void configure(const QString &, const QString &) override {}
	void playSound(const QString &) override {}
	void playTone(int, int msDuration) override;
	void say(const QString &msg) override;
	void stop() override;
	trikControl::MotorInterface *motor(const QString &port) override;
	trikControl::MarkerInterface *marker() override;
	trikControl::PwmCaptureInterface *pwmCapture(const QString &) override {return nullptr;}
	trikControl::SensorInterface *sensor(const QString &port) override;
	QStringList motorPorts(trikControl::MotorInterface::Type type) const override;
	QStringList pwmCapturePorts() const override {return {};}
	QStringList sensorPorts(trikControl::SensorInterface::Type type) const override;
	QStringList encoderPorts() const override;
	trikControl::VectorSensorInterface *accelerometer() override;
	trikControl::GyroSensorInterface *gyroscope() override;
	trikControl::LineSensorInterface *lineSensor(const QString &port) override;
	trikControl::ColorSensorInterface *colorSensor(const QString &port) override;
	trikControl::ObjectSensorInterface *objectSensor(const QString &port) override;
	trikControl::SoundSensorInterface *soundSensor(const QString &) override {return nullptr;}
	trikControl::EncoderInterface *encoder(const QString &port) override;
	trikControl::BatteryInterface *battery() override {return nullptr;}
	trikControl::KeysInterface *keys() override {return &mKeys;}
	trikControl::DisplayInterface *display() override;
	trikControl::LedInterface *led() override;
	trikControl::GamepadInterface *gamepad() override {return nullptr;}
	trikControl::FifoInterface *fifo(const QString &) override {return nullptr;}
	trikControl::I2cDeviceInterface *i2c(int, int) override {return nullptr;}

	QVector<uint8_t> getStillImage() override;
	trikControl::EventDeviceInterface *eventDevice(const QString &) override {return nullptr;}
	void stopEventDevice(const QString &) override {}

	/// some ScriptExecution control replacements. @todo: factor out in the separate class
	QStringList readAll(const QString &path);

	void processSensors(bool isRunning = true);

signals:
	void error(const QString &msg);
	void warning(const QString &msg);
	void log(const QString &msg);

private:
	void printToShell(const QString &msg);

	QSharedPointer<robotModel::twoD::TrikTwoDRobotModel> mTwoDRobotModel;

	TrikDisplayEmu mDisplay;
	TrikKeysInterfaceStub mKeys;

	QScopedPointer<utils::AbstractTimer> mSensorUpdater;

	QHash<QString, QSharedPointer<TrikMotorEmu>> mMotors;
	QHash<QString, QSharedPointer<TrikSensorEmu>> mSensors;
	QHash<QString, QSharedPointer<TrikEncoderAdapter>> mEncoders;
	QHash<QString, QSharedPointer<TrikLineSensorAdapter>> mLineSensors;
	QHash<QString, QSharedPointer<TrikColorSensorAdapter>> mColorSensors;
	QScopedPointer<TrikLedAdapter> mLed;
	QScopedPointer<TrikAccelerometerAdapter> mAccelerometer;
	QScopedPointer<TrikGyroscopeAdapter> mGyroscope;
	QScopedPointer<TrikProxyMarker> mTrikProxyMarker;

	QScopedPointer<trikControl::CameraImplementationInterface> mImitationCamera;

	QDir mCurrentDir;
	bool mIsExcerciseMode = false;
	QStringList mInputs;
	QVector<QSharedPointer<utils::AbstractTimer>> mTimers;
};

}
