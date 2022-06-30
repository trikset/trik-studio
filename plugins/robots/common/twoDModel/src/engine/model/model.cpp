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

#include "twoDModel/engine/model/model.h"

#include <qrkernel/settingsManager.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/logicalModelAssistInterface.h>
#include <kitBase/interpreterControlInterface.h>

#include "src/engine/constraints/constraintsChecker.h"
#include "src/robotModel/nullTwoDRobotModel.h"
#include "src/engine/items/startPosition.h"
#include "physics/simplePhysicsEngine.h"
#include "physics/box2DPhysicsEngine.h"

using namespace twoDModel::model;

static auto XML_VERSION = "20190819";

Model::Model(QObject *parent)
	: QObject(parent)
	, mChecker(nullptr)
	, mErrorReporter(nullptr)
	, mRealisticPhysicsEngine(nullptr)
	, mSimplePhysicsEngine(nullptr)
{
	initPhysics();
	connect(&mSettings, &Settings::physicsChanged, this, &Model::resetPhysics);
	resetPhysics();
}

Model::~Model()
{
	delete mRealisticPhysicsEngine;
	delete mSimplePhysicsEngine;
	delete mRobotModel;
}

void Model::init(qReal::ErrorReporterInterface &errorReporter
		, kitBase::InterpreterControlInterface &interpreterControl
		, qReal::LogicalModelAssistInterface &logicalModel)
{
	mErrorReporter = &errorReporter;
	mLogicalModel = &logicalModel;
	mWorldModel.init(errorReporter);
	connect(&timeline(), &Timeline::started, this, [&]() { mStartTimestamp = timeline().timestamp(); });
	mChecker.reset(new constraints::ConstraintsChecker(errorReporter, *this));
	connect(mChecker.data(), &constraints::ConstraintsChecker::success, this, [&]() {
		errorReporter.addInformation(tr("The task was accomplished in %1 sec!")
									.arg(QString::number((timeline().timestamp() - mStartTimestamp) / 1000.0)));
		// Stopping cannot be performed immediately because we still have constraints to check in event loop
		// and they need scene to be alive (in checker stopping interpretation means deleting all).
		QTimer::singleShot(0, &interpreterControl,
				[&interpreterControl](){ Q_EMIT interpreterControl.stopAllInterpretation(); });
	});
	connect(mChecker.data(), &constraints::ConstraintsChecker::fail, this, [&](const QString &message) {
		errorReporter.addError(message);
		// Stopping cannot be performed immediately because we still have constraints to check in event loop
		// and they need scene to be alive (in checker stopping interpretation means deleting all).
		QTimer::singleShot(0, &interpreterControl,
				[&interpreterControl](){ Q_EMIT interpreterControl.stopAllInterpretation(); });
	});
	connect(mChecker.data(), &constraints::ConstraintsChecker::message, this, [&](const QString &message) {
		errorReporter.addInformation(message);
	});
	connect(mChecker.data(), &constraints::ConstraintsChecker::checkerError
			, this, [&errorReporter](const QString &message) {
				errorReporter.addCritical(tr("Error in checker: %1").arg(message));
	});
}

WorldModel &Model::worldModel()
{
	return mWorldModel;
}

Timeline &Model::timeline()
{
	return mTimeline;
}

QList<RobotModel *> Model::robotModels() const
{
	if (mRobotModel) {
		return {mRobotModel};
	} else {
		return {};
	}
}

Settings &Model::settings()
{
	return mSettings;
}

qReal::ErrorReporterInterface *Model::errorReporter()
{
	return mErrorReporter;
}

QDomDocument Model::serialize() const
{
	QDomDocument save;
	QDomElement root = save.createElement("root");
	save.appendChild(root);
	root.setAttribute("version", XML_VERSION);

	mWorldModel.serializeWorld(root);

	QDomElement robots;
	const QString xml = mLogicalModel->logicalRepoApi().metaInformation("worldModel").toString();
	QDomDocument worldModel;
	if (!xml.isEmpty() && worldModel.setContent(xml)) {
		robots = worldModel.firstChildElement("root").firstChildElement("robots");
	}
	else {
		robots = save.createElement("robots");
	}
	if (mRobotModel) {
		mRobotModel->serialize(robots);
	}
	root.appendChild(robots);

	mSettings.serialize(root);
	mChecker->serializeConstraints(root);

	return save;
}

