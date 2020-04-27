#include "enventcontrol.h"
#include "config.h"
#include <QDateTime>
#include <QFile>

EnventControl::EnventControl(QObject *parent) : QObject(parent)
{
    m_tcpworker = new TcpSocketWork();
    m_tcpworker->moveToThread(&m_tcpThread);
    qDebug() << "Controller's thread is :" << QThread::currentThreadId();
    qDebug() << "m_tcpThread:" << &m_tcpThread;
    connect(this,&EnventControl::startRunning,m_tcpworker,&TcpSocketWork::connectServer);
    connect(this,&EnventControl::writeBytes,m_tcpworker,&TcpSocketWork::writeBytes);
    connect(m_tcpworker,&TcpSocketWork::bytesRead,this,&EnventControl::recvBytes);
    connect(m_tcpworker,&TcpSocketWork::errorRead,this,&EnventControl::readErrMsg);
    //connect(m_tcpworker,&TcpSocketWork::disconnected,this,&EnventControl::restart);
    connect(&m_tcpThread, &QThread::finished, m_tcpworker, &QObject::deleteLater);

    heartBeatBlk();
    connect(&m_heartbeatTm, &QTimer::timeout, this, &EnventControl::HeartbeatSend);//超时执行的函数
    m_tcpThread.start();

    //起一线程用于处理数据
    m_dmsdata = new DmsDataHandler();
    m_dmsdata->moveToThread(&m_dmsdataThread);
    connect(this,&EnventControl::apktReceived,m_dmsdata,&DmsDataHandler::DataHandle);
    connect(this,&EnventControl::rxBaseInfo,m_dmsdata,&DmsDataHandler::SendBaseInfo);
    m_dmsdataThread.start();
}

EnventControl::~EnventControl()
{
    m_heartbeatTm.stop();
    m_tcpThread.quit();
    m_tcpThread.wait();
    m_dmsdataThread.quit();
    m_dmsdataThread.wait();
}

void EnventControl::recordRawData(QByteArray qba)
{
    static QString datafile = "";
    if(datafile == "")
    {
        datafile = QString("dms%1.data").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    }
    QFile file(datafile);
    if(file.size()>LOG_SIZE_MAX) //大于100M，另存一个文件
    {
        datafile = "";
    }
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.write(qba);
    file.flush();
    file.close();
    return;
}

void EnventControl::recvBytes(QByteArray qba)
{
    qDebug()<<qba;
    //存储原始数据
    recordRawData(qba);
    decodedata(qba);
}

void EnventControl::readErrMsg(const QString & str)
{
    qDebug() << str;
}

void EnventControl::start(const QString & ip, quint16 port, int msec)
{
    qDebug() << "start running:"<<ip <<port <<msec;
    emit startRunning(ip, port);
    m_host = ip;
    m_port = port;
    m_heartbeatTm.setInterval(msec);//设置心跳超时时间
    m_heartbeatTm.start();
}

void EnventControl::restart()
{
    emit startRunning(m_host,m_port);
    qDebug() << m_host<<"::"<<m_port;
    return;
}

void EnventControl::heartBeatBlk()
{
    //使用数据流写入数据
    QDataStream out(&m_hbtBlk,QIODevice::ReadWrite);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    //设置发送长度初始值为0
    out << static_cast<quint16>(0);
    //设置发送内容
    out<<"GETDATA";

    //回到字节流起始位置
    out.device()->seek(0);
    //重置字节流长度
    out << static_cast<quint16>(static_cast<quint32>(m_hbtBlk.size())-sizeof(quint16));
}

void EnventControl::HeartbeatSend()
{
    //if(m_tcpworker->state()!=QAbstractSocket::ConnectedState)
    if((m_tcpworker->state()==QAbstractSocket::UnconnectedState)||
            (m_tcpworker->state()==QAbstractSocket::BoundState))
    {
        qDebug()<<"timeout reconnect:"<<m_tcpworker->state();
        emit startRunning(m_host,m_port);
    }
    else if(m_tcpworker->state()==QAbstractSocket::ConnectedState)
    {
        emit writeBytes(m_hbtBlk);
    }
    else {
        qDebug()<<"timeout:"<<m_tcpworker->state();
    }
}

void EnventControl::rxBaseInfo(BaseInfo &info)
{
    qDebug()<<"EnventControl emit";
    BaseInfo tmpInfo;
    memcpy(&info, &tmpInfo, sizeof(BaseInfo));
    emit sendBaseInfo(&tmpInfo);
}

