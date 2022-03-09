#include "SunnyTcsMapEditor.h"


SunnyTcsMapEditor::SunnyTcsMapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_model = new SunnyTcsGraphicsModel(1, "unnamed",150000);
	ui.graphicsView->setScene(_model);

	init();
// 	QWidget* lTitleBar = ui.dockWidget->titleBarWidget();
// 	QWidget* lEmptyWidget = new SunnyTcsTitleBar(ui.dockWidget);
// 	ui.dockWidget->setTitleBarWidget(lEmptyWidget);
// 	delete lTitleBar;
}


SunnyTcsMapEditor::~SunnyTcsMapEditor()
{

}


void SunnyTcsMapEditor::init()
{
	initUi();
	linkSignalsAndSlots();
	initOperation();
	
}


void SunnyTcsMapEditor::updateObjectTreeWidget()
{
	
}


void SunnyTcsMapEditor::addObjectInTreeWidget(qint32 id,QString name, E_SunnyTcsMapObject_type type)
{
	QTreeWidgetItem* treeBranch = nullptr;
	SunnyTcsObjectTreeWidgetItem* newElement = nullptr;
	switch (type)
	{
	case basic::Epoint:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(0);
		break;
	case basic::Epath:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(1);
		break;
	case basic::Elocation:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(3);
		break;
	case basic::Evehicle:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(2);
		break;
	default:
		return;
	}

	for (int i = 0; i < treeBranch->childCount(); ++i) {
		newElement = dynamic_cast<SunnyTcsObjectTreeWidgetItem*>(treeBranch->child(i));
		if (id == newElement->getId()) {
			return;
		}
	}
	new SunnyTcsObjectTreeWidgetItem(id,name, treeBranch);
}


void SunnyTcsMapEditor::delObjectInTreeWidget(qint32 id, E_SunnyTcsMapObject_type type)
{
	QTreeWidgetItem* treeBranch = nullptr;
	SunnyTcsObjectTreeWidgetItem* element = nullptr;
	switch (type)
	{
	case basic::Epoint:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(0);
		break;
	case basic::Epath:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(1);
		break;
	case basic::Elocation:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(3);
		break;
	case basic::Evehicle:
		treeBranch = ui.objectTreeWid->topLevelItem(0)->child(2);
		break;
	default:
		break;
	}

	for (int i = 0; i < treeBranch->childCount(); ++i) {
		element = dynamic_cast<SunnyTcsObjectTreeWidgetItem*>( treeBranch->child(i) );
		if (id != element->getId())continue;
		treeBranch->removeChild(element);
		delete element;
	}
}

void SunnyTcsMapEditor::clearObjectTreeWidget()
{
	QTreeWidgetItem* subLevelItem = nullptr;
	QTreeWidgetItem* sonItem = nullptr;
	ui.objectTreeWid->clear();
	ui.objectTreeWid->addTopLevelItem(new QTreeWidgetItem(ui.objectTreeWid));
	ui.objectTreeWid->topLevelItem(0)->setText(0, "model");
	subLevelItem = new QTreeWidgetItem(ui.objectTreeWid->topLevelItem(0));
	subLevelItem->setText(0,"point");
	subLevelItem = new QTreeWidgetItem(ui.objectTreeWid->topLevelItem(0));
	subLevelItem->setText(0, "path");
	subLevelItem = new QTreeWidgetItem(ui.objectTreeWid->topLevelItem(0));
	subLevelItem->setText(0, "location");
	subLevelItem = new QTreeWidgetItem(ui.objectTreeWid->topLevelItem(0));
	subLevelItem->setText(0, "agv");
}

void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsVehicle * item)
{
	ui.attributeStackWid->setCurrentIndex(3);
	
}

