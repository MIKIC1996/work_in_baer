#pragma once
#include "SunnyTcsCoreV3.h"
#include "SunnyTcsOrderCenter.h"
#include "SunnyTcsMapModel.h"


#define DEFAULT_DISPATCHER_DEAL_COUNT 3

using namespace basic;
using namespace algorithm;


namespace core {

	//声明
	class I_SunnyTcsDispatchAlgorithmFactory;
	class SunnyTcsDispatchAlgorithmFactory_basic;

	class A_SunnyTcsDispatcher
		:public I_SunnyTcsExecutor,
		public I_SunnyTcsCraftRecivier,
		public I_SunnyTcsMsgMember,
		public I_SunnyTcsLoggerUser
	{
	public:
		friend class I_SunnyTcsDispatchAlgorithmFactory;
		
		A_SunnyTcsDispatcher(
			std::shared_ptr<I_SunnyTcsActualData> acData,
			std::shared_ptr<I_SunnyTcsRunner> runner,
			std::shared_ptr<I_SunnyTcsCraftAgency> agency,
			std::shared_ptr<I_SunnyTcsMsgSender> sender,
			std::shared_ptr<I_SunnyTcsLogger> loger
		);

		A_SunnyTcsDispatcher(const A_SunnyTcsDispatcher&) = delete;

		virtual ~A_SunnyTcsDispatcher();

		A_SunnyTcsDispatcher& operator=(const A_SunnyTcsDispatcher&) = delete;

		void clearAlgorithms() {
			_dispatchAlgorithms.clear();
		}

		bool addAlgorithm(std::shared_ptr<I_SunnyTcsDispatchAlgorithm> algorithm_ptr) {
			if (_dispatchAlgorithms.keys().contains(algorithm_ptr->getId())) {
				return false;
			}
		//	_dispatchAlgorithms.insert(algorithm_ptr->getId())


		}

	protected:
		QMap<qint32, std::shared_ptr<I_SunnyTcsDispatchAlgorithm>> _dispatchAlgorithms;
		std::shared_ptr<I_SunnyTcsActualData> _model;

	};


	//通用分配器
	class SunnyTcsDispatcher_general : public A_SunnyTcsDispatcher
	{
	public:
		friend class SunnyTcsDispatchAlgorithmFactory_basic;

		SunnyTcsDispatcher_general(
			std::shared_ptr<I_SunnyTcsActualData> acData,
			std::shared_ptr<I_SunnyTcsRunner> runner,
			std::shared_ptr<I_SunnyTcsCraftAgency> agency,
			std::shared_ptr<I_SunnyTcsMsgSender> sender,
			std::shared_ptr<I_SunnyTcsLogger> loger);

	protected:
		void msgHandle();

		virtual ~SunnyTcsDispatcher_general() {}



	};


}




