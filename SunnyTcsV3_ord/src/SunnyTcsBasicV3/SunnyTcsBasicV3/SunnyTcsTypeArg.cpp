#include "SunnyTcsTypeArg.h"


namespace basic {

	/*
	* 这里列举了 typeArg所支持的类型，界面也是从这里读取
	*
	*/
	QMap<E_ARG_TYPE, QString> SunnyTcsTypeArg::supportArgTyps;


	/*
	* 用来初始化supportArgTyps的变量，用来触发mapInitFunc函数
	*
	*/
	bool SunnyTcsTypeArg::mapInit = mapInitFunc();


	/*
	* 用来初始化supportArgTyps的函数
	*
	*/
	bool SunnyTcsTypeArg::mapInitFunc()
	{
		supportArgTyps.insert(ARG_INT8, QSTRING_GBK(SunnyTcsArgTraits<int8_tcs>::decp));
		supportArgTyps.insert(ARG_INT16, QSTRING_GBK(SunnyTcsArgTraits<int16_tcs>::decp));
		supportArgTyps.insert(ARG_INT32, QSTRING_GBK(SunnyTcsArgTraits<int32_tcs>::decp));
		supportArgTyps.insert(ARG_INT64, QSTRING_GBK(SunnyTcsArgTraits<int64_tcs>::decp));
		supportArgTyps.insert(ARG_UINT8, QSTRING_GBK(SunnyTcsArgTraits<uint8_tcs>::decp));
		supportArgTyps.insert(ARG_UINT16, QSTRING_GBK(SunnyTcsArgTraits<uint16_tcs>::decp));
		supportArgTyps.insert(ARG_UINT32, QSTRING_GBK(SunnyTcsArgTraits<uint32_tcs>::decp));
		supportArgTyps.insert(ARG_UINT64, QSTRING_GBK(SunnyTcsArgTraits<uint64_tcs>::decp));
		supportArgTyps.insert(ARG_QSTRING, QSTRING_GBK(SunnyTcsArgTraits<string_tcs>::decp));
		return true; 
	}



	SunnyTcsTypeArg::SunnyTcsTypeArg()
		:_type(ARG_UNDEFINED), _data(), _copyConstructInMenFunc(nullptr), _releaseStorageFunc(nullptr),
		_constructInMemFunc(nullptr), _bytesFromMemFunc(nullptr),_toDataStringFunc(nullptr)
	{
		std::memset(_data.access(), 0, callable_storage_size);
	}



	SunnyTcsTypeArg::SunnyTcsTypeArg(const SunnyTcsTypeArg & rhs)
	{
		_type = rhs._type;
		_copyConstructInMenFunc = rhs._copyConstructInMenFunc;
		_releaseStorageFunc = rhs._releaseStorageFunc;
		_constructInMemFunc = rhs._constructInMemFunc;
		_bytesFromMemFunc = rhs._bytesFromMemFunc;
		_toDataStringFunc = rhs._toDataStringFunc;
		if (_copyConstructInMenFunc) {
			_copyConstructInMenFunc(rhs._data, _data);
		}
		else {
			std::memset(_data.access(), 0, callable_storage_size);
		}
	}



	SunnyTcsTypeArg::SunnyTcsTypeArg(SunnyTcsTypeArg && rhs)
	{
		//数据交换
		_type = rhs._type;
		_copyConstructInMenFunc = rhs._copyConstructInMenFunc;
		_releaseStorageFunc = rhs._releaseStorageFunc;
		_constructInMemFunc = rhs._constructInMemFunc;
		_bytesFromMemFunc = rhs._bytesFromMemFunc;
		_toDataStringFunc = rhs._toDataStringFunc;
		std::memcpy(_data.access(), rhs._data.access(), callable_storage_size);
		rhs._type = ARG_UNDEFINED;
		rhs._copyConstructInMenFunc = nullptr;
		rhs._releaseStorageFunc = nullptr;
		rhs._constructInMemFunc = nullptr;
		rhs._bytesFromMemFunc = nullptr;
		rhs._toDataStringFunc = nullptr;
		std::memset(rhs._data.access(), 0, callable_storage_size);
	}



	SunnyTcsTypeArg & SunnyTcsTypeArg::operator=(const SunnyTcsTypeArg & rhs)
	{
		if (_releaseStorageFunc)_releaseStorageFunc(_data);//先释放一下数据
		_type = rhs._type;
		_copyConstructInMenFunc = rhs._copyConstructInMenFunc;
		_releaseStorageFunc = rhs._releaseStorageFunc;
		_constructInMemFunc = rhs._constructInMemFunc;
		_bytesFromMemFunc = rhs._bytesFromMemFunc;
		_toDataStringFunc = rhs._toDataStringFunc;
		if (_copyConstructInMenFunc) {
			_copyConstructInMenFunc(rhs._data, _data);
		}
		else { // rhs也是一个空的
			std::memset(_data.access(), 0, callable_storage_size);
		}
		return *this;
	}



