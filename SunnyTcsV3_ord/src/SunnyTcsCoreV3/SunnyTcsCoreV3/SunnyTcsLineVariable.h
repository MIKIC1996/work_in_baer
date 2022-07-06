#pragma once
#include "SunnyTcsCoreV3.h"

namespace core {


	class SUNNYTCSCOREV3_EXPORT SunnyTcsLineVariable
	{
	public:
		SunnyTcsLineVariable() {
			_name = "NA";
			_id = 0;
			_ioType = 0;
			_value.append('\0');
			_peerAddress = "127.0.0.1";
			_peerPort = 0;
			_dataType = 1;
			_isUpdated = false;
		}

		SunnyTcsLineVariable(const SunnyTcsLineVariable& rhs)
		{
			_name = rhs._name;
			_id = rhs._id;
			_connectionID = rhs._connectionID;
			_value = rhs._value;
			_ioType = rhs._ioType;
			_peerAddress = rhs._peerAddress;
			_peerPort = rhs._peerPort;
			_dataType = rhs._dataType;
			_isUpdated = false;
		}

		bool operator ==(const SunnyTcsLineVariable& rhs)
		{
			return rhs._id == _id;
		}

		//json
		void writeToJson(QJsonObject& json);
		void readFromJson(const QJsonObject& json);

		qint16 id()const { return _id; }
		quint64 connectionID()const { return _connectionID; }

		void setBit(qint16 bit, bool value)
		{
			Q_ASSERT(bit >= 0 && bit < 8);
			qint8 temp = _value[0];
			if (value)
				temp |= qRound(qPow(2, bit));
			else
				temp &= (~qRound(qPow(2, bit)));
			_value[0] = temp;
			_isUpdated = true;
		}

		bool isBitOn(qint16 bit)const;


		QByteArray valueBytes()const { return _value; }

		QString name()const { return _name; }
		QString deviceAddress()const { return _peerAddress; }
		bool isOutPutSignal()const { return _ioType == 1; }
		bool isInPutSignal()const { return _ioType == 0; }
		
		qint16 dataType()const { return _dataType; }

	private:
		QString _name;
		qint16 _id;
		quint64 _connectionID;
		qint16 _ioType; //输入输出类型：0 输入； 1输出
		qint16 _dataType; //变量的数据类型：0 - string; 1 - char; 2 - short; 3 - int32; 4 - int64
		QString _peerAddress;
		qint32 _peerPort;
		QByteArray _value;
		bool _isUpdated; //变量值是否已更新

						 /*++++++++++++++++++++++++++++++++++++++++
						 *function:
						 * 将整型数转换为字节数组
						 *params:
						 *return:
						 *version:
						 *
						 +++++++++++++++++++++++++++++++++++++++++*/
	};




	//主控，是默认的外部设备
	class SunnyTcsCtrlMachine {
	public:


	protected:
		QHash<qint32, SunnyTcsLineVariable> _lineVars;
	};


}



