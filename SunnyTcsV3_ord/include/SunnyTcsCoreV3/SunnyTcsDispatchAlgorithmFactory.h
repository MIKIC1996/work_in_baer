#pragma once
#include "SunnyTcsCoreV3.h"
#include "SunnyTcsDispatcher.h"

using namespace algorithm;

namespace core {


	//分配算法的抽象工厂,考虑到每个项目所需要的分配算法或许不同。
	class I_SunnyTcsDispatchAlgorithmFactory
	{
	public:
		I_SunnyTcsDispatchAlgorithmFactory() = default;
		I_SunnyTcsDispatchAlgorithmFactory(const I_SunnyTcsDispatchAlgorithmFactory&) = default;
		virtual ~I_SunnyTcsDispatchAlgorithmFactory() {}
		I_SunnyTcsDispatchAlgorithmFactory& operator=(const I_SunnyTcsDispatchAlgorithmFactory&) = default;

		//一次性构造
		virtual bool createDispatchAlgorithm(A_SunnyTcsDispatcher& dispatcher)const = 0;
	};




	//基本分配器
	class SunnyTcsDispatchAlgorithmFactory_basic :public I_SunnyTcsDispatchAlgorithmFactory
	{
	public:
		SunnyTcsDispatchAlgorithmFactory_basic() = default;
		SunnyTcsDispatchAlgorithmFactory_basic(const SunnyTcsDispatchAlgorithmFactory_basic&) = default;
		~SunnyTcsDispatchAlgorithmFactory_basic() = default;
		SunnyTcsDispatchAlgorithmFactory_basic& operator=(const SunnyTcsDispatchAlgorithmFactory_basic&) = default;

		//一次性构造
		virtual bool createDispatchAlgorithm(A_SunnyTcsDispatcher& dispatcher)const override;
	};


}



