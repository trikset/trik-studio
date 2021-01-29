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

#include <QtCore/QTimer>
#include <QtCore/QEventLoop>

#include <QtCore/QThread>

#include <trikKitInterpreterCommon/trikbrick.h>

#include <utils/abstractTimer.h>
#include <kitBase/robotModel/robotModelUtils.h>
#include <trikKit/robotModel/parts/trikShell.h>
#include <trikKit/robotModel/parts/trikLineSensor.h>
#include <kitBase/robotModel/robotParts/gyroscopeSensor.h>
#include <kitBase/robotModel/robotParts/encoderSensor.h>
#include <kitBase/robotModel/robotParts/random.h>
#include <twoDModel/robotModel/parts/marker.h>
#include <twoDModel/engine/model/timeline.h>
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>
#include <qrkernel/platformInfo.h>
#include <src/qtCameraImplementation.h>
#include <src/imitationCameraImplementation.h>
#include <QApplication>

///todo: temporary
#include <trikKitInterpreterCommon/robotModel/twoD/parts/twoDDisplay.h>


using namespace trik;

TrikBrick::TrikBrick(const QSharedPointer<robotModel::twoD::TrikTwoDRobotModel> &model)
	: mTwoDRobotModel(model)
	, mDisplay(model)
	, mKeys(model)
	, mSensorUpdater(model->timeline().produceTimer())
{
	connect(this, &TrikBrick::log, this, &TrikBrick::printToShell);
	mSensorUpdater->setSingleShot(false);
	mSensorUpdater->setInterval(model->updateIntervalForInterpretation()); // seems to be x2 of timeline tick
	connect(mSensorUpdater.data(), &utils::AbstractTimer::timeout
			, mTwoDRobotModel.data(), &robotModel::twoD::TrikTwoDRobotModel::updateSensorsValues);
}

TrikBrick::~TrikBrick()
{
}

void TrikBrick::reset()
{
	mKeys.reset();///@todo: reset motos/device maps?
	//mDisplay.reset(); /// - is actually needed? Crashes app at exit
	for (const auto &m : mMotors) {
		m->powerOff();
	}

	for (const auto &e : mEncoders) {
		e->reset();
	}

	mTimers.clear();
}

void TrikBrick::printToShell(const QString &msg)
{
	using namespace kitBase::robotModel;
	using namespace trik::robotModel;
	parts::TrikShell* sh = RobotModelUtils::findDevice<parts::TrikShell>(*mTwoDRobotModel, "ShellPort");
	if (sh == nullptr) {
		emit error(tr("2d model shell part was not found"));
		return;
	}

	sh->print(msg);
}

QDir TrikBrick::getCurrentDir() const
{
	return mCurrentDir;
}

void TrikBrick::init()
{
	mDisplay.init();
	mKeys.init();
	mTwoDRobotModel->updateSensorsValues();

	mMotors.clear();
	mSensors.clear();
	mEncoders.clear();
	mLineSensors.clear();
	mColorSensors.clear();
	mTimers.clear();
	mGyroscope.reset(); // for some reason it won't reconnect to the robot parts otherwise.
	mAccelerometer.reset();
	mTrikProxyMarker.reset();
	reinitImitationCamera();
	processSensors(true);
}

void TrikBrick::setCurrentDir(const QString &dir)
{
	mCurrentDir = QFileInfo(dir).dir(); // maybe can be constructed directly
}

void TrikBrick::setCurrentInputs(const QString &f)
{
	mIsExcerciseMode = true;
	if (f.isEmpty()) {
		return; // no inputs has been passed, no need to complain
	}

	QFile in(f);
	if (!in.open(QIODevice::ReadOnly | QIODevice::Text)) {
		emit warning(tr("Trying to read from file %1 failed").arg(f)); // todo: remove? It's only in exercise.
		//not really an error, usually
	}

	QStringList result;

	while (!in.atEnd()) {
		const auto line = in.readLine();
		result << QString::fromUtf8(line);
	}

	mInputs = result;
}

void TrikBrick::reinitImitationCamera()
{
	if (not qReal::SettingsManager::value("TrikSimulatedCameraImagesFromProject").toBool()) {
		const QString path = qReal::SettingsManager::value("TrikSimulatedCameraImagesPath").toString();
		mImitationCamera.reset(new trikControl::ImitationCameraImplementation({"*.jpg","*.png"}, path));
	} else {
		const QString path = qReal::PlatformInfo::invariantSettingsPath("trikCameraImitationImagesDir");
		mImitationCamera.reset(new trikControl::ImitationCameraImplementation({"*.jpg","*.png"}, path));
	}
}

