#include "SunnyTcsVehicleLib.h"

namespace basic {






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

}