#include "SunnyTcsGraphicsModel.h"




SunnyTcsGraphicsModel::SunnyTcsGraphicsModel(qint32 id, QString name, qint32 wid, qint32 hei, qint32 resolution)
	: SunnyTcsMapAdjuster(wid,hei,resolution) , _id(id), _name(name),_pathTempPoint(nullptr),
	_pathTemp(nullptr),_pts(),_phs(),_locs(),_cs(nullptr),_aera(nullptr)
{
	_veFactory = new SunnyTcsGraphicsVehicleFactory();
	setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);//�ڲ������� ͼԪdelete�� �ᵼ�±���
	_cs = new SunnyTcsGraphicsCoorSys(QPointF(0, 0), this);
	this->addItem(_cs);
	setSceneRect(-_sceneWid / 2, -_sceneHei / 2,_sceneWid, _sceneHei);
	update();
}



QPointF SunnyTcsGraphicsModel::getTrackPoint(QPointF pt) const
{
	SunnyTcsAgvCoordinate&& rxy = _cs->transformToReality(SunnyTcsAgvCoordinate(E_TWO_DIMENSION, pt.x(), pt.y()));//����������ת��Ϊ ��ʵ����
	qint32 stepx = rxy._x / _resolution;
	qint32 stepy = rxy._y / _resolution;
	qint32 inayx = rxy._x % _resolution;
	qint32 inayy = rxy._y % _resolution;
	qreal inaccuracyAllowed = _resolution * 0.1;

	if ((qAbs(inayx) > inaccuracyAllowed && _resolution - qAbs(inayx) > inaccuracyAllowed) ||
		(qAbs(inayy) > inaccuracyAllowed && _resolution - qAbs(inayy) > inaccuracyAllowed)) {
		return pt;
	}

	if (qAbs(inayx) > qAbs(_resolution - inaccuracyAllowed)) {
		if (stepx == 0) {
			stepx += inayx > 0 ? 1 : -1;
		}
		else {
			stepx += stepx > 0 ? 1 : -1;
		}
	}
	if (qAbs(inayy) > qAbs(_resolution - inaccuracyAllowed)) {
		if (stepy == 0) {
			stepy += inayy > 0 ? 1 : -1;
		}
		else {
			stepy += stepy > 0 ? 1 : -1;
		}
	}
	rxy._x = stepx * _resolution;
	rxy._y = stepy * _resolution;
	SunnyTcsAgvCoordinate&& sxy = _cs->transformToScene(rxy);
	return QPointF(sxy._x, sxy._y);
}

bool SunnyTcsGraphicsModel::isOutOfSceneRect(QPointF pt) const
{
	if (qAbs(pt.x()) > qAbs(((qreal)_sceneWid) / 2.0) || qAbs(pt.y()) > qAbs(((qreal)_sceneHei) / 2.0)) {
		return true;
	}
	return false;
}


QList<SunnyTcsGraphicsPoint*> SunnyTcsGraphicsModel::selectedPointItems()
{
	QList<SunnyTcsGraphicsPoint*> ret;
	QList<QGraphicsItem*>& items = selectedItems();
	for (QGraphicsItem* item : items) {
		SunnyTcsGraphicsPoint* pt = dynamic_cast<SunnyTcsGraphicsPoint*>(item);
		if (pt)ret << pt;
	}
	return ret;
}


QList<SunnyTcsGraphicsPath*> SunnyTcsGraphicsModel::selectedPathItems()
{
	QList<SunnyTcsGraphicsPath*> ret;
	QList<QGraphicsItem*>& items = selectedItems();
	for (QGraphicsItem* item : items) {
		SunnyTcsGraphicsPath* pt = dynamic_cast<SunnyTcsGraphicsPath*>(item);
		if (pt)ret << pt;
	}
	return ret;
}


QList<SunnyTcsGraphicsLocation*> SunnyTcsGraphicsModel::selectedLocationItems()
{
	QList<SunnyTcsGraphicsLocation*> ret;
	QList<QGraphicsItem*>& items = selectedItems();
	for (QGraphicsItem* item : items) {
		SunnyTcsGraphicsLocation* pt = dynamic_cast<SunnyTcsGraphicsLocation*>(item);
		if (pt)ret << pt;
	}
	return ret;
}


