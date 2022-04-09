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
	_locEditWidget = new SunnyTcsLocationEditWidget(parent);
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


void SunnyTcsMapEditor::addObjectInTreeWidget(const SunnyTcsMapGraphicItem* item)
{
	if (!item)return;
	QTreeWidgetItem* treeBranch = nullptr;
	SunnyTcsObjectTreeWidgetMapItem* newElement = nullptr;
	switch (item->getItemTag()._eletype)
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
		newElement = dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*>(treeBranch->child(i));
		if (item->getItemId() == newElement->getItem()->getItemId()) {
			return;
		}
	}
	new SunnyTcsObjectTreeWidgetMapItem(item, treeBranch);
}



void SunnyTcsMapEditor::delObjectInTreeWidget(const SunnyTcsMapGraphicItem* item)
{
	QTreeWidgetItem* treeBranch = nullptr;
	SunnyTcsObjectTreeWidgetMapItem* element = nullptr;
	switch (item->getItemTag()._eletype)
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
		element = dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*>( treeBranch->child(i) );
		if (item->getItemId() != element->getItem()->getItemId())continue;
		treeBranch->removeChild(element);
		delete element;
	}
}



void SunnyTcsMapEditor::setCurrenctTreeItemInTreeWidget(const SunnyTcsMapGraphicItem * item)
{
	if (!item)return;
	if (item->getItemTag()._eletype == Epoint) {
		QTreeWidgetItem* pointItem = ui.objectTreeWid->topLevelItem(0)->child(0);
		for (int i = 0; i < pointItem->childCount(); ++i) {
			if( dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*>(pointItem->child(i))->getItem() == item){
				ui.objectTreeWid->setCurrentItem(pointItem->child(i));
				_currentEditingItem = const_cast<SunnyTcsMapGraphicItem*>(item);
				onObjectTreeWidCurrentItemChanged(pointItem->child(i),nullptr);
				return;
			}
		}
	}
	else if (item->getItemTag()._eletype == Epath) {
		QTreeWidgetItem* pathItem = ui.objectTreeWid->topLevelItem(0)->child(1);
		for (int i = 0; i < pathItem->childCount(); ++i) {
			if (dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*>(pathItem->child(i))->getItem() == item) {
				ui.objectTreeWid->setCurrentItem(pathItem->child(i));
				_currentEditingItem = const_cast<SunnyTcsMapGraphicItem*>(item);
				onObjectTreeWidCurrentItemChanged(pathItem->child(i), nullptr);
				return;
			}
		}
	}
	else if (item->getItemTag()._eletype == Evehicle) {
		QTreeWidgetItem* veItem = ui.objectTreeWid->topLevelItem(0)->child(2);
		for (int i = 0; i < veItem->childCount(); ++i) {
			if (dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*>(veItem->child(i))->getItem() == item) {
				ui.objectTreeWid->setCurrentItem(veItem->child(i));
				_currentEditingItem = const_cast<SunnyTcsMapGraphicItem*>(item);
				onObjectTreeWidCurrentItemChanged(veItem->child(i), nullptr);
				return;
			}
		}
	}
	else if (item->getItemTag()._eletype == Elocation) {
		QTreeWidgetItem* locItem = ui.objectTreeWid->topLevelItem(0)->child(3);
		for (int i = 0; i < locItem->childCount(); ++i) {
			if (dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*>(locItem->child(i))->getItem() == item) {
				ui.objectTreeWid->setCurrentItem(locItem->child(i));
				_currentEditingItem = const_cast<SunnyTcsMapGraphicItem*>(item);
				onObjectTreeWidCurrentItemChanged(locItem->child(i), nullptr);
				return;
			}
		}
	}
}



/*
* function: ��ʼ�����������Ƴ�����Ԫ������
* param : void
* return : void
*/
void SunnyTcsMapEditor::initObjectTreeWidget()
{
	QTreeWidgetItem* subLevelItem = nullptr;
	QTreeWidgetItem* sonItem = nullptr;
	
	for (int i = 0; i < 4; ++i) {
		subLevelItem = (ui.objectTreeWid->topLevelItem(0)->child(i));
		while( subLevelItem->childCount()>0) {
			sonItem = subLevelItem->child(0);
			subLevelItem->removeChild(sonItem);
			delete sonItem;
		}
	}
}


/*
* function: ���ݶ���������ʾ ���Ա༭����
* param[1] : ͼ�ζ���ָ��
* return : void
*/
void SunnyTcsMapEditor::updateAttribute(SunnyTcsMapGraphicItem * item)
{
	Q_ASSERT(item);//��������ָ��
	switch (item->getItemTag()._eletype)
	{
	case basic::Epoint:
		updateAttribute(dynamic_cast<SunnyTcsGraphicsPoint*>(item));
		break;
	case basic::Epath:
		updateAttribute(dynamic_cast<SunnyTcsGraphicsPath*>(item));
		break;
	case basic::Elocation:
		updateAttribute(dynamic_cast<SunnyTcsGraphicsLocation*>(item));
		break;
	case basic::Evehicle:
		updateAttribute(dynamic_cast<SunnyTcsGraphicsVehicle*>(item));
		break;
	default:
		Q_ASSERT(0);//��֧�ֵ�����
		return;
	}
	_currentEditingItem = item;
}


/*
* function: ��ʾ�����Ա༭���ڣ����������������
* param[1] : ͼ�γ�����ָ��
* return : void
*/
void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsVehicle * item)
{
	Q_ASSERT(item);
	ui.attributeStackWid->setCurrentIndex(3);
	ui.vehicleTableWidget->item(0, 1)->setText(item->getName());
	ui.vehicleTableWidget->item(1, 1)->setText(item->getVehicleIp());
	ui.vehicleTableWidget->item(2, 1)->setText(QString::number(item->getVehiclePort()));
	//ui.vehicleTableWidget->item(3, 1)->setText("");
	ui.vehicleTableWidget->item(4, 1)->setText(QString::number(item->getLadarRadius()));
}


/*
* function: ��ʾ�����Ա༭���ڣ����������������
* param[1] : ͼ�ε����ָ��
* return : void
*/
void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsPoint * item)
{
	Q_ASSERT(item);
	ui.attributeStackWid->setCurrentIndex(0);
	SunnyTcsAgvCoordinate&& rxy = item->getPointCoor();
	ui.pointTableWidget->item(0, 1)->setText(item->getName());
	ui.pointTableWidget->item(1, 1)->setText(QString::number(rxy._x));
	ui.pointTableWidget->item(2, 1)->setText(QString::number(rxy._y));
	qint32 nagaMode = item->getPointNaga();
	QComboBox* cbox = nullptr;
	cbox = qobject_cast<QComboBox*> ( ui.pointTableWidget->cellWidget(3, 1));
	cbox->setCurrentIndex(nagaMode & VEHICLE_NAGA_RUBBON ? 0 : 1);
	cbox = qobject_cast<QComboBox*> (ui.pointTableWidget->cellWidget(4, 1));
	cbox->setCurrentIndex(nagaMode & VEHICLE_NAGA_INERTIA ? 0 : 1);
	cbox = qobject_cast<QComboBox*> (ui.pointTableWidget->cellWidget(5, 1));
	cbox->setCurrentIndex(nagaMode & VEHICLE_NAGA_LASER ? 0 : 1);
	ui.pointTableWidget->item(6, 1)->setText(QString::number(item->getPointAbsPos()));
	//ui.pointTableWidget->item(7, 1)->setText(QString::number());
}


/*
* function: ��ʾ·�����Ա༭���ڣ����������������
* param[1] : ͼ��·������ָ��
* return : void
*/
void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsPath * item)
{
	Q_ASSERT(item);
	QString startName = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getStart())->getName();
	QString endName = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getEnd())->getName();
	QString ctrlName;
	if (item->getCtrl()) {
		ctrlName = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getCtrl())->getName();
	}
	ui.attributeStackWid->setCurrentIndex(1);
	ui.pathTableWidget->item(0, 1)->setText(item->getName());
	QComboBox* cbox = nullptr;
	cbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(1, 1));
	cbox->setCurrentIndex(item->isSupportPositive()? 0 : 1);
	cbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(2, 1));
	cbox->setCurrentIndex(item->isSupportNegative()? 0 : 1);
	ui.pathTableWidget->item(3, 1)->setText(QString::number(item->getPositiveSpeed()));
	ui.pathTableWidget->item(4, 1)->setText(QString::number(item->getNegativeSpeed()));
	cbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(5, 1));
	cbox->setCurrentIndex(item->isScanAeraActived() ? 0 : 1);
	ui.pathTableWidget->item(6, 1)->setText(QString::number(item->getPositiveScanAera()));
	ui.pathTableWidget->item(7, 1)->setText(QString::number(item->getNegativeScanAera()));
	//���Ƶ�
	cbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(8, 1));
	for (int i = 0; i < cbox->count(); ++i) {
		if (cbox->itemText(i) == startName) {
			cbox->setCurrentIndex(i);
			break;
		}
	}
	cbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(9, 1));
	for (int i = 0; i < cbox->count(); ++i) {
		if (cbox->itemText(i) == endName) {
			cbox->setCurrentIndex(i);
			break;
		}
	}
	cbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(10, 1));
	for (int i = 0; i < cbox->count(); ++i) {
		if (cbox->itemText(i) == ctrlName) {
			cbox->setCurrentIndex(i);
			break;
		}
		cbox->setCurrentIndex(0);
	}
}


