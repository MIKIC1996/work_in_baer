#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_newSunnyTcsGraphicTestV3.h"
#include "SunnyTcsGraphicsCoorSys.h"

#include "SunnyTcsGraphicsPoint.h"
#include "SunnyTcsGraphicsPath.h"
#include "SunnyTcsGraphicsLocation.h"
#include "SunnyTcsGraphicsModel.h"


class newSunnyTcsGraphicTestV3 : public QMainWindow
{
    Q_OBJECT

public:
    newSunnyTcsGraphicTestV3(QWidget *parent = Q_NULLPTR);



private slots :
	void onMouseMove(QPointF pt);

	void onMouseRelease(QPointF pt);

	void onMousePress(QPointF pt);

	void onWheelChange(int angle);


private:
    Ui::newSunnyTcsGraphicTestV3Class ui;

	
	SunnyTcsGraphicsModel* _scene;
	
	
};
