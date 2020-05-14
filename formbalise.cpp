#include "formbalise.h"
#include "ui_formbalise.h"

FormBalise::FormBalise(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormBalise)
{
    ui->setupUi(this);
}

FormBalise::~FormBalise()
{
    delete ui;
}