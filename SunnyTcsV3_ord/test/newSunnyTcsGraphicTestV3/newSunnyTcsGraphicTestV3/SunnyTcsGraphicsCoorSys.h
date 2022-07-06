#pragma once


#include "SunnyTcsGraphicsMapGeneral.h"


class SunnyTcsGraphicsCoorSys :public SunnyTcsCoorSys, public SunnyTcsMapGraphicItem
{
public:
	//CS ��������Ƴߴ�
	static constexpr qint32 _cs_axis_len = 1000;	//�����᳤				
	static constexpr qint32 _cs_axis_wid = 100;		//�������߿�				
	static constexpr qint32 _cs_arrow_len = 250;	//�������ͷ�߳�		
	static constexpr qint32 _cs_ex_rect_wid = 800;	//�ⷽ��			
	static constexpr qint32 _cs_in_rect_wid = 800;	//�ڷ���	
	static const QColor _cs_default_color ; //Ĭ����ɫ

	//ctor
	SunnyTcsGraphicsCoorSys(QPointF pt, const SunnyTcsMapAdjuster* ad, qint32 id = 1);
	//copy ctor
	SunnyTcsGraphicsCoorSys(const SunnyTcsGraphicsCoorSys&) = delete;
	//dtor
	virtual ~SunnyTcsGraphicsCoorSys() {}
	//assignment
	SunnyTcsGraphicsCoorSys& operator=(SunnyTcsGraphicsCoorSys&) = delete;


	// ͨ�� SunnyTcsMapGraphicItem �̳�
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;


	//ͨ�� SunnyTcsCoorSys �̳�
	virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const override;
	virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene) const override;
	

private:
	QPolygonF getArrow(int direction);

protected:
	const SunnyTcsMapAdjuster* _ad; //ͼ��ģ�͵Ľӿ�
};

