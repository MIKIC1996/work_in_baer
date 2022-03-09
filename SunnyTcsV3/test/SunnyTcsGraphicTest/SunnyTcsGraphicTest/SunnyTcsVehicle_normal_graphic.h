#pragma once

#include "SunnyTcsVehicle_graphic.h"



class SunnyTcsVehicle_normal_graphic :public SunnyTcsMapVehicle_normal, public SunnyTcsVehicle_graphic
{
public:

	SunnyTcsVehicle_normal_graphic(const SunnyTcsMapCoorSys_graphic* cs, qint32 id, const SunnyTcsMapAdjuster* ad, QPointF pt,QString name  = QString(),
		QString ip = "127.0.0.1", quint16 port = 5003, qint32 groupId = 0);

	virtual ~SunnyTcsVehicle_normal_graphic() {}


	// Í¨¹ý SunnyTcsVehicle_graphic ¼Ì³Ð
	virtual SunnyTcsAgvCoordinate getCurrentCoor()const override{
		
		return _coor;
	}

	virtual SunnyTcsMapObject_tag getItemTag() const override;

	virtual QRectF boundingRect() const override;

	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;

	virtual QJsonObject toJson()const override{
		QJsonObject jobj;
		jobj[JSON_MAP_VE_CODE] = _code._agvType;
		jobj[JSON_MAP_VE_ID] = _id;
		jobj[JSON_MAP_VE_GROUP_ID] = _groupId;
		jobj[JSON_MAP_VE_NAME] = _name;
		jobj[JSON_MAP_VE_IP] = _ip;
		jobj[JSON_MAP_VE_PORT] = _port;
		return jobj;
	}

	bool fromJson(QJsonObject& jobj, QString& err = QString()) override {
		return false;
	}


};