void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsPoint * item)
{

	
	ui.attributeStackWid->setCurrentIndex(0);
	SunnyTcsAgvCoordinate&& rxy = item->getPointCoor();
	ui.pointTableWidget->item(0, 1)->setText(QString::number(rxy._x));
	ui.pointTableWidget->item(1, 1)->setText(QString::number(rxy._y));
	ui.pointTableWidget->item(2, 1)->setText(item->getName());
	qint32 nagaMode = item->getPointNaga();
	QComboBox* cbox = nullptr;
	cbox = qobject_cast<QComboBox*> ( ui.pointTableWidget->cellWidget(3, 1));
	cbox->setCurrentIndex(nagaMode & VEHICLE_NAGA_RUBBON ? 0 : 1);
	cbox = qobject_cast<QComboBox*> (ui.pointTableWidget->cellWidget(4, 1));
	cbox->setCurrentIndex(nagaMode & VEHICLE_NAGA_INERTIA ? 0 : 1);
	cbox = qobject_cast<QComboBox*> (ui.pointTableWidget->cellWidget(5, 1));
	cbox->setCurrentIndex(nagaMode & VEHICLE_NAGA_LASER ? 0 : 1);


}

void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsPath * item)
{
	ui.attributeStackWid->setCurrentIndex(1);
}

void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsLocation * item)
{
	ui.attributeStackWid->setCurrentIndex(2);
}


void SunnyTcsMapEditor::initUi()
{
	//主视图
	ui.graphicsView->scale(0.01, 0.01);


	//设置车型图片 和 选中图片
	SunnyTcsGraphicsVehicle_normal::setImage(":/resource/res/image/agvNormal.png");
	SunnyTcsGraphicsVehicle_normal::setImageSelected(":/resource/res/image/agvNormal_select.png");

	SunnyTcsGraphicsVehicle_mitsubishi_battery::setImage(":/resource/res/image/agvNormal.png");
	SunnyTcsGraphicsVehicle_mitsubishi_battery::setImageSelected(":/resource/res/image/agvNormal_select.png");

	SunnyTcsGraphicsVehicle_daimler_engine::setImage(":/resource/res/image/agvMitsubishiBattery.png");
	SunnyTcsGraphicsVehicle_daimler_engine::setImageSelected(":/resource/res/image/agvMitsubishiBattery_selected.png");

	SunnyTcsGraphicsLocation::setImage(":/resource/res/image/mapLocationIcon.png");
	SunnyTcsGraphicsLocation::setImageSelected(":/resource/res/image/mapLocationIconSelected.png");

	//toolbutton组设置
	_paintTbtnGroup = new QButtonGroup(this);
	_paintTbtnGroup->setExclusive(true);
	_paintTbtnGroup->addButton(ui.paint_default_tbtn);
	_paintTbtnGroup->addButton(ui.paint_move_tbtn);
	_paintTbtnGroup->addButton(ui.paint_delete_tbrn);
	_paintTbtnGroup->addButton(ui.paint_select_rect_tbtn);

	_paintTbtnGroup->addButton(ui.paint_point_tbtn);
	_paintTbtnGroup->addButton(ui.paint_dir_iline_tbrn);
	_paintTbtnGroup->addButton(ui.paint_arch_line_tbtn);
	_paintTbtnGroup->addButton(ui.paint_loc_tbtn);
	_paintTbtnGroup->addButton(ui.paint_vehicle_tbtn);

	//菜单栏
	//工具
	_paintVehicleMenu = new QMenu(this);//添加agv
	for (auto iter : SunnyTcsVehicle::_vehicleSupported) {
		QAction* acn = ui.menuAddVehicleMenu->addAction(iter._description);
		_paintVehicleMenu->addAction(acn);
		_menuAddVehicleAcnList.append(acn);
	}

	//视图
	

	//绘图
	//添加小车按钮菜单初始化
	ui.paint_vehicle_tbtn->setPopupMode(QToolButton::InstantPopup);
	ui.paint_vehicle_tbtn->setMenu(_paintVehicleMenu);;
	

	//对象查看器
	_ObjectTreeWidPointMenu = new QMenu(ui.objectTreeWid);
	



	//属性表
	QTableWidgetItem* item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(1, 1, item);

	item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(2, 1, item);

	for (int i = 0; i < ui.pointTableWidget->rowCount(); ++i) {
		item =ui.pointTableWidget->item(i, 0);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
	}

	QComboBox* cBox = new QComboBox(this);
	cBox->addItem(QSTRING_GBK("支持"));
	cBox->addItem(QSTRING_GBK("不支持"));
	ui.pointTableWidget->setCellWidget(3, 1, cBox);
	cBox = new QComboBox(this);
	cBox->addItem(QSTRING_GBK("支持"));
	cBox->addItem(QSTRING_GBK("不支持"));
	ui.pointTableWidget->setCellWidget(4, 1, cBox);
	cBox = new QComboBox(this);
	cBox->addItem(QSTRING_GBK("支持"));
	cBox->addItem(QSTRING_GBK("不支持"));
	ui.pointTableWidget->setCellWidget(5, 1, cBox);



	//设置样式表
	QFile file(":/resource/res/qss/editor.qss");
	file.open(QIODevice::ReadOnly);
	this->setStyleSheet(file.readAll());
	setDockNestingEnabled(true);
	


}

