#ifndef FORMBASEINFO_H
#define FORMBASEINFO_H

#include <QtCharts/QChart>
#include <QWidget>

#include "baseinfo.h"
QT_CHARTS_BEGIN_NAMESPACE
//class QSplineSeries;
class QValueAxis;
class QDateTimeAxis;
class QLineSeries;
class QCategoryAxis;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


#define RUN_LEVEL_CTCS0     0
#define RUN_LEVEL_CTCS1     1
#define RUN_LEVEL_CTCS2     2
#define RUN_LEVEL_CTCS3     3

#define CONTROL_MODE_FS     0
#define CONTROL_MODE_PS     1
#define CONTROL_MODE_CO     3
#define CONTROL_MODE_RO     2
#define CONTROL_MODE_CS     4
#define CONTROL_MODE_BF     5
#define CONTROL_MODE_OS     6
#define CONTROL_MODE_SR     7
#define CONTROL_MODE_SH     8
#define CONTROL_MODE_UN     9
#define CONTROL_MODE_SL     10
#define CONTROL_MODE_SB     11
#define CONTROL_MODE_TR     12
#define CONTROL_MODE_PT     13
#define CONTROL_MODE_SF     14
#define CONTROL_MODE_IS     15
#define CONTROL_MODE_NL     16
#define CONTROL_MODE_SE     17
#define CONTROL_MODE_SN     18
#define CONTROL_MODE_RV     19

#define BRAKE_SB0             0
#define BRAKE_SB1             1
#define BRAKE_SB4             4
#define BRAKE_SB7             7
#define BRAKE_EB             13

#define CARRY_FREQ_UNKNOW       0
#define CARRY_FREQ_0            1
#define CARRY_FREQ_550          2
#define CARRY_FREQ_650          3
#define CARRY_FREQ_750          4
#define CARRY_FREQ_850          5
#define CARRY_FREQ_1700         6
#define CARRY_FREQ_2000         7
#define CARRY_FREQ_2300         8
#define CARRY_FREQ_2600         9

#define LOW_FREQ_UNKNOW     0
#define LOW_FREQ_0          1
#define LOW_FREQ_H          2
#define LOW_FREQ_HU         3
#define LOW_FREQ_HB         4
#define LOW_FREQ_U          5
#define LOW_FREQ_U2S        6
#define LOW_FREQ_U2         7
#define LOW_FREQ_UU         8
#define LOW_FREQ_UUS        9
#define LOW_FREQ_LU         10
#define LOW_FREQ_LU2        11
#define LOW_FREQ_L          12
#define LOW_FREQ_L2         13
#define LOW_FREQ_L3         14
#define LOW_FREQ_L4         15
#define LOW_FREQ_L5         16
#define LOW_FREQ_L6         17
#define LOW_FREQ_257        18
#define LOW_FREQ_279        19
#define LOW_FREQ_U3         20

namespace Ui {
class FormBaseInfo;
}

class FormBaseInfo : public QWidget
{
    Q_OBJECT

public:
    explicit FormBaseInfo(QWidget *parent = nullptr);
    ~FormBaseInfo();
    void initBaseInfoForm();
    QString runlevel2str(quint8 runLevel);
    QString contrlmod2str(quint8 runLevel);
    QString brakeinfo2str(quint8 info);
    QString carryfreq2str(quint8 freq);
    QString lowfreq2str(quint8 freq);
public slots:
    void UpDateBaseInfo(BaseInfo *info);

private:
    Ui::FormBaseInfo *ui;
    BaseInfo m_Info;
    QList<BaseInfo> listBaseInfo;

    QChart* chart;

    QLineSeries *m_series;              //列车当前速度
    QLineSeries *m_NBPseries;           //列车NBP速度
    QLineSeries *m_EBPseries;           //列车EBP速度
    QScatterSeries *m_Balisescatter;    //应答器数据点
    QScatterSeries *m_RBCscatter;       //RBC数据点
    QDateTimeAxis *m_axisX;
    //QValueAxis *m_axisY;
    //QDateTimeAxis *m_axisMX;
    QCategoryAxis *m_axisMY;
    qreal  m_step;
    QDateTime  m_x;
    qreal m_y;
};

#endif // FORMBASEINFO_H
