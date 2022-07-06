#include "SunnyTcsGraphicsMapGeneral.h"

QVariant SunnyTcsMapGraphicItem::itemChange(GraphicsItemChange change, const QVariant & value)
{

	if (change == ItemPositionChange  &&  scene()) // �ؼ������ƶ�
	{
		QPointF newPos = value.toPointF(); //����Ҫ�ƶ���λ��
		qreal wid = scene()->width();
		qreal hei = scene()->height();
		QRectF rect(-wid/2, -hei/2, wid, hei); // ��Ҫ���Ƶ�����
		if (!rect.contains(newPos)) // �Ƿ���������
		{
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsItem::itemChange(change, value);

}
