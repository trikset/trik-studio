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
#include <qrutils/graphicsUtils/abstractItem.h>

namespace twoDModel {
namespace view {

/// The region editing mode implies the following. If we use ReadOnlyWorldModel, the region editing mode should
/// not make any changes to the behavior. Otherwise, in the region editing mode, all regions
/// (depending on their semantics) should be able to be edited.  For other elements on the scene,
/// this may involve additional functionality that can be accessed in this mode.
enum class EditorMode {
	defaultMode,
	regionEditorMode
};

class TwoDSceneItem: public graphicsUtils::AbstractItem
{
	Q_OBJECT
	Q_DISABLE_COPY(TwoDSceneItem)
public:
	explicit TwoDSceneItem(QGraphicsItem *parent = nullptr): AbstractItem(parent) {};
	virtual void switchToMode(EditorMode mode) { mCurrentEditorMode = mode; };
protected:
	using EditorMode = twoDModel::view::EditorMode;
	EditorMode editorMode() const {return mCurrentEditorMode; }
	EditorMode mCurrentEditorMode = EditorMode::defaultMode;
};

}
}
