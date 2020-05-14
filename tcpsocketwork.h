#ifndef TCPSOCKETWORK_H
#define TCPSOCKETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <qdatastream.h>

class TcpSocketWork : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocketWork(QObject *parent = nullptr);

signals:
    void bytesRead(QByteArray);
    void errorRead(const QString &);
    void disconnectSocket();

public slots:
    void readBytes();
    void writeBytes(QByteArray data);
    void readError(QAbstractSocket::SocketError);
    void connectServer(const QString &host, quint16 port);

private:

};

#endif // TCPSOCKETWORK_H
