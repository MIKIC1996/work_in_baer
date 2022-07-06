#include "SunnyTcsGraphicsPath.h"

 const QColor SunnyTcsGraphicsPath::_ph_back_color = QColor(49, 57, 77, 200);
 const QColor SunnyTcsGraphicsPath::_ph_selected_color = QColor(75, 130, 255);
 const QColor SunnyTcsGraphicsPath::_ph_dash_color = QColor(120, 120, 140, 200);


SunnyTcsGraphicsPath::SunnyTcsGraphicsPath( const SunnyTcsMapAdjuster * ad, const SunnyTcsGraphicsPoint * start, const SunnyTcsGraphicsPoint * end, const SunnyTcsGraphicsPoint * ctrl)
	:SunnyTcsPath(ad->nextPhId()), SunnyTcsMapGraphicItem(""), _ad(ad),
	_last_start(),_last_end(),_last_ctrl(),_arrow_start(),_arrow_end(),
	_isStartNew(false),_isEndNew(false),_isCtrlNew(false)
{
	_name = QString("path%1").arg(QString::number(_id));
	this->setStart(start);
	this->setEnd(end);
	this->setCtrl(ctrl);
	if (_start && _end) {
		this->setPos((start->pos().x() + end->pos().x()) / 2, (start->pos().y() + end->pos().y()) / 2);
	}
	this->setZValue(2);
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);//设置不可移动
}


QRectF SunnyTcsGraphicsPath::boundingRect() const
{
	SunnyTcsAgvCoordinate&& st_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_start)->getSceneXy();
	SunnyTcsAgvCoordinate&& ed_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_end)->getSceneXy();
	QPointF start((qreal)st_sce._x - this->pos().x(), (qreal)st_sce._y - this->pos().y());//必须按照item坐标来画点，也就是从sx 转为 ix
	QPointF end((qreal)ed_sce._x - this->pos().x(), (qreal)ed_sce._y - this->pos().y());
	QPointF miner(start.x() < end.x() ? start.x() : end.x(), start.y() < end.y() ? start.y() : end.y());//取坐标值小的点
	QPointF maxer(start.x() > end.x() ? start.x() : end.x(), start.y() > end.y() ? start.y() : end.y());//取坐标值大的点

	if (_ctrl) {
		SunnyTcsAgvCoordinate&& cl_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_ctrl)->getSceneXy();
		QPointF ctrl((qreal)cl_sce._x - this->pos().x(), (qreal)cl_sce._y - this->pos().y());
		miner.setX(miner.x() < ctrl.x() ? miner.x() : ctrl.x());
		miner.setY(miner.y() < ctrl.y() ? miner.y() : ctrl.y());
		maxer.setX(maxer.x() > ctrl.x() ? maxer.x() : ctrl.x());
		maxer.setY(maxer.y() > ctrl.y() ? maxer.y() : ctrl.y());
	}
	
	if (miner.x() == maxer.x()) {//同x
		miner.setX(miner.x() - 800);
		maxer.setX(maxer.x() + 800);
	}
	else if (miner.y() == maxer.y()) {//同y
		miner.setY(miner.y() - 800);
		maxer.setY(maxer.y() + 800);
	}

	return QRectF(
		miner.x(),
		miner.y(),
		qAbs(maxer.x() - miner.x()),
		qAbs(maxer.y() - miner.y())
	);
}


void SunnyTcsGraphicsPath::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//quint64 starttime = QDateTime::currentMSecsSinceEpoch();

	SunnyTcsAgvCoordinate&& st_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_start)->getSceneXy();
	QPointF start_sce(st_sce._x, st_sce._y);
	SunnyTcsAgvCoordinate&& ed_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_end)->getSceneXy();
	QPointF end_sce = QPointF(ed_sce._x, ed_sce._y);
	
	QPointF start(start_sce.x() - this->pos().x(), start_sce.y() - this->pos().y());//必须按照item坐标来画点，也就是从sx 转为 ix
	QPointF start_copy(start);
	QPointF end(end_sce.x() - this->pos().x(), end_sce.y() - this->pos().y());
	QPointF quadPt(this->pos().x(), this->pos().y());

	//设置笔
	QPen pen;
	pen.setColor(_ph_back_color);
	pen.setWidth(_ph_ex_wid);
	pen.setCapStyle(Qt::RoundCap);
	painter->setPen(pen);
	QPointF& st_arrow = start;

	if (!_ctrl) {
		//根据 坐标轴 sx sy 和点的现实rx ry 推算 点的sx 和sy
		painter->drawLine(start, end);
		if (this->isSelected()) {
			pen.setWidth(_ph_selected_wid);
			pen.setColor(_ph_selected_color);
			painter->setPen(pen);
			painter->drawLine(start, end);
		}
	}
	else {
		QPainterPath path;
		SunnyTcsAgvCoordinate&& ct_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_ctrl)->getSceneXy();
		quadPt.setX(ct_sce._x - this->pos().x());
		quadPt.setY(ct_sce._y - this->pos().y());
		path.moveTo(start);
		path.quadTo(quadPt, end);
		painter->drawPath(path);

		if (this->isSelected()) {
			pen.setWidth(_ph_selected_wid);
			pen.setColor(_ph_selected_color);
			painter->setPen(pen);
			painter->drawPath(path);
		}

		QVector<qreal> dashs;
		dashs << 3 << 4;
		pen.setDashPattern(dashs);
		pen.setColor(_ph_dash_color);
		pen.setWidth(_ph_dash_wid);
		painter->setPen(pen);
		painter->drawLine(start, quadPt);
		painter->drawLine(end, quadPt);
		st_arrow = quadPt;
	}

	QPainterPath arrow;
	if (start_copy != _last_start || end != _last_end || quadPt != _last_ctrl) {
		_arrow_start = getArrow(st_arrow, end);
		_arrow_end = getArrow((_ctrl ? st_arrow : end), start_copy);
	}
	if (this->_isSupportPositive) {
		arrow.addPolygon(_arrow_start);
	}

	if (this->_isSupportNegative) {
		arrow.addPolygon(_arrow_end);
	}
	pen.setWidth(0);
	pen.setColor(Qt::white);
	painter->setPen(pen);
	painter->drawPath(arrow);
	painter->fillPath(arrow, Qt::white);

	_last_start = start_copy;
	_last_end = end;
	_last_ctrl = quadPt;

	this->setPos((start_sce.x() + end_sce.x()) / 2, (start_sce.y() + end_sce.y()) / 2);
	//qDebug() << "draw path " << (QDateTime::currentMSecsSinceEpoch() - starttime);
}


