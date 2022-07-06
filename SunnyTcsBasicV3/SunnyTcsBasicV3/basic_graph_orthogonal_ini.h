#pragma once

#include "basic_graph_orthogonal.h"


template<
	typename Key,
	typename Vertex,
	typename Edge
>
template<typename _Key, typename _EdgeType>
class  SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::_EdgeWarpper {
public:
	typedef _EdgeWarpper<_Key, _EdgeType>		SelfType;
	typedef SelfType*							SelfPointer;
	typedef SelfType&							SelfRef;
	//std
	typedef _EdgeType							value_type;
	typedef _Key								key_type;
	typedef _EdgeType*							pointer;
	typedef _EdgeType const*					const_pointer;
	typedef _EdgeType&							reference;
	typedef _EdgeType const&					const_reference;

public:
	_EdgeWarpper()
		:m_edge(nullptr), m_outKey(key_traits::getDefaultValue()),
		m_inKey(key_traits::getDefaultValue()), m_lastSameOut(nullptr),
		m_nextSameOut(nullptr), m_lastSameIn(nullptr), m_nextSameIn(nullptr)
	{
		m_edge = std::make_shared<value_type>();
	}

	_EdgeWarpper(const_reference val,
		key_type out = key_traits::getDefaultValue(),
		key_type in = key_traits::getDefaultValue())
		:m_edge(nullptr), m_outKey(out), m_inKey(in), m_lastSameOut(nullptr),
		m_nextSameOut(nullptr), m_lastSameIn(nullptr), m_nextSameIn(nullptr)
	{
		m_edge = std::make_shared<value_type>(val);
	}

	inline reference edge() { return *m_edge; }
	inline const_reference edge()const { return *m_edge; }
	inline key_type outKey()const { return m_outKey; }
	inline key_type inKey()const { return m_inKey; }
	inline SelfPointer lastSameOut()const { return m_lastSameOut; }
	inline SelfPointer nextSameOut()const { return m_nextSameOut; }
	inline SelfPointer lastSameIn()const { return m_lastSameIn; }
	inline SelfPointer nextSameIn()const { return m_nextSameIn; }

	inline void setEdge(const_reference val) { m_edge = val; }
	inline void setOutKey(key_type out) { m_outKey = out; }
	inline void setInKey(key_type in) { m_inKey = in; }
	inline void setLastSameOut(SelfPointer p) { m_lastSameOut = p; }
	inline void setNextSameOut(SelfPointer p) { m_nextSameOut = p; }
	inline void setLastSameIn(SelfPointer p) { m_lastSameIn = p; }
	inline void setNextSameIn(SelfPointer p) { m_nextSameIn = p; }

private:
	std::shared_ptr<value_type> m_edge;
	key_type m_outKey;
	key_type m_inKey;
	SelfPointer m_lastSameOut;
	SelfPointer m_nextSameOut;
	SelfPointer m_lastSameIn;
	SelfPointer m_nextSameIn;
};




template<
	typename Key,
	typename Vertex,
	typename Edge
>
template<typename _Key, typename _VertexType, typename _EdgeType>
class SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::_VertexWarpper
{
public:
	typedef _VertexWarpper<_Key, _VertexType, _EdgeType>	SelfType;
	typedef _EdgeWarpper<_Key, _EdgeType>					EdgeWarpperType;
	typedef typename EdgeWarpperType::SelfPointer			EdgeWarpperTypePointer;
	typedef typename EdgeWarpperType::SelfRef				EdgeWarpperTypeRef;
	//std
	typedef _VertexType										value_type;
	typedef _Key											key_type;
	typedef _VertexType*									pointer;
	typedef _VertexType const*								const_pointer;
	typedef _VertexType&									reference;
	typedef _VertexType const&								const_reference;

public:
	//ctor
	_VertexWarpper()
		:m_vertex(nullptr), m_headNode(nullptr),
		m_last(key_traits::getDefaultValue()),
		m_next(key_traits::getDefaultValue())
	{
		m_headNode = new EdgeWarpperType();
	}

