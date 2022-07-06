#pragma once


#include <SunnyTcsBasicV3.h>
#include <SunnyTcsPath.h>
#include <SunnyTcsLocation.h>
#include <SunnyTcsVehicle.h>


using namespace basic;

//接口定义





//消息中心接口
class I_SunnyTcsKernelMsgCenter {

	virtual void sendMsg(SunnyTcsMessage msg) = 0;

};



//订单中心接口定义
class I_SunnyTcsOrderCenter
{
	virtual void addNewTemplate(SunnyTcsCraft* craft) = 0;

	virtual void removeTemplate(quint64 templateId) = 0;

	virtual void addNewOrder(SunnyTcsOrder* order) = 0;

	virtual void addNewOrder(quint64 templateId) = 0;//根据模板ID,增加一个新订单

	virtual void changeOrderStatus(quint64 orderId,E_SunnyTcsRouteStatus status) = 0;//修改订单状态，一般用于取消

	virtual void modifyOrderPriority(quint16 level) = 0;//调整订单优先级

};




//订单中介接口
class I_SunnyTcsCraftAgency;


//订单流转的接收者接口定义
class I_SunnyTcsCraftRecivier
{
public:
	I_SunnyTcsCraftRecivier(quint8 craftId, I_SunnyTcsCraftAgency* agency)
		:_craftNodeId(craftId), _craftAgency(agency)
	{}
	I_SunnyTcsCraftRecivier(const I_SunnyTcsCraftRecivier&) = delete; //中介接收者一般都是独一无二的
	virtual ~I_SunnyTcsCraftRecivier() {}
	I_SunnyTcsCraftRecivier& operator=(const I_SunnyTcsCraftRecivier&) = delete;

	inline quint8 getCraftNodeId()const { return _craftNodeId; }

	//各个recivier自己去定义,接收订单
	virtual void insertCraft(std::shared_ptr<SunnyTcsOrder> craft) = 0;

	virtual bool tryInsertCraft(std::shared_ptr<SunnyTcsOrder> craft) = 0;

protected:
	const quint8 _craftNodeId; //中介接收者ID
	I_SunnyTcsCraftAgency* _craftAgency; //订单中介指针
};




//内部订单通讯的中介者接口定义
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

	//订单流转
	virtual bool transferCraft(std::shared_ptr<SunnyTcsOrder> craft,quint8 curNodeID, quint8 tarNodeId ) = 0;

	//注册
	virtual bool registerRecivier(quint8 id, I_SunnyTcsCraftRecivier* recv) = 0;
	
	//注销
	virtual void logoutRecivier(quint8 id) = 0;

};

