#include "SunnyTcsGraphicsVehicleLib.h"


QImage SunnyTcsGraphicsVehicle_normal::_image;
QImage SunnyTcsGraphicsVehicle_normal::_image_selected;

SunnyTcsGraphicsVehicle_normal::SunnyTcsGraphicsVehicle_normal(const SunnyTcsGraphicsCoorSys * cs, const SunnyTcsMapAdjuster * ad, QPointF pt)
	:SunnyTcsVehicle_normal(ad->nextVeId()),SunnyTcsGraphicsVehicle(cs,ad,pt)
{
	_name = QString("agv%1").arg(QString::number(_id));
	_ladarRadius = 1500;
}


void SunnyTcsGraphicsVehicle_normal::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (_image.isNull()) { //没有指定图片就使用父类默认绘制函数
		((SunnyTcsGraphicsVehicle&)(*this)).paint(painter, option, widget);
	}
	else {
		if (this->isSelected()) {
			painter->drawImage(QRectF(-2000, -1400, 4000, 2800), _image_selected);
		}
		else {
			painter->drawImage(QRectF(-2000, -1400, 4000, 2800), _image);
		}
	}
}


SunnyTcsMapObject_tag SunnyTcsGraphicsVehicle_normal::getItemTag() const
{
	return this->getTag();
}

bool SunnyTcsGraphicsVehicle_normal::updateGraphicsData(const QByteArray & data)
{
	this->updateData(data);
	return true;
}

SunnyTcsAgvCode SunnyTcsGraphicsVehicle_normal::getVehicleCode() const
{
	return _code;
}


QString SunnyTcsGraphicsVehicle_normal::getVehicleIp() const
{
	return _ip;
}

void SunnyTcsGraphicsVehicle_normal::setVehicleIp(QString ip)
{
	_ip = ip;
}

quint16 SunnyTcsGraphicsVehicle_normal::getVehiclePort() const
{
	return _port;
}

void SunnyTcsGraphicsVehicle_normal::setVehiclePort(quint16 port)
{
	_port = port;
}


//---------------------------------------


QImage SunnyTcsGraphicsVehicle_mitsubishi_battery::_image;
QImage SunnyTcsGraphicsVehicle_mitsubishi_battery::_image_selected;

SunnyTcsGraphicsVehicle_mitsubishi_battery::SunnyTcsGraphicsVehicle_mitsubishi_battery(const SunnyTcsGraphicsCoorSys * cs, const SunnyTcsMapAdjuster * ad, QPointF pt)
	:SunnyTcsVehicle_mitsubishi_battery(ad->nextVeId()), SunnyTcsGraphicsVehicle(cs, ad, pt)
{
	_name = QString("agv%1").arg(QString::number(_id));
	_ladarRadius = 1500;
}


void SunnyTcsGraphicsVehicle_mitsubishi_battery::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (_image.isNull()) { //没有指定图片就使用父类默认绘制函数
		((SunnyTcsGraphicsVehicle&)(*this)).paint(painter, option, widget);
	}
	else {
		if (this->isSelected()) {
			painter->drawImage(QRectF(-2000, -1400, 4000, 2800), _image_selected);
		}
		else {
			painter->drawImage(QRectF(-2000, -1400, 4000, 2800), _image);
		}
	}
}


SunnyTcsMapObject_tag SunnyTcsGraphicsVehicle_mitsubishi_battery::getItemTag() const
{
	return this->getTag();
}

bool SunnyTcsGraphicsVehicle_mitsubishi_battery::updateGraphicsData(const QByteArray & data)
{
	this->updateData(data);
	return true;
}

SunnyTcsAgvCode SunnyTcsGraphicsVehicle_mitsubishi_battery::getVehicleCode() const
{
	return _code;
}

QString SunnyTcsGraphicsVehicle_mitsubishi_battery::getVehicleIp() const
{
	return _ip;
}

void SunnyTcsGraphicsVehicle_mitsubishi_battery::setVehicleIp(QString ip)
{
	_ip = ip;
}

quint16 SunnyTcsGraphicsVehicle_mitsubishi_battery::getVehiclePort() const
{
	return _port;
}

void SunnyTcsGraphicsVehicle_mitsubishi_battery::setVehiclePort(quint16 port)
{
	_port = port;
}



//---------------------------------------


QImage SunnyTcsGraphicsVehicle_daimler_engine::_image;
QImage SunnyTcsGraphicsVehicle_daimler_engine::_image_selected;

SunnyTcsGraphicsVehicle_daimler_engine::SunnyTcsGraphicsVehicle_daimler_engine(const SunnyTcsGraphicsCoorSys * cs, const SunnyTcsMapAdjuster * ad, QPointF pt)
	:SunnyTcsVehicle_daimer_engine(ad->nextVeId()), SunnyTcsGraphicsVehicle(cs, ad, pt)
{
	_name = QString("agv%1").arg(QString::number(_id));
	_ladarRadius = 1500;
}


void SunnyTcsGraphicsVehicle_daimler_engine::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (_image.isNull()) { //没有指定图片就使用父类默认绘制函数
		((SunnyTcsGraphicsVehicle&)(*this)).paint(painter, option, widget);
	}
	else {
		if (this->isSelected()) {
			painter->drawImage(QRectF(-2000, -1400, 4000, 2800), _image_selected);
		}
		else {
			painter->drawImage(QRectF(-2000, -1400, 4000, 2800), _image);
		}
	}
}


SunnyTcsMapObject_tag SunnyTcsGraphicsVehicle_daimler_engine::getItemTag() const
{
	return this->getTag();
}

bool SunnyTcsGraphicsVehicle_daimler_engine::updateGraphicsData(const QByteArray & data)
{
	this->updateData(data);
	return true;
}

SunnyTcsAgvCode SunnyTcsGraphicsVehicle_daimler_engine::getVehicleCode() const
{
	return _code;
}

QString SunnyTcsGraphicsVehicle_daimler_engine::getVehicleIp() const
{
	return _ip;
}

void SunnyTcsGraphicsVehicle_daimler_engine::setVehicleIp(QString ip)
{
	_ip = ip;
}

quint16 SunnyTcsGraphicsVehicle_daimler_engine::getVehiclePort() const
{
	return _port;
}

void SunnyTcsGraphicsVehicle_daimler_engine::setVehiclePort(quint16 port)
{
	_port = port;
}
