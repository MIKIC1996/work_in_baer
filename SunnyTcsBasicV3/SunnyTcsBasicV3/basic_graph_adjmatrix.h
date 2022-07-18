#pragma once


#include "basic_graph.h"
#include "basic_graph_traits.h"



//基于邻接矩阵的有向图实现，内部采用了Variant矩阵，他对内存空间的需求是实际顶点数的平方级
//非内存扩容情况下的操作效率较高，强于十字链表
template<
	typename Key,
	typename Vertex,
	typename Edge,
	template<typename > class KeyTraitTemplate = SunnyTcsGraphKeyTrait
>
class SunnyTcsAdjMatrixOrientedGraph  {
public:
	typedef SunnyTcsAdjMatrixOrientedGraph<Key, Vertex, Edge>							Self;
	typedef KeyTraitTemplate<Key>														key_traits;
	typedef Key																			key_type;
	typedef typename key_traits::TransferedType											key_transfered_type;
	typedef Vertex																		VertexType;
	typedef Edge																		EdgeType;
	typedef SunnyTcsDynamicVariantMatrix<EdgeType>										MatrixType; //弧线矩阵
	typedef typename MatrixType::size_type												size_type;
	typedef typename MatrixType::difference_type										difference_type;

	struct VertexWarpper {
		size_type m_index; //在弧线矩阵中的索引
		VertexType m_vex;

		inline bool operator==(VertexWarpper const& var)const {
			return m_index == var.m_index && m_vex == var.m_vex;
		}

		inline bool operator!=(VertexWarpper const& var)const{
			return !this->operator==(var);
		}

	};
	typedef std::map<key_type, VertexWarpper>											VertexContainer;
	//迭代器
	typedef typename VertexContainer::iterator											iterator;
	typedef typename VertexContainer::const_iterator									const_iterator;

	static constexpr size_type defaultSize = 100;
	
	//ctor
	explicit SunnyTcsAdjMatrixOrientedGraph(size_type defSize = defaultSize):m_vertexs(),m_edges(defSize,defSize){}

	//copy ctor
	SunnyTcsAdjMatrixOrientedGraph(SunnyTcsAdjMatrixOrientedGraph const& var) 
		:m_vertexs(var.m_vertexs),m_edges(var.m_edges)
	{}

	//move ctor
	SunnyTcsAdjMatrixOrientedGraph(SunnyTcsAdjMatrixOrientedGraph&& var) 
		:m_vertexs(std::move(var.m_vertexs)),m_edges(std::move(var.m_edges))
	{}

	//dector
	virtual ~SunnyTcsAdjMatrixOrientedGraph() {}


	//assign
	SunnyTcsAdjMatrixOrientedGraph& operator=(SunnyTcsAdjMatrixOrientedGraph const& var) {
		m_vertexs = var.m_vertexs;
		m_edges = var.m_edges;
		return *this;
	}

	SunnyTcsAdjMatrixOrientedGraph& operator=(SunnyTcsAdjMatrixOrientedGraph&& var) {
		m_vertexs = std::move(var.m_vertexs);
		m_edges = std::move(var.m_edges);
		return *this;
	}

	//operator==
	bool operator==(SunnyTcsAdjMatrixOrientedGraph const& var)const {
		return m_vertexs == var.m_vertexs && m_edges == var.m_edges;
	}

	bool operator!=(SunnyTcsAdjMatrixOrientedGraph const& var)const {
		return !this->operator==(var);
	}

	//vex
	inline size_type vexSize()const { 
		return m_vertexs.size(); 
	}

	inline bool containsVex(key_transfered_type key)const {
		return m_vertexs.end() != m_vertexs.find(key);
	}


	key_type firstOutAdjVexOf(key_transfered_type key)const {
		assert(this->containsVex(key));
		size_type index = m_vertexs.at(key).m_index;
		size_type outIndex = m_edges.firstVaildPosInRow(index);
		if (-1 == outIndex)return key_traits::getInvaildValue();
		auto iter = std::find_if(m_vertexs.begin(), m_vertexs.end(),
			[outIndex](auto& ele)->bool {return ele.second.m_index == outIndex; }
		);
		return m_vertexs.end() == iter ? key_traits::getInvaildValue() : iter->first;
	}


	key_type nextOutAdjVexOf(key_transfered_type key, key_transfered_type cur)const {
		assert(this->containsVex(key));
		assert(this->containsVex(cur));
		size_type index = m_vertexs.at(key).m_index;
		size_type curIndex = m_vertexs.at(cur).m_index;
		size_type outIndex = m_edges.nextVaildPosInRow(index,curIndex);
		if (-1 == outIndex)return key_traits::getInvaildValue();
		auto iter = std::find_if(m_vertexs.begin(), m_vertexs.end(),
			[outIndex](auto& ele)->bool {return ele.second.m_index == outIndex; }
		);
		return m_vertexs.end() == iter ? key_traits::getInvaildValue() : iter->first;
	}


