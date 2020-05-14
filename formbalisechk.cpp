#include "formbalisechk.h"
#include "ui_formbalisechk.h"

FormBaliseChk::FormBaliseChk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormBaliseChk)
{
    ui->setupUi(this);
}

FormBaliseChk::~FormBaliseChk()
{
    delete ui;
}
