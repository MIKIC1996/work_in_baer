#pragma once


#include "SunnyTcsGraphicsVehicle.h"





//图形库车辆工厂接口，因为内核 与 图形模型 的业务很不一样，所以工厂也不太一样
class I_SunnyTcsGraphicsVehicleFactory {
public:
	virtual SunnyTcsGraphicsVehicle* createVehicleByJson(QJsonObject& jobj, const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad) {
		if (!jobj.contains(JSON_MAP_VE_CODE) ||
			!jobj.contains(JSON_MAP_VE_ID) ||
			!jobj.contains(JSON_MAP_VE_NAME) ||
			!jobj.contains(JSON_MAP_VE_IP) ||
			!jobj.contains(JSON_MAP_VE_PORT) ||
			!jobj.contains(JSON_MAP_VE_RADAR_RADIUS)||
			!jobj.contains(JSON_MAP_VE_SCENE_X)||
			!jobj.contains(JSON_MAP_VE_SCENE_Y)
			) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_TAG>::err_info_cn);
			return nullptr;
		}
		qint32 agvCodeType = jobj[JSON_MAP_VE_CODE].toInt();
		SunnyTcsGraphicsVehicle* vePtr = createVehicleByCode(agvCodeType, cs, ad);
		if (!vePtr) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_CODE>::err_info_cn);
			return nullptr;
		}
		if (!vePtr->fromVehicleJson(jobj)) {
			delete vePtr;
			return nullptr;
		}
		return vePtr;
	}

	virtual SunnyTcsGraphicsVehicle* createVehicleByCode(qint32 code, const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad)const = 0;
};





class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsVehicle_normal :public SunnyTcsVehicle_normal, public SunnyTcsGraphicsVehicle {
public:
	static void setImage(const char* path) {
		_image = QImage(path);
	}

	static void setImageSelected(const char* path) {
		_image_selected = QImage(path);
	}

protected:
	static QImage _image;
	static QImage _image_selected;

public:
	//ctor
	SunnyTcsGraphicsVehicle_normal(const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad, QPointF pt = QPointF(0, 0));
	//copy ctor
	SunnyTcsGraphicsVehicle_normal(const SunnyTcsGraphicsVehicle_normal&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsVehicle_normal() {
		_ad->returnVeId(_id);
	}
	//assignment
	SunnyTcsGraphicsVehicle_normal& operator=(const SunnyTcsGraphicsVehicle_normal&) = delete;

	// 通过 SunnyTcsGraphicsVehicle 继承
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	virtual bool updateGraphicsData(const QByteArray & data) override;
	virtual SunnyTcsAgvCode getVehicleCode() const override;


	// 通过 SunnyTcsGraphicsVehicle 继承
	virtual QString getVehicleIp() const override;

	virtual void setVehicleIp(QString ip) override;

	virtual quint16 getVehiclePort() const override;

	virtual void setVehiclePort(quint16 port) override;

	virtual bool fromVehicleJson(QJsonObject& jobj)override {
		qint32 id = jobj[JSON_MAP_VE_ID].toInt();
		if (id != _id) {
			if (_ad->applyForVeId(id)) {
				_ad->returnVeId(_id);
			}
			else {
				throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR>::err_info_cn);
				return false;
			}
		}
		_id = id;
		_name = jobj[JSON_MAP_VE_NAME].toString();
		_ip = jobj[JSON_MAP_VE_IP].toString();
		_port = jobj[JSON_MAP_VE_PORT].toInt();
		_ladarRadius = jobj[JSON_MAP_VE_RADAR_RADIUS].toInt();
		this->setPos(jobj[JSON_MAP_VE_SCENE_X].toInt(), jobj[JSON_MAP_VE_SCENE_Y].toInt());
		return true;
	}

	virtual QJsonObject toVehicleJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_VE_CODE] = _code._agvType;
		jobj[JSON_MAP_VE_ID] = _id;
		jobj[JSON_MAP_VE_NAME] = _name;
		jobj[JSON_MAP_VE_IP] = _ip;
		jobj[JSON_MAP_VE_PORT] = _port;
		jobj[JSON_MAP_VE_RADAR_RADIUS] = _ladarRadius;
		jobj[JSON_MAP_VE_SCENE_X] = (qint32)(this->pos().x());
		jobj[JSON_MAP_VE_SCENE_Y] = (qint32)(this->pos().y());
		return jobj;
	}

};




class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsVehicle_mitsubishi_battery :public SunnyTcsVehicle_mitsubishi_battery, public SunnyTcsGraphicsVehicle {
public:
	static void setImage(const char* path) {
		_image = QImage(path);
	}

