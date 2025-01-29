/* Copyright 2013-2015 CyberTech Labs Ltd.
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

#include "twoDModelEngineApi.h"

#include <QtCore/qmath.h>
#include <QThread>

#include <qrkernel/settingsManager.h>
#include <qrkernel/logging.h>
#include <qrutils/mathUtils/math.h>
#include <qrutils/mathUtils/geometry.h>
/// @todo: Get rid of it!
#include <kitBase/robotModel/robotParts/touchSensor.h>

#include "twoDModel/engine/twoDModelGuiFacade.h"
#include "twoDModel/engine/model/model.h"
#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/view/twoDModelWidget.h"

#include "view/scene/twoDModelScene.h"
#include "view/scene/robotItem.h"
#include "view/scene/fakeScene.h"

#include "src/engine/items/wallItem.h"
#include "src/engine/items/colorFieldItem.h"
#include "src/engine/items/ellipseItem.h"
#include "src/engine/items/stylusItem.h"
#include "src/engine/items/regions/ellipseRegion.h"
#include "src/engine/items/regions/rectangularRegion.h"

#include "kitBase/robotModel/robotModelUtils.h"

using namespace twoDModel;
using namespace kitBase::robotModel;
using namespace twoDModel::model;

TwoDModelEngineApi::TwoDModelEngineApi(model::Model &model, view::TwoDModelWidget &view)
	: mModel(model)
	, mView(view)
	, mFakeScene(new view::FakeScene(mModel.worldModel()))
	, mGuiFacade(new engine::TwoDModelGuiFacade(mView))
{
#ifdef BACKGROUND_SCENE_DEBUGGING
	enableBackgroundSceneDebugging();
#endif
}

TwoDModelEngineApi::~TwoDModelEngineApi()
{
}

void TwoDModelEngineApi::setNewMotor(int speed, uint degrees, const PortInfo &port, bool breakMode)
{
	auto target = mModel.robotModels()[0];
	QMetaObject::invokeMethod(target, [&](){target->setNewMotor(speed, degrees, port, breakMode);}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);
}

int TwoDModelEngineApi::readEncoder(const PortInfo &port) const
{
	int t;
	auto target = mModel.robotModels()[0];
	QMetaObject::invokeMethod(target, [&](){t = target->readEncoder(port);}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);
	return t;
}

void TwoDModelEngineApi::resetEncoder(const PortInfo &port)
{
	auto target = mModel.robotModels()[0];
	QMetaObject::invokeMethod(target, [&](){target->resetEncoder(port);}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);
}

int TwoDModelEngineApi::readTouchSensor(const PortInfo &port) const
{
	if (!mModel.robotModels()[0]->configuration().type(port).isA<robotParts::TouchSensor>()) {
		return touchSensorNotPressedSignal;
	}

	QPair<QPointF, qreal> const neededPosDir = countPositionAndDirection(port);
	const QPointF position(neededPosDir.first);
	const qreal rotation = neededPosDir.second / 180 * mathUtils::pi;
	const QRectF rect = mModel.robotModels()[0]->sensorRect(port, position);

	QPainterPath sensorPath;
	const qreal touchRegionRadius = qCeil(rect.height() / qSqrt(2));
	const qreal stickCenter = rect.width() / 2 - rect.height() / 2;
	// (0,0) in sensor coordinates is sensor`s center
	const QPointF ellipseCenter = QPointF(stickCenter * cos(rotation), stickCenter * sin(rotation));
	sensorPath.addEllipse(position + ellipseCenter, touchRegionRadius, touchRegionRadius);

	const bool pressed = mModel.worldModel().checkCollision(sensorPath);
	return pressed ? touchSensorPressedSignal : touchSensorNotPressedSignal;
}

int TwoDModelEngineApi::readRangeSensor(const PortInfo &port, int maxDistance, qreal scanningAngle) const
{
	QPair<QPointF, qreal> neededPosDir = countPositionAndDirection(port);

	int res;
	auto && target = &mModel.worldModel();
	QMetaObject::invokeMethod(target, [&](){res = target->rangeReading(
	neededPosDir.first, neededPosDir.second, maxDistance, scanningAngle);}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);

	return mModel.settings().realisticSensors() ? spoilRangeReading(res) : res;
}

QVector<int> TwoDModelEngineApi::readLidarSensor(const PortInfo &port, int maxDistance, qreal scanningAngle) const
{
	QPair<QPointF, qreal> neededPosDir = countPositionAndDirection(port);

	QVector<int> res;
	auto && target = &mModel.worldModel();
	QMetaObject::invokeMethod(target, [&](){res = target->lidarReading(
	neededPosDir.first, neededPosDir.second, maxDistance, scanningAngle);}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);

	if (mModel.settings().realisticSensors()) {
		for (int i = 0; i < res.size(); i++) {
			res[i] = spoilRangeReading(res[i]);
		}
	}
	return res;
}

QVector<int> TwoDModelEngineApi::readAccelerometerSensor() const
{
	QVector<int> t;
	auto target = mModel.robotModels()[0];
	QMetaObject::invokeMethod(target, [&](){t = target->accelerometerReading();}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);
	return t;
}

QVector<int> TwoDModelEngineApi::readGyroscopeSensor() const
{
	QVector<int> t;
	auto target = mModel.robotModels()[0];
	QMetaObject::invokeMethod(target, [&](){t = target->gyroscopeReading();}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);
	return t;
}

QVector<int> TwoDModelEngineApi::calibrateGyroscopeSensor()
{
	QVector<int> t;
	auto target = mModel.robotModels()[0];
	QMetaObject::invokeMethod(target, [&](){t = target->gyroscopeCalibrate();}
	, QThread::currentThread() != target->thread() ? Qt::BlockingQueuedConnection : Qt::DirectConnection);
	return t;
}

int TwoDModelEngineApi::spoilRangeReading(const int distance) const
{
	const qreal ran = mathUtils::Math::gaussianNoise(spoilRangeDispersion);
	return mathUtils::Math::truncateToInterval(0, 255, qRound(distance + ran));
}

QColor TwoDModelEngineApi::readColorSensor(const PortInfo &port) const
{
	const QImage image = areaUnderSensor(port, 0.3);
	if (image.isNull()) return QColor();

	qreal averageB = 0, averageG = 0, averageR = 0;
	auto arr = image.constBits();
	auto nPix = image.byteCount() / 4;
	for (int i = 0; i < nPix; i++) {
		averageB += arr[4 * i];
		averageG += arr[4 * i + 1];
		averageR += arr[4 * i + 2];
	}
	averageR /= nPix;
	averageG /= nPix;
	averageB /= nPix;

	if (mModel.settings().realisticSensors()) {
		const qreal noise = mathUtils::Math::gaussianNoise(spoilColorDispersion);
		averageR += noise;
		averageG += noise;
		averageB += noise;
	}

	auto r = mathUtils::Math::truncateToInterval(0, 255, qRound(averageR));
	auto g = mathUtils::Math::truncateToInterval(0, 255, qRound(averageG));
	auto b = mathUtils::Math::truncateToInterval(0, 255, qRound(averageB));

	return QColor(r, g, b);
}

uint TwoDModelEngineApi::spoilColor(const uint color) const
{
	const qreal noise = mathUtils::Math::gaussianNoise(spoilColorDispersion);

	int r = qRound(((color >> 16) & 0xFF) + noise);
	int g = qRound(((color >> 8) & 0xFF) + noise);
	int b = qRound(((color >> 0) & 0xFF) + noise);
	const int a = (color >> 24) & 0xFF;

	r = mathUtils::Math::truncateToInterval(0, 255, r);
	g = mathUtils::Math::truncateToInterval(0, 255, g);
	b = mathUtils::Math::truncateToInterval(0, 255, b);

	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF) + ((a & 0xFF) << 24);
}

QImage TwoDModelEngineApi::areaUnderSensor(const PortInfo &port, qreal widthFactor) const
{
	DeviceInfo device = mModel.robotModels()[0]->configuration().type(port);
	if (device.isNull()) {
		device = mModel.robotModels()[0]->info().specialDevices()[port];
		if (device.isNull()) {
			return QImage();
		}
	}

	const QPair<QPointF, qreal> neededPosDir = countPositionAndDirection(port);
	const QPointF position = neededPosDir.first;
	const qreal direction = neededPosDir.second;
	const QRect imageRect = mModel.robotModels()[0]->info().sensorImageRect(device);
	const qreal width = imageRect.width() * widthFactor / 2.0;

	const QRectF sensorRectangle = QTransform().rotate(direction).map(QPolygonF(QRectF(imageRect))).boundingRect();
	const qreal rotationFactor = sensorRectangle.width() / imageRect.width();

	const qreal realWidth = width * rotationFactor;
	const QRectF scanningRect = QRectF(position.x() - realWidth, position.y() - realWidth
			, 2 * realWidth, 2 * realWidth);
	const QImage image(mFakeScene->render(scanningRect));
	const QPoint offset = QPointF(width, width).toPoint() - QPoint(1, 1);
	const QImage rotated(image.transformed(QTransform().rotate(-(90 + direction))));
	const QRect realImage(rotated.rect().center() - offset, rotated.rect().center() + offset);
	QImage result(realImage.size(), QImage::Format_RGB32);
	result.fill(Qt::white);
	QPainter painter(&result);
	painter.drawImage(QRect(QPoint(), result.size()), rotated, realImage);
	painter.end();

#ifdef BACKGROUND_SCENE_DEBUGGING
	mView.scene()->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(result)));
#endif

	return result;
}

int TwoDModelEngineApi::readLightSensor(const PortInfo &port) const
{
	// Must return 1023 on white and 0 on black normalized to percents
	// http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color

	const QImage image = areaUnderSensor(port, 1.0);
	if (image.isNull()) {
		return 0;
	}

	uint sum = 0;
	const uint *data = reinterpret_cast<const uint *>(image.bits());
	const int n = image.byteCount() / 4;

	for (int i = 0; i < n; ++i) {
		const uint color = mModel.settings().realisticSensors() ? spoilLight(data[i]) : data[i];
		const uint b = (color >> 0) & 0xFF;
		const uint g = (color >> 8) & 0xFF;
		const uint r = (color >> 16) & 0xFF;
		// brightness in [0..256]
		const uint brightness = static_cast<uint>(0.2126 * r + 0.7152 * g + 0.0722 * b);

		sum += 4 * brightness; // 4 = max sensor value / max brightness value
	}

	const qreal rawValue = sum * 1.0 / n; // Average by whole region
	return static_cast<int>(rawValue * 100.0 / maxLightSensorValue); // Normalizing to percents
}

void TwoDModelEngineApi::playSound(int timeInMs)
{
	mModel.robotModels()[0]->playSound(timeInMs);
}

bool TwoDModelEngineApi::isMarkerDown() const
{
	return mModel.robotModels()[0]->markerColor() != Qt::transparent;
}

void TwoDModelEngineApi::markerDown(const QColor &color)
{
	mModel.robotModels()[0]->markerDown(color);
}

void TwoDModelEngineApi::markerUp()
{
	mModel.robotModels()[0]->markerUp();
}

utils::TimelineInterface &TwoDModelEngineApi::modelTimeline()
{
	return mModel.timeline();
}

engine::TwoDModelDisplayInterface *TwoDModelEngineApi::display()
{
	return mView.display();
}

engine::TwoDModelGuiFacade &TwoDModelEngineApi::guiFacade() const
{
	return *mGuiFacade;
}

uint TwoDModelEngineApi::spoilLight(const uint color) const
{
	const qreal noise = mathUtils::Math::gaussianNoise(spoilLightDispersion);

	if (noise > (1.0 - percentSaltPepperNoise / 100.0)) {
		return white;
	} else if (noise < (-1.0 + percentSaltPepperNoise / 100.0)) {
		return black;
	}

	return color;
}

QPair<QPointF, qreal> TwoDModelEngineApi::countPositionAndDirection(const PortInfo &port) const
{
	RobotModel * const robotModel = mModel.robotModels()[0];
	const QPointF robotCenter = robotModel->info().robotCenter();
	const QVector2D sensorVector = QVector2D(robotModel->configuration().position(port) - robotCenter);
	const QPointF rotatedVector = mathUtils::Geometry::rotateVector(sensorVector, robotModel->rotation()).toPointF();
	const QPointF position = robotModel->position() + robotCenter + rotatedVector;
	const qreal direction = robotModel->configuration().direction(port) + robotModel->rotation();
	return { position, direction };
}

void TwoDModelEngineApi::enableBackgroundSceneDebugging()
{
	// A crappy piece of code that must be never called in master branch,
	// but this is a pretty convenient way to debug a fake scene.
	// If called from constructor (where robotModels are not initialized yet)
	// then NXT and TRIK 2D fake scenes will be shown.
	QGraphicsView * const fakeScene = new QGraphicsView;
	fakeScene->setScene(mFakeScene.data());
	QTimer * const timer = new QTimer(fakeScene);
	QObject::connect(timer, &QTimer::timeout, &*mFakeScene, [this](){mFakeScene->update();});
	timer->setTimerType(Qt::TimerType::PreciseTimer);
	timer->setInterval(300);
	timer->setSingleShot(false);
	fakeScene->setMinimumWidth(700);
	fakeScene->setMinimumHeight(600);
	fakeScene->setWindowFlags(fakeScene->windowFlags() | Qt::WindowStaysOnTopHint);
	fakeScene->setVisible(mModel.robotModels().isEmpty()
			? true
			: mModel.robotModels()[0]->info().robotId().contains("trik"));
	timer->start();
}

kitBase::robotModel::PortInfo TwoDModelEngineApi::videoPort() const
{
	return RobotModelUtils::findPort(mModel.robotModels()[0]->info(), "Video2Port", input);
}
