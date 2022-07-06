#pragma once
#include "SunnyTcsCoreV3.h"


using namespace basic;

namespace core {

	//可执行对象的统一形式 void (int 单次循环次数，bool 是否为主线任务）
	typedef SunnyTcsThreadSeed_basic<void(int, bool), std::function<void(int, bool)>*> SunnyTcsCoreSeed_basic;

	class SunnyTcsCoreSeed :public SunnyTcsCoreSeed_basic
	{
	public:
		explicit SunnyTcsCoreSeed(int msleep)
			:SunnyTcsCoreSeed_basic(msleep){}
		SunnyTcsCoreSeed(const SunnyTcsCoreSeed&) = delete;
		virtual ~SunnyTcsCoreSeed() {
			QQueue<int>* argQueue_1 = (QQueue<int>*) _args[1];
			QQueue<bool>* argQueue_2 = (QQueue<bool>*) _args[2];
			delete argQueue_1;
			delete argQueue_2;
		}
		SunnyTcsCoreSeed& operator=(const SunnyTcsCoreSeed&) = delete;

		virtual bool work(int n) override {
			THREAD_EXEC_PTR(THREAD_ARG(1, int), THREAD_ARG(2, bool));
			THREAD_CLEAR_ARG(1, int);
			THREAD_CLEAR_ARG(2, bool);
			return true;
		}


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