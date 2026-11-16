/* Copyright 2026 CyberTech Labs Ltd.
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

#include "fontSettingsWidget.h"

#include <QtGui/QFontInfo>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

#include <qrgui/brandManager/brandManager.h>

using namespace qReal;

namespace {
/// Returns the font resolved to the family and style that actually exist.
/// This keeps the dialog and the description free from missing families such
/// as "Segoe UI" on Linux.
QFont resolvedFont(const QFont &font)
{
	const QFontInfo info(font);
	const auto family = info.family();
	const auto styleName = info.styleName();

	QFont resolved = font;
	if (!family.isEmpty()) {
		resolved.setFamily(family);
		resolved.setFamilies({family});
	}

	if (!styleName.isEmpty()) {
		resolved.setStyleName(styleName);
	}

	return resolved;
}
}

FontSettingsWidget::FontSettingsWidget(QWidget *parent)
	: QWidget(parent)
	, mFontSettings(BrandManager::fonts())
{
	setupUi();
	setupRoleRows();
	retranslate();
	reload();
}

void FontSettingsWidget::setupUi()
{
	auto *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);

	mHeader = new QToolButton(this);
	mHeader->setCheckable(true);
	mHeader->setChecked(true);
	mHeader->setAutoRaise(true);
	mHeader->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	mHeader->setArrowType(Qt::DownArrow);
	layout->addWidget(mHeader, 0, Qt::AlignLeft);

	mContent = new QFrame(this);
	mContent->setFrameShape(QFrame::StyledPanel);
	mContent->setFrameShadow(QFrame::Raised);

	mRolesLayout = new QGridLayout(mContent);
	mRolesLayout->setColumnStretch(1, 1);
	layout->addWidget(mContent);

	connect(mHeader, &QToolButton::toggled, this, [this](bool expanded) {
		mContent->setVisible(expanded);
		mHeader->setArrowType(expanded ? Qt::DownArrow : Qt::RightArrow);
	});
}

void FontSettingsWidget::setupRoleRows()
{
	const auto roles = FontSettingsManager::roles();
	mRows.reserve(roles.size());

	for (const auto role : roles) {
		const auto row = mRows.size();

		RoleRow widgets;
		widgets.role = role;
		widgets.title = new QLabel(mContent);
		widgets.description = new QLabel(mContent);
		widgets.description->setWordWrap(true);
		widgets.chooseButton = new QPushButton(mContent);
		widgets.resetButton = new QPushButton(mContent);

		mRolesLayout->addWidget(widgets.title, row, 0);
		mRolesLayout->addWidget(widgets.description, row, 1);
		mRolesLayout->addWidget(widgets.chooseButton, row, 2);
		mRolesLayout->addWidget(widgets.resetButton, row, 3);

		mRows.append(widgets);

		connect(widgets.chooseButton, &QPushButton::clicked, this, [this, row] { chooseFont(row); });
		connect(widgets.resetButton, &QPushButton::clicked, this, [this, row] { resetFont(row); });
	}
}

void FontSettingsWidget::reload()
{
	mFontSettings.reload();
	updateAllRows();
}

bool FontSettingsWidget::hasChanges() const
{
	return mFontSettings.hasChanges();
}

void FontSettingsWidget::save()
{
	mFontSettings.save();
}

void FontSettingsWidget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	if (e->type() == QEvent::LanguageChange) {
		retranslate();
	}
}

void FontSettingsWidget::chooseFont(int row)
{
	const auto role = mRows.at(row).role;

	QFontDialog dialog(this);
	// Bundled fonts live only in QFontDatabase, so the native GTK dialog
	// (which enumerates fonts through fontconfig) cannot see or select them.
	dialog.setOption(QFontDialog::DontUseNativeDialog);
	dialog.setCurrentFont(displayedFont(role));

	const auto initialFont = dialog.currentFont();
	if (dialog.exec() != QDialog::Accepted) {
		return;
	}

	// Accepting the unchanged selection must not turn the default font into
	// an explicit user override.
	const auto selectedFont = dialog.currentFont();
	if (selectedFont == initialFont) {
		return;
	}

	mFontSettings.setFont(role, selectedFont);
	updateRow(row);
}

void FontSettingsWidget::resetFont(int row)
{
	const auto role = mRows.at(row).role;

	mFontSettings.resetFont(role);
	updateRow(row);
}

void FontSettingsWidget::updateRow(int row)
{
	const auto &widgets = mRows.at(row);
	widgets.description->setText(fontDescription(displayedFont(widgets.role)));
}

void FontSettingsWidget::updateAllRows()
{
	for (auto row = 0; row < mRows.size(); ++row) {
		updateRow(row);
	}
}

void FontSettingsWidget::retranslate()
{
	mHeader->setText(tr("Fonts"));

	for (auto &widgets : mRows) {
		widgets.title->setText(tr("%1:").arg(roleTitle(widgets.role)));
		widgets.chooseButton->setText(tr("Choose Font..."));
		widgets.resetButton->setText(tr("Reset to Default"));
	}

	updateAllRows();
}

QFont FontSettingsWidget::displayedFont(FontRole role) const
{
	return resolvedFont(mFontSettings.displayedFont(role));
}

QString FontSettingsWidget::fontDescription(const QFont &font) const
{
	const QFontInfo info(font);
	QStringList parts;
	if (!info.family().isEmpty()) {
		parts << info.family();
	}

	if (font.pointSize() > 0) {
		parts << tr("%1 pt").arg(font.pointSize());
	} else if (font.pixelSize() > 0) {
		parts << tr("%1 px").arg(font.pixelSize());
	}

	if (!info.styleName().isEmpty()) {
		parts << info.styleName();
	}

	return parts.join(", ");
}

QString FontSettingsWidget::roleTitle(FontRole role) const
{
	switch (role) {
	case FontRole::SceneLabels:
		return tr("Diagram labels");
	case FontRole::CodeEditor:
		return tr("Code editor");
	case FontRole::Ui:
		return tr("Start screen");
	}

	return {};
}
