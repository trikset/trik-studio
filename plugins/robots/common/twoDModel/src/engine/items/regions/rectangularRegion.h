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

#include "regionItem.h"

namespace twoDModel {
namespace items {

/// Rectangle-shaped zone in 2D model.
class RectangularRegion : public RegionItem
{
	Q_OBJECT
public:
	explicit RectangularRegion(QGraphicsItem *parent = nullptr);

protected:
	QString regionType() const override;
private:
	QPainterPath shape() const override;
};

}
}