	static void setImageSelected(const char* path) {
		_image_selected = QImage(path);
	}

protected:
	static QImage _image;
	static QImage _image_selected;

public:
	//ctor
	SunnyTcsGraphicsVehicle_mitsubishi_battery(const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad, QPointF pt = QPointF(0, 0));
	//copy ctor
	SunnyTcsGraphicsVehicle_mitsubishi_battery(const SunnyTcsGraphicsVehicle_mitsubishi_battery&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsVehicle_mitsubishi_battery() {
		_ad->returnVeId(_id);
	}
	//assignment
	SunnyTcsGraphicsVehicle_mitsubishi_battery& operator=(const SunnyTcsGraphicsVehicle_mitsubishi_battery&) = delete;

	// 通过 SunnyTcsGraphicsVehicle 继承
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	virtual bool updateGraphicsData(const QByteArray & data) override;
	virtual SunnyTcsAgvCode getVehicleCode() const override;


	// 通过 SunnyTcsGraphicsVehicle 继承
	virtual QString getVehicleIp() const override;

	virtual void setVehicleIp(QString ip) override;

	virtual quint16 getVehiclePort() const override;

	virtual void setVehiclePort(quint16 port) override;


	virtual bool fromVehicleJson(QJsonObject& jobj)override {
		qint32 id = jobj[JSON_MAP_VE_ID].toInt();
		if (id != _id) {
			if (_ad->applyForVeId(id)) {
				_ad->returnVeId(_id);
			}
			else {
				throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR>::err_info_cn);
				return false;
			}
		}
		_id = id;
		_name = jobj[JSON_MAP_VE_NAME].toString();
		_ip = jobj[JSON_MAP_VE_IP].toString();
		_port = jobj[JSON_MAP_VE_PORT].toInt();
		_ladarRadius = jobj[JSON_MAP_VE_RADAR_RADIUS].toInt();
		this->setPos(jobj[JSON_MAP_VE_SCENE_X].toInt(), jobj[JSON_MAP_VE_SCENE_Y].toInt());
		return true;
	}

	virtual QJsonObject toVehicleJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_VE_CODE] = _code._agvType;
		jobj[JSON_MAP_VE_ID] = _id;
		jobj[JSON_MAP_VE_NAME] = _name;
		jobj[JSON_MAP_VE_IP] = _ip;
		jobj[JSON_MAP_VE_PORT] = _port;
		jobj[JSON_MAP_VE_RADAR_RADIUS] = _ladarRadius;
		jobj[JSON_MAP_VE_SCENE_X] = (qint32)(this->pos().x());
		jobj[JSON_MAP_VE_SCENE_Y] = (qint32)(this->pos().y());
		return jobj;
	}
};





class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsVehicle_daimler_engine :public SunnyTcsVehicle_daimer_engine, public SunnyTcsGraphicsVehicle {
public:
	static void setImage(const char* path) {
		_image = QImage(path);
	}

	static void setImageSelected(const char* path) {
		_image_selected = QImage(path);
	}

protected:
	static QImage _image;
	static QImage _image_selected;

public:
	//ctor
	SunnyTcsGraphicsVehicle_daimler_engine(const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad, QPointF pt = QPointF(0, 0));
	//copy ctor
	SunnyTcsGraphicsVehicle_daimler_engine(const SunnyTcsGraphicsVehicle_daimler_engine&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsVehicle_daimler_engine() {
		_ad->returnVeId(_id);
	}
	//assignment
	SunnyTcsGraphicsVehicle_daimler_engine& operator=(const SunnyTcsGraphicsVehicle_daimler_engine&) = delete;

	// 通过 SunnyTcsGraphicsVehicle 继承
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	virtual bool updateGraphicsData(const QByteArray & data) override;
	virtual SunnyTcsAgvCode getVehicleCode() const override;


	// 通过 SunnyTcsGraphicsVehicle 继承
	virtual QString getVehicleIp() const override;

	virtual void setVehicleIp(QString ip) override;

	virtual quint16 getVehiclePort() const override;

	virtual void setVehiclePort(quint16 port) override;


	virtual bool fromVehicleJson(QJsonObject& jobj)override {
		qint32 id = jobj[JSON_MAP_VE_ID].toInt();
		if (id != _id) {
			if (_ad->applyForVeId(id)) {
				_ad->returnVeId(_id);
			}
			else {
				throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR>::err_info_cn);
				return false;
			}
		}
		_id = id;
		_name = jobj[JSON_MAP_VE_NAME].toString();
		_ip = jobj[JSON_MAP_VE_IP].toString();
		_port = jobj[JSON_MAP_VE_PORT].toInt();
		_ladarRadius = jobj[JSON_MAP_VE_RADAR_RADIUS].toInt();
		this->setPos(jobj[JSON_MAP_VE_SCENE_X].toInt(), jobj[JSON_MAP_VE_SCENE_Y].toInt());
		return true;
	}

	virtual QJsonObject toVehicleJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_VE_CODE] = _code._agvType;
		jobj[JSON_MAP_VE_ID] = _id;
		jobj[JSON_MAP_VE_NAME] = _name;
		jobj[JSON_MAP_VE_IP] = _ip;
		jobj[JSON_MAP_VE_PORT] = _port;
		jobj[JSON_MAP_VE_RADAR_RADIUS] = _ladarRadius;
		jobj[JSON_MAP_VE_SCENE_X] = (qint32)(this->pos().x());
		jobj[JSON_MAP_VE_SCENE_Y] = (qint32)(this->pos().y());
		return jobj;
	}


};




class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsVehicleFactory :public I_SunnyTcsGraphicsVehicleFactory {
	// 通过 I_SunnyTcsVehicleFactory 继承
	virtual SunnyTcsGraphicsVehicle* createVehicleByCode(qint32 code,const SunnyTcsGraphicsCoorSys* cs,const SunnyTcsMapAdjuster* ad)const override;
};