QList<SunnyTcsGraphicsVehicle*> SunnyTcsGraphicsModel::selectedVehicleItems()
{
	QList<SunnyTcsGraphicsVehicle*> ret;
	QList<QGraphicsItem*>& items = selectedItems();
	for (QGraphicsItem* item : items) {
		SunnyTcsGraphicsVehicle* pt = dynamic_cast<SunnyTcsGraphicsVehicle*>(item);
		if (pt)ret << pt;
	}
	return ret;
}

SunnyTcsAgvCoordinate SunnyTcsGraphicsModel::transformRealityToScene(const SunnyTcsAgvCoordinate & rxy)
{
	return _cs->transformToScene(rxy);
}

SunnyTcsAgvCoordinate SunnyTcsGraphicsModel::transformSceneToReality(const SunnyTcsAgvCoordinate & sxy)
{
	return _cs->transformToReality(sxy);
}


void SunnyTcsGraphicsModel::setWidAndHei(qint32 wid, qint32 hei)
{
	_sceneWid = wid;
	_sceneHei = hei;
	this->setSceneRect(QRectF(-wid / 2, -hei / 2, wid, hei));
}

void SunnyTcsGraphicsModel::setItemFlags(QGraphicsItem::GraphicsItemFlags flags, E_SunnyTcsMapObject_type tar)
{
	QList<QGraphicsItem*>& items = this->items();
	switch (tar)
	{
	case basic::Enotype:
		for (auto ptr : items) {
			ptr->setFlags(flags);
		}
		break;
	case basic::Ecoorsys:
		_cs->setFlags(flags);
		break;
	case basic::Epoint:
		for (auto ptr : _pts) {
			ptr->setFlags(flags);
		}
		break;
	case basic::Epath:
		for (auto ptr : _phs) {
			ptr->setFlags(flags);
		}
		break;
	case basic::Elocation:
		for (auto ptr : _locs) {
			ptr->setFlags(flags);
		}
		break;
	case basic::Evehicle:
		for (auto ptr : _ves) {
			ptr->setFlags(flags);
		}
		break;
	case basic::Euls:
		break;
	default:
		break;
	}

}



void SunnyTcsGraphicsModel::setAllItemSelected(bool is , E_SunnyTcsMapObject_type tar)
{
	QList<QGraphicsItem*>& items = this->items();
	switch (tar)
	{
	case basic::Enotype:
		for (auto ptr : items) {
			ptr->setSelected(is);
		}
		break;
	case basic::Ecoorsys:
		_cs->setSelected(is);
		break;
	case basic::Epoint:
		for (auto ptr : _pts) {
			ptr->setSelected(is);
		}
		break;
	case basic::Epath:
		for (auto ptr : _phs) {
			ptr->setSelected(is);
		}
		break;
	case basic::Elocation:
		for (auto ptr : _locs) {
			ptr->setSelected(is);
		}
		break;
	case basic::Evehicle:
		for (auto ptr : _ves) {
			ptr->setSelected(is);
		}
		break;
	case basic::Euls:
		break;
	default:
		break;
	}
}



