#pragma once
#include "core_subcraft.h"




//使用十字链表作为工序模型的底层数据结构
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