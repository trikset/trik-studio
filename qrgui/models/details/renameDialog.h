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

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>

namespace qReal {
namespace gui {

class RenameDialog : public QDialog
{
public:
	static QString selectNewName(const QString &currentName, QWidget *parent = nullptr);

private slots:
	virtual void accept();
	virtual void reject();

private:
	explicit RenameDialog(const QString &initialText = "", QWidget *parent = nullptr);
	virtual ~RenameDialog();

	QString name() const;

	const QString mInitialName;
	QLineEdit *mTextBox;
};

}
}
