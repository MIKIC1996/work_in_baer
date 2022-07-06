#pragma once
#include "SunnyTcsLogicGeneral.hpp"

namespace basic {


	//单个条件
	class SUNNYTCSBASICV3_EXPORT SunnyTcsSingleCondition :
		public I_SunnyTcsCondition
	{
	public:
		explicit SunnyTcsSingleCondition(E_SunnyTcsMapObject_type tar)
			:I_SunnyTcsCondition(), _tar(tar), _prefix(), _suffix() {}

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

		
		//getter
		QList<SunnyTcsConditionValue>& getPrefix() {
			return _prefix;
		}

		const QList<SunnyTcsConditionValue>& getPrefix()const {
			return _prefix;
		}

		QList<SunnyTcsConditionValue>& getSuffix() {
			return _suffix;
		}

		const QList<SunnyTcsConditionValue>& getSuffix()const {
			return _suffix;
		}

		//setter
		template<typename T>
		bool setPrefixOption(qint32 opt, E_SunnyTcsComparisonOperation ope, T&& val) {
			SunnyTcsConditionValue cv;
			if (cv.setCondition(opt, ope, std::forward<T>(val))) {
				_prefix.append(cv);
				return true;
			}
			return false;
		}

		template<typename T>
		bool setSuffixOption(qint32 opt, E_SunnyTcsComparisonOperation ope, T&& val) {
			SunnyTcsConditionValue cv;
			if (cv.setCondition(opt, ope, std::forward<T>(val))) {
				_suffix.append(cv);
				return true;
			}
			return false;
		}

		// 通过 I_SunnyTcsCondition 继承
		virtual E_SunnyTcsConditionType getType()const override { return singleCondition; }

		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() override;

		virtual bool operate(I_SunnyTcsActualData& data) override;

		virtual QString toString() const override {
 			QString str = "[<";
 			str += SunnyTcsLogicInfo::get_conditionTarStr_conditionTar_map().key(_tar);
// 			str += ">";
// 			str += _prefix.toString();
// 			str += _suffix.toString();
// 			str += "]";
// 			return str;
			return QString();
		}

	protected:

		E_SunnyTcsMapObject_type _tar;//针对车还是针对主控,还是外围设备
		QList<SunnyTcsConditionValue> _prefix;//选取条件
		QList<SunnyTcsConditionValue> _suffix;//执行条件

	};

}