/*
* function: ��ʾ��λ���Ա༭���ڣ����������������
* param[1] : ͼ�ι�λ����ָ��
* return : void
*/
void SunnyTcsMapEditor::updateAttribute(SunnyTcsGraphicsLocation * item)
{
	Q_ASSERT(item);
	QVector<E_ARG_TYPE> sptParams = item->getParamsType();
	qint32 sptParamsCount = sptParams.count();
	qint32 paramRowCount = ui.locationTableWidget->rowCount()-2;
	while ( paramRowCount < sptParamsCount) {
		ui.locationTableWidget->setRowCount(ui.locationTableWidget->rowCount() + 1);
		ui.locationTableWidget->setItem(ui.locationTableWidget->rowCount() - 1, 0,
			new QTableWidgetItem( QSTRING_GBK("����%1").arg( QString::number( ui.locationTableWidget->rowCount() - 2) ) ));
		QComboBox* cbox = new QComboBox(this);
		for (auto typeDecp : SunnyTcsAction::supportArgTyps.values()) {
			cbox->addItem(typeDecp);
		}
		ui.locationTableWidget->setCellWidget(ui.locationTableWidget->rowCount() - 1, 1, cbox);
		++paramRowCount;
	}

	while (paramRowCount > sptParamsCount) {
		delete ui.locationTableWidget->item(ui.locationTableWidget->rowCount() - 1, 0);
		delete qobject_cast<QComboBox*>(ui.locationTableWidget->cellWidget(ui.locationTableWidget->rowCount() - 1, 1));
		ui.locationTableWidget->setRowCount(ui.locationTableWidget->rowCount() - 1);
		--paramRowCount;
	}

	int startIndex = 2;
	for (E_ARG_TYPE ty : sptParams) {
		qint32 tarIndex = SunnyTcsAction::supportArgTyps.keys().indexOf(ty);
		qobject_cast<QComboBox*>(ui.locationTableWidget->cellWidget(startIndex, 1))->setCurrentIndex(tarIndex);
		++startIndex;
	}

	ui.attributeStackWid->setCurrentIndex(2);
	ui.locationTableWidget->item(0, 1)->setText(item->getName());
	const SunnyTcsGraphicsPoint* lpt = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getLinkPointPtr());
	Q_ASSERT(lpt); // ���������û�й�����Ĺ�λ
	QComboBox* cbox = dynamic_cast<QComboBox*>(ui.locationTableWidget->cellWidget(1, 1));
	Q_ASSERT(cbox); //�������ᵼ�¸��ж�
	for (int i = 0; i < cbox->count(); ++i) {
		if (cbox->itemText(i) == lpt->getName()) {
			cbox->setCurrentIndex(i);
			return;
		}
	}
	Q_ASSERT(0); //û�д�Cbox���ҵ����ϵĵ��˵��cbox����ͬ��������
}


/*
* function: ��ʾģ�����Ա༭���ڣ����������������
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::updateModelAttribute()
{
	if (!_model)return; // ���ģ�Ͳ����ڣ��򷵻أ����ж�
	ui.attributeStackWid->setCurrentIndex(4);
	ui.modelTableWidget->item(0, 1)->setText(_model->getName());
	ui.modelTableWidget->item(1, 1)->setText(QString::number(_model->getWidth()));
	ui.modelTableWidget->item(2, 1)->setText(QString::number(_model->getHeight()));
	ui.modelTableWidget->item(3, 1)->setText(QString::number(_model->getResolution()));
	QComboBox* cbox = qobject_cast<QComboBox*>(ui.modelTableWidget->cellWidget(4, 1));
	Q_ASSERT(cbox);
	cbox->setCurrentIndex(_model->isAutoTrafficControlOpen() ? 0 : 1);
	_currentEditingItem = nullptr;
}



/*
* function: Ԥ��
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::updatePointsGroupAttribute()
{
}


/*
* function: Ԥ��
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::updatePathsGroupAttribute()
{
}


/*
* function: Ԥ��
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::updateLocationGroupAttribute()
{
}


/*
* function: Ԥ��
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::setModel(const QJsonObject & mapJson)
{
}


/*
* function: ����һ����ģ��
* param[1] : ��ģ��ָ�룬�ú����������� ģ�͵�json�����л�;
* return : void
*/
void SunnyTcsMapEditor::setModel(SunnyTcsGraphicsModel * model)
{
	if (_model) { //��ǰģ�ʹ��ڣ��򽫵�ǰģ���Ƴ�
		removeCurrentModel();
	}
	_model = model;
	ui.graphicsView->setScene(_model);
	const QHash<qint32, SunnyTcsGraphicsPoint*>& pts = _model->getPoints();
	for (auto ptr : pts) {
		addObjectInTreeWidget(ptr);
	}
	const QHash<qint32, SunnyTcsGraphicsPath*> & phs = _model->getPaths();
	for (auto ptr : phs) {
		addObjectInTreeWidget(ptr);
	}
	const QHash<qint32, SunnyTcsGraphicsLocation*>& locs = _model->getLocations();
	for (auto ptr : locs) {
		addObjectInTreeWidget(ptr);
	}
	const QHash<qint32, SunnyTcsGraphicsVehicle*>& ves = _model->getVehicles();
	for (auto ptr : ves) {
		addObjectInTreeWidget(ptr);
	}
	enableAllButtion();
	ui.menuBar->setEnabled(true);//�˵��� 
	ui.mainToolBar->setEnabled(true);//������
	updatePointInfoWhenEditPoint();
	_model->update();
}


/*
* function: ����ǰ��ģ���Ƴ��������ͷŸ�ģ�ͣ�����Ҫ��ս����ϵ����ݣ����н������еĹ��߰�ť
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::removeCurrentModel()
{
	ui.graphicsView->setScene(nullptr);
	disableAllButtion(); //���û�ͼ��ť
	ui.menuBar->setEnabled(false);//�˵��� ����
	ui.mainToolBar->setEnabled(false);//������ ����
	initObjectTreeWidget(); //��ʼ��������
	ui.attributeStackWid->setCurrentIndex(5);//���Դ����õ���ҳ
	_currentEditingItem = nullptr;
	//������еĳ�����������
	_operations.clear();
	_tempOperations.clear();
}



/*
* function: ��ʼ��UI
* param[1] : void
* return : void
*/
void SunnyTcsMapEditor::initUi()
{
	//����ͼ
	ui.graphicsView->scale(0.01, 0.01);

	//���ó���ͼƬ �� ѡ��ͼƬ
	SunnyTcsGraphicsVehicle_normal::setImage(":/resource/res/image/agvNormal.png");
	SunnyTcsGraphicsVehicle_normal::setImageSelected(":/resource/res/image/agvNormal_select.png");

	SunnyTcsGraphicsVehicle_mitsubishi_battery::setImage(":/resource/res/image/agvMitshubishi.png");
	SunnyTcsGraphicsVehicle_mitsubishi_battery::setImageSelected(":/resource/res/image/agvMitshubishi_selected.png");

	SunnyTcsGraphicsVehicle_daimler_engine::setImage(":/resource/res/image/agvMitsubishiBattery.png");
	SunnyTcsGraphicsVehicle_daimler_engine::setImageSelected(":/resource/res/image/agvMitsubishiBattery_selected.png");

	SunnyTcsGraphicsLocation::setImage(":/resource/res/image/mapLocationIcon2.png");
	SunnyTcsGraphicsLocation::setImageSelected(":/resource/res/image/mapLocationIcon2Selected.png");

	//toolbutton������
	_paintTbtnGroup = new QButtonGroup(this);
	_paintTbtnGroup->setExclusive(true);
	_paintTbtnGroup->addButton(ui.paint_default_tbtn);
	_paintTbtnGroup->addButton(ui.paint_move_tbtn);
	_paintTbtnGroup->addButton(ui.paint_delete_tbrn);
	_paintTbtnGroup->addButton(ui.paint_select_rect_tbtn);
	_paintTbtnGroup->addButton(ui.paint_cancel_select_tbtn);
	_paintTbtnGroup->addButton(ui.paint_move_cs_tbtn);

	_paintTbtnGroup->addButton(ui.paint_point_tbtn);
	_paintTbtnGroup->addButton(ui.paint_dir_iline_tbrn);
	_paintTbtnGroup->addButton(ui.paint_arch_line_tbtn);
	_paintTbtnGroup->addButton(ui.paint_loc_tbtn);
	_paintTbtnGroup->addButton(ui.paint_vehicle_tbtn);

	//�˵���
	//����
	_paintVehicleMenu = new QMenu(this);//�����֧�ֵ� agv���� ��menu�У����menu�ֹ������˻�ͼ���ߺͲ˵�����
	for (auto iter : I_SunnyTcsVehicleFactory::_vehicleSupported) { //֧�ֵ�AGV������Ϣ����� ��I_SunnyTcsVehicleFactory ��̬ȫ�ֱ�����
		QAction* acn = ui.menuAddVehicleMenu->addAction(iter._description); //ֻҪ��ȡ��������Ϣ����
		_paintVehicleMenu->addAction(acn);
		_menuAddVehicleAcnList.append(acn);
	}
	//��ͼ
	

	//��ͼ
	//���С����ť�˵���ʼ��
	ui.paint_vehicle_tbtn->setPopupMode(QToolButton::InstantPopup);
	ui.paint_vehicle_tbtn->setMenu(_paintVehicleMenu);;
	

	//����鿴��
	_ObjectTreeWidPointMenu = new QMenu(ui.objectTreeWid);
	QAction* buildNewGroupAcn = _ObjectTreeWidPointMenu->addAction(QSTRING_GBK("��������"));
	_objectTreeActionList.append(buildNewGroupAcn);

	ui.objectTreeWid->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	ui.objectTreeWid->verticalScrollBar()->hide();
	ui.objectTreeWid->horizontalScrollBar()->hide();

	//���Ա�
	initPointAttributionTable(); //��ʼ����ر�
	initPathAttributionTable();
	initLocationAttributionTable();
	initVehicleAttributionTable();
	initModelAttributionTable();

	//״̬����ʼ��
	_trackCbox = new QCheckBox(ui.statusBar);
	_trackCbox->setStyleSheet(" QCheckBox{color : rgb(255,255,255); } ");
	_trackCbox->setText(QSTRING_GBK( "��������   "));
	ui.statusBar->addPermanentWidget(_trackCbox);

	//������ʽ��
	QFile file(":/resource/res/qss/editor.qss");
	file.open(QIODevice::ReadOnly);
	this->setStyleSheet(file.readAll());
	file.close();
	setDockNestingEnabled(true);
}


/*
	function:�Ե����Ա���г�ʼ��
	param[1] : void;
	return : void;
*/
void SunnyTcsMapEditor::initPointAttributionTable()
{
	ui.pointTableWidget->verticalScrollBar()->hide();
	ui.pointTableWidget->horizontalScrollBar()->hide();
	ui.pointTableWidget->horizontalHeader()->setHidden(false);
	ui.pointTableWidget->verticalHeader()->setHidden(false);
	QTableWidgetItem* item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(1, 1, item);

	item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(2, 1, item);

	for (int i = 0; i < ui.pointTableWidget->rowCount(); ++i) {
		item = ui.pointTableWidget->item(i, 0);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
	}

	QComboBox* cBox = new QComboBox(this);
	cBox->addItem(QSTRING_GBK("֧��"));
	cBox->addItem(QSTRING_GBK("��֧��"));
	ui.pointTableWidget->setCellWidget(3, 1, cBox);
	cBox = new QComboBox(this);
	cBox->addItem(QSTRING_GBK("֧��"));
	cBox->addItem(QSTRING_GBK("��֧��"));
	ui.pointTableWidget->setCellWidget(4, 1, cBox);
	cBox = new QComboBox(this);
	cBox->addItem(QSTRING_GBK("֧��"));
	cBox->addItem(QSTRING_GBK("��֧��"));
	ui.pointTableWidget->setCellWidget(5, 1, cBox);

	item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(6, 1, item);
	item = new QTableWidgetItem("");
	ui.pointTableWidget->setItem(7, 1, item);

}



