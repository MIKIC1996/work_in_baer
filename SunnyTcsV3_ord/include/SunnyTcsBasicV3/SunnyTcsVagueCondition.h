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

		void appendCondition(std::shared_ptr<I_SunnyTcsCondition> ptr) {
			_conditions.append(ptr);
		}

		void removeCondition(qint32 index) { _conditions.removeAt(index); }

		void removeAllCondition() {
			_conditions.clear();
			_operations.clear();
		}

		void appendOperation(E_SunnyTcsLogicOperation ope) {
			_operations.append(ope);
		}

		void removeOperation(qint32 index) {
			_operations.removeAt(index);
		}

		qint32 conditionCount()const {
			return _conditions.count();
		}

		qint32 operationCount()const {
			return _operations.count();
		}


		// 通过 I_SunnyTcsCondition 继承
		virtual E_SunnyTcsConditionType getType() const override;
		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() override;
		virtual bool operate(I_SunnyTcsActualData & data) const override;
		virtual QString toString() const override;

	protected:
		QList<std::shared_ptr<I_SunnyTcsCondition>> _conditions;
		QList<E_SunnyTcsLogicOperation> _operations;
	};


}


