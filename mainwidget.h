#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "config.h"
#include "enventcontrol.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void initWidget();
public slots:

private:
    Ui::MainWidget *ui;
    Config congfigInfo;
    EnventControl eventcontrol;
};

#endif // MAINWIDGET_H