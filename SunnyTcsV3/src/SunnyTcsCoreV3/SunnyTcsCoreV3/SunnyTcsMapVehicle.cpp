#include "SunnyTcsMapVehicle.h"



namespace core {

	A_SunnyTcsMapVehicle::A_SunnyTcsMapVehicle(const SunnyTcsMapCoorSys * cs, SunnyTcsAgvCode code, qint32 id, QString ip, quint16 port, qint32 groupId)
		:A_SunnyTcsMapObject(id), _cs(cs), _code(code), 
		_ip(ip), _port(port), _connectId(0) , _groupId(groupId) ,
		_status(Eunconnected),_coor(),_curPos(),_orderId_binded(0)
	{
		_connectId = connectionID(_ip, _port);
	}


	A_SunnyTcsMapVehicle::~A_SunnyTcsMapVehicle()
	{

	}


	SunnyTcsMapObject_tag A_SunnyTcsMapVehicle::getTag() const
	{
		return SunnyTcsMapObject_tag(Evehicle, _id);
	}


}

