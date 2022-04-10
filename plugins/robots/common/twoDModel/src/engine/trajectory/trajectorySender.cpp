#include <QEventLoop>
#include <QtNetwork/QNetworkProxy>
#include "trajectorySender.h"

TrajectorySender::TrajectorySender()
//TrajectorySender::TrajectorySender(QString ip, int port)
//    : Ip(ip)
//    , Port(port)
{
}

TrajectorySender::~TrajectorySender()
{
    reset();
    keepaliveTimer->deleteLater();
    socket->deleteLater();
}

void TrajectorySender::init()
{
    keepaliveTimer = new QTimer();
    socket = new QTcpSocket();
    /// passing this to QTcpSocket allows `socket` to be moved
    /// to another thread with the parent
    /// when TrajectorySender.moveToThread() is called
    qRegisterMetaType<QAbstractSocket::SocketState>();
//    connect(socket, &QTcpSocket::stateChanged, this, &TrajectorySender::stateChanged);
    connect(keepaliveTimer, &QTimer::timeout, this, [this]() { write("keepalive 4000\n"); } );
    connect(socket, &QTcpSocket::readyRead, this, &TrajectorySender::onReadyRead);
}

bool TrajectorySender::isConnected() const
{
    return socket->state() == QTcpSocket::ConnectedState;
}

void TrajectorySender::write(const QString &data)
{
    qint64 result = socket->write(data.toLatin1().data());
//    emit dataWasWritten(static_cast<int>(result));
}

void TrajectorySender::onReadyRead()
{
    const QByteArray &data = socket->readAll();
    mBuffer = data;
    //qDebug(mBuffer);
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

void TrajectorySender::reset()
{
    if (!keepaliveTimer->isActive())
        return;
    keepaliveTimer->stop();
    socket->disconnectFromHost();
//    emit dataWasWritten(-1); // simulate disconnect
}

quint16 TrajectorySender::getPort() const
{
    return Port;
}

QString TrajectorySender::getIp() const
{
    return Ip;
}

void TrajectorySender::setPort(const quint16 &value)
{
    Port = value;
}

void TrajectorySender::setIp(const QString &value)
{
    Ip = value;
}

void TrajectorySender::connectToHost()
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
//        emit connectionFailed();
    }
}
