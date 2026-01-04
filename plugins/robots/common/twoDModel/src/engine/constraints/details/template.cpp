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


#include "template.h"
#include <QHash>

using namespace twoDModel::constraints::details;

XmlTemplate::XmlTemplate(const QString &id, const QString &text)
	: mId(id), mText(text) {};

void XmlTemplate::emplaceParam(uint16_t startPosition, uint32_t length, const QString &name, const QString& value)
{
	mParams.emplace(startPosition, XmlTemplate::TemplateParamInfo(startPosition, length, name, value));
};

QString XmlTemplate::proccess(const QHash<QString, QString> &paramsForReplace) const
{
	auto result = mText;
	for (auto it = mParams.rbegin(); it != mParams.rend(); ++it) {
		auto replaceIt = paramsForReplace.find(it->second.mName);
		if (replaceIt == paramsForReplace.end()) {
			result.replace(it->second.mStartPosition, it->second.mLength, it->second.mDefaultValue);
			continue;
		}

		const auto &value = replaceIt.value();
		result.replace(it->second.mStartPosition, it->second.mLength, value);
	}
	return result;
}
