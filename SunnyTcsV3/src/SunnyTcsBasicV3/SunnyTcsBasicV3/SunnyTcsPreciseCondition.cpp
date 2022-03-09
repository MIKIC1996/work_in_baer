#include "SunnyTcsPreciseCondition.h"

namespace basic {
	

		SunnyTcsPreciseCondition::SunnyTcsPreciseCondition(E_SunnyTcsLogicOperation ope) :_operation(ope), _conditions()
		{

		}

		SunnyTcsPreciseCondition::SunnyTcsPreciseCondition(E_SunnyTcsLogicOperation ope, QList<std::shared_ptr<I_SunnyTcsCondition>> cons)
			:_operation(ope),_conditions(cons)
		{

		}

		SunnyTcsPreciseCondition::~SunnyTcsPreciseCondition()
		{

		}

		std::shared_ptr<I_SunnyTcsCondition> SunnyTcsPreciseCondition::arrangement()
		{
			std::shared_ptr<I_SunnyTcsCondition> ptr(this);
			return ptr;
		}

		bool SunnyTcsPreciseCondition::operate( I_SunnyTcsActualData & data) 
		{
			bool ret = false;
			if (_operation == E_AND) { //and ȫ�� ��ȷ����ʽ
				ret = true;
				auto iter = _conditions.begin();
				while (iter != _conditions.end()) {
					Q_ASSERT(*iter);//�����ǿ�ָ��
					ret &= (*iter)->operate(data);
					if (!ret) {
						return false;
					}
					++iter;
				}
			}
			else { //or ȫ�� ��ȷ����ʽ
				ret = false;
				auto iter = _conditions.begin();
				while (iter != _conditions.end()) {
					Q_ASSERT(*iter);//�����ǿ�ָ��
					ret |= (*iter)->operate(data);
					if (ret) {
						return true;
					}
					++iter;
				}
			}
			return ret;

		}

		QString SunnyTcsPreciseCondition::toString() const
		{
			QString flag = _operation == E_AND ? "&&" : "||";
			auto iter = _conditions.begin();
			QString ret = "{";
			while (iter != _conditions.end()) {

				if (!(*iter)) { 
					Q_ASSERT(0);
				}
				ret += (*iter)->toString();

				if ((iter + 1) != _conditions.end())
					ret += flag;
				++iter;
			}
			ret += "}";
			return ret;
		}

		E_SunnyTcsConditionType SunnyTcsPreciseCondition::getType() const
		{
			return preciseExpression;
		}
	
}


