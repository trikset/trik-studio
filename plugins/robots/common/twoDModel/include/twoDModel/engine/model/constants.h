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

#pragma once

#include <QtCore/QPointF>
#include <QtCore/QSizeF>

namespace twoDModel {

const qreal lowPrecision = 0.00001;

const QSize displaySize(200, 300);
const qreal beepWavesSize = 120;

const qreal robotWheelDiameterInPx = 16;
const qreal robotWheelDiameterInCm = 5.6;
const qreal pixelsInCm = robotWheelDiameterInPx / robotWheelDiameterInCm;

const uint black   = 0xFF000000;
const uint white   = 0xFFFFFFFF;
const uint red     = 0xFFFF0000;
const uint green   = 0xFF008000;
const uint blue    = 0xFF0000FF;
const uint yellow  = 0xFFFFFF00;
const uint cyan    = 0xFF00FFFF;
const uint magenta = 0xFFFF00FF;

const qreal spoilColorDispersion = 2.0;
const qreal spoilLightDispersion = 1.0;
const qreal spoilSonarDispersion = 1.5;
const qreal varySpeedDispersion = 0.0125;
const qreal percentSaltPepperNoise = 20.0;

const qreal robotInertialMoment = 20;
const qreal reactionForceStabilizationCoefficient = 20;
const qreal floorFrictionCoefficient = 0.2;
const qreal wallFrictionCoefficient = 0.2;
const qreal rotationalFrictionFactor = 1500;
const qreal angularVelocityFrictionFactor = 200;

//const qreal onePercentAngularVelocity = 0.0055;
const int maxLightSensorValur = 1023;
const int touchSensorPressedSignal = 1;
const int touchSensorNotPressedSignal = 0;

}