	_VertexWarpper(const_reference val)
		:m_vertex(nullptr), m_headNode(nullptr),
		m_last(key_traits::getDefaultValue()),
		m_next(key_traits::getDefaultValue())
	{
		m_vertex = std::make_shared<value_type>(val);
		m_headNode = new EdgeWarpperType();
	}

	//copy ctor
	_VertexWarpper(_VertexWarpper const& ref)
		:m_vertex(nullptr), m_headNode(nullptr),
		m_last(ref.m_last), m_next(ref.m_next)
	{
		m_vertex = std::make_shared<value_type>(*(ref.m_vertex));
		m_headNode = new EdgeWarpperType(*(ref.m_headNode));
	}

	//detor
	~_VertexWarpper() {
		delete m_headNode; //头节点自己销毁
	}

	inline reference vertex() { return *m_vertex; }
	inline const_reference vertex()const { return *m_vertex; }
	inline EdgeWarpperTypePointer headNode()const { return m_headNode; }
	inline void setVertex(const_reference val) { *m_vertex = val; }

private:
	std::shared_ptr<value_type> m_vertex;
	EdgeWarpperTypePointer m_headNode;
	key_type m_last; //用来支持迭代器 以深度或者广度遍历
	key_type m_next;
};


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::
SunnyTcsOrthogonalListOrientedGraph() :m_vertexs() {}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::
SunnyTcsOrthogonalListOrientedGraph(SunnyTcsOrthogonalListOrientedGraph const& ref) :m_vertexs(ref.m_vertexs) {
	std::vector< EdgeWarpper*> edgeClone;
	std::vector<key_type>&& allKeys = ref.keys();
	//弧链表处理
	std::for_each(allKeys.begin(), allKeys.end(), [this, &edgeClone, &ref](key_transfered_type key)->void {
		//出弧处理
		key_type outin = ref.firstOutAdjVexOf(key);
		EdgeWarpper* currentEdgeWarpper = this->m_vertexs[key].headNode();
		EdgeWarpper* egwptr = nullptr;
		while (outin != key_traits::getDefaultValue()) {
			auto edgeiter = std::find_if(edgeClone.begin(), edgeClone.end(), [&key, &outin](EdgeWarpper* edgew)->bool { return edgew->inKey() == outin && edgew->outKey() == key; });
			if (edgeiter == edgeClone.end()) { //该线还没有拷贝
				EdgeType const& eg = ref.locateArc(key, outin);
				egwptr = new EdgeWarpper(eg, key, outin);
				edgeClone.push_back(egwptr);
			}
			else {
				egwptr = (*edgeiter);
			}
			currentEdgeWarpper->setNextSameOut(egwptr);
			egwptr->setLastSameOut(currentEdgeWarpper);
			currentEdgeWarpper = egwptr;
			outin = ref.nextOutAdjVexOf(key, outin);
		}
		//入弧处理
		key_type inout = ref.firstInAdjVexOf(key);
		currentEdgeWarpper = this->m_vertexs[key].headNode();
		egwptr = nullptr;
		while (inout != key_traits::getDefaultValue()) {
			auto edgeiter = std::find_if(edgeClone.begin(), edgeClone.end(), [&key, &inout](EdgeWarpper* edgew)->bool {return edgew->inKey() == key && edgew->outKey() == inout; });
			if (edgeiter == edgeClone.end()) { //该线还没有拷贝
				EdgeType const& eg = ref.locateArc(inout, key);
				egwptr = new EdgeWarpper(eg, inout, key);
				edgeClone.push_back(egwptr);
			}
			else {
				egwptr = (*edgeiter);
			}
			currentEdgeWarpper->setNextSameIn(egwptr);
			egwptr->setLastSameIn(currentEdgeWarpper);
			currentEdgeWarpper = egwptr;
			inout = ref.nextInAdjVexOf(key, inout);
		}
		});

}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>&
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::operator=(SunnyTcsOrthogonalListOrientedGraph const& ref) {
	this->destory();
	m_vertexs = ref.m_vertexs;
	std::vector< EdgeWarpper*> edgeClone;
	std::vector<key_type>&& allKeys = ref.keys();
	//弧链表处理
	std::for_each(allKeys.begin(), allKeys.end(), [this, &edgeClone, &ref](key_transfered_type key)->void {
		//出弧处理
		key_type outin = ref.firstOutAdjVexOf(key);
		EdgeWarpper* currentEdgeWarpper = this->m_vertexs[key].headNode();
		EdgeWarpper* egwptr = nullptr;
		while (outin != key_traits::getDefaultValue()) {
			auto edgeiter = std::find_if(allKeys.begin(), allKeys.end(), [&key, &outin](EdgeWarpper* edgew)->bool {edgew->inKey() == outin && edgew->outKey() == key; });
			if (edgeiter == allKeys.end()) { //该线还没有拷贝
				EdgeType const& eg = ref.locateArc(key, outin);
				egwptr = new EdgeWarpper(eg, key, outin);
				edgeClone.push_back(egwptr);
			}
			else {
				egwptr = &(*edgeiter);
			}
			currentEdgeWarpper->setNextSameOut(egwptr);
			egwptr->setLastSameOut(currentEdgeWarpper);
			currentEdgeWarpper = egwptr;
			outin = ref.nextOutAdjVexOf(key, outin);
		}
		//入弧处理
		key_type inout = ref.firstInAdjVexOf(key);
		currentEdgeWarpper = this->m_vertexs[key].headNode();
		egwptr = nullptr;
		while (inout != key_traits::getDefaultValue()) {
			auto edgeiter = std::find_if(allKeys.begin(), allKeys.end(), [&key, &inout](EdgeWarpper* edgew)->bool {edgew->inKey() == key && edgew->outKey() == inout; });
			if (edgeiter == allKeys.end()) { //该线还没有拷贝
				EdgeType const& eg = ref.locateArc(inout, key);
				egwptr = new EdgeWarpper(eg, inout, key);
				edgeClone.push_back(egwptr);
			}
			else {
				egwptr = &(*edgeiter);
			}
			currentEdgeWarpper->setNextSameIn(egwptr);
			egwptr->setLastSameIn(currentEdgeWarpper);
			currentEdgeWarpper = egwptr;
			inout = ref.nextInAdjVexOf(key, inout);
		}
		});
	return *this;
}

