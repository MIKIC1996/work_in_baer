#pragma once
#include "SunnyTcsLogicGeneral.hpp"
#include "SunnyTcsPreciseCondition.h"

namespace basic {


	//模糊条件集
	class SUNNYTCSBASICV3_EXPORT SunnyTcsVagueCondition :
		public I_SunnyTcsCondition
	{
	public:
		SunnyTcsVagueCondition();

		SunnyTcsVagueCondition(const SunnyTcsVagueCondition& rhs);

		virtual ~SunnyTcsVagueCondition();

		SunnyTcsVagueCondition& operator=(const SunnyTcsVagueCondition& rhs) {
			_conditions = rhs._conditions;
			_operations = rhs._operations;
			return *this;
		}

		//getter
		qint32 conditionCount()const {
			return _conditions.count();
		}

		qint32 operationCount()const {
			return _operations.count();
		}

		void appendCondition(E_SunnyTcsLogicOperation logicOpe,std::shared_ptr<I_SunnyTcsCondition> ptr) {
			if (!_conditions.isEmpty())_operations.append(logicOpe);
			_conditions.append(ptr);
		}

		void removeAllCondition() {
			_conditions.clear();
			_operations.clear();
		}

		
		// 通过 I_SunnyTcsCondition 继承
		virtual E_SunnyTcsConditionType getType() const override;
		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() override;
		virtual bool operate(I_SunnyTcsActualData & data) override;
		virtual QString toString() const override;

	protected:
		QVector<std::shared_ptr<I_SunnyTcsCondition>> _conditions;
		QVector<E_SunnyTcsLogicOperation> _operations;
	};


}


