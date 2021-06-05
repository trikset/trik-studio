#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "src/readableLabelManager.h"

namespace generatorBase {
namespace simple {

//class ReadableLabelManager;

class SyntheticVariableNameGenerator : public BindingGenerator
{
public:
	SyntheticVariableNameGenerator(const qrRepo::RepoApi &repo
			, GeneratorCustomizer &customizer
			, const qReal::Id &id
			, ReadableLabelManager &nameManager
			, QObject *parent);
};

}
}
