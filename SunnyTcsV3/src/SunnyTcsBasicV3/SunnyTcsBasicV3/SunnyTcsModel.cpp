#include "SunnyTcsModel.h"


namespace basic {





	void SunnyTcsModel::init_distribution()
	{//初始化分布
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
	{//更新车辆分布
		for (auto ptr : _ves) {
			QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
			if (bs.isEmpty()) { //不是二维车辆
								//调用一维车辆的匹配方法
				qDebug() << "isempty";
				continue;
			}
			else {
				if (!_distribution.keys().contains(bs.first())) {//无 匹配区块
					ptr->setAgvCurPos(SunnyTcsMapObject_tag());
					qDebug() << "no pipei";
					continue;
				}
				else { //存在匹配区块
					SunnyTcsMapBlock bl = bs.first();
					QList<I_SunnyTcsElementData*>& eles = _distribution[bl];
					//匹配点
					bool finded = false;
					for (auto eptr : eles) {
						if (eptr->getTag()._eletype == Epoint && eptr->isInRange(ptr->getAgvCurCoor())) {
							ptr->setAgvCurPos(eptr->getTag());
							finded = true;
							break;
						}
					}
					//匹配线
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
					//没有找到匹配的 点线
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