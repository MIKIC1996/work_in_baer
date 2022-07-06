#pragma once
#include "SunnyTcsCoreV3.h"
#include "SunnyTcsMapVehicle.h"



namespace core {


	//agv���󹤳�������ʵ�� agv �� ģ�� ֮��Ľ���
	class I_SunnyTcsAgvFactory
	{
	public:
		I_SunnyTcsAgvFactory() = default;
		I_SunnyTcsAgvFactory(const I_SunnyTcsAgvFactory&) = delete;
		virtual ~I_SunnyTcsAgvFactory() = default;
		I_SunnyTcsAgvFactory& operator=(const I_SunnyTcsAgvFactory&) = delete;

		//����agv
		virtual std::shared_ptr<A_SunnyTcsMapVehicle>  createVehicle(QJsonObject& params) = 0;
	};


}


