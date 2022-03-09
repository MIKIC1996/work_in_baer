#pragma once


#include "SunnyTcsLogicInfo.h"



namespace basic {


	//条件接口
	class SUNNYTCSBASICV3_EXPORT I_SunnyTcsCondition {
	public:
		I_SunnyTcsCondition() {}

		virtual E_SunnyTcsConditionType getType()const = 0;
		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() = 0;//整理
		virtual bool operate(I_SunnyTcsActualData &data)const = 0;
		virtual QString toString()const = 0;

		template<typename T, typename J>
		static bool basicOperation(const T& cval, E_SunnyTcsComparisonOperation ope, const J& val) {
			switch (ope)
			{
			case EQUAL:
				return (cval == val);
			case UNEQUAL:
				return (cval != val);
			case BIGGER:
				return (cval > val);
			case SMALLER:
				return (cval < val);
			case BIGGER_OR_EQUAL:
				return (cval >= val);
			case SMALLER_OR_EQUAL:
				return (cval <= val);
			case AND_OPERATION:
				return (cval &= val);
			case OR_OPERATION:
				return (cval |= val);
			default:
				Q_ASSERT(0);
			}
			return false;
		}
	};


	class  A_SunnyTcsSingleCondition;
	class  SunnyTcsSelectDecideTarget;


	//条件值，包括这个值的选取条件 和 选取标准值
	class SUNNYTCSBASICV3_EXPORT SunnyTcsConditionValue {
	public:
		friend class A_SunnyTcsSingleCondition;
		friend class SunnyTcsSelectDecideTarget;

		SunnyTcsConditionValue() :_bit(0), _ope(EQUAL), _value() {}

		SunnyTcsConditionValue(const SunnyTcsConditionValue& rhs) :_bit(rhs._bit), _ope(rhs._ope), _value(rhs._value)
		{}

		virtual ~SunnyTcsConditionValue() {}

		SunnyTcsConditionValue& operator=(const SunnyTcsConditionValue& rhs) {
			_bit = rhs._bit;
			_ope = rhs._ope;
			_value = rhs._value;
			return *this;
		}

		bool operator==(const SunnyTcsConditionValue& rhs) const {
			return _bit == rhs._bit && _ope == rhs._ope && _value == rhs._value;
		}

		template<typename T>
		bool setCondition(int8_t conditionId, E_SunnyTcsComparisonOperation ope, T&& val) {
			//给定ID不对
			if (!SunnyTcsLogicInfo::get_conditionId_compareOpe_map().keys().contains(conditionId)) {
				return false;
			}
			//给定运算符不对
			if (!SunnyTcsLogicInfo::get_conditionId_compareOpe_map()[conditionId].contains(ope)) {
				return false;
			}
			
			E_ARG_TYPE type = SunnyTcsArgTraits<T>::argType();
			//给定参数不对
			if (SunnyTcsLogicInfo::get_conditionId_argType_map()[conditionId] != type) {
				return false;
			}
			_bit = conditionId;
			_ope = ope;
			_value = std::forward<T>(val);
			return true;
		}


		inline int8_t getConditionId()const { return _bit; }
		inline E_SunnyTcsComparisonOperation getComparisonOpe()const { return _ope; }
		inline SunnyTcsArg getArg()const { return _value; }


	protected:
		int8_t _bit = 0;//这个值针对64位中的第几位
		E_SunnyTcsComparisonOperation _ope;
		SunnyTcsArg _value;
	};





	//选取与执行的基本条件,选出逻辑运算对象的ID,这些条件可以相互叠加
	class SUNNYTCSBASICV3_EXPORT SunnyTcsSelectDecideTarget { //选取对象 以及 判断条件
	public:
		friend class A_SunnyTcsSingleCondition;//友元

		explicit SunnyTcsSelectDecideTarget(E_SunnyTcsConditionTarget tar) : _tar(tar), _targetCondition(0), _conditionValue() {}

		SunnyTcsSelectDecideTarget(const SunnyTcsSelectDecideTarget& rhs)
			:_tar(rhs._tar), _targetCondition(rhs._targetCondition), _conditionValue(rhs._conditionValue)
		{}

		virtual ~SunnyTcsSelectDecideTarget() {}

		SunnyTcsSelectDecideTarget& operator=(const SunnyTcsSelectDecideTarget& rhs) {
			_tar = rhs._tar;
			_targetCondition = rhs._targetCondition;
			_conditionValue = rhs._conditionValue;
			return *this;
		}

		bool operator==(const SunnyTcsSelectDecideTarget& rhs)const {
			return _tar == rhs._tar && _targetCondition == rhs._targetCondition && _conditionValue == rhs._conditionValue;
		}

		template<typename T>
		bool setOption(int8_t opt, E_SunnyTcsComparisonOperation ope, T&& value) {
			//条件对象 不支持的 条件选项
			if (!SunnyTcsLogicInfo::get_conditionTar_conditionId_map()[_tar].contains(opt)) {
				return false;
			}

			SunnyTcsConditionValue cval;
			if (!cval.setCondition(opt, ope,std::forward<T>(value) )) {
				return false;
			}
			uint64_t i = 1;
			_targetCondition |= (i << opt);
			_conditionValue.insert(opt, cval);
			return true;
		}

		void removeOption(int8_t opt) {
			if (!_conditionValue.keys().contains(opt)) {
				return;
			}
			uint64_t i = 1;
			_targetCondition &= (~(i << opt));
			_conditionValue.remove(opt);
		}

		QString toString()const {
			QString str = "(";
			auto iter = _conditionValue.begin();
			while (iter != _conditionValue.end()) {
				QString conditionIdStr = SunnyTcsLogicInfo::get_conditionStr_conditionId_map().key(iter->getConditionId());
				QString compareOpeStr = SunnyTcsLogicInfo::get_compareOpeStr_compareOpe_map().key(iter->getComparisonOpe());
				QString argStr = iter->getArg().toString();
				str += conditionIdStr;
				str += compareOpeStr;
				str += argStr;
				str += ",";
				++iter;
			}
			str += ")";
			return str;
		}

	protected:
		E_SunnyTcsConditionTarget _tar;
		uint64_t  _targetCondition;//选取条件集 总共由64 位 ，也就是最多可以设置64个选取条件，前32位给车 后8位给线边 后24位预留					 
		QMap<qint8, SunnyTcsConditionValue> _conditionValue; //qint8 指第几位，qint32 是值
	};

}
