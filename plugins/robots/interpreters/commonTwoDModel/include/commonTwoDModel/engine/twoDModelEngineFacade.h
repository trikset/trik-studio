#pragma once

#include <QtCore/QString>
#include <QtCore/QScopedPointer>

#include <interpreterBase/robotModel/robotModelInterface.h>

#include "commonTwoDModel/engine/twoDModelControlInterface.h"
#include "commonTwoDModel/engine/twoDModelEngineInterface.h"

namespace twoDModel {

class D2RobotModel;

namespace engine {

class TwoDModelEngineFacade : public TwoDModelControlInterface
{
	Q_OBJECT

public:
	TwoDModelEngineFacade(interpreterBase::robotModel::RobotModelInterface &robotModel);
	~TwoDModelEngineFacade();
	qReal::ActionInfo &showTwoDModelWidgetActionInfo() override;
	interpreterBase::SensorsConfigurationProvider &sensorsConfigurationProvider() override;

	TwoDModelEngineInterface &engine();

public slots:
	void onStartInterpretation() override;
	void onStopInterpretation() override;

private:
	qReal::ActionInfo mTwoDModelActionInfo;  // Has ownership over contained QAction object.
	QScopedPointer<D2RobotModel> mTwoDModel;
};

}
}
