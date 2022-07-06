#pragma once
#include "SunnyTcsAlgorithmV3.h"


#define ERROR_ALGORITHM_DISPATCH_BASIC_NO_DECIDE_AGV "DISPATCH_ERROR_000001"

using namespace basic;

namespace algorithm {

	//ֱ�Ӱ��ն���ָ���ĳ������з������򵥵Ļ������䷽��
	class SUNNYTCSALGORITHMV3_EXPORT SunnyTcsDispatchAlgorithm_basic :public I_SunnyTcsDispatchAlgorithm
	{
	public:
		SunnyTcsDispatchAlgorithm_basic();
		SunnyTcsDispatchAlgorithm_basic(const SunnyTcsDispatchAlgorithm_basic&) = delete;
		virtual ~SunnyTcsDispatchAlgorithm_basic() {}
		SunnyTcsDispatchAlgorithm_basic& operator=(const SunnyTcsDispatchAlgorithm_basic&) = delete;

		// ͨ�� I_SunnyTcsDispatchAlgorithm �̳�
		virtual bool dispatch(SunnyTcsCraft & route,I_SunnyTcsActualData * data, qint32 & targetAgv) override;

		virtual qint32 getId() const override;

	};


}



