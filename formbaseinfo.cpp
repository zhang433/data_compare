#include "formbaseinfo.h"
#include "ui_formbaseinfo.h"
#include "enventcontrol.h"

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
    ui->mil_le->setText(QString::number(m_Info.get_curMileage()));
    ui->runtime_le->setText(m_Info.get_curTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->tardist_le->setText(QString::number(m_Info.get_tarDistant()));
    ui->trainno_le->setText(m_Info.get_trainNo());
    ui->curspeed_le->setText(QString::number(m_Info.get_curSpeed()));
    ui->driverid_le->setText(m_Info.get_driverID());
    ui->ebpspeed_le->setText(QString::number(m_Info.get_EBPSpeed()));
    ui->nbpspeed_le->setText(QString::number(m_Info.get_NBPSpeed()));
    ui->runlevel_le->setText(QString::number(m_Info.get_runLevel()));
    ui->tarspeed_le->setText(QString::number(m_Info.get_tarSpeed()));
    ui->controlmode_le->setText(QString::number(m_Info.get_controlMode()));
    //m_pInfo = new BaseInfo();
    //UpDateBaseInfo(m_pInfo);
    //connect()

}

void FormBaseInfo::UpDateBaseInfo(BaseInfo *info)
{
    BaseInfo *pinfo = new BaseInfo();
    memcpy((char*)pinfo, (char*)info, sizeof (BaseInfo));
    ui->mil_le->setText(QString::number(pinfo->get_curMileage()));
    ui->runtime_le->setText(pinfo->get_curTime().toString("yyyy-mm-dd hh:mm:ss zzz"));
    ui->tardist_le->setText(QString::number(pinfo->get_tarDistant()));
    ui->trainno_le->setText(pinfo->get_trainNo());
    ui->curspeed_le->setText(QString::number(pinfo->get_curSpeed()));
    ui->driverid_le->setText(pinfo->get_driverID());
    ui->ebpspeed_le->setText(QString::number(pinfo->get_EBPSpeed()));
    ui->nbpspeed_le->setText(QString::number(pinfo->get_NBPSpeed()));
    ui->runlevel_le->setText(QString::number(pinfo->get_runLevel()));
    ui->tarspeed_le->setText(QString::number(pinfo->get_tarSpeed()));
    ui->controlmode_le->setText(QString::number(pinfo->get_controlMode()));
    ui->baliseno_le->setText("----------");

    listBaseInfo.append(*pinfo);
}
