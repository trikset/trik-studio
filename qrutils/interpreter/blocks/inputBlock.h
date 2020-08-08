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

#pragma once

#include "qrutils/interpreter/block.h"
#include <QInputDialog>

namespace qReal {
namespace interpretation {
namespace blocks {

/// Interpreter`s implementation for variable initialization block.
class QRUTILS_EXPORT InputBlock : public Block
{
	Q_OBJECT

public:
	explicit InputBlock();
	~InputBlock() override;
	void run() override;
	void setFailedStatus() override;
private:
	bool initNextBlocks() override;
	bool checkLinksCount();
	void onValueSelected(const QString &text);
	void onRejected();

	qReal::Id mCancelBlockId;
	QInputDialog mDialog;
};

}
}
}
