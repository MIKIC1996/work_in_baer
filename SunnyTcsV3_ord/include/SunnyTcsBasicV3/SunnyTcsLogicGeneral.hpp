#pragma once


#include "SunnyTcsLogicInfo.h"



namespace basic {


	//�����ӿ�
	class SUNNYTCSBASICV3_EXPORT I_SunnyTcsCondition {
	public:
		I_SunnyTcsCondition() {}

		virtual E_SunnyTcsConditionType getType()const = 0;
		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() = 0;//����
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


	//����ֵ���������ֵ��ѡȡ���� �� ѡȡ��׼ֵ
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
			//����ID����
			if (!SunnyTcsLogicInfo::get_conditionId_compareOpe_map().keys().contains(conditionId)) {
				return false;
			}
			//�������������
			if (!SunnyTcsLogicInfo::get_conditionId_compareOpe_map()[conditionId].contains(ope)) {
				return false;
			}
			
			E_ARG_TYPE type = SunnyTcsArgTraits<T>::argType();
			//������������
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
		int8_t _bit = 0;//���ֵ���64λ�еĵڼ�λ
		E_SunnyTcsComparisonOperation _ope;
		SunnyTcsArg _value;
	};





	//ѡȡ��ִ�еĻ�������,ѡ���߼���������ID,��Щ���������໥����
	class SUNNYTCSBASICV3_EXPORT SunnyTcsSelectDecideTarget { //ѡȡ���� �Լ� �ж�����
	public:
		friend class A_SunnyTcsSingleCondition;//��Ԫ

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
			//�������� ��֧�ֵ� ����ѡ��
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
		uint64_t  _targetCondition;//ѡȡ������ �ܹ���64 λ ��Ҳ��������������64��ѡȡ������ǰ32λ���� ��8λ���߱� ��24λԤ��					 
		QMap<qint8, SunnyTcsConditionValue> _conditionValue; //qint8 ָ�ڼ�λ��qint32 ��ֵ
	};

}
