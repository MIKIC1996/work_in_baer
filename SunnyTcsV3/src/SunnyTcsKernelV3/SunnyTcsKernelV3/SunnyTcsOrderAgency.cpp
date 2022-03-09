#include "SunnyTcsOrderAgency.h"

bool SunnyTcsCraftAgency::transferCraft(std::shared_ptr<SunnyTcsOrder> craft, quint8 curNodeID, quint8 tarNodeId)
{
	if (!_recvs.contains(tarNodeId)) {
		return false; //向不存在的接收者发送订单
	}
	return false;
}

bool SunnyTcsCraftAgency::registerRecivier(quint8 id, I_SunnyTcsCraftRecivier * recv)
{
	if (_recvs.contains(id)) {
		return false;
	}
	_recvs.insert(id, recv);
	return true;
}

void SunnyTcsCraftAgency::logoutRecivier(quint8 id)
{
	_recvs.contains(id) ? _recvs.remove(id) : 1;
}