void SunnyTcsMapEditor::linkSignalsAndSlots()
{
	//graphics view鼠标信号
	connect(ui.graphicsView, SIGNAL(mousePress(QPointF)), this, SLOT(onMousePress(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseMove(QPointF)), this, SLOT(onMouseMove(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseRelease(QPointF)), this, SLOT(onMouseRelease(QPointF)));
	connect(ui.graphicsView, SIGNAL(wheelChange(int)), this, SLOT(onWheelChange(int)));


	//绘图
	connect(ui.paint_default_tbtn, SIGNAL(clicked()), this, SLOT(onPaintDefaultTbtnClicked()));
	connect(ui.paint_move_tbtn, SIGNAL(clicked()), this, SLOT(onPaintMoveTbtnClicked()));
	connect(ui.paint_delete_tbrn, SIGNAL(clicked()), this, SLOT(onPaintDeleteTbtnClicked()));

	connect(ui.paint_point_tbtn, SIGNAL(clicked()), this, SLOT(onPaintPointTbtnClicked()));
	connect(ui.paint_dir_iline_tbrn, SIGNAL(clicked()), this, SLOT(onPaintDirPathTbtnClicked()));
	connect(ui.paint_arch_line_tbtn, SIGNAL(clicked()), this, SLOT(onPaintArchPathTbtnClicked()));
	connect(ui.paint_loc_tbtn, SIGNAL(clicked()), this, SLOT(onPaintLocationTbtnClicked()));
	connect(ui.paint_vehicle_tbtn, SIGNAL(clicked()), this, SLOT(onPaintVehicleTbtnClicked()));


	//菜单栏信号
	//编辑
	connect(ui.undoAcn, SIGNAL(triggered()), this, SLOT(onUndoAcnTriggered()));
	connect(ui.redoAcn, SIGNAL(triggered()), this, SLOT(onRedoAcnTriggered()));

	//工具
	connect(ui.paintPointAcn, SIGNAL(triggered()), this, SLOT( onPaintPointAcnTriggered() ));
	connect(ui.paintDirLineAcn, SIGNAL(triggered()), this, SLOT(onPaintDirLineAcnTriggered()));
	connect(ui.paintArchLineAcn, SIGNAL(triggered()), this, SLOT(onPaintArchLineAcnTriggered()));
	connect(ui.paintLocAcn, SIGNAL(triggered()), this, SLOT(onPaintLocationAcnTriggered()));
	connect(ui.menuDelSelectedAcn, SIGNAL(triggered()), this, SLOT(onMenuDelSelectedAcnTriggered()));
	connect(ui.MenuClearMapAcn,SIGNAL(triggered()), this, SLOT(onMenuClearMapAcnTriggered()));
	for(QAction* acn : _menuAddVehicleAcnList){
		connect(acn, SIGNAL(triggered()), this, SLOT(onMenuAddVehicleAcnTriggered()));
	}
	

	//视图
	connect(ui.toolPanelPaintAcn, SIGNAL(triggered()), this, SLOT(onToolPanelPaintAcnTriggered()));
	connect(ui.toolPanelObjectAcn, SIGNAL(triggered()), this, SLOT(onToolPanelObjectgAcnTriggered()));
	connect(ui.toolPanelAttributeAcn, SIGNAL(triggered()), this, SLOT(onToolPanelAttributeAcnTriggered()));
	connect(ui.toolPanelGroupAcn, SIGNAL(triggered()), this, SLOT(onToolPanelGroupAcnTriggered()));


	//工具栏信号
	//坐标系信号
	connect(ui.XAxisMirrorAcn, SIGNAL(triggered()), this, SLOT(onXAxisAcnTriggered()));
	connect(ui.YAxisMirrorAcn, SIGNAL(triggered()), this, SLOT(onYAxisAcnTriggered()));
	connect(ui.AxisRotateAcn, SIGNAL(triggered()), this, SLOT(onAxisRotateAcnTriggered()));

	//对齐函数
	connect(ui.leftAlignAcn, SIGNAL(triggered()), this, SLOT(onLeftAlignAcnTriggered()));
	connect(ui.rightAlignAcn, SIGNAL(triggered()), this, SLOT(onRightAlignAcnTriggered()));
	connect(ui.topAlignAcn, SIGNAL(triggered()), this, SLOT(onTopAlignAcnTriggered()));
	connect(ui.bottomAlignAcn, SIGNAL(triggered()), this, SLOT(onBottomAlignAcnTriggered()));

	//排布函数
	connect(ui.equalDistributionAcn, SIGNAL(triggered()), this, SLOT(onEqualDistributionAcnTriggered()));
	connect(ui.yEqualDistributionAcn, SIGNAL(triggered()), this, SLOT(onYEqualDistributionAcnTriggered()));

	//对象查看器
	connect(ui.objectTreeWid, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(onObjectTreeWidItemPressed(QTreeWidgetItem*, int)));
	connect(ui.objectTreeWid, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
		this, SLOT(onObjectTreeWidCurrentItemChanged(QTreeWidgetItem * , QTreeWidgetItem * )));
}

void SunnyTcsMapEditor::initOperation()
{
	onPaintDefaultTbtnClicked(); //启动时按默认按钮

	//工具栏视图
	onToolPanelPaintAcnTriggered();
	onToolPanelPaintAcnTriggered();
	onToolPanelAttributeAcnTriggered();
	onToolPanelAttributeAcnTriggered();
	onToolPanelGroupAcnTriggered();
	
	onToolPanelObjectgAcnTriggered();
	onToolPanelObjectgAcnTriggered();
}


void SunnyTcsMapEditor::paintPointWhenMousePressed(QPointF pt)
{
	SunnyTcsGraphicsPoint* ptr = _model->addGraphicsPoint(pt);
	this->addObjectInTreeWidget(ptr->getItemId(), ptr->getName(), ptr->getTag()._eletype);
	//将操作存入撤销重做缓存
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[ptr, this]()->void {
		this->_model->addGraphicsPoint(ptr);
		this->addObjectInTreeWidget(ptr->getItemId(), ptr->getName(), ptr->getTag()._eletype);
	},
		[ptr, this]()->void {
		this->_model->removeGraphicsPoint(ptr);
		this->delObjectInTreeWidget(ptr->getItemId(), ptr->getTag()._eletype);
	},
		[ptr, this]()->void {
		delete ptr;
	}
	);
	_operations.push(userOperation);
}


void SunnyTcsMapEditor::onMouseMove(QPointF pt)
{
	//qDebug() << "move ( " << pt.x() << " , " << pt.y() << " );";

	if (_model->isPaintingPath()) {
		bool isArch = ui.paint_arch_line_tbtn->isChecked();
		_model->updateTempPath(pt, isArch, 1);
	}

	if (_model->isSelecting()) {
		_model->updateSelectAera(pt);
	}
	

	quint64 start = QDateTime::currentMSecsSinceEpoch();
	_model->update();
	qDebug() << "update time " << QDateTime::currentMSecsSinceEpoch() - start;
}


void SunnyTcsMapEditor::onMouseRelease(QPointF pt)
{
	//qDebug() << "release ( " << pt.x() << " , " << pt.y() << " );";

	if (ui.paint_select_rect_tbtn->isChecked()) {
		
		if(_model->isSelecting()) {
			_model->updateSelectAera(pt, true);
		}
	}
}


void SunnyTcsMapEditor::onMousePress(QPointF pt)
{
	//paint面板
	if (ui.paint_default_tbtn->isChecked()) {
		
	}
	else if (ui.paint_move_tbtn->isChecked()) {
		
	}
	else if (ui.paint_delete_tbrn->isChecked()) {
		//当前位置元素设置为选择
		QGraphicsItem* item = _model->itemAt(pt, QTransform());
		if (item) {
			_model->setAllItemSelected(false);
			item->setSelected(true);
			onMenuDelSelectedAcnTriggered();
		}
		
	}
	else if (ui.paint_select_rect_tbtn->isChecked()) {
		if (!_model->isSelecting()) {
			_model->addSelectAera(SunnyTcsGraphicsSelectAera::ERect, pt);
		}
	}
	else if (ui.paint_point_tbtn->isChecked()) {
		paintPointWhenMousePressed(pt);
		
	}
	else if (ui.paint_dir_iline_tbrn->isChecked() || ui.paint_arch_line_tbtn->isChecked()) {
		SunnyTcsGraphicsPath* ptr = nullptr;
		if (!_model->isPaintingPath()) {
			 _model->addGraphicsPath(pt);
		}
		else {
			ptr = _model->updateTempPath(pt, ui.paint_dir_iline_tbrn->isChecked()?  false : true, 2);
			if (!ptr)return;
			this->addObjectInTreeWidget(ptr->getItemId(), ptr->getName(), ptr->getTag()._eletype);
			const SunnyTcsGraphicsPoint* start = dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getStart());
			this->addObjectInTreeWidget(start->getElementId(), start->getName(), start->getTag()._eletype);
			const SunnyTcsGraphicsPoint* ctrl = dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getCtrl());
			if (ctrl) {
				this->addObjectInTreeWidget(ctrl->getElementId(), ctrl->getName(), ctrl->getTag()._eletype);
			}
			const SunnyTcsGraphicsPoint* end = dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getEnd());
			this->addObjectInTreeWidget(end->getElementId(), end->getName(), end->getTag()._eletype);

			//将操作存入撤销重做缓存
			updateTempUserOperationStack();
			SunnyTcsUserInterfaceOperation userOperation(
				[ptr, this]()->void { //重做操作
				this->_model->addGraphicsPath(ptr);
				this->addObjectInTreeWidget(ptr->getItemId(), ptr->getName(), ptr->getTag()._eletype);

			},
				[ptr, this]()->void { //撤销操作
				this->_model->removeGraphicsPath(ptr);
				this->delObjectInTreeWidget(ptr->getItemId(), ptr->getTag()._eletype);

			},
				[ptr, this]()->void {
				delete ptr;
			}
			);
			_operations.push(userOperation);

		}
	}
	else if (ui.paint_loc_tbtn->isChecked()) {
		SunnyTcsGraphicsLocation* ptr = _model->addGraphicsLocation(pt);
		if(ptr) this->addObjectInTreeWidget(ptr->getItemId(), ptr->getName(), ptr->getTag()._eletype);
	}
	else if (ui.paint_vehicle_tbtn->isChecked()) {
		qDebug() << _currentAgvCode._description;
		SunnyTcsGraphicsVehicle* ptr = _model->addGraphicsVehicle(pt,_currentAgvCode);
		if (ptr) this->addObjectInTreeWidget(ptr->getItemId(), ptr->getName(), ptr->getItemTag()._eletype);
	}

}

