#ifndef BASEINFO_H
#define BASEINFO_H

#include <QDateTime>

struct BaseInfo
{
    BaseInfo();

    QDateTime   get_curTime();
    QString     get_trainNo();
    quint8      get_runLevel();
    quint8      get_controlMode();
    quint8      get_breakInfo();
    quint16     get_curSpeed();
    quint16     get_EBPSpeed();
    quint16     get_NBPSpeed();
    quint16     get_tarSpeed();
    quint32     get_tarDistant();
    quint32     get_curMileage();
    quint8      get_carryFreq();
    quint8      get_lowFreq();
    QString     get_driverID();
    void set_curTime(QDateTime nowTime);
    void set_trainNo(QString no);
    void set_runLevel(quint8 level);
    void set_controlMode(quint8 mode);
    void set_breakInfo(quint8 info);
    void set_curSpeed(quint16 speed);
    void set_EBPSpeed(quint16 speed);
    void set_NBPSpeed(quint16 speed);
    void set_tarSpeed(quint16 speed);
    void set_tarDistant(quint32 dist);
    void set_curMileage(quint32 mil);
    void set_carryFreq(quint8 freq);
    void set_lowFreq(quint8 freq);
    void set_driverID(QString id);

private:
    QDateTime       curTime;
    QString         trainNo;
    quint8          runLevel;
    quint8          controlMode;
    quint8          breakInfo;
    quint16         curSpeed;
    quint16         EBPSpeed;
    quint16         NBPSpeed;
    quint16         tarSpeed;
    quint32         tarDistant;
    quint32         curMileage;
    quint8          carryFreq;
    quint8          lowFreq;
    QString         driverID;
};

#endif // BASEINFO_H
