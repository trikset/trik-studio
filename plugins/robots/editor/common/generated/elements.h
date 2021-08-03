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

	class AbstractNode : public qReal::NodeElementType
	{
	public:
		explicit AbstractNode(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("AbstractNode");
			setFriendlyName(QObject::tr("AbstractNode"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/AbstractNodeClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
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

	class BlackBox : public qReal::NodeElementType
	{
	public:
		explicit BlackBox(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("BlackBox");
			setFriendlyName(QObject::tr("Black Box"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Operator with an unknown information processing rule."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, -0.4, -0.7, "name", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.66, 1.2, "inputsCount", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Number of variables:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/BlackBoxClass.sdf").documentElement());
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
			addProperty("inputsCount", "int", QString::fromUtf8("1"), QObject::tr("Number of variables"), QObject::tr(""), false);
		}
	};

	class BlackBoxDiagram : public qReal::NodeElementType
	{
	public:
		explicit BlackBoxDiagram(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("BlackBoxDiagram");
			setFriendlyName(QObject::tr("Black Box Diagram"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.205882, 0.0588235, "name", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/BlackBoxDiagramClass.sdf").documentElement());
			setSize(QSizeF(204, 204));
			initProperties();
			setMouseGesture("");
			addPointPort(qReal::PointPortInfo(QPointF(0.00980392, 0.5), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.5, 0.00980392), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.990196, 0.5), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.5, 0.990196), false, false, 204, 204, "NonTyped"));
			setResizable(true);
			setContainer(true);
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
			addProperty("finished", "bool", QString::fromUtf8("false"), QObject::tr("Finished"), QObject::tr(""), false);
		}
	};

	class BlackBoxDiagramGroup : public qReal::PatternType
	{
	public:
		explicit BlackBoxDiagramGroup(qReal::Metamodel &metamodel)
			: PatternType(metamodel)
		{
			setName("BlackBoxDiagramGroup");
			setFriendlyName(QObject::tr("BlackBoxDiagramGroup"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			setXml(QString::fromUtf8(" <group rootNode=\"diagram\" name=\"BlackBoxDiagramGroup\">\n  <groupNode type=\"BlackBoxDiagram\" name=\"diagram\" xPosition=\"0\" yPosition=\"0\"/>\n  <groupNode type=\"InitialNode\" parent=\"diagram\" name=\"initialNode\" xPosition=\"50\" yPosition=\"300\"/>\n </group>\n"));
		}

	};

	class ClearScreen : public qReal::NodeElementType
	{
	public:
		explicit ClearScreen(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("ClearScreen");
			setFriendlyName(QObject::tr("Clear Screen"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Clears everything drawn on the robot`s screen."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/ClearScreenClass.sdf").documentElement());
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
		}
	};

	class CommentBlock : public qReal::NodeElementType
	{
	public:
		explicit CommentBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("CommentBlock");
			setFriendlyName(QObject::tr("Comment"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("This block can hold text notes that are ignored by generators and interpreters. Use it for improving the diagram readability."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.1, 0.2, "Comment", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/CommentBlockClass.sdf").documentElement());
			setSize(QSizeF(200, 100));
			initProperties();
			setMouseGesture("");
			addLinePort(qReal::LinePortInfo(QLineF(0, 0.05, 0, 0.95), false, false, false, false, 200, 100, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.025, 0, 0.875, 0), false, false, false, false, 200, 100, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(1, 0.25, 1, 0.95), false, false, false, false, 200, 100, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.025, 1, 0.975, 1), false, false, false, false, 200, 100, "NonTyped"));
			addLinePort(qReal::LinePortInfo(QLineF(0.9, 0, 1, 0.2), false, false, false, false, 200, 100, "NonTyped"));
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
			addProperty("Comment", "string", QObject::tr("Enter some text here..."), QObject::tr("Comment"), QObject::tr(""), false);
		}
	};

	class ControlFlow : public qReal::EdgeElementType
	{
	public:
		explicit ControlFlow(qReal::Metamodel &metamodel)
			: EdgeElementType(metamodel)
		{
			setName("ControlFlow");
			setFriendlyName(QObject::tr("Link"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("For creating a link between two elements A and B you can just hover a mouse above A, press the right mouse button and (without releasing it) draw a line to the element B. Alternatively you can just 'pull' a link from a small blue circle next to the element."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0, 0, "Guard", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			setFromPortTypes({"NonTyped", });
			setToPortTypes({"NonTyped", });
			setShapeType(qReal::LinkShape::broken);
			setPenWidth(1);
			setPenColor(QColor(0,0,0));
			setPenStyle(Qt::SolidLine);
			setDividable(true)
;			initProperties();
		}

		virtual ~ControlFlow() {}

		void drawStartArrow(QPainter * painter) const override
		{
			QBrush old = painter->brush();
			QBrush brush;
			brush.setStyle(Qt::SolidPattern);
			painter->setBrush(brush);
			painter->setBrush(old);
		}

		void drawEndArrow(QPainter * painter) const override
		{
			QBrush old = painter->brush();
			QBrush brush;
			brush.setStyle(Qt::SolidPattern);
			painter->setBrush(brush);
			static const QPointF points[] = {
				QPointF(-5,10),
				QPointF(0,0),
				QPointF(5,10)
			};
			painter->drawPolyline(points, 3);
			painter->setBrush(old);
		}

	private:
		void initProperties()
		{
			addProperty("Guard", "GuardType", QString::fromUtf8(""), QObject::tr("Guard"), QObject::tr(""), false);
		}
	};

	class DrawInCell : public qReal::NodeElementType
	{
	public:
		explicit DrawInCell(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("DrawInCell");
			setFriendlyName(QObject::tr("Draw in cell"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Paints the cell under the robot."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.54, -0.7, "Color", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Color:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1, 1.2, "PrintText", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(true);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Text:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/DrawInCellClass.sdf").documentElement());
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
			addProperty("Color", "BackgroundColor", QString::fromUtf8("blue"), QObject::tr("Color"), QObject::tr(""), false);
			addProperty("Evaluate", "bool", QString::fromUtf8("false"), QObject::tr("Evaluate"), QObject::tr(""), false);
			addProperty("PrintText", "string", QObject::tr(""), QObject::tr("Text"), QObject::tr(""), false);
		}
	};

	class EngineCommand : public qReal::NodeElementType
	{
	public:
		explicit EngineCommand(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("EngineCommand");
			setFriendlyName(QObject::tr("EngineCommand"));
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

	class EngineMovementCommand : public qReal::NodeElementType
	{
	public:
		explicit EngineMovementCommand(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("EngineMovementCommand");
			setFriendlyName(QObject::tr("EngineMovementCommand"));
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
			addProperty("Power", "string", QObject::tr("100"), QObject::tr("Power (%)"), QObject::tr(""), false);
		}
	};

	class FiBlock : public qReal::NodeElementType
	{
	public:
		explicit FiBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("FiBlock");
			setFriendlyName(QObject::tr("End if"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Unites control flow from different condition branches."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/FiBlockClass.sdf").documentElement());
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

	class FinalNode : public qReal::NodeElementType
	{
	public:
		explicit FinalNode(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("FinalNode");
			setFriendlyName(QObject::tr("Final Node"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("The final node of the program. If the program consists of some parallel execution lines the reachment of this block terminates the corresponding execution line. This block can`t have outgoing links."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/FinalNodeClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("13, 200 : 198, 15 :  | 12, 12 : 198, 198 : ");
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

	class Fork : public qReal::NodeElementType
	{
	public:
		explicit Fork(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Fork");
			setFriendlyName(QObject::tr("Fork"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Separates program execution into a number of threads that will be executed concurrently from the programmers`s point of view. For example in such way signal from sensor and some time interval can be waited synchroniously. This block must have at least two outgoing links. 'Guard' property of every link must contain unique thread identifiers, and one of those identifiers must be the same as the identifier of a thread where fork is placed (it must be 'main' if it is the first fork in a program."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/ForkClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("13, 86 : 231, 86 :  | 12, 12 : 231, 12 : ");
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

	class Function : public qReal::NodeElementType
	{
	public:
		explicit Function(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Function");
			setFriendlyName(QObject::tr("Expression"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Evaluates a value of the given expression. Also new variables can be defined in this block. See the 'Expressions Syntax' chapter in help for more information about 'Function' block syntax."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, 1.2, "Body", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Expression:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/FunctionClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("58, 12 : 58, 172 :  | 58, 12 : 148, 12 :  | 12, 96 : 108, 96 "
			": ");
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
			addProperty("Body", "string", QObject::tr(""), QObject::tr("Expression"), QObject::tr(""), false);
		}
	};

	class GetButtonCode : public qReal::NodeElementType
	{
	public:
		explicit GetButtonCode(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("GetButtonCode");
			setFriendlyName(QObject::tr("Get Button Code"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Assigns a given variable a value of pressed button. If no button is pressed at the moment and 'Wait' property is false when variable is set to -1."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, 1.2, "Variable", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.6, 1.8, "Wait", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(true);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Wait:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/GetButtonCodeClass.sdf").documentElement());
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
			addProperty("Variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
			addProperty("Wait", "bool", QString::fromUtf8("true"), QObject::tr("Wait"), QObject::tr(""), false);
		}
	};

	class IfBlock : public qReal::NodeElementType
	{
	public:
		explicit IfBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("IfBlock");
			setFriendlyName(QObject::tr("Condition"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Separates program execution in correspondece with the given condition. The 'Condition' parameter value must be some boolean expression that will determine subsequent program execution line. This block must have two outgoing links, at least one of them must have 'Guard' parameter set to 'true' or 'false'. The execution will be proceed trough the link marked with the guard corresponding to 'Condition' parameter of the block."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, 1.2, "Condition", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Condition:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/IfBlockClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("96, 182 : 180, 94 :  | 98, 12 : 180, 94 :  | 12, 98 : 96, 182"
			" :  | 98, 12 : 12, 98 : ");
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
			addProperty("Condition", "string", QObject::tr("x > 0"), QObject::tr("Condition"), QObject::tr(""), false);
		}
	};

	class InitialNode : public qReal::NodeElementType
	{
	public:
		explicit InitialNode(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("InitialNode");
			setFriendlyName(QObject::tr("Initial Node"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("The entry point of the program execution. Each diagram should have only one such block, it must not have incomming links and it must have only one outgoing link. The interpretation process starts from exactly this block."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/InitialNodeClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("210, 111 : 209, 120 : 208, 130 : 205, 139 : 202, 148 : 198, 1"
			"57 : 193, 166 : 187, 173 : 181, 181 : 173, 187 : 166, 193 : 157, 198 : 148, 202 "
			": 139, 205 : 130, 208 : 120, 209 : 111, 209 : 102, 209 : 92, 208 : 83, 205 : 74,"
			" 202 : 65, 198 : 56, 193 : 49, 187 : 41, 181 : 35, 173 : 29, 166 : 24, 157 : 20,"
			" 148 : 17, 139 : 14, 130 : 13, 120 : 13, 111 : 13, 102 : 14, 92 : 17, 83 : 20, 7"
			"4 : 24, 65 : 29, 56 : 35, 49 : 41, 41 : 49, 35 : 56, 29 : 65, 24 : 74, 20 : 83, "
			"17 : 92, 14 : 102, 13 : 111, 13 : 120, 13 : 130, 14 : 139, 17 : 148, 20 : 157, 2"
			"4 : 166, 29 : 173, 35 : 181, 41 : 187, 49 : 193, 56 : 198, 65 : 202, 74 : 205, 8"
			"3 : 208, 92 : 209, 102 : 210, 111 : ");
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

	class Input : public qReal::NodeElementType
	{
	public:
		explicit Input(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Input");
			setFriendlyName(QObject::tr("User Input"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Reads a value into variable from an input dialog."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.66, 1.2, "variable", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.66, 1.8, "default", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Default:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.66, 2.4, "prompt", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Text:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/InputClass.sdf").documentElement());
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
			addProperty("default", "string", QObject::tr(""), QObject::tr("Default"), QObject::tr(""), false);
			addProperty("prompt", "string", QObject::tr(""), QObject::tr("Text"), QObject::tr(""), false);
			addProperty("variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class Join : public qReal::NodeElementType
	{
	public:
		explicit Join(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Join");
			setFriendlyName(QObject::tr("Join"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Joins a number of threads into one. 'Guard' property of the single outgoing link must contain an identifier of one of threads being joined. The specified thread would wait until the rest of them finish execution, and then proceed in a normal way."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/JoinClass.sdf").documentElement());
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

	class KillThread : public qReal::NodeElementType
	{
	public:
		explicit KillThread(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("KillThread");
			setFriendlyName(QObject::tr("Kill Thread"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Terminates execution of a specified thread."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, 1.2, "Thread", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Thread:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/KillThreadClass.sdf").documentElement());
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
			addProperty("Thread", "string", QObject::tr("main"), QObject::tr("Thread"), QObject::tr(""), false);
		}
	};

	class Loop : public qReal::NodeElementType
	{
	public:
		explicit Loop(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Loop");
			setFriendlyName(QObject::tr("Loop"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("This block executes a sequence of blocks for a given number of times. The number of repetitions is specified by the 'Iterations' parameter. This block must have two outgoing links. One of them must be marked with the 'body' guard (that means that the property 'Guard' of the link must be set to 'body' value). Another outgoing link must be unmarked: the program execution will be proceeded through this link when it will go through our 'Loop' block for the given number of times."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Iterations", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Iterations:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/LoopClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("154, 251 : 205, 302 :  | 154, 251 : 209, 196 :  | 100, 12 : 1"
			"54, 66 :  | 154, 66 : 103, 117 :  | 12, 66 : 297, 66 : 297, 251 : 12, 251 : 12, "
			"66 : ");
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
			addProperty("Iterations", "string", QObject::tr("10"), QObject::tr("Iterations"), QObject::tr(""), false);
		}
	};

	class MarkerDown : public qReal::NodeElementType
	{
	public:
		explicit MarkerDown(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("MarkerDown");
			setFriendlyName(QObject::tr("Marker Down"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Moves the marker of the 2D model robot down to the floor: the robot will draw its trace on the floor after that. If the marker of another color is already drawing at the moment it will be replaced."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.54, -0.7, "Color", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Color:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/MarkerDownClass.sdf").documentElement());
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
			addProperty("Color", "BackgroundColor", QString::fromUtf8("blue"), QObject::tr("Color"), QObject::tr(""), false);
		}
	};

	class MarkerUp : public qReal::NodeElementType
	{
	public:
		explicit MarkerUp(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("MarkerUp");
			setFriendlyName(QObject::tr("Marker Up"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Lifts the marker of the 2D model robot up: the robot stops drawing its trace on the floor after that."));
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/MarkerUpClass.sdf").documentElement());
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

	class PreconditionalLoop : public qReal::NodeElementType
	{
	public:
		explicit PreconditionalLoop(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PreconditionalLoop");
			setFriendlyName(QObject::tr("Pre-conditional Loop"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("This block executes a sequence of blocks while condition in 'Condition' is true. This block must have two outgoing links. One of them must be marked with the 'body' guard (that means that the property 'Guard' of the link must be set to 'body' value). Another outgoing link must be unmarked: the program execution will be proceeded through this link when condition becomes false."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.8, -0.7, "Condition", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Condition:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PreconditionalLoopClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("0, 0 : 50, 300 : 100, 150 : 150, 300 : 200, 0");
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
			addProperty("Condition", "string", QObject::tr("x > 0"), QObject::tr("Condition"), QObject::tr(""), false);
		}
	};

	class PrintText : public qReal::NodeElementType
	{
	public:
		explicit PrintText(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("PrintText");
			setFriendlyName(QObject::tr("Print Text"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Prints a given line in the specified coordinates on the robot`s screen. The value of 'Text' property is interpreted as a plain text unless 'Evaluate' property is set to true, then it will be interpreted as an expression (that may be useful for example when debugging variables values)."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 1, 1.2, "XCoordinateText", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("X:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 1, 1.8, "YCoordinateText", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Y:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 1, 2.4, "PrintText", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("Text:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/PrintTextClass.sdf").documentElement());
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
			addProperty("Redraw", "bool", QString::fromUtf8("true"), QObject::tr("Redraw"), QObject::tr(""), false);
			addProperty("XCoordinateText", "string", QObject::tr("1"), QObject::tr("X"), QObject::tr(""), false);
			addProperty("YCoordinateText", "string", QObject::tr("1"), QObject::tr("Y"), QObject::tr(""), false);
		}
	};

	class Randomizer : public qReal::NodeElementType
	{
	public:
		explicit Randomizer(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Randomizer");
			setFriendlyName(QObject::tr("Random Initialization"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sets a variable value to a random value inside given interval."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, 1.2, "Variable", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.6, 1.8, "LowerBound", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("From:"));
			addLabel(label_2);
			QSharedPointer<qReal::LabelProperties> label_3(new qReal::LabelProperties(3, 0.6, 2.4, "UpperBound", false, 0));
			label_3->setBackground(Qt::white);
			label_3->setScalingX(false);
			label_3->setScalingY(false);
			label_3->setHard(false);
			label_3->setPlainTextMode(false);
			label_3->setPrefix(QObject::tr("To:"));
			addLabel(label_3);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/RandomizerClass.sdf").documentElement());
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
			addProperty("LowerBound", "string", QObject::tr("0"), QObject::tr("From"), QObject::tr(""), false);
			addProperty("UpperBound", "string", QObject::tr("10"), QObject::tr("To"), QObject::tr(""), false);
			addProperty("Variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

	class ReceiveMessageThreads : public qReal::NodeElementType
	{
	public:
		explicit ReceiveMessageThreads(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("ReceiveMessageThreads");
			setFriendlyName(QObject::tr("Receive Message From Thread"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Receive a message sent to a thread from which this block is called."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, 1.2, "Variable", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.6, 1.8, "Synchronized", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Synchronized:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/ReceiveMessageThreadsClass.sdf").documentElement());
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

	class RobotsDiagramGroup : public qReal::PatternType
	{
	public:
		explicit RobotsDiagramGroup(qReal::Metamodel &metamodel)
			: PatternType(metamodel)
		{
			setName("RobotsDiagramGroup");
			setFriendlyName(QObject::tr("RobotsDiagramGroup"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			setXml(QString::fromUtf8(" <group rootNode=\"diagram\" name=\"RobotsDiagramGroup\">\n  <groupNode type=\"RobotsDiagramNode\" name=\"diagram\" xPosition=\"0\" yPosition=\"0\"/>\n  <groupNode type=\"InitialNode\" parent=\"diagram\" name=\"initialNode\" xPosition=\"50\" yPosition=\"300\"/>\n </group>\n"));
		}

	};

	class RobotsDiagramNode : public qReal::NodeElementType
	{
	public:
		explicit RobotsDiagramNode(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("RobotsDiagramNode");
			setFriendlyName(QObject::tr("Robot`s Behaviour Diagram"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.205882, 0.0588235, "name", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/RobotsDiagramNodeClass.sdf").documentElement());
			setSize(QSizeF(204, 204));
			initProperties();
			setMouseGesture("");
			addPointPort(qReal::PointPortInfo(QPointF(0.00980392, 0.5), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.5, 0.00980392), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.990196, 0.5), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.5, 0.990196), false, false, 204, 204, "NonTyped"));
			setResizable(true);
			setContainer(true);
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
			addProperty("devicesConfiguration", "string", QObject::tr(""), QObject::tr("Devices configuration"), QObject::tr(""), false);
		}
	};

	class SendMessageThreads : public qReal::NodeElementType
	{
	public:
		explicit SendMessageThreads(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("SendMessageThreads");
			setFriendlyName(QObject::tr("Send Message To Thread"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Sends a message to a specified thread."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, 1.2, "Thread", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Thread:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.6, 1.8, "Message", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Message:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/SendMessageThreadsClass.sdf").documentElement());
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
			addProperty("Message", "string", QObject::tr(""), QObject::tr("Message"), QObject::tr(""), false);
			addProperty("Thread", "string", QObject::tr(""), QObject::tr("Thread"), QObject::tr(""), false);
		}
	};

	class Subprogram : public qReal::NodeElementType
	{
	public:
		explicit Subprogram(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Subprogram");
			setFriendlyName(QObject::tr("Subprogram"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Subprogram call. Subprograms are used for splitting repetitive program parts into a separate diagram and then calling it from main diagram or other subprograms. When this block is added into a diagram it will be suggested to enter subprogram name. The double click on subprogram call block may open the corresponding subprogram diagram. Moreover user palette will appear containing existing subrpograms, they can be dragged into a diagram like the usual blocks."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, -0.4, -0.7, "name", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/SubprogramClass.sdf").documentElement());
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

	class SubprogramDiagram : public qReal::NodeElementType
	{
	public:
		explicit SubprogramDiagram(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("SubprogramDiagram");
			setFriendlyName(QObject::tr("Subprogram Diagram"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.205882, 0.0588235, "name", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/SubprogramDiagramClass.sdf").documentElement());
			setSize(QSizeF(204, 204));
			initProperties();
			setMouseGesture("");
			addPointPort(qReal::PointPortInfo(QPointF(0.00980392, 0.5), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.5, 0.00980392), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.990196, 0.5), false, false, 204, 204, "NonTyped"));
			addPointPort(qReal::PointPortInfo(QPointF(0.5, 0.990196), false, false, 204, 204, "NonTyped"));
			setResizable(true);
			setContainer(true);
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

	class SubprogramDiagramGroup : public qReal::PatternType
	{
	public:
		explicit SubprogramDiagramGroup(qReal::Metamodel &metamodel)
			: PatternType(metamodel)
		{
			setName("SubprogramDiagramGroup");
			setFriendlyName(QObject::tr("SubprogramDiagramGroup"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr(""));
			setXml(QString::fromUtf8(" <group rootNode=\"diagram\" name=\"SubprogramDiagramGroup\">\n  <groupNode type=\"SubprogramDiagram\" name=\"diagram\" xPosition=\"0\" yPosition=\"0\"/>\n  <groupNode type=\"InitialNode\" parent=\"diagram\" name=\"initialNode\" xPosition=\"50\" yPosition=\"300\"/>\n </group>\n"));
		}

	};

	class SwitchBlock : public qReal::NodeElementType
	{
	public:
		explicit SwitchBlock(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("SwitchBlock");
			setFriendlyName(QObject::tr("Switch"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Selects the program execution branch in correspondence with some expression value. The value of the expression written in 'Expression' property is compared to the values on the outgoing links. If equal value is found then execution will be proceeded by that branch. Else branch without a marker will be selected."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 1, 1.2, "Expression", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Expression:"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/SwitchBlockClass.sdf").documentElement());
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
			addProperty("Expression", "string", QObject::tr("x"), QObject::tr("Expression"), QObject::tr(""), false);
		}
	};

	class Timer : public qReal::NodeElementType
	{
	public:
		explicit Timer(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("Timer");
			setFriendlyName(QObject::tr("Timer"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Waits for a given time in milliseconds."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.6, -0.7, "Delay", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(true);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Delay:"));
			label_1->setSuffix(QObject::tr("ms"));
			addLabel(label_1);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/TimerClass.sdf").documentElement());
			setSize(QSizeF(50, 50));
			initProperties();
			setMouseGesture("12, 117 : 117, 118 :  | 117, 12 : 117, 118 :  | 222, 117 : 22"
			"1, 127 : 219, 137 : 217, 147 : 214, 157 : 209, 166 : 204, 175 : 198, 183 : 191, "
			"191 : 183, 198 : 175, 204 : 166, 209 : 157, 214 : 147, 217 : 137, 219 : 127, 221"
			" : 117, 221 : 107, 221 : 97, 219 : 87, 217 : 77, 214 : 68, 209 : 59, 204 : 51, 1"
			"98 : 43, 191 : 36, 183 : 30, 175 : 25, 166 : 20, 157 : 17, 147 : 15, 137 : 13, 1"
			"27 : 13, 117 : 13, 107 : 15, 97 : 17, 87 : 20, 77 : 25, 68 : 30, 59 : 36, 51 : 4"
			"3, 43 : 51, 36 : 59, 30 : 68, 25 : 77, 20 : 87, 17 : 97, 15 : 107, 13 : 117, 13 "
			": 127, 13 : 137, 15 : 147, 17 : 157, 20 : 166, 25 : 175, 30 : 183, 36 : 191, 43 "
			": 198, 51 : 204, 59 : 209, 68 : 214, 77 : 217, 87 : 219, 97 : 221, 107 : 222, 11"
			"7 : ");
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
			addProperty("Delay", "string", QObject::tr("1000"), QObject::tr("Delay (ms)"), QObject::tr(""), false);
		}
	};

	class VariableInit : public qReal::NodeElementType
	{
	public:
		explicit VariableInit(qReal::Metamodel &metamodel)
			: NodeElementType(metamodel)
		{
			setName("VariableInit");
			setFriendlyName(QObject::tr("Variable Initialization"));
			setDiagram("RobotsDiagram");
			setDescription(QObject::tr("Assigns a given value to a given variable."));
			QSharedPointer<qReal::LabelProperties> label_1(new qReal::LabelProperties(1, 0.66, 1.2, "variable", false, 0));
			label_1->setBackground(Qt::white);
			label_1->setScalingX(false);
			label_1->setScalingY(false);
			label_1->setHard(false);
			label_1->setPlainTextMode(false);
			label_1->setPrefix(QObject::tr("Variable:"));
			addLabel(label_1);
			QSharedPointer<qReal::LabelProperties> label_2(new qReal::LabelProperties(2, 0.66, 1.8, "value", false, 0));
			label_2->setBackground(Qt::white);
			label_2->setScalingX(false);
			label_2->setScalingY(false);
			label_2->setHard(false);
			label_2->setPlainTextMode(false);
			label_2->setPrefix(QObject::tr("Value:"));
			addLabel(label_2);
			loadSdf(utils::xmlUtils::loadDocument(":/generated/shapes/VariableInitClass.sdf").documentElement());
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
			addProperty("value", "string", QObject::tr("0"), QObject::tr("Value"), QObject::tr(""), false);
			addProperty("variable", "string", QObject::tr("x"), QObject::tr("Variable"), QObject::tr(""), false);
		}
	};

