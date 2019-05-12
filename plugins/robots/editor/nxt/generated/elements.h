// ----------------------------------------------------------------------- //
// This file is auto-generated with qrxc v1.1. Do not modify its contents
// or prepare to lose your edits. If you want to change something in it
// consider editing language metamodel instead.
// ----------------------------------------------------------------------- //

#pragma once

#include <QBrush>
#include <QPainter>

#include <qrgraph/queries.h>
#include <qrutils/xmlUtils.h>
#include <metaMetaModel/nodeElementType.h>
#include <metaMetaModel/edgeElementType.h>
#include <metaMetaModel/patternType.h>
#include <metaMetaModel/labelProperties.h>

	class NxtBeep : public qReal::NodeElementType
	{
	public:
		explicit NxtBeep(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtBeep");
			setFriendlyName(QObject::tr("Beep"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Plays on the robot a sound with the fixed frequency. There are two parameters. The first one is a loudness of the sound, the second means if program should wait for sound completion or go to next block right away."));
			qReal::LabelProperties label_1(1, 1.2, -0.7, "Volume", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Volume:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.4, 1.2, "WaitForCompletion", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Wait for Completion:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtBeepClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("152, 12 : 281, 12 :  | 152, 183 : 152, 12 :  | 155, 170 : 154"
			", 176 : 153, 183 : 151, 190 : 149, 196 : 146, 202 : 143, 208 : 139, 214 : 134, 2"
			"19 : 129, 224 : 123, 228 : 117, 231 : 111, 234 : 105, 236 : 98, 238 : 91, 239 : "
			"85, 239 : 79, 239 : 72, 238 : 65, 236 : 59, 234 : 53, 231 : 47, 228 : 41, 224 : "
			"36, 219 : 31, 214 : 27, 208 : 24, 202 : 21, 196 : 19, 190 : 17, 183 : 16, 176 : "
			"16, 170 : 16, 164 : 17, 157 : 19, 150 : 21, 144 : 24, 138 : 27, 132 : 31, 126 : "
			"36, 121 : 41, 116 : 47, 112 : 53, 109 : 59, 106 : 65, 104 : 72, 102 : 79, 101 : "
			"85, 101 : 91, 101 : 98, 102 : 105, 104 : 111, 106 : 117, 109 : 123, 112 : 129, 1"
			"16 : 134, 121 : 139, 126 : 143, 132 : 146, 138 : 149, 144 : 151, 150 : 153, 157 "
			": 154, 164 : 155, 170 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Volume", "string", QObject::tr("50"), QObject::tr("Volume"), QObject::tr(""), false);
			addProperty("WaitForCompletion", "bool", QString::fromUtf8("true"), QObject::tr("Wait for Completion"), QObject::tr(""), false);
		}
	};

	class NxtClearEncoder : public qReal::NodeElementType
	{
	public:
		explicit NxtClearEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtClearEncoder");
			setFriendlyName(QObject::tr("Clear Encoder"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Nullifies tacho limit of the motors on the given ports."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Ports", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtClearEncoderClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("112, 176 : 78, 142 :  | 112, 176 : 148, 140 :  | 112, 33 : 11"
			"2, 176 :  | 12, 12 : 210, 12 : 210, 210 : 12, 210 : 12, 12 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Ports", "string", QObject::tr("A, B, C"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class NxtDrawCircle : public qReal::NodeElementType
	{
	public:
		explicit NxtDrawCircle(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtDrawCircle");
			setFriendlyName(QObject::tr("Draw Circle"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws on the robot screen a circle with the given center and radius."));
			qReal::LabelProperties label_1(1, 1, 1.2, "XCoordinateCircle", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.8, "YCoordinateCircle", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 2.4, "CircleRadius", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Radius:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtDrawCircleClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("CircleRadius", "int", QString::fromUtf8("5"), QObject::tr("Radius"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("XCoordinateCircle", "int", QString::fromUtf8("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateCircle", "int", QString::fromUtf8("0"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class NxtDrawLine : public qReal::NodeElementType
	{
	public:
		explicit NxtDrawLine(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtDrawLine");
			setFriendlyName(QObject::tr("Draw Line"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws a segment on the robot screen. The parameters specify the ends of the segment."));
			qReal::LabelProperties label_1(1, 0.72, 1.2, "X1CoordinateLine", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("X1:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.72, 1.8, "Y1CoordinateLine", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Y1:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 0.72, 2.4, "X2CoordinateLine", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("X2:"));
			addLabel(label_3);
			qReal::LabelProperties label_4(4, 0.72, 3, "Y2CoordinateLine", false, 0);
			label_4.setBackground(Qt::white);
			label_4.setScalingX(false);
			label_4.setScalingY(false);
			label_4.setHard(false);
			label_4.setPlainTextMode(false);
			label_4.setPrefix(QObject::tr("Y2:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtDrawLineClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("X1CoordinateLine", "int", QString::fromUtf8("0"), QObject::tr("X1"), QObject::tr(""), false);
			addProperty("X2CoordinateLine", "int", QString::fromUtf8("10"), QObject::tr("X2"), QObject::tr(""), false);
			addProperty("Y1CoordinateLine", "int", QString::fromUtf8("0"), QObject::tr("Y1"), QObject::tr(""), false);
			addProperty("Y2CoordinateLine", "int", QString::fromUtf8("10"), QObject::tr("Y2"), QObject::tr(""), false);
		}
	};

	class NxtDrawPixel : public qReal::NodeElementType
	{
	public:
		explicit NxtDrawPixel(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtDrawPixel");
			setFriendlyName(QObject::tr("Draw Pixel"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws one pixel in the specified coordinates on the robot screen."));
			qReal::LabelProperties label_1(1, 0.72, 1.2, "XCoordinatePix", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.72, 1.8, "YCoordinatePix", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtDrawPixelClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("XCoordinatePix", "int", QString::fromUtf8("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinatePix", "int", QString::fromUtf8("0"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class NxtDrawRect : public qReal::NodeElementType
	{
	public:
		explicit NxtDrawRect(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtDrawRect");
			setFriendlyName(QObject::tr("Draw Rectangle"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws a rectangle on the robot screen. The parameters specify the coordinates of top-left corner, the width and the height of the rectangle."));
			qReal::LabelProperties label_1(1, 1, 1.2, "XCoordinateRect", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.8, "YCoordinateRect", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 2.4, "WidthRect", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Width:"));
			addLabel(label_3);
			qReal::LabelProperties label_4(4, 1, 3, "HeightRect", false, 0);
			label_4.setBackground(Qt::white);
			label_4.setScalingX(false);
			label_4.setScalingY(false);
			label_4.setHard(false);
			label_4.setPlainTextMode(false);
			label_4.setPrefix(QObject::tr("Height:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtDrawRectClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("HeightRect", "int", QString::fromUtf8("5"), QObject::tr("Height"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("WidthRect", "int", QString::fromUtf8("5"), QObject::tr("Width"), QObject::tr(""), false);
			addProperty("XCoordinateRect", "int", QString::fromUtf8("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateRect", "int", QString::fromUtf8("0"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class NxtEngineMovementCommand : public qReal::NodeElementType
	{
	public:
		explicit NxtEngineMovementCommand(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtEngineMovementCommand");
			setFriendlyName(QObject::tr("NxtEngineMovementCommand"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			setSize(QSizeF(-1, -1));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(true);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Mode", "BreakEngineMode", QString::fromUtf8("break"), QObject::tr("Mode"), QObject::tr(""), false);
			addProperty("Ports", "string", QObject::tr("B, C"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class NxtEnginesBackward : public qReal::NodeElementType
	{
	public:
		explicit NxtEnginesBackward(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtEnginesBackward");
			setFriendlyName(QObject::tr("Motors Backward"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables motors on the given ports in reverse mode with the given power. Ports are specified with A, B or C letters divided by commas. The power is specified in percents with the number from -100 to 100, if negative number is specified then the motor is enabled in the usual mode."));
			qReal::LabelProperties label_1(1, 0.5, -0.7, "Ports", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.7, 1.2, "Power", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Power:"));
			label_2.setSuffix(QObject::tr("%"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtEnginesBackwardClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("111, 224 : 0, 113 :  | 113, 0 : 0, 113 :  | 0, 113 : 287, 113"
			" : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Mode", "BreakEngineMode", QString::fromUtf8("break"), QObject::tr("Mode"), QObject::tr(""), false);
			addProperty("Ports", "string", QObject::tr("B, C"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class NxtEnginesForward : public qReal::NodeElementType
	{
	public:
		explicit NxtEnginesForward(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtEnginesForward");
			setFriendlyName(QObject::tr("Motors Forward"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables motors on the given ports with the given power. Ports are specified with A, B or C letters divided by commas. The power is specified in percents with the number from -100 to 100, if negative number is specified then the motor is enabled in the reverse mode."));
			qReal::LabelProperties label_1(1, 0.5, -0.7, "Ports", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.7, 1.2, "Power", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Power:"));
			label_2.setSuffix(QObject::tr("%"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtEnginesForwardClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("185, 207 : 287, 105 :  | 287, 105 : 182, 0 :  | 0, 105 : 287,"
			" 105 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Mode", "BreakEngineMode", QString::fromUtf8("break"), QObject::tr("Mode"), QObject::tr(""), false);
			addProperty("Ports", "string", QObject::tr("B, C"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class NxtEnginesStop : public qReal::NodeElementType
	{
	public:
		explicit NxtEnginesStop(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtEnginesStop");
			setFriendlyName(QObject::tr("Stop Motors"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Disables motors on the given ports."));
			qReal::LabelProperties label_1(1, 0.5, -0.7, "Ports", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtEnginesStopClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("49, 117 : 185, 117 :  | 223, 118 : 222, 128 : 221, 138 : 218,"
			" 148 : 215, 158 : 211, 167 : 205, 176 : 199, 184 : 192, 192 : 184, 199 : 176, 20"
			"5 : 167, 211 : 158, 215 : 148, 218 : 138, 221 : 128, 222 : 118, 223 : 108, 222 :"
			" 98, 221 : 88, 218 : 78, 215 : 69, 211 : 60, 205 : 52, 199 : 44, 192 : 37, 184 :"
			" 31, 176 : 25, 167 : 21, 158 : 18, 148 : 15, 138 : 14, 128 : 13, 118 : 14, 108 :"
			" 15, 98 : 18, 88 : 21, 78 : 25, 69 : 31, 60 : 37, 52 : 44, 44 : 52, 37 : 60, 31 "
			": 69, 25 : 78, 21 : 88, 18 : 98, 15 : 108, 14 : 118, 13 : 128, 14 : 138, 15 : 14"
			"8, 18 : 158, 21 : 167, 25 : 176, 31 : 184, 37 : 192, 44 : 199, 52 : 205, 60 : 21"
			"1, 69 : 215, 78 : 218, 88 : 221, 98 : 222, 108 : 223, 118 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Ports", "string", QObject::tr("A, B, C"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class NxtPlayTone : public qReal::NodeElementType
	{
	public:
		explicit NxtPlayTone(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtPlayTone");
			setFriendlyName(QObject::tr("Play Tone"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Plays on the robot a sound with the given frequency and duration. This block is similar to the 'Beep' block wuth the only difference that here you can specify sound parameters."));
			qReal::LabelProperties label_1(1, 1, -0.7, "Frequency", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Frequency:"));
			label_1.setSuffix(QObject::tr("Hz"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.2, 1.2, "Volume", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Volume:"));
			label_2.setSuffix(QObject::tr("%"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1.2, 1.8, "Duration", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Duration"));
			label_3.setSuffix(QObject::tr("ms"));
			addLabel(label_3);
			qReal::LabelProperties label_4(4, 1.2, 2.4, "WaitForCompletion", false, 0);
			label_4.setBackground(Qt::white);
			label_4.setScalingX(false);
			label_4.setScalingY(false);
			label_4.setHard(false);
			label_4.setPlainTextMode(false);
			label_4.setPrefix(QObject::tr("Wait for Completion:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtPlayToneClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("130, 62 : 130, 146 :  | 106, 0 : 106, 212 :  | 0, 106 : 106, "
			"212 :  | 0, 106 : 106, 0 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Duration", "string", QObject::tr("1000"), QObject::tr("Duration"), QObject::tr(""), false);
			addProperty("Frequency", "string", QObject::tr("1000"), QObject::tr("Frequency"), QObject::tr(""), false);
			addProperty("Volume", "string", QObject::tr("50"), QObject::tr("Volume"), QObject::tr(""), false);
			addProperty("WaitForCompletion", "bool", QString::fromUtf8("true"), QObject::tr("Wait for Completion"), QObject::tr(""), false);
		}
	};

	class NxtSensorBlock : public qReal::NodeElementType
	{
	public:
		explicit NxtSensorBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtSensorBlock");
			setFriendlyName(QObject::tr("NxtSensorBlock"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			setSize(QSizeF(-1, -1));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(true);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class NxtWaitForButton : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForButton(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForButton");
			setFriendlyName(QObject::tr("Wait for Button"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits for press of a button on a brick."));
			qReal::LabelProperties label_1(1, 0.8, 1.2, "Button", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Button:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForButtonClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Button", "NxtButtons", QString::fromUtf8("Enter"), QObject::tr("Button"), QObject::tr(""), false);
		}
	};

	class NxtWaitForColor : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForColor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForColor");
			setFriendlyName(QObject::tr("Wait for Color"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the color sensor on the given port will recognize the given color."));
			qReal::LabelProperties label_1(1, 0.74, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.74, 1.2, "Color", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Color:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForColorClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("196, 12 : 196, 154 :  | 12, 12 : 380, 12 : 380, 154 : 12, 154"
			" : 12, 12 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Color", "Color", QString::fromUtf8("red"), QObject::tr("Color"), QObject::tr(""), false);
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class NxtWaitForColorIntensity : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForColorIntensity(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForColorIntensity");
			setFriendlyName(QObject::tr("Wait for Color Intensity"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the color sensor on the given port will be greater or less than the given in the 'Intensity' parameter value (the intensity is specified in percents, 0 to 100)."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.1, 1.2, "Intensity", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Intensity:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1.1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForColorIntensityClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("201, 137 : 200, 143 : 199, 149 : 198, 154 : 196, 160 : 193, 1"
			"66 : 190, 171 : 186, 176 : 182, 180 : 178, 184 : 173, 188 : 168, 191 : 162, 194 "
			": 156, 196 : 151, 197 : 145, 198 : 139, 198 : 133, 198 : 127, 197 : 122, 196 : 1"
			"16, 194 : 110, 191 : 105, 188 : 100, 184 : 96, 180 : 92, 176 : 88, 171 : 85, 166"
			" : 82, 160 : 80, 154 : 79, 149 : 78, 143 : 78, 137 : 78, 131 : 79, 125 : 80, 120"
			" : 82, 114 : 85, 108 : 88, 103 : 92, 98 : 96, 94 : 100, 90 : 105, 86 : 110, 83 :"
			" 116, 80 : 122, 78 : 127, 77 : 133, 76 : 139, 76 : 145, 76 : 151, 77 : 156, 78 :"
			" 162, 80 : 168, 83 : 173, 86 : 178, 90 : 182, 94 : 186, 98 : 190, 103 : 193, 108"
			" : 196, 114 : 198, 120 : 199, 125 : 200, 131 : 201, 137 :  | 260, 136 : 259, 148"
			" : 257, 160 : 254, 171 : 250, 183 : 245, 194 : 239, 204 : 231, 214 : 223, 223 : "
			"214, 231 : 204, 239 : 194, 245 : 183, 250 : 171, 254 : 160, 257 : 148, 259 : 136"
			", 259 : 124, 259 : 112, 257 : 101, 254 : 89, 250 : 78, 245 : 68, 239 : 58, 231 :"
			" 49, 223 : 41, 214 : 33, 204 : 27, 194 : 22, 183 : 18, 171 : 15, 160 : 13, 148 :"
			" 13, 136 : 13, 124 : 15, 112 : 18, 101 : 22, 89 : 27, 78 : 33, 68 : 41, 58 : 49,"
			" 49 : 58, 41 : 68, 33 : 78, 27 : 89, 22 : 101, 18 : 112, 15 : 124, 13 : 136, 13 "
			": 148, 13 : 160, 15 : 171, 18 : 183, 22 : 194, 27 : 204, 33 : 214, 41 : 223, 49 "
			": 231, 58 : 239, 68 : 245, 78 : 250, 89 : 254, 101 : 257, 112 : 259, 124 : 260, "
			"136 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Intensity", "string", QObject::tr("0"), QObject::tr("Intensity"), QObject::tr(""), false);
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class NxtWaitForEncoder : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForEncoder");
			setFriendlyName(QObject::tr("Wait for Encoder"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the tacho limit of the motor on the given port will reach the value of the 'Tacho Limit' parameter."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.8, 1.2, "TachoLimit", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Tacho Limit:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 0.8, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForEncoderClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("203, 211 : 168, 176 :  | 203, 211 : 240, 174 :  | 12, 48 : 50"
			", 86 :  | 12, 48 : 48, 12 :  | 203, 48 : 203, 211 :  | 12, 48 : 203, 48 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Port", "string", QObject::tr("B"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
			addProperty("TachoLimit", "string", QObject::tr(""), QObject::tr("Tacho Limit"), QObject::tr(""), false);
		}
	};

	class NxtWaitForLight : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForLight(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForLight");
			setFriendlyName(QObject::tr("Wait for Light"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the light sensor on the given port will be greater or less than the given in the 'Percents' parameter value (0 to 100)."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.9, 1.2, "Percents", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Percents:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForLightClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("249, 220 : 349, 220 :  | 130, 12 : 130, 102 :  | 249, 221 : 2"
			"48, 232 : 247, 244 : 244, 255 : 240, 266 : 235, 276 : 229, 286 : 222, 296 : 214,"
			" 304 : 206, 312 : 196, 319 : 186, 325 : 176, 330 : 165, 334 : 154, 337 : 142, 33"
			"8 : 131, 339 : 120, 338 : 108, 337 : 97, 334 : 86, 330 : 76, 325 : 66, 319 : 56,"
			" 312 : 48, 304 : 40, 296 : 33, 286 : 27, 276 : 22, 266 : 18, 255 : 15, 244 : 14,"
			" 232 : 13, 221 : 14, 210 : 15, 198 : 18, 187 : 22, 176 : 27, 166 : 33, 156 : 40,"
			" 146 : 48, 138 : 56, 130 : 66, 123 : 76, 117 : 86, 112 : 97, 108 : 108, 105 : 12"
			"0, 104 : 131, 103 : 142, 104 : 154, 105 : 165, 108 : 176, 112 : 186, 117 : 196, "
			"123 : 206, 130 : 214, 138 : 222, 146 : 229, 156 : 235, 166 : 240, 176 : 244, 187"
			" : 247, 198 : 248, 210 : 249, 221 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Percents", "string", QObject::tr("0"), QObject::tr("Percents"), QObject::tr(""), false);
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class NxtWaitForSonarDistance : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForSonarDistance(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForSonarDistance");
			setFriendlyName(QObject::tr("Wait for Sonar Distance"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the ultrasonic sensor on the given port will be greater or less than the given in the 'Distance' parameter value (the distance is specified in centimeters, 0 to 255)."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.2, "Distance", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Distance:"));
			label_2.setSuffix(QObject::tr("cm"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForSonarDistanceClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("190, 162 : 219, 122 :  | 219, 122 : 190, 86 :  | 120, 122 : 2"
			"19, 122 :  | 12, 118 : 118, 12 :  | 12, 118 : 118, 224 :  | 118, 12 : 118, 224 :"
			" ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Distance", "string", QObject::tr("0"), QObject::tr("Distance"), QObject::tr(""), false);
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class NxtWaitForSound : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForSound(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForSound");
			setFriendlyName(QObject::tr("Wait for Sound Sensor"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the loudness obtained by the sound sensor on the given port will be greater or less than the given value."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.2, "Volume", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Volume:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForSoundClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("12, 178 : 117, 178 :  | 117, 96 : 117, 178 :  | 13, 96 : 117,"
			" 96 :  | 13, 12 : 13, 96 :  | 13, 12 : 118, 12 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
			addProperty("Volume", "string", QObject::tr("0"), QObject::tr("Volume"), QObject::tr(""), false);
		}
	};

	class NxtWaitForTouchSensor : public qReal::NodeElementType
	{
	public:
		explicit NxtWaitForTouchSensor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("NxtWaitForTouchSensor");
			setFriendlyName(QObject::tr("Wait for Touch Sensor"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the touch sensor is pressed. The only parameter is a sensor`s port number (1, 2, 3 or 4)."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/NxtWaitForTouchSensorClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("12, 123 : 174, 123 :  | 174, 12 : 358, 12 : 358, 234 : 174, 2"
			"34 : 174, 12 : ");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.1, 0, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 0, 0.9, 0), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.1, 1, 0.9), false, false, false, false, 50, 50, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.1, 1, 0.9, 1), false, false, false, false, 50, 50, "NonTyped"));
			setResizable(false);
			setContainer(false);
			setSortingContainer(false);
			setSizeOfForestalling({0, 0, 0, 0});
			setSizeOfChildrenForestalling(0);
			setChildrenMovable(true);
			setMinimizesToChildren(false);
			setMaximizesChildren(false);
			setCreateChildrenFromMenu(false);
			setBorder({});
		}

		void initProperties()
		{
			addProperty("Port", "NxtSensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

