#include "SunnyTcsModel.h"


namespace basic {





	void SunnyTcsModel::init_distribution()
	{//��ʼ���ֲ�
		for (auto ptr : _pts) {
			QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
			for (auto bl : bs) {
				if (!_distribution.keys().contains(bl)) {
					_distribution.insert(bl, QList<I_SunnyTcsElementData*>());
				}
				_distribution[bl].append(ptr);
			}
		}
		for (auto ptr : _paths) {
			QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
			for (auto bl : bs) {
				if (!_distribution.keys().contains(bl)) {
					_distribution.insert(bl, QList<I_SunnyTcsElementData*>());
				}
				_distribution[bl].append(ptr);
			}
		}
	}


	void SunnyTcsModel::update_distribution()
	{//���³����ֲ�
		for (auto ptr : _ves) {
			QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
			if (bs.isEmpty()) { //���Ƕ�ά����
								//����һά������ƥ�䷽��
				qDebug() << "isempty";
				continue;
			}
			else {
				if (!_distribution.keys().contains(bs.first())) {//�� ƥ������
					ptr->setAgvCurPos(SunnyTcsMapObject_tag());
					qDebug() << "no pipei";
					continue;
				}
				else { //����ƥ������
					SunnyTcsMapBlock bl = bs.first();
					QList<I_SunnyTcsElementData*>& eles = _distribution[bl];
					//ƥ���
					bool finded = false;
					for (auto eptr : eles) {
						if (eptr->getTag()._eletype == Epoint && eptr->isInRange(ptr->getAgvCurCoor())) {
							ptr->setAgvCurPos(eptr->getTag());
							finded = true;
							break;
						}
					}
					//ƥ����
					if (!finded) {
						for (auto eptr : eles) {
							if (eptr->getTag()._eletype == Epath && eptr->isInRange(ptr->getAgvCurCoor())) {
								ptr->setAgvCurPos(eptr->getTag());
								finded = true;
								break;
							}
						}
					}
					qDebug() << "no pipei2";
					//û���ҵ�ƥ��� ����
					if (!finded)ptr->setAgvCurPos(SunnyTcsMapObject_tag());
				}
			}
		}
	}

	SunnyTcsModel::SunnyTcsModel(quint64 id)
	{
	}

	bool SunnyTcsModel::judgeSingleCondition(const SunnyTcsSingleCondition & conditon)
	{
		return false;
	}

	void SunnyTcsModel::agvStats(QHash<qint32, I_SunnyTcsAgvStat*>& ref)
	{
	}

	void SunnyTcsModel::points(QHash<qint32, I_SunnyTcsVertex*>& ref)
	{
	}

	void SunnyTcsModel::paths(QHash<qint32, I_SunnyTcsEdge*>& ref)
	{
	}

	void SunnyTcsModel::uls(QHash<qint32, I_SunnyTcsUlsData*>& ref)
	{
	}

}