SunnyTcsGraphicsPath*  SunnyTcsGraphicsModel::updateTempPath(QPointF pt, bool isArch, qint32 flag)
{
	SunnyTcsGraphicsPath* ret = nullptr;

	_pathTempPoint->setPos(pt);
	if (flag == 2) {
		SunnyTcsGraphicsPoint* start = const_cast<SunnyTcsGraphicsPoint*> (dynamic_cast<const SunnyTcsGraphicsPoint*>(_pathTemp->getStart()));
		SunnyTcsGraphicsPoint* end = const_cast<SunnyTcsGraphicsPoint*> (dynamic_cast<const SunnyTcsGraphicsPoint*>(_pathTemp->getEnd()));
		SunnyTcsGraphicsPoint* ctrl = _pathTemp->getCtrl() ?
			const_cast<SunnyTcsGraphicsPoint*> (dynamic_cast<const SunnyTcsGraphicsPoint*>(_pathTemp->getCtrl())) : nullptr;

		if (!isArch) {
			//ֱ�߽�����
			end->setZValue(GRAPHICS_LOW_ZVALUE);//���Լ���Ū������ȥ
			SunnyTcsGraphicsPoint* tempEnd = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));//��ȡ��ǰλ�õ�
			if (tempEnd && tempEnd != end) { //��ǰλ��������ĵ�
				_pathTemp->setEnd(tempEnd);
				this->removeItem(end);
				delete end; //ԭ��ʹ�õ�temp end���û����
				end = tempEnd;
				_pathTemp->setIsEndNew(false); //����ֱ���յ��Ƿ�Ϊ�µ�
			}
			else {
				_pathTemp->setIsEndNew(true); //����ֱ���յ��Ƿ�Ϊ�µ�
			}
			
			end->setZValue(GRAPHICS_POINT_ZVALUE);

			_pts.insert(start->getElementId(), start);
			_pts.insert(end->getElementId(), end);
			_phs.insert(_pathTemp->getElementId(), _pathTemp);
			ret = _pathTemp;
			_pathTemp = nullptr;
			_pathTempPoint = nullptr;			
		}
		else if (isArch && !ctrl) {
			//���߽�����
			end->setZValue(GRAPHICS_LOW_ZVALUE);//���Լ���Ū������ȥ
			SunnyTcsGraphicsPoint* tempEnd = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));//��ȡ��ǰλ�õ�
			bool hasOne = (tempEnd && tempEnd != end);
			tempEnd = hasOne ? tempEnd : new  SunnyTcsGraphicsPoint(_cs, this, pt); //�µĽ�����
			_pathTemp->setIsEndNew(hasOne ? false : true);
			if (!hasOne) { //tempEnd ���� new SunnyTcsGraphicsPoint
				this->addItem(tempEnd); //��
			}

			//_pathTempPoint ���� ԭend ����Ϊ�µ� ctrl��
			end->setZValue(GRAPHICS_POINT_ZVALUE);
			_pathTemp->setEnd(tempEnd);
			_pathTemp->setCtrl(end); //ԭend����Ϊ�е�
			
		}
		else {
			ctrl->setZValue(GRAPHICS_LOW_ZVALUE);//���Լ���Ū������ȥ
			SunnyTcsGraphicsPoint* tempCtrl = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));//��ȡ��ǰλ�õ�
			if (tempCtrl && tempCtrl != ctrl) { //��ǰλ��������ĵ�
				_pathTemp->setCtrl(tempCtrl);
				this->removeItem(ctrl);
				delete ctrl; //ԭ��ʹ�õ�temp end���û����
				ctrl = tempCtrl;
				_pathTemp->setIsCtrlNew(false);
			}
			else {
				_pathTemp->setIsCtrlNew(true);
			}
			ctrl->setZValue(GRAPHICS_POINT_ZVALUE);

			_pts.insert(start->getElementId(), start);
			_pts.insert(end->getElementId(), end);
			_pts.insert(ctrl->getElementId(), ctrl);
			_phs.insert(_pathTemp->getElementId(), _pathTemp);
			ret = _pathTemp;
			_pathTemp = nullptr;
			_pathTempPoint = nullptr;
		}
	}
	
	return ret;
}



void SunnyTcsGraphicsModel::updatePointRxy()
{
	for (auto ptr : _pts) {
		ptr->updateData();
	}
}



void SunnyTcsGraphicsModel::leftAlign()
{
	QList<QGraphicsItem*>&& itemsSelected = this->selectedItems();
	if (itemsSelected.isEmpty())return;
	qreal minX = itemsSelected.first()->x();
	for (auto ptr : itemsSelected) {
		minX = ptr->x() < minX ? ptr->x() : minX;
	}
	for (auto ptr : itemsSelected) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Epath || dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Ecoorsys) {
			continue;
		}
		ptr->setX(minX);
	}

}



