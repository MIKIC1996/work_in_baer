#pragma once

#include <QWidget>
#include "ui_SunnyTcsLocationEditWidget.h"
#include "SunnyTcsSupervisoryV3_general.h"







class SunnyTcsLocationEditWidget : public QWidget
{
	Q_OBJECT

public:
	SunnyTcsLocationEditWidget(QWidget *parent = Q_NULLPTR);
	~SunnyTcsLocationEditWidget();

private:
	Ui::SunnyTcsLocationEditWidget ui;
};
