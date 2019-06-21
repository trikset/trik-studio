#include "waitForColorBlockGenerator.h"

#include <src/ev3GeneratorCustomizer.h>

using namespace ev3::simple;
using namespace generatorBase::simple;

WaitForColorBlockGenerator::WaitForColorBlockGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const qReal::Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "wait/color.t",
		{ Binding::createConverting("@@PORT@@", "Port", customizer.factory()->portNameConverter())
		, Binding::createConverting("@@COLOR@@", "Color"
				, static_cast<Ev3GeneratorFactory *>(customizer.factory())->colorConverter())
		}, parent)
{
}
