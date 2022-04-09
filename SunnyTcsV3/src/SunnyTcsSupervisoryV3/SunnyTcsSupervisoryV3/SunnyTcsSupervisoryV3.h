#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SunnyTcsSupervisoryV3.h"
#include "SunnyTcsSupervisoryV3_general.h"

class SunnyTcsSupervisoryV3 : public QMainWindow
{
    Q_OBJECT
public:
    SunnyTcsSupervisoryV3(QWidget *parent = Q_NULLPTR);

private slots:

	void onWheelChange(int angle)
	{
		if (!_curCraft)return; //ÎÞÄ£ÐÍ×´Ì¬
		if (angle > 0) {
			ui.graphicsView->scale(1.2, 1.2);
		}
		else if (angle < 0) {
			ui.graphicsView->scale(0.85, 0.85);
		}
	}

private:
    Ui::SunnyTcsSupervisoryV3Class ui;
	SunnyTcsGraphicsCraft*  _curCraft;
};




