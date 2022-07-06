#pragma once

#include "SunnyTcsCoreV3.h"


namespace core {

	class I_SunnyTcsCraftAgency;

	//订单流转的接收者
	class I_SunnyTcsCraftRecivier
	{
	public:
		I_SunnyTcsCraftRecivier(qint8 craftId, std::shared_ptr<I_SunnyTcsCraftAgency> agency)
			:_craftNodeId(craftId), _craftAgency(agency), _craftQueue()
		{}
		I_SunnyTcsCraftRecivier(const I_SunnyTcsCraftRecivier&) = delete;
		virtual ~I_SunnyTcsCraftRecivier() {}
		I_SunnyTcsCraftRecivier& operator=(const I_SunnyTcsCraftRecivier&) = delete;

		inline qint8 getCraftNodeId()const { return _craftNodeId; }

		//各个recivier自己去定义
		virtual void insertCraft(std::shared_ptr<SunnyTcsCraft> craft) {
			_queueLock.lock();
			_craftQueue.push_back(craft);
			_queueLock.unlock();
		}

		virtual bool tryInsertCraft(std::shared_ptr<SunnyTcsCraft> craft) {
			if (_queueLock.tryLock()) {
				_craftQueue.push_back(craft);
				_queueLock.unlock();
				return true;
			}
			return false;
		}

	protected:
		const qint8 _craftNodeId;
		std::shared_ptr<I_SunnyTcsCraftAgency> _craftAgency;
		QMutex _queueLock;
		QQueue<std::shared_ptr<SunnyTcsCraft>> _craftQueue;
	};



	//内部订单通讯的中介者
	class I_SunnyTcsCraftAgency
	{
	public:
		I_SunnyTcsCraftAgency() :_reciviers() {}
		I_SunnyTcsCraftAgency(const I_SunnyTcsCraftAgency&) = delete;
		virtual ~I_SunnyTcsCraftAgency() {}
		I_SunnyTcsCraftAgency& operator=(const I_SunnyTcsCraftAgency&) = delete;

		//订单流转
		virtual bool transferCraft(std::shared_ptr<SunnyTcsCraft> craft,
			qint32 curNodeID, qint32 tarNodeId = 0, bool isTry = false) = 0;

		//注册
		virtual bool registerRecivier(qint32 id, std::shared_ptr<I_SunnyTcsCraftRecivier> recv)
		{
			if (_reciviers.keys().contains(id)) {
				return false;
			}
			_reciviers.insert(id, recv);
			return true;
		}

		//注销
		virtual void logoutRecivier(qint32 id)
		{
			if (_reciviers.keys().contains(id)) {
				_reciviers.remove(id);
				return;
			}
		}

	protected:
		QMap<qint32, std::shared_ptr<I_SunnyTcsCraftRecivier>> _reciviers;
	};






}




