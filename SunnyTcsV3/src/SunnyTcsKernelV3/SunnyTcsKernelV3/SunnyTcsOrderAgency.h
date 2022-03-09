#pragma once
#include "SunnyTcsKernelGeneral.h"




class SunnyTcsCraftAgency :public I_SunnyTcsCraftAgency{
public:

	SunnyTcsCraftAgency() :I_SunnyTcsCraftAgency() {}


	// ͨ�� I_SunnyTcsCraftAgency �̳�
	virtual bool transferCraft(std::shared_ptr<SunnyTcsOrder> craft, quint8 curNodeID, quint8 tarNodeId) override;

	virtual bool registerRecivier(quint8 id, I_SunnyTcsCraftRecivier * recv) override;

	virtual void logoutRecivier(quint8 id) override;



protected:
	QHash<quint8, I_SunnyTcsCraftRecivier*> _recvs;//����н�����Ŀǰֻ�г������г��ڲŻ�����,û�б�ҪӦ�Զ��̻߳���������û��




};