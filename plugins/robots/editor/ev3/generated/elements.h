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

	class Ev3Beep : public qReal::NodeElementType
	{
	public:
		explicit Ev3Beep(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3Beep");
			setFriendlyName(QObject::tr("Beep"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Plays on the robot a sound with the fixed frequency. There are two parameters. The first one is a loudness of the sound, the second means if program should wait for sound completion or go to next block right away."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 1.2, -0.7, "Volume", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Volume:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1.4, 1.2, "WaitForCompletion", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Wait for Completion:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3BeepClass.sdf").documentElement());
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

	class Ev3CalibrateBlackLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3CalibrateBlackLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3CalibrateBlackLL");
			setFriendlyName(QObject::tr("Calibrate Black"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Calibrates the black threshold for each sensor in the array. Place the array over the black surface with all sensors on the black area."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3CalibrateBlackLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3CalibrateGyroscope : public qReal::NodeElementType
	{
	public:
		explicit Ev3CalibrateGyroscope(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3CalibrateGyroscope");
			setFriendlyName(QObject::tr("Calibrate gyroscope"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets gyroscope's angle to zero in current position."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3CalibrateGyroscopeClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3CalibratePIDLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3CalibratePIDLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3CalibratePIDLL");
			setFriendlyName(QObject::tr("Calibrate PID"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets set point, P, I, D value of PID control and P factor, I factor, D factor for P, I, D value of PID control."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.2, "SetPoint", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Set point:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.9, 1.8, "P", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("P:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.9, 2.4, "PFactor", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("P factor:"));
			addLabel(label_4);
			QSharedPointer<qReal::LabelProperties> label_5(new qReal::LabelProperties(5, 0.9, 3, "I", false, 0));
			label_5->setBackground(Qt::white);
			label_5->setScalingX(false);
			label_5->setScalingY(false);
			label_5->setHard(false);
			label_5->setPlainTextMode(false);
			label_5->setPrefix(QObject::tr("I:"));
			addLabel(label_5);
			QSharedPointer<qReal::LabelProperties> label_6(new qReal::LabelProperties(6, 0.9, 3.6, "IFactor", false, 0));
			label_6->setBackground(Qt::white);
			label_6->setScalingX(false);
			label_6->setScalingY(false);
			label_6->setHard(false);
			label_6->setPlainTextMode(false);
			label_6->setPrefix(QObject::tr("I factor:"));
			addLabel(label_6);
			QSharedPointer<qReal::LabelProperties> label_7(new qReal::LabelProperties(7, 0.9, 4.2, "D", false, 0));
			label_7->setBackground(Qt::white);
			label_7->setScalingX(false);
			label_7->setScalingY(false);
			label_7->setHard(false);
			label_7->setPlainTextMode(false);
			label_7->setPrefix(QObject::tr("D:"));
			addLabel(label_7);
			QSharedPointer<qReal::LabelProperties> label_8(new qReal::LabelProperties(8, 0.9, 4.8, "DFactor", false, 0));
			label_8->setBackground(Qt::white);
			label_8->setScalingX(false);
			label_8->setScalingY(false);
			label_8->setHard(false);
			label_8->setPlainTextMode(false);
			label_8->setPrefix(QObject::tr("D factor:"));
			addLabel(label_8);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3CalibratePIDLLClass.sdf").documentElement());
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
			addProperty("D", "int", QString::fromUtf8("8"), QObject::tr("D"), QObject::tr(""), false);
			addProperty("DFactor", "int", QString::fromUtf8("32"), QObject::tr("D factor"), QObject::tr(""), false);
			addProperty("I", "int", QString::fromUtf8("0"), QObject::tr("I"), QObject::tr(""), false);
			addProperty("IFactor", "int", QString::fromUtf8("32"), QObject::tr("I factor"), QObject::tr(""), false);
			addProperty("P", "int", QString::fromUtf8("25"), QObject::tr("P"), QObject::tr(""), false);
			addProperty("PFactor", "int", QString::fromUtf8("32"), QObject::tr("P factor"), QObject::tr(""), false);
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("SetPoint", "int", QString::fromUtf8("45"), QObject::tr("Set point"), QObject::tr(""), false);
		}
	};

	class Ev3CalibrateWhiteLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3CalibrateWhiteLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3CalibrateWhiteLL");
			setFriendlyName(QObject::tr("Calibrate White"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Calibrates the white threshold for each sensor in the array. Place the array over the white surface with all sensors on the white area."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3CalibrateWhiteLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3ClearEncoder : public qReal::NodeElementType
	{
	public:
		explicit Ev3ClearEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3ClearEncoder");
			setFriendlyName(QObject::tr("Clear Encoder"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Nullifies tacho limit of the motors on the given ports."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Ports", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3ClearEncoderClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("A, B, C, D"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class Ev3DrawCircle : public qReal::NodeElementType
	{
	public:
		explicit Ev3DrawCircle(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3DrawCircle");
			setFriendlyName(QObject::tr("Draw Circle"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws on the robot screen a circle with the given center and radius."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 1, 1.2, "XCoordinateCircle", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1, 1.8, "YCoordinateCircle", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1, 2.4, "CircleRadius", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Radius:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 1, 3, "Filled", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Filled:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3DrawCircleClass.sdf").documentElement());
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
			addProperty("CircleRadius", "int", QString::fromUtf8("40"), QObject::tr("Radius"), QObject::tr(""), false);
			addProperty("Filled", "bool", QString::fromUtf8("false"), QObject::tr("Filled"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("XCoordinateCircle", "int", QString::fromUtf8("85"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateCircle", "int", QString::fromUtf8("70"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class Ev3DrawLine : public qReal::NodeElementType
	{
	public:
		explicit Ev3DrawLine(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3DrawLine");
			setFriendlyName(QObject::tr("Draw Line"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws a segment on the robot screen. The parameters specify the ends of the segment."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.72, 1.2, "X1CoordinateLine", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X1:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.72, 1.8, "Y1CoordinateLine", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y1:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.72, 2.4, "X2CoordinateLine", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("X2:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.72, 3, "Y2CoordinateLine", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Y2:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3DrawLineClass.sdf").documentElement());
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
			addProperty("X1CoordinateLine", "int", QString::fromUtf8("20"), QObject::tr("X1"), QObject::tr(""), false);
			addProperty("X2CoordinateLine", "int", QString::fromUtf8("150"), QObject::tr("X2"), QObject::tr(""), false);
			addProperty("Y1CoordinateLine", "int", QString::fromUtf8("90"), QObject::tr("Y1"), QObject::tr(""), false);
			addProperty("Y2CoordinateLine", "int", QString::fromUtf8("20"), QObject::tr("Y2"), QObject::tr(""), false);
		}
	};

	class Ev3DrawPixel : public qReal::NodeElementType
	{
	public:
		explicit Ev3DrawPixel(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3DrawPixel");
			setFriendlyName(QObject::tr("Draw Pixel"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws one pixel in the specified coordinates on the robot screen."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.72, 1.2, "XCoordinatePix", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.72, 1.8, "YCoordinatePix", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3DrawPixelClass.sdf").documentElement());
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
			addProperty("XCoordinatePix", "int", QString::fromUtf8("90"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinatePix", "int", QString::fromUtf8("70"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class Ev3DrawRect : public qReal::NodeElementType
	{
	public:
		explicit Ev3DrawRect(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3DrawRect");
			setFriendlyName(QObject::tr("Draw Rectangle"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Draws a rectangle on the robot screen. The parameters specify the coordinates of top-left corner, the width and the height of the rectangle."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 1, 1.2, "XCoordinateRect", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1, 1.8, "YCoordinateRect", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1, 2.4, "WidthRect", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Width:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 1, 3, "HeightRect", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Height:"));
			addLabel(label_4);
			QSharedPointer<qReal::LabelProperties> label_5(new qReal::LabelProperties(5, 1, 3.6, "Filled", false, 0));
			label_5->setBackground(Qt::white);
			label_5->setScalingX(false);
			label_5->setScalingY(false);
			label_5->setHard(false);
			label_5->setPlainTextMode(false);
			label_5->setPrefix(QObject::tr("Filled:"));
			addLabel(label_5);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3DrawRectClass.sdf").documentElement());
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
			addProperty("HeightRect", "int", QString::fromUtf8("30"), QObject::tr("Height"), QObject::tr(""), false);
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("WidthRect", "int", QString::fromUtf8("40"), QObject::tr("Width"), QObject::tr(""), false);
			addProperty("XCoordinateRect", "int", QString::fromUtf8("75"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateRect", "int", QString::fromUtf8("50"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class Ev3EngineMovementCommand : public qReal::NodeElementType
	{
	public:
		explicit Ev3EngineMovementCommand(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3EngineMovementCommand");
			setFriendlyName(QObject::tr("Ev3EngineMovementCommand"));
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
			addProperty("Ports", "string", QObject::tr("B, C"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class Ev3EnginesBackward : public qReal::NodeElementType
	{
	public:
		explicit Ev3EnginesBackward(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3EnginesBackward");
			setFriendlyName(QObject::tr("Motors Backward"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables motors on the given ports in reverse mode with the given power. Ports are specified with A, B or C letters divided by commas. The power is specified in percents with the number from -100 to 100, if negative number is specified then the motor is enabled in the usual mode."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.5, -0.7, "Ports", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.2, "Power", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Power:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3EnginesBackwardClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("B, C"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class Ev3EnginesForward : public qReal::NodeElementType
	{
	public:
		explicit Ev3EnginesForward(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3EnginesForward");
			setFriendlyName(QObject::tr("Motors Forward"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Enables motors on the given ports with the given power. Ports are specified with A, B or C letters divided by commas. The power is specified in percents with the number from -100 to 100, if negative number is specified then the motor is enabled in the reverse mode."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.5, -0.7, "Ports", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.2, "Power", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Power:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3EnginesForwardClass.sdf").documentElement());
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
			addProperty("Ports", "string", QObject::tr("B, C"), QObject::tr("Ports"), QObject::tr(""), false);
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class Ev3EnginesStop : public qReal::NodeElementType
	{
	public:
		explicit Ev3EnginesStop(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3EnginesStop");
			setFriendlyName(QObject::tr("Stop Motors"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Disables motors on the given ports."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.5, -0.7, "Ports", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Ports:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3EnginesStopClass.sdf").documentElement());
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
			addProperty("Mode", "BrakeEngineMode", QString::fromUtf8("brake"), QObject::tr("Mode"), QObject::tr(""), false);
			addProperty("Ports", "string", QObject::tr("A, B, C, D"), QObject::tr("Ports"), QObject::tr(""), false);
		}
	};

	class Ev3Led : public qReal::NodeElementType
	{
	public:
		explicit Ev3Led(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3Led");
			setFriendlyName(QObject::tr("Led"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets the color of the LED on the robot`s front panel."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, -0.7, "Color", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Color:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3LedClass.sdf").documentElement());
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
			addProperty("Color", "Ev3LedColor", QString::fromUtf8("red"), QObject::tr("Color"), QObject::tr(""), false);
		}
	};

	class Ev3PlayTone : public qReal::NodeElementType
	{
	public:
		explicit Ev3PlayTone(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3PlayTone");
			setFriendlyName(QObject::tr("Play Tone"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Plays on the robot a sound with the given frequency and duration. This block is similar to the 'Beep' block wuth the only difference that here you can specify sound parameters."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 1, -0.7, "Frequency", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Frequency:"));
			label_1->setSuffix(QObject::tr("Hz"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1.2, 1.2, "Volume", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Volume:"));
			label_2->setSuffix(QObject::tr("%"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1.2, 1.8, "Duration", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Duration"));
			label_3->setSuffix(QObject::tr("ms"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 1.2, 2.4, "WaitForCompletion", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Wait for Completion:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3PlayToneClass.sdf").documentElement());
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

	class Ev3ReadAllLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3ReadAllLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3ReadAllLL");
			setFriendlyName(QObject::tr("Read Sensor to Array"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Read the values from the Line Leader.  Amount of light or dark each sensor sees.  Typically between 0-20.  0=black, 100=white."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.2, "Variable", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Array:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3ReadAllLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr("a"), QObject::tr("Array Variable"), QObject::tr(""), false);
		}
	};

	class Ev3ReadAvrLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3ReadAvrLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3ReadAvrLL");
			setFriendlyName(QObject::tr("Read Average to Variable"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Read the Weighted Average value from the sensor.  This value is calculated internally by the sensor where each of the eight sensors is either triggered or not and multiplied by a factor to help determine if the line is left, right or on center of the line (according to the set point). EXPECTED VALUES: 0-80 (-1=ERROR)"));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.2, "Variable", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Variable:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3ReadAvrLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class Ev3ReadRGB : public qReal::NodeElementType
	{
	public:
		explicit Ev3ReadRGB(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3ReadRGB");
			setFriendlyName(QObject::tr("Read RGB into Variables"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Reads R, G, B channels values into given variables"));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.8, 1.2, "RVariable", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("R Variable:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.8, 1.8, "GVariable", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("G Variable:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.8, 2.4, "BVariable", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("B Variable:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3ReadRGBClass.sdf").documentElement());
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
			addProperty("BVariable", "string", QObject::tr("b"), QObject::tr("B Variable"), QObject::tr(""), false);
			addProperty("GVariable", "string", QObject::tr("g"), QObject::tr("G Variable"), QObject::tr(""), false);
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("RVariable", "string", QObject::tr("r"), QObject::tr("R Variable"), QObject::tr(""), false);
		}
	};

	class Ev3ReadSteeringLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3ReadSteeringLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3ReadSteeringLL");
			setFriendlyName(QObject::tr("Read Steering to Variable"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Read the Steering value from the sensor.  This value is calculated internally and can directly be used to set turning values for the robot's motors. EXPECTED VALUES: -100 to 100 (-101=ERROR)"));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.2, "Variable", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Variable:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3ReadSteeringLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class Ev3SendMail : public qReal::NodeElementType
	{
	public:
		explicit Ev3SendMail(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3SendMail");
			setFriendlyName(QObject::tr("Send Mail"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sends mail (message) to another robot. If Receiver name left empty, message will be sent to all connected robots"));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.9, 1.2, "MsgType", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Message type:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.8, "Message", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Message:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.9, 2.4, "ReceiverName", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Receiver name:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.9, 3, "ReceiverMailBoxName", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Mailbox name:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3SendMailClass.sdf").documentElement());
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
			addProperty("Message", "string", QObject::tr("42"), QObject::tr("Message"), QObject::tr(""), false);
			addProperty("MsgType", "Ev3MsgType", QString::fromUtf8("int"), QObject::tr("Message type"), QObject::tr(""), false);
			addProperty("ReceiverMailBoxName", "string", QObject::tr("EV3MailBox"), QObject::tr("Mailbox name"), QObject::tr(""), false);
			addProperty("ReceiverName", "string", QObject::tr(""), QObject::tr("Receiver name"), QObject::tr(""), false);
		}
	};

	class Ev3SensorBlock : public qReal::NodeElementType
	{
	public:
		explicit Ev3SensorBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3SensorBlock");
			setFriendlyName(QObject::tr("Ev3SensorBlock"));
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3SleepLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3SleepLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3SleepLL");
			setFriendlyName(QObject::tr("Sleep Line Leader"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Puts the line leader to sleep conserve power"));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3SleepLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3StartCompassCalibration : public qReal::NodeElementType
	{
	public:
		explicit Ev3StartCompassCalibration(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3StartCompassCalibration");
			setFriendlyName(QObject::tr("Start Compass Calibration"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Starts compass calibration under program control. To calibrate, robot needs to spin >=540 clockwise and counterclockwise with minimum 20 seconds duration for each direction. Atfer robot rotation add Stop Compass Сalibration block."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3StartCompassCalibrationClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3StopCompassCalibration : public qReal::NodeElementType
	{
	public:
		explicit Ev3StopCompassCalibration(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3StopCompassCalibration");
			setFriendlyName(QObject::tr("Stop Compass Calibration"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Ends compass calibration process. Stores result of calibration into the given variable. Not zero means success."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.8, 1.2, "Variable", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Variable:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3StopCompassCalibrationClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr(""), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForButton : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForButton(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForButton");
			setFriendlyName(QObject::tr("Wait for button"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits for press of a button on a brick."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, 1.2, "Button", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Button:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForButtonClass.sdf").documentElement());
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
			addProperty("Button", "Ev3Buttons", QString::fromUtf8("Up"), QObject::tr("Button"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForColor : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForColor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForColor");
			setFriendlyName(QObject::tr("Wait for Color"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the color sensor on the given port will recognize the given color."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.74, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.74, 1.2, "Color", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Color:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForColorClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForColorIntensity : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForColorIntensity(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForColorIntensity");
			setFriendlyName(QObject::tr("Wait for Color Intensity"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the color sensor on the given port will be greater or less than the given in the 'Intensity' parameter value (the intensity is specified in percents, 0 to 100)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1.1, 1.2, "Intensity", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Intensity:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1.1, 1.8, "Sign", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForColorIntensityClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForEncoder : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForEncoder(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForEncoder");
			setFriendlyName(QObject::tr("Wait for Encoder"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the tacho limit of the motor on the given port will reach the value of the 'Tacho Limit' parameter."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.8, 1.2, "TachoLimit", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Tacho Limit:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.8, 1.8, "Sign", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForEncoderClass.sdf").documentElement());
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
			addProperty("Port", "Ev3MotorPort", QString::fromUtf8("B"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
			addProperty("TachoLimit", "string", QObject::tr(""), QObject::tr("Tacho Limit"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForGyroscope : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForGyroscope(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForGyroscope");
			setFriendlyName(QObject::tr("Wait for Gyroscope"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the gyroscope on the given port will be greater or less than the given."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1.1, 1.2, "Degrees", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Value:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1.1, 1.8, "Sign", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForGyroscopeClass.sdf").documentElement());
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
			addProperty("Degrees", "string", QObject::tr("90"), QObject::tr("Value"), QObject::tr(""), false);
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForLight : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForLight(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForLight");
			setFriendlyName(QObject::tr("Wait for Light"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the light sensor on the given port will be greater or less than the given in the 'Percents' parameter value (0 to 100)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.2, "Percents", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Percents:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1, 1.8, "Sign", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForLightClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForReceivingMail : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForReceivingMail(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForReceivingMail");
			setFriendlyName(QObject::tr("Wait for Mail Receiving"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Stores a message from another robot (fom mailbox) into a given variable. When no incoming messages are present at the moment, a robot will wait for incoming message if 'Synchronized' property is true, and doing nothing otherwise."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.9, 1.2, "MsgType", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Message type:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.9, 1.8, "MailBoxName", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Mailbox name:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.9, 2.4, "Variable", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Variable:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.9, 3, "Synchronized", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Synchronized:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForReceivingMailClass.sdf").documentElement());
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
			addProperty("MailBoxName", "string", QObject::tr("EV3MailBox"), QObject::tr("Mailbox name"), QObject::tr(""), false);
			addProperty("MsgType", "Ev3MsgType", QString::fromUtf8("int"), QObject::tr("Message type"), QObject::tr(""), false);
			addProperty("Synchronized", "bool", QString::fromUtf8("true"), QObject::tr("Synchronized"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr(""), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForSonarDistance : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForSonarDistance(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForSonarDistance");
			setFriendlyName(QObject::tr("Wait for Range Sensor"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the value returned by the ultrasonic or infrared range sensor on the given port will be greater or less than the given in the 'Distance' parameter value (the distance is specified in centimeters, 0 to 255)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1, 1.2, "Distance", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Distance:"));
			label_2->setSuffix(QObject::tr("cm"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1.1, 1.8, "Sign", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForSonarDistanceClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForSound : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForSound(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForSound");
			setFriendlyName(QObject::tr("Wait for Sound Sensor"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the loudness obtained by the sound sensor on the given port will be greater or less than the given value."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1, 1.2, "Volume", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Volume:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1, 1.8, "Sign", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Sign:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForSoundClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
			addProperty("Sign", "DistanceSign", QString::fromUtf8("greater"), QObject::tr("Sign"), QObject::tr(""), false);
			addProperty("Volume", "string", QObject::tr("0"), QObject::tr("Volume"), QObject::tr(""), false);
		}
	};

	class Ev3WaitForTouchSensor : public qReal::NodeElementType
	{
	public:
		explicit Ev3WaitForTouchSensor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WaitForTouchSensor");
			setFriendlyName(QObject::tr("Wait for Touch Sensor"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits till the touch sensor is pressed. The only parameter is a sensor`s port number (1, 2, 3 or 4)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WaitForTouchSensorClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class Ev3WakeUpLL : public qReal::NodeElementType
	{
	public:
		explicit Ev3WakeUpLL(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Ev3WakeUpLL");
			setFriendlyName(QObject::tr("Wake Up Line Leader"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Wakes the line leader to prepare for use."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Port", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Port:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/Ev3WakeUpLLClass.sdf").documentElement());
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
			addProperty("Port", "Ev3SensorPort", QString::fromUtf8("1"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

