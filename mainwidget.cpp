#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initWidget();
    ui->tabWidget->setCurrentIndex(0);

}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::initWidget()
{
    congfigInfo.readConfig();
    qDebug()<<congfigInfo.TcpServerIP<<congfigInfo.TcpServerPort<<congfigInfo.IntervalMS;
    //控制管理收包和处理包
    qDebug()<<"From main thread: "<<QThread::currentThreadId();
    eventcontrol.start(congfigInfo.TcpServerIP, congfigInfo.TcpServerPort, congfigInfo.IntervalMS);
    connect(&eventcontrol,&EnventControl::sendBaseInfo, ui->tabBaseInfo, &FormBaseInfo::UpDateBaseInfo);
}
