// ----------------------------------------------------------------------- //
// This file is auto-generated with qrxc v1.1. Do not modify its contents
// or prepare to lose your edits. If you want to change something in it
// consider editing language metamodel instead.
// ----------------------------------------------------------------------- //

#pragma once

#include <metaMetaModel/metamodel.h>

class RobotsMetamodelPlugin : public QObject, public qReal::MetamodelLoaderInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::MetamodelLoaderInterface)
	Q_PLUGIN_METADATA(IID "RobotsMetamodel")

public:
	RobotsMetamodelPlugin();

	QStringList dependencies() const override;
	void load(qReal::Metamodel &metamodel) override;

private:
	void initPlugin();
	void initMultigraph();
	void initNameMap();
	void initEnums();
	void initPaletteGroupsMap();
	void initPaletteGroupsDescriptionMap();
	void initShallPaletteBeSortedMap();

private:
	qReal::Metamodel *mMetamodel;  // Does not have ownership.
};

