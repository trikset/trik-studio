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

#include "editor/private/lineHandler.h"

namespace qReal {
namespace gui {
namespace editor {

/// @brief A strategy class for handling Bezier curve link
class CurveLine : public LineHandler
{
	Q_OBJECT
public:
	CurveLine(EdgeElement *edge
			, const LogicalModelAssistInterface &logicalModel
			, const GraphicalModelAssistInterface &graphicalModel);

	/// Draws Bezier curve
	void drawLine(QPainter *painter, bool drawSavedLine) override;

	/// Draw ports and control lines for editing curve link
	void drawPorts(QPainter *painter) override;

	/// @return Link's Bezier curve
	QPainterPath shape() const override;

	/// Adjust end points and update curve configuration
	void adjust() override;

protected:
	/// Create correct curve configuration (two ports, two intermediate points)
	void setBezierPoints();

	/// Create Bezier curve based on the line
	QPainterPath bezierCurve(const QPolygonF &line) const;

	/// If user is dragging a point then move it. Otherwise, do nothing
	void handleEdgeMove(QPointF pos) override;

	/// Draw ordinary port or special curve control point
	void drawPort(QPainter *painter, int portNumber) override;

	/// Draw dash lines used for editing of Bezier curve
	void drawControlLines(QPainter *painter);
};

}
}
}
