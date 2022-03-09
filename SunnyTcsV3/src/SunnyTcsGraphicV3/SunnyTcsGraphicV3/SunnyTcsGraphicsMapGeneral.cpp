#include "SunnyTcsGraphicsMapGeneral.h"

QVariant SunnyTcsMapGraphicItem::itemChange(GraphicsItemChange change, const QVariant & value)
{

	if (change == ItemPositionChange  &&  scene()) // 控件发生移动
	{
		QPointF newPos = value.toPointF(); //即将要移动的位置
		qreal wid = scene()->width();
		qreal hei = scene()->height();
		QRectF rect(-wid/2, -hei/2, wid, hei); // 你要限制的区域
		if (!rect.contains(newPos)) // 是否在区域内
		{
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsItem::itemChange(change, value);

}
