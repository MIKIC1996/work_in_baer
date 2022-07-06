#include "SunnyTcsAction.h"

namespace basic {


	/*
	* 这里列举了 指令所支持的参数类型，界面也是从这里读取
	*
	*/
	QMap<E_ARG_TYPE, QString> A_SunnyTcsCommand::supportArgTyps;


	/*
	* 用来初始化supportArgTyps的变量，用来触发mapInitFunc函数
	*
	*/
	bool A_SunnyTcsCommand::mapInit = mapInitFunc();


	/*
	* 用来初始化supportArgTyps的函数
	*
	*/
	bool A_SunnyTcsCommand::mapInitFunc()
	{
		supportArgTyps.insert(ARG_INT8, QSTRING_GBK(SunnyTcsArgTraits<int8_tcs>::decp));
		supportArgTyps.insert(ARG_INT16, QSTRING_GBK(SunnyTcsArgTraits<int16_tcs>::decp));
		supportArgTyps.insert(ARG_INT32, QSTRING_GBK(SunnyTcsArgTraits<int32_tcs>::decp));
		supportArgTyps.insert(ARG_INT64, QSTRING_GBK(SunnyTcsArgTraits<int64_tcs>::decp));
		supportArgTyps.insert(ARG_UINT8, QSTRING_GBK(SunnyTcsArgTraits<uint8_tcs>::decp));
		supportArgTyps.insert(ARG_UINT16, QSTRING_GBK(SunnyTcsArgTraits<uint16_tcs>::decp));
		supportArgTyps.insert(ARG_UINT32, QSTRING_GBK(SunnyTcsArgTraits<uint32_tcs>::decp));
		supportArgTyps.insert(ARG_UINT64, QSTRING_GBK(SunnyTcsArgTraits<uint64_tcs>::decp));
		return true;
	}

	/*
	* 这里列举了 所有的指令样本
	*
	*/
	QMap<QString, SunnyTcsAction> SunnyTcsAction::actionSample;


	/*
	* 将样本map初始化
	*
	*/
	bool SunnyTcsAction::sampleInit = sampleInitFunc();


	/*
	* 用来触发样本初始化的标志
	*
	*/
	bool SunnyTcsAction::sampleInitFunc()
	{
		
		actionSample.insert("GP", SunnyTcsAction(0, "GP", QSTRING_GBK("目标位移动(GP)")));
		actionSample.insert("SP", SunnyTcsAction(0, "SP", QSTRING_GBK("区间限速(SP)")));
		actionSample.insert("GD", SunnyTcsAction(0, "GD", QSTRING_GBK("选向(GD)")));
		actionSample.insert("CF", SunnyTcsAction(0, "CF", QSTRING_GBK("切换扫描区(CF)")));
		actionSample.insert("HL", SunnyTcsAction(0, "HL", QSTRING_GBK("举升(HL)")));
		actionSample.insert("BL", SunnyTcsAction(0, "BL", QSTRING_GBK("转向灯(BL)")));
		return true;
	}



	SunnyTcsAction::SunnyTcsAction()
		:A_SunnyTcsCommand(), _commandId(0), _commandCode(),_description(""),
		_params(), _isInOrder(true), _isUpdated(false),
		_actionType(Eagv), _status(Eunsend)
	{
		initTuple<SunnyTcsParamsSet, qint32>::init(_params, 0);
	}

	SunnyTcsAction::SunnyTcsAction(qint16 commandId, QString commandCode,QString description)
		:A_SunnyTcsCommand(), _commandId(commandId), _commandCode(commandCode),_description(description),
		_params(), _isInOrder(true),
		_isUpdated(false), _actionType(Eagv), _status(Eunsend)
	{
		initTuple<SunnyTcsParamsSet, qint32>::init(_params, 0);
	}

	bool SunnyTcsAction::operator==(const SunnyTcsAction & rhs) const
	{
		bool ok = true;
		do {
			ok &= (_isInOrder == rhs._isInOrder);
			if (!ok)break;
			ok &= (_actionType == rhs._actionType);
			if (!ok)break;
			ok &= (_commandId == rhs._commandId);
			if (!ok)break;
			ok &= (_commandCode == rhs._commandCode);
			if (!ok)break;
			ok &= (_params == rhs._params);
			if (!ok)break;
		} while (0);
		return ok;
	}




	QJsonObject SunnyTcsAction::toJson() const
	{
		QJsonObject jobj;
		jobj[JSON_ACTION_COMMAND_CODE] = _commandCode;
		QJsonArray paramArray;
		getParamsJsonArray<0>(paramArray);
		jobj[JSON_ACTION_PARAMS] = paramArray;
		return jobj;
	}

	bool SunnyTcsAction::fromJson(QJsonObject & jobj, QString & err)
	{
		if (!jobj.contains(JSON_ACTION_COMMAND_CODE) ||
			!jobj.contains(JSON_ACTION_PARAMS)
			) {
			err = QSTRING_GBK("指令的JSON标签缺失");
			return false;
		}
		_commandCode = jobj[JSON_ACTION_COMMAND_CODE].toString();
		QJsonArray jarr = jobj[JSON_ACTION_PARAMS].toArray();
		if (jarr.count() != action_params_count) {
			err = QSTRING_GBK("指令数不足");
			return false;
		}
		return setParamsByJsonArray<0>(jarr ,err);
	}

	QString SunnyTcsAction::toString() const
	{
		QString str;
		str += _commandCode;
		str += "   ";
		str += std::get<0>(_params).toString();
		str += "   ";
		str += std::get<1>(_params).toString();
		str += "   ";
		str += std::get<2>(_params).toString();
		str += "   ";
		str += std::get<3>(_params).toString();
		str += "   ";
		str += std::get<4>(_params).toString();
		str += "   ";
		str += std::get<5>(_params).toString();
		str += "   ";
		str += std::get<6>(_params).toString();

		return str;
	}

}

