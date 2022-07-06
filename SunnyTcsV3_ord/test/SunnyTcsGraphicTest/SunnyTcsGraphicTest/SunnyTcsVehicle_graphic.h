#pragma once
#include "stafix.h"
#include "SunnyTcsCoorSys_graphic.h"


class SunnyTcsVehicle_graphic 
	:public  SunnyTcsMapItem_graphic{
public:
	SunnyTcsVehicle_graphic(const SunnyTcsMapAdjuster* ad, QString name = QString(), qint32 ladarRadius = 3000, qint32 veLen = 2000)
		:SunnyTcsMapItem_graphic(), _ad(ad), _name(name), _ladarRadius(ladarRadius), _veLen(veLen)
	{
		
	}
	virtual ~SunnyTcsVehicle_graphic() {}

	//¼Ì³Ð SunnyTcsMapItem_graphic
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;

	

protected:
	const SunnyTcsMapAdjuster* _ad;
	QString _name;
	qreal _ladarRadius; //À×´ï°ë¾¶,Ä¬ÈÏ3Ã×
	qreal _veLen;
};



