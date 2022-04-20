#include <QEventLoop>
#include <QtNetwork/QNetworkProxy>
#include "connectionToVizualizator.h"

ConnectionToVizualizator::ConnectionToVizualizator()
//ConnectionToVizualizator::ConnectionToVizualizator(QString ip, int port)
//	: Ip(ip)
//	, Port(port)
{
}

ConnectionToVizualizator::~ConnectionToVizualizator()
{
	reset();
	keepaliveTimer->deleteLater();
	socket->deleteLater();
}

void ConnectionToVizualizator::init()
{
	keepaliveTimer = new QTimer();
	socket = new QTcpSocket();
	/// passing this to QTcpSocket allows `socket` to be moved
	/// to another thread with the parent
	/// when ConnectionToVizualizator.moveToThread() is called
	qRegisterMetaType<QAbstractSocket::SocketState>();
//	connect(socket, &QTcpSocket::stateChanged, this, &ConnectionToVizualizator::stateChanged);
	connect(keepaliveTimer, &QTimer::timeout, this, [this]() { write("keepalive 4000\n"); } );
	connect(socket, &QTcpSocket::readyRead, this, &ConnectionToVizualizator::onReadyRead);
}

bool ConnectionToVizualizator::isConnected() const
{
	return socket->state() == QTcpSocket::ConnectedState;
}

void ConnectionToVizualizator::write(const QString &data)
{
	socket->write(data.toLatin1().data());
//	emit dataWasWritten(static_cast<int>(result));
}

void ConnectionToVizualizator::onReadyRead()
{
	const QByteArray &data = socket->readAll();
	mBuffer = data;
	if (mBuffer == "Stop") {
		emit stopRequested();
	}
	else if (mBuffer == "Run") {
		emit runRequested();
	}
	else if (mBuffer == "Restart") {
		emit restartRequested();
	}
}

void ConnectionToVizualizator::stopPressed()
{
	write("Stop");
}

void ConnectionToVizualizator::startPressed()
{
	write("Run");
}

void ConnectionToVizualizator::restartPressed()
{
	write("Restart");
}

void ConnectionToVizualizator::reset()
{
	if (!keepaliveTimer->isActive())
		return;
	keepaliveTimer->stop();
	socket->disconnectFromHost();
//	emit dataWasWritten(-1); // simulate disconnect
}

quint16 ConnectionToVizualizator::getPort() const
{
	return Port;
}

QString ConnectionToVizualizator::getIp() const
{
	return Ip;
}

void ConnectionToVizualizator::setPort(const quint16 &value)
{
	Port = value;
}

void ConnectionToVizualizator::setIp(const QString &value)
{
	Ip = value;
}

void ConnectionToVizualizator::connectToHost()
{
	reset();
	constexpr auto timeout = 3 * 1000 * 10;
	QEventLoop loop;
	QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
	connect(socket, &QTcpSocket::connected, &loop, &QEventLoop::quit);
	connect(socket
			, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error)
			, &loop
			, [&loop](QAbstractSocket::SocketError) { loop.quit(); });
	socket->setProxy(QNetworkProxy::NoProxy);
	socket->connectToHost(Ip, Port);
	loop.exec();

	if (socket->state() == QTcpSocket::ConnectedState) {
		keepaliveTimer->start(3000 * 10);
	} else {
		socket->abort();
//		emit connectionFailed();
	}
}
