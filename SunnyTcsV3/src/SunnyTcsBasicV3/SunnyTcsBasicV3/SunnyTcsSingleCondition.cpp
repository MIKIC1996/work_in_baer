#include "SunnyTcsSingleCondition.h"

namespace basic {



	std::shared_ptr<I_SunnyTcsCondition> SunnyTcsSingleCondition::arrangement()
	{
		std::shared_ptr<I_SunnyTcsCondition> ptr(this);
		return ptr;
	}


	bool SunnyTcsSingleCondition::operate(I_SunnyTcsActualData & data)
	{
		//����ɸѡ�����ʵĶ���
		QVector<I_SunnyTcsElementData*> vecRet;
		QVector<I_SunnyTcsElementData*> vec;
		QVector<I_SunnyTcsElementData*> temp;
		for (auto& iter : _prefix) {
			vec.clear();
			if (iter.getTargetFunc(data, vec)) {
				if (vecRet.isEmpty()) { //vecRet��Ϊ��
					vecRet += vec;
				}
				else { //ȡ����
					set_intersection(vec.begin(), vec.end(), vecRet.begin(), vecRet.end(), std::insert_iterator<QVector<I_SunnyTcsElementData*>>(temp, temp.begin()));
					vecRet = temp;
					temp.clear();
				}
			}
			else {
				return false;
			}
		}
		//û�з���ѡȡ�����Ķ���
		if (vecRet.isEmpty()) {
			return false;
		}
		//��ÿ���������������ж�
		for (auto& iter : _suffix) {
			if (!iter.operateFunc(data, vecRet)) {
				return false;
			}
		}
		//��������������
		return true;
	}



}
