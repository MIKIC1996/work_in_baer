#include "SunnyTcsGraphicsModel.h"




SunnyTcsGraphicsModel::SunnyTcsGraphicsModel(quint64 id, QString name, qint32 wid, qint32 hei, qint32 resolution)
	: SunnyTcsMapAdjuster(wid,hei,resolution) , _id(id), _name(name)
{
	_cs = new SunnyTcsGraphicsCoorSys(QPointF(0, 0), this);
	this->addItem(_cs);
	setSceneRect(-_sceneWid / 2, -_sceneHei / 2,_sceneWid, _sceneHei);
	update();
}





void SunnyTcsGraphicsModel::drawBackground(QPainter * painter, const QRectF & rect)
{
	painter->fillRect(this->sceneRect(), QColor(63, 72, 101));

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
