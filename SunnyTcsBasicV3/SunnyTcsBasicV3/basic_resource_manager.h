#pragma once



#include "basic_defs.h"

//资源管理者 的接口标准
#define TCS_RESOURCE_MANAGER_INTERFACE_CHECK(_Type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(_Type, RMIY_1, ResourceType)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(_Type, RMIY_2,SharedResource)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(_Type, RMIY_3,UniqueResource)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(_Type,RMMF_4,SharedResource,getNextSharedResource)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(_Type,RMMF_5,UniqueResource,getNextUniqueResource)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(_Type,RMMF_6,SharedResource,getDesignatedSharedResource,ResourceType const&)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(_Type,RMMF_7,UniqueResource,getDesignatedUniqueResource,ResourceType const&)



//资源持有者的 接口标准
#define TCS_RESOURCE_KEEPER_INTERFACE_CHECK(_Type)\




template<typename Ty>
class SunnyTcsResourceManagePolicy {
public:
	typedef Ty value_type;
	static value_type getNextResource(value_type const& var) { return var + 1; }
	
};





