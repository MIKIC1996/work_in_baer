#pragma once

#include "SunnyTcsCoreV3.h"

#include "I_SunnyTcsMsgSender.h"
#include "I_SunnyTcsRunner.h"

namespace core {

	class SunnyTcsMessageCenter :public I_SunnyTcsMsgSender
	{
	public:
		SunnyTcsMessageCenter(std::shared_ptr<I_SunnyTcsRunner>  runnerPtr,std::shared_ptr<I_SunnyTcsLogger> logger);
		 ~SunnyTcsMessageCenter();

		

	protected:
		QMutex _recvLock;
		QQueue<QByteArray> _recvQueue;//�ɸ���recivier�Լ�����Ϣ���н��봦�����ͨѶ��Ч��
	};


}



