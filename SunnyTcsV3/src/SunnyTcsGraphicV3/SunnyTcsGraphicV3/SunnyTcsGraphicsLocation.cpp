#include "SunnyTcsGraphicsLocation.h"


const QColor SunnyTcsGraphicsLocation::_loc_dash_color = QColor(120, 120, 140, 200);
const QColor SunnyTcsGraphicsLocation::_loc_ex_color = QColor(186, 205, 255);
QImage SunnyTcsGraphicsLocation::_image;
QImage SunnyTcsGraphicsLocation::_image_selected;


SunnyTcsGraphicsLocation::SunnyTcsGraphicsLocation(const SunnyTcsMapAdjuster * ad, const SunnyTcsGraphicsPoint * pt)
	:SunnyTcsLocation(ad->nextLocId(), pt), SunnyTcsMapGraphicItem(""),  _ad(ad)
{
	_name = QString("location%1").arg(QString::number(_id));
	this->setPos(pt->pos());
	this->setZValue(4);
}

QRectF SunnyTcsGraphicsLocation::boundingRect() const
{
	return QRectF(
		META_REVERSE(qint32 , META_DIVIDE(qint32 ,_loc_ex_wid,2)),
		META_REVERSE(qint32, META_DIVIDE(qint32, _loc_ex_wid, 2)),
		_loc_ex_wid,
		_loc_ex_wid
	);
}


void SunnyTcsGraphicsLocation::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
	if (_image.isNull()||_image_selected.isNull()) { //没有设置图片
		QPen pen;
		pen.setColor(this->isSelected() ? _ad->_item_select_color : _loc_ex_color);
		pen.setWidth(_loc_line_wid);
		painter->setPen(pen);
		painter->drawRect(this->boundingRect());
	}
	else { 
		if (this->isSelected()) {
			painter->drawImage(boundingRect(), _image_selected);
		}
		else {
			painter->drawImage(boundingRect(), _image);
		}

	}
	//绘制与连接点的连线
	SunnyTcsAgvCoordinate&& st_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_linkedPt)->getSceneXy();
	QPointF start_sce(st_sce._x, st_sce._y);
	QPointF start(start_sce.x() - this->pos().x(), start_sce.y() - this->pos().y());//必须按照item坐标来画点，也就是从sx 转为 ix
	
	QVector<qreal> dashs;
	dashs << 3 << 4;
	QPen pen;
	pen.setDashPattern(dashs);
	pen.setColor(_loc_dash_color);
	pen.setWidth(_loc_dash_wid);
	painter->setPen(pen);
	painter->drawLine(start, QPointF(0,0));
}


SunnyTcsMapObject_tag SunnyTcsGraphicsLocation::getItemTag() const
{
	return getTag();
}

