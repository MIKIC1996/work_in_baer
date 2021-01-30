#ifndef SUNNYTCSITEMLINKDIG_H
#define SUNNYTCSITEMLINKDIG_H

#include <QWidget>

namespace Ui {
class SunnyTcsItemLinkDig;
}

class SunnyTcsItemLinkDig : public QWidget
{
    Q_OBJECT

public:
    explicit SunnyTcsItemLinkDig(QWidget *parent = 0);
    ~SunnyTcsItemLinkDig();

private:
    Ui::SunnyTcsItemLinkDig *ui;
};

#endif // SUNNYTCSITEMLINKDIG_H
