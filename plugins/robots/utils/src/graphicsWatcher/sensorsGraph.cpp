/* Copyright 2012-2016 Ivan Senin, Dmitry Mordvinov
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

#include "utils/sensorsGraph.h"
#include "ui_sensorsGraph.h"

#include "utils/timelineInterface.h"
#include "utils/abstractTimer.h"
#include "plugins/robots/utils/src/graphicsWatcher/sensorViewer.h"

using namespace utils::sensorsGraph;

struct SensorsGraph::TrackObject {
	int index;
	QString inParserName;
	QString displayName;

	TrackObject(int id, const QString &internalName, const QString &externalName)
		: index(id)
		, inParserName(internalName)
		, displayName(externalName)
	{
	}

	explicit TrackObject(int id)
		: index(id)
	{
	}

	bool operator ==(const TrackObject &other) const
	{
		return index == other.index;
	}
};

SensorsGraph::SensorsGraph(const qrtext::DebuggerInterface &parser, QWidget *parent)
	: QWidget(parent)
	, mUi(new Ui::SensorsGraph)
	, mUpdateTimer(nullptr)
	, mParser(parser)
	, mCurrentSlot(0)
{
	mUi->setupUi(this);
	initGui();
	makeConnections();

	mPlotFrame->centerOn(mPlotFrame->sceneRect().center());
}

SensorsGraph::~SensorsGraph() = default;

void SensorsGraph::setTimeline(utils::TimelineInterface &timeline)
{
	mUpdateTimer.reset(timeline.produceTimer());
	mUpdateTimer->setInterval(mUpdateInterval);
	mUpdateTimer->setSingleShot(false);
	mPlotFrame->setTimeline(timeline);
	connect(&*mUpdateTimer, &AbstractTimer::timeout, this, &SensorsGraph::updateValues);
}

void SensorsGraph::setStartStopButtonsVisible(bool visible)
{
	mStartButton.setVisible(visible);
	mStopButton.setVisible(visible);
}

void SensorsGraph::addTrackingObject(const int index, const QString &inParserName, const QString &displayName)
{
	TrackObject newObject(index, inParserName, displayName);
	if (mWatchList.contains(newObject)) {
		mWatchList.removeOne(newObject);
	}

	mWatchList.append(newObject);
	watchListChanged();
}

void SensorsGraph::removeTracking(const int index)
{
	TrackObject temp(index);
	mWatchList.removeOne(temp);
	watchListChanged();
}

void SensorsGraph::clearTrackingObjects()
{
	mWatchList.clear();
	watchListChanged();
}

void SensorsGraph::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	const qreal verticalCoefficent = 0.8;
	const qreal horizontalCoefficent = 0.8;
	const qreal plotWidth = size().width() * horizontalCoefficent;
	const qreal plotHeight = size().height() * verticalCoefficent;

	mPlotFrame->setSceneRect(-plotWidth, -plotHeight, plotWidth, plotHeight);
	mPlotFrame->setFixedSize(plotWidth, plotHeight);
}

void SensorsGraph::initGui()
{
	setupToolElements();

	mToolLayout.addWidget(&mStopButton, 0);
	mToolLayout.addWidget(&mStartButton, 0);
	mToolLayout.addWidget(&mZoomInButton, 0);
	mToolLayout.addWidget(&mZoomOutButton, 0);
	mToolLayout.addWidget(&mResetButton, 0);
	mToolLayout.addWidget(&mSaveButton, 0);

	mPlotFrame.reset(new SensorViewer(this));

	mUi->mainLayout->addWidget(&*mPlotFrame, 0, 0);
	mUi->mainLayout->addLayout(&mToolLayout, 0, 1);
	mUi->mainLayout->addWidget(&mSlotComboBox, 1, 0);
	mUi->mainLayout->setAlignment(&*mPlotFrame, Qt::AlignTop);
	mUi->mainLayout->setAlignment(&mSlotComboBox, Qt::AlignTop);
	mPlotFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void SensorsGraph::setupToolElements()
{
	const QSize iconSize(20, 20);

	mStopButton.setIcon(QPixmap(":/icons/graphicsWatcher/stop_btn.png"));
	mStopButton.setIconSize(iconSize);
	mStopButton.setToolTip(tr("Stop tracking"));

	mStartButton.setIcon(QPixmap(":/icons/graphicsWatcher/start_btn.png"));
	mStartButton.setIconSize(iconSize);
	mStartButton.setToolTip(tr("Start tracking"));

	mResetButton.setIcon(QPixmap(":/icons/graphicsWatcher/reset_btn.png"));
	mResetButton.setIconSize(iconSize);
	mResetButton.setToolTip(tr("Reset plot"));

	mZoomInButton.setIcon(QPixmap(":/icons/graphicsWatcher/zoomIn_btn.png"));
	mZoomInButton.setIconSize(iconSize);
	mZoomInButton.setToolTip(tr("Zoom In"));

	mZoomOutButton.setIcon(QPixmap(":/icons/graphicsWatcher/zoomOut_btn.png"));
	mZoomOutButton.setIconSize(iconSize);
	mZoomOutButton.setToolTip(tr("Zoom Out"));

	mSaveButton.setIcon(QPixmap(":/mainWindow/images/save_as.png"));
	mSaveButton.setIconSize(iconSize);
	mSaveButton.setToolTip(tr("Export values..."));
}

void SensorsGraph::makeConnections()
{
	connect(&mStartButton, &QAbstractButton::clicked, this, &SensorsGraph::startJob);
	connect(&mStopButton, &QAbstractButton::clicked, this, &SensorsGraph::stopJob);
	connect(&mSaveButton, &QAbstractButton::clicked, &*mPlotFrame, &SensorViewer::exportHistory);
	connect(&mResetButton, &QAbstractButton::clicked, &*mPlotFrame, &SensorViewer::clear);
	connect(&mZoomInButton, &QAbstractButton::clicked, &*mPlotFrame, &SensorViewer::zoomIn);
	connect(&mZoomOutButton, &QAbstractButton::clicked, &*mPlotFrame, &SensorViewer::zoomOut);

	connect(&mSlotComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged)
			, &*mPlotFrame, &SensorViewer::onSensorChange);
	connect(&mSlotComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged)
			, this, &SensorsGraph::setCurrentSensor);
}

void SensorsGraph::watchListChanged()
{
	mSlotComboBox.clear();
	if (mWatchList.isEmpty()) {
		return;
	}

	for (const TrackObject &item : mWatchList) {
		mSlotComboBox.addItem(tr(item.displayName.toUtf8()), item.index);
	}
}

void SensorsGraph::sensorsInput(const int slotIndex, const qreal value)
{
	if (mCurrentSlot == slotIndex) {
		mPlotFrame->setNextValue(value);
	}
}

void SensorsGraph::setCurrentSensor(const int newSlotIndex)
{
	mCurrentSlot = newSlotIndex;
}

void SensorsGraph::startJob()
{
	if (mWatchList.isEmpty()) {
		return;
	}

	mUpdateTimer->start(mUpdateInterval);
	mPlotFrame->startJob();
}

void SensorsGraph::updateValues()
{
	const int notExists = -1;

	TrackObject currentObject(mCurrentSlot);
	const int index = mWatchList.indexOf(currentObject);
	if (index != notExists) {
		double number = mParser.value<double>(mWatchList.at(index).inParserName);
		if (number) {
			sensorsInput(mCurrentSlot, number);
		}
	}
}

void SensorsGraph::stopJob()
{
	mUpdateTimer->stop();
	mPlotFrame->stopJob();
}

void SensorsGraph::resetAll()
{
	mPlotFrame->zoomIn();
	mPlotFrame->zoomOut();
}

void SensorsGraph::configureUpdateIntervals(const int &readSensorsInterval, const int &autoScaleInterval
		, const int &textUpdaterInterval)
{
	mPlotFrame->configureUserOptions(readSensorsInterval, autoScaleInterval, textUpdaterInterval);
}
