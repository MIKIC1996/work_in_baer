#include "SunnyTcsMessage.h"

namespace basic {

	QMutex  SunnyTcsMessage::bufferLock;
	QQueue<SunnyTcsMessageHeader*> SunnyTcsMessage::headerBuffer;
	QQueue<SunnyTcsMessageBody*> SunnyTcsMessage::bodyBuffer;

	SunnyTcsMessageHeader::SunnyTcsMessageHeader()
		:_msgMark(MSG_HEAD_MARK),_headLen(MSG_HEAD_LENGTH),_msgCounter(0),
		_msgId(0),_sendTime(0),_isBroadcast(false),_isNeedReply(false),
		_targetId(0),_sourceId(0),_msgBodyLength(0)
	{
	}


	SunnyTcsMessageHeader::SunnyTcsMessageHeader(qint32 msgId, qint32 msgCounter, qint16 targetId, 
		qint16 sourceId, bool broadcast, bool reply, quint64 resendTime)
		:_msgMark(MSG_HEAD_MARK),_headLen(MSG_HEAD_LENGTH),_msgCounter(msgCounter),_msgId(msgId),
		_targetId(targetId),_sourceId(sourceId),_isBroadcast(broadcast),_isNeedReply(reply),_resendWaitTime(resendTime)
	{
	}

	SunnyTcsMessageHeader::SunnyTcsMessageHeader(const SunnyTcsMessageHeader & rhs)
		:_msgMark(MSG_HEAD_MARK), _headLen(MSG_HEAD_LENGTH), _msgCounter(rhs._msgCounter),
		_msgId(rhs._msgId), _sendTime(rhs._sendTime), _isBroadcast(rhs._isBroadcast), _isNeedReply(rhs._isNeedReply),
		_targetId(rhs._targetId), _sourceId(rhs._sourceId), _msgBodyLength(rhs._msgBodyLength)
	{
	}

	SunnyTcsMessageHeader & SunnyTcsMessageHeader::operator=(const SunnyTcsMessageHeader & rhs)
	{
		_msgCounter = rhs._msgCounter;
		_msgId = rhs._msgId;
		_sendTime = rhs._sendTime;
		_isBroadcast = rhs._isBroadcast;
		_isNeedReply = rhs._isNeedReply;
		_targetId = rhs._targetId;
		_sourceId = rhs._sourceId;
		_msgBodyLength = rhs._msgBodyLength;
		return *this;
	}

	QByteArray SunnyTcsMessageHeader::toBytes() const
	{
		QByteArray ret;
		ret += _msgMark.toLocal8Bit();
		ret += SunnyTcsBytesTransformer::toBytes(_headLen);
		ret += SunnyTcsBytesTransformer::toBytes(_msgCounter);
		ret += SunnyTcsBytesTransformer::toBytes(_msgId);
		ret += SunnyTcsBytesTransformer::toBytes(_sendTime);
		ret += SunnyTcsBytesTransformer::toBytes((qint8)_isBroadcast);
		ret += SunnyTcsBytesTransformer::toBytes((qint8)_isNeedReply);
		ret += SunnyTcsBytesTransformer::toBytes(_targetId);
		ret += SunnyTcsBytesTransformer::toBytes(_sourceId);
		ret += SunnyTcsBytesTransformer::toBytes(_msgBodyLength);
		return ret;
	}

