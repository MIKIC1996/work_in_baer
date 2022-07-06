#pragma once
#include "I_SunnyTcsRunner.h"


using namespace basic;

namespace core {

	//线程中心
	class SUNNYTCSCOREV3_EXPORT SunnyTcsThreadCenter :public I_SunnyTcsRunner
	{
	public:

		SunnyTcsThreadCenter(qint32 count, qint32 msleep);
		SunnyTcsThreadCenter(const SunnyTcsThreadCenter&) = delete;
		virtual ~SunnyTcsThreadCenter() {
			stopRun();
		}
		SunnyTcsThreadCenter& operator=(const SunnyTcsThreadCenter&) = delete;

		inline qint32 seedCount()const {
			return _count;
		}

		void startRun() {
			auto iter = _seeds.begin();
			while (iter != _seeds.end()) {
				(*iter)->start();
				++iter;
			}
		}

		void stopRun() {
			auto iter = _seeds.begin();
			while (iter != _seeds.end()) {
				(*iter)->stopRun();
				++iter;
			}
		}

		// 通过 I_SunnyTcsRunner 继承
		virtual void submitTask(SunnyTcsCoreSeed::Task func,int cirCount,bool isMainLine) override;

	protected:
		qint32 _count;
		QList<std::shared_ptr<SunnyTcsCoreSeed>> _seeds;
	};


}


