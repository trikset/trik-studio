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
#include <QtCore/QThread>


/// This class performs win8 drag manager hack for workaround of
/// https://github.com/qreal/qreal/issues/1014
class HackTouchDragThread : public QThread
{
	Q_OBJECT
public:
	explicit HackTouchDragThread(QObject *parent = nullptr);

	static void simulateSystemPress();
	static void simulateSystemMove();
	static void simulateSystemRelease();

protected:
	virtual void run();
};


