#include "SunnyTcsGraphicsSonCraft.h"




QRectF SunnyTcsGraphicsSonCraft::boundingRect() const
{
	return QRectF(-150,-100,300 ,200);


}

void SunnyTcsGraphicsSonCraft::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
	if (!_indexer)return;
	const SunnyTcsCraftPaintingAttribution& attr = _indexer->_paintAttribution;

	qint32 wid = attr._sonCraftWid;
	qint32 hei = attr._sonCraftHei;
	qint32 tabHei = attr._sonCraftTabHeight;
	qint32 rectRadius = attr._sonCraftRectRadius;


	//绘制外边框
	QPen pen;
	pen.setWidth(2);
	pen.setColor(this->isSelected() ? Qt::yellow : QColor(255,255,255,100));

	painter->setPen(pen);
	painter->drawRoundedRect(QRectF(-wid / 2, -hei / 2, wid, hei), rectRadius, rectRadius);
	
	pen.setColor(QColor(0,0,0,0));
	painter->setPen(pen);






	//绘制主框
	QLinearGradient linear(
		QPointF(- attr._sonCraftWid / 2,- attr._sonCraftHei  / 2),
		QPointF( attr._sonCraftWid / 2, - attr._sonCraftHei / 2)
	);
	linear.setSpread(QGradient::PadSpread);

	linear.setColorAt(0, attr._sonCraftMainRectLeftColor);
	linear.setColorAt(1, attr._sonCraftMainRectRightColor);
	painter->setBrush(linear);
	painter->drawRoundedRect(QRectF(-wid / 2, -hei / 2 , wid, hei), rectRadius, rectRadius);
	



	//绘制顶框
	QLinearGradient linear_top(
		QPointF(-wid / 2, -hei / 2),
		QPointF(wid / 2, -hei / 2)
	);
	linear_top.setSpread(QGradient::PadSpread);
	linear_top.setColorAt(0, attr._sonCraftTabLeftColor);
	QColor topColor = attr._sonCraftTabLeftColor;
	topColor.setAlpha(((qreal)(QDateTime::currentMSecsSinceEpoch() % 3000) / 3000.0) * 150.0);
	linear_top.setColorAt(0.5, topColor);
	linear_top.setColorAt(1, attr._sonCraftTabRightColor);
	painter->setBrush(linear_top);
	painter->drawRoundedRect(QRectF(-wid / 2, -hei / 2, wid, tabHei), rectRadius, rectRadius);
	

	


	//绘制五边箭头
	QPolygonF poly;
	poly << QPointF(wid * 0.4, -hei * 0.05) <<
		QPointF(wid * 0.42, -hei * 0.05) <<
		QPointF(wid*0.46, hei*0.01) <<
		QPointF(wid * 0.42, hei * 0.07) <<
		QPointF(wid * 0.4, hei * 0.07) <<
		QPointF(wid * 0.4, -hei * 0.05);
	QPainterPath path;
	path.addPolygon(poly);
	painter->fillPath(path, Qt::green);


	//绘制顶框上边光装饰效果
	QLinearGradient linear2(
		QPointF(-wid / 2, -hei / 2),
		QPointF(-wid / 2, -hei / 2 + tabHei)
	);
	linear2.setSpread(QGradient::PadSpread);
	linear2.setColorAt(0, attr._sonCraftTabBackColor);
	linear2.setColorAt(0.15, attr._sonCraftTabBackColor_to);
	painter->setBrush(linear2);
	painter->drawRoundedRect(QRectF(-wid / 2, -hei / 2, wid, tabHei), rectRadius, rectRadius);

	//绘制顶框下边阴影效果
// 	QLinearGradient linear3(
// 		QPointF(-wid / 2, -hei / 2 + tabHei / 2),
// 		QPointF(-wid / 2, -hei / 2 + tabHei)
// 	);
// 	linear3.setColorAt(0, QColor(40, 40, 40, 100));
// 	linear3.setColorAt(1, QColor(40, 40, 40, 30));
// 	painter->setBrush(linear3);
// 	painter->drawRoundedRect(QRectF(-wid / 2, -hei / 2 + tabHei / 2, wid, tabHei / 2), 0, 0);




}
