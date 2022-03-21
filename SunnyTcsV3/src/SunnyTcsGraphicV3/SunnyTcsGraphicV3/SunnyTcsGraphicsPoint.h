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
	void setPointRealityXy(SunnyTcsAgvCoordinate coor);//图形库用来设置rxy的函数，如果使用超类的Set方法，会因为图形库更新时updatePoint的调用而被改回来

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;

	// 通过 SunnyTcsPoint 继承
	virtual bool fromJson(QJsonObject& jobj)override {
		if (!jobj.contains(JSON_MAP_PT_ID) ||
			!jobj.contains(JSON_MAP_PT_NAME) ||
			!jobj.contains(JSON_MAP_PT_ABS_POS) ||
			!jobj.contains(JSON_MAP_PT_REALITY_X) ||
			!jobj.contains(JSON_MAP_PT_REALITY_Y) ||
			!jobj.contains(JSON_MAP_PT_SPT_NAGAMODE)
			) {
			return false;
		}
		qint32 id = jobj[JSON_MAP_PT_ID].toInt();
		QString name = jobj[JSON_MAP_PT_NAME].toString();
		qint32 absPos = jobj[JSON_MAP_PT_ABS_POS].toInt();
		qint32 rx = jobj[JSON_MAP_PT_REALITY_X].toInt();
		qint32 ry = jobj[JSON_MAP_PT_REALITY_Y].toInt();
		qint32 nagamode = jobj[JSON_MAP_PT_SPT_NAGAMODE].toInt();

		_id = id;
		_name = name;
		_absPos = absPos;
		_rxy._x = rx;
		_rxy._y = ry;
		_nagaMode = nagamode;
		return false; 
	}


	virtual QJsonObject toJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_PT_ID] = _id;
		jobj[JSON_MAP_PT_NAME] = _name;
		jobj[JSON_MAP_PT_ABS_POS] = _absPos;
		jobj[JSON_MAP_PT_REALITY_X] = _rxy._x;
		jobj[JSON_MAP_PT_REALITY_Y] = _rxy._y;
		jobj[JSON_MAP_PT_SPT_NAGAMODE] = _nagaMode;
		return jobj;
	}

protected:
	const SunnyTcsMapAdjuster* _ad;
	
	
};

