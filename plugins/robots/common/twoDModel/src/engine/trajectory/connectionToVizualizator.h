#ifndef CONNECTIONTOVIZUALIZATOR_H
#define CONNECTIONTOVIZUALIZATOR_H

#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtCore/QIODevice>
#include <QScopedPointer>
#include <QTimer>


/// TODO description
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
	/// TODO description
//	void stateChanged(QAbstractSocket::SocketState socketState);

//	/// TODO description
//	void dataWasWritten(int);

//	/// TODO description
//	void connectionFailed();

private:
	QTcpSocket *socket;
	QTimer *keepaliveTimer;

	QString Ip {"10.0.5.2"};
	quint16 Port { 8080 };
	QByteArray mBuffer;
	bool sendData = true;
};


#endif // CONNECTIONTOVIZUALIZATOR_H
