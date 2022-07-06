#include "SunnyTcsSingleCondition.h"

namespace basic {



	std::shared_ptr<I_SunnyTcsCondition> SunnyTcsSingleCondition::arrangement()
	{
		std::shared_ptr<I_SunnyTcsCondition> ptr(this);
		return ptr;
	}


	bool SunnyTcsSingleCondition::operate(I_SunnyTcsActualData & data)
	{
		//首先筛选出合适的对象
		QVector<I_SunnyTcsElementData*> vecRet;
		QVector<I_SunnyTcsElementData*> vec;
		QVector<I_SunnyTcsElementData*> temp;
		for (auto& iter : _prefix) {
			vec.clear();
			if (iter.getTargetFunc(data, vec)) {
				if (vecRet.isEmpty()) { //vecRet还为空
					vecRet += vec;
				}
				else { //取并集
					set_intersection(vec.begin(), vec.end(), vecRet.begin(), vecRet.end(), std::insert_iterator<QVector<I_SunnyTcsElementData*>>(temp, temp.begin()));
					vecRet = temp;
					temp.clear();
				}
			}
			else {
				return false;
			}
		}
		//没有符合选取条件的对象
		if (vecRet.isEmpty()) {
			return false;
		}
		//对每个后置条件进行判断
		for (auto& iter : _suffix) {
			if (!iter.operateFunc(data, vecRet)) {
				return false;
			}
		}
		//所有条件均满足
		return true;
	}



}
