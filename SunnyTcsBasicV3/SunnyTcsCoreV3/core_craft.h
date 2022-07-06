#pragma once
#include "core_subcraft.h"




//ʹ��ʮ��������Ϊ����ģ�͵ĵײ����ݽṹ
typedef SunnyTcsOrthogonalListOrientedGraph<SunnyTcsSubCraft::SubCraftId, SunnyTcsSubCraft, SunnyTcsSubCraftLinkLine> SunnyTcsCraftPrototype;






class SunnyTcsCraftModelImpl :public SunnyTcsCraftPrototype
{
public:
	typedef int32_t CraftIdType;
	typedef typename SunnyTcsTypeTraits<CraftIdType>::TransferedType CraftIdTransferedType;

	CraftIdType getId()const { return m_id; }
	void setId(CraftIdTransferedType var) { m_id = var; }
	key_type getStartSubCraftId()const { return m_startSubCraft; }
	void setStartSubCraftId(key_transfered_type k) { m_startSubCraft = k; }

private:

	CraftIdType m_id;
	key_type m_startSubCraft;
};

typedef SunnyTcsCraftModelImpl SunnyTcsCraftModel;