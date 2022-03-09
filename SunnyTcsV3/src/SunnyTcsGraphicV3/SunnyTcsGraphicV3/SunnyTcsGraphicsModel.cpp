#include "SunnyTcsGraphicsModel.h"




SunnyTcsGraphicsModel::SunnyTcsGraphicsModel(quint64 id, QString name, qint32 wid, qint32 hei, qint32 resolution)
	: SunnyTcsMapAdjuster(wid,hei,resolution) , _id(id), _name(name),_pathTempPoint(nullptr),_pathTemp(nullptr),_pts(),_phs(),_locs(),_cs(nullptr),_aera(nullptr)
{

	setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);//内部索引在 图元delete后 会导致奔溃
	_cs = new SunnyTcsGraphicsCoorSys(QPointF(0, 0), this);
	this->addItem(_cs);
	setSceneRect(-_sceneWid / 2, -_sceneHei / 2,_sceneWid, _sceneHei);
	update();
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
			//直线结束点
			end->setZValue(GRAPHICS_LOW_ZVALUE);//把自己线弄到底下去
			SunnyTcsGraphicsPoint* tempEnd = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));//获取当前位置点
			if (tempEnd && tempEnd != end) { //当前位置有另外的点
				_pathTemp->setEnd(tempEnd);
				this->removeItem(end);
				delete end; //原来使用的temp end点就没用了
				end = tempEnd;
			}
			_pathTemp->setIsEndNew(tempEnd ? false : true); //设置直线终点是否为新点
			end->setZValue(GRAPHICS_POINT_ZVALUE);

			_pts.insert(start->getElementId(), start);
			_pts.insert(end->getElementId(), end);
			_phs.insert(_pathTemp->getElementId(), _pathTemp);
			ret = _pathTemp;
			_pathTemp = nullptr;
			_pathTempPoint = nullptr;			
		}
		else if (isArch && !ctrl) {
			//曲线结束点
			end->setZValue(GRAPHICS_LOW_ZVALUE);//把自己线弄到底下去
			SunnyTcsGraphicsPoint* tempEnd = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));//获取当前位置点
			bool hasOne = (tempEnd && tempEnd != end);
			tempEnd = hasOne ? tempEnd : new  SunnyTcsGraphicsPoint(_cs, this, pt); //新的结束点
			_pathTemp->setIsEndNew(hasOne ? false : true);
			if (!hasOne) { //tempEnd 就是 new SunnyTcsGraphicsPoint
				this->addItem(tempEnd); //画
			}

			//_pathTempPoint 还是 原end ，作为新的 ctrl点
			end->setZValue(GRAPHICS_POINT_ZVALUE);
			_pathTemp->setEnd(tempEnd);
			_pathTemp->setCtrl(end); //原end设置为中点
			
		}
		else {
			ctrl->setZValue(GRAPHICS_LOW_ZVALUE);//把自己线弄到底下去
			SunnyTcsGraphicsPoint* tempCtrl = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));//获取当前位置点
			if (tempCtrl && tempCtrl != ctrl) { //当前位置有另外的点
				_pathTemp->setCtrl(tempCtrl);
				this->removeItem(ctrl);
				delete ctrl; //原来使用的temp end点就没用了
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

SunnyTcsGraphicsPoint* SunnyTcsGraphicsModel::addGraphicsPoint(QPointF pt)
{
	if (isOutOfSceneRect(pt)) {
		throw SunnyTcsException<ERROR_GRAPHICS_POINT_OUT_SCENE>();
	}
	SunnyTcsGraphicsPoint* ptr = new SunnyTcsGraphicsPoint(_cs, this, pt);
	addGraphicsPoint(ptr);
	return ptr;
}



SunnyTcsGraphicsPath*  SunnyTcsGraphicsModel::addGraphicsPath(QPointF pt)
{
	if (isOutOfSceneRect(pt)) {
		throw SunnyTcsException<ERROR_GRAPHICS_PATH_OUT_SCENE>();
	}
	//start end
	SunnyTcsGraphicsPoint* tempStart = dynamic_cast<SunnyTcsGraphicsPoint*>(itemAt(pt, QTransform()));
	SunnyTcsGraphicsPoint* start = tempStart ? tempStart : new SunnyTcsGraphicsPoint(_cs, this, pt); //当前位置已将有点就用该点
	_pathTempPoint = new SunnyTcsGraphicsPoint(_cs, this, pt);
	//tempPath
	_pathTemp = new SunnyTcsGraphicsPath(this, start, _pathTempPoint);

	if (!tempStart) {
		this->addItem(start);
	}
	_pathTemp->setIsStartNew(tempStart ? false : true);//设置起点是否为全新点
	this->addItem(_pathTempPoint);
	this->addItem(_pathTemp);
	return _pathTemp;
}



SunnyTcsGraphicsLocation*  SunnyTcsGraphicsModel::addGraphicsLocation(QPointF pt)
{
	SunnyTcsMapGraphicItem* item = dynamic_cast<SunnyTcsMapGraphicItem*>(itemAt(pt, QTransform()));
	if (item && item->getItemTag()._eletype == Epoint) {
		SunnyTcsGraphicsLocation* loc = new SunnyTcsGraphicsLocation(this,_pts[item->getItemId()]);
		addGraphicsLocation(loc);
		return loc;
	}
	return nullptr;
}



SunnyTcsGraphicsVehicle* SunnyTcsGraphicsModel::addGraphicsVehicle(QPointF pt, SunnyTcsAgvCode code)
{
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
		addGraphicsVehicle(ve);
	}
	return ve;
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
	removeItem(item);//取消显示
	_phs.remove(item->getItemId());//从PHS中删除
								   //最后删除路径
	return true;
}



bool SunnyTcsGraphicsModel::removeGraphicsLocation(SunnyTcsGraphicsLocation * item)
{
	if (!item) {
		return false;
	}
	removeItem(item);//取消显示
	_locs.remove(item->getItemId());//从locs中删除
	return true;
}



bool SunnyTcsGraphicsModel::removeGraphicsVehicle(SunnyTcsGraphicsVehicle * item)
{
	if (!item) {
		return false;
	}
	removeItem(item);//取消显示
	_ves.remove(item->getItemId());//从locs中删除
	return true;
}



void SunnyTcsGraphicsModel::xEqualDistributionOfPoints()
{
	QList<SunnyTcsGraphicsPoint*>&& pts = selectedPointItems();
	if (pts.count() < 3)return; //三个点一下无法进行分布

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
	if (pts.count() < 3)return; //三个点一下无法进行分布

	std::sort(pts.begin(), pts.end(), [](SunnyTcsGraphicsPoint* p1, SunnyTcsGraphicsPoint* p2)->bool {return p1->pos().y() < p2->pos().y(); });
	qreal interval = (pts.last()->pos().y() - pts.first()->pos().y()) / (qreal)(pts.count()-1);
	qreal start = pts.first()->pos().y();
	for (qint32 i = 1; i < pts.count() - 1; ++i) {
		start += interval;
		pts[i]->setY(start);
	}
}



void SunnyTcsGraphicsModel::drawBackground(QPainter * painter, const QRectF & rect)
{
	painter->fillRect(this->sceneRect(), QColor(70, 80, 110));

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

// QPainterPath SunnyTcsGraphicsSelectAera::shape() const
// {
// 	QPainterPath path;
// 	if (_curAera == ERect) {//方框选取
// 		path.addRect(QRectF(_tracks[0], _tracks[1]));
// 	}
// 	else { //多边形选取
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
