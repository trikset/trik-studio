/* Copyright 2007-2016 QReal Research Group
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

#include "errorReporter.h"

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>

#include <qrkernel/exception/exception.h>

#include "mainWindow/errorListWidget.h"
#include "scriptAPI/hintReporter.h"

using namespace qReal;
using namespace gui;

ErrorReporter::ErrorReporter()
	: mErrorListWidget(nullptr)
	, mErrorList(nullptr)
	, mIsVisible(true)
{
}

ErrorReporter::ErrorReporter(ErrorListWidget* const errorListWidget, QDockWidget* const errorList)
	: mErrorListWidget(errorListWidget)
	, mErrorList(errorList)
	, mIsVisible(true)
{
	connect(mErrorListWidget, &ErrorListWidget::clearRequested, this, &ErrorReporter::clear);
}

void ErrorReporter::updateVisibility(bool isVisible)
{
	if (mIsVisible == isVisible) {
		return;
	}

	mIsVisible = isVisible;

	if (!mIsVisible) {
		mErrorList->hide();
	} else if (mErrorListWidget->count() > 0) {
		mErrorList->show();
	}
}

void ErrorReporter::reportOperation(const QFuture<void> &operation, const QString &description)
{
	ProgressBar * const progressBar = new ProgressBar;
	progressBar->reportOperation(operation, description);
	progressBar->setToolTip(description);

	QListWidgetItem *item = new QListWidgetItem(mErrorListWidget);
	progressBar->hide();

	connect(&progressBar->currentOperation(), &QFutureWatcher<void>::started, this, [=]() {
		mErrorListWidget->addItem(item);
		mErrorListWidget->setItemWidget(item, progressBar);
		progressBar->show();
		mErrorList->show();
	});
	connect(&progressBar->currentOperation(), &QFutureWatcher<void>::finished, this, [=]() {
		delete item;
		progressBar->deleteLater();
	});
	connect(&progressBar->currentOperation(), &QFutureWatcher<void>::canceled, this, [=]() {
		delete item;
		progressBar->deleteLater();
	});
}

void ErrorReporter::addInformation(const QString &message, const Id &position)
{
	Error error(message, Error::information, position);
	mErrors.append(error);
	showError(error, mErrorListWidget);
	emit informationAdded(message, position);
}

void ErrorReporter::addWarning(const QString &message, const Id &position)
{
	Error error(message, Error::warning, position);
	mErrors.append(error);
	showError(error, mErrorListWidget);
	emit warningAdded(message, position);
}

void ErrorReporter::addError(const QString &message, const Id &position)
{
	Error error(message, Error::error, position);
	mErrors.append(error);
	showError(error, mErrorListWidget);
	emit errorAdded(message, position);
}

void ErrorReporter::addCritical(const QString &message, const Id &position)
{
	Error error(message, Error::critical, position);
	mErrors.append(error);
	showError(error, mErrorListWidget);
	emit criticalAdded(message, position);
}

bool ErrorReporter::showErrors(ErrorListWidget* const errorListWidget, QDockWidget* const errorList) const
{
	errorListWidget->clear();

	if (mErrors.isEmpty()) {
		errorList->setVisible(false);
		return true;
	}

	errorList->setVisible(true);
	for (const Error &error : mErrors) {
		showError(error, errorListWidget);
	}

	return false;
}

void ErrorReporter::clear()
{
	if (mErrorListWidget) {
		mErrorListWidget->clear();
	}
	if (mErrorList) {
		mErrorList->setVisible(false);
	}
}

void ErrorReporter::clearErrors()
{
	mErrors.clear();
}

bool ErrorReporter::wereErrors() const
{
	for (const Error &error : mErrors) {
		if (error.severity() == Error::critical || error.severity() == Error::error) {
			return true;
		}
	}

	return false;
}

void ErrorReporter::sendBubblingMessage(const QString &message, int duration, QWidget *parent)
{
	if (!parent) {
		// A bit hacky, but not criminal way to get main window.
		parent = mErrorListWidget->topLevelWidget();
	}

	// The message will show and dispose itself.
	new HintReporter(parent, message, duration);
}

void ErrorReporter::showError(const Error &error, ErrorListWidget * const errorListWidget) const
{
	if (!errorListWidget) {
		return;
	}

	if (mErrorList && !mErrorList->isVisible() &&  mIsVisible) {
		mErrorList->setVisible(true);
	}

	QListWidgetItem *item = new QListWidgetItem(errorListWidget);
	item->setData(ErrorListWidget::positionRole, error.position().toString());
	const QString message = QString(" <font color='gray'>%1</font> <u>%2</u> %3").arg(
			error.timestamp(), severityMessage(error), error.message());
	switch (error.severity()) {
	case Error::information:
		item->setIcon(QIcon(":/mainWindow/images/information.png"));
		break;
	case Error::warning:
		item->setIcon(QIcon(":/mainWindow/images/warning.png"));
		break;
	case Error::error:
		item->setIcon(QIcon(":/mainWindow/images/error.png"));
		break;
	case Error::critical:
		item->setIcon(QIcon(":/mainWindow/images/critical.png"));
		break;
	default:
		throw new Exception("Incorrect total severity");
	}

	QLabel *label = new QLabel(message.trimmed());
	label->setAlignment(Qt::AlignVCenter);
	label->setOpenExternalLinks(true);
	errorListWidget->addItem(item);
	errorListWidget->setItemWidget(item, label);
	errorListWidget->setCurrentItem(item);
}

QString ErrorReporter::severityMessage(const Error &error)
{
	switch (error.severity()) {
	case Error::information:
		return tr("INFORMATION:");
	case Error::warning:
		return tr("WARNING:");
	case Error::error:
		return tr("ERROR:");
	case Error::critical:
		return tr("CRITICAL:");
	default:
		throw new Exception("Incorrect severity of an error");
	}
}
