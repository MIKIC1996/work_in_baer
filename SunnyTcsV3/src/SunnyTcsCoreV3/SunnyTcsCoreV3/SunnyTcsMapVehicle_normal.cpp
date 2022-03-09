#include "SunnyTcsMapVehicle_normal.h"

/*
bool core::SunnyTcsAgvData_normal::update(const QByteArray & data, QString & err)
{
	 	const qint32 bytesOfFeedback = 82;
	 	if (data.count() != bytesOfFeedback) return false;
	 
	 	const qint16 bytesOfCommandID = 2;
	 	const qint16 bytesOfCommandStatu = 2;
	 	const qint16 maxFeedBackCount = 10;
	 	bool ok = true;
	 	qint16 index = 0;
	 	for (qint32 i = 0; i < maxFeedBackCount; ++i)
	 	{
	 		qint16 id = data.mid(index, bytesOfCommandID).toHex().toShort(&ok, 16);
	 		index += bytesOfCommandID;
	 		qint16 st = data.mid(index, bytesOfCommandStatu).toHex().toShort(&ok, 16);
	 		index += bytesOfCommandStatu;
	 		if (!ok) return false;
	 		_commandFeedbackMap[id] = st;
	 	}
	 
	 	quint32 x = data.mid(index, 4).toHex().toUInt(&ok, 16);
	 	index += 4;
	 	quint32 y = data.mid(index, 4).toHex().toUInt(&ok, 16);
	 	index += 4;
	 	qint16 lh = data.mid(index, 2).toHex().toShort(&ok, 16);
	 	index += 2;
	 	qint16 degree_0_1 = data.mid(index, 2).toHex().toShort(&ok, 16);
	 	index += 2;
	 	qint16 degree = data.mid(index, 2).toHex().toShort(&ok, 16);
	 	index += 2;
	 	qint16 rfid = data.mid(index, 2).toHex().toShort(&ok, 16);
	 	index += 2;
	 	quint32 speed = data.mid(index, 4).toHex().toUInt(&ok, 16);
	 	index += 4;
	 	quint64 error = data.mid(index, 8).toHex().toULongLong(&ok, 16);
	 	index += 8;
	 	quint64 warning = data.mid(index, 8).toHex().toULongLong(&ok, 16);
	 	index += 8;
	 	quint32 statu = data.mid(index, 4).toHex().toUInt(&ok, 16);
	 	index += 4;
	 	qint16 battery = data.mid(index, 2).toHex().toShort(&ok, 16);
	 
	 	if (ok)
	 	{
	 		_xPos = x;
	 		_yPos = y;
			_liftHeight = lh;
	 		_degree_0_1 = degree_0_1;
			_degree = degree;
	 		_rfid = rfid;
	 		_speed = speed;
			_error = error;
	 		_warning = warning;
			_status = statu;
			_battery = battery;
			return true;
	 	}
		return false;
}

*/



namespace core {
	//qint32 agvType = 0, qint32 nagaMode = 0, qint32 paramsCount = 0, E_ARG_TYPE argType = ARG_UNDEFINED
	const SunnyTcsAgvCode SunnyTcsMapVehicle_normal::_code(MAP_VEHICLE_NORMAL_CODE_ID,
		MAP_VEHICLE_NORMAL_CODE_NAGE, 
		MAP_VEHICLE_NORMAL_CODE_PARAM_COUNT, 
		MAP_VEHICLE_NORMAL_CODE_ARG_TYPE);

}



core::SunnyTcsMapVehicle_normal::SunnyTcsMapVehicle_normal(const SunnyTcsMapCoorSys * cs, qint32 id, QString ip, quint16 port, qint32 groupId)
	: A_SunnyTcsMapVehicle(cs, _code, id, ip, port, groupId)
{
	_coor._dim = E_TWO_DIMENSION;
	
}

SunnyTcsAgvStat core::SunnyTcsMapVehicle_normal::getAgvStat() const
{
	return SunnyTcsAgvStat();
}

bool core::SunnyTcsMapVehicle_normal::CreateOrderAction(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData * data, QString & err)
{
	return false;
}

bool core::SunnyTcsMapVehicle_normal::updateCommand(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData * data, QString & err)
{
	return false;
}

bool core::SunnyTcsMapVehicle_normal::updateData(const QByteArray & data, QString & err)
{
	return false;
}
