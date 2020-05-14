#ifndef FORMBALISECHK_H
#define FORMBALISECHK_H

#include <QWidget>

namespace Ui {
class FormBaliseChk;
}

class FormBaliseChk : public QWidget
{
    Q_OBJECT

public:
    explicit FormBaliseChk(QWidget *parent = nullptr);
    ~FormBaliseChk();

private:
    Ui::FormBaliseChk *ui;
};

#endif // FORMBALISECHK_H