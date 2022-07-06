#pragma once
#include "SunnyTcsCoreV3.h"


using namespace basic;

namespace core {

	//可执行对象的统一形式 void (int 单次循环次数，bool 是否为主线任务）
	typedef SunnyTcsThreadSeed_basic<void(int, bool)> SunnyTcsCoreSeed_basic;

	class SunnyTcsCoreThread : public QThread
	{
	public:

		

	};


	//内核执行中心接口
	class I_SunnyTcsRunner {
	public:
		I_SunnyTcsRunner() {}
		I_SunnyTcsRunner(const I_SunnyTcsRunner&) = delete;
		virtual ~I_SunnyTcsRunner() {}
		I_SunnyTcsRunner& operator=(const I_SunnyTcsRunner&) = delete;

		virtual void submitTask(SunnyTcsCoreSeed::Task func, int cirCount, bool isMainLine/*是否是主线*/) = 0;
	};


	//内核的执行器接口
	class I_SunnyTcsExecutor {
	public:
		I_SunnyTcsExecutor() :_runner(nullptr), _function() {}
		explicit I_SunnyTcsExecutor(std::shared_ptr<I_SunnyTcsRunner> ptr) :_runner(ptr), _function() {}
		I_SunnyTcsExecutor(const I_SunnyTcsExecutor&) = delete;
		virtual ~I_SunnyTcsExecutor() {};
		I_SunnyTcsExecutor& operator=(const I_SunnyTcsExecutor&) = delete;

	protected:
		std::shared_ptr<I_SunnyTcsRunner> _runner;
		std::function<void(int, bool)> _function;
	};


}