void SunnyTcsGraphicsModel::rightAlign()
{
	QList<QGraphicsItem*>&& itemsSelected = this->selectedItems();
	if (itemsSelected.isEmpty())return;
	qreal maxX = itemsSelected.first()->x();
	for (auto ptr : itemsSelected) {
		maxX = ptr->x() > maxX ? ptr->x() : maxX;
	}
	for (auto ptr : itemsSelected) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Epath || dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Ecoorsys) {
			continue;
		}
		ptr->setX(maxX);
	}
}



void SunnyTcsGraphicsModel::topAlign()
{
	QList<QGraphicsItem*>&& itemsSelected = this->selectedItems();
	if (itemsSelected.isEmpty())return;
	qreal minY = itemsSelected.first()->y();
	for (auto ptr : itemsSelected) {
		minY = ptr->y() < minY ? ptr->y() : minY;
	}
	for (auto ptr : itemsSelected) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Epath || dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Ecoorsys) {
			continue;
		}
		ptr->setY(minY);
	}
}



void SunnyTcsGraphicsModel::bottomAlign()
{
	QList<QGraphicsItem*>&& itemsSelected = this->selectedItems();
	if (itemsSelected.isEmpty())return;
	qreal maxY = itemsSelected.first()->y();
	for (auto ptr : itemsSelected) {
		maxY = ptr->y() > maxY ? ptr->y() : maxY;
	}
	for (auto ptr : itemsSelected) {
		if (dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Epath || dynamic_cast<SunnyTcsMapGraphicItem*>(ptr)->getItemTag()._eletype == Ecoorsys) {
			continue;
		}
		ptr->setY(maxY);
	}
}



void SunnyTcsGraphicsModel::addSelectAera(SunnyTcsGraphicsSelectAera::selectAera type, QPointF first)
{
	if (_aera)return;
	_aera = new SunnyTcsGraphicsSelectAera(type, first, first);
	addItem(_aera);
}



void SunnyTcsGraphicsModel::updateSelectAera(QPointF pt, bool isEnd)
{
	if (!_aera)return;
	_aera->updateAera(pt);
	if (isEnd) {
		QList<QGraphicsItem*> targets = _aera->collidingItems();
		setAllItemSelected(false);
		for (auto ptr : targets) {
			ptr->setSelected(true);
		}
		removeItem(_aera);
		delete _aera;
		_aera = nullptr;
	}
	update();
}

const QHash<qint32, SunnyTcsMapGroups*>& SunnyTcsGraphicsModel::getGroup(E_SunnyTcsMapObject_type type) const
{
	switch (type)
	{
	case basic::Epoint:
		return _ptGroups;
	case basic::Epath:
		return _phGroups;
	case basic::Elocation:
		return _locGroups;
	case basic::Evehicle:
		return _veGroups;
	default:
		Q_ASSERT(0);
	}
	return _ptGroups;
}

void SunnyTcsGraphicsModel::addItemGroup(E_SunnyTcsMapObject_type type, QString name)
{
	SunnyTcsMapGroups* gp = new SunnyTcsMapGroups(this, name);
	if (name.isEmpty()) {
		switch (type)
		{
		case basic::Epoint:
			name = QString("point group %1").arg(gp->getId());
			_ptGroups.insert(gp->getId(), gp);
			break;
		case basic::Epath:
			name = QString("path group %1").arg(gp->getId());
			_phGroups.insert(gp->getId(), gp);
			break;
		case basic::Elocation:
			name = QString("location group %1").arg(gp->getId());
			_locGroups.insert(gp->getId(), gp);
			break;
		case basic::Evehicle:
			name = QString("agv group %1").arg(gp->getId());
			_veGroups.insert(gp->getId(), gp);
			break;
		default:
			delete gp;
			return;
		}
	}
	
}

void SunnyTcsGraphicsModel::removeItemGroup(E_SunnyTcsMapObject_type type, qint32 id)
{
	QHash<qint32, SunnyTcsMapGroups*> *groupPtr = nullptr;
	switch (type)
	{
	case basic::Epoint:
		groupPtr = &_ptGroups;
		break;
	case basic::Epath:
		groupPtr = &_phGroups;
		break;
	case basic::Elocation:
		groupPtr = &_locGroups;
		break;
	case basic::Evehicle:
		groupPtr = &_veGroups;
		break;
	default:
		Q_ASSERT(0);
		break;
	}
	if (groupPtr->contains(id)) {
		groupPtr->remove(id);
	}
}



