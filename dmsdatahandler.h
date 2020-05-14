#ifndef DMSDATAHANDLER_H
#define DMSDATAHANDLER_H

#include <QObject>
#include "baseinfo.h"
#include <QByteArray>
#include <QDebug>
#include "balise.h"

#define     DMS_BASE_DATA      1
#define     DMS_BALISE_DATA    2
#define     DMS_RBC_DATA       3

class DmsDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit DmsDataHandler(QObject *parent = nullptr);
    void BaseInfoProc(QByteArray qba);
    void BaliseDataProc(QByteArray qba);

signals:
    void SendBaseInfo(BaseInfo info);
public slots:
    void DataHandle(QByteArray qba);
private:
    BaseInfo m_baseInfo;
};

#endif // DMSDATAHANDLER_H