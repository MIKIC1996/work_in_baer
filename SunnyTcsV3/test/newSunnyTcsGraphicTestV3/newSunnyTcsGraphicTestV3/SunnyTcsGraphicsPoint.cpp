#include "SunnyTcsGraphicsPoint.h"


 const QColor SunnyTcsGraphicsPoint::_pt_back_color = QColor(49, 57, 77, 200);		//底色
 const QColor SunnyTcsGraphicsPoint::_pt_ex_color = QColor(186, 205, 255);			//圆框颜色
 const QColor SunnyTcsGraphicsPoint::_pt_rect_color = QColor(75, 130, 255);			//内圆颜色
 const QColor SunnyTcsGraphicsPoint::_pt_park_color = QColor(218, 134, 129, 100);	//停留点颜色
 const QColor SunnyTcsGraphicsPoint::_pt_rubbon_color = Qt::blue;
 const QColor SunnyTcsGraphicsPoint::_pt_ine_color = Qt::red;
 const QColor SunnyTcsGraphicsPoint::_pt_laser_color = Qt::green;
 const QColor SunnyTcsGraphicsPoint::_pt_help_color = Qt::gray;



SunnyTcsGraphicsPoint::SunnyTcsGraphicsPoint( const SunnyTcsGraphicsCoorSys * cs, const SunnyTcsMapAdjuster * ad, QPointF pt)
	:SunnyTcsPoint(0, cs), SunnyTcsMapGraphicItem(), _ad(ad)
{
	_id = _ad->nextPtId();
	this->setPos(pt.x(), pt.y());
	updateData();
	this->setZValue(3);
	this->setPointNaga(7);
}


SunnyTcsAgvCoordinate SunnyTcsGraphicsPoint::getSceneXy() const
{
	return _cs->transformToScene(_rxy);
}


void SunnyTcsGraphicsPoint::updateData()
{
	SunnyTcsAgvCoordinate&& ret = _cs->transformToReality(SunnyTcsAgvCoordinate(E_TWO_DIMENSION, this->pos().x(), this->pos().y()));
	this->_rxy._x = ret._x;
	this->_rxy._y = ret._y;
}

QRectF SunnyTcsGraphicsPoint::boundingRect() const
{
	return QRectF(
		- META_DIVIDE(qint32,_pt_ex_wid,2),
		- META_DIVIDE(qint32, _pt_ex_wid, 2),
		_pt_ex_wid,
		_pt_ex_wid
	);
}

void SunnyTcsGraphicsPoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//quint64 start = QDateTime::currentMSecsSinceEpoch();

	updateData();
	QPen pen;
	//绘制上圆
	QColor lineColor = this->isSelected() ? _ad->_item_select_color : _pt_ex_color;
	pen.setWidth(100);
	pen.setColor(lineColor);
	painter->setPen(pen);
	QRectF ex_rect(
		META_REVERSE(qint32 , META_DIVIDE(qint32 ,_pt_ex_wid , 2)),
		META_REVERSE(qint32, META_DIVIDE(qint32, _pt_ex_wid, 2)),
		_pt_ex_wid,
		_pt_ex_wid
	);
	QPainterPath ex_ellipse;
	ex_ellipse.addEllipse(ex_rect);
	painter->drawPath(ex_ellipse);
	painter->fillPath(ex_ellipse, lineColor);

	//绘制导航色
	if (_nagaMode & 1) { //支持色带导航
		QConicalGradient conical(0, 0, 0);
		conical.setColorAt(0.0, _pt_rubbon_color);
		conical.setColorAt(0.33, QColor(0, 0, 0, 0));
		painter->setBrush(conical);
		painter->drawEllipse(ex_rect);
	}
	if (_nagaMode & 2) {
		QConicalGradient conical(0, 0, 120);
		conical.setColorAt(0.0, _pt_ine_color);
		conical.setColorAt(0.33, QColor(0, 0, 0, 0));
		painter->setBrush(conical);
		painter->drawEllipse(ex_rect);
	}
	if (_nagaMode & 4) {
		QConicalGradient conical(0, 0, 240);
		conical.setColorAt(0.0, _pt_laser_color);
		conical.setColorAt(0.33, QColor(0, 0, 0, 0));
		painter->setBrush(conical);
		painter->drawEllipse(ex_rect);
	}

	//画内圆
	QPainterPath in_ellipse;
	QColor rectColor = _nagaMode == 0 ? _pt_help_color : _pt_rect_color;
	in_ellipse.addEllipse(QRectF(-_pt_rect_wid / 2, -_pt_rect_wid / 2, _pt_rect_wid, _pt_rect_wid));
	painter->drawPath(in_ellipse);
	painter->fillPath(in_ellipse, rectColor);

	//字体
	QFont font;
	font.setPointSize(_pt_font_size);
	font.setFamily("Microsoft YaHei");
	painter->setFont(font);
	QTextOption text_option;
	text_option.setAlignment(Qt::AlignCenter);

	painter->drawText(QRectF(-_pt_text_rect_len / 2, _pt_text_rect_wid, _pt_text_rect_len, _pt_text_rect_wid),
		QString("(") + QString::number(_rxy._x) + "," + QString::number(_rxy._y) + ")" + QString(" : ") + QString::number(_absPos),
		text_option
	);

	//qDebug() << "draw point " << (QDateTime::currentMSecsSinceEpoch() - start);
}

SunnyTcsMapObject_tag SunnyTcsGraphicsPoint::getItemTag() const
{
	return this->getTag();
}
