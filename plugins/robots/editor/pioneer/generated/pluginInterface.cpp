// ----------------------------------------------------------------------- //
// This file is auto-generated with qrxc v1.1. Do not modify its contents
// or prepare to lose your edits. If you want to change something in it
// consider editing language metamodel instead.
// ----------------------------------------------------------------------- //

#include "pluginInterface.h"

#include "elements.h"

PioneerMetamodelPlugin::PioneerMetamodelPlugin()
	: mMetamodel(nullptr){
}

QStringList PioneerMetamodelPlugin::dependencies() const
{
	return {"RobotsMetamodel"};
}

void PioneerMetamodelPlugin::load(qReal::Metamodel &metamodel)
{
	mMetamodel = &metamodel;
	initPlugin();
}

void PioneerMetamodelPlugin::initPlugin()
{
	if (mMetamodel->id().isEmpty()) {
		mMetamodel->setId("PioneerMetamodel");
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

void PioneerMetamodelPlugin::initMultigraph()
{
	mMetamodel->addNode(new GeoLanding(*mMetamodel));
	mMetamodel->addNode(new GeoTakeoff(*mMetamodel));
	mMetamodel->addNode(new GoToGPSPoint(*mMetamodel));
	mMetamodel->addNode(new GoToPoint(*mMetamodel));
	mMetamodel->addNode(new PioneerGetLPSPosition(*mMetamodel));
	mMetamodel->addNode(new PioneerLed(*mMetamodel));
	mMetamodel->addNode(new PioneerMagnet(*mMetamodel));
	mMetamodel->addNode(new PioneerPrint(*mMetamodel));
	mMetamodel->addNode(new PioneerReadRangeSensor(*mMetamodel));
	mMetamodel->addNode(new PioneerSystem(*mMetamodel));
	mMetamodel->addNode(new PioneerYaw(*mMetamodel));
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "GeoLanding"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "GeoTakeoff"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "GoToGPSPoint"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "GoToPoint"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerGetLPSPosition"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerLed"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerMagnet"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerPrint"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerReadRangeSensor"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerSystem"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "PioneerYaw"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
}

void PioneerMetamodelPlugin::initNameMap()
{
	mMetamodel->addDiagram("RobotsDiagram");
	mMetamodel->setDiagramFriendlyName("RobotsDiagram", QObject::tr("RobotsDiagram"));
	mMetamodel->setDiagramNode("RobotsDiagram", "");

}

void PioneerMetamodelPlugin::initPaletteGroupsMap()
{
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("GeoTakeoff"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("GeoLanding"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("GoToPoint"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("PioneerGetLPSPosition"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("PioneerLed"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("PioneerMagnet"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("PioneerSystem"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("PioneerYaw"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("PioneerReadRangeSensor"));
}

void PioneerMetamodelPlugin::initPaletteGroupsDescriptionMap()
{
}

void PioneerMetamodelPlugin::initShallPaletteBeSortedMap()
{
	mMetamodel->setPaletteSorted(QString::fromUtf8("RobotsDiagram"), false);
}

void PioneerMetamodelPlugin::initEnums()
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

