/* Copyright 2025 CyberTech Labs Ltd.
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

#include "twoDModel/engine/model/aliasConfiguration.h"
#include "twoDModel/robotModel/twoDRobotModel.h"

using namespace twoDModel::model;
using namespace kitBase::robotModel;

AliasConfiguration::AliasConfiguration(twoDModel::robotModel::TwoDRobotModel &robotModel)
	: mRobotModel(robotModel) {}

void AliasConfiguration::deserialize(const QDomElement &element)
{
	mAllowedAliases.clear();
	// The configurator block is used to set aliases for non-configurable ports,
	// as the syntax for aliases for the configurator sensor and wheels already
	// exists in worldModel.xml. However, they can also be used in this block,
	// but the information from their own blocks will take precedence and
	// overwrite this information.
	auto &&configurators = element.firstChildElement("configurators");
	for (auto &&configurator = configurators.firstChildElement("configurator");
		!configurator.isNull();
		configurator = configurator.nextSiblingElement("configurator"))
	{
		auto &&portInfo = PortInfo::fromString(configurator.attribute("port"));
		addAliases(portInfo, true);
	}
}

QStringList AliasConfiguration::getAliases(const kitBase::robotModel::PortInfo &portInfo) const
{
	const auto &aliasesIt = mAllowedAliases.find(portInfo);
	if (aliasesIt == mAllowedAliases.end()) {
		return {};
	}
	return aliasesIt.value().mNames;
}

PortInfo AliasConfiguration::createFromPort(const PortInfo &port) const
{
	return PortInfo {
		port.name(),
		port.userFriendlyName(),
		port.direction(),
		getAliases(port),
		port.reservedVariable(),
		port.reservedVariableType()};
}

void AliasConfiguration::addAliases(const kitBase::robotModel::PortInfo &portInfo, bool needSerialize)
{
	QStringList result;
	const auto &portName = portInfo.name();
	const auto &aliases = portInfo.nameAliases();
	for (auto &&alias: aliases) {
		bool found = {};
		for (auto &&otherPort : mRobotModel.availablePorts()) {
			if ((portName != otherPort.name())
				&& (otherPort.name() == alias)) {
				found = true;
				break;
			}
		}
		if (!found) {
			result.append(alias);
		}
	}
	mAllowedAliases[portInfo] = AliasInfo{result, needSerialize};
}

void AliasConfiguration::serialize(QDomElement &element) const
{
	auto &&configurators = element.ownerDocument().createElement("configurators");

	bool exist = false;
	for (auto it = mAllowedAliases.begin(), end = mAllowedAliases.end(); it != end; ++it) {
		if (!it.value().mNeedSerliaze) {
			continue;
		}
		exist = true;
		auto &&configurator = element.ownerDocument().createElement("configurator");
		auto &&port = it.key();
		auto &&portInfo = createFromPort(port);
		configurator.setAttribute("port", portInfo.toString());
		configurators.appendChild(configurator);
	}
	if (exist) {
		element.appendChild(configurators);
	}
}
