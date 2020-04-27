#ifndef FORMTRACKINFO_H
#define FORMTRACKINFO_H

#include <QWidget>

namespace Ui {
class FormTrackInfo;
}

class FormTrackInfo : public QWidget
{
    Q_OBJECT

public:
    explicit FormTrackInfo(QWidget *parent = nullptr);
    ~FormTrackInfo();

private:
    Ui::FormTrackInfo *ui;
};

#endif // FORMTRACKINFO_H
