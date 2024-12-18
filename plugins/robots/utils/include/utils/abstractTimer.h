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

#include <QtCore/QObject>

#include <QTimer>

#include "utilsDeclSpec.h"

namespace utils {

class ROBOTS_UTILS_EXPORT AbstractTimer : public QObject
{
	Q_OBJECT

public:
	virtual bool isActive() const = 0;
	virtual int interval() const = 0;
	virtual void setInterval(int ms) = 0;
	virtual void setSingleShot(bool isSingleShot) = 0;
	virtual bool isSingleShot() = 0;

public slots:
	virtual void start() = 0;
	virtual void start(int ms) = 0;
	virtual void stop() = 0;

signals:
	void timeout() ;

protected slots:
	virtual void onTimeout();
};

}
