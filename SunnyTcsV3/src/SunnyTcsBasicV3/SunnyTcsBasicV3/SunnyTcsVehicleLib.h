#pragma once

#include "SunnyTcsVehicle.h"


namespace basic {


	


	//初始车型，最常见的指令型车型
	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle_normal : public SunnyTcsVehicle
	{
	public:
		//ctor
		SunnyTcsVehicle_normal(qint32 id) : SunnyTcsVehicle(vehicle_normal, id) {}
		//copy ctor
		SunnyTcsVehicle_normal(const SunnyTcsVehicle_normal&) = delete;
		//detor
		virtual ~SunnyTcsVehicle_normal() {}
		//assignment
		SunnyTcsVehicle_normal& operator=(const SunnyTcsVehicle_normal&) = delete;



		// 通过 SunnyTcsVehicle 继承
		virtual bool updateData(const QByteArray & data) override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

	};


	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle_mitsubishi_battery :public SunnyTcsVehicle 
	{
	public:
		//ctor
		SunnyTcsVehicle_mitsubishi_battery(qint32 id) : SunnyTcsVehicle(vehicle_mitsubishi, id) {}
		//copy ctor
		SunnyTcsVehicle_mitsubishi_battery(const SunnyTcsVehicle_mitsubishi_battery&) = delete;
		//detor
		virtual ~SunnyTcsVehicle_mitsubishi_battery() {}
		//assignment
		SunnyTcsVehicle_mitsubishi_battery& operator=(const SunnyTcsVehicle_mitsubishi_battery&) = delete;




		// 通过 SunnyTcsVehicle 继承
		virtual bool updateData(const QByteArray & data) override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

	};




	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle_daimer_engine :public SunnyTcsVehicle
	{
	public:
		//ctor
		SunnyTcsVehicle_daimer_engine(qint32 id) : SunnyTcsVehicle(vehicle_daimler_engine, id) {}
		//copy ctor
		SunnyTcsVehicle_daimer_engine(const SunnyTcsVehicle_daimer_engine&) = delete;
		//detor
		virtual ~SunnyTcsVehicle_daimer_engine() {}
		//assignment
		SunnyTcsVehicle_daimer_engine& operator=(const SunnyTcsVehicle_daimer_engine&) = delete;

		// 通过 SunnyTcsVehicle 继承
		virtual bool updateData(const QByteArray & data) override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

	};
	

}

