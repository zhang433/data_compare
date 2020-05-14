#ifndef ENVENTCONTROL_H
#define ENVENTCONTROL_H

#include <QObject>
#include <QThread>
#include "tcpsocketwork.h"
#include <qtimer.h>
#include "dmsdatahandler.h"

#define DMS_MIN_LEN     10
#define DMS_HEAD_LEN    2
#define DMS_VER_LEN    2
#define DMS_TAIL_LEN    2
#define DMS_CRC_LEN    2
#define DMS_BYTES_LEN    2
#define DMS_HEAD        0xA0A0
#define DMS_TAIL        0x0A0A

class EnventControl : public QObject
{
    Q_OBJECT
public:
    explicit EnventControl(QObject *parent = nullptr);
    ~EnventControl();
public:
    void start(const QString & ip, quint16 port, int msec);
    void heartBeatBlk();
    void recordRawData(QByteArray qba);
    void decodedata(QByteArray &qba);
    quint16 calculate_crc(quint16 wCRCin, quint16 wCPoly, quint16 wResultXOR, bool input_invert, bool ouput_invert, const char *puchMsg, int usDataLen);
signals:
    void startRunning(const QString & ip, quint16 port);
    void writeBytes(QByteArray qba);
    void apktReceived(QByteArray qba);
    void sendBaseInfo(BaseInfo *info);
public slots:
    void recvBytes(QByteArray qba);
    void readErrMsg(const QString & str);
    void restart();
    void HeartbeatSend();
    void rxBaseInfo(BaseInfo info);
private:
    QThread m_tcpThread;
    TcpSocketWork *m_tcpworker;
    QTimer m_heartbeatTm;
    QString m_host;
    quint16 m_port;
    QByteArray m_hbtBlk;

    DmsDataHandler *m_dmsdata;
    QThread m_dmsdataThread;
};

#endif // ENVENTCONTROL_H
