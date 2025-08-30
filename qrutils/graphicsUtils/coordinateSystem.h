/* Copyright 2025 CyberTech Labs Ltd.
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
#include <QObject>
#include "abstractCoordinateSystem.h"
#include "qrutils/utilsDeclSpec.h"

namespace graphicsUtils {

class QRUTILS_EXPORT CoordinateSystem : public AbstractCoordinateSystem
{
	Q_OBJECT

public:
	CoordinateSystem() = default;
	qreal toPx(const qreal size) const override;
	QPointF toPx(const QPointF &size) const override;
	qreal toUnit(const qreal size) const override;
	QPointF toUnit(const QPointF &size) const override;
};
}
