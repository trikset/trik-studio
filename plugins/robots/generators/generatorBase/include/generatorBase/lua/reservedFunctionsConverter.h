/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include "generatorBase/templateParametrizedEntity.h"

namespace generatorBase {
namespace lua {

/// Converts the given Lua reserved function call to the target language one.
class ROBOTS_GENERATOR_EXPORT ReservedFunctionsConverter : public TemplateParametrizedEntity
{
public:
	explicit ReservedFunctionsConverter(const QStringList &pathsToTemplates);

	QString convert(const QString &name, const QStringList &args) const;

	inline bool needChangeArg(const QString &name) const {
		return name == "cos" || name == "sin";
	}

	inline bool needChangeResult(const QString &name) const {
		return name == "atan2" || name == "acos" || name == "asin" || name == "atan";
	}

	inline QString translateArg(const QString &functionName, const QString &argName, const QString &newArgName) const {
		return needChangeArg(functionName) ? QString("MULF(%1, %2, %3)").arg(argName, s180dividedByPi, newArgName) : QString();
	}


	inline QString translateResult(const QString &functionName, const QString &argName) const {
		return needChangeResult(functionName) ? QString("DIVF(%1, %2, %1)").arg(argName, s180dividedByPi) : QString();
	}
private:
	static constexpr auto s180dividedByPi = "57.29577951308232F";
};

}
}
