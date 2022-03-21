#pragma once


#include "SunnyTcsGeneralArg.hpp"
#include "SunnyTcsLibGeneral.hpp"
#include "SunnyTcsMapGeneral.hpp"


#define JSON_ACTION_COMMAND_ID "commandId"
#define JSON_ACTION_COMMAND_CODE "commandCode"
#define JSON_ACTION_IS_INORDER "isInOrder"
#define JSON_ACTION_IS_UPDATED "isUpdated"
#define JSON_ACTION_TYPE "actionType"
#define JSON_ACTION_STATUS "actionStatus"
#define JSON_ACTION_ARGS "actionArgs"
#define JSON_ACTION_DISTRIBUTION "actionDistribution"

#define ACTION_PARAMSSET_MAX basic::actionParamsSetMax 

namespace   basic {

	//默认最大参数集为7个，如果以后有需求的话可以随时扩充
	//为什么不使用QVector<SunnyTcsArg>？ 因为这样感觉太臃肿了，参数的数量基本是固定的，不可能会太多，没必要配一个Vector,不够时自行扩充即可
	//现阶段7个参数已经可以满足需求,以后增加了可以扩充
	typedef std::tuple<
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg
	> SunnyTcsParamsSet;

	static constexpr quint16 actionParamsSetMax = std::tuple_size<SunnyTcsParamsSet>::value;

	
	//动作类型
	enum E_SunnyTcsActionType {
		Eagv = 0,
		Enotify = 1,
		Ewait = 2
	};


	//指令状态
	enum E_SunnyTcsActionStatus {
		Eunsend = 0,
		Ealready_send = 5,
		Erecived = 1,
		Edoing = 2,
		Efinished = 3,
		Eunexecutable = 4
	};


	template<typename _Tuple, int _Index>
	struct TupleInit_int32 {
		static void application(_Tuple& t ) { //自定义规则 ，函数名application
			static_assert( _Index >= 0 && _Index < std::tuple_size<_Tuple>::value ,"out of Tuple range");
			std::get<_Index>(t) = SunnyTcsArg( ARG_INT32 );
		}
	};


	//赋值元函数外覆器
	struct TupleInit_int32_f {
		template<typename _Tuple, int _Index>
		struct apply : TupleInit_int32<_Tuple,_Index> {}; //自定义规则，元函数名 apply
	};



	template<typename _Tuple,typename _Ty,int _index = std::tuple_size<_Tuple>::value -1>
	struct initTuple {
		static void init(_Tuple& t, _Ty val) {
			static_assert(_index >= 0 && _index < std::tuple_size<_Tuple>::value, " out of tuple range.");
			initTuple<_Tuple,_Ty,_index -1 > :: init(t, val);
			std::get<_index>(t) = val;
		}
	};


	template<typename _Tuple, typename _Ty>
	struct initTuple<_Tuple,_Ty,0> {
		static void init(_Tuple& t, _Ty val) {
			std::get<0>(t) = val;
		}
	};



	//指令接口,考虑到了泛用性，接口的设计很难确定
	class A_SunnyTcsCommand {

	}; 

	//指令
	class SUNNYTCSBASICV3_EXPORT SunnyTcsAction:public A_SunnyTcsCommand
	{
	public:
		//default
		SunnyTcsAction()
			:A_SunnyTcsCommand(), _commandId(0), _commandCode(),
			_params(), _paramType(ARG_INT32), _isInOrder(true),
			_isUpdated(false),_actionType(Eagv),_status(Eunsend)
		{
			Tuple_for_each<TupleInit_int32_f, SunnyTcsParamsSet>::for_each(_params);
		}

		//ctor
		explicit SunnyTcsAction(E_ARG_TYPE type) 
			:A_SunnyTcsCommand(), _commandId(0), _commandCode(),
			_params(), _paramType(type), _isInOrder(true),
			_isUpdated(false), _actionType(Eagv), _status(Eunsend)
		{
			initTuple<SunnyTcsParamsSet, SunnyTcsArg>::init(_params, SunnyTcsArg(type));
		}
		//copy ctor
		SunnyTcsAction(const SunnyTcsAction&) = default;
		//operator =
		SunnyTcsAction& operator=(const SunnyTcsAction&) = default;
		//detor
		virtual ~SunnyTcsAction() {}
		//operator ==
		bool operator==(const SunnyTcsAction& rhs) const {
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

		//getter
		inline bool isInOrder()const { return _isInOrder; }
		inline bool isUpdated()const { return _isUpdated; }
		template<int index>
		SunnyTcsArg getParam_meta()const {
			return std::get<index>(_params);
		}

		//setter
		template<int index,typename T>
		bool setParams_meta(const T& value) {
			SunnyTcsArg vtoa(value);
			setParams_meta<index>(vtoa);
		}

		template<int index>
		bool setParams_meta(const SunnyTcsArg& param) {
			if (param.getType() != _paramType) {
				return false;
			}
			std::get<index>(_params) = param;
			return true;
		}
		void setOrder(bool is) { _isInOrder = is; }
		void setUpdated(bool is) { _isUpdated = is; }


		//json
		virtual QJsonObject toJson()const {
			QJsonObject jobj;
			return jobj;
		}

		virtual bool fromJson(QJsonObject& jobj, QString& err) {
			return true;
		}


		void updateStatus(E_SunnyTcsActionStatus status) {
			_status = status;
			_isUpdated = true;
		}

		void setStatus(E_SunnyTcsActionStatus status) {
			_status = status;
		}

		QString toString()const;

	protected:
		qint16 _commandId; //指令ID
		QString _commandCode;//指令码
		E_ARG_TYPE _paramType; //参数类型
		SunnyTcsParamsSet _params;//参数集
		bool _isInOrder;//是否为时序指令
		bool _isUpdated;//是否更新了，更新了就发出去
		E_SunnyTcsActionType _actionType;//指令类型
		E_SunnyTcsActionStatus _status;//指令状态
	};


}

	
	
		
	
	
	