/*
function:��·�����Ա���г�ʼ��
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::initPathAttributionTable()
{
	ui.pathTableWidget->verticalScrollBar()->hide();
	ui.pathTableWidget->horizontalScrollBar()->hide();

	ui.pathTableWidget->horizontalHeader()->setHidden(false);
	ui.pathTableWidget->verticalHeader()->setHidden(false);

	ui.pathTableWidget->setItem(0, 1, new QTableWidgetItem(""));
	QComboBox* supportForwardDirection = new QComboBox(this);
	supportForwardDirection->addItem(QSTRING_GBK("֧��"));
	supportForwardDirection->addItem(QSTRING_GBK("��֧��"));
	ui.pathTableWidget->setCellWidget(1, 1, supportForwardDirection);
	QComboBox* supportBackDirection = new QComboBox(this);
	supportBackDirection->addItem(QSTRING_GBK("֧��"));
	supportBackDirection->addItem(QSTRING_GBK("��֧��"));
	ui.pathTableWidget->setCellWidget(2, 1, supportBackDirection);
	ui.pathTableWidget->setItem(3, 1, new QTableWidgetItem(""));
	ui.pathTableWidget->setItem(4, 1, new QTableWidgetItem(""));
	QComboBox* activeScanAera = new QComboBox(this);
	activeScanAera->addItem(QSTRING_GBK("֧��"));
	activeScanAera->addItem(QSTRING_GBK("��֧��"));
	ui.pathTableWidget->setCellWidget(5, 1, activeScanAera);
	ui.pathTableWidget->setItem(6, 1, new QTableWidgetItem(""));
	ui.pathTableWidget->setItem(7, 1, new QTableWidgetItem(""));
	QComboBox* startPts = new QComboBox(this);
	ui.pathTableWidget->setCellWidget(8, 1, startPts);
	QComboBox* endPts = new QComboBox(this);
	ui.pathTableWidget->setCellWidget(9, 1, endPts);
	QComboBox* ctrlPts = new QComboBox(this);
	ui.pathTableWidget->setCellWidget(10, 1, ctrlPts);
}


/*
function:�Թ�λ���Ա���г�ʼ��
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::initLocationAttributionTable()
{
	ui.locationTableWidget->verticalScrollBar()->hide();
	ui.locationTableWidget->horizontalScrollBar()->hide();

	ui.locationTableWidget->horizontalHeader()->setHidden(false);
	ui.locationTableWidget->verticalHeader()->setHidden(false);

	ui.locationTableWidget->setItem(0, 1, new QTableWidgetItem(""));
	
	QComboBox* pts = new QComboBox(this);
	ui.locationTableWidget->setCellWidget(1, 1, pts);
}


/*
function:�Գ������Ա���г�ʼ��
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::initVehicleAttributionTable()
{
	ui.vehicleTableWidget->verticalScrollBar()->hide();
	ui.vehicleTableWidget->horizontalScrollBar()->hide();

	ui.vehicleTableWidget->horizontalHeader()->setHidden(false);
	ui.vehicleTableWidget->verticalHeader()->setHidden(false);

	ui.vehicleTableWidget->setItem(0, 1, new QTableWidgetItem(""));
	ui.vehicleTableWidget->setItem(1, 1, new QTableWidgetItem(""));
	ui.vehicleTableWidget->setItem(2, 1, new QTableWidgetItem(""));
	ui.vehicleTableWidget->setItem(3, 1, new QTableWidgetItem(""));
	ui.vehicleTableWidget->setItem(4, 1, new QTableWidgetItem(""));
}


/*
function:��ģ�����Ա���г�ʼ��
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::initModelAttributionTable()
{
	ui.modelTableWidget->verticalScrollBar()->hide();
	ui.modelTableWidget->horizontalScrollBar()->hide();

	ui.modelTableWidget->horizontalHeader()->setHidden(false);
	ui.modelTableWidget->verticalHeader()->setHidden(false);

	ui.modelTableWidget->setItem(0, 1, new QTableWidgetItem(""));
	ui.modelTableWidget->setItem(1, 1, new QTableWidgetItem(""));
	ui.modelTableWidget->setItem(2, 1, new QTableWidgetItem(""));
	ui.modelTableWidget->setItem(3, 1, new QTableWidgetItem(""));
	QComboBox* cbox = new QComboBox(this);
	cbox->addItem( QSTRING_GBK("����"));
	cbox->addItem(QSTRING_GBK("�ر�"));
	ui.modelTableWidget->setCellWidget(4,1,cbox);
}


/*
function:��ʼ�������ź�
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::linkSignalsAndSlots()
{
	//graphics view����ź�
	connect(ui.graphicsView, SIGNAL(mousePress(QPointF)), this, SLOT(onMousePress(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseMove(QPointF)), this, SLOT(onMouseMove(QPointF)));
	connect(ui.graphicsView, SIGNAL(mouseRelease(QPointF)), this, SLOT(onMouseRelease(QPointF)));
	connect(ui.graphicsView, SIGNAL(wheelChange(int)), this, SLOT(onWheelChange(int)));

	//��ͼ
	connect(ui.paint_default_tbtn, SIGNAL(clicked()), this, SLOT(onPaintDefaultTbtnClicked()));
	connect(ui.paint_move_tbtn, SIGNAL(clicked()), this, SLOT(onPaintMoveTbtnClicked()));
	connect(ui.paint_move_cs_tbtn, SIGNAL(clicked()), this, SLOT(onPaintMoveCsTbtnClicked()));

	connect(ui.paint_select_rect_tbtn, SIGNAL(clicked()), this, SLOT(onPaintSelectTbtnClicked()));
	connect(ui.paint_cancel_select_tbtn, SIGNAL(clicked()), this, SLOT(onPaintCancelSelectTbtnClicked()));
	

	connect(ui.paint_delete_tbrn, SIGNAL(clicked()), this, SLOT(onPaintDeleteTbtnClicked()));
	connect(ui.paint_point_tbtn, SIGNAL(clicked()), this, SLOT(onPaintPointTbtnClicked()));
	connect(ui.paint_dir_iline_tbrn, SIGNAL(clicked()), this, SLOT(onPaintDirPathTbtnClicked()));
	connect(ui.paint_arch_line_tbtn, SIGNAL(clicked()), this, SLOT(onPaintArchPathTbtnClicked()));
	connect(ui.paint_loc_tbtn, SIGNAL(clicked()), this, SLOT(onPaintLocationTbtnClicked()));
	connect(ui.paint_vehicle_tbtn, SIGNAL(clicked()), this, SLOT(onPaintVehicleTbtnClicked()));

	//�˵����ź�
	//�༭
	connect(ui.undoAcn, SIGNAL(triggered()), this, SLOT(onUndoAcnTriggered()));
	connect(ui.redoAcn, SIGNAL(triggered()), this, SLOT(onRedoAcnTriggered()));

	//��ͼѡ��
	connect(ui.toolPanelPaintAcn, SIGNAL(triggered()), this, SLOT(onMenuPanelPaintAcnTriggered()));
	connect(ui.toolPanelObjectAcn, SIGNAL(triggered()), this, SLOT(onMenuPanelObjectgAcnTriggered()));
	connect(ui.toolPanelAttributeAcn, SIGNAL(triggered()), this, SLOT(onMenuPanelAttributeAcnTriggered()));
	connect(ui.toolPanelGroupAcn, SIGNAL(triggered()), this, SLOT(onMenuPanelGroupAcnTriggered()));


	//����ѡ��
	connect(ui.paintPointAcn, SIGNAL(triggered()), this, SLOT(onPaintPointAcnTriggered()));
	connect(ui.paintDirLineAcn, SIGNAL(triggered()), this, SLOT(onPaintDirLineAcnTriggered()));
	connect(ui.paintArchLineAcn, SIGNAL(triggered()), this, SLOT(onPaintArchLineAcnTriggered()));
	connect(ui.paintLocAcn, SIGNAL(triggered()), this, SLOT(onPaintLocationAcnTriggered()));
	connect(ui.menuDelSelectedAcn, SIGNAL(triggered()), this, SLOT(onMenuDelSelectedAcnTriggered()));
	connect(ui.MenuClearMapAcn, SIGNAL(triggered()), this, SLOT(onMenuClearMapAcnTriggered()));
	for (QAction* acn : _menuAddVehicleAcnList) {
		connect(acn, SIGNAL(triggered()), this, SLOT(onMenuAddVehicleAcnTriggered()));
	}
	connect(ui.menuToolSelectAcn, SIGNAL(triggered()), this, SLOT(onMenuToolSelectAcnTriggered()));
	connect(ui.menuToolAntiSelectAcn, SIGNAL(triggered()), this, SLOT(onMenuToolAntiSelectAcnTriggered()));
	connect(ui.menuToolMoveAcn, SIGNAL(triggered()), this, SLOT(onMenuToolMoveAcnTriggered()));
	connect(ui.menuToolMoveCsAcn, SIGNAL(triggered()), this, SLOT(onMenuToolMoveCsAcnTriggered()));
	//ѡ��ѡ��


	//�������ź�
	connect(ui.newFileAcn, SIGNAL(triggered()), this, SLOT(onNewFileAcnTriggered()));
	connect(ui.closeAcn, SIGNAL(triggered()), this, SLOT(onCloseAcnTriggered()));
	connect(ui.saveAcn, SIGNAL(triggered()), this, SLOT(onSaveAcnTriggered()));
	connect(ui.setBackPixmapAcn, SIGNAL(triggered()), this, SLOT(onSetBackImageAcnTriggered() ));


	//�������ź�
	//����ϵ�ź�
	connect(ui.XAxisMirrorAcn, SIGNAL(triggered()), this, SLOT(onXAxisAcnTriggered()));
	connect(ui.YAxisMirrorAcn, SIGNAL(triggered()), this, SLOT(onYAxisAcnTriggered()));
	connect(ui.AxisRotateAcn, SIGNAL(triggered()), this, SLOT(onAxisRotateAcnTriggered()));

	//���뺯��
	connect(ui.leftAlignAcn, SIGNAL(triggered()), this, SLOT(onLeftAlignAcnTriggered()));
	connect(ui.rightAlignAcn, SIGNAL(triggered()), this, SLOT(onRightAlignAcnTriggered()));
	connect(ui.topAlignAcn, SIGNAL(triggered()), this, SLOT(onTopAlignAcnTriggered()));
	connect(ui.bottomAlignAcn, SIGNAL(triggered()), this, SLOT(onBottomAlignAcnTriggered()));

	//�Ų�����
	connect(ui.equalDistributionAcn, SIGNAL(triggered()), this, SLOT(onEqualDistributionAcnTriggered()));
	connect(ui.yEqualDistributionAcn, SIGNAL(triggered()), this, SLOT(onYEqualDistributionAcnTriggered()));

	//����鿴��
	connect(ui.objectTreeWid, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(onObjectTreeWidItemPressed(QTreeWidgetItem*, int)));
	connect(ui.objectTreeWid, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
		this, SLOT(onObjectTreeWidCurrentItemChanged(QTreeWidgetItem * , QTreeWidgetItem * )));
	connect(_objectTreeActionList[0], SIGNAL(triggered()), this, SLOT(onObjectTreeWidNewGroupAcnTriggered()));

	//���Ա༭��
	connect(ui.attributeOkTbtn, SIGNAL(clicked()), this, SLOT(onAttributeOkTbtnClicked()));
	connect(ui.attributeFlushTbtn, SIGNAL(clicked()), this, SLOT(onAttributeFlushClicked()));
	connect(ui.attributeLocAddTbtn, SIGNAL(clicked()), this, SLOT(onAttributeLocAddTbtnClicked()));
	connect(ui.attributeLocDecTbtn, SIGNAL(clicked()), this, SLOT(onAttributeLocDecTbtnClicked()));
	connect(ui.attributeLocAcnEditTbtn, SIGNAL(clicked()), this, SLOT(onAttributeLocAcnEditClicked()));
}


/*
function: ��ʼ������
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::initOperation()
{
	//��ͼ���
	onPaintDefaultTbtnClicked(); //����ʱ��Ĭ�ϰ�ť
	//�˵���
	flushUndoRedoAcnEnable();//����������ť��ʼ��
	//��������ͼ��dock���ڵ���ʾ�͹ر�
	onMenuPanelPaintAcnTriggered();
	onMenuPanelPaintAcnTriggered();
	onMenuPanelAttributeAcnTriggered();
	onMenuPanelAttributeAcnTriggered();
	onMenuPanelGroupAcnTriggered();
	onMenuPanelObjectgAcnTriggered();
	onMenuPanelObjectgAcnTriggered();
	//������
	ui.objectTreeWid->setCurrentItem(ui.objectTreeWid->topLevelItem(0));//��ʼѡ��model
	onObjectTreeWidCurrentItemChanged(ui.objectTreeWid->currentItem(),nullptr);
}


/*
function: �ر����л�ͼ��ť��ʹ�ܣ���Ҫ����ģ�͸�����������߹�����
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::disableAllButtion()
{
	//����
	ui.paint_default_tbtn->setEnabled(false);
	ui.paint_select_rect_tbtn->setEnabled(false);
	ui.paint_cancel_select_tbtn->setEnabled(false);
	ui.paint_move_tbtn->setEnabled(false);
	ui.paint_move_cs_tbtn->setEnabled(false);
	ui.paint_delete_tbrn->setEnabled(false);
	ui.paint_point_tbtn->setEnabled(false);
	ui.paint_dir_iline_tbrn->setEnabled(false);
	ui.paint_arch_line_tbtn->setEnabled(false);
	ui.paint_loc_tbtn->setEnabled(false);
	ui.paint_vehicle_tbtn->setEnabled(false);
	ui.paint_dev_tbtn->setEnabled(false);
}


/*
function: ʹ�����л�ͼ��ť
param[1] : void;
return : void;
*/
void SunnyTcsMapEditor::enableAllButtion()
{
	//����
	ui.paint_default_tbtn->setEnabled(true);
	ui.paint_select_rect_tbtn->setEnabled(true);
	ui.paint_cancel_select_tbtn->setEnabled(true);
	ui.paint_move_tbtn->setEnabled(true);
	ui.paint_move_cs_tbtn->setEnabled(true);
	ui.paint_delete_tbrn->setEnabled(true);
	ui.paint_point_tbtn->setEnabled(true);
	ui.paint_dir_iline_tbrn->setEnabled(true);
	ui.paint_arch_line_tbtn->setEnabled(true);
	ui.paint_loc_tbtn->setEnabled(true);
	ui.paint_vehicle_tbtn->setEnabled(true);
	ui.paint_dev_tbtn->setEnabled(true);

}


