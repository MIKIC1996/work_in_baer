#pragma once
#include "SunnyTcsOrderCenter.h"




class SunnyTcsKernelMsgCenter
{
public:
	SunnyTcsKernelMsgCenter();
	~SunnyTcsKernelMsgCenter();

	

protected:
	I_SunnyTcsActualData* _model;//ģ�ͽӿ�
	I_SunnyTcsOrderCenter* _orderCenter;//�������Ľӿ�
	

};

