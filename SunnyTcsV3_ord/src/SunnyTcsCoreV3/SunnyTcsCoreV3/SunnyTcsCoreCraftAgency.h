#pragma once

#include "I_SunnyTcsCraftAgency.h"

namespace core {

	class SunnyTcsCoreCraftAgency :public I_SunnyTcsCraftAgency
	{
	public:
		SunnyTcsCoreCraftAgency();
		SunnyTcsCoreCraftAgency(const SunnyTcsCoreCraftAgency&) = delete;
		virtual ~SunnyTcsCoreCraftAgency() {}
		SunnyTcsCoreCraftAgency& operator=(const SunnyTcsCoreCraftAgency&) = delete;

		// ͨ�� I_SunnyTcsCraftAgency �̳�
		virtual bool transferCraft(std::shared_ptr<SunnyTcsCraft> craft,
			qint32 curNodeID, qint32 tarNodeId = 0, bool isTry = false) override;

	};

}



