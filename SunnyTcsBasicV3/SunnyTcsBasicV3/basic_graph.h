#pragma once

#include "basic_defs.h"


	/*
	* 本项目中有向图的接口规定
	* 内嵌类型检测
		typedef typename GraphType::key_type				key_type;
		typedef typename GraphType::VertexType				VertexType;
		typedef typename GraphType::EdgeType				EdgeType;
		typedef typename GraphType::size_type				size_type;
		typedef typename GraphType::difference_type			difference_type;
		typedef typename GraphType::key_transfered_type		key_transfered_type;
	
	//vex 接口检测
	//size_type vexSize()const;
	//bool containsVex(key_transfered_type)const;
	//key_type firstOutAdjVexOf(key_transfered_type);
	//key_type nextOutAdjVexOf(key_transfered_type, key_transfered_type);
	//key_type firstInAdjVexOf(key_transfered_type);
	//key_type nextInAdjVexOf(key_transfered_type, key_transfered_type);
	//size_type vexOutDegree(key_transfered_type)const;
	//size_type vexInDegree(key_transfered_type)const;
	//VertexType& locateVex(key_transfered_type);
	//VertexType const& locateVex(key_transfered_type)const;
	//void insertVex(key_transfered_type, VertexType const&);
	//void deleteVex(key_transfered_type);
	//std::vector<key_type> keys()const;
	//arc 接口检测
	//size_type arcSize()const;
	//bool containsArc(key_transfered_type, key_transfered_type)const;
	//EdgeType& locateArc(key_transfered_type, key_transfered_type);
	//EdgeType const& locateArc(key_transfered_type, key_transfered_type)const;
	//void insertArc(key_transfered_type, key_transfered_type, EdgeType const&);
	//void deleteArc(key_transfered_type, key_transfered_type);
*/


#define TCS_ORIENTED_GRAPH_INTERFACECHECK(GraphType)\
	TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(GraphType, OGIT_1, key_type)\
	TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(GraphType, OGIT_2, VertexType)\
	TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(GraphType, OGIT_3, EdgeType)\
	TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(GraphType, OGIT_4, size_type)\
	TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(GraphType, OGIT_5, difference_type)\
	TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(GraphType, OGIT_6, key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,1,size_type,vexSize)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,2,bool, containsVex,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,3,key_type, firstOutAdjVexOf, key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType, 4, key_type, nextOutAdjVexOf, key_transfered_type,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,5,key_type, firstInAdjVexOf,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,6,key_type, nextInAdjVexOf,key_transfered_type,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,7,size_type, vexOutDegree,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType, 8, size_type, vexInDegree,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(GraphType,9,VertexType& ,locateVex,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType, 18, VertexType const&, locateVex, key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(GraphType,10,void,insertVex,key_transfered_type,VertexType const&)\
	TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(GraphType,11,void,deleteVex,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,12,std::vector<key_type>,keys)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,13,size_type,arcSize)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType,14,bool,containsArc,key_transfered_type,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(GraphType,15,EdgeType& ,locateArc,key_transfered_type,key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(GraphType, 19, EdgeType const&, locateArc, key_transfered_type, key_transfered_type)\
	TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(GraphType,16,void,insertArc,key_transfered_type,key_transfered_type,EdgeType const&)\
	TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(GraphType,17,void,deleteArc,key_transfered_type,key_transfered_type)




enum GraphErrorType {
	NoError = 0
};









