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

#pragma once

#include <trikControl/colorSensorInterface.h>
#include <trikKit/robotModel/parts/trikColorSensor.h> // replace with forward declaration

class TrikColorSensorAdapter : public trikControl::ColorSensorInterface
{
Q_OBJECT

public:
	TrikColorSensorAdapter(trik::robotModel::parts::TrikColorSensor *sensor);
	virtual Status status() const override;

public slots:
	void init(bool showOnDisplay) override;
	QVector<int> read(int m, int n) override;
	void stop() override;

private:
	trik::robotModel::parts::TrikColorSensor *mColorSensor;
};
