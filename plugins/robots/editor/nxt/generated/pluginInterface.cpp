// ----------------------------------------------------------------------- //
// This file is auto-generated with qrxc v1.1. Do not modify its contents
// or prepare to lose your edits. If you want to change something in it
// consider editing language metamodel instead.
// ----------------------------------------------------------------------- //

#include "pluginInterface.h"

#include "elements.h"

NxtMetamodelPlugin::NxtMetamodelPlugin()
	: mMetamodel(nullptr){
}

QStringList NxtMetamodelPlugin::dependencies() const
{
	return {"RobotsMetamodel"};
}

void NxtMetamodelPlugin::load(qReal::Metamodel &metamodel)
{
	mMetamodel = &metamodel;
	initPlugin();
}

void NxtMetamodelPlugin::initPlugin()
{
	if (mMetamodel->id().isEmpty()) {
		mMetamodel->setId("NxtMetamodel");
	}
	if (mMetamodel->version().isEmpty()) {
		mMetamodel->setVersion("");
	}

	initMultigraph();
	initNameMap();
	initEnums();
	initPaletteGroupsMap();
	initPaletteGroupsDescriptionMap();
	initShallPaletteBeSortedMap();
}

void NxtMetamodelPlugin::initMultigraph()
{
	mMetamodel->addNode(*(new NxtBeep(*mMetamodel)));
	mMetamodel->addNode(*(new NxtClearEncoder(*mMetamodel)));
	mMetamodel->addNode(*(new NxtDrawCircle(*mMetamodel)));
	mMetamodel->addNode(*(new NxtDrawLine(*mMetamodel)));
	mMetamodel->addNode(*(new NxtDrawPixel(*mMetamodel)));
	mMetamodel->addNode(*(new NxtDrawRect(*mMetamodel)));
	mMetamodel->addNode(*(new NxtEngineMovementCommand(*mMetamodel)));
	mMetamodel->addNode(*(new NxtEnginesBackward(*mMetamodel)));
	mMetamodel->addNode(*(new NxtEnginesForward(*mMetamodel)));
	mMetamodel->addNode(*(new NxtEnginesStop(*mMetamodel)));
	mMetamodel->addNode(*(new NxtPlayTone(*mMetamodel)));
	mMetamodel->addNode(*(new NxtSensorBlock(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForButton(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForColor(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForColorIntensity(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForEncoder(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForLight(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForSonarDistance(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForSound(*mMetamodel)));
	mMetamodel->addNode(*(new NxtWaitForTouchSensor(*mMetamodel)));
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtEnginesBackward"), mMetamodel->elementType("RobotsDiagram", "NxtEngineMovementCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtEnginesForward"), mMetamodel->elementType("RobotsDiagram", "NxtEngineMovementCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtEnginesStop"), mMetamodel->elementType("RobotsDiagram", "EngineCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtWaitForColor"), mMetamodel->elementType("RobotsDiagram", "NxtSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtWaitForColorIntensity"), mMetamodel->elementType("RobotsDiagram", "NxtSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtWaitForLight"), mMetamodel->elementType("RobotsDiagram", "NxtSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtWaitForSonarDistance"), mMetamodel->elementType("RobotsDiagram", "NxtSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtWaitForSound"), mMetamodel->elementType("RobotsDiagram", "NxtSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "NxtWaitForTouchSensor"), mMetamodel->elementType("RobotsDiagram", "NxtSensorBlock"), qReal::ElementType::generalizationLinkType);
}

void NxtMetamodelPlugin::initNameMap()
{
	mMetamodel->addDiagram("RobotsDiagram");
	mMetamodel->setDiagramFriendlyName("RobotsDiagram", QObject::tr("RobotsDiagram"));
	mMetamodel->setDiagramNode("RobotsDiagram", "");

}

void NxtMetamodelPlugin::initPaletteGroupsMap()
{
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("NxtBeep"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("NxtPlayTone"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("NxtEnginesForward"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("NxtEnginesBackward"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("NxtEnginesStop"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("NxtClearEncoder"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForTouchSensor"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForSonarDistance"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForColor"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForEncoder"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForColorIntensity"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForLight"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForSound"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("NxtWaitForButton"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("NxtDrawRect"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("NxtDrawPixel"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("NxtDrawLine"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("NxtDrawCircle"));
}

void NxtMetamodelPlugin::initPaletteGroupsDescriptionMap()
{
}

void NxtMetamodelPlugin::initShallPaletteBeSortedMap()
{
	mMetamodel->setPaletteSorted(QString::fromUtf8("RobotsDiagram"), false);
}

void NxtMetamodelPlugin::initEnums()
{
	mMetamodel->addEnum("VisibilityKind", { qMakePair(QString("package"), tr("Package")), qMakePair(QString("private"), tr("Private")), qMakePair(QString("protected"), tr("Protected")), qMakePair(QString("public"), tr("Public")) });
	mMetamodel->setEnumEditable("VisibilityKind", false);
	mMetamodel->addEnum("DistanceSign", { qMakePair(QString("greater"), tr("greater")), qMakePair(QString("less"), tr("less")), qMakePair(QString("notGreater"), tr("not greater")), qMakePair(QString("notLess"), tr("not less")) });
	mMetamodel->setEnumEditable("DistanceSign", false);
	mMetamodel->addEnum("AggregationKind", { qMakePair(QString("composite"), tr("Composite")), qMakePair(QString("none"), tr("None")), qMakePair(QString("shared"), tr("Shared")) });
	mMetamodel->setEnumEditable("AggregationKind", false);
	mMetamodel->addEnum("CallConcurrencyKind", { qMakePair(QString("concurrent"), tr("Concurrent")), qMakePair(QString("guarded"), tr("Guarded")), qMakePair(QString("sequential"), tr("Sequential")) });
	mMetamodel->setEnumEditable("CallConcurrencyKind", false);
	mMetamodel->addEnum("Accelerations", { qMakePair(QString("normal"), tr("norm")), qMakePair(QString("xAxis"), tr("x-axis")), qMakePair(QString("yAxis"), tr("y-axis")), qMakePair(QString("zAxis"), tr("z-axis")) });
	mMetamodel->setEnumEditable("Accelerations", false);
	mMetamodel->addEnum("BreakEngineMode", { qMakePair(QString("break"), tr("break")), qMakePair(QString("float"), tr("float")) });
	mMetamodel->setEnumEditable("BreakEngineMode", false);
	mMetamodel->addEnum("NxtSensorPort", { qMakePair(QString("1"), tr("1")), qMakePair(QString("2"), tr("2")), qMakePair(QString("3"), tr("3")), qMakePair(QString("4"), tr("4")) });
	mMetamodel->setEnumEditable("NxtSensorPort", false);
	mMetamodel->addEnum("NxtButtons", { qMakePair(QString("Enter"), tr("Enter")), qMakePair(QString("Escape"), tr("Escape")), qMakePair(QString("Left"), tr("Left")), qMakePair(QString("Right"), tr("Right")) });
	mMetamodel->setEnumEditable("NxtButtons", false);
	mMetamodel->addEnum("ParameterDirectionKind", { qMakePair(QString("in"), tr("In")), qMakePair(QString("inout"), tr("Inout")), qMakePair(QString("out"), tr("Out")), qMakePair(QString("return"), tr("Return")) });
	mMetamodel->setEnumEditable("ParameterDirectionKind", false);
	mMetamodel->addEnum("GuardType", { qMakePair(QString("false"), tr("false")), qMakePair(QString("iteration"), tr("body")), qMakePair(QString("true"), tr("true")) });
	mMetamodel->setEnumEditable("GuardType", true);
	mMetamodel->addEnum("Color", { qMakePair(QString("black"), tr("black")), qMakePair(QString("blue"), tr("blue")), qMakePair(QString("green"), tr("green")), qMakePair(QString("red"), tr("red")), qMakePair(QString("white"), tr("white")), qMakePair(QString("yellow"), tr("yellow")) });
	mMetamodel->setEnumEditable("Color", false);
	mMetamodel->addEnum("bool", { qMakePair(QString("false"), tr("false")), qMakePair(QString("true"), tr("true")) });
	mMetamodel->setEnumEditable("bool", false);
}