/*
function: ����������� ɾ������
param[1] : ���������
return : void;
*/
void SunnyTcsMapEditor::removeItemWhenMousePressed(QPointF pt)
{
	Q_ASSERT(_model);//ģ����������ڣ���Ӧ�ô����˺��������������˵����ťʹ�� û����
	//��ǰλ��Ԫ������Ϊѡ��
	QGraphicsItem* item = _model->itemAt(pt, QTransform());
	if (item) {
		_model->setAllItemSelected(false);
		item->setSelected(true);
		onMenuDelSelectedAcnTriggered();
	}
}


/*
function: ����������� ����ѡȡ����
param[1] :  ���������
return : void;
*/
void SunnyTcsMapEditor::paintSelectAeraWhenMousePressed(QPointF pt)
{
	Q_ASSERT(_model); //ģ����������ڣ���Ӧ�ô����˺��������������˵����ťʹ�� û����
	if (!_model->isSelecting()) {
		_model->addSelectAera(SunnyTcsGraphicsSelectAera::ERect, pt);
	}
}


/*
	function: ����������� ���Ƶ㺯��
	param[1] :  ���������
	return : void;
*/
void SunnyTcsMapEditor::paintPointWhenMousePressed(QPointF pt)
{
	try
	{
		SunnyTcsGraphicsPoint* ptr = _model->addGraphicsPoint(pt);
		this->addObjectInTreeWidget(ptr);
		updatePointInfoWhenEditPoint();
		//���������볷����������
		updateTempUserOperationStack();
		SunnyTcsUserInterfaceOperation userOperation(
			[ptr, this]()->void {
			this->_model->addGraphicsPoint(ptr);
			this->addObjectInTreeWidget(ptr);
			updatePointInfoWhenEditPoint();
		},
			[ptr, this]()->void {
			this->_model->removeGraphicsPoint(ptr);
			this->delObjectInTreeWidget(ptr);
			updatePointInfoWhenEditPoint();
		},
			[ptr, this]()->void {
			delete ptr;
		}
		);
		_operations.push(userOperation);
		flushUndoRedoAcnEnable();
	}
	catch (SunnyTcsException<ERROR_GRAPHICS_POINT_OUT_SCENE>& e)
	{
		ui.statusBar->showMessage(QSTRING_GBK(e.what()));
	}
	
	
}


/*
	function: ����������� �����ߺ���
	param[1] :  ���������
	return : void;
*/
void SunnyTcsMapEditor::paintPathWhenMousePressed(QPointF pt)
{
	try {
		SunnyTcsGraphicsPath* ptr = nullptr;
		if (!_model->isPaintingPath()) { //��һ�ε��
			_model->addGraphicsPath(pt);
			
			disableAllButtion();//��ťʧ��
			ui.menuBar->setEnabled(false);//�˵��� ����
			ui.mainToolBar->setEnabled(false);//������ ����
			ui.objectDwid->setEnabled(false); //���������ڽ���
			ui.attributeDwid->setEnabled(false); //���Դ��ڽ���
		}
		else {//�ڶ������ε��
			ptr = _model->updateTempPath(pt, ui.paint_dir_iline_tbrn->isChecked() ? false : true, 2);
			if (!ptr)return;
			this->addObjectInTreeWidget(ptr);
			const SunnyTcsGraphicsPoint* start = dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getStart());
			this->addObjectInTreeWidget(start);
			const SunnyTcsGraphicsPoint* ctrl = dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getCtrl());
			if (ctrl) {
				this->addObjectInTreeWidget(ctrl);
			}
			const SunnyTcsGraphicsPoint* end = dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getEnd());
			this->addObjectInTreeWidget(end);
			updatePointInfoWhenEditPoint();
			//���������볷����������
			updateTempUserOperationStack();
			SunnyTcsUserInterfaceOperation userOperation(
				[ptr, this]()->void { //��������

				if (ptr->isStartNew()) {
					SunnyTcsGraphicsPoint* startPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getStart()));
					Q_ASSERT(startPt);
					this->_model->addGraphicsPoint(startPt);
					addObjectInTreeWidget(startPt);

				}
				if (ptr->isCtrlNew() && ptr->getCtrl()) {
					SunnyTcsGraphicsPoint* ctrlPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getCtrl()));
					Q_ASSERT(ctrlPt);
					this->_model->addGraphicsPoint(ctrlPt);
					addObjectInTreeWidget(ctrlPt);

				}
				if (ptr->isEndNew()) {
					SunnyTcsGraphicsPoint* endPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getEnd()));
					Q_ASSERT(endPt);
					this->_model->addGraphicsPoint(endPt);
					addObjectInTreeWidget(endPt);
				}
				this->_model->addGraphicsPath(ptr);
				this->addObjectInTreeWidget(ptr);
				updatePointInfoWhenEditPoint();
			},
				[ptr, this]()->void { //��������
				this->_model->removeGraphicsPath(ptr);
				this->delObjectInTreeWidget(ptr);
				if (ptr->isStartNew()) {
					SunnyTcsGraphicsPoint* startPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getStart()));
					Q_ASSERT(startPt);
					this->_model->removeGraphicsPoint(startPt);
					delObjectInTreeWidget(startPt);
				}
				if (ptr->isCtrlNew() && ptr->getCtrl()) {
					SunnyTcsGraphicsPoint* ctrlPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getCtrl()));
					Q_ASSERT(ctrlPt);
					this->_model->removeGraphicsPoint(ctrlPt);
					delObjectInTreeWidget(ctrlPt);
				}
				if (ptr->isEndNew()) {
					SunnyTcsGraphicsPoint* endPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getEnd()));
					Q_ASSERT(endPt);
					this->_model->removeGraphicsPoint(endPt);
					delObjectInTreeWidget(endPt);
				}
				updatePointInfoWhenEditPoint();
			},
				[ptr, this]()->void {
				if (ptr->isStartNew()) {
					SunnyTcsGraphicsPoint* startPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getStart()));
					Q_ASSERT(startPt);
					delete startPt;
				}
				if (ptr->isCtrlNew() && ptr->getCtrl()) {
					SunnyTcsGraphicsPoint* ctrlPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getCtrl()));
					Q_ASSERT(ctrlPt);
					delete ctrlPt;
				}
				if (ptr->isEndNew()) {
					SunnyTcsGraphicsPoint* endPt = const_cast<SunnyTcsGraphicsPoint*>(dynamic_cast<const SunnyTcsGraphicsPoint*>(ptr->getEnd()));
					Q_ASSERT(endPt);
					delete endPt;
				}
				delete ptr;
			}
			);
			_operations.push(userOperation);
			flushUndoRedoAcnEnable();
			enableAllButtion();
			ui.menuBar->setEnabled(true);//�˵��� ����
			ui.mainToolBar->setEnabled(true);//������ ����
			ui.objectDwid->setEnabled(true); //���������ڽ���
			ui.attributeDwid->setEnabled(true); //���Դ��ڽ���
		}
	}
	catch (SunnyTcsException<ERROR_GRAPHICS_PATH_OUT_SCENE>& e)
	{
		ui.statusBar->showMessage(QSTRING_GBK(e.what()));
	}
}


