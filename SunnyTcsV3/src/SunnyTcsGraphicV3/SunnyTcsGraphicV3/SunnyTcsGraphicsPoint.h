#pragma once
#include "SunnyTcsGraphicsCoorSys.h"



class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsPoint : public SunnyTcsPoint ,public SunnyTcsMapGraphicItem
{
public:
	//PT
	static constexpr qint32 _pt_ex_wid = 1200;							//圆的线宽
	static constexpr qint32 _pt_rect_wid = 800;							//圆的直径
	static constexpr qint32 _pt_back_wid = 2000;							//底圆的直径
	static constexpr qint32 _pt_park_wid = 3000;							//停留圆直径
	static constexpr qint32 _pt_text_rect_len = 16000;						//点的字体方框长
	static constexpr qint32 _pt_text_rect_wid = 1000;						//点的字体方框宽
	static constexpr qint32 _pt_font_size = 400;							//字体大小

	static const QColor _pt_back_color;		//底色
	static const QColor _pt_ex_color;		//圆框颜色
	static const QColor _pt_rect_color ;	//内圆颜色
	static const QColor _pt_select_color ;	//选中颜色
	static const QColor _pt_park_color ;	//必经点颜色

	static const QColor _pt_rubbon_color ;	
	static const QColor _pt_ine_color;
	static const QColor _pt_laser_color ;
	static const QColor _pt_help_color;


	//ctor
	SunnyTcsGraphicsPoint( const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad, QPointF pt = QPointF(0, 0));

	SunnyTcsGraphicsPoint(const SunnyTcsGraphicsPoint&) = delete;

	virtual ~SunnyTcsGraphicsPoint() {
		qDebug() << "delete point";
		_ad->returnPtId(_id);
	}

	SunnyTcsGraphicsPoint& operator=(const SunnyTcsGraphicsPoint&) = delete;

	//得到场景坐标
	SunnyTcsAgvCoordinate getSceneXy()const;

	//从当前的Sx Sy计算出RX RY 只有图形库中需要用到这个函数，因为坐标系会移动，这时候需要实时更新rx ry
	void updateData();

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	
protected:
	const SunnyTcsMapAdjuster* _ad;
	
	
};

