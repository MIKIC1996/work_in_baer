#pragma once
#include "SunnyTcsCoreV3.h"
#include "SunnyTcsMapVehicle.h"



namespace core {


	//agv抽象工厂，负责实现 agv 与 模型 之间的解耦
	class I_SunnyTcsAgvFactory
	{
	public:
		I_SunnyTcsAgvFactory() = default;
		I_SunnyTcsAgvFactory(const I_SunnyTcsAgvFactory&) = delete;
		virtual ~I_SunnyTcsAgvFactory() = default;
		I_SunnyTcsAgvFactory& operator=(const I_SunnyTcsAgvFactory&) = delete;

		//创建agv
		virtual std::shared_ptr<A_SunnyTcsMapVehicle>  createVehicle(QJsonObject& params) = 0;
	};


}


