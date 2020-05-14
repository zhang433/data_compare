#include "formbaseinfo.h"
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include "ui_formbaseinfo.h"
#include "enventcontrol.h"
//#include <QSplineSeries>
#include <QLineSeries>

FormBaseInfo::FormBaseInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormBaseInfo)
{
    ui->setupUi(this);
    initBaseInfoForm();
}

FormBaseInfo::~FormBaseInfo()
{
    delete ui;
}

void FormBaseInfo::initBaseInfoForm()
{
    //边框项目初始化
    ui->mil_le->setText(QString::number(m_Info.get_curMileage()));
    ui->runtime_le->setText(m_Info.get_curTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->tardist_le->setText(QString::number(m_Info.get_tarDistant()));
    ui->trainno_le->setText(m_Info.get_trainNo());
    ui->curspeed_le->setText(QString::number(m_Info.get_curSpeed()));
    ui->driverid_le->setText(m_Info.get_driverID());
    ui->ebpspeed_le->setText(QString::number(m_Info.get_EBPSpeed()));
    ui->nbpspeed_le->setText(QString::number(m_Info.get_NBPSpeed()));
    ui->runlevel_le->setText(runlevel2str(m_Info.get_runLevel()));
    ui->tarspeed_le->setText(QString::number(m_Info.get_tarSpeed()));
    ui->controlmode_le->setText(contrlmod2str(m_Info.get_controlMode()));
    //当前速度曲线绘图区初始化
    m_series = new QLineSeries();
    QPen green(Qt::blue);
    green.setWidth(2);
    m_series->setPen(green);
    //NBP速度曲线绘图区初始化
    m_NBPseries = new QLineSeries();
    QPen NBPPen(Qt::yellow);
    NBPPen.setWidth(2);
    m_NBPseries->setPen(NBPPen);
    //EBP速度曲线绘图区初始化
    m_EBPseries = new QLineSeries();
    QPen EBPPen(Qt::red);
    EBPPen.setWidth(2);
    m_EBPseries->setPen(EBPPen);

    m_Balisescatter = new QScatterSeries();
    m_Balisescatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    m_Balisescatter->setMarkerSize(16.0);
    QPainterPath starPath;
    starPath.moveTo(2,14);
    starPath.lineTo(8,2);
    starPath.lineTo(14,14);
    starPath.closeSubpath();
    QImage star(16, 16, QImage::Format_ARGB32);
    star.fill(Qt::transparent);
    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(QBrush(painter.pen().color(),Qt::NoBrush));
    painter.drawPath(starPath);
    m_Balisescatter->setBrush(star);
    m_Balisescatter->setPen(QColor(Qt::transparent));

    m_RBCscatter = new QScatterSeries();
    m_RBCscatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    m_RBCscatter->setMarkerSize(15.0);
    m_RBCscatter->setColor(QRgb(0x00FF00));

    chart = new QChart();
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->addSeries(m_series);
    chart->addSeries(m_NBPseries);
    chart->addSeries(m_EBPseries);
    chart->addSeries(m_Balisescatter);
    chart->addSeries(m_RBCscatter);
    chart->setDropShadowEnabled(false);
    //chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);

    m_axisX = new QDateTimeAxis;
    m_axisX->setTickCount(11);
    m_axisX->setFormat("hh:mm:ss");
    m_axisX->setTitleText("Time");
    chart->addAxis(m_axisX,Qt::AlignBottom);
    m_series->attachAxis(m_axisX);
    m_NBPseries->attachAxis(m_axisX);
    m_EBPseries->attachAxis(m_axisX);
    m_Balisescatter->attachAxis(m_axisX);
    m_RBCscatter->attachAxis(m_axisX);

    m_axisMY = new QCategoryAxis;
    m_axisMY->setMin(-150);
    m_axisMY->setMax(350);
    m_axisMY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    m_axisMY->setStartValue(0);
    m_axisMY->append("RBC", -100);
    m_axisMY->append("Balise", -50);

    m_axisMY->append("0", 0);
    m_axisMY->append("50", 50);
    m_axisMY->append("100", 100);
    m_axisMY->append("150", 150);
    m_axisMY->append("200", 200);
    m_axisMY->append("250", 250);
    m_axisMY->append("300", 300);
    m_axisMY->append("350", 350);

    chart->addAxis(m_axisMY,Qt::AlignLeft);
    m_series->attachAxis(m_axisMY);
    m_NBPseries->attachAxis(m_axisMY);
    m_EBPseries->attachAxis(m_axisMY);

    ui->speed_chart->setChart(chart);
    ui->speed_chart->setRenderHint(QPainter::Antialiasing);
    //ui->speed_chart->setRubberBand(QChartView::RectangleRubberBand);  //矩形缩放
    ui->speed_chart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

void FormBaseInfo::UpDateBaseInfo(BaseInfo *info)
{
    BaseInfo *pinfo = new BaseInfo();
    memcpy(pinfo, info, sizeof (BaseInfo));
    ui->mil_le->setText(QString::number(pinfo->get_curMileage()));
    ui->runtime_le->setText(pinfo->get_curTime().toString("yyyy-MM-dd hh:mm:ss zzz"));
    ui->tardist_le->setText(QString::number(pinfo->get_tarDistant()));
    ui->trainno_le->setText(pinfo->get_trainNo());
    ui->curspeed_le->setText(QString::number(pinfo->get_curSpeed()));
    ui->driverid_le->setText(pinfo->get_driverID());
    ui->ebpspeed_le->setText(QString::number(pinfo->get_EBPSpeed()));
    ui->nbpspeed_le->setText(QString::number(pinfo->get_NBPSpeed()));
    ui->runlevel_le->setText(runlevel2str(pinfo->get_runLevel()));
    ui->tarspeed_le->setText(QString::number(pinfo->get_tarSpeed()));
    ui->controlmode_le->setText(contrlmod2str(pinfo->get_controlMode()));
    static int i = 0;
    i++;
    QString str = QString("------%1-----").arg(i);
    ui->baliseno_le->setText(str);

    listBaseInfo.append(*pinfo);
    
    //更新曲线图
    m_x = pinfo->get_curTime();
    qint64 msec_new = m_x.toMSecsSinceEpoch();
    m_step = chart->plotArea().width()/(m_axisX->tickCount()-1);
    static qint64 msec_last = 0;
    if(0 == msec_last)//第一个时间点
    {
        qint64 Xstart = msec_new/5000*5000;//时间轴以5S的整数倍为起始点
        qint64 Xend = Xstart+50000;  //时间轴长为50秒
        QDateTime startT = QDateTime::fromMSecsSinceEpoch(Xstart);
        QDateTime endT = QDateTime::fromMSecsSinceEpoch(Xend);
        //m_axisX->setMin(startT);
        //m_axisX->setMax(startT.addDays(1));
        m_axisX->setRange(startT,endT);
    }
    else {
        //在画图区末尾前5秒的时间，更新坐标轴
        qint64 msec_update = msec_new+5000;
        qint64 msec_max = m_axisX->max().toMSecsSinceEpoch();
        //两个时间点的时间差值
        if((msec_update > msec_max)&&(msec_update < (msec_max+5000))) //超出一格，滚动坐标轴
        {
            chart->scroll(m_step,0);
        }
        else if(msec_update > (msec_max+5000)) //超出2格以上，重新设置坐标轴
        {
            qint64 Xstart = msec_new/5000*5000;//时间轴以5S的整数倍为起始点
            qint64 Xend = Xstart+50000;  //时间轴长为50秒
            QDateTime startT = QDateTime::fromMSecsSinceEpoch(Xstart);
            QDateTime endT = QDateTime::fromMSecsSinceEpoch(Xend);
            //m_axisX->setMin(startT);
            //m_axisX->setMax(startT.addDays(1));
            m_axisX->setRange(startT,endT);
        }
        else {
            //没有超出当前坐标轴的范围时，继续画图
        }
    }
    msec_last = msec_new;

    //设置Y轴的值
    m_y = pinfo->get_curSpeed();
    m_series->append(msec_new,m_y);

    m_y = pinfo->get_NBPSpeed();
    m_NBPseries->append(msec_new,m_y);

    m_y = pinfo->get_EBPSpeed();
    m_EBPseries->append(msec_new,m_y);
}

QString FormBaseInfo::runlevel2str(quint8 runLevel)
{
    QString strRet = "";
    if(runLevel == RUN_LEVEL_CTCS3)
    {
        strRet = "CTCS-3";
    }
    else if(runLevel == RUN_LEVEL_CTCS2)
    {
        strRet = "CTCS-2";
    }
    else if(runLevel == RUN_LEVEL_CTCS1)
    {
        strRet = "CTCS-1";
    }
    else if(runLevel == RUN_LEVEL_CTCS0)
    {
        strRet = "CTCS-0";
    }
    else
    {
        strRet = QString::number(runLevel);
    }
    return strRet;
}

QString FormBaseInfo::contrlmod2str(quint8 mode)
{
    QString strRet = "";
    switch (mode) {
    case CONTROL_MODE_FS:
        strRet = "FS";
        break;
    case CONTROL_MODE_PS:
        strRet = "PS";
        break;
    case CONTROL_MODE_CO:
        strRet = "CO";
        break;
    case CONTROL_MODE_OS:
        strRet = "OS";
        break;
    case CONTROL_MODE_SH:
        strRet = "SH";
        break;
    case CONTROL_MODE_SL:
        strRet = "SL";
        break;
    case CONTROL_MODE_SB:
        strRet = "SB";
        break;
    case CONTROL_MODE_TR:
        strRet = "TR";
        break;
    case CONTROL_MODE_PT:
        strRet = "PT";
        break;
    default:
        strRet = QString::number(mode);
        break;
    }
    return strRet;
}

QString FormBaseInfo::brakeinfo2str(quint8 info)
{
    QString strRet = "";
    if(info == BRAKE_SB0)
    {
        strRet = "------";
    }
    else if(info == BRAKE_SB1)
    {
        strRet = "SB1";
    }
    else if(info == BRAKE_SB4)
    {
        strRet = "SB4";
    }
    else if(info == BRAKE_SB7)
    {
        strRet = "SB7";
    }
    else if(info == BRAKE_EB)
    {
        strRet = "EB";
    }
    else
    {
        strRet = QString::number(info);
    }
    return strRet;
}

QString FormBaseInfo::carryfreq2str(quint8 freq)
{
    QString strRet = "";
    switch (freq) {
    case CARRY_FREQ_UNKNOW:
        strRet = "Unknown";
        break;
    case CARRY_FREQ_0:
        strRet = "0";
        break;
    case CARRY_FREQ_550:
        strRet = "550";
        break;
    case CARRY_FREQ_650:
        strRet = "650";
        break;
    case CARRY_FREQ_750:
        strRet = "750";
        break;
    case CARRY_FREQ_850:
        strRet = "850";
        break;
    case CARRY_FREQ_1700:
        strRet = "1700";
        break;
    case CARRY_FREQ_2000:
        strRet = "2000";
        break;
    case CARRY_FREQ_2300:
        strRet = "2300";
        break;
    case CARRY_FREQ_2600:
        strRet = "2600";
        break;
    default:
        strRet = QString::number(freq);
        break;
    }
    return strRet;
}

QString FormBaseInfo::lowfreq2str(quint8 freq)
{
    QString strRet = "";
    switch (freq) {
    case LOW_FREQ_UNKNOW:
        strRet = "Unknown";
        break;
    case LOW_FREQ_0:
        strRet = "0";
        break;
    case LOW_FREQ_H:
        strRet = "H";
        break;
    case LOW_FREQ_HU:
        strRet = "HU";
        break;
    case LOW_FREQ_HB:
        strRet = "HB";
        break;
    case LOW_FREQ_U:
        strRet = "U";
        break;
    case LOW_FREQ_U2S:
        strRet = "U2S";
        break;
    case LOW_FREQ_U2:
        strRet = "U2";
        break;
    case LOW_FREQ_UU:
        strRet = "UU";
        break;
    case LOW_FREQ_UUS:
        strRet = "UUS";
        break;
    case LOW_FREQ_LU:
        strRet = "LU";
        break;
    case LOW_FREQ_L:
        strRet = "L";
        break;
    case LOW_FREQ_L2:
        strRet = "L2";
        break;
    case LOW_FREQ_L3:
        strRet = "L3";
        break;
    case LOW_FREQ_L4:
        strRet = "L4";
        break;
    case LOW_FREQ_L5:
        strRet = "L5";
        break;
    case LOW_FREQ_257:
        strRet = "257Hz";
        break;
    case LOW_FREQ_279:
        strRet = "279Hz";
        break;
    default:
        strRet = QString::number(freq);
        break;
    }
    return strRet;
}