SunnyTcsGraphicsPoint* SunnyTcsGraphicsModel::addGraphicsPoint(QPointF pt)
{
	if (isOutOfSceneRect(pt)) {
		throw SunnyTcsException<ERROR_GRAPHICS_POINT_OUT_SCENE>();
	}
	SunnyTcsGraphicsPoint* ptr = new SunnyTcsGraphicsPoint(_cs, this, pt);
	Q_ASSERT(addGraphicsPoint(ptr)); //�����ظ�ID��������жϣ�˵��ID ����������⣬�Ҵ��󲻿���
	return ptr;
}



SunnyTcsGraphicsPath*  SunnyTcsGraphicsModel::addGraphicsPath(QPointF pt)
{
	if (isOutOfSceneRect(pt)) {
		throw SunnyTcsException<ERROR_GRAPHICS_PATH_OUT_SCENE>();
	}
	//start end
	SunnyTcsGraphicsPoint* tempStart = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));
	SunnyTcsGraphicsPoint* start = tempStart ? tempStart : new SunnyTcsGraphicsPoint(_cs, this, pt); //��ǰλ���ѽ��е���øõ�
	_pathTempPoint = new SunnyTcsGraphicsPoint(_cs, this, pt);
	//tempPath
	_pathTemp = new SunnyTcsGraphicsPath(this, start, _pathTempPoint);

	if (!tempStart) {
		this->addItem(start);
	}
	_pathTemp->setIsStartNew(tempStart ? false : true);//��������Ƿ�Ϊȫ�µ�
	this->addItem(_pathTempPoint);
	this->addItem(_pathTemp);
	return _pathTemp;
}



SunnyTcsGraphicsLocation*  SunnyTcsGraphicsModel::addGraphicsLocation(QPointF pt)
{
	SunnyTcsMapGraphicItem* item = dynamic_cast<SunnyTcsMapGraphicItem*>(itemAt(pt, QTransform()));
	if (item && item->getItemTag()._eletype == Epoint) {
		SunnyTcsGraphicsLocation* loc = new SunnyTcsGraphicsLocation(this,_pts[item->getItemId()]);
		Q_ASSERT( addGraphicsLocation(loc));
		return loc;
	}
	else { //��ǰλ�ò����ڵ㣬��λ�޷�����
		throw SunnyTcsException<ERROR_GRAPHICS_LOCATION_NO_LINK_POINT>();
	}
	return nullptr;
}



SunnyTcsGraphicsVehicle* SunnyTcsGraphicsModel::addGraphicsVehicle(QPointF pt, SunnyTcsAgvCode code)
{
	if (isOutOfSceneRect(pt)) {
		throw SunnyTcsException<ERROR_GRAPHICS_VEHICLE_OUT_SCENE>(); //�����˳�������
	}

	SunnyTcsGraphicsVehicle* ve = nullptr;
	if (code == vehicle_normal) {
		 ve = new SunnyTcsGraphicsVehicle_normal(_cs, this, pt);
	}
	else if (code == vehicle_mitsubishi) {
		 ve = new SunnyTcsGraphicsVehicle_mitsubishi_battery(_cs, this, pt);
	}	
	else if (code == vehicle_daimler_engine) {
		 ve = new SunnyTcsGraphicsVehicle_daimler_engine(_cs, this, pt);
	}

	if (ve) {
		Q_ASSERT( addGraphicsVehicle(ve) ); //�������й����У������ǲ���������false�ģ����Բ��ö���
	}
	return ve;
}



bool SunnyTcsGraphicsModel::addGraphicsItems(SunnyTcsMapGraphicItem * item)
{
	if (!item) {
		return false;
	}
	switch (item->getItemTag()._eletype)
	{
	case basic::Epoint:
		return addGraphicsPoint(dynamic_cast<SunnyTcsGraphicsPoint*>(item));
	case basic::Epath:
		return addGraphicsPath(dynamic_cast<SunnyTcsGraphicsPath*>(item));
	case basic::Elocation:
		return addGraphicsLocation(dynamic_cast<SunnyTcsGraphicsLocation*>(item));
	case basic::Evehicle:
		return addGraphicsVehicle(dynamic_cast<SunnyTcsGraphicsVehicle*>(item));
	default:
		return false;
	}
}