/*
function: ����������� ���ƹ�λ����
param[1] :  ���������
return : void;
*/
void SunnyTcsMapEditor::paintLocationWhenMousePressed(QPointF pt)
{
	try
	{
		SunnyTcsGraphicsLocation* ptr = _model->addGraphicsLocation(pt); //��ǰλ��û�е���׳��쳣
		if (!ptr)return;
		this->addObjectInTreeWidget(ptr);

		//���������볷����������
		updateTempUserOperationStack();
		SunnyTcsUserInterfaceOperation userOperation(
			[ptr, this]()->void {
			this->_model->addGraphicsLocation(ptr);
			this->addObjectInTreeWidget(ptr);
		},
			[ptr, this]()->void {
			this->_model->removeGraphicsLocation(ptr);
			this->delObjectInTreeWidget(ptr);
		},
			[ptr, this]()->void {
			delete ptr;
		}
		);
		_operations.push(userOperation);
		flushUndoRedoAcnEnable();
	}
	catch (SunnyTcsException<ERROR_GRAPHICS_LOCATION_NO_LINK_POINT>& e)
	{
		ui.statusBar->showMessage(QSTRING_GBK(e.what()));
	}
	
}


/*
function: ����������� ���Ƴ�����
param[1] :  ���������
return : void;
*/
void SunnyTcsMapEditor::paintVehicleWhenMousePressed(QPointF pt)
{
	SunnyTcsGraphicsVehicle* ptr = _model->addGraphicsVehicle(pt, _currentAgvCode);
	if (ptr) this->addObjectInTreeWidget(ptr);

	//���������볷����������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[ptr, this]()->void {
		this->_model->addGraphicsVehicle(ptr);
		this->addObjectInTreeWidget(ptr);
	},
		[ptr, this]()->void {
		this->_model->removeGraphicsVehicle(ptr);
		this->delObjectInTreeWidget(ptr);
	},
		[ptr, this]()->void {
		delete ptr;
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
}


/*
function: �Ե��������ɾ��ʱ��Ҫ���¸������Ա��� �йص��comboBox ��Ϣ
param[1] :  ���������
return : void;
*/
void SunnyTcsMapEditor::updatePointInfoWhenEditPoint()
{
	QList<SunnyTcsGraphicsPoint*> pts = _model->getPoints().values();
	std::sort(pts.begin(), pts.end(), [](SunnyTcsGraphicsPoint* p1, SunnyTcsGraphicsPoint* p2)->bool { return p1->getElementId() < p2->getElementId(); });
	QComboBox* startCbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(8,1));
	Q_ASSERT(startCbox);
	startCbox->clear();
	QComboBox* endCbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(9, 1));
	Q_ASSERT(endCbox);
	endCbox->clear();
	QComboBox* ctrlCbox = qobject_cast<QComboBox*>(ui.pathTableWidget->cellWidget(10, 1));
	Q_ASSERT(ctrlCbox);
	ctrlCbox->clear();
	ctrlCbox->addItem("N/A");
	QComboBox* locPtsCbox = qobject_cast<QComboBox*>(ui.locationTableWidget->cellWidget(1, 1));
	Q_ASSERT(locPtsCbox);
	locPtsCbox->clear();
	for (auto ptr : pts) {
		startCbox->addItem(ptr->getName());
		ctrlCbox->addItem(ptr->getName());
		endCbox->addItem(ptr->getName());
		locPtsCbox->addItem(ptr->getName());
	}
	onObjectTreeWidCurrentItemChanged(ui.objectTreeWid->currentItem(), nullptr);//�㼯��Ϣ�ı��ˣ������ʱ��ǰ����ҳ��·��,����Ҫ����
}



/*
function: ����ƶ�ʱ�����Ĳۺ���
param[1] :  �������
return : void;
*/
void SunnyTcsMapEditor::onMouseMove(QPointF pt)
{	
	if (!_model)return; //��ģ��״̬
	//QPointF npt = _model->getTrackPoint(pt);
	//QCursor::setPos(  ui.graphicsView->mapToGlobal(ui.graphicsView->mapFromScene(npt)));

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


/*
function : ����ͷ�
param[1] :  ����ͷ�����
return : void;
*/
void SunnyTcsMapEditor::onMouseRelease(QPointF pt)
{
	if (!_model)return; //��ģ��״̬
	if (ui.paint_move_tbtn->isChecked()||ui.paint_move_cs_tbtn->isChecked()) {
		if (_startMovePosition.isEmpty())return;
		SunnyTcsMapGraphicItem* firstItem = _startMovePosition.keys().at(0);
		if (firstItem->pos() != _startMovePosition[firstItem]) {
			//�ƶ���
			QHash <SunnyTcsMapGraphicItem*, QPointF> ordPosition(_startMovePosition);
			_startMovePosition.clear();
			QHash<SunnyTcsMapGraphicItem*, QPointF> newPositions;
			for (auto ptr : ordPosition.keys()) {
				newPositions.insert(ptr, ptr->pos());
			}
			//��ӳ����������� ������
			updateTempUserOperationStack();
			SunnyTcsUserInterfaceOperation userOperation(
				[newPositions]()->void {
				for (auto ptr : newPositions.keys()) {
					ptr->setPos(newPositions[ptr]);
				}
			},
				[ordPosition]()->void {
				for (auto ptr : ordPosition.keys()) {
					ptr->setPos(ordPosition[ptr]);
				}
			},
				[]()->void {
			}
			);
			_operations.push(userOperation);
			flushUndoRedoAcnEnable();
		}
	}
	else if (ui.paint_select_rect_tbtn->isChecked()) {
		if (_model->isSelecting()) {
			_model->updateSelectAera(pt, true);
		}
	}
	else if (ui.paint_cancel_select_tbtn->isChecked()) {
		if (_model->isSelecting()) {
			_model->updateSelectAera(pt, true);
			QList<QGraphicsItem*> ret = _model->selectedItems();
			for (auto ptr : ret) {
				if (_currentSelected.contains(ptr)) {
					_currentSelected.removeOne(ptr);
				}
				ptr->setSelected(false);
			}

			for (auto ptr : _currentSelected) {
				ptr->setSelected(true);
			}
		}
	}
	_model->update();
}


/*
function : �����
param[1] :  ���������
return : void;
*/
void SunnyTcsMapEditor::onMousePress(QPointF pt)
{
	if (!_model)return; //��ģ��״̬

	if (_trackCbox->isChecked()) {
		pt = _model->getTrackPoint(pt);
	}
	
	//QCursor::setPos(  ui.graphicsView->mapToGlobal(ui.graphicsView->mapFromScene(npt)));

	//paint���
	if (ui.paint_default_tbtn->isChecked()) {
		QGraphicsItem* item = _model->itemAt(pt, QTransform());
		this->setCurrenctTreeItemInTreeWidget(dynamic_cast<SunnyTcsMapGraphicItem*>(item));
	}
	else if (ui.paint_move_tbtn->isChecked()|| ui.paint_move_cs_tbtn->isChecked()) {
		QGraphicsItem* item = _model->itemAt(pt, QTransform());
		if(item)item->setSelected(true);
		QList<QGraphicsItem*> && selectedItems = _model->selectedItems();
		if (!selectedItems.isEmpty()) {
			_startMovePosition.clear();
		}
		for (auto ptr : selectedItems) {
			SunnyTcsMapGraphicItem* item = dynamic_cast<SunnyTcsMapGraphicItem*>(ptr);
			Q_ASSERT(item); //�������в���ת��ΪSunnyTcsMapGraphicItem�ĵ�ͼԪ��
			_startMovePosition.insert(item , ptr->pos());
		}
	}
	else if (ui.paint_delete_tbrn->isChecked()) {
		removeItemWhenMousePressed(pt);
	}
	else if (ui.paint_select_rect_tbtn->isChecked()) {
		paintSelectAeraWhenMousePressed(pt);
	}
	else if (ui.paint_cancel_select_tbtn->isChecked()) {
		for (auto ptr : _currentSelected) {
			ptr->setSelected(true);
		}
		_model->update();
		paintSelectAeraWhenMousePressed(pt);
	}
	else if (ui.paint_point_tbtn->isChecked()) {
		paintPointWhenMousePressed(pt);
	}
	else if (ui.paint_dir_iline_tbrn->isChecked() || ui.paint_arch_line_tbtn->isChecked()) {
		paintPathWhenMousePressed(pt);
	}
	else if (ui.paint_loc_tbtn->isChecked()) {
		paintLocationWhenMousePressed(pt);
	}
	else if (ui.paint_vehicle_tbtn->isChecked()) {
		paintVehicleWhenMousePressed(pt);
	}
}


/*
function : ������
param[1] :  �Ƕ�
return : void;
*/
void SunnyTcsMapEditor::onWheelChange(int angle)
{
	if (!_model)return; //��ģ��״̬
	if (angle > 0) {
		ui.graphicsView->scale(1.2, 1.2);
	}
	else if (angle < 0) {
		ui.graphicsView->scale(  0.85, 0.85);
	}
}



/*
function : Ĭ�ϰ�ť�ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintDefaultTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : ѡȡ��ť�ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintSelectTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : ȡ��ѡȡ��ť�ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintCancelSelectTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected = _model->selectedItems();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : �ƶ�Ԫ�زۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintMoveTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemSendsGeometryChanges);
	_model->setItemFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable, Epath);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : �ƶ�����ϵ�ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintMoveCsTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(0);
	_model->setItemFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemSendsGeometryChanges, Ecoorsys);
}


/*
function : ɾ���ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintDeleteTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : ���Ƶ�ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintPointTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : ����ֱ�߲ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintDirPathTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : �������߲ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintArchPathTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : ���ƹ�λ�ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintLocationTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function : ���Ƴ����ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintVehicleTbtnClicked()
{
	Q_ASSERT(_model); // û��ģ�͵�ʱ�򣬰�ťӦ���Ѿ�ʧ�ܣ������ܴ����ú���
	_currentSelected.clear();
	_model->setItemFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	_model->setItemFlags(0, Ecoorsys);
}


/*
function :���ݳ��������������������ʹ�ܻ���ʧ�ܳ�����������ť 
param[1] :  void 
return : void;   
*/
void SunnyTcsMapEditor::flushUndoRedoAcnEnable()
{
	_operations.isEmpty() ? ui.undoAcn->setEnabled(false) : ui.undoAcn->setEnabled(true);
	_tempOperations.isEmpty() ? ui.redoAcn->setEnabled(false) : ui.redoAcn->setEnabled(true);
}



/*
function :����ѡ��ۺ���
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onUndoAcnTriggered()
{
	if (_operations.isEmpty()) {
		return;
	}
	_operations.top().undo();
	_tempOperations.push( _operations.pop());
	this->_model->update();
	flushUndoRedoAcnEnable();
}


/*
	function :����ѡ��ۺ���
	param[1] :  void
	return : void;
*/
void SunnyTcsMapEditor::onRedoAcnTriggered()
{
	if (_tempOperations.isEmpty()) {
		return;
	}
	_tempOperations.top().redo();
	_operations.push(_tempOperations.pop());
	this->_model->update();
	flushUndoRedoAcnEnable();
}


/*
	function :�����������
	param[1] :  void
	return : void;
*/
void SunnyTcsMapEditor::updateTempUserOperationStack()
{
	while (!_tempOperations.isEmpty()) {
		_tempOperations.pop().dropOperation();
	}
	_tempOperations.clear();
	ui.redoAcn->setEnabled(false);
}


/*
	function :�˵�������ѡ�
	param[1] :  void
	return : void;
*/
void SunnyTcsMapEditor::onPaintPointAcnTriggered()
{
	ui.paint_point_tbtn->setChecked(true);
	emit ui.paint_point_tbtn->clicked();
}


/*
function :�˵�������ѡ�
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintDirLineAcnTriggered()
{
	ui.paint_dir_iline_tbrn->setChecked(true);
	emit ui.paint_dir_iline_tbrn->clicked();
}


/*
function :�˵�������ѡ�
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintArchLineAcnTriggered()
{
	ui.paint_arch_line_tbtn->setChecked(true);
	emit ui.paint_arch_line_tbtn->clicked();
}


/*
function :�˵�������ѡ�
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onPaintLocationAcnTriggered()
{
	ui.paint_loc_tbtn->setChecked(true);
	emit ui.paint_loc_tbtn->clicked();
}


/*
function :�ۺ�����ɾ��ѡ����
param[1] :  void
return : void;
*/
void SunnyTcsMapEditor::onMenuDelSelectedAcnTriggered()
{
	QList<QGraphicsItem*>&& itemsSelected = _model->selectedItems();
	QVector<SunnyTcsMapGraphicItem*> pts;
	QVector<SunnyTcsMapGraphicItem*> removedItems;

	SunnyTcsMapGraphicItem* item = nullptr;
	if (itemsSelected.isEmpty())return;
	
	for (auto ptr : itemsSelected) {
		item = dynamic_cast<SunnyTcsMapGraphicItem*>(ptr);
		Q_ASSERT(item);
		if (item->getItemTag()._eletype == Epoint) {
			pts.append(item);
			continue;
		}
		_model->remiveGraphicsItems(item);
		delObjectInTreeWidget(item);
		removedItems.append(item);
	}

	for (auto ptr : pts) {
		item = dynamic_cast<SunnyTcsMapGraphicItem*>(ptr);
		Q_ASSERT(item);
		if (_model->checkIsPointUsedByPathOrLoc(ptr->getItemId()))continue;
		_model->remiveGraphicsItems(item);
		delObjectInTreeWidget(item);
		updatePointInfoWhenEditPoint();
		removedItems.append(item);
	}
	_model->update();


	//���������볷����������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[removedItems, this]()->void {
		for (auto ptr : removedItems) {
			this->_model->remiveGraphicsItems(ptr);
			this->delObjectInTreeWidget(ptr);
		}
		updatePointInfoWhenEditPoint();
	},
		[removedItems, this]()->void {
		for (auto ptr : removedItems) {
			this->_model->addGraphicsItems(ptr);
			this->addObjectInTreeWidget(ptr);
		}
		updatePointInfoWhenEditPoint();
	},
		[removedItems]()->void {
		/*
		qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++";
		for (auto ptr : removedItems) {
			qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++";
			delete ptr;
		}
		*/
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
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
			_currentAgvCode = I_SunnyTcsVehicleFactory::_vehicleSupported.values().at(i);
			ui.paint_vehicle_tbtn->setChecked(true);
			break;
		}
	}
	emit ui.paint_vehicle_tbtn->clicked();
}

