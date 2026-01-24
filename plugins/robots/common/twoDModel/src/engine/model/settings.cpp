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

#include <QtXml/QDomElement>
#include <qrkernel/settingsManager.h>
#include "twoDModel/engine/model/settings.h"
#include "twoDModel/engine/model/metricSystem.h"

using namespace twoDModel::model;

Settings::Settings(QObject *parent)
	: QObject(parent)
	, mSizeUnitSystem(new SizeUnit())
{}

bool Settings::realisticPhysics() const
{
	return mRealisticPhysics;
}

bool Settings::realisticSensors() const
{
	return mRealisticSensors;
}

qreal Settings::pixelsInCm() const
{
	return mSizeUnitSystem->pixelsInCm();
}

bool Settings::realisticMotors() const
{
	return mRealisticMotors;
}

void Settings::serialize(QDomElement &parent) const
{
	auto result = parent.ownerDocument().createElement("settings");
	parent.appendChild(result);
	result.setAttribute("realisticPhysics", mRealisticPhysics ? "true" : "false");
	result.setAttribute("realisticSensors", mRealisticSensors ? "true" : "false");
	result.setAttribute("realisticMotors", mRealisticMotors ? "true" : "false");
	mSizeUnitSystem->serialize(result);
	const auto currentGridSize = qReal::SettingsManager::value("2dDoubleGridCellSize")
						.toReal() / mSizeUnitSystem->countFactor();
	result.setAttribute("gridCellSize", QString::number(currentGridSize));
}

void Settings::deserialize(const QDomElement &parent)
{
	mRealisticPhysics = parent.attribute("realisticPhysics") == "true";
	mRealisticSensors = parent.attribute("realisticSensors") == "true";
	mRealisticMotors = parent.attribute("realisticMotors") == "true";
	mSizeUnitSystem->deserialize(parent);
	Q_EMIT physicsChanged(mRealisticPhysics);
	Q_EMIT sizeUnitChanged(mSizeUnitSystem);
	if (parent.hasAttribute("gridCellSize")) {
		const auto gridSize = parent.attribute("gridCellSize").toDouble();
		// TODO: Synchronize with GridParamters.h
		constexpr auto minimalSize = 10;
		constexpr auto maximumSize = 150;
		if (mSizeUnitSystem->toPx(gridSize) >= minimalSize
				&& mSizeUnitSystem->toPx(gridSize) <= maximumSize) {
			Q_EMIT gridSizeChanged(gridSize);
			return;
		}
	}
	const auto gridSize = qReal::SettingsManager::value("2dDefaultGridCellSize", "50").toReal();
	Q_EMIT gridSizeChanged(gridSize);
}

void Settings::setRealisticPhysics(bool set)
{
	mRealisticPhysics = set;
	Q_EMIT physicsChanged(mRealisticPhysics);
}

void Settings::setRealisticSensors(bool set)
{
	mRealisticSensors = set;
}

void Settings::setRealisticMotors(bool set)
{
	mRealisticMotors = set;
}

QSharedPointer<SizeUnit> Settings::sizeUnit() const
{
	return mSizeUnitSystem;
}
