#pragma once


#include "SunnyTcsTypeArg.h"
#include "SunnyTcsMapGeneral.hpp"




namespace basic {

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
		SunnyTcsArg,
		SunnyTcsArg
	> SunnyTcsParamsSet;

	//指令参数集的最大参数数量
	static constexpr qint32 actionParamsSetMax = std::tuple_size<SunnyTcsParamsSet>::value;

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
			std::get<_Index>(t) = SunnyTcsArg(0);
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
	class SUNNYTCSBASICV3_EXPORT A_SunnyTcsCommand {
	public:
		static constexpr qint32 action_params_count = actionParamsSetMax;
		static QMap<E_ARG_TYPE, QString> supportArgTyps;
		static bool mapInitFunc();
		static bool mapInit;
	}; 


	//指令
	class SUNNYTCSBASICV3_EXPORT SunnyTcsAction:public A_SunnyTcsCommand
	{
	public:
		static QMap<QString, SunnyTcsAction> actionSample;//所支持的指令样本
		static bool sampleInitFunc();
		static bool sampleInit;
		

		//default ctor
		SunnyTcsAction();
		//ctor 必须指定参数类型，指令ID,指令码
		explicit SunnyTcsAction(qint16 commandId, QString commandCode, QString description="");
		//copy ctor
		SunnyTcsAction(const SunnyTcsAction&) = default;
		//detor
		virtual ~SunnyTcsAction() {}
		//operator =
		SunnyTcsAction& operator=(const SunnyTcsAction&) = default;
		//operator ==
		bool operator==(const SunnyTcsAction& rhs) const;

		//getter
		inline qint16 getCommandId()const { return _commandId; }
		inline QString getCommandCode()const { return _commandCode; }
		inline E_SunnyTcsActionStatus getCommandStatus()const { return _status; }
		inline E_SunnyTcsActionType getCommandType()const { return _actionType; }
		inline QString getDescription()const { return _description; }

		inline bool isInOrder()const { return _isInOrder; }
		inline bool isUpdated()const { return _isUpdated; }
		template<int index>
		SunnyTcsArg getParam_meta()const { return std::get<index>(_params);}
		SunnyTcsArg getParam(int ct) {
			Q_ASSERT(ct >= 0 && ct <= SunnyTcsAction::action_params_count);
			return getParam_aux<SunnyTcsParamsSet>(ct, _params);
		}

		//setter
		void setOrder(bool is) { _isInOrder = is; }
		void setUpdated(bool is) { _isUpdated = is; }
		void setCommandCode(QString code) { _commandCode = code; }
		void setCommandId(qint16 cid) { _commandId = cid; }
		void updateStatus(E_SunnyTcsActionStatus status) {
			_status = status;
			_isUpdated = true;
		}
		void setStatus(E_SunnyTcsActionStatus status) { _status = status; }
		//设置参数
		template<int index,typename T>
		void setParams_meta(const T& value) {
			SunnyTcsArg vtoa(value);
			std::get<index>(_params) = value;
		}

		template<typename _Ty>
		void setParams(int ct, const _Ty val) {
			setParam_aux(ct, _params, val);
		}
		
		//json
		virtual QJsonObject toJson()const;
		virtual bool fromJson(QJsonObject& jobj, QString& err);
		//获取描述信息
		QString toString()const;

	protected:
		//根据tuple的实现原理，写的运行中获取参数的函数
		template<typename _tupleTy>
		SunnyTcsArg getParam_aux(int ct, _tupleTy& tup)
		{
			using base = typename _tupleTy::_Mybase;
			return ct == 0 ? std::get<0>(tup) : getParam_aux(ct - 1, (base&)(tup));
		}


		SunnyTcsArg getParam_aux(int ct, std::tuple<SunnyTcsArg>& tup) {
			Q_ASSERT(ct == 0);
			return std::get<0>(tup);
		}

		template<typename _tupleTy,typename _Ty>
		void setParam_aux(int ct, _tupleTy& tup, const _Ty& val) {
			using base = typename _tupleTy::_Mybase;
			ct == 0 ? std::get<0>(tup)=val : setParam_aux(ct - 1, (base&)tup ,val);
			
		}

		template< typename _Ty>
		void setParam_aux(int ct, std::tuple<SunnyTcsArg>& tup, const _Ty& val) {
			Q_ASSERT(ct == 0);
			std::get<0>(tup) = val;
		}

		//序列化的相关函数
		template<int index = 0>
		void getParamsJsonArray(QJsonArray& jobj) const{
			jobj.append(std::get<index>(_params).toJson());
			getParamsJsonArray<index + 1>(jobj);
		}

		template<>
		void getParamsJsonArray<action_params_count - 1>(QJsonArray& jobj) const{
			jobj.append(std::get<action_params_count - 1>(_params).toJson());
		}

		template<int index =0>
		bool setParamsByJsonArray(QJsonArray& jarr ,QString& err) {
			if (!SunnyTcsTypeArgBuilder::buildTypeArgFromJson(std::get<index>(_params), jarr[index].toObject(),err))return false;
			return setParamsByJsonArray<index + 1>(jarr,err);
		}

		template<>
		bool setParamsByJsonArray<action_params_count - 1>(QJsonArray& jarr, QString& err) {
			return SunnyTcsTypeArgBuilder::buildTypeArgFromJson(std::get<action_params_count - 1>(_params), jarr[action_params_count - 1].toObject(), err);
		}

	protected:
		qint16 _commandId; //指令ID
		QString _commandCode;//指令码
		QString _description;//指令描述
		SunnyTcsParamsSet _params;//参数集
		bool _isInOrder;//是否为时序指令
		bool _isUpdated;//是否更新了，更新了就发出去
		E_SunnyTcsActionType _actionType;//指令类型
		E_SunnyTcsActionStatus _status;//指令状态
	};


}

	
	
		
	
	
	





