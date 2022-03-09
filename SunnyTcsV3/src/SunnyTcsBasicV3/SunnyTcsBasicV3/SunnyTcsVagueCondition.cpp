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
		Q_ASSERT(_operations.count() != _conditions.count() - 1); //���øú��������Ѿ���������һ��������
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

		QList<std::shared_ptr<I_SunnyTcsCondition>> retList;//���ռ���,Ĭ��ΪOR ����
		QList<std::shared_ptr<I_SunnyTcsCondition>> andList;//�������&&��ϵ����������

		while (opeindex < _operations.count()) {
			//������������������&&��ϵ�����������andList
			if (_operations.at(opeindex) == E_AND && !isAnd) {//������һ��&&��ϵ
				isAnd = true;
				andList.append(_conditions.at(opeindex));

				if (opeindex + 1 == _operations.count()) {//�Ѿ������һ��operation
					andList.append(_conditions.at(opeindex + 1));
					retList.append(std::make_shared<SunnyTcsPreciseCondition>(E_AND, andList));
					andList.clear();
				}
			}
			else if (_operations.at(opeindex) == E_AND&&isAnd) {//����&& ��ϵ
				andList.append(_conditions.at(opeindex));

				if (opeindex + 1 == _operations.count()) {//�Ѿ������һ��operation
					andList.append(_conditions.at(opeindex + 1));
					retList.append(std::make_shared<SunnyTcsPreciseCondition>(E_AND, andList));
					andList.clear();
				}
			}
			else if (_operations.at(opeindex) == E_OR&&isAnd) {//����&&��ϵ����
				isAnd = false;
				andList.append(_conditions.at(opeindex));
				retList.append(std::make_shared<SunnyTcsPreciseCondition>(E_AND, andList));//�����ȫ&& ���ϷŽ� �����
				andList.clear();
				if (opeindex + 1 == _operations.count()) {//�Ѿ������һ��operation
					retList.append(_conditions.at(opeindex + 1));
				}
			}
			else if (_operations.at(opeindex) == E_OR) {//�������ͨ�� or��ϵ
				retList.append(_conditions.at(opeindex));
				if (opeindex + 1 == _operations.count()) {//�Ѿ������һ��operation
					retList.append(_conditions.at(opeindex + 1));
				}
			}
			++opeindex;
		}

		if (retList.count() == 0) {
			Q_ASSERT(0);// �����ܽ������� ��retList������һ��
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


