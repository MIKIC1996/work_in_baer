#pragma once


#include "basic_graph.h"
#include "basic_resource_manager_shared.h"


template<
	typename Key,
	typename Vertex,
	typename Edge
>
class SunnyTcsAdjMatrixOrientedGraph  {
public:
	typedef Key											key_type;
	typedef Vertex										VertexType;
	typedef Edge										EdgeType;
	typedef std::ptrdiff_t								IndexType;
	typedef SunnyTcsSharedPtrResourceManager<IndexType> IndexManager;
 

	//是否将Vertex直接存储于数组中
// 	typedef typename std::conditional<std::is_trivially_copyable<VertexType>::value,
// 		std::true_type, std::false_type>::type IsVertexStoredLocal;
// 	typedef typename std::conditional<IsVertexStoredLocal::value, VertexType, VertexType*>::type VertexStoredType;


	//是否将Edge直接存储于矩阵中
	typedef typename std::conditional< std::is_trivially_copyable<EdgeType>::value,
		std::true_type, std::false_type>::type IsEdgeStoredLocal;

	typedef typename std::conditional< IsEdgeStoredLocal::value, EdgeType, EdgeType*>::type EdgeStoredType;

	struct VertexNode {
		IndexType m_index;
		VertexType m_vex;
	};

	typedef std::map<key_type, VertexNode> VertexContainer;

private:
	IndexType m_currentSize;
	VertexContainer m_vertexs;
	EdgeStoredType** m_edgeMatrix; 
	



};