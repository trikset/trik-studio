#include "syntheticVariableNameGenerator.h"
#include "generatorBase/generatorCustomizer.h"

using namespace generatorBase;
using namespace qReal;

simple::SyntheticVariableNameGenerator::SyntheticVariableNameGenerator(const qrRepo::RepoApi &repo
		, GeneratorCustomizer &customizer
		, const Id &id
		, ReadableLabelManager &nameManager
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "function.t"
			, { Binding::createStaticConverting("@@BODY@@"
					, nameManager.labelFor(id) + "=" +
						repo.property(id, repo.hasProperty(id, "Condition") ? "Condition" : "Expression").toString()
					, customizer.factory()->functionBlockConverter(id, "Condition")) }
			, parent)
{
}
