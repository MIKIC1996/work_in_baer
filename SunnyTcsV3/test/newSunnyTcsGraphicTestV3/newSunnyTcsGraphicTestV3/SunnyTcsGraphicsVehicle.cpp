#include "SunnyTcsGraphicsVehicle.h"


 const QColor SunnyTcsGraphicsVehicle::_ve_ladar_color = QColor(42, 87, 191, 150);//�״�Ȧ����ɫ
 const QColor SunnyTcsGraphicsVehicle::_ve_ladar_warn_color = QColor(218, 134, 129, 200); //�״���ײ��ɫ
 const QColor SunnyTcsGraphicsVehicle::_ve_ladar_from_color = QColor(0, 0, 0, 0);
 const QColor SunnyTcsGraphicsVehicle::_ve_ladar_deco_color = QColor(200, 200, 255, 50);
 const QColor SunnyTcsGraphicsVehicle::_ve_back_color = Qt::white; //���ĵ�ɫ

 const QColor _ve_outLine_color = Qt::gray; //������ɫ
 const QColor _ve_unconnected_color = Qt::darkGray;//������ɫ
 const QColor _ve_connected_color = Qt::darkBlue;//��������ɫ
 const QColor _ve_working_color =Qt::blue;//��������ɫ

 

SunnyTcsGraphicsVehicle::SunnyTcsGraphicsVehicle(const SunnyTcsGraphicsCoorSys * cs, const SunnyTcsMapAdjuster * ad,QPointF pt)
	:SunnyTcsMapGraphicItem(),_cs(cs),_ad(ad), _ladarRadius(0)
{
	this->setPos(pt);
	this->setZValue(5);
}

QRectF SunnyTcsGraphicsVehicle::boundingRect() const
{
	qreal len = _ladarRadius - (qSqrt(2)* _ladarRadius - _ladarRadius) / 3;
	return QRectF(-len, -len, len*2.0, len*2.0);
}

void SunnyTcsGraphicsVehicle::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ĭ�Ϸ���
}