void SunnyTcsMapEditor::onWheelChange(int angle)
{
	if (angle > 0) {
		ui.graphicsView->scale(1.2, 1.2);
	}
	else if (angle < 0) {
		ui.graphicsView->scale(  0.85, 0.85);
	}
}


//QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemSendsGeometryChanges

void SunnyTcsMapEditor::onPaintDefaultTbtnClicked()
{
	qDebug() << "onPaintDefaultTbtnClicked";
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintMoveTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemSendsGeometryChanges);
	_model->setItemFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable, Epath);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintDeleteTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintPointTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintDirPathTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintArchPathTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintLocationTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}

void SunnyTcsMapEditor::onPaintVehicleTbtnClicked()
{
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


void SunnyTcsMapEditor::onUndoAcnTriggered()
{
	if (_operations.isEmpty()) {
		return;
	}
	_operations.top().undo();
	_tempOperations.push( _operations.pop());

}

void SunnyTcsMapEditor::onRedoAcnTriggered()
{
	if (_tempOperations.isEmpty()) {
		return;
	}
	_tempOperations.top().redo();
	_operations.push(_tempOperations.pop());
}

void SunnyTcsMapEditor::updateTempUserOperationStack()
{
	while (!_tempOperations.isEmpty()) {
		_tempOperations.pop().dropOperation();
	}
	_tempOperations.clear();
}

void SunnyTcsMapEditor::onPaintPointAcnTriggered()
{
	ui.paint_point_tbtn->setChecked(true);
}

void SunnyTcsMapEditor::onPaintDirLineAcnTriggered()
{
	ui.paint_dir_iline_tbrn->setChecked(true);
}

void SunnyTcsMapEditor::onPaintArchLineAcnTriggered()
{
	ui.paint_arch_line_tbtn->setChecked(true);
}

void SunnyTcsMapEditor::onPaintLocationAcnTriggered()
{
	ui.paint_loc_tbtn->setChecked(true);
}

void SunnyTcsMapEditor::onMenuDelSelectedAcnTriggered()
{
	QList<QGraphicsItem*>&& itemsSelected = _model->selectedItems();
	QList<SunnyTcsMapGraphicItem*> pts;

	SunnyTcsMapGraphicItem* item = nullptr;
	E_SunnyTcsMapObject_type type = Enotype;
	qint32 id;
	bool success = false;
	
	for (auto ptr : itemsSelected) {
		item = dynamic_cast<SunnyTcsMapGraphicItem*>(ptr);
		Q_ASSERT(item);
		if (item->getItemTag()._eletype == Epoint) {
			pts.append(item);
			continue;
		}
		type = item->getItemTag()._eletype;
		id = item->getItemId();
		success = _model->deleteGraphicsItem(item);
		success ? delObjectInTreeWidget(id, type) : 1;
	}

	for (auto ptr : pts) {
		item = dynamic_cast<SunnyTcsMapGraphicItem*>(ptr);
		Q_ASSERT(item);
		type = item->getItemTag()._eletype;
		id = item->getItemId();
		success = _model->deleteGraphicsItem(item);
		success ? delObjectInTreeWidget(id, type) : 1;
	}
	_model->update();

}

void SunnyTcsMapEditor::onMenuClearMapAcnTriggered()
{
	_model->setAllItemSelected(true);
	onMenuDelSelectedAcnTriggered();
}

void SunnyTcsMapEditor::onMenuAddVehicleAcnTriggered()
{
	for (int i = 0; i < _menuAddVehicleAcnList.count(); ++i) {
		if (sender() == _menuAddVehicleAcnList.at(i)) {
			_currentAgvCode = SunnyTcsVehicle::_vehicleSupported.at(i);
			ui.paint_vehicle_tbtn->setChecked(true);
			break;
		}
	}
}


void SunnyTcsMapEditor::onToolPanelPaintAcnTriggered()
{
	if (ui.paintDwid->isHidden() ){
		ui.paintDwid->show();
		ui.toolPanelPaintAcn->setIcon(QIcon( ":/resource/res/image/panel_show.png" ));
	}
	else {
		ui.paintDwid->hide();
		ui.toolPanelPaintAcn->setIcon(QIcon());
	}
}

void SunnyTcsMapEditor::onToolPanelObjectgAcnTriggered()
{
	if (ui.objectDwid->isHidden()) {
		ui.objectDwid->show();
		ui.toolPanelObjectAcn->setIcon(QIcon(":/resource/res/image/panel_show.png"));
	}
	else {
		ui.objectDwid->hide();
		ui.toolPanelObjectAcn->setIcon(QIcon());
	}
}


void SunnyTcsMapEditor::onToolPanelAttributeAcnTriggered()
{
	if (ui.attributeDwid->isHidden()) {
		ui.attributeDwid->show();
		ui.toolPanelAttributeAcn->setIcon(QIcon(":/resource/res/image/panel_show.png"));
	}
	else {
		ui.attributeDwid->hide();
		ui.toolPanelAttributeAcn->setIcon(QIcon());
	}
}

void SunnyTcsMapEditor::onToolPanelGroupAcnTriggered()
{
	if (ui.groupDwid->isHidden()) {
		ui.groupDwid->show();
		ui.toolPanelGroupAcn->setIcon(QIcon(":/resource/res/image/panel_show.png"));
	}
	else {
		ui.groupDwid->hide();
		ui.toolPanelGroupAcn->setIcon(QIcon());
	}
}

void SunnyTcsMapEditor::onXAxisAcnTriggered()
{
	_model->xAxisMirror();
	_model->update();
}

void SunnyTcsMapEditor::onYAxisAcnTriggered()
{
	_model->yAxisMirror();
	_model->update();
}

void SunnyTcsMapEditor::onAxisRotateAcnTriggered()
{
	_model->rotateAxis();
	_model->update();
}

void SunnyTcsMapEditor::onLeftAlignAcnTriggered()
{
	_model->leftAlign();
	_model->update();
}

void SunnyTcsMapEditor::onRightAlignAcnTriggered()
{
	_model->rightAlign();
	_model->update();
}

void SunnyTcsMapEditor::onTopAlignAcnTriggered()
{
	_model->topAlign();
	_model->update();
}

void SunnyTcsMapEditor::onBottomAlignAcnTriggered()
{
	_model->bottomAlign();
	_model->update();
}

void SunnyTcsMapEditor::onEqualDistributionAcnTriggered()
{
	_model->xEqualDistributionOfPoints();
}

void SunnyTcsMapEditor::onYEqualDistributionAcnTriggered()
{
	_model->yEqualDistributionOfPoints();
}



void SunnyTcsMapEditor::onObjectTreeWidItemPressed(QTreeWidgetItem * item, int column)
{
	
	if (qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
	{
		qDebug() << "pressed";
// 		QMenu*menu = new QMenu(ui->treeWidget);
// 		if (pressedItem->text(column) == "A")   //在我的QTreeWidget对象中，有三个QTreeWidgetItem对象，其中有一个内容为“Ａ”
// 		{
// 			menu->addAction(test);
// 			menu->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
// 		}
		_ObjectTreeWidPointMenu->exec(QCursor::pos());
	}

}



void SunnyTcsMapEditor::onObjectTreeWidCurrentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
	_model->setAllItemSelected(false);
	SunnyTcsObjectTreeWidgetItem* cur = dynamic_cast<SunnyTcsObjectTreeWidgetItem*> (current);
	if (!cur)return;
	QString par = cur->parent()->text(0);
	if (par == "point") {
		_model->getPoints().value(cur->getId())->setSelected(true);
		updateAttribute(_model->getPoints().value(cur->getId()));
	}
	else if (par == "path") {
		_model->getPaths().value(cur->getId())->setSelected(true);
	}
	else if (par == "location") {
		_model->getLocations().value(cur->getId())->setSelected(true);
	}
	else if (par == "agv") {
		_model->getVehicles().value(cur->getId())->setSelected(true);
	}
}

void SunnyTcsMapEditor::onAttributeOkTbtnClicked()
{
	if (ui.attributeStackWid->currentIndex() == 0)//point
	{
	}

}

void SunnyTcsMapEditor::onAttributeFlushClicked()
{
}
