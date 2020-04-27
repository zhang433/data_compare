#ifndef FORMBASEINFO_H
#define FORMBASEINFO_H

#include <QWidget>
#include <QtCharts>
#include "baseinfo.h"

QT_CHARTS_USE_NAMESPACE

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
public slots:
    void UpDateBaseInfo(BaseInfo *info);

private:
    Ui::FormBaseInfo *ui;
    BaseInfo m_Info;
    QList<BaseInfo> listBaseInfo;
};

#endif // FORMBASEINFO_H
