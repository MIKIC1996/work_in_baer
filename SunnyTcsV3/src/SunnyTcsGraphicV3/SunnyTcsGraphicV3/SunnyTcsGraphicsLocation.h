#pragma once

#include "SunnyTcsGraphicsPath.h"


class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsLocation :public SunnyTcsLocation ,public SunnyTcsMapGraphicItem
{
public:
	static void setImage(const char* path) {
		_image = QImage(path);
	}

	static void setImageSelected(const char* path) {
		_image_selected = QImage(path);
	}

	static const QColor _loc_dash_color;
	static constexpr qint32 _loc_dash_wid = 100;

	static constexpr qint32 _loc_ex_wid = 3000;
	static constexpr qint32 _loc_line_wid = 100;
	static const QColor _loc_ex_color;

protected:
	static QImage _image;
	static QImage _image_selected;


public:
	//ctor
	SunnyTcsGraphicsLocation(const SunnyTcsMapAdjuster* ad ,const SunnyTcsGraphicsPoint* pt);
	//copy ctor
	SunnyTcsGraphicsLocation(const SunnyTcsGraphicsLocation&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsLocation() {
		_ad->returnLocId(_id);
	}
	//assignment
	SunnyTcsGraphicsLocation& operator=(const SunnyTcsGraphicsLocation&) = delete;

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;

	// 通过 SunnyTcsLocation 继承
	virtual bool fromJson(QJsonObject& jobj) override
	{
		return false; 
	}
	
	virtual QJsonObject toJson()const override 
	{ 
		return QJsonObject(); 
	}

protected:
	const SunnyTcsMapAdjuster* _ad;

	

};

