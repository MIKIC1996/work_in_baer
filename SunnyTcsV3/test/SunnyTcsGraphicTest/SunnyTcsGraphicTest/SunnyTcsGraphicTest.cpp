#include "SunnyTcsGraphicTest.h"


using namespace graphic;

SunnyTcsGraphicTest::SunnyTcsGraphicTest(QWidget *parent)
	: QMainWindow(parent), _timer()
{
    ui.setupUi(this);

	qint32 cc = 10;
	cc / 0;

	connect(ui.graphicsView, SIGNAL(mousePress(QPointF)), this, SLOT(onMousePress(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseMove(QPointF)), this, SLOT(onMouseMove(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseRelease(QPointF)), this, SLOT(onMouseRelease(QPointF)));
	connect(ui.graphicsView, SIGNAL(wheelChange(int)), this, SLOT(onWheelChange(int)));


	connect(ui.graphicsView_2, SIGNAL(mousePress(QPointF)), this, SLOT(onMousePress(QPointF)));
	connect(ui.graphicsView_2, SIGNAL(mouseMove(QPointF)), this, SLOT(onMouseMove(QPointF)));
	connect(ui.graphicsView_2, SIGNAL(mouseRelease(QPointF)), this, SLOT(onMouseRelease(QPointF)));
	connect(ui.graphicsView_2, SIGNAL(wheelChange(int)), this, SLOT(onWheelChange(int)));

	connect( ui.distr_init_btn  , SIGNAL(clicked()), this, SLOT(onDistrInitBtnClicked()));

	connect(ui.x_mirror_btn, SIGNAL(clicked()), this, SLOT(onMirrorX()));
	connect(ui.y_mirror_btn, SIGNAL(clicked()), this, SLOT(onMirrorY()));
	
	//craft
	_currentCraft = new SunnyTcsCraft_graphic(20000,10000);
	_map = new SunnyTcsMapGraphicsScene(1,200000, 150000 ,10000); //假设为一个长 100 米，宽60米的场地

	

	qreal sceneLen = _map->width() > _map->height() ? _map->width() : _map->height();
	qreal ratio1 = 30* ui.graphicsView->width() / sceneLen;
	ui.graphicsView->scale(ratio1, ratio1);


	ui.graphicsView_2->setScene(_currentCraft);
	ui.graphicsView->setScene(_map);


	//timer
	connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
	_timer.start(200);

}

void SunnyTcsGraphicTest::onMouseMove(QPointF pt)
{
	//qDebug() << "move ( " << pt.x() << " , " << pt.y() << " );";

	if (_currentCraft->getCurrentLinkingLine()) {
		_currentCraft->setCurrentLinkingLineEnd(pt);
	}

	_currentCraft->update();


	if (_map->selectedItems().count() > 0) {
		_map->update_distribution();
		_map->update();
	}
	
	
}

void SunnyTcsGraphicTest::onMouseRelease(QPointF pt)
{
	//qDebug() << "release ( " << pt.x() << " , " << pt.y() << " );";
	if (_currentCraft->getCurrentLinkingLine()) {
		_currentCraft->setCurrentLinkingLineEndRoute(pt);
		
	}
	_currentCraft->update();

	
	_map->update();

}

void SunnyTcsGraphicTest::onMousePress(QPointF pt)
{
	//craft
	//qDebug() << "press ( " << pt.x() << " , " << pt.y() << " );";
	if (ui.routeRBtn->isChecked()) {

		//创建子订单
		_currentCraft->addRoute(pt);
		_currentCraft->setItemsMoveSelectFlags(false);
	}
	else if (ui.linkRBtn->isChecked()) {
		
		_currentCraft->addLinkLine(pt);
		_currentCraft->setItemsMoveSelectFlags(false);
	}
	else  {
		_currentCraft->setItemsMoveSelectFlags(true);
	}

	_currentCraft->update();


	//map
	if (ui.map_pt_crt->isChecked()) {
		_map->addTcsPointItem(pt);
	}
	else if (ui.map_ph_crt->isChecked()) {
		_map->addTcsPathItem(false);
	}
	else if (ui.map_aph_crt->isChecked()) {
		_map->addTcsPathItem(true);
	}
	else if (ui.map_ve_crt->isChecked()) {
		_map->addTcsVehicleItem(pt);
	}
	
}

void SunnyTcsGraphicTest::onWheelChange(int angle)
{
	if (angle > 0){
		ui.graphicsView->scale(1.2, 1.2);
		ui.graphicsView_2->scale(1.2, 1.2);
	}
	else if (angle < 0) {
		ui.graphicsView->scale(1 / 1.2, 1 / 1.2);
		ui.graphicsView_2->scale(1 / 1.2, 1 / 1.2);
	}


}