SunnyTcsMapObject_tag SunnyTcsGraphicsPath::getItemTag() const
{
	return this->getTag();
}

QPainterPath SunnyTcsGraphicsPath::shape() const
{
	SunnyTcsAgvCoordinate&& st_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_start)->getSceneXy();
	QPointF start(st_sce._x - this->pos().x(), st_sce._y - this->pos().y());
	SunnyTcsAgvCoordinate&& ed_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_end)->getSceneXy();
	QPointF end(ed_sce._x - this->pos().x(), ed_sce._y - this->pos().y());

	QPointF miner(start.x() < end.x() ? start.x() : end.x(), start.y() < end.y() ? start.y() : end.y());//取坐标值小的点
	QPointF maxer(start.x() > end.x() ? start.x() : end.x(), start.y() > end.y() ? start.y() : end.y());//取坐标值大的点

	QPolygonF poly;
	QPainterPath path;
	if (!_ctrl) {//直线
		if (end.x() == start.x()) { //垂直线
			poly << QPointF(start.x() - GRAPHICS_PATH_SHAPE_BIGGER, start.y()) <<
				QPointF(end.x() - GRAPHICS_PATH_SHAPE_BIGGER, end.y()) <<
				QPointF(end.x() + GRAPHICS_PATH_SHAPE_BIGGER, end.y()) <<
				QPointF(start.x() + GRAPHICS_PATH_SHAPE_BIGGER, start.y()) <<
				QPointF(start.x() - GRAPHICS_PATH_SHAPE_BIGGER, start.y());
		}
		else {
			qreal k = (end.y() - start.y()) / (end.x() - start.x());//斜率
			qreal angle = qAbs(qAtan(k));

			qreal move_x = qAbs(qSin(angle)*GRAPHICS_PATH_SHAPE_BIGGER);
			qreal move_y = qAbs(qCos(angle)*GRAPHICS_PATH_SHAPE_BIGGER);
			move_x = k > 0 ? -move_x : move_x;

			poly << QPointF(start.x() + move_x, start.y() + move_y) <<
				QPointF(end.x() + move_x, end.y() + move_y) <<
				QPointF(end.x() - move_x, end.y() - move_y) <<
				QPointF(start.x() - move_x, start.y() - move_y) <<
				QPointF(start.x() + move_x, start.y() + move_y);
		}
		path.addPolygon(poly);
	}
	else { //曲线 三角形shape
		SunnyTcsAgvCoordinate&& ct_sce = dynamic_cast<const SunnyTcsGraphicsPoint*>(_ctrl)->getSceneXy();
		QPointF ctrl(ct_sce._x - this->pos().x(), ct_sce._y - this->pos().y());
		poly << start << end << ctrl << start;
		path.addPolygon(poly);
	}
	return path;
}



QPolygonF SunnyTcsGraphicsPath::getArrow(QPointF from, QPointF to)
{
	if (to.x() == from.x()) {//垂直线
		QPolygonF poly;
		qreal y_move1 = to.x() - from.x() > 0.0 ? _ph_arrow_len : -_ph_arrow_len;
		qreal y_move2 = to.y() - from.y() > 0.0 ? _ph_arrow_move : -_ph_arrow_move;

		poly << QPointF(to.x(), to.y() - y_move2) <<
			QPointF(to.x() + _ph_arrow_len / 2.0, to.y() - y_move2 - y_move1) <<
			QPointF(to.x() - _ph_arrow_len / 2.0, to.y() - y_move2 - y_move1) <<
			QPointF(to.x(), to.y() - y_move2);
		return poly;
	}

	qreal angle = qAtan(qAbs(to.y() - from.y()) / qAbs(to.x() - from.x()));
	qreal x_move = to.x() - from.x() > 0.0 ? _ph_arrow_move : -_ph_arrow_move;
	qreal y_move = to.y() - from.y() > 0.0 ? _ph_arrow_move : -_ph_arrow_move;
	to.setX(from.x() + to.x() - from.x() - (x_move * qCos(angle)));
	to.setY(from.y() + to.y() - from.y() - (y_move * qSin(angle)));

	qint32 fromSx = from.x();
	qint32 fromSy = from.y();
	qint32 toSx = to.x();
	qint32 toSy = to.y();
	qreal tan = (qreal)(toSy - fromSy) / (qreal)(toSx - fromSx);
	angle = qAtan(tan);

	qreal ptx = 0.0;
	qreal pty = 0.0;
	qreal dx = qAbs(_ph_arrow_len*qCos(qAbs(angle)));
	qreal dy = qAbs(_ph_arrow_len*qSin(qAbs(angle)));

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

	qreal deltaX = 0.5* _ph_arrow_len* qSin(qAbs(angle));
	qreal deltaY = 0.5* _ph_arrow_len* qCos(qAbs(angle));

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
