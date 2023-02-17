/* Copyright 2020 CyberTech Labs Ltd.
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

#include "trikPrintTextBlock.h"
#include "trikKit/robotModel/parts/trikDisplay.h"

using namespace trik;
using namespace blocks::details;

TrikPrintTextBlock::TrikPrintTextBlock(kitBase::robotModel::RobotModelInterface &robotModel)
	: kitBase::blocksBase::common::DisplayBlock(robotModel)
{
}

void TrikPrintTextBlock::doJob(kitBase::robotModel::robotParts::Display &display)
{
	auto trikDisplay = static_cast<robotModel::parts::TrikDisplay *>(&display);

	const int x = eval<int>("XCoordinateText");
	const int y = eval<int>("YCoordinateText");
	const int fontSize = eval<int>("FontSize");
	const QString result = boolProperty("Evaluate")
			? QString::number(QString::number(eval<qreal>("PrintText"), 'f', 6).toDouble())
			: stringProperty("PrintText");
	const bool redraw = boolProperty("Redraw");

	if (!errorsOccured()) {
		trikDisplay->printText(x, y, result, fontSize);
		if (redraw) {
			trikDisplay->redraw();
		}

		emit done(mNextBlockId);
	}
}

