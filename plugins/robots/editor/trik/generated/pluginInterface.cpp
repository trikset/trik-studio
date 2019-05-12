// ----------------------------------------------------------------------- //
// This file is auto-generated with qrxc v1.1. Do not modify its contents
// or prepare to lose your edits. If you want to change something in it
// consider editing language metamodel instead.
// ----------------------------------------------------------------------- //

#include "pluginInterface.h"

#include "elements.h"

TrikMetamodelPlugin::TrikMetamodelPlugin()
	: mMetamodel(nullptr){
}

QStringList TrikMetamodelPlugin::dependencies() const
{
	return {"RobotsMetamodel"};
}

void TrikMetamodelPlugin::load(qReal::Metamodel &metamodel)
{
	mMetamodel = &metamodel;
	initPlugin();
}

void TrikMetamodelPlugin::initPlugin()
{
	if (mMetamodel->id().isEmpty()) {
		mMetamodel->setId("TrikMetamodel");
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

void TrikMetamodelPlugin::initMultigraph()
{
	mMetamodel->addNode(*(new TrikAnalogSensorBlock(*mMetamodel)));
	mMetamodel->addNode(*(new TrikAngularServo(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDetect(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDetectorToVariable(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDigitalSensorBlock(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDrawArc(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDrawEllipse(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDrawLine(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDrawPixel(*mMetamodel)));
	mMetamodel->addNode(*(new TrikDrawRect(*mMetamodel)));
	mMetamodel->addNode(*(new TrikInitCamera(*mMetamodel)));
	mMetamodel->addNode(*(new TrikInitVideoStreaming(*mMetamodel)));
	mMetamodel->addNode(*(new TrikLed(*mMetamodel)));
	mMetamodel->addNode(*(new TrikPlayTone(*mMetamodel)));
	mMetamodel->addNode(*(new TrikPlayToneHz(*mMetamodel)));
	mMetamodel->addNode(*(new TrikRemoveFile(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSadSmile(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSay(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSendMessage(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSensorBlock(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSetBackground(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSetPainterColor(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSetPainterWidth(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSmile(*mMetamodel)));
	mMetamodel->addNode(*(new TrikStopCamera(*mMetamodel)));
	mMetamodel->addNode(*(new TrikStopVideoStreaming(*mMetamodel)));
	mMetamodel->addNode(*(new TrikSystem(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV62AngularServo(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV62ClearEncoder(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV62WaitForEncoder(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV6ClearEncoder(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV6EngineMovementCommand(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV6EnginesBackward(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV6EnginesForward(*mMetamodel)));
	mMetamodel->addNode(*(new TrikV6EnginesStop(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForAccelerometer(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForButton(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForEncoder(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForGyroscope(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForIRDistance(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForLight(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForMessage(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForMotion(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForSonarDistance(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitForTouchSensor(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitGamepadButton(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitGamepadConnect(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitGamepadDisconnect(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitGamepadWheel(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWaitPadPress(*mMetamodel)));
	mMetamodel->addNode(*(new TrikWriteToFile(*mMetamodel)));
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikAnalogSensorBlock"), mMetamodel->elementType("RobotsDiagram", "TrikSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikAngularServo"), mMetamodel->elementType("RobotsDiagram", "EngineCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDetect"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDetectorToVariable"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDigitalSensorBlock"), mMetamodel->elementType("RobotsDiagram", "TrikSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDrawArc"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDrawEllipse"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDrawLine"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDrawPixel"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikDrawRect"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikInitCamera"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikInitVideoStreaming"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikLed"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikPlayTone"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikPlayToneHz"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikRemoveFile"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSadSmile"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSay"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSendMessage"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSensorBlock"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSetBackground"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSetPainterColor"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSetPainterWidth"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSmile"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikStopCamera"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikStopVideoStreaming"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikSystem"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV62AngularServo"), mMetamodel->elementType("RobotsDiagram", "EngineCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV62ClearEncoder"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV62WaitForEncoder"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV6ClearEncoder"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV6EngineMovementCommand"), mMetamodel->elementType("RobotsDiagram", "EngineMovementCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV6EnginesBackward"), mMetamodel->elementType("RobotsDiagram", "TrikV6EngineMovementCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV6EnginesForward"), mMetamodel->elementType("RobotsDiagram", "TrikV6EngineMovementCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikV6EnginesStop"), mMetamodel->elementType("RobotsDiagram", "EngineCommand"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForAccelerometer"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForButton"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForEncoder"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForGyroscope"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForIRDistance"), mMetamodel->elementType("RobotsDiagram", "TrikAnalogSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForLight"), mMetamodel->elementType("RobotsDiagram", "TrikAnalogSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForMessage"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForMotion"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForSonarDistance"), mMetamodel->elementType("RobotsDiagram", "TrikDigitalSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitForTouchSensor"), mMetamodel->elementType("RobotsDiagram", "TrikAnalogSensorBlock"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitGamepadButton"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitGamepadConnect"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitGamepadDisconnect"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitGamepadWheel"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWaitPadPress"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
	mMetamodel->produceEdge(mMetamodel->elementType("RobotsDiagram", "TrikWriteToFile"), mMetamodel->elementType("RobotsDiagram", "AbstractNode"), qReal::ElementType::generalizationLinkType);
}

void TrikMetamodelPlugin::initNameMap()
{
	mMetamodel->addDiagram("RobotsDiagram");
	mMetamodel->setDiagramFriendlyName("RobotsDiagram", QObject::tr("RobotsDiagram"));
	mMetamodel->setDiagramNode("RobotsDiagram", "");

}

void TrikMetamodelPlugin::initPaletteGroupsMap()
{
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikPlayTone"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikPlayToneHz"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikV6EnginesForward"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikV6EnginesBackward"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikV6EnginesStop"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikV6ClearEncoder"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikV62ClearEncoder"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikAngularServo"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikV62AngularServo"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikSay"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikLed"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikSystem"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikInitCamera"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikStopCamera"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikDetect"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikDetectorToVariable"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikInitVideoStreaming"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikStopVideoStreaming"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikSendMessage"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikWriteToFile"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Actions"), QString::fromUtf8("TrikRemoveFile"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForTouchSensor"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForLight"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForSonarDistance"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForIRDistance"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForEncoder"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikV62WaitForEncoder"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForButton"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitForMessage"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitGamepadButton"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitPadPress"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitGamepadWheel"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitGamepadDisconnect"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Wait"), QString::fromUtf8("TrikWaitGamepadConnect"));
	mMetamodel->appendDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikSetPainterColor"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikSetPainterWidth"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikDrawPixel"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikDrawLine"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikDrawRect"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikDrawEllipse"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikDrawArc"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikSmile"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikSadSmile"));
	mMetamodel->addElementToDiagramPaletteGroup("RobotsDiagram", QObject::tr("Drawing"), QString::fromUtf8("TrikSetBackground"));
}

void TrikMetamodelPlugin::initPaletteGroupsDescriptionMap()
{
}

void TrikMetamodelPlugin::initShallPaletteBeSortedMap()
{
	mMetamodel->setPaletteSorted(QString::fromUtf8("RobotsDiagram"), false);
}

void TrikMetamodelPlugin::initEnums()
{
	mMetamodel->addEnum("Accelerations", { qMakePair(QString("normal"), tr("norm")), qMakePair(QString("xAxis"), tr("x-axis")), qMakePair(QString("yAxis"), tr("y-axis")), qMakePair(QString("zAxis"), tr("z-axis")) });
	mMetamodel->setEnumEditable("Accelerations", false);
	mMetamodel->addEnum("AggregationKind", { qMakePair(QString("composite"), tr("Composite")), qMakePair(QString("none"), tr("None")), qMakePair(QString("shared"), tr("Shared")) });
	mMetamodel->setEnumEditable("AggregationKind", false);
	mMetamodel->addEnum("BackgroundColor", { qMakePair(QString("black"), tr("black")), qMakePair(QString("blue"), tr("blue")), qMakePair(QString("cyan"), tr("cyan")), qMakePair(QString("darkBlue"), tr("dark blue")), qMakePair(QString("darkCyan"), tr("dark cyan")), qMakePair(QString("darkGray"), tr("dark gray")), qMakePair(QString("darkGreen"), tr("dark green")), qMakePair(QString("darkMagenta"), tr("dark magenta")), qMakePair(QString("darkRed"), tr("dark red")), qMakePair(QString("darkYellow"), tr("dark yellow")), qMakePair(QString("gray"), tr("gray")), qMakePair(QString("green"), tr("green")), qMakePair(QString("lightGray"), tr("light gray")), qMakePair(QString("magenta"), tr("magenta")), qMakePair(QString("red"), tr("red")), qMakePair(QString("white"), tr("white")), qMakePair(QString("yellow"), tr("yellow")) });
	mMetamodel->setEnumEditable("BackgroundColor", false);
	mMetamodel->addEnum("BreakEngineMode", { qMakePair(QString("break"), tr("break")), qMakePair(QString("float"), tr("float")) });
	mMetamodel->setEnumEditable("BreakEngineMode", false);
	mMetamodel->addEnum("CallConcurrencyKind", { qMakePair(QString("concurrent"), tr("Concurrent")), qMakePair(QString("guarded"), tr("Guarded")), qMakePair(QString("sequential"), tr("Sequential")) });
	mMetamodel->setEnumEditable("CallConcurrencyKind", false);
	mMetamodel->addEnum("Color", { qMakePair(QString("black"), tr("black")), qMakePair(QString("blue"), tr("blue")), qMakePair(QString("green"), tr("green")), qMakePair(QString("red"), tr("red")), qMakePair(QString("white"), tr("white")), qMakePair(QString("yellow"), tr("yellow")) });
	mMetamodel->setEnumEditable("Color", false);
	mMetamodel->addEnum("DetectableVideoSensor", { qMakePair(QString("line"), tr("Line sensor")), qMakePair(QString("object"), tr("Object sensor")) });
	mMetamodel->setEnumEditable("DetectableVideoSensor", false);
	mMetamodel->addEnum("DistanceSign", { qMakePair(QString("greater"), tr("greater")), qMakePair(QString("less"), tr("less")), qMakePair(QString("notGreater"), tr("not greater")), qMakePair(QString("notLess"), tr("not less")) });
	mMetamodel->setEnumEditable("DistanceSign", false);
	mMetamodel->addEnum("GuardType", { qMakePair(QString("false"), tr("false")), qMakePair(QString("iteration"), tr("body")), qMakePair(QString("true"), tr("true")) });
	mMetamodel->setEnumEditable("GuardType", true);
	mMetamodel->addEnum("JpgEncoderQuality", { qMakePair(QString("15"), tr("15")), qMakePair(QString("30"), tr("30")), qMakePair(QString("50"), tr("50")), qMakePair(QString("80"), tr("80")) });
	mMetamodel->setEnumEditable("JpgEncoderQuality", false);
	mMetamodel->addEnum("ParameterDirectionKind", { qMakePair(QString("in"), tr("In")), qMakePair(QString("inout"), tr("Inout")), qMakePair(QString("out"), tr("Out")), qMakePair(QString("return"), tr("Return")) });
	mMetamodel->setEnumEditable("ParameterDirectionKind", false);
	mMetamodel->addEnum("TrikButtons", { qMakePair(QString("Down"), tr("Down")), qMakePair(QString("Enter"), tr("Enter")), qMakePair(QString("Esc"), tr("Esc")), qMakePair(QString("Left"), tr("Left")), qMakePair(QString("Right"), tr("Right")), qMakePair(QString("Up"), tr("Up")) });
	mMetamodel->setEnumEditable("TrikButtons", false);
	mMetamodel->addEnum("TrikLedColor", { qMakePair(QString("green"), tr("green")), qMakePair(QString("off"), tr("off")), qMakePair(QString("orange"), tr("orange")), qMakePair(QString("red"), tr("red")) });
	mMetamodel->setEnumEditable("TrikLedColor", false);
	mMetamodel->addEnum("TrikV62EncoderPort", { qMakePair(QString("E1"), tr("E1")), qMakePair(QString("E2"), tr("E2")), qMakePair(QString("E3"), tr("E3")), qMakePair(QString("E4"), tr("E4")) });
	mMetamodel->setEnumEditable("TrikV62EncoderPort", false);
	mMetamodel->addEnum("TrikV6AnalogSensorPort", { qMakePair(QString("A1"), tr("A1")), qMakePair(QString("A2"), tr("A2")), qMakePair(QString("A3"), tr("A3")), qMakePair(QString("A4"), tr("A4")), qMakePair(QString("A5"), tr("A5")), qMakePair(QString("A6"), tr("A6")) });
	mMetamodel->setEnumEditable("TrikV6AnalogSensorPort", false);
	mMetamodel->addEnum("TrikV6DigitalSensorPort", { qMakePair(QString("D1"), tr("D1")), qMakePair(QString("D2"), tr("D2")) });
	mMetamodel->setEnumEditable("TrikV6DigitalSensorPort", false);
	mMetamodel->addEnum("TrikV6EncoderPort", { qMakePair(QString("B1"), tr("B1")), qMakePair(QString("B2"), tr("B2")), qMakePair(QString("B3"), tr("B3")), qMakePair(QString("B4"), tr("B4")) });
	mMetamodel->setEnumEditable("TrikV6EncoderPort", false);
	mMetamodel->addEnum("VideoSensor", { qMakePair(QString("color"), tr("Color sensor")), qMakePair(QString("line"), tr("Line sensor")), qMakePair(QString("object"), tr("Object sensor")) });
	mMetamodel->setEnumEditable("VideoSensor", false);
	mMetamodel->addEnum("VisibilityKind", { qMakePair(QString("package"), tr("Package")), qMakePair(QString("private"), tr("Private")), qMakePair(QString("protected"), tr("Protected")), qMakePair(QString("public"), tr("Public")) });
	mMetamodel->setEnumEditable("VisibilityKind", false);
	mMetamodel->addEnum("bool", { qMakePair(QString("false"), tr("false")), qMakePair(QString("true"), tr("true")) });
	mMetamodel->setEnumEditable("bool", false);
}