void EnventControl::decodedata(QByteArray &qba)
{
    QDataStream datastream(&qba,QIODevice::ReadWrite);
    int baLen = qba.size();
    char *pcBuf = qba.data();
    quint16  usBytesLen = 0;
    quint16  usCrcChk = 0;
    quint16  usVersion = 0;
    quint16  usTail = 0;
    QByteArray rawDataQba;
    rawDataQba.clear();
    static quint32 ulCnt = 0;
    if(baLen<DMS_MIN_LEN)
    {
        return;
    }
    int i=0;
    for (i=0;i<=baLen-DMS_HEAD_LEN;i++)
    {
        quint16* pusTmp =((quint16*)(pcBuf+i));
        quint16 usHead = *pusTmp;

        if(usHead == DMS_HEAD)//找到起始符
        {
            if(baLen-i-DMS_HEAD_LEN > DMS_BYTES_LEN)//数据长度字段已知
            {
                usBytesLen = *(++pusTmp);
                if(baLen-i>=usBytesLen)  //缓冲区长度大于一包数据长度
                {
                    usVersion = *(++pusTmp);
                    usCrcChk = *((quint16*)(pcBuf+i+usBytesLen-DMS_CRC_LEN-DMS_TAIL_LEN));
                    usTail = *((quint16*)(pcBuf+i+usBytesLen-DMS_TAIL_LEN));
                    quint16 my_calculate = calculate_crc(0,0x1021,0,false,false,(const char *)(pcBuf+i+DMS_HEAD_LEN),usBytesLen-DMS_HEAD_LEN-DMS_CRC_LEN-DMS_TAIL_LEN);
                    //校验收到的数据包内容：CRC校验和尾部校验
                    if((usTail!=DMS_TAIL)||(my_calculate!=usCrcChk)) //校验不通过
                    {
                        continue;
                    }
                    else//校验通过，取出数据
                    {
                        QByteArray tmp_qba = qba.mid(i+DMS_HEAD_LEN+DMS_BYTES_LEN+DMS_VER_LEN,usBytesLen-DMS_MIN_LEN);
                        qDebug() << tmp_qba.toHex();
                        i=i+usBytesLen-1;
                        ulCnt++;
                        qDebug() << "Pkt No "<<ulCnt;
                        emit apktReceived(tmp_qba);
                        continue;
                    }
                }
                else  //一包数据不足
                {
                    qba.remove(0,i);
                    return;
                }
            }
            else//数据长度未知
            {
                qba.remove(0,i);
                return;
            }
        }
        else //未找到起始符
        {

        }
    }
    if(i>=baLen-DMS_HEAD_LEN)
    {
        //qba.remove(0,i);
        qba.clear();
        qDebug() <<"2."<< &qba;
    }
    return;
}

/*************************************************
Function:       calculate_crc
Description:    通用的16位CRC校验算法
Input:          wCRCin：CRC16算法的初始值
                wCPoly：特征多项式
                wResultXOR：结果异或值
                input_invert：输入值是否反转
                ouput_invert：输出值是否反转
                puchMsg：开始校验的数据的起始地址
                usDataLen：校验的数据长度
Output:         无输出
Return:         16位CRC校验结果
Others:         example：CRC-16/CCITT由本函数实现则填充参数如下：
                calculate_crc(0,0x1021,0,true,true,puchMsg,usDataLen)
*************************************************/
quint16 EnventControl::calculate_crc(quint16 wCRCin, quint16 wCPoly, quint16 wResultXOR, bool input_invert, bool ouput_invert, const char *puchMsg, int usDataLen)
{
    quint8 wChar = 0;
    while (usDataLen--)
    {
        wChar = static_cast<quint8>(*(puchMsg++));
        if(input_invert)//输入值反转
        {
            quint8 temp_char = wChar;
            wChar=0;
            for(int i=0;i<8;++i)
            {
                if(temp_char&0x01)
                    wChar|=0x01<<(7-i);
                temp_char>>=1;
            }
        }
        wCRCin ^= (wChar << 8);
        for (int i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = static_cast<quint16>((wCRCin << 1) ^ wCPoly);
            else
                wCRCin = static_cast<quint16>(wCRCin << 1);
        }
    }
    if(ouput_invert)
    {
        quint16 temp_short = wCRCin;
        wCRCin=0;
        for(int i=0;i<16;++i)
        {
            if(temp_short&0x01)
                wCRCin|=0x01<<(15-i);
            temp_short>>=1;
        }
    }
    return (wCRCin^wResultXOR);
}
