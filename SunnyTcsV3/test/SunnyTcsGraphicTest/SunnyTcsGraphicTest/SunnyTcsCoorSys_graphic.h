#pragma once

#include "stafix.h"
#include "SunnyTcsMapAdjuster.h"


using namespace basic;
using namespace core;


class SunnyTcsMapItem_graphic :public QGraphicsItem
{
public:
	SunnyTcsMapItem_graphic()
		:QGraphicsItem(nullptr)
	{
		setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable);
	}

	virtual ~SunnyTcsMapItem_graphic() {}

	// 通过 QGraphicsItem 继承
	virtual QRectF boundingRect() const override =0;

	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;

	virtual SunnyTcsMapObject_tag getItemTag()const = 0;

	qint32 getItemId()const { return getItemTag()._id; }
};



class SunnyTcsMapCoorSys_graphic :public SunnyTcsMapCoorSys, public SunnyTcsMapItem_graphic
{
public:
	SunnyTcsMapCoorSys_graphic(QPointF pt,const SunnyTcsMapAdjuster* ad,qint32 id) :SunnyTcsMapCoorSys(id), SunnyTcsMapItem_graphic() {
		this->setPos(pt.x(), pt.y());
		_ad = ad;
		this->setZValue(2);
	}

	// SunnyTcsMapItem_graphic interface
	virtual SunnyTcsMapObject_tag getItemTag() const override;

	QRectF boundingRect() const {
		return QRectF(-_ad->_cs_ex_rect_wid / 2, -_ad->_cs_ex_rect_wid / 2, _ad->_cs_ex_rect_wid, _ad->_cs_ex_rect_wid);
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
		
		QPen pen;
		QColor color = this->isSelected() ? _ad->_item_select_color : _ad->_cs_default_color;
		
		QLineF xline(QPointF(-_ad->_cs_axis_len, 0), QPointF(_ad->_cs_axis_len, 0));
		QLineF yline(QPointF(0, -_ad->_cs_axis_len), QPointF(0, _ad->_cs_axis_len));
		
		QRect exrect(-_ad->_cs_ex_rect_wid / 2, -_ad->_cs_ex_rect_wid / 2, _ad->_cs_ex_rect_wid, _ad->_cs_ex_rect_wid);
		QRect inrect(-_ad->_cs_in_rect_wid / 2, -_ad->_cs_in_rect_wid / 2, _ad->_cs_in_rect_wid, _ad->_cs_in_rect_wid);

		pen.setCapStyle(Qt::RoundCap);
		pen.setColor(color);
		pen.setWidth(_ad->_cs_axis_wid);
		painter->setPen(pen);
		
		//绘制外圆
		painter->drawEllipse(exrect);
		painter->drawEllipse(inrect);
		painter->drawLine(xline);
		painter->drawLine(yline);

		//painter->drawEllipse(QRect(-_ad->_cs_in_rect_wid / 4 , -_ad->_cs_in_rect_wid / 4, _ad->_cs_in_rect_wid / 2, _ad->_cs_in_rect_wid / 2));

		QPolygonF xpoly = getArrow(_xpos);
		QPolygonF ypoly = getArrow(_ypos);
		painter->drawPolygon(xpoly);
		painter->drawPolygon(ypoly);
		QPainterPath path;
		path.addPolygon(xpoly);
		QPainterPath path2;
		path2.addPolygon(ypoly);
		painter->fillPath(path, color);
		painter->fillPath(path2, color);

	}

	virtual QJsonObject toJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_CS_SCENE_X] = (qint32)(this->pos().x());
		jobj[JSON_MAP_CS_SCENE_Y] = (qint32)(this->pos().y());
		jobj[JSON_MAP_CS_AXIS_X] = (qint32)_xpos;
		jobj[JSON_MAP_CS_AXIS_Y] = (qint32)_ypos;
		return jobj;
	}



	virtual bool fromJson(QJsonObject& jobj, QString& err) override{
		if (!jobj.keys().contains(JSON_MAP_CS_SCENE_X) ||
			!jobj.keys().contains(JSON_MAP_CS_SCENE_Y) ||
			!jobj.keys().contains(JSON_MAP_CS_AXIS_X) ||
			!jobj.keys().contains(JSON_MAP_CS_AXIS_Y)) {
			return false;
		}

		qreal sx = static_cast<qreal>(jobj[JSON_MAP_CS_SCENE_X].toInt());
		qreal sy = static_cast<qreal>(jobj[JSON_MAP_CS_SCENE_Y].toInt());
		E_SunnyTcsAxisDirection axisX = static_cast<E_SunnyTcsAxisDirection>(jobj[JSON_MAP_CS_AXIS_X].toInt());
		E_SunnyTcsAxisDirection axisY = static_cast<E_SunnyTcsAxisDirection>(jobj[JSON_MAP_CS_AXIS_Y].toInt());
		this->setPos(sx, sy);
		_xpos = axisX;
		_ypos = axisY;
		return true;
	}


	QPolygonF getArrow(int direction) {
		QPolygonF arr;
		switch (direction) {
		case 1:
			arr << QPointF(_ad->_cs_axis_len +  _ad->_cs_arrow_len/4 , 0) << QPointF(_ad->_cs_axis_len  ,-_ad->_cs_arrow_len /2) << QPointF(_ad->_cs_axis_len + _ad->_cs_arrow_len , 0) << QPointF(_ad->_cs_axis_len, _ad->_cs_arrow_len / 2) << QPointF(_ad->_cs_axis_len + _ad->_cs_arrow_len / 4, 0);
			return arr;
		case 2:
			arr << QPointF(0, -_ad->_cs_axis_len - _ad->_cs_arrow_len / 4) << QPointF(-_ad->_cs_arrow_len / 2, -_ad->_cs_axis_len) << QPointF(0, -(_ad->_cs_axis_len + _ad->_cs_arrow_len)) << QPointF(_ad->_cs_arrow_len / 2, -_ad->_cs_axis_len) << QPointF(0, -_ad->_cs_axis_len - _ad->_cs_arrow_len / 4);
			return arr;
		case 3:
			arr << QPointF(-_ad->_cs_axis_len, _ad->_cs_arrow_len) << QPointF(-_ad->_cs_axis_len, -_ad->_cs_arrow_len) << QPointF(-_ad->_cs_axis_len - _ad->_cs_arrow_len, 0) << QPointF(-_ad->_cs_axis_len, _ad->_cs_arrow_len);
			return arr;
		case 4:
			arr << QPointF(_ad->_cs_arrow_len, _ad->_cs_axis_len) << QPointF(-_ad->_cs_arrow_len, _ad->_cs_axis_len) << QPointF(0, _ad->_cs_axis_len + _ad->_cs_arrow_len) << QPointF(_ad->_cs_arrow_len, _ad->_cs_axis_len);
			return arr;
		default:
			return arr;
		}
	}

	// 将一个现实坐标 转化为 scene
	virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const override
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
		return SunnyTcsAgvCoordinate(E_TWO_DIMENSION,ptsx, ptsy);
	}

	// 将一个scene坐标 转化为 现实坐标
	virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene) const override
	{
		SunnyTcsAgvCoordinate reality(E_TWO_DIMENSION,0,0);
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
	

protected:

	const SunnyTcsMapAdjuster* _ad;


};

