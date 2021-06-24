// ----------------------------------------------------------------------- //
// This file is auto-generated with qrxc v1.1. Do not modify its contents
// or prepare to lose your edits. If you want to change something in it
// consider editing language metamodel instead.
// ----------------------------------------------------------------------- //

#include "pluginInterface.h"

#include "elements.h"

RobotsMetamodelPlugin::RobotsMetamodelPlugin()
	: mMetamodel(nullptr){
}

QStringList RobotsMetamodelPlugin::dependencies() const
{
	return {};
}

void RobotsMetamodelPlugin::load(qReal::Metamodel &metamodel)
{
	mMetamodel = &metamodel;
	initPlugin();
}

void RobotsMetamodelPlugin::initPlugin()
{
	if (mMetamodel->id().isEmpty()) {
		mMetamodel->setId("RobotsMetamodel");
	}
	if (mMetamodel->version().isEmpty()) {
		mMetamodel->setVersion("2020.4.1");
	}

	initMultigraph();
	initNameMap();
	initEnums();
	initPaletteGroupsMap();
	initPaletteGroupsDescriptionMap();
	initShallPaletteBeSortedMap();
}

void RobotsMetamodelPlugin::initMultigraph()
{
	mMetamodel->addNode(new AbstractNode(*mMetamodel));
	mMetamodel->addNode(new BlackBox(*mMetamodel));
	mMetamodel->addNode(new BlackBoxDiagram(*mMetamodel));
	mMetamodel->addNode(new BlackBoxDiagramGroup(*mMetamodel));
	mMetamodel->addNode(new ClearScreen(*mMetamodel));
	mMetamodel->addNode(new CommentBlock(*mMetamodel));
	mMetamodel->addNode(new ControlFlow(*mMetamodel));
	mMetamodel->addNode(new DrawInCell(*mMetamodel));
	mMetamodel->addNode(new EngineCommand(*mMetamodel));
	mMetamodel->addNode(new EngineMovementCommand(*mMetamodel));
	mMetamodel->addNode(new FiBlock(*mMetamodel));
	mMetamodel->addNode(new FinalNode(*mMetamodel));
	mMetamodel->addNode(new Fork(*mMetamodel));
	mMetamodel->addNode(new Function(*mMetamodel));
	mMetamodel->addNode(new GetButtonCode(*mMetamodel));
	mMetamodel->addNode(new IfBlock(*mMetamodel));
	mMetamodel->addNode(new InitialNode(*mMetamodel));
	mMetamodel->addNode(new Input(*mMetamodel));
	mMetamodel->addNode(new Join(*mMetamodel));
	mMetamodel->addNode(new KillThread(*mMetamodel));
	mMetamodel->addNode(new Loop(*mMetamodel));
	mMetamodel->addNode(new MarkerDown(*mMetamodel));
	mMetamodel->addNode(new MarkerUp(*mMetamodel));
	mMetamodel->addNode(new PreconditionalLoop(*mMetamodel));
	mMetamodel->addNode(new PrintText(*mMetamodel));
	mMetamodel->addNode(new Randomizer(*mMetamodel));
	mMetamodel->addNode(new ReceiveMessageThreads(*mMetamodel));
	mMetamodel->addNode(new RobotsDiagramGroup(*mMetamodel));
	mMetamodel->addNode(new RobotsDiagramNode(*mMetamodel));
	mMetamodel->addNode(new SendMessageThreads(*mMetamodel));
	mMetamodel->addNode(new Subprogram(*mMetamodel));
	mMetamodel->addNode(new SubprogramDiagram(*mMetamodel));
	mMetamodel->addNode(new SubprogramDiagramGroup(*mMetamodel));
	mMetamodel->addNode(new SwitchBlock(*mMetamodel));
	mMetamodel->addNode(new Timer(*mMetamodel));
	mMetamodel->addNode(new VariableInit(*mMetamodel));
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "BlackBox"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->addExplosion(mMetamodel->elementType("RobotsDiagram", "BlackBox"), mMetamodel->elementType("RobotsDiagram", "BlackBoxDiagramGroup"), true, true);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "BlackBoxDiagram"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::containmentLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "ClearScreen"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "CommentBlock"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "DrawInCell"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "EngineCommand"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "EngineMovementCommand"), mMetamodel->elementType("RobotsDiagram", "EngineCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "FiBlock"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "FinalNode"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Fork"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Function"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "GetButtonCode"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "IfBlock"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "InitialNode"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Input"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Join"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "KillThread"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Loop"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "MarkerDown"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "MarkerUp"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PreconditionalLoop"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PrintText"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Randomizer"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "ReceiveMessageThreads"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "RobotsDiagramNode"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::containmentLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "SendMessageThreads"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Subprogram"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->addExplosion(mMetamodel->elementType("RobotsDiagram", "Subprogram"), mMetamodel->elementType("RobotsDiagram", "SubprogramDiagramGroup"), true, true);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "SubprogramDiagram"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::containmentLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "SwitchBlock"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "Timer"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "VariableInit"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
}

