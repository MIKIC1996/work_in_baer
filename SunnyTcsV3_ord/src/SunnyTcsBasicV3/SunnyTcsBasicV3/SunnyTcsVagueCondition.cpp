#include "SunnyTcsVagueCondition.h"


namespace basic {


	SunnyTcsVagueCondition::SunnyTcsVagueCondition()
		:I_SunnyTcsCondition(), _operations(), _conditions()
	{
	}

	SunnyTcsVagueCondition::SunnyTcsVagueCondition(const SunnyTcsVagueCondition & rhs)
		: I_SunnyTcsCondition(), _operations(rhs._operations), _conditions(rhs._conditions)
	{
	}


	SunnyTcsVagueCondition::~SunnyTcsVagueCondition()
	{

	}

	E_SunnyTcsConditionType SunnyTcsVagueCondition::getType() const
	{
		return vagueExpression;
	}

	std::shared_ptr<I_SunnyTcsCondition> SunnyTcsVagueCondition::arrangement()
	{
		Q_ASSERT(_operations.count() != _conditions.count() - 1); //调用该函数必须已经存在至少一个子条件
		auto iter = _conditions.begin();
		while (iter != _conditions.end()) {
			if ((*iter)->getType() == vagueExpression) {
				std::shared_ptr<I_SunnyTcsCondition> cn = (*iter)->arrangement();
				(*iter) = cn;
			}
			++iter;
		}

		if (_operations.count() == 0) {
			return _conditions.first();
		}

		int opeindex = 0;
		bool isAnd = false;

		QList<std::shared_ptr<I_SunnyTcsCondition>> retList;//最终集合,默认为OR 集合
		QList<std::shared_ptr<I_SunnyTcsCondition>> andList;//存放连续&&关系的条件容器

		while (opeindex < _operations.count()) {
			//以下用来将具有连续&&关系的条件保存进andList
			if (_operations.at(opeindex) == E_AND && !isAnd) {//遇到第一个&&关系
				isAnd = true;
				andList.append(_conditions.at(opeindex));

				if (opeindex + 1 == _operations.count()) {//已经是最后一个operation
					andList.append(_conditions.at(opeindex + 1));
					retList.append(std::make_shared<SunnyTcsPreciseCondition>(E_AND, andList));
					andList.clear();
				}
			}
			else if (_operations.at(opeindex) == E_AND&&isAnd) {//连续&& 关系
				andList.append(_conditions.at(opeindex));

				if (opeindex + 1 == _operations.count()) {//已经是最后一个operation
					andList.append(_conditions.at(opeindex + 1));
					retList.append(std::make_shared<SunnyTcsPreciseCondition>(E_AND, andList));
					andList.clear();
				}
			}
			else if (_operations.at(opeindex) == E_OR&&isAnd) {//连续&&关系结束
				isAnd = false;
				andList.append(_conditions.at(opeindex));
				retList.append(std::make_shared<SunnyTcsPreciseCondition>(E_AND, andList));//把这个全&& 集合放进 结果集
				andList.clear();
				if (opeindex + 1 == _operations.count()) {//已经是最后一个operation
					retList.append(_conditions.at(opeindex + 1));
				}
			}
			else if (_operations.at(opeindex) == E_OR) {//如果是普通的 or关系
				retList.append(_conditions.at(opeindex));
				if (opeindex + 1 == _operations.count()) {//已经是最后一个operation
					retList.append(_conditions.at(opeindex + 1));
				}
			}
			++opeindex;
		}

		if (retList.count() == 0) {
			Q_ASSERT(0);// 不可能进入这里 ，retList至少有一对
		}

		if (retList.count() == 1) {
			return retList.first();
		}

		return std::make_shared<SunnyTcsPreciseCondition>(E_OR, retList);
	}


	bool SunnyTcsVagueCondition::operate(I_SunnyTcsActualData & data) 
	{
		return false;
	}

	QString SunnyTcsVagueCondition::toString() const
	{
		QString str = "{";
		Q_ASSERT(_conditions.count() == _operations.count() + 1);
		int i = 0;
		for (i = 0; i < _operations.count(); ++i) {
			str += _conditions[i]->toString();
			str += SunnyTcsLogicInfo::get_logicOpeStr_logicOpe_map().key(_operations[i]);
		}
		str += _conditions[i]->toString();
		str += "}";
		return str;
	}



}


