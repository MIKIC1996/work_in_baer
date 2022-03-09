#pragma once

#include "SunnyTcsGraphicsPoint.h"

#define GRAPHICS_PATH_SHAPE_BIGGER 1200


class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsPath :public SunnyTcsPath ,public SunnyTcsMapGraphicItem
{
public:
	//PATH
	static constexpr qint32 _ph_ex_wid = 1200;
	static constexpr qint32 _ph_selected_wid = 650;						
	static constexpr qint32 _ph_arrow_len = 400;						//路劲箭头宽
	static constexpr qint32 _ph_dash_wid = 100;							//虚线线宽
	static constexpr qint32 _ph_arrow_move = 1500;						//箭头偏移
	static const QColor _ph_back_color;
	static const QColor _ph_selected_color;
	static const QColor _ph_dash_color ;

	//ctor
	SunnyTcsGraphicsPath(
		const SunnyTcsMapAdjuster* ad,
		const SunnyTcsGraphicsPoint* start,
		const SunnyTcsGraphicsPoint* end,
		const SunnyTcsGraphicsPoint* ctrl = nullptr
	);
	//copy ctor
	SunnyTcsGraphicsPath(const SunnyTcsGraphicsPath&) = delete;
	//dector
	virtual ~SunnyTcsGraphicsPath() {
		_ad->returnPhId(_id);
	}
	//assignment
	SunnyTcsGraphicsPath operator=(SunnyTcsGraphicsPath&) = delete;

	//getter
	inline bool isStartNew()const { return _isStartNew; }
	inline bool isCtrlNew()const { return _isCtrlNew; }
	inline bool isEndNew()const { return _isEndNew; }

	//setter
	void setIsStartNew(bool is) { _isStartNew = is; }
	void setIsCtrlNew(bool is) { _isCtrlNew = is; }
	void setIsEndNew(bool is) { _isEndNew = is; }

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	virtual QPainterPath shape()const override;

private:
	QPolygonF getArrow(QPointF from, QPointF to);

protected:
	//记录三点是否是新点
	bool _isStartNew;
	bool _isCtrlNew;
	bool _isEndNew;

	//上次记录的三点
	QPointF _last_start;
	QPointF _last_end;
	QPointF _last_ctrl;
	//上次记录的箭头，重画的时候如果三点与之前相同，就不需要重新计算了
	QPolygonF _arrow_start;
	QPolygonF _arrow_end;

	const SunnyTcsMapAdjuster* _ad;
};

