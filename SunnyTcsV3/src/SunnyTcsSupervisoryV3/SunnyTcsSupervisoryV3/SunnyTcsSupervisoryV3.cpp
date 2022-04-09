#include "SunnyTcsSupervisoryV3.h"



SunnyTcsSupervisoryV3::SunnyTcsSupervisoryV3(QWidget *parent)
    : QMainWindow(parent)
{

	

    ui.setupUi(this);

	_curCraft = new SunnyTcsGraphicsCraft("unnamed");

	_curCraft->appendNewSonCraft(QPointF(0,0));

	ui.graphicsView->setScene(_curCraft);

	this->setDockNestingEnabled(true);


	connect(ui.graphicsView, SIGNAL(wheelChange(int)), this, SLOT(onWheelChange(int) ));
}
