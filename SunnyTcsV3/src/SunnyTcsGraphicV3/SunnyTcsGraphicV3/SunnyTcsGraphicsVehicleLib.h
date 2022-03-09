#pragma once


#include "SunnyTcsGraphicsVehicle.h"


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

};