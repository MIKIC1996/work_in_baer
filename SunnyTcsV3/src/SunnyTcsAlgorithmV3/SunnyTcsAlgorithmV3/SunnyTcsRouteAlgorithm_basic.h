#pragma once

#include "SunnyTcsAlgorithmV3.h"

//订单状态不对
#define ERROR_ALGORITHM_ROUTE_ORDER_STATUS_ERROR "ROUTE_ERROR_000001"
//订单无需规划
#define ERROR_ALGORITHM_ROUTE_ORDER_NONEED_TOROUTE "ROUTE_ERROR_000002"
//不存在可规划的路径
#define ERROR_ALGORITHM_ROUTE_NOROUTE_TOPLAN "ROUTE_ERROR_000003"
//actualData错误
#define ERROR_ALGORITHM_ROUTE_ACTUALDATA_ERROR "ROUTE_ERROR_000004"

using namespace basic;

namespace algorithm {

	//2.0使用的 最短路径算法，作为 3.0 的基本算法使用
	class SUNNYTCSALGORITHMV3_EXPORT SunnyTcsRouteAlgorithm_basic :public I_SunnyTcsRouteAlgorithm
	{
	public:
		SunnyTcsRouteAlgorithm_basic();
		SunnyTcsRouteAlgorithm_basic(const SunnyTcsRouteAlgorithm_basic&) = delete;
		virtual ~SunnyTcsRouteAlgorithm_basic() {}
		SunnyTcsRouteAlgorithm_basic& operator=(const SunnyTcsRouteAlgorithm_basic&) = delete;

		// 通过 I_SunnyTcsRouteAlgorithm 继承
		virtual bool route(SunnyTcsCraft & route, I_SunnyTcsActualData * data) override;

		virtual qint32 getId() const override;

		//两点之间做最短路径规划
		bool routeBetweenTwoPoints(qint32 source, qint32 target, I_SunnyTcsActualData * data, QList<qint32>& ret);

	};


}



