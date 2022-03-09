#pragma once

#include "SunnyTcsGraphicsLocation.h"


//�����û�м̳�SunnyTcsVehicle,��ֻ���ṩ��Ĭ�ϵĳ������Ʒ�����ÿ�ֳ��Ϳ������Լ��Ļ��Ʒ���
class SunnyTcsGraphicsVehicle :public SunnyTcsMapGraphicItem
{
public:
	//ֻ��һ��ͨ�ö���
	static const QColor _ve_ladar_color;//�״�Ȧ����ɫ
	static const QColor _ve_ladar_warn_color; //�״���ײ��ɫ
	static const QColor _ve_ladar_from_color;
	static const QColor _ve_ladar_deco_color;
	static const QColor _ve_back_color; //���ĵ�ɫ

	static const QColor _ve_outLine_color; //������ɫ
	static const QColor _ve_unconnected_color;//������ɫ
	static const QColor _ve_connected_color;//��������ɫ
	static const QColor _ve_working_color;//��������ɫ

	//ctor
	SunnyTcsGraphicsVehicle(const SunnyTcsGraphicsCoorSys* cs,const SunnyTcsMapAdjuster* ad,QPointF pt = QPointF(0, 0));
	//copy ctor
	SunnyTcsGraphicsVehicle(const SunnyTcsGraphicsVehicle&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsVehicle() {}
	//assignment
	SunnyTcsGraphicsVehicle& operator=(const SunnyTcsGraphicsVehicle&) = delete;

	// ͨ�� SunnyTcsMapGraphicItem �̳�
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override =0;

protected:
	const SunnyTcsGraphicsCoorSys* _cs;
	const SunnyTcsMapAdjuster* _ad;
	qreal _ladarRadius; //ģ���״�����С
	
};

