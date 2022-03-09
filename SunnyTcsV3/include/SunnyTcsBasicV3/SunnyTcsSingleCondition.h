#pragma once
#include "SunnyTcsLogicGeneral.hpp"

namespace basic {


	//单个条件
	class SUNNYTCSBASICV3_EXPORT SunnyTcsSingleCondition :
		public I_SunnyTcsCondition
	{
	public:
		explicit SunnyTcsSingleCondition(E_SunnyTcsConditionTarget tar)
			:I_SunnyTcsCondition(), _tar(tar), _prefix(tar), _suffix(tar) {}

		//ctor
		SunnyTcsSingleCondition(const SunnyTcsSingleCondition& rhs) :_tar(rhs._tar), _prefix(rhs._prefix), _suffix(rhs._suffix) {}


		virtual ~SunnyTcsSingleCondition() {}

		virtual SunnyTcsSingleCondition& operator=(const SunnyTcsSingleCondition& rhs) {
			_tar = rhs._tar;
			_prefix = rhs._prefix;
			_suffix = rhs._suffix;
			return *this;
		}

		virtual bool operator==(const SunnyTcsSingleCondition& rhs)const {
			return _tar == rhs._tar && _prefix == rhs._prefix && _suffix == rhs._suffix;
		}

		template<typename T>
		bool setPrefixOption(int8_t opt, E_SunnyTcsComparisonOperation ope, const T& val) {
			return _prefix.setOption(opt, ope, val);
		}

		template<typename T>
		bool setSuffixOption(int8_t opt, E_SunnyTcsComparisonOperation ope, const T& val) {
			return _suffix.setOption(opt, ope, val);
		}

		SunnyTcsSelectDecideTarget& getPrefix() {
			return _prefix;
		}

		const SunnyTcsSelectDecideTarget& getPrefix()const {
			return _prefix;
		}

		SunnyTcsSelectDecideTarget& getSuffix() {
			return _suffix;
		}

		const SunnyTcsSelectDecideTarget& getSuffix()const {
			return _suffix;
		}

		// 通过 I_SunnyTcsCondition 继承
		virtual E_SunnyTcsConditionType getType()const { return singleCondition; }

		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() override;

		virtual bool operate(I_SunnyTcsActualData& data) const {
			return data.judgeSingleCondition(*this);
		}

		virtual QString toString() const override {
			QString str = "[<";
			str += SunnyTcsLogicInfo::get_conditionTarStr_conditionTar_map().key(_tar);
			str += ">";
			str += _prefix.toString();
			str += _suffix.toString();
			str += "]";
			return str;
		}

	protected:
		E_SunnyTcsConditionTarget _tar;//针对车还是针对主控,还是外围设备
		SunnyTcsSelectDecideTarget _prefix;//选取条件
		SunnyTcsSelectDecideTarget _suffix;//执行条件
	};

}



