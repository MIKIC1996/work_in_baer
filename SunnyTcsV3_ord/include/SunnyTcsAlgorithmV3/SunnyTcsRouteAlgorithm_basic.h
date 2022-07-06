#pragma once

#include "SunnyTcsAlgorithmV3.h"

//����״̬����
#define ERROR_ALGORITHM_ROUTE_ORDER_STATUS_ERROR "ROUTE_ERROR_000001"
//��������滮
#define ERROR_ALGORITHM_ROUTE_ORDER_NONEED_TOROUTE "ROUTE_ERROR_000002"
//�����ڿɹ滮��·��
#define ERROR_ALGORITHM_ROUTE_NOROUTE_TOPLAN "ROUTE_ERROR_000003"
//actualData����
#define ERROR_ALGORITHM_ROUTE_ACTUALDATA_ERROR "ROUTE_ERROR_000004"

using namespace basic;

namespace algorithm {

	//2.0ʹ�õ� ���·���㷨����Ϊ 3.0 �Ļ����㷨ʹ��
	class SUNNYTCSALGORITHMV3_EXPORT SunnyTcsRouteAlgorithm_basic :public I_SunnyTcsRouteAlgorithm
	{
	public:
		SunnyTcsRouteAlgorithm_basic();
		SunnyTcsRouteAlgorithm_basic(const SunnyTcsRouteAlgorithm_basic&) = delete;
		virtual ~SunnyTcsRouteAlgorithm_basic() {}
		SunnyTcsRouteAlgorithm_basic& operator=(const SunnyTcsRouteAlgorithm_basic&) = delete;

		// ͨ�� I_SunnyTcsRouteAlgorithm �̳�
		virtual bool route(SunnyTcsCraft & route, I_SunnyTcsActualData * data) override;

		virtual qint32 getId() const override;

		//����֮�������·���滮
		bool routeBetweenTwoPoints(qint32 source, qint32 target, I_SunnyTcsActualData * data, QList<qint32>& ret);

	};


}



