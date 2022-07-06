#pragma once


#include "SunnyTcsGraphicsMapGeneral.h"


class SunnyTcsGraphicsCoorSys :public SunnyTcsCoorSys, public SunnyTcsMapGraphicItem
{
public:
	//CS 坐标轴绘制尺寸
	static constexpr qint32 _cs_axis_len = 1000;	//坐标轴长				
	static constexpr qint32 _cs_axis_wid = 100;		//坐标轴线宽				
	static constexpr qint32 _cs_arrow_len = 250;	//坐标轴箭头边长		
	static constexpr qint32 _cs_ex_rect_wid = 800;	//外方框长			
	static constexpr qint32 _cs_in_rect_wid = 800;	//内方框长	
	static const QColor _cs_default_color ; //默认颜色

	//ctor
	SunnyTcsGraphicsCoorSys(QPointF pt, const SunnyTcsMapAdjuster* ad, qint32 id = 1);
	//copy ctor
	SunnyTcsGraphicsCoorSys(const SunnyTcsGraphicsCoorSys&) = delete;
	//dtor
	virtual ~SunnyTcsGraphicsCoorSys() {}
	//assignment
	SunnyTcsGraphicsCoorSys& operator=(SunnyTcsGraphicsCoorSys&) = delete;


	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;


	//通过 SunnyTcsCoorSys 继承
	virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const override;
	virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene) const override;
	

private:
	QPolygonF getArrow(int direction);

protected:
	const SunnyTcsMapAdjuster* _ad; //图形模型的接口
};