void SunnyTcsMapEditor::onMenuToolSelectAcnTriggered()
{
	ui.paint_select_rect_tbtn->setChecked(true);
	emit ui.paint_select_rect_tbtn->clicked();
}

void SunnyTcsMapEditor::onMenuToolAntiSelectAcnTriggered()
{
	ui.paint_cancel_select_tbtn->setChecked(true);
	emit ui.paint_cancel_select_tbtn->clicked();
}

void SunnyTcsMapEditor::onMenuToolMoveAcnTriggered()
{
	ui.paint_move_tbtn->setChecked(true);
	emit ui.paint_move_tbtn->clicked();
}

void SunnyTcsMapEditor::onMenuToolMoveCsAcnTriggered()
{
	ui.paint_move_cs_tbtn->setChecked(true);
	emit ui.paint_move_cs_tbtn->clicked();
}


void SunnyTcsMapEditor::onMenuPanelPaintAcnTriggered()
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

void SunnyTcsMapEditor::onMenuPanelObjectgAcnTriggered()
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


void SunnyTcsMapEditor::onMenuPanelAttributeAcnTriggered()
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

void SunnyTcsMapEditor::onMenuPanelGroupAcnTriggered()
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



void SunnyTcsMapEditor::onNewFileAcnTriggered()
{
	QString path = QFileDialog::getOpenFileName(this);
	QFile file(path);
	if (!file.exists() || !file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::information(this, "info", "open error");
	}
	QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());
	QJsonObject jobj = jdoc.object();
	SunnyTcsGraphicsModel* model = new SunnyTcsGraphicsModel(1, "");
	QString err;
	if (!model->fromJson(jobj, err)) {
		ui.statusBar->showMessage(err);
		return;
	}
	
	this->setModel(model);
}

void SunnyTcsMapEditor::onSaveAcnTriggered()
{
	QString path = QFileDialog::getSaveFileName(this);
	QFile file(path);
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::information(this, tr("��ʾ"), "save error");
	}

	QJsonDocument jdoc(_model->toJson());
	file.write(jdoc.toJson());
	
}



void SunnyTcsMapEditor::onCloseAcnTriggered()
{
	removeCurrentModel();
}

void SunnyTcsMapEditor::onSetBackImageAcnTriggered()
{
	QString path =  QFileDialog::getOpenFileName(this);
	 _model->setImagePath(path);
}

void SunnyTcsMapEditor::onXAxisAcnTriggered()
{
	_model->xAxisMirror();
	_model->update();

	//��������������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[this]()->void {
		this->_model->xAxisMirror();
	},
		[this]()->void {
		this->_model->xAxisMirror();
	},
		[]()->void {}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
}

void SunnyTcsMapEditor::onYAxisAcnTriggered()
{
	_model->yAxisMirror();
	_model->update();

	//��������������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[this]()->void {
		this->_model->yAxisMirror();
	},
		[this]()->void {
		this->_model->yAxisMirror();
	},
		[]()->void {}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
}

void SunnyTcsMapEditor::onAxisRotateAcnTriggered()
{
	_model->rotateAxis();
	_model->update();

	//��������������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[this]()->void {
		this->_model->rotateAxis();
	},
		[this]()->void {
		this->_model->rotateAxis();
		this->_model->rotateAxis();
		this->_model->rotateAxis();
	},
		[]()->void {}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
}

void SunnyTcsMapEditor::onLeftAlignAcnTriggered()
{
	
	//��¼��ԭ����λ��
	QList<QGraphicsItem*> && selectedItems = _model->selectedItems();
	if (selectedItems.isEmpty()) return;
	_startMovePosition.clear();
	for (auto ptr : selectedItems) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype != Epoint)continue;
		_startMovePosition.insert(dynamic_cast<SunnyTcsMapGraphicItem*>(ptr), ptr->pos());
	}
	_model->leftAlign();
	//��¼���µ�λ��
	QHash <SunnyTcsMapGraphicItem*, QPointF> ordPosition(_startMovePosition);
	_startMovePosition.clear();
	QHash<SunnyTcsMapGraphicItem*, QPointF> newPositions;
	for (auto ptr : ordPosition.keys()) {
		newPositions.insert(ptr, ptr->pos());
	}
	//��ӳ����������� ������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[newPositions]()->void {
		for (auto ptr : newPositions.keys()) {
			ptr->setPos(newPositions[ptr]);
		}
	},
		[ordPosition]()->void {
		for (auto ptr : ordPosition.keys()) {
			ptr->setPos(ordPosition[ptr]);
		}
	},
		[]()->void {
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
	_model->update();
}

void SunnyTcsMapEditor::onRightAlignAcnTriggered()
{
	//��¼��ԭ����λ��
	QList<QGraphicsItem*> && selectedItems = _model->selectedItems();
	if (selectedItems.isEmpty()) return;
	_startMovePosition.clear();
	for (auto ptr : selectedItems) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype != Epoint)continue;
		_startMovePosition.insert(dynamic_cast<SunnyTcsMapGraphicItem*>(ptr), ptr->pos());
	}
	_model->rightAlign();
	//��¼���µ�λ��
	QHash <SunnyTcsMapGraphicItem*, QPointF> ordPosition(_startMovePosition);
	_startMovePosition.clear();
	QHash<SunnyTcsMapGraphicItem*, QPointF> newPositions;
	for (auto ptr : ordPosition.keys()) {
		newPositions.insert(ptr, ptr->pos());
	}
	//��ӳ����������� ������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[newPositions]()->void {
		for (auto ptr : newPositions.keys()) {
			ptr->setPos(newPositions[ptr]);
		}
	},
		[ordPosition]()->void {
		for (auto ptr : ordPosition.keys()) {
			ptr->setPos(ordPosition[ptr]);
		}
	},
		[]()->void {
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
	_model->update();
}