bool SunnyTcsGraphicsModel::addGraphicsPoint(SunnyTcsGraphicsPoint * item)
{
	if (_pts.contains(item->getItemId()))return false;
	_pts.insert(item->getElementId(), item);
	this->addItem(item);
	return true;
}



bool SunnyTcsGraphicsModel::addGraphicsPath(SunnyTcsGraphicsPath * item)
{
	if (_phs.contains(item->getItemId()))return false;
	_phs.insert(item->getElementId(), item);
	this->addItem(item);
	return true;
}



bool SunnyTcsGraphicsModel::addGraphicsLocation(SunnyTcsGraphicsLocation * item)
{
	if (_locs.contains(item->getItemId()))return false;
	_locs.insert(item->getElementId(), item);
	this->addItem(item);
	return true;
}



bool SunnyTcsGraphicsModel::addGraphicsVehicle(SunnyTcsGraphicsVehicle * item)
{
	if (_ves.contains(item->getItemId()))return false;
	_ves.insert(item->getItemId(), item);
	this->addItem(item);
	return true;
}



bool SunnyTcsGraphicsModel::deleteGraphicsItem(SunnyTcsMapGraphicItem * item)
{
	if (!item) {
		return false;
	}
	switch (item->getItemTag()._eletype)
	{
	case basic::Epoint:
		return deleteGraphicsPoint(dynamic_cast<SunnyTcsGraphicsPoint*>(item));
	case basic::Epath:
		return deleteGraphicsPath(dynamic_cast<SunnyTcsGraphicsPath*>(item));
	case basic::Elocation:
		return deleteGraphicsLocation(dynamic_cast<SunnyTcsGraphicsLocation*>(item));
	case basic::Evehicle:
		return deleteGraphicsVehicle(dynamic_cast<SunnyTcsGraphicsVehicle*>(item));
	default:
		return false;
	}

}



bool SunnyTcsGraphicsModel::deleteGraphicsPoint(SunnyTcsGraphicsPoint * item)
{
	if (removeGraphicsPoint(item)) {
		delete item;
		return true;
	}
	return false;
}



bool SunnyTcsGraphicsModel::deleteGraphicsPath(SunnyTcsGraphicsPath * item)
{
	if (removeGraphicsPath(item)) {
		delete item;
		return true;
	}
	return false;
}



bool SunnyTcsGraphicsModel::deleteGraphicsLocation(SunnyTcsGraphicsLocation * item)
{
	if (removeGraphicsLocation(item)) {
		delete item;
		return true;
	}
	return false;
}



bool SunnyTcsGraphicsModel::deleteGraphicsVehicle(SunnyTcsGraphicsVehicle * item)
{
	if (removeGraphicsVehicle(item)) {
		delete item;
		return true;
	}
	return false;
}



bool SunnyTcsGraphicsModel::remiveGraphicsItems(SunnyTcsMapGraphicItem * item)
{
	if (!item) {
		return false;
	}
	switch (item->getItemTag()._eletype)
	{
	case basic::Epoint:
		return removeGraphicsPoint(dynamic_cast<SunnyTcsGraphicsPoint*>(item));
	case basic::Epath:
		return removeGraphicsPath(dynamic_cast<SunnyTcsGraphicsPath*>(item));
	case basic::Elocation:
		return removeGraphicsLocation(dynamic_cast<SunnyTcsGraphicsLocation*>(item));
	case basic::Evehicle:
		return removeGraphicsVehicle(dynamic_cast<SunnyTcsGraphicsVehicle*>(item));
	default:
		return false;
	}
}



