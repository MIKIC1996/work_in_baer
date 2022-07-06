#include "SunnyTcsVehicleLib.h"

namespace basic {


	QMap<qint32, SunnyTcsAgvCode> I_SunnyTcsVehicleFactory::_vehicleSupported;
	bool I_SunnyTcsVehicleFactory::isInited = initVehicleSupportedMap();

	bool SunnyTcsVehicle_normal::updateData(const QByteArray & data)
	{
		return false;
	}

	bool SunnyTcsVehicle_normal::CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data)
	{
		return false;
	}

	bool SunnyTcsVehicle_normal::updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data)
	{
		return false;
	}

	bool SunnyTcsVehicle_mitsubishi_battery::updateData(const QByteArray & data)
	{
		return false;
	}

	bool SunnyTcsVehicle_mitsubishi_battery::CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data)
	{
		return false;
	}

	bool SunnyTcsVehicle_mitsubishi_battery::updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data)
	{
		return false;
	}

	bool SunnyTcsVehicle_daimer_engine::updateData(const QByteArray & data)
	{
		return false;
	}

	bool SunnyTcsVehicle_daimer_engine::CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data)
	{
		return false;
	}

	bool SunnyTcsVehicle_daimer_engine::updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data)
	{
		return false;
	}



	SunnyTcsVehicle * SunnyTcsBasicVehicleFactory::createVehicleByCodeId(qint32 id)
	{

		if (id == vehicle_normal._agvType) {
			return new SunnyTcsVehicle_normal(0);
		}
		else if(id== vehicle_mitsubishi._agvType){
			return new SunnyTcsVehicle_mitsubishi_battery(0);
		}
		else if (id == vehicle_daimler_engine._agvType) {
			return new SunnyTcsVehicle_daimer_engine(0);
		}
		return nullptr;
	}


}