	SunnyTcsTypeArg & SunnyTcsTypeArg::operator=(SunnyTcsTypeArg && rhs)
	{
		//备份一份
		E_ARG_TYPE tempType = _type;
		void(*copyConstructInMenFuncTemp)(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst) = _copyConstructInMenFunc;
		void(*releaseStorageFuncTemp)(SunnyTcsAnyData& data) = _releaseStorageFunc;
		bool(*constructInMemFuncTemp)(const SunnyTcsAnyData& data, void* pos, std::size_t size) = _constructInMemFunc;
		void(*bytesFromMemFuncTemp)(QByteArray& ret, const SunnyTcsAnyData& data) = _bytesFromMemFunc;
		QString(*toDataStringTemp)(const SunnyTcsAnyData& data) = _toDataStringFunc;
		char dataTemp[callable_storage_size];
		std::memcpy(dataTemp, _data.access(), callable_storage_size);
		//数据交换
		_type = rhs._type;
		_copyConstructInMenFunc = rhs._copyConstructInMenFunc;
		_releaseStorageFunc = rhs._releaseStorageFunc;
		_constructInMemFunc = rhs._constructInMemFunc;
		_bytesFromMemFunc = rhs._bytesFromMemFunc;
		_toDataStringFunc = rhs._toDataStringFunc;
		std::memcpy(_data.access(), rhs._data.access(), callable_storage_size);
		rhs._type = tempType;
		rhs._copyConstructInMenFunc = copyConstructInMenFuncTemp;
		rhs._releaseStorageFunc = releaseStorageFuncTemp;
		rhs._constructInMemFunc = constructInMemFuncTemp;
		rhs._bytesFromMemFunc = bytesFromMemFuncTemp;
		rhs._toDataStringFunc = toDataStringTemp;
		std::memcpy(rhs._data.access(), dataTemp, callable_storage_size);
		return *this;
	}



	bool SunnyTcsTypeArg::operator==(const SunnyTcsTypeArg & arg) const
	{
		return _type == arg._type && 0 == std::memcmp(_data.access(), arg.access(), callable_storage_size);
	}



	bool SunnyTcsTypeArg::constructInMem(void * pos, std::size_t size)
	{
		Q_ASSERT(_constructInMemFunc);
		return _constructInMemFunc(_data, pos, size);
	}



	QByteArray SunnyTcsTypeArg::bytesFromMem() const
	{
		Q_ASSERT(_bytesFromMemFunc);
		QByteArray dataRet;
		_bytesFromMemFunc(dataRet, _data);//数据体
		QByteArray && ret = SunnyTcsBytesTransformer::toBytes<qint32>(static_cast<qint32>(_type));
		qint32 headSize = argHeadSize + dataRet.count();
		ret += SunnyTcsBytesTransformer::toBytes<qint32>(headSize);//数据头
		ret += dataRet;
		return ret;
	}


	QJsonObject SunnyTcsTypeArg::toJson() const
	{
		QJsonObject jobj;
		jobj[JSON_ARG_TYPE] = (qint32)_type;
		QByteArray dataBytes;
		_bytesFromMemFunc(dataBytes, _data);
		QJsonArray dataArray;
		for (char c : dataBytes) {
			dataArray.append((qint32)c);
		}
		jobj[JSON_ARG_PARAM] = dataArray;
		jobj[JSON_ARG_SIZE] = argHeadSize + dataBytes.count();
		return jobj;
	}

	QString SunnyTcsTypeArg::toDataString() const
	{
		Q_ASSERT(_toDataStringFunc);
		return _toDataStringFunc(_data);
	}



	QString SunnyTcsTypeArg::toString() const
	{
		QString str;
		QString* ptr;
		char storeSpace[callable_storage_size] = {};
		switch (_type)
		{
		case basic::ARG_UNDEFINED:
			str += "undefine ： NAN";
			break;
		case basic::ARG_CHAR:
			_constructInMemFunc(_data, storeSpace, 1);
			str += QString("char : %1").arg( *storeSpace );
			break;
		case basic::ARG_BOOL:
			_constructInMemFunc(_data, storeSpace, 1);
			str += QString("bool : %1").arg(*storeSpace ? "true" : "false" );
			break;
		case basic::ARG_MIXED:
			str += QString("mixed : NAN");
			break;
		case basic::ARG_INT8:
			_constructInMemFunc(_data, storeSpace, 1);
			str += QString("int8 : %1").arg( QString::number( *((qint8*)(storeSpace) )) );
			break;
		case basic::ARG_INT16:
			_constructInMemFunc(_data, storeSpace, 2);
			str += QString("int16 : %1").arg(QString::number(*((qint16*)(storeSpace))));
			break;
		case basic::ARG_INT32:
			_constructInMemFunc(_data, storeSpace, 4);
			str += QString("int32 : %1").arg(QString::number(*((qint32*)(storeSpace))));
			break;
		case basic::ARG_INT64:
			_constructInMemFunc(_data, storeSpace, 8);
			str += QString("int64 : %1").arg(QString::number(*((qint64*)(storeSpace))));
			break;
		case basic::ARG_UINT8:
			_constructInMemFunc(_data, storeSpace, 1);
			str += QString("uint8 : %1").arg(QString::number(*((quint8*)(storeSpace))));
			break;
		case basic::ARG_UINT16:
			_constructInMemFunc(_data, storeSpace, 2);
			str += QString("uint16 : %1").arg(QString::number(*((quint16*)(storeSpace))));
			break;
		case basic::ARG_UINT32:
			_constructInMemFunc(_data, storeSpace, 4);
			str += QString("uint32 : %1").arg(QString::number(*((quint32*)(storeSpace))));
			break;
		case basic::ARG_UINT64:
			_constructInMemFunc(_data, storeSpace,8);
			str += QString("uint64 : %1").arg(QString::number(*((quint64*)(storeSpace))));
			break;
		case basic::ARG_QBYTEARRAY:
			str += "bytesArray ： NAN";
			break;
		case basic::ARG_QSTRING:
			_constructInMemFunc(_data, storeSpace, 8);
			ptr = (QString*)storeSpace;
			str += QString("string : %1").arg(*ptr);
			break;
		default:
			str += "unknow ： NAN";
			break;
		}
		return str;
	}