bool SunnyTcsGraphicsModel::removeGraphicsPoint(SunnyTcsMapGraphicItem * item)
{
	if (!item) {
		return false;
	}
	for (auto ptr : _locs) {
		if ((void*)(ptr->getLinkPointPtr()) == (void*)item) {
			return false;
		}
	}
	for (auto ptr : _phs) {
		if (
			(ptr->getStart()->getElementId()) == item->getItemId() ||
			(ptr->getCtrl() ? ptr->getCtrl()->getElementId() : 0) == item->getItemId() ||
			(ptr->getEnd()->getElementId()) == item->getItemId()
			)
		{
			return false;
		}
	}
	removeItem(item);
	_pts.remove(item->getItemId());
	return true;
}



bool SunnyTcsGraphicsModel::removeGraphicsPath(SunnyTcsGraphicsPath * item)
{
	if (!item) {
		return false;
	}
	removeItem(item);//ȡ����ʾ
	_phs.remove(item->getItemId());//��PHS��ɾ��
								   //���ɾ��·��
	return true;
}



bool SunnyTcsGraphicsModel::removeGraphicsLocation(SunnyTcsGraphicsLocation * item)
{
	if (!item) {
		return false;
	}
	removeItem(item);//ȡ����ʾ
	_locs.remove(item->getItemId());//��locs��ɾ��
	return true;
}



bool SunnyTcsGraphicsModel::removeGraphicsVehicle(SunnyTcsGraphicsVehicle * item)
{
	if (!item) {
		return false;
	}
	removeItem(item);//ȡ����ʾ
	_ves.remove(item->getItemId());//��locs��ɾ��
	return true;
}



void SunnyTcsGraphicsModel::xEqualDistributionOfPoints()
{
	QList<SunnyTcsGraphicsPoint*>&& pts = selectedPointItems();
	if (pts.count() < 3)return; //������һ���޷����зֲ�

	std::sort(pts.begin(), pts.end(), [](SunnyTcsGraphicsPoint* p1, SunnyTcsGraphicsPoint* p2)->bool {return p1->pos().x() < p2->pos().x(); });
	qreal interval = (pts.last()->pos().x() - pts.first()->pos().x()) / (qreal)(pts.count()-1);
	qreal start = pts.first()->pos().x();
	for (qint32 i = 1; i < pts.count() - 1; ++i) {
		start += interval;
		pts[i]->setX(start);
	}
}


void SunnyTcsGraphicsModel::yEqualDistributionOfPoints()
{
	QList<SunnyTcsGraphicsPoint*>&& pts = selectedPointItems();
	if (pts.count() < 3)return; //������һ���޷����зֲ�

	std::sort(pts.begin(), pts.end(), [](SunnyTcsGraphicsPoint* p1, SunnyTcsGraphicsPoint* p2)->bool {return p1->pos().y() < p2->pos().y(); });
	qreal interval = (pts.last()->pos().y() - pts.first()->pos().y()) / (qreal)(pts.count()-1);
	qreal start = pts.first()->pos().y();
	for (qint32 i = 1; i < pts.count() - 1; ++i) {
		start += interval;
		pts[i]->setY(start);
	}
}

bool SunnyTcsGraphicsModel::checkIsPointUsedByPathOrLoc(qint32 ptId)
{
	for (auto ptr : _phs) {
		if (ptr->getStart()->getElementId() == ptId || ptr->getEnd()->getElementId() == ptId ||
			(ptr->getCtrl() && ptr->getCtrl()->getElementId() == ptId)
			) {
			return true;
		}
	}

	for (auto ptr : _locs) {
		if (ptr->getLinkedPointId() == ptId) {
			return true;
		}
	}

	return false;
}



bool SunnyTcsGraphicsModel::setImagePath(QString path)
{
	_backGroundPixmapPath = path;
	_backGroundPixmap = QImage(path);
	if (_backGroundPixmap.isNull()) {
		return false;
	}
	return true;
}

