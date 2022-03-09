#pragma once


#include "stafix.h"
#include "SunnyTcsCoorSys_graphic.h"

using namespace core;

class SunnyTcsPoint_graphic :public SunnyTcsMapPoint, public SunnyTcsMapItem_graphic
{
public:
	SunnyTcsPoint_graphic( const SunnyTcsMapCoorSys_graphic* cs,
		qint32 id,
		const SunnyTcsMapAdjuster* ad ,
		qint32 type = 7, //默认为全支持
		QPointF pt = QPointF(0,0) 
	) :SunnyTcsMapPoint( cs, id, type), SunnyTcsMapItem_graphic() 
	{
		this->setPos(pt.x(), pt.y());
		updateData();
		_ad = ad;
		this->setZValue(3);
	}

	// SunnyTcsMapItem_graphic interface
	virtual SunnyTcsMapObject_tag getItemTag() const override;

	QRectF boundingRect() const {
		return QRectF(-_ad->_pt_ex_wid / 2, -_ad->_pt_ex_wid / 2, _ad->_pt_ex_wid, _ad->_pt_ex_wid);
	}


	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
		updateData();
		QPen pen;
		QLinearGradient linear;

		//绘制上圆
		QColor lineColor = this->isSelected()&& _ad->_status== E_EDIT ? _ad->_item_select_color : _ad->_pt_ex_color;
		pen.setWidth(100);
		pen.setColor(lineColor);
		painter->setPen(pen);
		linear.setColorAt(0, lineColor);
		linear.setColorAt(1, lineColor);
		painter->setBrush(linear);
		painter->drawEllipse(QRectF(-_ad->_pt_ex_wid / 2, -_ad->_pt_ex_wid / 2, _ad->_pt_ex_wid, _ad->_pt_ex_wid));
		
		//绘制导航色
		if (_nagaMode & 1) { //支持色带导航
			QConicalGradient conical(0, 0, 0);
			conical.setColorAt(0.0, _ad->_pt_rubbon_color);
			//conical.setColorAt(0.3, _ad->_pt_rubbon_color);
			conical.setColorAt(0.33, QColor(0,0,0,0));
			painter->setBrush(conical);
			painter->drawEllipse(QRectF(-_ad->_pt_ex_wid / 2, -_ad->_pt_ex_wid / 2, _ad->_pt_ex_wid, _ad->_pt_ex_wid));
		}
		if (_nagaMode & 2) {
			QConicalGradient conical(0, 0, 120);
			conical.setColorAt(0.0, _ad->_pt_ine_color);
			//conical.setColorAt(0.3, _ad->_pt_ine_color);
			conical.setColorAt(0.33, QColor(0, 0, 0, 0));
			painter->setBrush(conical);
			painter->drawEllipse(QRectF(-_ad->_pt_ex_wid / 2, -_ad->_pt_ex_wid / 2, _ad->_pt_ex_wid, _ad->_pt_ex_wid));
		}
		if (_nagaMode & 4) {
			QConicalGradient conical(0, 0, 240);
			conical.setColorAt(0.0, _ad->_pt_laser_color);
			//conical.setColorAt(0.3, _ad->_pt_laser_color);
			conical.setColorAt(0.33, QColor(0, 0, 0, 0));
			painter->setBrush(conical);
			painter->drawEllipse(QRectF(-_ad->_pt_ex_wid / 2, -_ad->_pt_ex_wid / 2, _ad->_pt_ex_wid, _ad->_pt_ex_wid));
		}
		
		QColor rectColor = _nagaMode == 0 ? _ad->_pt_help_color : _ad->_pt_rect_color;
		linear.setColorAt(0, rectColor);
		linear.setColorAt(1, rectColor);
		painter->setBrush(linear);
		painter->drawEllipse(QRectF(-_ad->_pt_rect_wid / 2, -_ad->_pt_rect_wid / 2, _ad->_pt_rect_wid, _ad->_pt_rect_wid));


		//字体
		QFont font;
		font.setPointSize(_ad->_pt_font_size);
		font.setFamily("Microsoft YaHei");
		painter->setFont(font);
		QTextOption text_option;
		text_option.setAlignment(Qt::AlignCenter);
		painter->drawText(QRectF(-_ad->_pt_text_rect_len / 2, _ad->_pt_text_rect_wid, _ad->_pt_text_rect_len, _ad->_pt_text_rect_wid),
			QString("(") + QString::number(_rxy._x) + "," + QString::number(_rxy._y) + ")"+ QString(" : ") +QString ::number( _absPos)  ,
			text_option
		);
	}

	SunnyTcsAgvCoordinate getSceneXy()const {
		return _cs->transformToScene(_rxy);
	}


	//从当前的Sx Sy计算出RX RY 只有图形库中需要用到这个函数，因为坐标系会移动，这时候需要实时更新rx ry
	void updateData() {
		SunnyTcsAgvCoordinate&& ret = _cs->transformToReality( SunnyTcsAgvCoordinate(E_TWO_DIMENSION, this->pos().x(), this->pos().y()));
		this->_rxy._x = ret._x;
		this->_rxy._y = ret._y;
	}

	virtual QJsonObject toJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_PT_ID] = _id;
		jobj[JSON_MAP_PT_NAME] = _name;
		jobj[JSON_MAP_PT_ABS_POS] = _absPos;
		jobj[JSON_MAP_PT_REALITY_X] = _rxy._x;
		jobj[JSON_MAP_PT_REALITY_Y] = _rxy._y;
		jobj[JSON_MAP_PT_SPT_NAGAMODE] = _nagaMode;
		return jobj;
	}

	virtual bool fromJson(QJsonObject& jobj, QString& err)override {
		if (
			!jobj.keys().contains(JSON_MAP_PT_ID) ||
			!jobj.keys().contains(JSON_MAP_PT_NAME) ||
			!jobj.keys().contains(JSON_MAP_PT_ABS_POS) ||
			!jobj.keys().contains(JSON_MAP_PT_REALITY_X) ||
			!jobj.keys().contains(JSON_MAP_PT_REALITY_Y) ||
			!jobj.keys().contains(JSON_MAP_PT_SPT_NAGAMODE)
			) {
			return false;
		}
		qint32 id = jobj[JSON_MAP_PT_ID].toInt();
		QString name = jobj[JSON_MAP_PT_NAME].toString();
		qint32 absPos = jobj[JSON_MAP_PT_ABS_POS].toInt();
		qint32 rx = jobj[JSON_MAP_PT_REALITY_X].toInt();
		qint32 ry = jobj[JSON_MAP_PT_REALITY_Y].toInt();
		qint32 sptNaga = jobj[JSON_MAP_PT_SPT_NAGAMODE].toInt();

		_id = id;
		_name = name;
		_absPos = absPos;
		_rxy._dim = E_TWO_DIMENSION;
		_rxy._x = rx;
		_rxy._y = ry;
		Q_ASSERT(_cs);
		SunnyTcsAgvCoordinate&& sxy = _cs->transformToScene(SunnyTcsAgvCoordinate(E_TWO_DIMENSION, rx, ry));
		this->setPos((qreal)(sxy._x), (qreal)(sxy._y));
		_nagaMode = sptNaga;
		return true;
	}

protected:
	const SunnyTcsMapAdjuster* _ad;
	QString _name;
};