void RobotsMetamodelPlugin::initNameMap()
{
	mMetamodel->addDiagram("RobotsDiagram");
	mMetamodel->setDiagramFriendlyName("RobotsDiagram", QObject::tr("Robot`s Behaviour Diagram"));
	mMetamodel->setDiagramNode("RobotsDiagram", "RobotsDiagramGroup");

}

void RobotsMetamodelPlugin::initPaletteGroupsMap()
{
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("InitialNode"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("FinalNode"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("VariableInit"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("IfBlock"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("FiBlock"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("PreconditionalLoop"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("Loop"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("SwitchBlock"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("Function"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("Subprogram"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("BlackBox"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("Fork"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("Join"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("KillThread"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("Randomizer"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Algorithms"), QString::fromUtf8("CommentBlock"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("SendMessageThreads"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("GetButtonCode"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("Timer"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("ReceiveMessageThreads"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("Input"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("PrintText"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("ClearScreen"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("MarkerDown"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("MarkerUp"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("DrawInCell"));
}

void RobotsMetamodelPlugin::initPaletteGroupsDescriptionMap()
{
}

void RobotsMetamodelPlugin::initShallPaletteBeSortedMap()
{
	mMetamodel->setPaletteSorted(QString::fromUtf8("RobotsDiagram"), false);
}

void RobotsMetamodelPlugin::initEnums()
{
	mMetamodel->addEnum("Accelerations", { qMakePair(QString("normal"), tr("norm")), qMakePair(QString("xAxis"), tr("x-axis")), qMakePair(QString("yAxis"), tr("y-axis")), qMakePair(QString("zAxis"), tr("z-axis")) });
	mMetamodel->setEnumEditable("Accelerations", false);
	mMetamodel->addEnum("AggregationKind", { qMakePair(QString("composite"), tr("Composite")), qMakePair(QString("none"), tr("None")), qMakePair(QString("shared"), tr("Shared")) });
	mMetamodel->setEnumEditable("AggregationKind", false);
	mMetamodel->addEnum("BrakeEngineMode", { qMakePair(QString("brake"), tr("brake")), qMakePair(QString("float"), tr("float")) });
	mMetamodel->setEnumEditable("BrakeEngineMode", false);
	mMetamodel->addEnum("CallConcurrencyKind", { qMakePair(QString("concurrent"), tr("Concurrent")), qMakePair(QString("guarded"), tr("Guarded")), qMakePair(QString("sequential"), tr("Sequential")) });
	mMetamodel->setEnumEditable("CallConcurrencyKind", false);
	mMetamodel->addEnum("Color", { qMakePair(QString("black"), tr("black")), qMakePair(QString("blue"), tr("blue")), qMakePair(QString("green"), tr("green")), qMakePair(QString("red"), tr("red")), qMakePair(QString("white"), tr("white")), qMakePair(QString("yellow"), tr("yellow")) });
	mMetamodel->setEnumEditable("Color", false);
	mMetamodel->addEnum("DistanceSign", { qMakePair(QString("greater"), tr("greater")), qMakePair(QString("less"), tr("less")), qMakePair(QString("notGreater"), tr("not greater")), qMakePair(QString("notLess"), tr("not less")) });
	mMetamodel->setEnumEditable("DistanceSign", false);
	mMetamodel->addEnum("GuardType", { qMakePair(QString("false"), tr("false")), qMakePair(QString("iteration"), tr("body")), qMakePair(QString("true"), tr("true")) });
	mMetamodel->setEnumEditable("GuardType", true);
	mMetamodel->addEnum("ParameterDirectionKind", { qMakePair(QString("in"), tr("In")), qMakePair(QString("inout"), tr("Inout")), qMakePair(QString("out"), tr("Out")), qMakePair(QString("return"), tr("Return")) });
	mMetamodel->setEnumEditable("ParameterDirectionKind", false);
	mMetamodel->addEnum("VisibilityKind", { qMakePair(QString("package"), tr("Package")), qMakePair(QString("private"), tr("Private")), qMakePair(QString("protected"), tr("Protected")), qMakePair(QString("public"), tr("Public")) });
	mMetamodel->setEnumEditable("VisibilityKind", false);
	mMetamodel->addEnum("bool", { qMakePair(QString("false"), tr("false")), qMakePair(QString("true"), tr("true")) });
	mMetamodel->setEnumEditable("bool", false);
}

