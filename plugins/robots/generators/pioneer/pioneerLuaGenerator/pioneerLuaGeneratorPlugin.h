/* Copyright 2017 QReal Research Group
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

#include <QtCore/QScopedPointer>
#include <QProcess>
#include <QComboBox>

#include <generatorBase/robotsGeneratorPluginBase.h>

class QProcess;

namespace qReal {
class EditorManagerInterface;
}

namespace pioneer {

namespace blocks {
class PioneerBlocksFactory;
}

namespace lua {

class PioneerGeneratorRobotModel;
class PioneerAdditionalPreferences;
class CommunicationManager;

/// Main class for Pioneer Lua generator plugin.
class PioneerLuaGeneratorPlugin : public generatorBase::RobotsGeneratorPluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "pioneer.lua.PioneerLuaGeneratorPlugin")

public:
	PioneerLuaGeneratorPlugin();
	~PioneerLuaGeneratorPlugin() override;

	void init(const kitBase::KitPluginConfigurator &configurator) override;

	QList<qReal::ActionInfo> customActions() override;

	QList<qReal::HotKeyActionInfo> hotKeyActions() override;

	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

	QList<QWidget *>listOfQuickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model) override;

	int priority() const override;

	QString kitId() const override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;

	QSharedPointer<kitBase::blocksBase::BlocksFactoryInterface> blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model
			) override;

	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;

	QString defaultSettingsFile() const override;

	void onCurrentRobotModelChanged(kitBase::robotModel::RobotModelInterface &model) override;

	void onCurrentDiagramChanged(const qReal::TabInfo &info) override;

private slots:
	/// Uploads current program to a quadcopter.
	void uploadProgram();

	/// Displays errors and output
	void uploadFinished();

private:
	generatorBase::MasterGeneratorBase *masterGenerator() override;

	QString defaultFilePath(const QString &projectName) const override;

	qReal::text::LanguageInfo language() const override;

	QString generatorName() const override;

	void regenerateExtraFiles(const QFileInfo &newFileInfo) override;

	/// Set "enabled" state of "upload" and "run" actions to a given value.
	void setActionsEnabled(bool isEnabled);

	void connectSelector(QComboBox * selector, QString settings);
	QWidget *ipSelector();
	QWidget *portSelector();
	QWidget *modeSelector();

	/// Action that launches code generator.
	QAction *mGenerateCodeAction;  // Doesn't have ownership; may be disposed by GUI.

	/// Action that uploads generated program onto quadcopter.
	QAction *mUploadProgramAction;  // Doesn't have ownership; may be disposed by GUI.

	/// Factory for blocks on a diagram that can be processed by this generator.
	QSharedPointer<kitBase::blocksBase::BlocksFactoryInterface> mBlocksFactory;

	/// Robot model for a generator, defines robot name and other unneeded properties.
	QScopedPointer<PioneerGeneratorRobotModel> mGeneratorForRealCopterRobotModel;

	/// Additional preferences widget, which allows to set IP of a base station.
	/// Transfers ownership.
	PioneerAdditionalPreferences *mAdditionalPreferences = nullptr;

	/// Whether we need to delete mAdditionalPreferences (sometimes plugin gets destroyed before it is able to pass
	/// an ownership, so it is needed to avoid memleak). Need to use smart pointers instead of this.
	bool mOwnsAdditionalPreferences = true;

	/// Metamodel object with visual language infomation.
	/// Does not have ownership.
	const qReal::EditorManagerInterface *mMetamodel {};

	QProcess mUploader;
};

}
}