template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::size_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::vexSize() const
{
	return m_vertexs.size();
}



template<
	typename Key,
	typename Vertex,
	typename Edge
>
bool SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::containsVex(key_transfered_type key)const {
	return  m_vertexs.find(key) != m_vertexs.end();
}



template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::firstOutAdjVexOf(key_transfered_type k) const{
	assert(m_vertexs.find(k) != m_vertexs.end());
	EdgeWarpper* outHeadNode = m_vertexs.at(k).headNode();
	EdgeWarpper* next = outHeadNode->nextSameOut();
	return !next ? key_traits::getDefaultValue() : next->inKey();
}


template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::nextOutAdjVexOf(key_transfered_type out, key_transfered_type in)const {
	assert(m_vertexs.find(out) != m_vertexs.end() && m_vertexs.find(in) != m_vertexs.end());
	EdgeWarpper* outHeadNode = m_vertexs.at(out).headNode();
	EdgeWarpper* next = outHeadNode->nextSameOut();
	while (next)
	{
		if (in == next->inKey()) {
			return next->nextSameOut() ? next->nextSameOut()->inKey() : key_traits::getDefaultValue();
		}
		next = next->nextSameOut();
	}
	assert(false); //out 和 in 并不构成一条出弧
}


template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::firstInAdjVexOf(key_transfered_type k)const {
	assert(m_vertexs.find(k) != m_vertexs.end());
	EdgeWarpper* outHeadNode = m_vertexs.at(k).headNode();
	EdgeWarpper* next = outHeadNode->nextSameIn();
	return !next ? key_traits::getDefaultValue() : next->outKey();
}


template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::nextInAdjVexOf(key_transfered_type in, key_transfered_type out)const {
	assert(m_vertexs.find(out) != m_vertexs.end() && m_vertexs.find(in) != m_vertexs.end());
	EdgeWarpper* outHeadNode = m_vertexs.at(in).headNode();
	EdgeWarpper* next = outHeadNode->nextSameIn();
	while (next)
	{
		if (out == next->outKey()) {
			return next->nextSameIn() ? next->nextSameIn()->outKey() : key_traits::getDefaultValue();
		}
		next = next->nextSameIn();
	}
	assert(false); //out 和 in 并不构成一条出弧
}