	bool SunnyTcsTypeArgBuilder::buildTypeArgFromJson(SunnyTcsTypeArg & arg, const QJsonObject & jobj, QString& err)
	{
		if (!jobj.contains(JSON_ARG_TYPE) ||
			!jobj.contains(JSON_ARG_SIZE) ||
			!jobj.contains(JSON_ARG_PARAM)
			) {
			err = QSTRING_GBK("指令的JSON标签缺失");
			return false;
		}
		E_ARG_TYPE argType = static_cast<E_ARG_TYPE>(jobj[JSON_ARG_TYPE].toInt());
		QJsonArray dataArray = jobj[JSON_ARG_PARAM].toArray();
		QByteArray dataBytes;
		for (auto v : dataArray) {
			dataBytes.append((char)(v.toInt()));
		}
		qint32 argSize = jobj[JSON_ARG_SIZE].toInt();
		if (argSize != 8 + dataBytes.count())return false; //json中记录的大小不对
		return buildTypeArgByTypeAndDataBytes(arg, argType, dataBytes,err);
	}



	bool SunnyTcsTypeArgBuilder::buildTypeArgByBytes(SunnyTcsTypeArg & arg, const QByteArray & bytes)
	{
		if (bytes.count() <= SunnyTcsTypeArg::argHeadSize)return false; // 数据只有数据头大小
		qint32 argTypeVal = SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(0, sizeof(qint32)));//计算数据类型
		E_ARG_TYPE argType = static_cast<E_ARG_TYPE>(argTypeVal);
		qint32 size = SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(4, sizeof(qint32)));//比对数据头记录的数据大小和实际大小
		if (size != bytes.count())return false;
		return buildTypeArgByTypeAndDataBytes(arg, argType, bytes.mid(8, bytes.count() - 8),QString());
	}



	bool SunnyTcsTypeArgBuilder::buildTypeArgByTypeAndDataBytes(SunnyTcsTypeArg & arg, E_ARG_TYPE argType, const QByteArray & bytes, QString& err)
	{
		if (argType == ARG_INT32) {
			using argType = int32_tcs;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_INT8)
		{
			using argType = int8_t;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_INT16)
		{
			using argType = int16_t;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_INT64)
		{
			using argType = int64_t;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT32) {
			using argType = uint32_tcs;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT8)
		{
			using argType = uint8_t;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT16)
		{
			using argType = uint16_t;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT64)
		{
			using argType = uint64_t;
			if (bytes.count() != sizeof(argType)) return false;
			argType val = SunnyTcsBytesTransformer::fromByte<argType>(bytes);
			arg = val;
			return true;
		}
		else if (argType == ARG_QSTRING) {
			QString&& str = QString::fromLocal8Bit(bytes);
			arg = str;
			return true;
		}
		err = QSTRING_GBK("不支持的参数解析类型");
		return false;
	}



	bool SunnyTcsTypeArgBuilder::buildTypeArgByString(SunnyTcsTypeArg & arg, E_ARG_TYPE argType, QString & str)
	{
		if (argType == ARG_INT32) {
			using argType = int32_tcs;
			bool ok = true;
			argType val = str.toInt(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_INT8)
		{
			using argType = int8_t;
			bool ok = true;
			argType val = str.toInt(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_INT16)
		{
			using argType = int16_t;
			bool ok = true;
			argType val = str.toInt(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_INT64)
		{
			using argType = int64_t;
			bool ok = true;
			argType val = str.toLongLong(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT32) {
			using argType = uint32_tcs;
			bool ok = true;
			argType val = str.toUInt(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT8)
		{
			using argType = uint8_t;
			bool ok = true;
			argType val = str.toUInt(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT16)
		{
			using argType = uint16_t;
			bool ok = true;
			argType val = str.toUInt(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_UINT64)
		{
			using argType = uint64_t;
			bool ok = true;
			argType val = str.toULongLong(&ok);
			if (!ok)return false;
			arg = val;
			return true;
		}
		else if (argType == ARG_QSTRING) {
			arg = str;
			return true;
		}
		return false;
	}

}


