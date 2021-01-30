#include "sunnytcsitemlinkdig.h"
#include "ui_sunnytcsitemlinkdig.h"

SunnyTcsItemLinkDig::SunnyTcsItemLinkDig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SunnyTcsItemLinkDig)
{
    ui->setupUi(this);
}

SunnyTcsItemLinkDig::~SunnyTcsItemLinkDig()
{
    delete ui;
}
