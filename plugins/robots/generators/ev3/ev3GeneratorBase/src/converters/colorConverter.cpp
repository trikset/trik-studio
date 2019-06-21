#include "colorConverter.h"

using namespace ev3::converters;

ColorConverter::ColorConverter(const QStringList &pathsToTemplates)
	: generatorBase::converters::DynamicPathConverter(pathsToTemplates, "colors/@@DATA@@.t")
{
}
