#include "SunnyTcsOrderCenter.h"

namespace core {


	A_SunnyTcsOrderCenter::A_SunnyTcsOrderCenter(std::shared_ptr<I_SunnyTcsRunner> runner, 
		std::shared_ptr<I_SunnyTcsCraftAgency> agency, 
		std::shared_ptr<I_SunnyTcsMsgSender> sender,
		std::shared_ptr<I_SunnyTcsLogger> loger)
		:I_SunnyTcsExecutor(runner),
		I_SunnyTcsCraftRecivier(NODE_ID_ORDERCENTER,agency),
		I_SunnyTcsMsgMember(NODE_ID_ORDERCENTER,sender),
		I_SunnyTcsLoggerUser(loger)
	{
		//订单中心执行的工作有
		//1 同步订单数据（有需求的话)
		//2 对完成的订单进行删除
		//3 创建订单
		//4 取消订单
		//5 发送更新数据
		_function = [this](int cirCount, bool isMainLine)->void {

			return;
		};

	}

	A_SunnyTcsOrderCenter::~A_SunnyTcsOrderCenter()
	{
	}


	bool A_SunnyTcsOrderCenter::createOrder(qint32 craftId, QString & err, qint32 agvId)
	{
// 		if (!_crafts.keys().contains(craftId)) {
// 			err = "no this craft id";
// 			return false;
// 		}
// 
// 		std::shared_ptr<SunnyTcsCraft> ptr = _crafts[craftId]->toInitOrder(agvId);
// 
// 		if (_allOrders.keys().contains(ptr->getOrderId())) {//UID error
// 			Q_ASSERT(0);
// 		}
// 		_allOrders.insert(ptr->getOrderId(), ptr);
// 
// 		ptr->setCurrentStatus(ERactived);//设置为分配状态
// 										 //激活订单队列
// 		_craftAgency->transferCraft(ptr, NODE_ID_ORDERCENTER, NODE_ID_DISPATCHER, false);
		return true;
	}

	//取消订单
	void A_SunnyTcsOrderCenter::cancelOrder(qint32 orderId)
	{
// 		if (!_allOrders.keys().contains(orderId)) {
// 			return;
// 		}
// 		_allOrders[orderId]->setCurrentStatus(ERcanceled);//订单中心只允许将状态改变到取消，具体工作交由其他执行者来做
// 		_allOrders.remove(orderId);

	}

	
	void A_SunnyTcsOrderCenter::msgHandle()
	{
		SunnyTcsMessage msg;
		if (!this->getFirstMsg(msg)) {
			return;
		}

		switch (msg.getMsgId()) {
		case MSG_RECV_ID_ADD_CRAFT:
			break;
		case MSG_RECV_ID_CREATE_ORDER:
			break;
		case MSG_RECV_ID_CANCEL_ORDER:
			break;
		case MSG_RECV_ID_DELETE_CRAFT:
			break;
		}



	}

}

