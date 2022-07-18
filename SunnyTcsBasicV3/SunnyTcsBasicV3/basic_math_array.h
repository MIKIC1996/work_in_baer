#pragma once


#include "basic_math_object.h"



#define TCS_ARRAY_INTERFACE_CHECK(Type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,ARIT_1,size_type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,ARIT_2,difference_type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,ARIT_3 , value_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,ARMF_1,size_type,size)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,ARMF_2,void ,resetSize,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,ARMF_3,size_type,vaildSize)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,ARMF_4,bool ,isPosVaild,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,ARMF_4_5,size_type ,firstInVaildPos)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,ARMF_5,size_type ,firstVaildPos)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,ARMF_6,size_type ,nextVaildPos,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,ARMF_7, size_type ,push_front,value_type const&)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,ARMF_8, size_type ,push_back,value_type const&)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,ARMF_9 , void ,remove,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,ARMF_10 , void ,insert,size_type,value_type const&)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,ARMF_11,value_type& , operator[],size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, ARMF_12, value_type const&, operator[], size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, ARMF_13, bool, operator==, Type const&)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, ARMF_14, bool, operator!=, Type const&)





















