#include "SunnyTcsDispatchAlgorithm_basic.h"





algorithm::SunnyTcsDispatchAlgorithm_basic::SunnyTcsDispatchAlgorithm_basic()
	:I_SunnyTcsDispatchAlgorithm(2)
{
}

bool algorithm::SunnyTcsDispatchAlgorithm_basic::dispatch(SunnyTcsCraft & route, I_SunnyTcsActualData * data, qint32 & targetAgv)
{
	
// 	if (route.getCurrentStatus() != ERactived)return false;
// 	int tar = route.getAgvId();
// 	if (tar == 0) {
// 		route.setCurrentStatus(ERFailed);//û��ָ��agv����ʧ��
// 		route.setErrorMsg(ERROR_ALGORITHM_DISPATCH_BASIC_NO_DECIDE_AGV);
// 		return false;
// 	}
// 	bool ok(true);
// 	
// 
// 	if (data->getAgvStat(tar, ok)._status != Econnected) {
// 		return false;
// 	}
// 	targetAgv = tar;
// 	route.setAgvId(tar);
// 	route.setCurrentStatus(ERrouting);//ָ���ɹ���ִ����һ�׶�
	return true;
}

qint32 algorithm::SunnyTcsDispatchAlgorithm_basic::getId() const
{
	return ALGORITHM_DISPATCH_BASIC_ID;
}
