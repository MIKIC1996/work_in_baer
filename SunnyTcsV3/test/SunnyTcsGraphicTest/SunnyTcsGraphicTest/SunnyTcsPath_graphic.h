#pragma once


#include "stafix.h"
#include "SunnyTcsCoorSys_graphic.h"
#include "SunnyTcsPoint_graphic.h"

using namespace core;

class SunnyTcsPath_graphic :public SunnyTcsMapPath, public SunnyTcsMapItem_graphic
{
public:
	SunnyTcsPath_graphic(
		qint32 id,
		const SunnyTcsMapAdjuster* ad,
		const SunnyTcsPoint_graphic* start,
		const SunnyTcsPoint_graphic* end ,
		const SunnyTcsPoint_graphic* ctrl = nullptr,
		qint32 positiveSpeed = 0
	)
		:SunnyTcsMapPath(id, start,end,ctrl,positiveSpeed), SunnyTcsMapItem_graphic() ,_ad(ad)
	{
		this->setPos( (start->pos().x() + end->pos().x())/2 , (start->pos().y()+ end->pos().y())/2 );
		this->setZValue(1);
		setFlags(QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable);
	}

	// QGraphicsItem interface
	virtual SunnyTcsMapObject_tag getItemTag() const override;

	QRectF boundingRect() const {
		SunnyTcsAgvCoordinate&& st_sce = dynamic_cast<const SunnyTcsPoint_graphic*>(_start)->getSceneXy();
		SunnyTcsAgvCoordinate&& ed_sce = dynamic_cast<const SunnyTcsPoint_graphic*>(_end)->getSceneXy();
		QPointF start(st_sce._x - this->pos().x(), st_sce._y - this->pos().y());//必须按照item坐标来画点，也就是从sx 转为 ix
		QPointF end(ed_sce._x - this->pos().x(), ed_sce._y - this->pos().y());
		
		

		return QRectF(
			start.x() < end.x() ? start.x() : end.x(),
			start.y() < end.y() ? start.y() : end.y(),
			qAbs(start.x() - end.x()),
			qAbs(start.y()-end.y())
		);
	}


	void setCtrlPoint(const SunnyTcsPoint_graphic* pt) {
		_ctrl = pt;
	}
	
	void setStartPoint(const SunnyTcsPoint_graphic* pt) {
		_start = pt;
	}

	void setEndPoint(const SunnyTcsPoint_graphic* pt) {
		_end = pt;
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


		SunnyTcsAgvCoordinate&& st_sce = dynamic_cast<const SunnyTcsPoint_graphic*>(_start)->getSceneXy();
		QPointF start_sce(st_sce._x, st_sce._y);

		SunnyTcsAgvCoordinate&& ed_sce = dynamic_cast<const SunnyTcsPoint_graphic*>(_end)->getSceneXy();
		QPointF end_sce =QPointF(ed_sce._x , ed_sce._y);
		
		this->setPos((start_sce.x() + end_sce.x()) / 2, (start_sce.y() + end_sce.y()) / 2);
		
		QPointF start(start_sce.x() - this->pos().x(), start_sce.y() - this->pos().y());//必须按照item坐标来画点，也就是从sx 转为 ix
		QPointF start_copy(start);
		QPointF end(end_sce.x()- this->pos().x(), end_sce.y() - this->pos().y());
		QPointF quadPt( this->pos().x(), this->pos().y());

		QPen pen;
		QLinearGradient linear;
		
		

		//绘制底圆
		pen.setWidth(0);
		pen.setColor(_ad->_pt_back_color);
		painter->setPen(pen);

		linear.setColorAt(0, _ad->_pt_park_color);
		linear.setColorAt(1, _ad->_pt_park_color);
		painter->setBrush(linear);
		if (_start && dynamic_cast<const SunnyTcsPoint_graphic*>(_start)->isSelected()) {
			painter->drawEllipse(QRectF(start.x() - _ad->_pt_park_wid / 2, start.y() - _ad->_pt_park_wid / 2, _ad->_pt_park_wid, _ad->_pt_park_wid));
		}
		if (_end && dynamic_cast<const SunnyTcsPoint_graphic*>(_end)->isSelected()) {
			painter->drawEllipse(QRectF(end.x() - _ad->_pt_park_wid / 2, end.y() - _ad->_pt_park_wid / 2, _ad->_pt_park_wid, _ad->_pt_park_wid));
		}

		linear.setColorAt(0, _ad->_pt_back_color);
		linear.setColorAt(1, _ad->_pt_back_color);
		painter->setBrush(linear);
		if (_start) {
			painter->drawEllipse(QRectF(start.x() - _ad->_pt_back_wid / 2, start.y() - _ad->_pt_back_wid / 2, _ad->_pt_back_wid, _ad->_pt_back_wid));
		}
		if(_end) {
			painter->drawEllipse(QRectF(end.x() - _ad->_pt_back_wid / 2, end.y() - _ad->_pt_back_wid / 2, _ad->_pt_back_wid, _ad->_pt_back_wid));
		}
		

		//设置笔
		pen.setColor(_ad->_pt_back_color);
		pen.setWidth(_ad->_pt_ex_wid);
		pen.setCapStyle(Qt::RoundCap);
		painter->setPen(pen);
		painter->setBrush(QBrush());
		QPointF& st_arrow = start;

		if (!_ctrl) {
			//根据 坐标轴 sx sy 和点的现实rx ry 推算 点的sx 和sy
			painter->drawLine(start, end);

			if (this->isSelected()) {
				pen.setWidth(_ad->_ph_selected_wid);
				pen.setColor(_ad->_ph_selected_color);
				painter->setPen(pen);
				painter->drawLine(start, end);
			}
		}
		else {
			QPainterPath path;
			SunnyTcsAgvCoordinate&& ct_sce = dynamic_cast<const SunnyTcsPoint_graphic*>(_ctrl)->getSceneXy();
			qDebug() << ct_sce._x;
			qDebug() << ct_sce._y;
			quadPt.setX(ct_sce._x - this->pos().x());
			quadPt.setY(ct_sce._y - this->pos().y());
			
			path.moveTo(start);
			path.quadTo(quadPt, end);
			painter->drawPath(path);

			if (this->isSelected()) {
				pen.setWidth(_ad->_ph_selected_wid);
				pen.setColor(_ad->_ph_selected_color);
				painter->setPen(pen);
				painter->drawPath(path);
			}
			

			QVector<qreal> dashs;
			dashs << 3 << 4;
			pen.setDashPattern(dashs);
			pen.setColor(_ad->_ph_dash_color);
			pen.setWidth(_ad->_ph_dash_wid);
			painter->setPen(pen);
			painter->drawLine(start, quadPt);
			painter->drawLine(end, quadPt);
			st_arrow = quadPt;

		}

		QPainterPath arrow;
		arrow.addPolygon(getArrow(st_arrow, end));
		if (this->_isDoubleDirection) {
			arrow.addPolygon(getArrow( (_ctrl ?  st_arrow : end) , start_copy) );
		}

		pen.setWidth(0);
		pen.setColor(Qt::white);
		painter->setPen(pen);
		painter->drawPath(arrow);
		painter->fillPath(arrow, Qt::white);

	}


