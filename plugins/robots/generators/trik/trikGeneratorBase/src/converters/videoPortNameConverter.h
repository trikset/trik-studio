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

#include <kitBase/robotModel/portInfo.h>

#include <generatorBase/simpleGenerators/binding.h>

namespace trik {
namespace converters {

/// Port name converter that maps ports of video detectors (line/color/object sensors configured on
/// a video camera) to the actual camera source string used by the brick API ("video1", "video2",
/// "usb-camera"). All other ports are delegated to the generic converter.
class VideoPortNameConverter : public generatorBase::simple::Binding::ConverterInterface
{
public:
	VideoPortNameConverter(const QList<kitBase::robotModel::PortInfo> &ports,
		generatorBase::simple::Binding::ConverterInterface *genericConverter);

	~VideoPortNameConverter() override;

	QString convert(const QString &portNameOrAlias) const override;

private:
	const QList<kitBase::robotModel::PortInfo> mPorts;
	generatorBase::simple::Binding::ConverterInterface *mGenericConverter;
};

}
}
