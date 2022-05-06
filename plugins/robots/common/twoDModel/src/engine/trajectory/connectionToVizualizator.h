/* Copyright 2022 Lada Egorova
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

#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QIODevice>
#include <QScopedPointer>
#include <QTimer>

//namespace trajectory {
/// Connection to Unity to send frames and run/stop/restart
class alignas(8) ConnectionToVizualizator : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(ConnectionToVizualizator)

public:
//	ConnectionToVizualizator(QString ip, int port);
	ConnectionToVizualizator();
	~ConnectionToVizualizator();

	/// inits manager after moved to correct thread
	void init();

	/// checks connection
	bool isConnected() const;

	/// sets ip
	void setIp(const QString &value);

	/// sets port
	void setPort(const quint16 &value);

	void onReadyRead();

	bool isSendingData();

	/// returns ip
	QString getIp() const;

	/// returns port
	quint16 getPort() const;

public slots:
	void connectToHost();
	void disconnectFromHost();
	void write(const QString &);

	/// Disconnect
	void reset();

	void stopPressed();
	void startPressed();
	void restartPressed();

signals:
	void stopRequested();
	void runRequested();
	void restartRequested();

private:
	QTcpSocket *mSocket;
	QTimer *mKeepaliveTimer;

	QString mIp {"10.0.5.2"};
	quint16 mPort { 8080 };
	QByteArray mBuffer;
	bool mSendData = true;
};
//}
