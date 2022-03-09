#pragma once
#include "SunnyTcsCoreV3.h"
#include "SunnyTcsDispatcher.h"

using namespace algorithm;

namespace core {


	//�����㷨�ĳ��󹤳�,���ǵ�ÿ����Ŀ����Ҫ�ķ����㷨����ͬ��
	class I_SunnyTcsDispatchAlgorithmFactory
	{
	public:
		I_SunnyTcsDispatchAlgorithmFactory() = default;
		I_SunnyTcsDispatchAlgorithmFactory(const I_SunnyTcsDispatchAlgorithmFactory&) = default;
		virtual ~I_SunnyTcsDispatchAlgorithmFactory() {}
		I_SunnyTcsDispatchAlgorithmFactory& operator=(const I_SunnyTcsDispatchAlgorithmFactory&) = default;

		//һ���Թ���
		virtual bool createDispatchAlgorithm(A_SunnyTcsDispatcher& dispatcher)const = 0;
	};




	//����������
	class SunnyTcsDispatchAlgorithmFactory_basic :public I_SunnyTcsDispatchAlgorithmFactory
	{
	public:
		SunnyTcsDispatchAlgorithmFactory_basic() = default;
		SunnyTcsDispatchAlgorithmFactory_basic(const SunnyTcsDispatchAlgorithmFactory_basic&) = default;
		~SunnyTcsDispatchAlgorithmFactory_basic() = default;
		SunnyTcsDispatchAlgorithmFactory_basic& operator=(const SunnyTcsDispatchAlgorithmFactory_basic&) = default;

		//һ���Թ���
		virtual bool createDispatchAlgorithm(A_SunnyTcsDispatcher& dispatcher)const override;
	};


}



