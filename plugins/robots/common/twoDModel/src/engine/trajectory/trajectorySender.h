#ifndef TRAJECTORYSENDER_H
#define TRAJECTORYSENDER_H

#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtCore/QIODevice>
#include <QScopedPointer>
#include <QTimer>


/// TODO description
class alignas(8) TrajectorySender : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TrajectorySender)

public:
//    TrajectorySender(QString ip, int port);
    TrajectorySender();
    ~TrajectorySender();

    /// inits manager after moved to correct thread
    void init();

    /// checks connection
    bool isConnected() const;

    /// sets ip
    void setIp(const QString &value);

    /// sets port
    void setPort(const quint16 &value);

    void onReadyRead();

    /// returns ip
    QString getIp() const;

    /// returns port
    quint16 getPort() const;

public slots:
    void connectToHost();
    void write(const QString &);

    /// Disconnect
    void reset();

signals:
    void stopRequested();
    void runRequested();
    void restartRequested();
    /// TODO description
//    void stateChanged(QAbstractSocket::SocketState socketState);

//    /// TODO description
//    void dataWasWritten(int);

//    /// TODO description
//    void connectionFailed();

private:
    QTcpSocket *socket;
    QTimer *keepaliveTimer;

    QString Ip;
    quint16 Port { 4444 };
    QByteArray mBuffer;
};


#endif // TRAJECTORYSENDER_H