void TrikBrick::say(const QString &msg) {
	using namespace kitBase::robotModel;
	using namespace trik::robotModel;
	auto* sh = RobotModelUtils::findDevice<parts::TrikShell>(*mTwoDRobotModel, "ShellPort");
	if (sh == nullptr) {
		emit error(tr("2d model shell part was not found"));
		return;
	}

	QMetaObject::invokeMethod(sh, [sh, msg](){sh->say(msg);});
}

void TrikBrick::playTone(int, int msDuration) {
	auto* robot = mTwoDRobotModel.data();
	QMetaObject::invokeMethod(robot, [robot, msDuration](){robot->engine()->playSound(msDuration);});
}

void TrikBrick::stop() {
	/// @todo: properly implement this?
	mTwoDRobotModel->stopRobot();
//	for (const auto &m : mMotors) {
//		m->powerOff();
//	}
//	for (const auto &e : mEncoders) {
//		e->reset();
//	}
}

trikControl::MotorInterface *TrikBrick::motor(const QString &port)
{
	using namespace kitBase::robotModel;
	if (!mMotors.contains(port)) {
		robotParts::Motor * motor =
				RobotModelUtils::findDevice<robotParts::Motor>(*mTwoDRobotModel, port);
		if (motor == nullptr) {
			emit error(tr("No configured motor on port: %1").arg(port));
			return nullptr;
		}
		mMotors[port].reset(new TrikMotorEmu(motor));
	}
	return mMotors[port].get();
}

trikControl::MarkerInterface *TrikBrick::marker()
{
	kitBase::robotModel::PortInfo markerPort = kitBase::robotModel::RobotModelUtils::findPort(*mTwoDRobotModel
			, "MarkerPort"
			, kitBase::robotModel::Direction::output);
	if (markerPort.isValid()) {
		using Marker = twoDModel::robotModel::parts::Marker;
		Marker* marker = kitBase::robotModel::RobotModelUtils::findDevice<Marker>(*mTwoDRobotModel, markerPort);
		mTrikProxyMarker.reset(new TrikProxyMarker(marker));
		return mTrikProxyMarker.data();
	}

	return nullptr;
}

trikControl::SensorInterface *TrikBrick::sensor(const QString &port)
{
	//testing
	using namespace kitBase::robotModel;
	if (!mSensors.contains(port)) {
		robotParts::ScalarSensor * sens =
				RobotModelUtils::findDevice<robotParts::ScalarSensor>(*mTwoDRobotModel, port);
		if (sens == nullptr) {
			emit error(tr("No configured sensor on port: %1").arg(port));
			return nullptr;
		}
		mSensors[port].reset(new TrikSensorEmu(sens));
	}
	return mSensors[port].get();
}

QStringList TrikBrick::motorPorts(trikControl::MotorInterface::Type type) const
{
	Q_UNUSED(type)
//	QLOG_INFO() << "Motor type is ignored";
	return mMotors.keys();
}

QStringList TrikBrick::sensorPorts(trikControl::SensorInterface::Type type) const
{
	Q_UNUSED(type)
//	QLOG_INFO() << "Sensor type is ignored";
	return mMotors.keys();
}

QStringList TrikBrick::encoderPorts() const {
	return mEncoders.keys();
}

trikControl::VectorSensorInterface *TrikBrick::accelerometer() {
	using namespace kitBase::robotModel;
	if (mAccelerometer.isNull()) {
		auto a = RobotModelUtils::findDevice<robotParts::AccelerometerSensor>(*mTwoDRobotModel
				, "AccelerometerPort");
		if (a == nullptr) {
			emit error(tr("No configured accelerometer"));
			return nullptr;
		}

		mAccelerometer.reset(new TrikAccelerometerAdapter(a));
	}

	return mAccelerometer.data();
}

trikControl::GyroSensorInterface *TrikBrick::gyroscope() {
	using namespace kitBase::robotModel;
	if (mGyroscope.isNull()) {
		auto a = RobotModelUtils::findDevice<robotParts::GyroscopeSensor>(*mTwoDRobotModel
				, "GyroscopePort");
		if (a == nullptr) {
			emit error(tr("No configured gyroscope"));
			return nullptr;
		}

		mGyroscope.reset(new TrikGyroscopeAdapter(a, mTwoDRobotModel));
	}

	return mGyroscope.data();
}

