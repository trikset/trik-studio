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
#include "qrutils/utilsDeclSpec.h"

namespace graphicsUtils {

class QRUTILS_EXPORT AbstractCoordinateSystem: public QObject
{
	Q_OBJECT

public:
	virtual qreal toPx(const qreal size) const = 0;

	virtual QPointF toPx(const QPointF &size) const = 0;

	virtual qreal toUnit(const qreal size) const = 0;

	virtual QPointF toUnit(const QPointF &size) const = 0;
};

}
