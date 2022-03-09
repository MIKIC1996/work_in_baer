#include "SunnyTcsVehicle_normal_graphic.h"




SunnyTcsVehicle_normal_graphic::SunnyTcsVehicle_normal_graphic(const SunnyTcsMapCoorSys_graphic * cs, qint32 id, const SunnyTcsMapAdjuster * ad,QPointF pt, QString name,
	QString ip, quint16 port, qint32 groupId)
	:SunnyTcsMapVehicle_normal(cs,id,ip,port,groupId),SunnyTcsVehicle_graphic(ad,name)
{

	if (_name.isEmpty()) {
		_name = QString("AGV ") + QString::number(_id);
	}

	this->setPos(pt);
	this->setZValue(4);
}


SunnyTcsMapObject_tag SunnyTcsVehicle_normal_graphic::getItemTag() const
{
	return this->getTag();
}


QRectF SunnyTcsVehicle_normal_graphic::boundingRect() const
{
	qreal len = _ladarRadius - ( qSqrt(2)* _ladarRadius  - _ladarRadius ) /3;
	return QRectF(-len , -len , len*2.0, len*2.0);
}


void SunnyTcsVehicle_normal_graphic::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

	QPen pen;
	pen.setWidth(0);
	
	//更新坐标
	_coor._dim = E_TWO_DIMENSION;

	SunnyTcsAgvCoordinate rea= _cs->transformToReality(SunnyTcsAgvCoordinate(E_TWO_DIMENSION,pos().x(), this->pos().y()));

	this->_coor._x = rea._x;
	this->_coor._y = rea._y;

	//雷达圈 与 碰撞检测
	bool isColl = false;
	if (this->collidingItems().count() > 0) {
		SunnyTcsMapItem_graphic* item = dynamic_cast<SunnyTcsMapItem_graphic*>(this->collidingItems().first());
		if(item&& item->getItemTag()._eletype == Evehicle){
			isColl = true;
		}
	}

	QColor ladar_color = isColl ? _ad->_ve_ladar_warn_color: _ad->_ve_ladar_color;
	pen.setColor(ladar_color);
	painter->setPen(pen);
	
	QRadialGradient radial(0,0, _ladarRadius);
	radial.setColorAt(0.0, _ad->_ve_ladar_from_color);
	radial.setColorAt(1.0, ladar_color);
	painter->setBrush(radial);
	painter->drawEllipse(QRectF(-_ladarRadius , -_ladarRadius , _ladarRadius* 2.0, _ladarRadius*2.0));

	QPainterPath laderRect;
	qreal lader_radius = (qreal)(QDateTime::currentMSecsSinceEpoch() % 6000L) / 6000L * _ladarRadius;
	laderRect.addEllipse(QRectF(-lader_radius, -lader_radius, lader_radius* 2.0, lader_radius*2.0));
	painter->fillPath(laderRect, _ad->_ve_ladar_deco_color);

	painter->setBrush(QBrush());
	pen.setColor(_ad->_ve_back_color);
	painter->setPen(pen);


	//车本体
	QPainterPath exRect;
	exRect.addEllipse(QRectF(   -_veLen /2.0 , -_veLen / 2.0, _veLen, _veLen));
	painter->fillPath(exRect, _ad->_ve_back_color);

	QColor inColor = _error_normal != 0 ? _ad->_ve_error_color : (_warning_normal != 0 ? _ad->_ve_warning_color : _ad->_ve_status_color_hash[_status]);
	
	qreal inLen = _veLen *0.8;
	QPainterPath inRect;
	inRect.addEllipse(QRectF(-inLen / 2, -inLen / 2, inLen, inLen));
	painter->fillPath(inRect, inColor);
	
	QRectF text(-_ad->_ve_text_len / 2, _ad->_ve_text_hei, _ad->_ve_text_len, _ad->_ve_text_hei);
	

	//车的字体
	QPen fontPen;
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(_ad->_ve_font_size);
	painter->setFont(font);
	QTextOption text_option;
	text_option.setAlignment(Qt::AlignCenter);
	fontPen.setWidth(10);
	fontPen.setColor(Qt::white);
	painter->setPen(fontPen);
	QString pos = this->getCurrentPos()._eletype == Epoint ? QString(" point: ") : this->getCurrentPos()._eletype == Epath ? QString(" path: ") : QString(" noType :");
	pos += QString::number(this->getCurrentPos()._id);
	painter->drawText(text, _name + pos, text_option);


	//info 泡
// 	QRectF info(0, -_ad->_ve_info_rect_hei - _ad->_ve_rect_short_wid , _ad->_ve_info_rect_wid , _ad->_ve_info_rect_hei);
// 	QPolygonF info_arrow;
// 	info_arrow << QPointF(200, -_ad->_ve_rect_short_wid*0.7) <<
// 		QPointF(0, -_ad->_ve_rect_short_wid) <<
// 		QPointF(_ad->_ve_info_rect_wid * 0.1, -_ad->_ve_rect_short_wid) <<
// 		QPointF(200, -_ad->_ve_rect_short_wid*0.7);
// 
// 	QPainterPath info_path;
// 	info_path.addPolygon(info_arrow);
// 
// 	painter->drawRect(QRectF(0,-_ad->_ve_info_rect_hei* 0.5 , _ad->_ve_info_rect_hei* 0.5, _ad->_ve_info_rect_hei* 0.5 - _ad->_ve_rect_short_wid));
// 	painter->drawRoundRect(info, 25);
// 	painter->drawPath(info_path);

	
	
}
