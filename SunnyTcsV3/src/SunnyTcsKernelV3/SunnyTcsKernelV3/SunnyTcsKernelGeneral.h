#pragma once


#include <SunnyTcsBasicV3.h>
#include <SunnyTcsPath.h>
#include <SunnyTcsLocation.h>
#include <SunnyTcsVehicle.h>


using namespace basic;

//�ӿڶ���





//��Ϣ���Ľӿ�
class I_SunnyTcsKernelMsgCenter {

	virtual void sendMsg(SunnyTcsMessage msg) = 0;

};



//�������Ľӿڶ���
class I_SunnyTcsOrderCenter
{
	virtual void addNewTemplate(SunnyTcsCraft* craft) = 0;

	virtual void removeTemplate(quint64 templateId) = 0;

	virtual void addNewOrder(SunnyTcsOrder* order) = 0;

	virtual void addNewOrder(quint64 templateId) = 0;//����ģ��ID,����һ���¶���

	virtual void changeOrderStatus(quint64 orderId,E_SunnyTcsRouteStatus status) = 0;//�޸Ķ���״̬��һ������ȡ��

	virtual void modifyOrderPriority(quint16 level) = 0;//�����������ȼ�

};




//�����н�ӿ�
class I_SunnyTcsCraftAgency;


//������ת�Ľ����߽ӿڶ���
class I_SunnyTcsCraftRecivier
{
public:
	I_SunnyTcsCraftRecivier(quint8 craftId, I_SunnyTcsCraftAgency* agency)
		:_craftNodeId(craftId), _craftAgency(agency)
	{}
	I_SunnyTcsCraftRecivier(const I_SunnyTcsCraftRecivier&) = delete; //�н������һ�㶼�Ƕ�һ�޶���
	virtual ~I_SunnyTcsCraftRecivier() {}
	I_SunnyTcsCraftRecivier& operator=(const I_SunnyTcsCraftRecivier&) = delete;

	inline quint8 getCraftNodeId()const { return _craftNodeId; }

	//����recivier�Լ�ȥ����,���ն���
	virtual void insertCraft(std::shared_ptr<SunnyTcsOrder> craft) = 0;

	virtual bool tryInsertCraft(std::shared_ptr<SunnyTcsOrder> craft) = 0;

protected:
	const quint8 _craftNodeId; //�н������ID
	I_SunnyTcsCraftAgency* _craftAgency; //�����н�ָ��
};




//�ڲ�����ͨѶ���н��߽ӿڶ���
class I_SunnyTcsCraftAgency
{
public:
	//ctor
	I_SunnyTcsCraftAgency() {}
	//copy ctor
	I_SunnyTcsCraftAgency(const I_SunnyTcsCraftAgency&) = delete;
	//dtor
	virtual ~I_SunnyTcsCraftAgency() {}
	//assignment
	I_SunnyTcsCraftAgency& operator=(const I_SunnyTcsCraftAgency&) = delete;

	//������ת
	virtual bool transferCraft(std::shared_ptr<SunnyTcsOrder> craft,quint8 curNodeID, quint8 tarNodeId ) = 0;

	//ע��
	virtual bool registerRecivier(quint8 id, I_SunnyTcsCraftRecivier* recv) = 0;
	
	//ע��
	virtual void logoutRecivier(quint8 id) = 0;

};