	QPointF startPos()const{
		return (dynamic_cast<const SunnyTcsPoint_graphic*>(_start))->pos();
	}


	


protected:

	QPolygonF getArrow(QPointF from, QPointF to) {
		if (to.x() == from.x()) {//垂直线
			QPolygonF poly;
			qreal y_move1 = to.x() - from.x() > 0.0 ? _ad->_ph_arrow_len : -_ad->_ph_arrow_len;
			qreal y_move2 = to.y() - from.y() > 0.0 ? _ad->_ph_arrow_move : -_ad->_ph_arrow_move;

			poly << QPointF(to.x(), to.y() - y_move2) <<
				QPointF(to.x() + _ad->_ph_arrow_len / 2.0, to.y() - y_move2 - y_move1) <<
				QPointF(to.x() - _ad->_ph_arrow_len / 2.0, to.y() - y_move2 - y_move1) <<
				QPointF(to.x(), to.y() - y_move2);
			return poly;
		}

		
		
		qreal angle = qAtan( qAbs(to.y() - from.y())/ qAbs(to.x() - from.x()));
		qreal x_move = to.x() - from.x() > 0.0 ? _ad->_ph_arrow_move : -_ad->_ph_arrow_move;
		qreal y_move = to.y() - from.y() > 0.0 ? _ad->_ph_arrow_move : -_ad->_ph_arrow_move;
		to.setX(from.x() + to.x() - from.x() - ( x_move * qCos(angle)));
		to.setY(from.y() + to.y() -from.y() - ( y_move * qSin(angle)));


		qint32 fromSx = from.x();
		qint32 fromSy = from.y();
		qint32 toSx = to.x();
		qint32 toSy = to.y();
		qreal tan = (qreal)(toSy - fromSy) / (qreal)(toSx - fromSx);
		 angle = qAtan(tan);

		qreal ptx = 0.0;
		qreal pty = 0.0;
		qreal dx = qAbs(_ad->_ph_arrow_len*qCos(qAbs(angle)));
		qreal dy = qAbs(_ad->_ph_arrow_len*qSin(qAbs(angle)));

		if (toSy - fromSy > 0.0) {
			pty = toSy - dy;
		}
		else {
			pty = toSy + dy;
		}

		if (toSx - fromSx > 0.0) {
			ptx = toSx - dx;
		}
		else {
			ptx = toSx + dx;
		}

		qreal deltaX = 0.5* _ad->_ph_arrow_len* qSin(qAbs(angle));
		qreal deltaY = 0.5* _ad->_ph_arrow_len* qCos(qAbs(angle));

		QPointF f1;
		QPointF f2;
		if ((toSy - fromSy > 0.0 && toSx - fromSx > 0.0) || (toSy - fromSy < 0.0 && toSx - fromSx < 0.0)) {//
			f1.setX(ptx + deltaX);
			f1.setY(pty - deltaY);
			f2.setX(ptx - deltaX);
			f2.setY(pty + deltaY);
		}
		else {
			f1.setX(ptx + deltaX);
			f1.setY(pty + deltaY);
			f2.setX(ptx - deltaX);
			f2.setY(pty - deltaY);
		}
		QPolygonF poly;
		poly << f1 << f2 << to << f1;
		return poly;
	}

	const SunnyTcsMapAdjuster* _ad;
	




};
