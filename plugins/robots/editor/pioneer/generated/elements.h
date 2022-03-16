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

	class GeoLanding : public qReal::NodeElementType
	{
	public:
		explicit GeoLanding(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("GeoLanding");
			setFriendlyName(QObject::tr("Landing"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Orders quadcopter to land."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/GeoLandingClass.sdf").documentElement());
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

	class GeoTakeoff : public qReal::NodeElementType
	{
	public:
		explicit GeoTakeoff(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("GeoTakeoff");
			setFriendlyName(QObject::tr("Takeoff"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Orders quadcopter to takeoff."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/GeoTakeoffClass.sdf").documentElement());
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

	class GoToGPSPoint : public qReal::NodeElementType
	{
	public:
		explicit GoToGPSPoint(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("GoToGPSPoint");
			setFriendlyName(QObject::tr("Go to point"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Orders quadcopter to fly to given GPS coordinates."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "Latitude", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Latitude:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Longitude", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Longitude:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Altitude", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Altitude:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/GoToGPSPointClass.sdf").documentElement());
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
			addProperty("Altitude", "string", QObject::tr("50"), QObject::tr("Altitude"), QObject::tr(""), false);
			addProperty("Latitude", "string", QObject::tr("600859810"), QObject::tr("Latitude"), QObject::tr(""), false);
			addProperty("Longitude", "string", QObject::tr("304206500"), QObject::tr("Longitude"), QObject::tr(""), false);
		}
	};

	class GoToPoint : public qReal::NodeElementType
	{
	public:
		explicit GoToPoint(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("GoToPoint");
			setFriendlyName(QObject::tr("Go to local point"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Orders quadcopter to fly to given coordinates."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "X", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Y", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Z", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Z:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.7, 3, "Time", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Time:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/GoToPointClass.sdf").documentElement());
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
			addProperty("Time", "string", QObject::tr(""), QObject::tr("Time"), QObject::tr(""), false);
			addProperty("X", "string", QObject::tr("0"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("Y", "string", QObject::tr("0"), QObject::tr("Y"), QObject::tr(""), false);
			addProperty("Z", "string", QObject::tr("0"), QObject::tr("Z"), QObject::tr(""), false);
		}
	};

	class PioneerGPIOInit : public qReal::NodeElementType
	{
	public:
		explicit PioneerGPIOInit(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGPIOInit");
			setFriendlyName(QObject::tr("GPIO Initialization"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Create GPIO in settings port."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, -0.7, "PinName", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Pin name:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.2, "Port", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Port:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 1.8, "Pin", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Pin:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.7, 2.4, "Mode", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Mode:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGPIOInitClass.sdf").documentElement());
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
			addProperty("Mode", "GPIOMode", QString::fromUtf8("INPUT"), QObject::tr("Mode"), QObject::tr(""), false);
			addProperty("Pin", "int", QString::fromUtf8("0"), QObject::tr("Pin"), QObject::tr(""), false);
			addProperty("PinName", "string", QObject::tr("pin_name"), QObject::tr("Pin name"), QObject::tr(""), false);
			addProperty("Port", "GPIOPort", QString::fromUtf8("A"), QObject::tr("Port"), QObject::tr(""), false);
		}
	};

	class PioneerGetAccel : public qReal::NodeElementType
	{
	public:
		explicit PioneerGetAccel(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGetAccel");
			setFriendlyName(QObject::tr("Get Accelerometer"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns accelerometer."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "X", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Y", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Z", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Z:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGetAccelClass.sdf").documentElement());
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
			addProperty("X", "string", QObject::tr("aX"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("Y", "string", QObject::tr("aY"), QObject::tr("Y"), QObject::tr(""), false);
			addProperty("Z", "string", QObject::tr("aZ"), QObject::tr("Z"), QObject::tr(""), false);
		}
	};

	class PioneerGetGyro : public qReal::NodeElementType
	{
	public:
		explicit PioneerGetGyro(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGetGyro");
			setFriendlyName(QObject::tr("Get Gyroscope"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns gyroscope."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "X", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Y", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Z", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Z:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGetGyroClass.sdf").documentElement());
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
			addProperty("X", "string", QObject::tr("gX"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("Y", "string", QObject::tr("gY"), QObject::tr("Y"), QObject::tr(""), false);
			addProperty("Z", "string", QObject::tr("gZ"), QObject::tr("Z"), QObject::tr(""), false);
		}
	};

	class PioneerGetLPSPosition : public qReal::NodeElementType
	{
	public:
		explicit PioneerGetLPSPosition(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGetLPSPosition");
			setFriendlyName(QObject::tr("Get LPS Position"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns position (local positioning system)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "X", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Y", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Z", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Z:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGetLPSPositionClass.sdf").documentElement());
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
			addProperty("X", "string", QObject::tr("x"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("Y", "string", QObject::tr("y"), QObject::tr("Y"), QObject::tr(""), false);
			addProperty("Z", "string", QObject::tr("z"), QObject::tr("Z"), QObject::tr(""), false);
		}
	};

	class PioneerGetLPSVelocity : public qReal::NodeElementType
	{
	public:
		explicit PioneerGetLPSVelocity(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGetLPSVelocity");
			setFriendlyName(QObject::tr("Get LPS Velocity"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns velocity (local position system)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "X", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Y", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Z", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Z:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGetLPSVelocityClass.sdf").documentElement());
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
			addProperty("X", "string", QObject::tr("velX"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("Y", "string", QObject::tr("velY"), QObject::tr("Y"), QObject::tr(""), false);
			addProperty("Z", "string", QObject::tr("velZ"), QObject::tr("Z"), QObject::tr(""), false);
		}
	};

	class PioneerGetLPSYaw : public qReal::NodeElementType
	{
	public:
		explicit PioneerGetLPSYaw(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGetLPSYaw");
			setFriendlyName(QObject::tr("Get LPS Yaw"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns yaw (local position system)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "Yaw", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Yaw:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGetLPSYawClass.sdf").documentElement());
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
			addProperty("Yaw", "string", QObject::tr("yaw"), QObject::tr("Yaw"), QObject::tr(""), false);
		}
	};

	class PioneerGetOrientation : public qReal::NodeElementType
	{
	public:
		explicit PioneerGetOrientation(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerGetOrientation");
			setFriendlyName(QObject::tr("Get Orientation"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns orientation."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "Roll", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Roll:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.8, "Pitch", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Pitch:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 2.4, "Azimuth", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Azimuth:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerGetOrientationClass.sdf").documentElement());
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
			addProperty("Azimuth", "string", QObject::tr("azimuth"), QObject::tr("Azimuth"), QObject::tr(""), false);
			addProperty("Pitch", "string", QObject::tr("pitch"), QObject::tr("Pitch"), QObject::tr(""), false);
			addProperty("Roll", "string", QObject::tr("roll"), QObject::tr("Roll"), QObject::tr(""), false);
		}
	};

	class PioneerLed : public qReal::NodeElementType
	{
	public:
		explicit PioneerLed(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerLed");
			setFriendlyName(QObject::tr("Led"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets the color of the specified LED on a quadcopter."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, -0.8, "Number", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Number:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.2, "Red", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Red:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.7, 1.8, "Green", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Green:"));
			addLabel(label_3);
			QSharedPointer<qReal::LabelProperties> label_4(new qReal::LabelProperties(4, 0.7, 2.4, "Blue", false, 0));
			label_4->setBackground(Qt::white);
			label_4->setScalingX(false);
			label_4->setScalingY(false);
			label_4->setHard(false);
			label_4->setPlainTextMode(false);
			label_4->setPrefix(QObject::tr("Blue:"));
			addLabel(label_4);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerLedClass.sdf").documentElement());
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
			addProperty("Blue", "string", QObject::tr("0.0"), QObject::tr("Blue"), QObject::tr(""), false);
			addProperty("Green", "string", QObject::tr("0.0"), QObject::tr("Green"), QObject::tr(""), false);
			addProperty("Number", "string", QObject::tr("0"), QObject::tr("Number"), QObject::tr(""), false);
			addProperty("Red", "string", QObject::tr("0.0"), QObject::tr("Red"), QObject::tr(""), false);
		}
	};

	class PioneerMagnet : public qReal::NodeElementType
	{
	public:
		explicit PioneerMagnet(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerMagnet");
			setFriendlyName(QObject::tr("Magnet"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Controls magnet on a quadcopter."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerMagnetClass.sdf").documentElement());
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
			addProperty("State", "bool", QString::fromUtf8("false"), QObject::tr("State on"), QObject::tr(""), false);
		}
	};

	class PioneerPrint : public qReal::NodeElementType
	{
	public:
		explicit PioneerPrint(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerPrint");
			setFriendlyName(QObject::tr("Print"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Prints given string on a console."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, 1.2, "PrintText", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Text:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerPrintClass.sdf").documentElement());
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
			addProperty("PrintText", "string", QObject::tr("Enter some text here"), QObject::tr("Text"), QObject::tr(""), false);
		}
	};

	class PioneerReadGPIO : public qReal::NodeElementType
	{
	public:
		explicit PioneerReadGPIO(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerReadGPIO");
			setFriendlyName(QObject::tr("Read GPIO"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Returns GPIO value."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, -0.7, "PinName", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Pin name:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.7, 1.2, "Variable", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Variable:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerReadGPIOClass.sdf").documentElement());
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
			addProperty("PinName", "string", QObject::tr("pin_name"), QObject::tr("Pin name"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class PioneerReadRangeSensor : public qReal::NodeElementType
	{
	public:
		explicit PioneerReadRangeSensor(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerReadRangeSensor");
			setFriendlyName(QObject::tr("Read Range Sensor"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Reads distance from rangefinder."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, 1.2, "Variable", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerReadRangeSensorClass.sdf").documentElement());
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
			addProperty("Variable", "string", QObject::tr("dist"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class PioneerSetGPIO : public qReal::NodeElementType
	{
	public:
		explicit PioneerSetGPIO(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerSetGPIO");
			setFriendlyName(QObject::tr("Set GPIO state"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Set GPIO value in \"true/false\"."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, -0.7, "PinName", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Pin name:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerSetGPIOClass.sdf").documentElement());
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
			addProperty("PinName", "string", QObject::tr("pin_name"), QObject::tr("Pin name"), QObject::tr(""), false);
			addProperty("State", "bool", QString::fromUtf8("false"), QObject::tr("State on"), QObject::tr(""), false);
		}
	};

	class PioneerSystem : public qReal::NodeElementType
	{
	public:
		explicit PioneerSystem(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerSystem");
			setFriendlyName(QObject::tr("System"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Executes given Lua script."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, 1.2, "Command", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Command:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerSystemClass.sdf").documentElement());
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
			addProperty("Command", "string", QObject::tr("print('Hello')"), QObject::tr("Command"), QObject::tr(""), false);
			addProperty("Evaluate", "bool", QString::fromUtf8("false"), QObject::tr("Evaluate"), QObject::tr(""), false);
		}
	};

	class PioneerYaw : public qReal::NodeElementType
	{
	public:
		explicit PioneerYaw(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PioneerYaw");
			setFriendlyName(QObject::tr("Yaw"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets yaw for quadcopter"));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.7, -0.8, "Angle", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Angle:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PioneerYawClass.sdf").documentElement());
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
			addProperty("Angle", "string", QObject::tr("0.0"), QObject::tr("Angle (degrees)"), QObject::tr(""), false);
		}
	};