template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::size_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::vexOutDegree(key_transfered_type key)const {
	auto iter = m_vertexs.find(key);
	assert(iter != m_vertexs.end());
	size_type degree = 0;
	EdgeWarpper* next = iter->second.headNode()->nextSameOut();
	while (next) {
		++degree;
		next = next->nextSameOut();
	}
	return degree;
}


template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::size_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::vexInDegree(key_transfered_type key)const {
	auto iter = m_vertexs.find(key);
	assert(iter != m_vertexs.end());
	size_type degree = 0;
	EdgeWarpper* next = iter->second.headNode()->nextSameIn();
	while (next) {
		++degree;
		next = next->nextSameIn();
	}
	return degree;
}


template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::VertexType&
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::locateVex(key_transfered_type key) {
	auto iter = m_vertexs.find(key);
	assert(iter != m_vertexs.end());
	return iter->second.vertex();
}



template<
	typename Key,
	typename Vertex,
	typename Edge
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::VertexType const&
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::locateVex(key_transfered_type key)const {
	auto iter = m_vertexs.find(key);
	assert(iter != m_vertexs.end());
	return iter->second.vertex();
}



template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
void SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::insertVex(key_transfered_type key, VertexType const& val)
{
	m_vertexs.insert(std::pair<key_type, VertexWarpper>(key, VertexWarpper(val)));
}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
void SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::deleteVex(key_transfered_type key) {
	assert(this->containsVex(key));
	key_type nextOne = this->firstOutAdjVexOf(key);
	//删除所有的出弧
	while (key_traits::getDefaultValue() != nextOne) {
		this->deleteArc(key, nextOne);
		nextOne = this->firstOutAdjVexOf(key);
	}
	//删除所有的入弧
	nextOne = this->firstInAdjVexOf(key);
	while (key_traits::getDefaultValue() != nextOne) {
		this->deleteArc(nextOne, key);
		nextOne = this->firstInAdjVexOf(key);
	}
	//删除点本身
	m_vertexs.erase(m_vertexs.find(key));
}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
std::vector<typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type>
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::keys()const {
	std::vector<key_type> ret;
	auto iter = m_vertexs.begin();
	while (iter != m_vertexs.end()) {
		ret.push_back(iter->first);
		++iter;
	}
	return ret;
}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::size_type
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::arcSize()const
{
	size_type ct = 0;
	std::vector<key_type>&& allKeys = this->keys();
	//所有点的出度加起来就是弧的总数
	std::for_each(allKeys.begin(), allKeys.end(), [&ct, this](key_type k)->void { ct += this->vexOutDegree(k); });
	return ct;
}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
bool SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::containsArc(key_transfered_type out, key_transfered_type in)const {
	if (!this->containsVex(out) || !this->containsVex(in))return false;
	EdgeWarpper* outHeadNode = m_vertexs.at(out).headNode();
	EdgeWarpper* next = outHeadNode->nextSameOut();
	while (next)
	{
		if (in == next->inKey()) {
			return true;
		}
		next = next->nextSameOut();
	}
	return false;
}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::EdgeType&
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::locateArc(key_transfered_type out, key_transfered_type in) {
	assert(this->containsVex(out) && this->containsVex(in));
	EdgeWarpper* outHeadNode = m_vertexs[out].headNode();
	EdgeWarpper* next = outHeadNode->nextSameOut();
	while (next)
	{
		if (in == next->inKey()) {
			return next->edge();
		}
		next = next->nextSameOut();
	}
	assert(false);//抛出异常
}




template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::EdgeType const&
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::locateArc(key_transfered_type out, key_transfered_type in)const {
	assert(this->containsVex(out) && this->containsVex(in));
	EdgeWarpper* outHeadNode = m_vertexs.at(out).headNode();
	EdgeWarpper* next = outHeadNode->nextSameOut();
	while (next)
	{
		if (in == next->inKey()) {
			return next->edge();
		}
		next = next->nextSameOut();
	}
	assert(false);//抛出异常
}



