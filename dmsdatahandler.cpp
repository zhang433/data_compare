#include "dmsdatahandler.h"
#include <QDateTime>

DmsDataHandler::DmsDataHandler(QObject *parent) : QObject(parent)
{

}

void DmsDataHandler::BaseInfoProc(QByteArray qba)
{
    //时间处理
    QByteArray time_qba = qba.left(8);
    QString strTime = time_qba.toHex().toUpper();
    strTime+='0';
    QDateTime time = QDateTime::fromString(strTime, "yyyyMMddhhmmsszzz");
    //qDebug()<<"time:"<<strTime;
    m_baseInfo.set_curTime(time);

    //车次处理
    QByteArray trainno_qba = qba.mid(8,8);
    QString strNo = trainno_qba.toHex().toUpper();
    if(strNo != "FFFFFFFFFFFFFFFF")
    {
        quint32 ulNum = *(quint32 *)(&(trainno_qba.data()[4]));
        QString str_ascii = QString(trainno_qba.data()[3]);
        str_ascii+=QString(trainno_qba.data()[2]);
        str_ascii+=QString(trainno_qba.data()[1]);
        str_ascii+=QString(trainno_qba.data()[0]);
        str_ascii+=QString::number(ulNum);
        m_baseInfo.set_trainNo(str_ascii);
    }

    //运行等级
    quint8 level = static_cast<quint8>(qba.at(16));
    if(level!=0xFF)
    {
        m_baseInfo.set_runLevel(level);
    }
    //动作模式
    quint8 mode = static_cast<quint8>(qba.at(17));
    if(level!=0xFF)
    {
        m_baseInfo.set_controlMode(mode);
    }
    //制动命令
    quint8 info = static_cast<quint8>(qba.at(18));
    if(level!=0xFF)
    {
        m_baseInfo.set_breakInfo(info);
    }
    //当前速度
    QByteArray speed_qba = qba.mid(19,2);
    quint16 speed = *(quint16 *)(&(speed_qba.data()[0]));
    if(speed!=0xFFFF)
    {
        m_baseInfo.set_curSpeed(speed);
    }
    //EBP速度
    speed_qba = qba.mid(21,2);
    speed = *(quint16 *)(&(speed_qba.data()[0]));
    if(speed!=0xFFFF)
    {
        m_baseInfo.set_EBPSpeed(speed);
    }
    //NBP速度
    speed_qba = qba.mid(23,2);
    speed = *(quint16 *)(&(speed_qba.data()[0]));
    if(speed!=0xFFFF)
    {
        m_baseInfo.set_NBPSpeed(speed);
    }
    //目标速度
    speed_qba = qba.mid(25,2);
    speed = *(quint16 *)(&(speed_qba.data()[0]));
    if(speed!=0xFFFF)
    {
        m_baseInfo.set_EBPSpeed(speed);
    }
    //目标距离
    QByteArray tar_dist = qba.mid(27,4);
    quint32 dist = *(quint32 *)(&(tar_dist.data()[0]));
    if(dist!=0xFFFFFFFF)
    {
        m_baseInfo.set_tarDistant(dist);
    }
    //里程信息
    QByteArray cur_mil = qba.mid(31,4);
    quint32 mil = *(quint32 *)(&(cur_mil.data()[0]));
    if(mil!=0xFFFFFFFF)
    {
        m_baseInfo.set_curMileage(mil);
    }
    //载频
    quint8 freq = static_cast<quint8>(qba.at(35));
    if(freq!=0xFF)
    {
        m_baseInfo.set_carryFreq(freq);
    }
    //低频
    quint8 low_freq = static_cast<quint8>(qba.at(36));
    if(low_freq!=0xFF)
    {
        m_baseInfo.set_lowFreq(low_freq);
    }
    //司机ID
    QByteArray driver_id = qba.mid(37,4);
    quint32 id = *(quint32 *)(&(driver_id.data()[0]));
    if(id!=0xFFFFFFFF)
    {
        m_baseInfo.set_driverID(QString::number(id));
    }
    emit SendBaseInfo(m_baseInfo);
}

void DmsDataHandler::BaliseDataProc(QByteArray qba)
{
    struct BaliseHead *pBaliseHead;
    //时间处理
    QByteArray time_qba = qba.left(8);
    QString strTime = time_qba.toHex().toUpper();
    strTime+='0';
    QDateTime time = QDateTime::fromString(strTime, "yyyyMMddhhmmsszzz");


}

void DmsDataHandler::DataHandle(QByteArray qba)
{
    quint8  ucType = static_cast<quint8>(qba.at(0));
    int     iLen = qba.size();
    QByteArray  tmp_qba = qba.mid(1,iLen-1);

    if(ucType==DMS_BASE_DATA)
    {
        BaseInfoProc(tmp_qba);
    }
    else if(ucType==DMS_BALISE_DATA)
    {
        BaliseDataProc(tmp_qba);
    }
    else if (ucType==DMS_RBC_DATA)
    {
        //RBCDataProc(tmp_qba);
    }
    else {
        qDebug() << "Received data type error:" << ucType;
    }
    return;
}