	bool SunnyTcsMessageHeader::parseFromBytes(const QByteArray & bytes)
	{
		if (bytes.count() < MSG_HEAD_LENGTH)return false;
		if (QString::fromLocal8Bit(bytes.mid(0,4)) != MSG_HEAD_MARK ) return false;
		if (SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(4, 4)) != MSG_HEAD_LENGTH)return false;
		_msgCounter = SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(8, 4));
		_msgId = SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(12, 4));
		_sendTime = SunnyTcsBytesTransformer::fromByte<quint64>(bytes.mid(16, 8));
		_isBroadcast = static_cast<bool>(SunnyTcsBytesTransformer::fromByte<qint8>(bytes.mid(24, 1)));
		_isNeedReply = static_cast<bool>(SunnyTcsBytesTransformer::fromByte<qint8>(bytes.mid(25, 1)));
		_targetId = SunnyTcsBytesTransformer::fromByte<qint16>(bytes.mid(26, 2));
		_sourceId = SunnyTcsBytesTransformer::fromByte<qint16>(bytes.mid(28, 2));
		_msgBodyLength = SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(30, 4));
		if (_msgBodyLength < 0)return false;
		return true;
	}

	QString SunnyTcsMessageHeader::toString() const
	{
		QString str;
		str += "---------header---------\n";
		str += "mark : ";
		str += _msgMark;
		str += '\n';

		str += "msgHeadLen : ";
		str += QString::number(_headLen);
		str += '\n';

		str += "msgCounter : ";
		str += QString::number( _msgCounter);
		str += '\n';

		str += "msgId : ";
		str += QString::number(_msgId);
		str += '\n';

		str += "sendtime : ";
		str += QString::number(_sendTime);
		str += '\n';

		str += "isBroadcast : ";
		str += QString::number((qint8)_isBroadcast);
		str += '\n';

		str += "isNeedReply : ";
		str += QString::number((qint8)_isNeedReply);
		str += '\n';

		str += "targetId : ";
		str += QString::number(_targetId);
		str += '\n';

		str += "sourceId : ";
		str += QString::number(_sourceId);
		str += '\n';

		str += "bodyLength : ";
		str += QString::number(_msgBodyLength);
		str += '\n';
		return str;
	}


	SunnyTcsMessage::SunnyTcsMessage()
		:_header( std::make_shared<SunnyTcsMessageHeader>()),
		_body(std::make_shared<SunnyTcsMessageBody>())
	{

	}

	SunnyTcsMessage::SunnyTcsMessage(qint32 msgId, qint32 msgCounter, qint16 targetId,
		qint16 sourceId, bool broadcast, bool reply, quint64 resendTime)
		:_header(std::make_shared<SunnyTcsMessageHeader>( msgId,msgCounter,targetId,sourceId,broadcast,reply,resendTime )),
		_body(std::make_shared<SunnyTcsMessageBody>())
	{
	}

	SunnyTcsMessage::SunnyTcsMessage(const SunnyTcsMessage & rhs)
		: _header(std::make_shared<SunnyTcsMessageHeader>( *rhs._header)),
		_body(std::make_shared<SunnyTcsMessageBody>(*rhs._body))
	{

	}

	SunnyTcsMessage::SunnyTcsMessage(SunnyTcsMessage && rhs)noexcept
		:_header(std::make_shared<SunnyTcsMessageHeader>()),
		_body(std::make_shared<SunnyTcsMessageBody>())
	{
		std::shared_ptr<SunnyTcsMessageHeader> head_t = _header;
		std::shared_ptr<SunnyTcsMessageBody> body_t = _body;
		_header = rhs._header;
		rhs._header = head_t;
		_body = rhs._body;
		rhs._body = body_t;
	}


	SunnyTcsMessage & SunnyTcsMessage::operator=(const SunnyTcsMessage & rhs)
	{
		*_header = *rhs._header;
		*_body = *rhs._body;
		return *this;
	}


	SunnyTcsMessage & SunnyTcsMessage::operator=(SunnyTcsMessage && rhs)
	{
		std::shared_ptr<SunnyTcsMessageHeader> head_t = _header;
		std::shared_ptr<SunnyTcsMessageBody> body_t = _body;
		_header = rhs._header;
		rhs._header = head_t;
		_body = rhs._body;
		rhs._body = body_t;
		return *this;
	}


	bool SunnyTcsMessage::operator==(const SunnyTcsMessage & msg)
	{
		Q_ASSERT(_body&&_header);
		return *_header == *msg._header;
	}

	qint32 SunnyTcsMessage::parseFromBytes(const QByteArray & bytes, bool& ok)
	{
		Q_ASSERT(_body&&_header);
		ok = true;
		int counter = 0;//已经解析的字节数
		_body->clear();
		if (!_header->parseFromBytes(bytes)) {
			ok = false;
			return counter;
		}
		//截取数据体
		counter += MSG_HEAD_LENGTH;
		if (bytes.count() < (MSG_HEAD_LENGTH + _header->getMsgBodyLen())) {
			ok = false;
			return counter;
		}

		QByteArray body = bytes.mid(MSG_HEAD_LENGTH, _header->getMsgBodyLen());
		while (ok && counter < (MSG_HEAD_LENGTH+_header->getMsgBodyLen())) {
			SunnyTcsArg arg(SunnyTcsArg::fromBytes(std::move(body), ok));
			if (!ok) {
				_body->clear();
				return counter;
			}
			_body->append(std::move(arg));
			counter += arg.getSize();
		}
		return counter;
	}


	QByteArray SunnyTcsMessage::toBytes() const 
	{
		Q_ASSERT(_body&&_header);
		_header->updateTime();
		QByteArray ret = _header->toBytes();
		std::for_each(_body->begin(), _body->end(), [&ret](SunnyTcsArg& arg)->void { ret += arg.toBytes();});
		
		return ret;
	}


	QString SunnyTcsMessage::toString() const
	{
		QString str = _header->toString();
		str += "-----------body---------\n";
		std::for_each(_body->begin(), _body->end(), [&str](SunnyTcsArg& arg)->void {
			str += arg.toString();
		});
		str += "-----------end----------\n";
		return str;
	}

}