#pragma once

#include "SunnyTcsGraphicsPath.h"


class SunnyTcsGraphicsLocation :public SunnyTcsLocation ,public SunnyTcsMapGraphicItem
{
public:
	static constexpr qint32 _loc_ex_wid = 2000;
	static constexpr qint32 _loc_line_wid = 100;

	SunnyTcsGraphicsLocation(const SunnyTcsMapAdjuster* ad ,const SunnyTcsGraphicsPoint* pt);

	SunnyTcsGraphicsLocation(const SunnyTcsGraphicsLocation&) = delete;

	virtual ~SunnyTcsGraphicsLocation() {}

	SunnyTcsGraphicsLocation& operator=(const SunnyTcsGraphicsLocation&) = delete;

	// Í¨¹ý SunnyTcsMapGraphicItem ¼Ì³Ð
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;

protected:
	QString _name;
	const SunnyTcsMapAdjuster* _ad;

	

};

