#pragma once


#include "SunnyTcsLogicInfo.h"



namespace basic {


	//条件接口
	class SUNNYTCSBASICV3_EXPORT I_SunnyTcsCondition {
	public:
		I_SunnyTcsCondition() {}

		virtual E_SunnyTcsConditionType getType()const = 0;
		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() = 0;//整理
		virtual bool operate(I_SunnyTcsActualData &data) = 0;
		virtual QString toString()const = 0;

	};


	//条件值，包括这个值的选取条件 和 选取标准值
	class SUNNYTCSBASICV3_EXPORT SunnyTcsConditionValue {
	public:
		typedef bool (*check_func_ptr)(E_SunnyTcsMapObject_type, E_SunnyTcsComparisonOperation, E_ARG_TYPE);
		typedef bool (*getTarget_func_ptr)(E_SunnyTcsMapObject_type, E_SunnyTcsComparisonOperation, SunnyTcsArg&, I_SunnyTcsActualData &, QVector<I_SunnyTcsElementData*>&);
		typedef bool (*operate_func_ptr)(QVector<I_SunnyTcsElementData*>&, E_SunnyTcsComparisonOperation, SunnyTcsArg&, I_SunnyTcsActualData &);

		//ctor
		explicit SunnyTcsConditionValue(E_SunnyTcsMapObject_type targetType)
			:_targetType(targetType),_conditionId(0), _ope(EQUAL), _value(),_checkFuncPtr(nullptr),_getTargetFuncPtr(nullptr),_operateFuncPtr(nullptr) {
		}
		//copy ctor
		SunnyTcsConditionValue(const SunnyTcsConditionValue& rhs) 
			:_targetType(rhs._targetType),_conditionId(rhs._conditionId), _ope(rhs._ope), _value(rhs._value),
			_checkFuncPtr(rhs._checkFuncPtr), _getTargetFuncPtr(rhs._getTargetFuncPtr), _operateFuncPtr(rhs._operateFuncPtr)
		{}
		//dector
		virtual ~SunnyTcsConditionValue() {}
		//assginment
		SunnyTcsConditionValue& operator=(const SunnyTcsConditionValue& rhs) {
			_targetType = rhs._targetType;
			_conditionId = rhs._conditionId;
			_ope = rhs._ope;
			_value = rhs._value;
			_checkFuncPtr = rhs._checkFuncPtr;
			_getTargetFuncPtr = rhs._getTargetFuncPtr;
			_operateFuncPtr = rhs._operateFuncPtr;
			return *this;
		}

		bool operator==(const SunnyTcsConditionValue& rhs) {
			return _targetType == rhs._targetType && _ope == rhs._ope && _conditionId == rhs._conditionId && _value == rhs._value;
		}

		//getter
		inline E_SunnyTcsMapObject_type getTargetType()const { return _targetType; }
		inline qint32 getConditionId()const { return _conditionId; }
		inline E_SunnyTcsComparisonOperation getComparisonOpe()const { return _ope; }
		inline SunnyTcsArg getArg()const { return _value; }

		//setter
		template<typename T>
		bool setCondition(qint32 conditionId, E_SunnyTcsComparisonOperation ope, T&& val)
		{
			//保存原来的函数指针的值
			check_func_ptr temp1 = _checkFuncPtr;
			getTarget_func_ptr temp2 = _getTargetFuncPtr;
			operate_func_ptr temp3 = _operateFuncPtr;
			//绑定函数指针
			bindDealFuncByConditionId(conditionId);
			//测试是否满足条件
			if (_checkFuncPtr&&_checkFuncPtr(_targetType, _ope, _value.getType());) {
				_conditionId = conditionId;
				_ope = ope;
				_value = std::forward<T>(val);
				return true;
			}
			_checkFuncPtr = temp1;
			_getTargetFuncPtr = temp2;
			_operateFuncPtr = temp3;
			return false;
		}

		//子条件获取对象
		bool getTargetFunc(I_SunnyTcsActualData& data, QVector<I_SunnyTcsElementData*>& vec) {
			Q_ASSERT(_getTargetFuncPtr);
			return _getTargetFuncPtr(_targetType, _ope, _value, data, vec);
		}

