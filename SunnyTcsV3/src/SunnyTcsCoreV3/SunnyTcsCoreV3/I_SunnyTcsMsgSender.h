#pragma once
#include "SunnyTcsCoreV3.h"
#include "I_SunnyTcsRunner.h"
#include "I_SunnyTcsLogger.h"



using namespace basic;

namespace core {

	class I_SunnyTcsMsgMember;

	//外部通讯器接口
	class I_SunnyTcsMsgSender
		:public I_SunnyTcsExecutor,
		 public I_SunnyTcsLoggerUser
	{
	public:
		I_SunnyTcsMsgSender(std::shared_ptr<I_SunnyTcsRunner> runner,std::shared_ptr<I_SunnyTcsLogger> logger)
			:I_SunnyTcsExecutor(runner),I_SunnyTcsLoggerUser(logger),_sendLock(), _sendQueue() {}
		I_SunnyTcsMsgSender(const I_SunnyTcsMsgSender&) = delete;
		virtual ~I_SunnyTcsMsgSender() {}
		I_SunnyTcsMsgSender& operator=(const I_SunnyTcsMsgSender&) = delete;


		virtual void sendMsg(const SunnyTcsMessage& msg) {
			_sendLock.lock();
			_sendQueue.push_back(msg);
			_sendLock.unlock();
		}

		virtual void sendMsg(SunnyTcsMessage&& msg) {
			_sendLock.lock();
			_sendQueue.push_back(std::forward<SunnyTcsMessage>(msg));
			_sendLock.unlock();
		}

		virtual bool registerMsgNode(qint8 id, std::shared_ptr<I_SunnyTcsMsgMember> ptr) {
			if (_msgReciviers.keys().contains(id) || !ptr) {
				return false;
			}
			_msgReciviers.insert(id, ptr);
			return true;
		}

		virtual void removeMsgNode(qint8 id) {
			if (_msgReciviers.keys().contains(id)) {
				_msgReciviers.remove(id);
			}
		}

	protected:
		QMutex _sendLock;
		QQueue<SunnyTcsMessage> _sendQueue;
		QMap<qint8, std::shared_ptr<I_SunnyTcsMsgMember>> _msgReciviers;
	};



	//内核成员的消息收发接口
	class I_SunnyTcsMsgMember {
	public:
		I_SunnyTcsMsgMember(qint8 msgNodeId, std::shared_ptr<I_SunnyTcsMsgSender> ptr)
			:_msgNodeId(msgNodeId), _msgSender(ptr), _msgRecvQueue(), _msgRecvLock() {}

		I_SunnyTcsMsgMember(const I_SunnyTcsMsgMember&) = delete;

		virtual ~I_SunnyTcsMsgMember() {}

		I_SunnyTcsMsgMember& operator=(const I_SunnyTcsMsgMember&) = delete;

		virtual void insertMsg(const SunnyTcsMessage& msg) {
			_msgRecvLock.lock();
			_msgRecvQueue.push_back(msg);
			_msgRecvLock.unlock();
		}

		virtual void insertMsg(SunnyTcsMessage&& msg) {
			_msgRecvLock.lock();
			_msgRecvQueue.push_back(std::forward<SunnyTcsMessage>(msg));
			_msgRecvLock.unlock();
		}

		inline qint8 getMsgNodeId()const {
			return _msgNodeId;
		}

	protected:
		//得到第一条数据
		virtual bool getFirstMsg(SunnyTcsMessage& data) {
			if (_msgRecvQueue.count() > 0) {
				data = std::move( _msgRecvQueue.first() );
				_msgRecvQueue.pop_front();
				return true;
			}
			return false;
		}

	protected:
		const qint8 _msgNodeId;
		std::shared_ptr<I_SunnyTcsMsgSender> _msgSender;
		QQueue<SunnyTcsMessage> _msgRecvQueue;
		QMutex _msgRecvLock;

	};


}


