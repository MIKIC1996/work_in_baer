#pragma once


#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_SunnyTcsGraphicTest.h"

#include "stafix.h"
#include "SunnyTcsRoute_graphic.h"
#include "SunnyTcsCraftGraphicsScene.h"

#include "SunnyTcsMapGraphicsScene.h"

using namespace graphic;

class SunnyTcsGraphicTest : public QMainWindow
{
    Q_OBJECT

public:
    SunnyTcsGraphicTest(QWidget *parent = Q_NULLPTR);


private slots :
	
	void onMirrorX() {
		_map->mirrorX();
	}

	void onMirrorY() {
		_map->mirrorY();
	}

	void onRotate() {
		_map->rotateCoordinateSystem();
	}

	void onMouseMove(QPointF pt);

	void onMouseRelease(QPointF pt);

	void onMousePress(QPointF pt);

	void onWheelChange(int angle);

	void onTimeOut() {
		_currentCraft->update();
		_map->update();
	}

	void onDistrInitBtnClicked() {
		qDebug() << 111;
		_map->init_distribution();
	}

protected:
    Ui::SunnyTcsGraphicTestClass ui;

	SunnyTcsMapGraphicsScene* _map;
	SunnyTcsCraft_graphic* _currentCraft;

	//SunnyTcsCraftGraphicsScene* _scene;
	QTimer _timer;

};
