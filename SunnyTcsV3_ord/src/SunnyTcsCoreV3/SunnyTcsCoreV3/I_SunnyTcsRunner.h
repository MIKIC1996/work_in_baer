#pragma once
#include "SunnyTcsCoreV3.h"


using namespace basic;

namespace core {

	//��ִ�ж����ͳһ��ʽ void (int ����ѭ��������bool �Ƿ�Ϊ��������
	typedef SunnyTcsThreadSeed_basic<void(int, bool)> SunnyTcsCoreSeed_basic;

	class SunnyTcsCoreThread : public QThread
	{
	public:

		

	};


	//�ں�ִ�����Ľӿ�
	class I_SunnyTcsRunner {
	public:
		I_SunnyTcsRunner() {}
		I_SunnyTcsRunner(const I_SunnyTcsRunner&) = delete;
		virtual ~I_SunnyTcsRunner() {}
		I_SunnyTcsRunner& operator=(const I_SunnyTcsRunner&) = delete;

		virtual void submitTask(SunnyTcsCoreSeed::Task func, int cirCount, bool isMainLine/*�Ƿ�������*/) = 0;
	};


	//�ں˵�ִ�����ӿ�
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