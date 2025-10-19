#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

namespace ev3 {
namespace simple {

class SubprogramCallGenerator : public generatorBase::simple::BindingGenerator
{
	Q_OBJECT
	Q_DISABLE_COPY(SubprogramCallGenerator)
public:
	SubprogramCallGenerator(const qrRepo::RepoApi &repo
				, generatorBase::GeneratorCustomizer &customizer
				, const qReal::Id &id
				, QObject *parent = nullptr);
};

}
}
