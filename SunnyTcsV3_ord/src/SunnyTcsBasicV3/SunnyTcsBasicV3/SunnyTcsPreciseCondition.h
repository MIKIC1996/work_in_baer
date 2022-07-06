#pragma once
#include "SunnyTcsLogicGeneral.hpp"
#include "SunnyTcsSingleCondition.h"


namespace basic {


	//精确条件集
	class SUNNYTCSBASICV3_EXPORT SunnyTcsPreciseCondition :
		public I_SunnyTcsCondition
	{
	public:
		SunnyTcsPreciseCondition(E_SunnyTcsLogicOperation ope);
		SunnyTcsPreciseCondition(E_SunnyTcsLogicOperation ope, QList<std::shared_ptr<I_SunnyTcsCondition>> cons);
		virtual ~SunnyTcsPreciseCondition();


		E_SunnyTcsLogicOperation getOperation()const { return _operation; }
		void setOperation(E_SunnyTcsLogicOperation ope) { _operation = ope; }
		void append(std::shared_ptr<I_SunnyTcsCondition> co) { _conditions.append(co); }
		void clear() { _conditions.clear(); }

		// 通过 I_SunnyTcsCondition 继承
		virtual E_SunnyTcsConditionType getType() const override;
		virtual std::shared_ptr<I_SunnyTcsCondition> arrangement() override;
		virtual bool operate(I_SunnyTcsActualData & data)  override;
		virtual QString toString() const override;

	protected:
		E_SunnyTcsLogicOperation _operation;
		QList<std::shared_ptr<I_SunnyTcsCondition>> _conditions;

	};

}


