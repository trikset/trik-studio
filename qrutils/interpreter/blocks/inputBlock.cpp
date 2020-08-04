/* Copyright 2020 CyberTech Labs Ltd.
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

#include "inputBlock.h"
#include <QInputDialog>

using namespace qReal::interpretation::blocks;

void InputBlock::run()
{
	bool ok;
	const auto var = stringProperty("variable");
	const auto defaultValue = stringProperty("default");
	auto prompt = stringProperty("prompt");
	if (prompt.isEmpty()) {
		prompt = tr("Input value for %1:").arg(var);
	}
	const auto value = QInputDialog::getText(nullptr, tr("Input"), prompt, QLineEdit::Normal, defaultValue, &ok);

	if (!ok || value.isEmpty()) {
		emit error(tr("You must input some value!"));
		return;
	}
	evalCode(var + " = " + value);
	if (!errorsOccured()) {
		emit done(mNextBlockId);
	}
}
