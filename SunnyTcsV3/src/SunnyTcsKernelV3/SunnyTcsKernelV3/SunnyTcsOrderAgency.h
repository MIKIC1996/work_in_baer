#pragma once
#include "SunnyTcsKernelGeneral.h"




class SunnyTcsCraftAgency :public I_SunnyTcsCraftAgency{
public:

	SunnyTcsCraftAgency() :I_SunnyTcsCraftAgency() {}


	// 通过 I_SunnyTcsCraftAgency 继承
	virtual bool transferCraft(std::shared_ptr<SunnyTcsOrder> craft, quint8 curNodeID, quint8 tarNodeId) override;

	virtual bool registerRecivier(quint8 id, I_SunnyTcsCraftRecivier * recv) override;

	virtual void logoutRecivier(quint8 id) override;



protected:
	QHash<quint8, I_SunnyTcsCraftRecivier*> _recvs;//这个中介配置目前只有程序运行初期才会配置,没有必要应对多线程环境，所以没锁




};