#pragma once

#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsLibGeneral.hpp"
#include "SunnyTcsTypeArg.h"

#define MSG_HEAD_MARK "MSGH"
#define MSG_HEAD_LENGTH 34

namespace basic {

	/*消息头【
		消息标志 "MSGH"       4 4 4 8 1 1 2 2  4  = 30
		消息counter qint32
		消息id qint32
		发送时间时间戳 quint64
		多久不回复就重新发送 quint64
		是否广播 bool
		是否需要回复，不回复会重发 bool
		目的地 qint16 目标服务ID,或者 群组ID
		来源   qint16	
		消息总长度 qint32 包括消息头
	】
	消息数据体【
		参数1 arg
		参数2 arg
		参数3 arg
	】
	*/

	class SunnyTcsMessage;

	//消息类，作为服务之间的中转对象
	class SUNNYTCSBASICV3_EXPORT SunnyTcsMessageHeader
	{
	public:
		friend class SunnyTcsMessage;

		SunnyTcsMessageHeader();

		SunnyTcsMessageHeader(qint32 msgId, qint32 msgCounter,
			qint16 targetId = 0, qint16 sourceId = 0, 
			bool broadcast = false, bool reply = false,quint64 resendTime = 0);

		SunnyTcsMessageHeader(const SunnyTcsMessageHeader& rhs);

		virtual ~SunnyTcsMessageHeader() {}

		SunnyTcsMessageHeader& operator=(const SunnyTcsMessageHeader& rhs);

		bool operator==(const SunnyTcsMessageHeader& rhs) {
			return _msgCounter == rhs._msgCounter && _msgId == rhs._msgId; //同类型 同counter 即为同一消息
		}

		//getter
		inline qint32 getMsgCounter()const { return _msgCounter; }
		inline qint32 getMsgId()const { return _msgId; }
		inline quint64 getSendTime()const { return _sendTime; }
		inline bool isBroadcast()const { return _isBroadcast; }
		inline bool isNeedReply()const { return _isNeedReply; }
		inline qint16 getTargetId()const { return _targetId; }
		inline qint16 getSourceId()const { return _sourceId; }
		inline qint32 getMsgBodyLen()const { return _msgBodyLength; }

		inline quint64 getResendWaitTime()const { return _resendWaitTime; }
		inline qint32 getHeaderLen()const { return _headLen; }
		inline QString getMsgMark()const { return _msgMark; }

		//setter
		void setMsgCounter(qint32 counter) { _msgCounter = counter; }
		void setMsgId(qint32 id) { _msgId = id; }
		void setSeedTime(quint64 time) { _sendTime = time; }
		void setIsBroadcast(bool is) { _isBroadcast = is; }
		void setIsNeedReply(bool is) { _isNeedReply = is; }
		void setTargetId(qint16 id) { _targetId = id; }
		void setSourceId(qint16 id) { _sourceId = id; }
		void setMsgBodyLen(qint32 len) { _msgBodyLength = len; }
		void setResendWaitTime(quint64 time) { _resendWaitTime = time; }
		
		//normal
		bool isOutTime() { return QDateTime::currentMSecsSinceEpoch() - _sendTime > _resendWaitTime; }
		void updateTime() { _sendTime = QDateTime::currentMSecsSinceEpoch(); }

		QByteArray toBytes()const;
		bool parseFromBytes(const QByteArray& bytes);

		QString toString()const;

	protected:
		//数据打包  4 4  4 4 8 1 1 2 2 4  =v34
		const QString _msgMark;
		const qint32 _headLen;
		qint32 _msgCounter;
		qint32 _msgId;
		quint64 _sendTime;
		bool _isBroadcast;
		bool _isNeedReply;
		qint16 _targetId;
		qint16 _sourceId;
		qint32 _msgBodyLength;
	
		//重发时间,超过这个时间就不再重发
		quint64 _resendWaitTime;

	};


	//msg body
	typedef QList<SunnyTcsArg> SunnyTcsMessageBody;


	// msg
	class SUNNYTCSBASICV3_EXPORT SunnyTcsMessage {
	protected:
		static QMutex bufferLock;
		static QQueue<SunnyTcsMessageHeader*> headerBuffer;
		static QQueue<SunnyTcsMessageBody*> bodyBuffer;

	public:
		SunnyTcsMessage();

		SunnyTcsMessage(qint32 msgId, qint32 msgCounter,
			qint16 targetId = 0, qint16 sourceId = 0,
			bool broadcast = false, bool reply = false, quint64 resendTime = 0);
		

		SunnyTcsMessage(const SunnyTcsMessage& rhs);

		SunnyTcsMessage(SunnyTcsMessage&& rhs)noexcept;

		virtual ~SunnyTcsMessage() 
		{}

		SunnyTcsMessage& operator=(const SunnyTcsMessage& rhs);

		SunnyTcsMessage& operator=(SunnyTcsMessage&& rhs);

		bool operator==(const SunnyTcsMessage& msg);


		//getter
		inline qint32 getMsgCounter()const { return _header->_msgCounter; }
		inline qint32 getMsgId()const { return  _header->_msgId; }
		inline quint64 getSendTime()const { return  _header->_sendTime; }
		inline bool isBroadcast()const { return  _header->_isBroadcast; }
		inline bool isNeedReply()const { return  _header->_isNeedReply; }
		inline qint16 getTargetId()const { return  _header->_targetId; }
		inline qint16 getSourceId()const { return  _header->_sourceId; }
		inline qint32 getMsgBodyLen()const { return  _header->_msgBodyLength; }

		inline quint64 getResendWaitTime()const { return  _header->_resendWaitTime; }
		inline qint32 getHeaderLen()const { return  _header->_headLen; }
		inline QString getMsgMark()const { return  _header->_msgMark; }

		//setter
		void setMsgCounter(qint32 counter) { _header->_msgCounter = counter; }
		void setMsgId(qint32 id) { _header->_msgId = id; }
		void setSeedTime(quint64 time) { _header->_sendTime = time; }
		void setIsBroadcast(bool is) { _header->_isBroadcast = is; }
		void setIsNeedReply(bool is) { _header->_isNeedReply = is; }
		void setTargetId(qint16 id) { _header->_targetId = id; }
		void setSourceId(qint16 id) { _header->_sourceId = id; }
		void setMsgBodyLen(qint32 len) { _header->_msgBodyLength = len; }
		void setResendWaitTime(quint64 time) { _header->_resendWaitTime = time; }

		//normal
		bool isOutTime() { return (QDateTime::currentMSecsSinceEpoch() - _header->_sendTime > _header->_resendWaitTime); }
		void updateTime() { _header->_sendTime = QDateTime::currentMSecsSinceEpoch(); }


		template<typename T>
		bool appendArg(T&& arg) {
// 			Q_ASSERT(_header&&_body);
// 			SunnyTcsArg ag(std::forward<T>(arg));
// 			if (ag.getType() == ARG_UNDEFINED) {
// 				Q_ASSERT(0);
// 				return false; //使用了未注册的类型
// 			}
// 			_body->append(std::move(ag));
// 			_header->_msgBodyLength += ag.getSize();
			return true;
		}

		
		qint32 parseFromBytes(const QByteArray& bytes,bool& ok);
		QByteArray toBytes()const ;
		QString toString()const;

	protected:
		std::shared_ptr<SunnyTcsMessageHeader> _header;
		std::shared_ptr<SunnyTcsMessageBody> _body;
	};


}




