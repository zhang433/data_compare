#include "tcpsocketwork.h"
#include <QDebug>
#include <qdatastream.h>

TcpSocketWork::TcpSocketWork(QObject *parent) : QTcpSocket(parent)
{
    connect(this,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(readError(QAbstractSocket::SocketError)));
    connect(this,&TcpSocketWork::readyRead, this, &TcpSocketWork::readBytes);
}

void TcpSocketWork::connectServer(const QString &host, quint16 port)
{
    qDebug() << host<<":"<<port <<this->state();
    if((this->state()==QAbstractSocket::BoundState)||(this->state()==QAbstractSocket::UnconnectedState))
    {
        this->connectToHost(host,port);
        if(this->waitForConnected())
        {
            emit errorRead(tr("无法连接到服务器")+this->errorString());
        }
    }
    return;
}

void TcpSocketWork::readBytes()
{
    this->waitForReadyRead(1000);
    QByteArray data = this->readAll();
    //qDebug() << data;
    if (!data.isEmpty()){
        emit bytesRead(data);
    }
}

void TcpSocketWork::writeBytes(QByteArray data)
{
    qint64 ret = 0;
    if(this->state() == QAbstractSocket::ConnectedState)
    {
        //往套接字缓存中写入数据，并发送
        ret = this->write(data);
        this->waitForBytesWritten(500);
        if (ret == -1){
            emit errorRead(tr("发送数据失败：")+this->errorString());
        }
    }
    else
    {
        emit errorRead(tr("端口未连接：")+this->errorString()+this->state());
    }
}

void TcpSocketWork::readError(QAbstractSocket::SocketError)
{
    QString str(QString::number(this->peerPort()));
    str+=":erro:";
    str+=this->errorString();
    emit errorRead(str);
}
