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


#pragma once

#include <QDomElement>
#include <unordered_map>
#include <map>

namespace twoDModel {
namespace constraints {
namespace details {

class XmlTemplate {
public:
	XmlTemplate(const QString &id, const QString &text);
	void emplaceParam(uint16_t startPosition, uint32_t length, const QString &name, const QString& value);
	QString proccess(const QHash<QString, QString> &paramsForReplace) const;

private:
	struct TemplateParamInfo {
		uint16_t mStartPosition;
		uint32_t mLength;
		QString mName;
		QString mDefaultValue;

		TemplateParamInfo(uint16_t startPosition,
			      uint32_t length,
			      const QString& name,
			      const QString &defaultValue)
		    : mStartPosition(startPosition), mLength(length), mName(name), mDefaultValue(defaultValue) {}
	};
	QString mId;
	QString mText;
	std::map<int, TemplateParamInfo> mParams;
};
}
}
}