void SunnyTcsMapEditor::onTopAlignAcnTriggered()
{
	//��¼��ԭ����λ��
	QList<QGraphicsItem*> && selectedItems = _model->selectedItems();
	if (selectedItems.isEmpty()) return;
	_startMovePosition.clear();
	for (auto ptr : selectedItems) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype != Epoint)continue;
		_startMovePosition.insert(dynamic_cast<SunnyTcsMapGraphicItem*>(ptr), ptr->pos());
	}
	_model->topAlign();
	//��¼���µ�λ��
	QHash <SunnyTcsMapGraphicItem*, QPointF> ordPosition(_startMovePosition);
	_startMovePosition.clear();
	QHash<SunnyTcsMapGraphicItem*, QPointF> newPositions;
	for (auto ptr : ordPosition.keys()) {
		newPositions.insert(ptr, ptr->pos());
	}
	//��ӳ����������� ������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[newPositions]()->void {
		for (auto ptr : newPositions.keys()) {
			ptr->setPos(newPositions[ptr]);
		}
	},
		[ordPosition]()->void {
		for (auto ptr : ordPosition.keys()) {
			ptr->setPos(ordPosition[ptr]);
		}
	},
		[]()->void {
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
	_model->update();
}

void SunnyTcsMapEditor::onBottomAlignAcnTriggered()
{
	//��¼��ԭ����λ��
	QList<QGraphicsItem*> && selectedItems = _model->selectedItems();
	if (selectedItems.isEmpty()) return;
	_startMovePosition.clear();
	for (auto ptr : selectedItems) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype != Epoint)continue;
		_startMovePosition.insert(dynamic_cast<SunnyTcsMapGraphicItem*>(ptr), ptr->pos());
	}
	_model->bottomAlign();
	//��¼���µ�λ��
	QHash <SunnyTcsMapGraphicItem*, QPointF> ordPosition(_startMovePosition);
	_startMovePosition.clear();
	QHash<SunnyTcsMapGraphicItem*, QPointF> newPositions;
	for (auto ptr : ordPosition.keys()) {
		newPositions.insert(ptr, ptr->pos());
	}
	//��ӳ����������� ������
	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[newPositions]()->void {
		for (auto ptr : newPositions.keys()) {
			ptr->setPos(newPositions[ptr]);
		}
	},
		[ordPosition]()->void {
		for (auto ptr : ordPosition.keys()) {
			ptr->setPos(ordPosition[ptr]);
		}
	},
		[]()->void {
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
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
	
	if (qApp->mouseButtons() == Qt::RightButton)   //�ж��Ƿ�Ϊ�Ҽ�
	{
		qDebug() << "pressed";
// 		QMenu*menu = new QMenu(ui->treeWidget);
// 		if (pressedItem->text(column) == "A")   //���ҵ�QTreeWidget�����У�������QTreeWidgetItem����������һ������Ϊ������
// 		{
// 			menu->addAction(test);
// 			menu->exec(QCursor::pos());   //�˵�����λ��Ϊ�����λ��
// 		}
		_ObjectTreeWidPointMenu->exec(QCursor::pos());
		
	}

}


/*
	function: ��������ǰ�� �仯ʱ �����Ĳۺ�������Ҫ�Ǹ������Ա༭���ڣ�ʹ�����������ǰ���һ��;
	param[1] : ��ǰ��;
	param[2] : ֮ǰ���������û����;
	return : void;
*/
void SunnyTcsMapEditor::onObjectTreeWidCurrentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
	if (!current)return;
	_model->setAllItemSelected(false);
	SunnyTcsObjectTreeWidgetMapItem* cur = dynamic_cast<SunnyTcsObjectTreeWidgetMapItem*> (current);
	if (!cur) { //��ѡ��������ǵ�ͼͼ��Ԫ�أ��ͽ����Դ������õ� ģ����һҳ
		updateModelAttribute();
		return;
	}
	SunnyTcsMapGraphicItem* item = const_cast<SunnyTcsMapGraphicItem*>(cur->getItem());
	item->setSelected(true);
	updateAttribute(item);
}

void SunnyTcsMapEditor::onObjectTreeWidNewGroupAcnTriggered()
{
	qDebug() << "create new group";
	switch (_newGrouptype)
	{
	case basic::Enotype:
		break;
	case basic::Epoint:
		_model->addItemGroup(Epoint);
		break;
	case basic::Epath:
		_model->addItemGroup(Epath);
		break;
	case basic::Elocation:
		_model->addItemGroup(Elocation);
		break;
	case basic::Evehicle:
		_model->addItemGroup(Evehicle);
		break;
	default:
		return;
	}
}



void SunnyTcsMapEditor::onAttributeOkTbtnClicked()
{
	try {
		if (ui.attributeStackWid->currentIndex() == 4) {//model
			QString name = ui.modelTableWidget->item(0, 1)->text();
			if (name.isEmpty())throw QSTRING_GBK("ģ����Ϊ��");
			if (name.contains(' '))throw QSTRING_GBK("ģ�������ܰ����ո�");
			_model->setName(name);
			qint32 wid = ui.modelTableWidget->item(1, 1)->text().toInt();
			qint32 hei = ui.modelTableWidget->item(2, 1)->text().toInt();
			qint32 res = ui.modelTableWidget->item(3, 1)->text().toInt();
			_model->setWidAndHei(wid, hei);
			_model->setResolution(res);

			QComboBox* cbox = qobject_cast<QComboBox*>(ui.modelTableWidget->cellWidget(4, 1));
			_model->setAutoTrafficControlOpen(cbox->currentIndex() == 0 ? true : false);
			_model->update();
		}
		if (!_currentEditingItem)return;
		E_SunnyTcsMapObject_type type = _currentEditingItem->getItemTag()._eletype;
		if (type == Epoint) {
			setPointAttribution();
		}
		else if (type == Epath) {
			setPathAttribution();
		}
		else if (type == Elocation) {
			setLocationAttribution();
		}
		else if (type == Evehicle) {
			setVehicleAttribution();
		}
		_model->update();
	}
	catch (const QString err) {
		QMessageBox::information(this, QSTRING_GBK("��ʾ"), err);
	}
}

void SunnyTcsMapEditor::onAttributeLocAddTbtnClicked()
{
	try
	{
		qint32 paramRowCount = ui.locationTableWidget->rowCount() - 2;
		if (paramRowCount >= SunnyTcsAction::action_params_count)throw QSTRING_GBK("�������������֧����");
		ui.locationTableWidget->setRowCount(ui.locationTableWidget->rowCount() + 1);
		ui.locationTableWidget->setItem(ui.locationTableWidget->rowCount() - 1, 0,
			new QTableWidgetItem(QSTRING_GBK("����%1").arg(QString::number(ui.locationTableWidget->rowCount() - 2))));
		QComboBox* cbox = new QComboBox(this);
		for (auto typeDecp : SunnyTcsAction::supportArgTyps.values()) {
			cbox->addItem(typeDecp);
		}
		ui.locationTableWidget->setCellWidget(ui.locationTableWidget->rowCount() - 1, 1, cbox);
	}
	catch (QString& e)
	{
		ui.statusBar->showMessage(e);
	}
	
}

void SunnyTcsMapEditor::onAttributeLocDecTbtnClicked()
{
	try
	{
		qint32 paramRowCount = ui.locationTableWidget->rowCount() - 2;
		if (paramRowCount <= 1)throw QSTRING_GBK("������������С��1��");
		delete ui.locationTableWidget->item(ui.locationTableWidget->rowCount() - 1, 0);
		delete qobject_cast<QComboBox*>(ui.locationTableWidget->cellWidget(ui.locationTableWidget->rowCount() - 1, 1));
		ui.locationTableWidget->setRowCount(ui.locationTableWidget->rowCount() - 1);
	}
	catch (QString& e)
	{
		ui.statusBar->showMessage(e);
	}
}

void SunnyTcsMapEditor::onAttributeLocAcnEditClicked()
{
	SunnyTcsGraphicsLocation* loc = dynamic_cast<SunnyTcsGraphicsLocation*>(_currentEditingItem);
	if (loc) {
		
		_locEditWidget->show();
		_locEditWidget->init(loc);
	}
	

}



void SunnyTcsMapEditor::setPointAttribution()
{
	SunnyTcsGraphicsPoint* item = dynamic_cast<SunnyTcsGraphicsPoint*>(_currentEditingItem);
	Q_ASSERT(item);
	//��¼��ԭ����ֵ
	QString ordName = item->getName();
	SunnyTcsAgvCoordinate ordCoor = item->getPointCoor();
	qint32 ordNagamode = item->getPointNaga();
	qint32 ordAbs = item->getPointAbsPos();

	//��Ķ�����
	QString name = ui.pointTableWidget->item(0, 1)->text();
	if (name.isEmpty())throw QSTRING_GBK("ģ����Ϊ��");
	if (name.contains(' '))throw QSTRING_GBK("ģ�������ܰ����ո�");
	
	//��ľ���λ��
	qint32 rx = ui.pointTableWidget->item(1, 1)->text().toInt();
	qint32 ry = ui.pointTableWidget->item(2, 1)->text().toInt();
	
	//֧�ֵĵ���ģʽ
	qint32 nagamode = 0;
	QComboBox* cbox = qobject_cast<QComboBox*>(ui.pointTableWidget->cellWidget(3, 1));
	nagamode |= cbox->currentIndex() == 0 ? VEHICLE_NAGA_RUBBON : 0;
	cbox = qobject_cast<QComboBox*>(ui.pointTableWidget->cellWidget(4, 1));
	nagamode |= cbox->currentIndex() == 0 ? VEHICLE_NAGA_INERTIA : 0;
	cbox = qobject_cast<QComboBox*>(ui.pointTableWidget->cellWidget(5, 1));
	nagamode |= cbox->currentIndex() == 0 ? VEHICLE_NAGA_LASER : 0;
	
	//����λ��
	qint32 abspos = ui.pointTableWidget->item(6, 1)->text().toInt();
	
	//rfid
	item->SetName(name);
	SunnyTcsAgvCoordinate coor(E_TWO_DIMENSION, rx, ry);
	item->setPointRealityXy(coor);
	item->setPointNaga(nagamode);
	item->setPointAbsPos(abspos);

	updateTempUserOperationStack();
	SunnyTcsUserInterfaceOperation userOperation(
		[name, coor,nagamode,abspos,item,this]()->void {
		item->SetName(name);
		item->setPointRealityXy(coor);
		item->setPointNaga(nagamode);
		item->setPointAbsPos(abspos);
		this->setCurrenctTreeItemInTreeWidget(item);
	},
		[ordName, ordCoor, ordNagamode, ordAbs, item,this]()->void {
		item->SetName(ordName);
		item->setPointRealityXy(ordCoor);
		item->setPointNaga(ordNagamode);
		item->setPointAbsPos(ordAbs);
		this->setCurrenctTreeItemInTreeWidget(item);
	},
		[]()->void {
	}
	);
	_operations.push(userOperation);
	flushUndoRedoAcnEnable();
}



