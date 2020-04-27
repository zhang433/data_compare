#include "formtrackinfo.h"
#include "ui_formtrackinfo.h"

FormTrackInfo::FormTrackInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTrackInfo)
{
    ui->setupUi(this);
}

FormTrackInfo::~FormTrackInfo()
{
    delete ui;
}
