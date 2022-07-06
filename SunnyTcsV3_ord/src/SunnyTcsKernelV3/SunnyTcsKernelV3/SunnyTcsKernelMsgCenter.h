#pragma once
#include "SunnyTcsOrderCenter.h"




class SunnyTcsKernelMsgCenter
{
public:
	SunnyTcsKernelMsgCenter();
	~SunnyTcsKernelMsgCenter();

	

protected:
	I_SunnyTcsActualData* _model;//模型接口
	I_SunnyTcsOrderCenter* _orderCenter;//订单中心接口
	

};

