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

	class TrikAnalogSensorBlock : public qReal::NodeElementType
	{
	public:
		explicit TrikAnalogSensorBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikAnalogSensorBlock");
			setFriendlyName(QObject::tr("TrikAnalogSensorBlock"));
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
			addProperty("Port", "TrikV6AnalogSensorPort", QString::fromUtf8("A1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class TrikAngularServo : public qReal::NodeElementType
	{
	public:
		explicit TrikAngularServo(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikAngularServo");
			setFriendlyName(QObject::tr("Angular Servo"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Manages angular servomotor. Sets up rotation angle on the given port in degrees. Values from 0 to 90 are correspond to a clockwise rotation and values from -90 to 0 correspond to counterclockwise rotation."));
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
			label_2.setPrefix(QObject::tr("Angle:"));
			label_2.setSuffix(QObject::tr("°"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikAngularServoClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("E1"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("0"), QObject::tr("Angle (degrees)"), QObject::tr(""), false);
		}
	};

	class TrikBackwardOneCell : public qReal::NodeElementType
	{
	public:
		explicit TrikBackwardOneCell(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikBackwardOneCell");
			setFriendlyName(QObject::tr("Backward one cell"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("IKHONAKHBEEVA"));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikBackwardOneCellClass.sdf").documentElement());
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
		}
	};

	class TrikCalibrateGyroscope : public qReal::NodeElementType
	{
	public:
		explicit TrikCalibrateGyroscope(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikCalibrateGyroscope");
			setFriendlyName(QObject::tr("Calibrate gyroscope"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets gyroscope's angle to zero in current position."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikCalibrateGyroscopeClass.sdf").documentElement());
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
		}
	};

	class TrikDetect : public qReal::NodeElementType
	{
	public:
		explicit TrikDetect(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDetect");
			setFriendlyName(QObject::tr("Detect by Videocamera"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Initializes videocamera line or object detector with the color of the object in the middle of the camera`s sight."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Mode", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Mode:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, -0.5, 1.2, QObject::tr("Detect by Videocamera"), 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDetectClass.sdf").documentElement());
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
			addProperty("Mode", "DetectableVideoSensor", QString::fromUtf8("line"), QObject::tr("Mode"), QObject::tr(""), false);
		}
	};

	class TrikDetectorToVariable : public qReal::NodeElementType
	{
	public:
		explicit TrikDetectorToVariable(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDetectorToVariable");
			setFriendlyName(QObject::tr("Line Detector into Variable"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Stores videocamera line detector`s value into a given variable."));
			qReal::LabelProperties label_1(1, -0.3, 1.2, QObject::tr("Line Detector into Variable"), 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.8, 1.8, "Variable", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Variable:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDetectorToVariableClass.sdf").documentElement());
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
			addProperty("Variable", "string", QObject::tr("err"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class TrikDigitalSensorBlock : public qReal::NodeElementType
	{
	public:
		explicit TrikDigitalSensorBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDigitalSensorBlock");
			setFriendlyName(QObject::tr("TrikDigitalSensorBlock"));
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
			addProperty("Port", "TrikV6DigitalSensorPort", QString::fromUtf8("D1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class TrikDrawArc : public qReal::NodeElementType
	{
	public:
		explicit TrikDrawArc(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDrawArc");
			setFriendlyName(QObject::tr("Draw Arc"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws the arc defined by the rectangle beginning at (x, y) with the specified width and height, and the given startAngle and spanAngle."));
			qReal::LabelProperties label_1(1, 1, 1.2, "XCoordinateArc", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.8, "YCoordinateArc", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 2.4, "WidthArc", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Width:"));
			addLabel(label_3);
			qReal::LabelProperties label_4(4, 1, 3, "HeightArc", false, 0);
			label_4.setBackground(Qt::white);
			label_4.setScalingX(false);
			label_4.setScalingY(false);
			label_4.setHard(false);
			label_4.setPlainTextMode(false);
			label_4.setPrefix(QObject::tr("Height:"));
			addLabel(label_4);
			qReal::LabelProperties label_5(5, 1, 3.6, "StartAngle", false, 0);
			label_5.setBackground(Qt::white);
			label_5.setScalingX(false);
			label_5.setScalingY(false);
			label_5.setHard(false);
			label_5.setPlainTextMode(false);
			label_5.setPrefix(QObject::tr("Start Angle:"));
			addLabel(label_5);
			qReal::LabelProperties label_6(6, 1, 4.2, "SpanAngle", false, 0);
			label_6.setBackground(Qt::white);
			label_6.setScalingX(false);
			label_6.setScalingY(false);
			label_6.setHard(false);
			label_6.setPlainTextMode(false);
			label_6.setPrefix(QObject::tr("Span Angle:"));
			addLabel(label_6);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDrawArcClass.sdf").documentElement());
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
			addProperty("HeightArc", "string", QObject::tr("5"), QObject::tr("Height"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("SpanAngle", "int", QString::fromUtf8("20"), QObject::tr("SpanAngle"), QObject::tr(""), false);
			addProperty("StartAngle", "int", QString::fromUtf8("20"), QObject::tr("StartAngle"), QObject::tr(""), false);
			addProperty("WidthArc", "string", QObject::tr("5"), QObject::tr("Width"), QObject::tr(""), false);
			addProperty("XCoordinateArc", "string", QObject::tr("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateArc", "string", QObject::tr("0"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class TrikDrawEllipse : public qReal::NodeElementType
	{
	public:
		explicit TrikDrawEllipse(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDrawEllipse");
			setFriendlyName(QObject::tr("Draw Ellipse"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws the ellipse defined by the rectangle beginning at (x, y) with the given width and height."));
			qReal::LabelProperties label_1(1, 1, 1.2, "XCoordinateEllipse", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.8, "YCoordinateEllipse", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 2.4, "WidthEllipse", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Width:"));
			addLabel(label_3);
			qReal::LabelProperties label_4(4, 1, 3, "HeightEllipse", false, 0);
			label_4.setBackground(Qt::white);
			label_4.setScalingX(false);
			label_4.setScalingY(false);
			label_4.setHard(false);
			label_4.setPlainTextMode(false);
			label_4.setPrefix(QObject::tr("Height:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDrawEllipseClass.sdf").documentElement());
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
			addProperty("Filled", "bool", QString::fromUtf8("false"), QObject::tr("Filled"), QObject::tr(""), false);
			addProperty("HeightEllipse", "string", QObject::tr("5"), QObject::tr("Height"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("WidthEllipse", "string", QObject::tr("5"), QObject::tr("Width"), QObject::tr(""), false);
			addProperty("XCoordinateEllipse", "string", QObject::tr("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateEllipse", "string", QObject::tr("0"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class TrikDrawLine : public qReal::NodeElementType
	{
	public:
		explicit TrikDrawLine(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDrawLine");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDrawLineClass.sdf").documentElement());
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
			addProperty("X1CoordinateLine", "string", QObject::tr("0"), QObject::tr("X1"), QObject::tr(""), false);
			addProperty("X2CoordinateLine", "string", QObject::tr("10"), QObject::tr("X2"), QObject::tr(""), false);
			addProperty("Y1CoordinateLine", "string", QObject::tr("0"), QObject::tr("Y1"), QObject::tr(""), false);
			addProperty("Y2CoordinateLine", "string", QObject::tr("10"), QObject::tr("Y2"), QObject::tr(""), false);
		}
	};

	class TrikDrawPixel : public qReal::NodeElementType
	{
	public:
		explicit TrikDrawPixel(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDrawPixel");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDrawPixelClass.sdf").documentElement());
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
			addProperty("XCoordinatePix", "string", QObject::tr("5"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinatePix", "string", QObject::tr("5"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class TrikDrawRect : public qReal::NodeElementType
	{
	public:
		explicit TrikDrawRect(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikDrawRect");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikDrawRectClass.sdf").documentElement());
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
			addProperty("Filled", "bool", QString::fromUtf8("false"), QObject::tr("Filled"), QObject::tr(""), false);
			addProperty("HeightRect", "string", QObject::tr("5"), QObject::tr("Height"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("WidthRect", "string", QObject::tr("5"), QObject::tr("Width"), QObject::tr(""), false);
			addProperty("XCoordinateRect", "string", QObject::tr("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateRect", "string", QObject::tr("0"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class TrikForwardOneCell : public qReal::NodeElementType
	{
	public:
		explicit TrikForwardOneCell(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikForwardOneCell");
			setFriendlyName(QObject::tr("Forward one cell"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("IKHONAKHBEEVA"));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikForwardOneCellClass.sdf").documentElement());
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
		}
	};

	class TrikInitCamera : public qReal::NodeElementType
	{
	public:
		explicit TrikInitCamera(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikInitCamera");
			setFriendlyName(QObject::tr("Initialize Videocamera"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables line or object or color detector by videocamera and draws videostream on the robot`s screen."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Mode", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Mode:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, -0.5, 1.2, QObject::tr("Initialize Videocamera"), 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikInitCameraClass.sdf").documentElement());
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
			addProperty("DrawStream", "Bool", QString::fromUtf8("true"), QObject::tr("Draw stream"), QObject::tr(""), false);
			addProperty("Mode", "VideoSensor", QString::fromUtf8("line"), QObject::tr("Mode"), QObject::tr(""), false);
		}
	};

	class TrikInitVideoStreaming : public qReal::NodeElementType
	{
	public:
		explicit TrikInitVideoStreaming(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikInitVideoStreaming");
			setFriendlyName(QObject::tr("Enable Video Streaming"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables video stream on robot. Video then can be watched on TRIK gamepad or in browser using URL http://ROBOT.IP.ADDRESS:8080/?action=stream"));
			qReal::LabelProperties label_1(1, -0.5, 1.2, QObject::tr("Enable Video Streaming"), 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikInitVideoStreamingClass.sdf").documentElement());
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
			addProperty("Grayscaled", "bool", QString::fromUtf8("false"), QObject::tr("Grayscaled"), QObject::tr(""), false);
			addProperty("Quality", "JpgEncoderQuality", QString::fromUtf8("30"), QObject::tr("Quality"), QObject::tr(""), false);
		}
	};

	class TrikLed : public qReal::NodeElementType
	{
	public:
		explicit TrikLed(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikLed");
			setFriendlyName(QObject::tr("Led"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets the color of the LED on the robot`s front panel."));
			qReal::LabelProperties label_1(1, 0.7, -0.7, "Color", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Color:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikLedClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("70, 79 : 70, 121 :  | 25, 78 : 25, 122 :  | 12, 12 : 86, 12 :"
			" 86, 78 : 12, 78 : 12, 12 : ");
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
			addProperty("Color", "TrikLedColor", QString::fromUtf8("red"), QObject::tr("Color"), QObject::tr(""), false);
		}
	};

	class TrikPlayTone : public qReal::NodeElementType
	{
	public:
		explicit TrikPlayTone(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikPlayTone");
			setFriendlyName(QObject::tr("Play Sound"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Plays on the robot a sound file (.wav or .mp3) previously uploaded to it."));
			qReal::LabelProperties label_1(1, 1, -0.7, "FileName", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("File name:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikPlayToneClass.sdf").documentElement());
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
			addProperty("FileName", "string", QObject::tr("media/beep.wav"), QObject::tr("File Name"), QObject::tr(""), false);
		}
	};

	class TrikPlayToneHz : public qReal::NodeElementType
	{
	public:
		explicit TrikPlayToneHz(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikPlayToneHz");
			setFriendlyName(QObject::tr("Play Tone"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Plays on the robot a sound with the given frequency and duration."));
			qReal::LabelProperties label_1(1, 1, -0.7, "Frequency", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Frequency:"));
			label_1.setSuffix(QObject::tr("Hz"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.2, "Duration", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Duration:"));
			label_2.setSuffix(QObject::tr("ms"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikPlayToneHzClass.sdf").documentElement());
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
			addProperty("Duration", "string", QObject::tr("1000"), QObject::tr("Duration"), QObject::tr(""), false);
			addProperty("Frequency", "string", QObject::tr("1000"), QObject::tr("Frequency"), QObject::tr(""), false);
		}
	};

	class TrikRemoveFile : public qReal::NodeElementType
	{
	public:
		explicit TrikRemoveFile(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikRemoveFile");
			setFriendlyName(QObject::tr("Remove File"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Removes a file. File path may be absolute or relative to a directory containing TRIK Studio executable."));
			qReal::LabelProperties label_1(1, 0.66, 1.2, "File", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("File:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikRemoveFileClass.sdf").documentElement());
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
			addProperty("File", "string", QObject::tr("output.txt"), QObject::tr("File"), QObject::tr(""), false);
		}
	};

	class TrikSadSmile : public qReal::NodeElementType
	{
	public:
		explicit TrikSadSmile(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSadSmile");
			setFriendlyName(QObject::tr("Sad Smile"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws a sad smile on the robot`s screen :("));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSadSmileClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("156, 91 : 173, 110 :  | 115, 73 : 156, 91 :  | 78, 73 : 114, "
			"73 :  | 33, 85 : 78, 73 :  | 12, 106 : 33, 85 :  | 126, 12 : 126, 48 :  | 63, 12"
			" : 63, 49 : ");
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
		}
	};

	class TrikSay : public qReal::NodeElementType
	{
	public:
		explicit TrikSay(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSay");
			setFriendlyName(QObject::tr("Say"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Synthesizes the given phrase and plays it on the robot. If 'Evaluate' property is set to true then the value of 'Text' property is interpreted as a formula, otherwise it is interpreted as plain string."));
			qReal::LabelProperties label_1(1, 0.7, -0.7, "Text", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Text:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSayClass.sdf").documentElement());
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
			addProperty("Evaluate", "bool", QString::fromUtf8("false"), QObject::tr("Evaluate"), QObject::tr(""), false);
			addProperty("Text", "string", QObject::tr("Hi!"), QObject::tr("Text"), QObject::tr(""), false);
		}
	};

	class TrikSendMessage : public qReal::NodeElementType
	{
	public:
		explicit TrikSendMessage(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSendMessage");
			setFriendlyName(QObject::tr("Send message"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sends message to another robot."));
			qReal::LabelProperties label_1(1, 0.9, 1.2, "Message", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Message:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.9, 1.8, "HullNumber", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Hull number:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSendMessageClass.sdf").documentElement());
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
			addProperty("HullNumber", "string", QObject::tr(""), QObject::tr("Hull Number"), QObject::tr(""), false);
			addProperty("Message", "string", QObject::tr(""), QObject::tr("Message"), QObject::tr(""), false);
		}
	};

	class TrikSensorBlock : public qReal::NodeElementType
	{
	public:
		explicit TrikSensorBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSensorBlock");
			setFriendlyName(QObject::tr("TrikSensorBlock"));
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
		}
	};

	class TrikSetBackground : public qReal::NodeElementType
	{
	public:
		explicit TrikSetBackground(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSetBackground");
			setFriendlyName(QObject::tr("Background Color"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets the background color of the current picture on the robot`s screen."));
			qReal::LabelProperties label_1(1, 0.7, -0.7, "Color", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Color:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSetBackgroundClass.sdf").documentElement());
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
			addProperty("Color", "BackgroundColor", QString::fromUtf8("white"), QObject::tr("Color"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
		}
	};

	class TrikSetPainterColor : public qReal::NodeElementType
	{
	public:
		explicit TrikSetPainterColor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSetPainterColor");
			setFriendlyName(QObject::tr("Painter Color"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets the painter color."));
			qReal::LabelProperties label_1(1, 0.5, -0.7, "Color", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Color:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSetPainterColorClass.sdf").documentElement());
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
			addProperty("Color", "BackgroundColor", QString::fromUtf8("black"), QObject::tr("Color"), QObject::tr(""), false);
		}
	};

	class TrikSetPainterWidth : public qReal::NodeElementType
	{
	public:
		explicit TrikSetPainterWidth(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSetPainterWidth");
			setFriendlyName(QObject::tr("Painter Width"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets the painter width."));
			qReal::LabelProperties label_1(1, 1, -0.7, "Width", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Width:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSetPainterWidthClass.sdf").documentElement());
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
			addProperty("Width", "string", QObject::tr("1"), QObject::tr("Width"), QObject::tr(""), false);
		}
	};

	class TrikSmile : public qReal::NodeElementType
	{
	public:
		explicit TrikSmile(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSmile");
			setFriendlyName(QObject::tr("Smile"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws a smile on the robot`s screen :)"));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSmileClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("161, 71 : 166, 57 :  | 149, 82 : 161, 70 :  | 113, 91 : 149, "
			"83 :  | 67, 91 : 113, 91 :  | 29, 84 : 65, 91 :  | 17, 74 : 28, 83 :  | 12, 59 :"
			" 17, 73 :  | 130, 13 : 130, 51 :  | 62, 12 : 62, 51 : ");
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
		}
	};

	class TrikStopCamera : public qReal::NodeElementType
	{
	public:
		explicit TrikStopCamera(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikStopCamera");
			setFriendlyName(QObject::tr("Stop Videocamera"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Stops line or object or color detector by videocamera."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Mode", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Mode:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, -0.5, 1.2, QObject::tr("Stop Videocamera"), 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikStopCameraClass.sdf").documentElement());
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
			addProperty("Mode", "VideoSensor", QString::fromUtf8("line"), QObject::tr("Mode"), QObject::tr(""), false);
		}
	};

	class TrikStopVideoStreaming : public qReal::NodeElementType
	{
	public:
		explicit TrikStopVideoStreaming(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikStopVideoStreaming");
			setFriendlyName(QObject::tr("Disable Video Streaming"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Disables video stream on robot."));
			qReal::LabelProperties label_1(1, -0.5, 1.2, QObject::tr("Disable Video Streaming"), 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikStopVideoStreamingClass.sdf").documentElement());
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
		}
	};

	class TrikSystem : public qReal::NodeElementType
	{
	public:
		explicit TrikSystem(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikSystem");
			setFriendlyName(QObject::tr("System Call"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Invokes bash script-style command on the robot. If 'Evaluate' property is set to true then the value of 'Command' property is interpreted as a formula, otherwise it is interpreted as plain string."));
			qReal::LabelProperties label_1(1, 0.8, 1.2, "Command", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Command:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikSystemClass.sdf").documentElement());
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
			addProperty("Code", "bool", QString::fromUtf8("false"), QObject::tr("Code"), QObject::tr(""), false);
			addProperty("Command", "string", QObject::tr("echo 123"), QObject::tr("Command"), QObject::tr(""), false);
			addProperty("Evaluate", "bool", QString::fromUtf8("false"), QObject::tr("Evaluate"), QObject::tr(""), false);
		}
	};

	class TrikTurnLeft : public qReal::NodeElementType
	{
	public:
		explicit TrikTurnLeft(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikTurnLeft");
			setFriendlyName(QObject::tr("Turn left"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("IKHONAKHBEEVA"));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikTurnLeftClass.sdf").documentElement());
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
		}
	};

	class TrikTurnRight : public qReal::NodeElementType
	{
	public:
		explicit TrikTurnRight(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikTurnRight");
			setFriendlyName(QObject::tr("Turn right"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("IKHONAKHBEEVA"));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikTurnRightClass.sdf").documentElement());
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
		}
	};

	class TrikV62AngularServo : public qReal::NodeElementType
	{
	public:
		explicit TrikV62AngularServo(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV62AngularServo");
			setFriendlyName(QObject::tr("Angular Servo"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Manages angular servomotor. Sets up rotation angle on the given port in degrees. Values from 0 to 90 are correspond to a clockwise rotation and values from -90 to 0 correspond to counterclockwise rotation."));
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
			label_2.setPrefix(QObject::tr("Angle:"));
			label_2.setSuffix(QObject::tr("°"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV62AngularServoClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("S1"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("0"), QObject::tr("Angle (degrees)"), QObject::tr(""), false);
		}
	};

	class TrikV62ClearEncoder : public qReal::NodeElementType
	{
	public:
		explicit TrikV62ClearEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV62ClearEncoder");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV62ClearEncoderClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("E1, E2, E3, E4"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class TrikV62WaitForEncoder : public qReal::NodeElementType
	{
	public:
		explicit TrikV62WaitForEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV62WaitForEncoder");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV62WaitForEncoderClass.sdf").documentElement());
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
			addProperty("Port", "TrikV62EncoderPort", QString::fromUtf8("E3"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
			addProperty("TachoLimit", "string", QObject::tr(""), QObject::tr("Tacho Limit"), QObject::tr(""), false);
		}
	};

	class TrikV6ClearEncoder : public qReal::NodeElementType
	{
	public:
		explicit TrikV6ClearEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV6ClearEncoder");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV6ClearEncoderClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("B1, B2, B3, B4"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class TrikV6EngineMovementCommand : public qReal::NodeElementType
	{
	public:
		explicit TrikV6EngineMovementCommand(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV6EngineMovementCommand");
			setFriendlyName(QObject::tr("TrikV6EngineMovementCommand"));
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
			addProperty("Ports", "string", QObject::tr("M3, M4"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class TrikV6EnginesBackward : public qReal::NodeElementType
	{
	public:
		explicit TrikV6EnginesBackward(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV6EnginesBackward");
			setFriendlyName(QObject::tr("Motors Backward"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables motors on the given ports in reverse mode with the given power. Ports are specified in accordance with TRIK controller notations (for example M1, E2) and divided by commas. The power is specified in percents with the number from -100 to 100, if negative number is specified then the motor is enabled in the usual mode."));
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV6EnginesBackwardClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("M3, M4"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class TrikV6EnginesForward : public qReal::NodeElementType
	{
	public:
		explicit TrikV6EnginesForward(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV6EnginesForward");
			setFriendlyName(QObject::tr("Motors Forward"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables motors on the given ports with the given power. Ports are specified in accordance with TRIK controller notations (for example M1, E2) and divided by commas. The power is specified in percents with the number from -100 to 100, if negative number is specified then the motor is enabled in the reverse mode."));
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV6EnginesForwardClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("M3, M4"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class TrikV6EnginesStop : public qReal::NodeElementType
	{
	public:
		explicit TrikV6EnginesStop(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikV6EnginesStop");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikV6EnginesStopClass.sdf").documentElement());
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
			addProperty("Mode", "BrakeEngineMode", QString::fromUtf8("float"), QObject::tr("Mode"), QObject::tr(""), false);
			addProperty("Ports", "string", QObject::tr("M1, M2, M3, M4"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class TrikWaitForAccelerometer : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForAccelerometer(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForAccelerometer");
			setFriendlyName(QObject::tr("Wait for Accelerometer"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			qReal::LabelProperties label_1(1, 1, 1.2, "Acceleration", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Acceleration:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.8, "Sign", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Sign:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1, 2.4, "AccelerationAxis", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Axis:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForAccelerometerClass.sdf").documentElement());
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
			addProperty("Acceleration", "string", QObject::tr("0"), QObject::tr("Acceleration"), QObject::tr(""), false);
			addProperty("AccelerationAxis", "Accelerations", QString::fromUtf8("xAxis"), QObject::tr("Acceleration Axis"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class TrikWaitForButton : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForButton(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForButton");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForButtonClass.sdf").documentElement());
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
			addProperty("Button", "TrikButtons", QString::fromUtf8("Up"), QObject::tr("Button"), QObject::tr(""), false);
		}
	};

	class TrikWaitForEncoder : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForEncoder");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForEncoderClass.sdf").documentElement());
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
			addProperty("Port", "TrikV6EncoderPort", QString::fromUtf8("B3"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
			addProperty("TachoLimit", "string", QObject::tr(""), QObject::tr("Tacho Limit"), QObject::tr(""), false);
		}
	};

	class TrikWaitForGyroscope : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForGyroscope(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForGyroscope");
			setFriendlyName(QObject::tr("Wait for Gyroscope"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the gyroscope on the given port will be greater or less than the given in the 'Degrees' parameter value."));
			qReal::LabelProperties label_1(1, 1.1, 1.2, "Degrees", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Degrees:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.1, 1.8, "Sign", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Sign:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForGyroscopeClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("101, 106 : 212, 106 :  | 156, 183 : 156, 107 :  | 12, 183 : 1"
			"56, 183 :  | 12, 12 : 12, 183 :  | 12, 12 : 164, 12 : ");
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
			addProperty("Degrees", "string", QObject::tr("0"), QObject::tr("Degrees"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class TrikWaitForIRDistance : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForIRDistance(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForIRDistance");
			setFriendlyName(QObject::tr("Wait for Infrared Distance"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the infrared sensor on the given port will be greater or less than the given in the 'Distance' parameter value. By default on ports A1 and A2 the distance is specified in centimeters (from 0 to 100). It is not recommended to plug IR sensor into other ports because its raw value will be processed by software on robot with expectation of another sensor type."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.1, 1.2, "Distance", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Distance:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1.1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForIRDistanceClass.sdf").documentElement());
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
			addProperty("Port", "TrikV6AnalogSensorPort", QString::fromUtf8("A1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class TrikWaitForLight : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForLight(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForLight");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForLightClass.sdf").documentElement());
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
			addProperty("Port", "TrikV6AnalogSensorPort", QString::fromUtf8("A1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class TrikWaitForMessage : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForMessage(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForMessage");
			setFriendlyName(QObject::tr("Wait for Message"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Stores a message from another robot into a given variable. When no incoming messages are present at the moment, a robot will wait for incoming message if 'Synchronized' property is true, and empty string will be assigned to a variable otherwise."));
			qReal::LabelProperties label_1(1, 1, 1.2, "Variable", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, 1.8, "Synchronized", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Synchronized:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForMessageClass.sdf").documentElement());
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
			addProperty("Synchronized", "bool", QString::fromUtf8("true"), QObject::tr("Synchronized"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr(""), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class TrikWaitForMotion : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForMotion(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForMotion");
			setFriendlyName(QObject::tr("Wait for Motion"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the motion sensor on the given port is triggered."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, QObject::tr("F1"), 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForMotionClass.sdf").documentElement());
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
		}
	};

	class TrikWaitForSonarDistance : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForSonarDistance(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForSonarDistance");
			setFriendlyName(QObject::tr("Wait for Ultrasonic Distance"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the ultrasonic sensor on the given port will be greater or less than the given in the 'Distance' parameter value (the distance is specified in centimeters, from 0 to 300)."));
			qReal::LabelProperties label_1(1, 0.8, -0.7, "Port", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.1, 1.2, "Distance", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Distance:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1.1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForSonarDistanceClass.sdf").documentElement());
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
			addProperty("Distance", "string", QObject::tr("0"), QObject::tr("Distance"), QObject::tr(""), false);
			addProperty("Port", "TrikV6DigitalSensorPort", QString::fromUtf8("D1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class TrikWaitForTouchSensor : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitForTouchSensor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitForTouchSensor");
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
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitForTouchSensorClass.sdf").documentElement());
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
			addProperty("Port", "TrikV6AnalogSensorPort", QString::fromUtf8("A1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class TrikWaitGamepadButton : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitGamepadButton(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitGamepadButton");
			setFriendlyName(QObject::tr("Wait Gamepad Button"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits for Android gamepad 'magic button' press. Buttons are identified by numbers from 1 to 5 (from left to right)"));
			qReal::LabelProperties label_1(1, -0.7, 1.2, QObject::tr("Wait gamepad button"), 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, -0.7, "Button", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(true);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Button:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitGamepadButtonClass.sdf").documentElement());
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
			addProperty("Button", "int", QString::fromUtf8("1"), QObject::tr("Button"), QObject::tr(""), false);
		}
	};

	class TrikWaitGamepadConnect : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitGamepadConnect(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitGamepadConnect");
			setFriendlyName(QObject::tr("Wait for Gamepad Connect"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits until Android gamepad is connected."));
			qReal::LabelProperties label_1(1, -1.4, -0.7, QObject::tr("Wait for Gamepad Connect"), 0);
			label_1.setBackground(Qt::transparent);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitGamepadConnectClass.sdf").documentElement());
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
		}
	};

	class TrikWaitGamepadDisconnect : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitGamepadDisconnect(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitGamepadDisconnect");
			setFriendlyName(QObject::tr("Wait for Gamepad Disconnect"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits until Android gamepad is disconnected."));
			qReal::LabelProperties label_1(1, -1.4, -0.7, QObject::tr("Wait for Gamepad Disconnect"), 0);
			label_1.setBackground(Qt::transparent);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitGamepadDisconnectClass.sdf").documentElement());
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
		}
	};

	class TrikWaitGamepadWheel : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitGamepadWheel(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitGamepadWheel");
			setFriendlyName(QObject::tr("Wait for Gamepad Wheel"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by gamepad wheel be greater or less than the given in the 'Angle' parameter value. Angle is measured from -100 (max left) to 100 (max right)."));
			qReal::LabelProperties label_1(1, -1.4, -0.7, QObject::tr("Wait for Gamepad Wheel"), 0);
			label_1.setBackground(Qt::transparent);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(true);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1.1, 1.2, "Angle", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Angle:"));
			addLabel(label_2);
			qReal::LabelProperties label_3(3, 1.1, 1.8, "Sign", false, 0);
			label_3.setBackground(Qt::white);
			label_3.setScalingX(false);
			label_3.setScalingY(false);
			label_3.setHard(false);
			label_3.setPlainTextMode(false);
			label_3.setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitGamepadWheelClass.sdf").documentElement());
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
			addProperty("Angle", "string", QObject::tr("0"), QObject::tr("Angle"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class TrikWaitPadPress : public qReal::NodeElementType
	{
	public:
		explicit TrikWaitPadPress(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWaitPadPress");
			setFriendlyName(QObject::tr("Wait Pad Press"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits for Android gamepad pad press (left pad has number 1, right pad - number 2)."));
			qReal::LabelProperties label_1(1, -0.4, 1.2, QObject::tr("Wait pad press"), 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 1, -0.7, "Pad", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(true);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Pad:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWaitPadPressClass.sdf").documentElement());
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
			addProperty("Pad", "int", QString::fromUtf8("1"), QObject::tr("Pad"), QObject::tr(""), false);
		}
	};

	class TrikWriteToFile : public qReal::NodeElementType
	{
	public:
		explicit TrikWriteToFile(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("TrikWriteToFile");
			setFriendlyName(QObject::tr("Write To File"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Writes a given message to a file. File path may be absolute or relative to a directory containing TRIK Studio executable."));
			qReal::LabelProperties label_1(1, 0.66, 1.2, "File", false, 0);
			label_1.setBackground(Qt::white);
			label_1.setScalingX(false);
			label_1.setScalingY(false);
			label_1.setHard(false);
			label_1.setPlainTextMode(false);
			label_1.setPrefix(QObject::tr("File:"));
			addLabel(label_1);
			qReal::LabelProperties label_2(2, 0.66, 1.8, "Text", false, 0);
			label_2.setBackground(Qt::white);
			label_2.setScalingX(false);
			label_2.setScalingY(false);
			label_2.setHard(false);
			label_2.setPlainTextMode(false);
			label_2.setPrefix(QObject::tr("Text:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TrikWriteToFileClass.sdf").documentElement());
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
			addProperty("File", "string", QObject::tr("output.txt"), QObject::tr("File"), QObject::tr(""), false);
			addProperty("Text", "string", QObject::tr(""), QObject::tr("Text"), QObject::tr(""), false);
		}
	};

