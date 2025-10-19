#include "subprogramCallGenerator.h"

#include <QDomElement>

#include "generatorBase/generatorCustomizer.h"
#include "ev3GeneratorBase/ev3GeneratorFactory.h"

using namespace ev3::simple;
using namespace generatorBase::simple;

namespace {
	Binding::ConverterInterface *createConverter(
		const QString &type,
		const QString &dynamicPropertyValue,
		generatorBase::GeneratorCustomizer &customizer,
		const qReal::Id &id) {
		if (type == "int") {
			return customizer.factory()->intPropertyConverter(id, dynamicPropertyValue);
		} else if (type == "bool") {
			return customizer.factory()->boolPropertyConverter(id, dynamicPropertyValue, false);
		} else if (type == "string") {
			return customizer.factory()->stringPropertyConverter(id, dynamicPropertyValue);
		}
		return customizer.factory()->floatPropertyConverter(id, dynamicPropertyValue);
	}
}

SubprogramCallGenerator::SubprogramCallGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const qReal::Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "subprograms/subprogramCall.t", QList<Binding *>()
			   << Binding::createConverting("@@NAME@@", "name", customizer.factory()->nameNormalizerConverter())
				, parent)
{
	const auto &dynamicProperties = mRepo.property(id, "dynamicProperties").toString();
	QDomDocument dynamicPropertiesXml;
	dynamicPropertiesXml.setContent(dynamicProperties);
	const auto &properties = dynamicPropertiesXml.firstChildElement("properties");
	QStringList argumentsList;
	for (auto property = properties.firstChildElement("property");
		!property.isNull(); property = property.nextSiblingElement()) {
		const auto &type = property.attribute("type");
		const auto dynamicPropertyValue = property.attribute("dynamicPropertyValue");
		const auto *converter = createConverter(type, dynamicPropertyValue, customizer, id);
		argumentsList << converter->convert(dynamicPropertyValue);
	}
	QString result = argumentsList.join(readTemplate("luaPrinting/argumentsSeparator.t"));
	addBinding(Binding::createStatic("@@ARGUMENTS@@", result));
}