void SunnyTcsGraphicsModel::drawBackground(QPainter * painter, const QRectF & rect)
{
	if (_backGroundPixmap.isNull()) {
		painter->fillRect(this->sceneRect(), QColor(70, 80, 110));
	}
	else {
		painter->drawImage(this->sceneRect(), _backGroundPixmap);
	}
	

	qreal wid = _sceneWid;
	qreal hei = _sceneHei;
	qreal res = _resolution;
	qreal cur_x = _cs->pos().x();
	qreal cur_y = _cs->pos().y();
	qreal dis_x_left = qAbs(cur_x - (-wid / 2.0));
	qreal dis_x_right = qAbs(wid / 2.0 - cur_x);
	qreal dis_y_down = qAbs(hei / 2.0 - cur_y);
	qreal dis_y_up = qAbs(cur_y - (-hei / 2.0));

	QPen pen;
	pen.setWidth(101.0);
	pen.setColor(QColor(83, 92, 121));
	painter->setPen(pen);
	QFont font;
	font.setPixelSize(600);
	painter->setFont(font);
	QPen textPen;
	textPen.setColor(Qt::white);

	bool axis_x_right = _cs->getAxisDirectionX() == Eright || _cs->getAxisDirectionY() == Eright;
	bool axis_y_up = _cs->getAxisDirectionX() == Eup || _cs->getAxisDirectionY() == Eup;

	for (qreal i = 0; i < dis_x_left; i += res) {
		painter->drawLine(QPointF(cur_x - i, -hei / 2.0), QPointF(cur_x - i, hei / 2.0));
		painter->setPen(textPen);
		painter->drawText(QRectF(cur_x - i + 500.0, cur_y + 500, 3000.0, 3000.0), QString::number(axis_x_right ? -i : i) + QString("mm"));
		painter->setPen(pen);
	}

	for (qreal i = 0; i < dis_x_right; i += res) {
		painter->drawLine(QPointF(cur_x + i, -hei / 2.0), QPointF(cur_x + i, hei / 2.0));
		painter->setPen(textPen);
		painter->drawText(QRectF(cur_x + i + 500.0, cur_y + 500, 3000.0, 3000.0), QString::number(axis_x_right ? i : -i) + QString("mm"));
		painter->setPen(pen);
	}

	for (qreal i = 0; i < dis_y_down; i += res) {
		painter->drawLine(QPointF(-wid / 2.0, cur_y + i), QPointF(wid / 2.0, cur_y + i));
		painter->setPen(textPen);
		painter->drawText(QRectF(cur_x + 500.0, cur_y + i + 500.0, 3000.0, 3000.0), QString::number(axis_y_up ? -i : i) + QString("mm"));
		painter->setPen(pen);
	}

	for (qreal i = 0; i < dis_y_up; i += res) {
		painter->drawLine(QPointF(-wid / 2.0, cur_y - i), QPointF(wid / 2.0, cur_y - i));
		painter->setPen(textPen);
		painter->drawText(QRectF(cur_x + 500.0, cur_y - i + 500.0, 3000.0, 3000.0), QString::number(axis_y_up ? i : -i) + QString("mm"));
		painter->setPen(pen);
	}
}

void SunnyTcsGraphicsModel::releaseAllSource()
{
	for (auto ptr : this->items()) {
		removeItem(ptr);
	}
	for (auto ptr : _ves) {
		delete ptr;
	}
	for (auto ptr : _locs) {
		delete ptr;
	}
	for (auto ptr : _phs) {
		delete ptr;
	}
	for (auto ptr : _pts) {
		delete ptr;
	}

}


// QPainterPath SunnyTcsGraphicsSelectAera::shape() const
// {
// 	QPainterPath path;
// 	if (_curAera == ERect) {//����ѡȡ
// 		path.addRect(QRectF(_tracks[0], _tracks[1]));
// 	}
// 	else { //�����ѡȡ
// 		QPolygonF poly;
// 		for (auto iter : _tracks) {
// 			poly << iter;
// 		}
// 		path.addPolygon(poly);
// 	}
// 	return path;
// }


QRectF SunnyTcsGraphicsSelectAera::boundingRect() const
{
	return QRectF(_tracks[0], _tracks[1]);
}

void SunnyTcsGraphicsSelectAera::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPen pen;
	pen.setColor(QColor(120, 120, 150, 120));
	painter->setPen(pen);
	QPainterPath path;
	path.addRect(boundingRect());
	painter->drawPath(path);
	painter->fillPath(path,QColor(120,120,150,100));
}