trikControl::LineSensorInterface *TrikBrick::lineSensor(const QString &port) {
	using namespace trik::robotModel::parts;
	using namespace kitBase::robotModel;
	if (port == "video0" || port == "video2") {
		return lineSensor("LineSensorPort"); // seems to be the case for 2d model
	}

	if (!mLineSensors.contains(port)) {
		auto sens = RobotModelUtils::findDevice<TrikLineSensor>(*mTwoDRobotModel, port);
		if (sens == nullptr) {
			emit error(tr("No configured LineSensor on port: %1").arg(port));
			return nullptr;
		}
		mLineSensors[port].reset(new TrikLineSensorAdapter(sens));
	}

	return mLineSensors[port].get();
}

trikControl::ColorSensorInterface *TrikBrick::colorSensor(const QString &port) {
	using namespace trik::robotModel::parts;
	using namespace kitBase::robotModel;
	if (port == "video0" || port == "video2") {
		return colorSensor("ColorSensorPort"); // seems to be the case for 2d model
	}

	if (!mColorSensors.contains(port)) {
		auto sens = RobotModelUtils::findDevice<TrikColorSensor>(*mTwoDRobotModel, port);
		if (sens == nullptr) {
			emit error(tr("No configured ColorSensor on port: %1").arg(port));
			return nullptr;
		}
		mColorSensors[port].reset(new TrikColorSensorAdapter(sens));
	}

	return mColorSensors[port].get();
}

trikControl::ObjectSensorInterface *TrikBrick::objectSensor(const QString &port) {
	emit error(tr("Sensor not implemented in simulation mode. Used port: %1").arg(port));
	return nullptr;
}

trikControl::EncoderInterface *TrikBrick::encoder(const QString &port) {
	using namespace kitBase::robotModel;
	if (!mEncoders.contains(port)) {
		robotParts::EncoderSensor * enc =
				RobotModelUtils::findDevice<robotParts::EncoderSensor>(*mTwoDRobotModel, port);
		if (enc == nullptr) {
			emit error(tr("No configured encoder on port: %1").arg(port));
			return nullptr;
		}

		mEncoders[port].reset(new TrikEncoderAdapter(enc->port(), mTwoDRobotModel->engine()));
	}

	return mEncoders[port].get();
}

trikControl::DisplayInterface *TrikBrick::display()
{
	return &mDisplay;
}

trikControl::LedInterface *TrikBrick::led() {
	using namespace trik::robotModel::parts;
	using namespace kitBase::robotModel;
	if (mLed.isNull()) {
		auto l = RobotModelUtils::findDevice<TrikLed>(*mTwoDRobotModel, "LedPort");
		if (l == nullptr) {
			emit error(tr("No configured led"));
			return nullptr;
		}

		mLed.reset(new TrikLedAdapter(l));
	}

	return mLed.data();
}

QVector<uint8_t> TrikBrick::getStillImage()
{
	const bool webCamera = qReal::SettingsManager::value("TrikWebCameraReal").toBool();

	if (webCamera) {
		const QString webCameraName = qReal::SettingsManager::value("TrikWebCameraRealName").toString();
		trikControl::QtCameraImplementation camera(webCameraName);
		camera.setTempDir(qReal::PlatformInfo::invariantSettingsPath("pathToTempFolder"));

		log(tr("Get photo with camera started"));
		QVector<uint8_t> photo = camera.getPhoto();
		log(tr("Get photo with camera finished"));
		if (photo.isEmpty()) {
			error(tr("Cannot get a photo from camera (possibly because of wrong camera name)"));
		}

		return photo;
	} else {
		QVector<uint8_t> photo = mImitationCamera->getPhoto();
		if (photo.isEmpty()) {
			error(tr("Cannot get a photo from folders/project (possibly because of wrong path/empty project)"));
		}

		return photo;
	}
}


QStringList TrikBrick::readAll(const QString &path)
{
	if (mIsExcerciseMode) {
		return mInputs;
	}
	//if (mCurrentDir) todo: check that the current working dir is a save dir
	QFileInfo normalizedPath(mCurrentDir.absoluteFilePath(path)); // absoluteDir?
	QString file = normalizedPath.filePath();
	QFile in(file);
	if (!in.open(QIODevice::ReadOnly | QIODevice::Text)) {
		emit error(tr("Trying to read from file %1 failed").arg(file));
		return {};
	}

	QStringList result;

	while (!in.atEnd()) {
		const auto line = in.readLine();
		result << QString::fromUtf8(line);
	}

	return result;
}


void TrikBrick::processSensors(bool isRunning)
{
	QMetaObject::invokeMethod(mSensorUpdater.data()
				  , [this, isRunning](){isRunning ? mSensorUpdater->start() : mSensorUpdater->stop();});
}
