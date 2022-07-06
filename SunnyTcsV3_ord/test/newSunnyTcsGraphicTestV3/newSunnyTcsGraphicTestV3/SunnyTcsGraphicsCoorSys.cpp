#include "SunnyTcsGraphicsCoorSys.h"



const QColor SunnyTcsGraphicsCoorSys::_cs_default_color = Qt::gray;


SunnyTcsGraphicsCoorSys::SunnyTcsGraphicsCoorSys(QPointF pt, const SunnyTcsMapAdjuster * ad, qint32 id)
	:SunnyTcsCoorSys(id), SunnyTcsMapGraphicItem(), _ad(ad) 
{
	Q_ASSERT(ad);
	this->setPos(pt.x(), pt.y());
	this->setZValue(1);
}



QRectF SunnyTcsGraphicsCoorSys::boundingRect() const
{
	return QRectF(  
		META_DIVIDE(qint32 , META_REVERSE(qint32, _cs_ex_rect_wid) ,2), 
		META_DIVIDE(qint32 , META_REVERSE(qint32, _cs_ex_rect_wid), 2),
		_cs_ex_rect_wid,
		_cs_ex_rect_wid
	);
}

void SunnyTcsGraphicsCoorSys::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPen pen;
	QColor color = this->isSelected() ? _ad->_item_select_color : _cs_default_color;//设置颜色
	pen.setColor(color);
	pen.setWidth(_cs_axis_wid);
	pen.setCapStyle(Qt::RoundCap);
	painter->setPen(pen);
	QLineF xline(QPointF(META_REVERSE(qint32,_cs_axis_len), 0), QPointF(_cs_axis_len, 0));
	QLineF yline(QPointF(0, META_REVERSE(qint32, _cs_axis_len)), QPointF(0, _cs_axis_len));
	//绘制轴线
	painter->drawLine(xline);	
	painter->drawLine(yline);
	//绘制箭头
	QPolygonF xpoly = getArrow(_xpos);
	QPolygonF ypoly = getArrow(_ypos);
	painter->drawPolygon(xpoly);
	painter->drawPolygon(ypoly);
	QPainterPath path;
	path.addPolygon(xpoly);
	path.addPolygon(ypoly);
	painter->fillPath(path, color);
}

SunnyTcsMapObject_tag SunnyTcsGraphicsCoorSys::getItemTag() const
{
	return this->getTag();
}

QPolygonF SunnyTcsGraphicsCoorSys::getArrow(int direction)
{
	QPolygonF arr;
	qreal max_asix_len = META_PLUS(qint32, _cs_axis_len, _cs_arrow_len);
	qreal half_arrow_len = META_DIVIDE(qint32, _cs_arrow_len, 2);

	switch (direction) {
	case 1:
		arr <<
			QPointF(max_asix_len, 0) <<
			QPointF(_cs_axis_len, -half_arrow_len) <<
			QPointF(_cs_axis_len, half_arrow_len) <<
			QPointF(max_asix_len, 0);
		return arr;
	case 2:
		arr <<
			QPointF(0,-max_asix_len) <<
			QPointF(half_arrow_len, -_cs_axis_len) <<
			QPointF(-half_arrow_len, -_cs_axis_len) <<
			QPointF(0, -max_asix_len);
		return arr;
	case 3:
		arr <<
			QPointF(-max_asix_len, 0) <<
			QPointF(-_cs_axis_len, -half_arrow_len) <<
			QPointF(-_cs_axis_len, half_arrow_len) <<
			QPointF(-max_asix_len, 0);
		return arr;
	case 4:
		arr <<
			QPointF(0, max_asix_len) <<
			QPointF(half_arrow_len, _cs_axis_len) <<
			QPointF(-half_arrow_len, _cs_axis_len) <<
			QPointF(0, max_asix_len);
		return arr;
	default:
		return arr;
	}
}


SunnyTcsAgvCoordinate SunnyTcsGraphicsCoorSys::transformToScene(SunnyTcsAgvCoordinate reality) const
{
	qint32 ptsx = 0, ptsy = 0;
	SunnyTcsAgvCoordinate _sxy(E_TWO_DIMENSION, this->pos().x(), this->pos().y());
	switch (_xpos) {
	case Eright:
		ptsx = _sxy._x + reality._x;
		break;
	case Eup:
		ptsy = _sxy._y - reality._x;
		break;
	case Eleft:
		ptsx = _sxy._x - reality._x;
		break;
	case Edown:
		ptsy = _sxy._y + reality._x;
		break;
	}

	switch (_ypos) {
	case Eright:
		ptsx = _sxy._x + reality._y;
		break;
	case Eup:
		ptsy = _sxy._y - reality._y;
		break;
	case Eleft:
		ptsx = _sxy._x - reality._y;
		break;
	case Edown:
		ptsy = _sxy._y + reality._y;
		break;
	}
	return SunnyTcsAgvCoordinate(E_TWO_DIMENSION, ptsx, ptsy);
}



SunnyTcsAgvCoordinate SunnyTcsGraphicsCoorSys::transformToReality(SunnyTcsAgvCoordinate scene) const
{
	SunnyTcsAgvCoordinate reality(E_TWO_DIMENSION, 0, 0);
	SunnyTcsAgvCoordinate _sxy(E_TWO_DIMENSION, this->pos().x(), this->pos().y());
	switch (_xpos) {
	case Eright:
		reality._x = scene._x - _sxy._x;
		break;
	case Eup:
		reality._x = _sxy._y - scene._y;
		break;
	case Eleft:
		reality._x = _sxy._x - scene._x;
		break;
	case Edown:
		reality._x = scene._y - _sxy._y;
		break;
	}
	switch (_ypos) {
	case Eright:
		reality._y = scene._x - _sxy._x;
		break;
	case Eup:
		reality._y = _sxy._y - scene._y;
		break;
	case Eleft:
		reality._y = _sxy._x - scene._x;
		break;
	case Edown:
		reality._y = scene._y - _sxy._y;
		break;
	}
	return reality;
}