void SunnyTcsMapEditor::setPathAttribution()
{
	try
	{
		SunnyTcsGraphicsPath* item = dynamic_cast<SunnyTcsGraphicsPath*>(_currentEditingItem);
		Q_ASSERT(item);

		//ԭ����ֵ�ȼ�¼�����㳷��
		QString ordName = item->getName();
		bool ordIsSupportForward = item->isSupportPositive();
		bool ordIsSupportBack = item->isSupportNegative();
		qint32 ordSpeed = item->getPositiveSpeed();
		qint32 ordbackSpeed = item->getNegativeSpeed();
		bool ordIsScanActived = item->isScanAeraActived();
		qint32 ordScanAera = item->getPositiveScanAera();
		qint32 ordBackScanAera = item->getNegativeScanAera();
		const SunnyTcsGraphicsPoint* ordStart = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getStart());
		Q_ASSERT(ordStart);
		const SunnyTcsGraphicsPoint* ordEnd = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getEnd());
		Q_ASSERT(ordEnd);
		const SunnyTcsGraphicsPoint* ordCtrl = dynamic_cast<const SunnyTcsGraphicsPoint*>(item->getCtrl());

		//��ֵ
		//·���Ķ�����
		QString name = ui.pathTableWidget->item(0, 1)->text();
		if (name.isEmpty())throw QSTRING_GBK("ģ����Ϊ��");
		if (name.contains(' '))throw QSTRING_GBK("ģ�������ܰ����ո�");

		//�Ƿ�֧��ǰ����
		bool isSupportForward = dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(1, 1))->currentIndex() == 0 ? true : false;
		bool isSupportBack = dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(2, 1))->currentIndex() == 0 ? true : false;

		//�ٶ�����
		qint32 speed = ui.pathTableWidget->item(3, 1)->text().toInt();
		qint32 back_speed = ui.pathTableWidget->item(4, 1)->text().toInt();

		//ɨ����
		bool isScanActived = dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(5, 1))->currentIndex() == 0 ? true : false;
		qint32 scanAera = ui.pathTableWidget->item(6, 1)->text().toInt();
		qint32 back_scanAera = ui.pathTableWidget->item(7, 1)->text().toInt();

		//���õ�
		QString start = dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(8, 1))->currentText();
		QString end = dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(9, 1))->currentText();

		if (start == end) {
			throw QSTRING_GBK("·���㲻���ظ�");
		}

		const QHash<qint32, SunnyTcsGraphicsPoint*> & pts = _model->getPoints();
		auto iter_start = std::find_if(pts.begin(), pts.end(), [&start](SunnyTcsGraphicsPoint* ptr)->bool {return ptr->getName() == start; });
		Q_ASSERT(iter_start != pts.end());
		SunnyTcsGraphicsPoint* startPtr = *iter_start;

		auto iter_end = std::find_if(pts.begin(), pts.end(), [&end](SunnyTcsGraphicsPoint* ptr)->bool {return ptr->getName() == end; });
		Q_ASSERT(iter_end != pts.end());
		SunnyTcsGraphicsPoint* endPtr = *iter_end;

		SunnyTcsGraphicsPoint* ctrlPtr = nullptr;
		QString ctrl = dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(10, 1))->currentText();
		if (dynamic_cast<QComboBox*>(ui.pathTableWidget->cellWidget(10, 1))->currentIndex() == 0) {
			item->setCtrl(nullptr);
		}
		else {
			auto iter_ctrl = std::find_if(pts.begin(), pts.end(), [&ctrl](SunnyTcsGraphicsPoint* ptr)->bool {return ptr->getName() == ctrl; });
			Q_ASSERT(iter_ctrl != pts.end());
			if (ctrl == start || ctrl == end) {
				throw QSTRING_GBK("·���㲻���ظ�");
			}
			else {
				ctrlPtr = *iter_ctrl;
				item->setCtrl(*iter_ctrl);
			}
		}
		//����ֵ
		item->setStart(*iter_start);
		item->setEnd(*iter_end);
		item->SetName(name);
		item->setIsSupportPositive(isSupportForward);
		item->setIsSupportNegative(isSupportBack);
		item->setPositiveSpeed(speed);
		item->setNegativeSpeed(back_speed);
		item->setIfScanAeraActived(isScanActived);
		item->setPositiveScanAera(scanAera);
		item->setNegativeScanAera(back_scanAera);

		//���³�������������
		updateTempUserOperationStack();
		SunnyTcsUserInterfaceOperation userOperation(
			[name, isSupportForward, isSupportBack, speed, back_speed, isScanActived,
			scanAera, back_scanAera, startPtr, endPtr, ctrlPtr, item, this]()->void {
			item->setStart(startPtr);
			item->setCtrl(ctrlPtr);
			item->setEnd(endPtr);
			item->SetName(name);
			item->setIsSupportPositive(isSupportForward);
			item->setIsSupportNegative(isSupportBack);
			item->setPositiveSpeed(speed);
			item->setNegativeSpeed(back_speed);
			item->setIfScanAeraActived(isScanActived);
			item->setPositiveScanAera(scanAera);
			item->setNegativeScanAera(back_scanAera);
			this->setCurrenctTreeItemInTreeWidget(item);
		},
			[ordName, ordIsSupportForward, ordIsSupportBack, ordSpeed,
			ordbackSpeed, ordIsScanActived, ordScanAera, ordBackScanAera,
			ordStart, ordEnd, ordCtrl,item,this]()->void {
			item->setStart(ordStart);
			item->setCtrl(ordCtrl);
			item->setEnd(ordEnd);
			item->SetName(ordName);
			item->setIsSupportPositive(ordIsSupportForward);
			item->setIsSupportNegative(ordIsSupportBack);
			item->setPositiveSpeed(ordSpeed);
			item->setNegativeSpeed(ordbackSpeed);
			item->setIfScanAeraActived(ordIsScanActived);
			item->setPositiveScanAera(ordScanAera);
			item->setNegativeScanAera(ordBackScanAera);
			this->setCurrenctTreeItemInTreeWidget(item);
		},
			[]()->void {
		}
		);
		_operations.push(userOperation);
		flushUndoRedoAcnEnable();

	}
	catch (QString e)
	{
		ui.statusBar->showMessage(e);
	}
}

void SunnyTcsMapEditor::setLocationAttribution()
{
	try
	{
		SunnyTcsGraphicsLocation* item = dynamic_cast<SunnyTcsGraphicsLocation*>(_currentEditingItem);
		Q_ASSERT(item);

		//��¼��ֵ
		QString ordName = item->getName();
		const SunnyTcsGraphicsPoint* ordPt = dynamic_cast<const SunnyTcsGraphicsPoint*> (item->getLinkPointPtr());
		QVector<E_ARG_TYPE> ordArgTYpe = item->getParamsType();

		//��ȡ��ֵ
		QString name = ui.locationTableWidget->item(0, 1)->text();
		QComboBox* cbox = dynamic_cast<QComboBox*>(ui.locationTableWidget->cellWidget(1, 1));
		Q_ASSERT(cbox);
		QString newPtName = cbox->currentText();
		const QHash<qint32, SunnyTcsGraphicsPoint*> & pts = _model->getPoints();
		auto iter = std::find_if(pts.begin(), pts.end(), [&newPtName](SunnyTcsGraphicsPoint* ptr)->bool {return ptr->getName() == newPtName; });
		Q_ASSERT(iter != pts.end());
		SunnyTcsGraphicsPoint* ptPtr = *iter;
		QVector<E_ARG_TYPE> argTypes;
		for (int i = 2; i < ui.locationTableWidget->rowCount(); ++i) {
			qint32 index = qobject_cast<QComboBox*>(ui.locationTableWidget->cellWidget(i, 1))->currentIndex();
			E_ARG_TYPE argType = SunnyTcsAction::supportArgTyps.keys().at(index);
			argTypes << argType;
		}

		//��������
		item->SetName(name);
		item->bindLinkPt(ptPtr);
		item->setParamsType(argTypes);

		//���³�����������
		updateTempUserOperationStack();
		SunnyTcsUserInterfaceOperation userOperation(
			[name,ptPtr,this,item, argTypes]()->void {
			item->SetName(name);
			item->bindLinkPt(ptPtr);
			item->setParamsType(argTypes);
			this->setCurrenctTreeItemInTreeWidget(item);
		},
			[ordName,ordPt,this,item,ordArgTYpe]()->void {
			item->SetName(ordName);
			item->bindLinkPt(ordPt);
			item->setParamsType(ordArgTYpe);
			this->setCurrenctTreeItemInTreeWidget(item);
		},
			[this]()->void {}
		);
		flushUndoRedoAcnEnable();
		_operations.push(userOperation);

	}
	catch (QString& e)
	{
		
	}
	
}

void SunnyTcsMapEditor::setVehicleAttribution()
{
	try
	{
		SunnyTcsGraphicsVehicle* item = dynamic_cast<SunnyTcsGraphicsVehicle*>(_currentEditingItem);
		Q_ASSERT(item);

		//��¼��ֵ
		QString ordName = item->getName();
		QString ordIp = item->getVehicleIp();
		qint16 ordPort = item->getVehiclePort();
		qint32 ordLadarRadius = item->getLadarRadius();

		//��ֵ
		QString name = ui.vehicleTableWidget->item(0, 1)->text();
		QString ip = ui.vehicleTableWidget->item(1, 1)->text();
		quint16 port = ui.vehicleTableWidget->item(2, 1)->text().toInt();
		qint32 ladarRadius = ui.vehicleTableWidget->item(4, 1)->text().toInt();

		//������ֵ
		item->SetName(name);
		item->setVehicleIp(ip);
		item->setVehiclePort(port);
		item->setLadarRadius(ladarRadius);

		//����������
		updateTempUserOperationStack();
		SunnyTcsUserInterfaceOperation userOperation(
			[name, ip, port, ladarRadius, this, item]()->void {
			item->SetName(name);
			item->setVehicleIp(ip);
			item->setVehiclePort(port);
			item->setLadarRadius(ladarRadius);
			this->setCurrenctTreeItemInTreeWidget(item);
		},
			[ordName, ordIp, ordPort, ordLadarRadius, this, item]()->void {
			item->SetName(ordName);
			item->setVehicleIp(ordIp);
			item->setVehiclePort(ordPort);
			item->setLadarRadius(ordLadarRadius);
			this->setCurrenctTreeItemInTreeWidget(item);
		},
			[]()->void {}
		);
		_operations.push(userOperation);
		this->flushUndoRedoAcnEnable();
	}
	catch (QString& e)
	{
		ui.statusBar->showMessage(e);
	}
	
}

void SunnyTcsMapEditor::onAttributeFlushClicked()
{
	onObjectTreeWidCurrentItemChanged(ui.objectTreeWid->currentItem(), nullptr);
}