	key_type firstInAdjVexOf(key_transfered_type key)const {
		assert(this->containsVex(key));
		size_type index = m_vertexs.at(key).m_index;
		size_type outIndex = m_edges.firstVaildPosInColumn(index);
		if (-1 == outIndex)return key_traits::getInvaildValue();
		auto iter = std::find_if(m_vertexs.begin(), m_vertexs.end(),
			[outIndex](auto& ele)->bool {return ele.second.m_index == outIndex; }
		);
		return m_vertexs.end() == iter ? key_traits::getInvaildValue() : iter->first;
	}


	key_type nextInAdjVexOf(key_transfered_type key, key_transfered_type cur)const {
		assert(this->containsVex(key));
		assert(this->containsVex(cur));
		size_type index = m_vertexs.at(key).m_index;
		size_type curIndex = m_vertexs.at(cur).m_index;
		size_type outIndex = m_edges.nextVaildPosInColumn(index, curIndex);
		if (-1 == outIndex)return key_traits::getInvaildValue();
		auto iter = std::find_if(m_vertexs.begin(), m_vertexs.end(),
			[outIndex](auto& ele)->bool {return ele.second.m_index == outIndex; }
		);
		return m_vertexs.end() == iter ? key_traits::getInvaildValue() : iter->first;
	}

	
	size_type vexOutDegree(key_transfered_type key)const {
		assert(this->containsVex(key));
		size_type index = m_vertexs.at(key).m_index;
		m_edges.vaildSizeInRow(index);
	}

	size_type vexInDegree(key_transfered_type key)const {
		assert(this->containsVex(key));
		size_type index = m_vertexs.at(key).m_index;
		m_edges.vaildSizeInColumn(index);
	}

	VertexType& locateVex(key_transfered_type key) {
		return m_vertexs.at(key).m_vex;
	}

	VertexType const& locateVex(key_transfered_type key) const{
		return m_vertexs.at(key).m_vex;
	}
	
	void insertVex(key_transfered_type key, VertexType const& vex) {

		m_vertexs.insert(std::pair<key_type, VertexWarpper>(key, VertexWarpper{m_edges.firstInVaildRow(),vex }));
		m_edges.activeInVaildRow(m_edges.firstInVaildRow()); //激活矩阵中的第一个无效行
	}

	void deleteVex(key_transfered_type key) {
		if (!this->containsVex(key))return;
		size_type index = m_vertexs.at(key).m_index;
		m_edges.removeRow(index); //删除所有的出度连接，并且将该行改回为无效行，回收index
		m_edges.removeColumn(index); //删除所有的入度连接
	}

	std::vector<key_type> keys()const {
		std::vector<key_type> ret;
		auto iter = m_vertexs.begin();
		while (iter != m_vertexs.end()) {
			ret.push_back(iter->first);
			++iter;
		}
		return ret;
	}

	//arc
	size_type arcSize()const {
		return m_edges.vaildSize();
	}

	bool containsArc(key_transfered_type from, key_transfered_type to)const {
		if(!this->containsVex(from) || !this->containsVex(to))return false;
		size_type fromIndex = m_vertexs.at(from).m_index;
		size_type toIndex = m_vertexs.at(to).m_index;
		return m_edges.isPosVaild(fromIndex, toIndex);
	}


	EdgeType& locateArc(key_transfered_type from, key_transfered_type to) {
		assert(this->containsVex(from) && this->containsVex(to));
		size_type fromIndex = m_vertexs.at(from).m_index;
		size_type toIndex = m_vertexs.at(to).m_index;
		assert(this->containsArc(from, to));
		return m_edges[fromIndex][toIndex];
	}


	EdgeType const& locateArc(key_transfered_type from, key_transfered_type to)const {
		assert(this->containsVex(from) && this->containsVex(to));
		size_type fromIndex = m_vertexs.at(from).m_index;
		size_type toIndex = m_vertexs.at(to).m_index;
		assert(this->containsArc(fromIndex, to));
		return m_edges[fromIndex][toIndex];
	}

	void insertArc(key_transfered_type from, key_transfered_type to, EdgeType const& var) {
		if (!this->containsVex(from) || !this->containsVex(to))return;;
		size_type fromIndex = m_vertexs.at(from).m_index;
		size_type toIndex = m_vertexs.at(to).m_index;
		m_edges.insert( fromIndex, toIndex, var);
	}

	void deleteArc(key_transfered_type from, key_transfered_type to) {
		if (!this->containsVex(from) || !this->containsVex(to))return;;
		size_type fromIndex = m_vertexs.at(from).m_index;
		size_type toIndex = m_vertexs.at(to).m_index;
		m_edges.remove(fromIndex, toIndex);
	}
	
	//以下为选择性接口
	//兼容标准库
	iterator begin() { return m_vertexs.begin(); }
	const_iterator cbegin()const { return m_vertexs.cbegin(); }
	iterator end() { return m_vertexs.end(); }
	const_iterator cend()const { return m_vertexs.cend(); }

	//转权值矩阵
	template<typename Valty,typename Functor>
	SunnyTcsDynamicVariantMatrix<Valty> toWeightMatrix(Functor&& func)const{
		return m_edges.toOtherMatrix<Valty>(std::forward<Functor>(func));
	}

#ifdef STRICT_INTERFACE_CHECK
	TCS_ORIENTED_GRAPH_INTERFACECHECK(Self)
#endif // STRICT_INTERFACE_CHECK

private:
	VertexContainer m_vertexs;
	MatrixType m_edges;
};