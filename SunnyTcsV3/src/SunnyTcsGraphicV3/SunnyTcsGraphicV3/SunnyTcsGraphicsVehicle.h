#pragma once

#include "SunnyTcsGraphicsLocation.h"


//这个类没有继承SunnyTcsVehicle,他只是提供了默认的车辆绘制方法，每种车型可以有自己的绘制方法
class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsVehicle : public SunnyTcsMapGraphicItem
{
public:
	//只有一切通用定义
	static const QColor _ve_ladar_color;//雷达圈的颜色
	static const QColor _ve_ladar_warn_color; //雷达碰撞颜色
	static const QColor _ve_ladar_from_color;
	static const QColor _ve_ladar_deco_color;
	static const QColor _ve_back_color; //车的底色

	static const QColor _ve_outLine_color; //下线颜色
	static const QColor _ve_unconnected_color;//断连颜色
	static const QColor _ve_connected_color;//已连接颜色
	static const QColor _ve_working_color;//工作中颜色

	//ctor
	SunnyTcsGraphicsVehicle(const SunnyTcsGraphicsCoorSys* cs,const SunnyTcsMapAdjuster* ad,QPointF pt = QPointF(0, 0));
	//copy ctor
	SunnyTcsGraphicsVehicle(const SunnyTcsGraphicsVehicle&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsVehicle() {
	}
	//assignment
	SunnyTcsGraphicsVehicle& operator=(const SunnyTcsGraphicsVehicle&) = delete;

	//getter
	qreal getLadarRadius()const { return _ladarRadius; }
	//setter
	void setLadarRadius(qreal val) { _ladarRadius = val; }

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual QPainterPath shape()const override;

	//自己的纯虚函数
	virtual bool updateGraphicsData(const QByteArray & data) = 0; 
	
	virtual SunnyTcsMapObject_tag getItemTag() const override =0;
	virtual SunnyTcsAgvCode getVehicleCode()const = 0;

	virtual QString getVehicleIp()const = 0;
	virtual void setVehicleIp(QString ip) = 0;

	virtual quint16 getVehiclePort()const = 0;
	virtual void setVehiclePort(quint16 port) = 0;

	virtual bool fromVehicleJson(QJsonObject& jobj) { return false; }
	virtual QJsonObject toVehicleJson()const { return QJsonObject(); }

protected:
	const SunnyTcsGraphicsCoorSys* _cs;
	const SunnyTcsMapAdjuster* _ad;
	qreal _ladarRadius; //模拟雷达区大小
	



};