template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
void SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::insertArc(key_transfered_type outIndex, key_transfered_type inIndex, EdgeType const& val) {
	assert(outIndex != inIndex);
	EdgeWarpper* newArcPtr = new EdgeWarpper(val, outIndex, inIndex);
	//出弧链表 使用头插法 插入新的弧
	EdgeWarpper* outHeadNode = m_vertexs[outIndex].headNode();
	EdgeWarpper* tempCurNextSameOut = outHeadNode->nextSameOut();
	outHeadNode->setNextSameOut(newArcPtr);
	newArcPtr->setLastSameOut(outHeadNode);
	newArcPtr->setNextSameOut(tempCurNextSameOut);
	if (tempCurNextSameOut)
		tempCurNextSameOut->setLastSameOut(newArcPtr);

	//入弧链表也采用头插法 插入新弧
	EdgeWarpper* inHeadNode = m_vertexs.at(inIndex).headNode();
	EdgeWarpper* tempCurNextSameIn = inHeadNode->nextSameIn();
	inHeadNode->setNextSameIn(newArcPtr);
	newArcPtr->setLastSameIn(inHeadNode);
	newArcPtr->setNextSameIn(tempCurNextSameIn);
	if (tempCurNextSameIn)
		tempCurNextSameIn->setLastSameIn(newArcPtr);
}



template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
void SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::deleteArc(key_transfered_type out, key_transfered_type in) {
	assert(this->containsVex(out) && this->containsVex(in));
	EdgeWarpper* next = m_vertexs[out].headNode()->nextSameOut();
	while (next) {
		if (next->inKey() == in) {
			next->lastSameOut()->setNextSameOut(next->nextSameOut());
			if (next->nextSameOut()) {
				next->nextSameOut()->setLastSameOut(next->lastSameOut());
			}

			next->lastSameIn()->setNextSameIn(next->nextSameIn());
			if (next->nextSameIn()) {
				next->nextSameIn()->setLastSameIn(next->lastSameIn());
			}
			delete next;
			return;
		}
		next = next->nextSameOut();
	}
}


template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
template<typename _Functor>
std::shared_ptr<std::map<typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type, bool>>
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::dfsTraverse(key_transfered_type start, _Functor&& func)
{
	std::shared_ptr<std::map<key_type, bool>> visited = std::make_shared<std::map<key_type, bool>>();
	std::for_each(this->begin(), this->end(),
		[visited](typename VertexContainter::value_type& ref)->void { (*visited).insert(std::pair<key_type, bool>(ref.first, false)); });
	_dfsTraverse(start, std::forward<_Functor>(func), *visited);
	return visited;
}



template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
template<typename _Functor>
std::shared_ptr<std::map<typename SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::key_type, bool>>
SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::bfsTraverse(key_transfered_type start, _Functor&& func)
{
	std::shared_ptr<std::map<key_type, bool>> visited = std::make_shared<std::map<key_type, bool>>();
	std::for_each(this->begin(), this->end(),
		[visited](typename VertexContainter::value_type& ref)->void { (*visited).insert(std::pair<key_type, bool>(ref.first, false)); });
	std::queue<key_type> unvisited;
	unvisited.push(start);
	while (!unvisited.empty()) {
		key_type top = unvisited.front();
		func(m_vertexs[top].vertex());
		visited[top] = true;
		EdgeWarpper* next = m_vertexs.operator[](top).headNode()->nextSameOut();
		while (next)
		{
			unvisited.push(next->inKey());
			next = next->nextSameOut();
		}
		unvisited.pop();
	}
	return visited;
}



template<
	typename Key,
	typename Vertex,
	typename Edge
	
>
template<typename _Functor>
void SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>::_dfsTraverse(key_transfered_type start, _Functor&& func, std::map<key_type, bool>& visited) {
	//对当前点进行操作
	func(m_vertexs[start].vertex());
	visited[start] = true; //记录已遍历点
	//遍历他的出弧线
	EdgeWarpper* next = m_vertexs[start].headNode()->nextSameOut();
	while (next)
	{
		if (!visited[next->inKey()]) {
			_dfsTraverse(next->inKey(), std::forward<_Functor>(func), visited);
		}
		next = next->nextSameOut();
	}
}

