#include "baseinfo.h"

BaseInfo::BaseInfo()
{
    set_curTime(QDateTime::currentDateTime());
    set_trainNo("xxxx");
    set_runLevel(0);
    set_controlMode(0);
    set_breakInfo(0);
    set_curSpeed(0);
    set_EBPSpeed(0);
    set_NBPSpeed(0);
    set_tarSpeed(0);
    set_tarDistant(0);
    set_curMileage(0);
    set_carryFreq(0);
    set_lowFreq(0);
    set_driverID("oooo");
}

QDateTime   BaseInfo::get_curTime()
{
    return curTime;
}
QString     BaseInfo::get_trainNo()
{
    return trainNo;
}
quint8      BaseInfo::get_runLevel()
{
    return runLevel;
}
quint8      BaseInfo::get_controlMode()
{
    return controlMode;
}
quint8      BaseInfo::get_breakInfo()
{
    return breakInfo;
}
quint16     BaseInfo::get_curSpeed()
{
    return curSpeed;
}
quint16     BaseInfo::get_EBPSpeed()
{
    return EBPSpeed;
}
quint16     BaseInfo::get_NBPSpeed()
{
    return NBPSpeed;
}
quint16     BaseInfo::get_tarSpeed()
{
    return tarSpeed;
}
quint32     BaseInfo::get_tarDistant()
{
    return tarDistant;
}
quint32     BaseInfo::get_curMileage()
{
    return curMileage;
}
quint8      BaseInfo::get_carryFreq()
{
    return carryFreq;
}
quint8      BaseInfo::get_lowFreq()
{
    return lowFreq;
}
QString     BaseInfo::get_driverID()
{
    return driverID;
}
void BaseInfo::set_curTime(QDateTime nowTime)
{
    curTime = nowTime;
}
void BaseInfo::set_trainNo(QString no)
{
    trainNo = no;
}
void BaseInfo::set_runLevel(quint8 level)
{
    runLevel = level;
}
void BaseInfo::set_controlMode(quint8 mode)
{
    controlMode = mode;
}
void BaseInfo::set_breakInfo(quint8 info)
{
    breakInfo = info;
}
void BaseInfo::set_curSpeed(quint16 speed)
{
    curSpeed = speed;
}
void BaseInfo::set_EBPSpeed(quint16 speed)
{
    EBPSpeed = speed;
}
void BaseInfo::set_NBPSpeed(quint16 speed)
{
    NBPSpeed = speed;
}
void BaseInfo::set_tarSpeed(quint16 speed)
{
    tarSpeed = speed;
}
void BaseInfo::set_tarDistant(quint32 dist)
{
    tarDistant = dist;
}
void BaseInfo::set_curMileage(quint32 mil)
{
    curMileage = mil;
}
void BaseInfo::set_carryFreq(quint8 freq)
{
    carryFreq = freq;
}
void BaseInfo::set_lowFreq(quint8 freq)
{
    lowFreq = freq;
}
void BaseInfo::set_driverID(QString id)
{
    driverID = id;
}