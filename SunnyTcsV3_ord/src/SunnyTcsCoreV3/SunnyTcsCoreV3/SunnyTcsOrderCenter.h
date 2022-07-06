#pragma once

#include "SunnyTcsCoreV3.h"
#include "I_SunnyTcsCraftAgency.h"
#include "I_SunnyTcsMsgSender.h"
#include "I_SunnyTcsRunner.h"
#include "I_SunnyTcsLogger.h"



#define JSON_ORDERCENTER_CRAFTS "orderCenterCrafts"

#define CORE_ORDERCENTER_DISPATCH_QUEUE 1
#define CORE_ORDERCENTER_ROUTING_QUEUE 2
#define CORE_ORDERCENTER_WORKING_QUEUE 3


using namespace basic;

namespace core {

	//订单中心
	class SUNNYTCSCOREV3_EXPORT A_SunnyTcsOrderCenter
		:public I_SunnyTcsExecutor, //支持作为执行器提交任务
		public I_SunnyTcsCraftRecivier,//支持内部订单交换
		public I_SunnyTcsMsgMember,//支持外部通讯
		public I_SunnyTcsLoggerUser //支持日志记录
	{
	public:

		A_SunnyTcsOrderCenter(std::shared_ptr<I_SunnyTcsRunner> runner,
			std::shared_ptr<I_SunnyTcsCraftAgency> agency,
			std::shared_ptr<I_SunnyTcsMsgSender> sender,
			std::shared_ptr<I_SunnyTcsLogger> loger);

		A_SunnyTcsOrderCenter(const A_SunnyTcsOrderCenter&) = delete;

		virtual ~A_SunnyTcsOrderCenter();

		A_SunnyTcsOrderCenter& operator=(const A_SunnyTcsOrderCenter&) = delete;


		//由工艺ID来创建订单，如果没有指定AGV,就用该工艺默认的分配算法来决定
		bool createOrder(qint32 craftId, QString& err, qint32 agvId = 0);

		//删除订单
		void cancelOrder(qint32 orderId);

		//添加新工艺
		bool addCraft(QJsonObject& jobj, QString& err);
		
		//删除原有工艺
		void removeCraft(qint32 craftId);

		//改变订单状态
		bool changeOrderStatus(std::shared_ptr<SunnyTcsCraft> ptr, E_SunnyTcsRouteStatus newStatus);

		//json
		bool fromJson(QJsonObject& jobj, QString& err);
		QJsonObject toJson();
		void toJson(QJsonObject& jobj);

	protected:
		//对收到的数据进行处理
		void msgHandle();


	protected:
		//订单中心专管，订单中心也是工艺中心
		QMap<qint32, std::shared_ptr<SunnyTcsCraft>> _crafts;//现有工艺集

		//订单，只由订单中心自己访问，订单中心线程专管
		QMutex _allOrdersLock;
		QMap<quint64, std::shared_ptr<SunnyTcsCraft>> _allOrders;//所有的订单都在这,创建订单的时候，删除订单的时候，对外发送订单信息的时候

	};

}

