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

	//��������
	class SUNNYTCSCOREV3_EXPORT A_SunnyTcsOrderCenter
		:public I_SunnyTcsExecutor, //֧����Ϊִ�����ύ����
		public I_SunnyTcsCraftRecivier,//֧���ڲ���������
		public I_SunnyTcsMsgMember,//֧���ⲿͨѶ
		public I_SunnyTcsLoggerUser //֧����־��¼
	{
	public:

		A_SunnyTcsOrderCenter(std::shared_ptr<I_SunnyTcsRunner> runner,
			std::shared_ptr<I_SunnyTcsCraftAgency> agency,
			std::shared_ptr<I_SunnyTcsMsgSender> sender,
			std::shared_ptr<I_SunnyTcsLogger> loger);

		A_SunnyTcsOrderCenter(const A_SunnyTcsOrderCenter&) = delete;

		virtual ~A_SunnyTcsOrderCenter();

		A_SunnyTcsOrderCenter& operator=(const A_SunnyTcsOrderCenter&) = delete;


		//�ɹ���ID���������������û��ָ��AGV,���øù���Ĭ�ϵķ����㷨������
		bool createOrder(qint32 craftId, QString& err, qint32 agvId = 0);

		//ɾ������
		void cancelOrder(qint32 orderId);

		//����¹���
		bool addCraft(QJsonObject& jobj, QString& err);
		
		//ɾ��ԭ�й���
		void removeCraft(qint32 craftId);

		//�ı䶩��״̬
		bool changeOrderStatus(std::shared_ptr<SunnyTcsCraft> ptr, E_SunnyTcsRouteStatus newStatus);

		//json
		bool fromJson(QJsonObject& jobj, QString& err);
		QJsonObject toJson();
		void toJson(QJsonObject& jobj);

	protected:
		//���յ������ݽ��д���
		void msgHandle();


	protected:
		//��������ר�ܣ���������Ҳ�ǹ�������
		QMap<qint32, std::shared_ptr<SunnyTcsCraft>> _crafts;//���й��ռ�

		//������ֻ�ɶ��������Լ����ʣ����������߳�ר��
		QMutex _allOrdersLock;
		QMap<quint64, std::shared_ptr<SunnyTcsCraft>> _allOrders;//���еĶ���������,����������ʱ��ɾ��������ʱ�򣬶��ⷢ�Ͷ�����Ϣ��ʱ��

	};

}

