#include "SunnyTcsVehicle.h"


namespace basic {

	QList<SunnyTcsAgvCode> SunnyTcsVehicle::_vehicleSupported;
	bool SunnyTcsVehicle::isInited = initVehicleSupportedList();


	SunnyTcsVehicle::SunnyTcsVehicle(SunnyTcsAgvCode code, qint32 id)
		:I_SunnyTcsAgvStat(code,id),_ip("127.0.0.1"),_port(4000)
	{
		_connectId = connectionID(_ip, _port);
	}

	SunnyTcsArg SunnyTcsVehicle::getAttribution(QString key, bool & ok) const
	{
		return SunnyTcsArg();
	}

	bool SunnyTcsVehicle::setAttribution(QString key, SunnyTcsArg arg)
	{
		return false;
	}

	QVector<SunnyTcsMapBlock> SunnyTcsVehicle::getBlocks(qint32 resolution) const
	{
		SunnyTcsAgvCoordinate&& coor = this->getAgvCurCoor();
		QVector<SunnyTcsMapBlock> bs;
		if (coor._dim == E_TWO_DIMENSION) {//getblock ��ר�����ڼ����ά����ĺ�����һά����û���ã���������������
			SunnyTcsMapBlock bl(coor._x / resolution + 1, coor._y / resolution + 1);
			bs << bl;
		}
		return bs;
	}

}