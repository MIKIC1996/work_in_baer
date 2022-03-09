#include "SunnyTcsMessageCenter.h"


namespace core {
	


		SunnyTcsMessageCenter::SunnyTcsMessageCenter(std::shared_ptr<I_SunnyTcsRunner> runnerPtr, std::shared_ptr<I_SunnyTcsLogger> logger)
			:I_SunnyTcsMsgSender(runnerPtr, logger)
		{
			_function = [this](int, bool)->void {
				return;
			};
		}

		SunnyTcsMessageCenter::~SunnyTcsMessageCenter()
		{
		}


}

