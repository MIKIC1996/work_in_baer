#include "SunnyTcsGraphicsLocation.h"



SunnyTcsGraphicsLocation::SunnyTcsGraphicsLocation(const SunnyTcsMapAdjuster * ad, const SunnyTcsGraphicsPoint * pt)
	:SunnyTcsLocation(0, pt), SunnyTcsMapGraphicItem(), _name(), _ad(ad)
{
	_id = _ad->nextLocId();
	_name = QString("Location ") + QString::number(_id);
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
	QPen pen;
	pen.setWidth(_loc_line_wid);
	painter->setPen(pen);
	painter->drawRect(this->boundingRect());
}


SunnyTcsMapObject_tag SunnyTcsGraphicsLocation::getItemTag() const
{
	return SunnyTcsMapObject_tag();
}

