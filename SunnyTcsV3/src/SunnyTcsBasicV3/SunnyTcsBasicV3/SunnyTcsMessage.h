#pragma once

#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsLibGeneral.hpp"
#include "SunnyTcsTypeArg.h"

#define MSG_HEAD_MARK "MSGH"
#define MSG_HEAD_LENGTH 34

namespace basic {

	/*��Ϣͷ��
		��Ϣ��־ "MSGH"       4 4 4 8 1 1 2 2  4  = 30
		��Ϣcounter qint32
		��Ϣid qint32
		����ʱ��ʱ��� quint64
		��ò��ظ������·��� quint64
		�Ƿ�㲥 bool
		�Ƿ���Ҫ�ظ������ظ����ط� bool
		Ŀ�ĵ� qint16 Ŀ�����ID,���� Ⱥ��ID
		��Դ   qint16	
		��Ϣ�ܳ��� qint32 ������Ϣͷ
	��
	��Ϣ�����塾
		����1 arg
		����2 arg
		����3 arg
	��
	*/

	class SunnyTcsMessage;

	//��Ϣ�࣬��Ϊ����֮�����ת����
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
			return _msgCounter == rhs._msgCounter && _msgId == rhs._msgId; //ͬ���� ͬcounter ��Ϊͬһ��Ϣ
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
		//���ݴ��  4 4  4 4 8 1 1 2 2 4  =v34
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
	
		//�ط�ʱ��,�������ʱ��Ͳ����ط�
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
// 				return false; //ʹ����δע�������
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




