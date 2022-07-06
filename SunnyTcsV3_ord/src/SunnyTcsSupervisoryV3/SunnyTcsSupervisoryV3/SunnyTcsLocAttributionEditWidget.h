#pragma once

#include <QWidget>
#include "ui_SunnyTcsLocAttributionEditWidget.h"
#include "SunnyTcsSupervisoryV3_general.h"

class SunnyTcsLocAttributionEditWidget : public QWidget
{
	Q_OBJECT

public:
	SunnyTcsLocAttributionEditWidget(QWidget *parent = Q_NULLPTR);
	~SunnyTcsLocAttributionEditWidget();

	void init(SunnyTcsGraphicsLocation* loc) {
	
		

	
	}


private:
	Ui::SunnyTcsLocAttributionEditWidget ui;
	SunnyTcsGraphicsLocation* _currentLoc;
};
