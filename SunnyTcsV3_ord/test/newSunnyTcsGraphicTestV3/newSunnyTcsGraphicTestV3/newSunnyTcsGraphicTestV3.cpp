#include "newSunnyTcsGraphicTestV3.h"




newSunnyTcsGraphicTestV3::newSunnyTcsGraphicTestV3(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	_scene = new SunnyTcsGraphicsModel(1,"default");
	
	

	



	

	ui.graphicsView->setScene(_scene);
	_scene->update();

	connect(ui.graphicsView, SIGNAL(mousePress(QPointF)), this, SLOT(onMousePress(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseMove(QPointF)), this, SLOT(onMouseMove(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseRelease(QPointF)), this, SLOT(onMouseRelease(QPointF)));
	connect(ui.graphicsView, SIGNAL(wheelChange(int)), this, SLOT(onWheelChange(int)));

	
}




void newSunnyTcsGraphicTestV3::onMouseMove(QPointF pt)
{
	//qDebug() << "move ( " << pt.x() << " , " << pt.y() << " );";

	qDebug() << "1111";

	
		_scene->update();
	


}

void newSunnyTcsGraphicTestV3::onMouseRelease(QPointF pt)
{
	//qDebug() << "release ( " << pt.x() << " , " << pt.y() << " );";
	

}

void newSunnyTcsGraphicTestV3::onMousePress(QPointF pt)
{
	//craft
	//qDebug() << "press ( " << pt.x() << " , " << pt.y() << " );";
	

}

void newSunnyTcsGraphicTestV3::onWheelChange(int angle)
{
	qDebug() << "1111";
	if (angle > 0) {
		ui.graphicsView->scale(1.2, 1.2);
		
	}
	else if (angle < 0) {
		ui.graphicsView->scale(1 / 1.2, 1 / 1.2);
		
	}

}