		//子条件判断
		bool operateFunc(I_SunnyTcsActualData& data, QVector<I_SunnyTcsElementData*>& vec) {
			Q_ASSERT(_operateFuncPtr);
			return _operateFuncPtr(vec, _ope, _value, data);
		}

	private:
		void bindDealFuncByConditionId(qint32 conditionId);

	protected:
		check_func_ptr _checkFuncPtr;
		getTarget_func_ptr _getTargetFuncPtr;
		operate_func_ptr _operateFuncPtr;
		E_SunnyTcsMapObject_type _targetType;
		qint32 _conditionId;
		E_SunnyTcsComparisonOperation _ope;
		SunnyTcsArg _value;
	};




	//选取与执行的基本条件,选出逻辑运算对象的ID,这些条件可以相互叠加
	// 	class SUNNYTCSBASICV3_EXPORT SunnyTcsSelectDecideTarget { //选取对象 以及 判断条件
	// 	public:
	// 		friend class A_SunnyTcsSingleCondition;//友元
	// 
	// 		explicit SunnyTcsSelectDecideTarget(E_SunnyTcsConditionTarget tar) : _tar(tar), _targetCondition(0), _conditionValue() {}
	// 
	// 		SunnyTcsSelectDecideTarget(const SunnyTcsSelectDecideTarget& rhs)
	// 			:_tar(rhs._tar), _targetCondition(rhs._targetCondition), _conditionValue(rhs._conditionValue)
	// 		{}
	// 
	// 		virtual ~SunnyTcsSelectDecideTarget() {}
	// 
	// 		SunnyTcsSelectDecideTarget& operator=(const SunnyTcsSelectDecideTarget& rhs) {
	// 			_tar = rhs._tar;
	// 			_targetCondition = rhs._targetCondition;
	// 			_conditionValue = rhs._conditionValue;
	// 			return *this;
	// 		}
	// 
	// 		bool operator==(const SunnyTcsSelectDecideTarget& rhs)const {
	// 			return _tar == rhs._tar && _targetCondition == rhs._targetCondition && _conditionValue == rhs._conditionValue;
	// 		}
	// 
	// 		template<typename T>
	// 		bool setOption(int8_t opt, E_SunnyTcsComparisonOperation ope, T&& value) {
	// 			//条件对象 不支持的 条件选项
	// 			if (!SunnyTcsLogicInfo::get_conditionTar_conditionId_map()[_tar].contains(opt)) {
	// 				return false;
	// 			}
	// 
	// 			SunnyTcsConditionValue cval;
	// 			if (!cval.setCondition(opt, ope,std::forward<T>(value) )) {
	// 				return false;
	// 			}
	// 			uint64_t i = 1;
	// 			_targetCondition |= (i << opt);
	// 			_conditionValue.insert(opt, cval);
	// 			return true;
	// 		}
	// 
	// 		void removeOption(int8_t opt) {
	// 			if (!_conditionValue.keys().contains(opt)) {
	// 				return;
	// 			}
	// 			uint64_t i = 1;
	// 			_targetCondition &= (~(i << opt));
	// 			_conditionValue.remove(opt);
	// 		}
	// 
	// 		QString toString()const {
	// 			QString str = "(";
	// 			auto iter = _conditionValue.begin();
	// 			while (iter != _conditionValue.end()) {
	// 				QString conditionIdStr = SunnyTcsLogicInfo::get_conditionStr_conditionId_map().key(iter->getConditionId());
	// 				QString compareOpeStr = SunnyTcsLogicInfo::get_compareOpeStr_compareOpe_map().key(iter->getComparisonOpe());
	// 				QString argStr = iter->getArg().toString();
	// 				str += conditionIdStr;
	// 				str += compareOpeStr;
	// 				str += argStr;
	// 				str += ",";
	// 				++iter;
	// 			}
	// 			str += ")";
	// 			return str;
	// 		}
	// 
	// 	protected:
	// 		E_SunnyTcsConditionTarget _tar;
	// 		uint64_t  _targetCondition;//选取条件集 总共由64 位 ，也就是最多可以设置64个选取条件，前32位给车 后8位给线边 后24位预留					 
	// 		QMap<qint8, SunnyTcsConditionValue> _conditionValue; //qint8 指第几位，qint32 是值
	// 	};

}