void Model::deserialize(const QDomDocument &model)
{
	const auto &settings = model.documentElement().firstChildElement("settings");
	mSettings.deserialize(settings);

	if (mChecker) {
		const auto &constraints = model.documentElement().firstChildElement("constraints");
		/// @todo: should we handle if it returned false?
		mChecker->parseConstraints(constraints);
	}

	const auto &worldList = model.elementsByTagName("world");
	const auto &world = worldList.isEmpty() ? QDomElement() : worldList.at(0).toElement();
	const auto &blobsList = model.elementsByTagName("blobs");
	mWorldModel.deserialize(world, blobsList.isEmpty() ? QDomElement() : blobsList.at(0).toElement());

	const auto &robotsList = model.elementsByTagName("robots");
	if (!mRobotModel || robotsList.isEmpty()) return;
	mRobotModel->reinit();
	for (QDomElement element = robotsList.at(0).firstChildElement("robot")
			; !element.isNull(); element = element.nextSiblingElement("robot")) {
		if (mRobotModel->info().robotId() == element.toElement().attribute("id")) {
			mRobotModel->deserialize(element);
			return;
		}
	}
}

void Model::addRobotModel(robotModel::TwoDRobotModel &robotModel, const QPointF &pos)
{
	if (mRobotModel) {
		mErrorReporter->addCritical(tr("This robot model already exists"));
		return;
	}

	mRobotModel = new RobotModel(robotModel, mSettings, this);
	mRobotModel->setPosition(pos);

	connect(&mTimeline, &Timeline::started, mRobotModel, &RobotModel::reinit);
	connect(&mTimeline, &Timeline::stopped, mRobotModel, &RobotModel::stopRobot);

	connect(&mTimeline, &Timeline::tick, mRobotModel, &RobotModel::recalculateParams);
	connect(&mTimeline, &Timeline::nextFrame, mRobotModel, &RobotModel::nextFragment);

	mRobotModel->setPhysicalEngine(mSettings.realisticPhysics() ? *mRealisticPhysicsEngine : *mSimplePhysicsEngine);

	mWorldModel.setRobotModel(mRobotModel);

	emit robotAdded(mRobotModel);
}

void Model::removeRobotModel()
{
	if (!mRobotModel) {
		return;
	}

	mWorldModel.setRobotModel(nullptr);
	emit robotRemoved(mRobotModel);
	delete mRobotModel;
}

void Model::replaceRobotModel(twoDModel::robotModel::TwoDRobotModel &newModel)
{
	const QPointF pos = mRobotModel ? mRobotModel->position() : QPointF();
	removeRobotModel();
	addRobotModel(newModel, pos);
}

bool Model::hasConstraints() const
{
	return mChecker->hasConstraints();
}

void Model::setConstraintsEnabled(bool enabled)
{
	mChecker->setEnabled(enabled);
}

void Model::resetPhysics()
{
	auto engine = mSettings.realisticPhysics() ? mRealisticPhysicsEngine : mSimplePhysicsEngine;
	if (mRobotModel) mRobotModel->setPhysicalEngine(*engine);

	engine->wakeUp();
}

void Model::initPhysics()
{
	mRealisticPhysicsEngine = new physics::Box2DPhysicsEngine(mWorldModel, robotModels());
	mSimplePhysicsEngine = new physics::SimplePhysicsEngine(mWorldModel, robotModels());
	connect(this, &model::Model::robotAdded, mRealisticPhysicsEngine, &physics::PhysicsEngineBase::addRobot);
	connect(this, &model::Model::robotRemoved, mRealisticPhysicsEngine, &physics::PhysicsEngineBase::removeRobot);
	connect(this, &model::Model::robotAdded, mSimplePhysicsEngine, &physics::PhysicsEngineBase::addRobot);
	connect(this, &model::Model::robotRemoved, mSimplePhysicsEngine, &physics::PhysicsEngineBase::removeRobot);

	connect(&mTimeline, &Timeline::stopped, mRealisticPhysicsEngine, &physics::PhysicsEngineBase::clearForcesAndStop);
	connect(&mTimeline, &Timeline::tick, this, &Model::recalculatePhysicsParams);
	connect(&mTimeline, &Timeline::nextFrame
			, mRealisticPhysicsEngine, &physics::PhysicsEngineBase::nextFrame, Qt::UniqueConnection);
}

void Model::recalculatePhysicsParams()
{
	if (mSettings.realisticPhysics()) {
		mRealisticPhysicsEngine->recalculateParameters(Timeline::timeInterval);
	} else {
		mSimplePhysicsEngine->recalculateParameters(Timeline::timeInterval);
	}
}
