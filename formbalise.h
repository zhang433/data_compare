#ifndef FORMBALISE_H
#define FORMBALISE_H

#include <QWidget>
#include "balise.h"

namespace Ui {
class FormBalise;
}

class FormBalise : public QWidget
{
    Q_OBJECT

public:
    explicit FormBalise(QWidget *parent = nullptr);
    ~FormBalise();

private:
    Ui::FormBalise *ui;
};

#endif // FORMBALISE_H