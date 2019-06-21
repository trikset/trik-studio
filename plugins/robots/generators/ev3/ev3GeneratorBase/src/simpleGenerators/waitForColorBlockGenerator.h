#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

namespace ev3 {
namespace simple {

class WaitForColorBlockGenerator : public generatorBase::simple::BindingGenerator
{
public:
	WaitForColorBlockGenerator(const qrRepo::RepoApi &repo
							   , generatorBase::GeneratorCustomizer &customizer
							   , const qReal::Id &id
							   , QObject *parent = nullptr);
};

}
}
