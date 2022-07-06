#pragma once

#include "basic_graph.h"




//ͨ�õ�����ͼ ���ݽṹ�������Ż�����˫��ʮ������ʵ��
template<
	typename Key,
	typename Vertex,
	typename Edge
>
class SunnyTcsOrthogonalListOrientedGraph 
{
public:

	//��Ƕ��ģ�壬������ 
	template<typename _Key, typename _EdgeType>
	class _EdgeWarpper;

	//��Ƕ��ģ�壬�������
	template<typename _Key, typename _VertexType, typename _EdgeType>
	class _VertexWarpper;

	//��������
	enum TraverseStrategy {
		DFS = 0x02, //������ȱ���
		BFS = 0x03  //������ȱ���
	};

	//����
	typedef SunnyTcsOrthogonalListOrientedGraph<Key, Vertex, Edge>	Self;
	typedef SunnyTcsTypeTraits<Key>														key_traits;
	typedef Key																			key_type;
	typedef typename SunnyTcsTypeTraits<Key>::TransferedType							key_transfered_type;
	typedef Vertex																		VertexType;
	typedef Edge																		EdgeType;
	//�ڵ�����
	typedef _EdgeWarpper<key_type, EdgeType>											EdgeWarpper;
	typedef _VertexWarpper<key_type, VertexType, EdgeType>								VertexWarpper;
	//�ڲ�����
	typedef std::map<key_type, VertexWarpper>											VertexContainter;
	typedef typename VertexContainter::size_type										size_type;
	//������
	typedef typename VertexContainter::iterator											iterator;
	typedef typename VertexContainter::const_iterator									const_iterator;

	

public:
	//ctor
	SunnyTcsOrthogonalListOrientedGraph();
	//copy ctor ���δ���
	SunnyTcsOrthogonalListOrientedGraph(SunnyTcsOrthogonalListOrientedGraph const&);
	//dector
	virtual ~SunnyTcsOrthogonalListOrientedGraph() { this->destory(); }
	//operator
	SunnyTcsOrthogonalListOrientedGraph& operator=(SunnyTcsOrthogonalListOrientedGraph const&);
// 	bool operator==(SunnyTcsOrthogonalListOrientedGraph const&)const;
// 	bool operator!=(SunnyTcsOrthogonalListOrientedGraph const&)const;
// 	VertexType& operator[](key_transfered_type);
	//vertex
	inline size_type vexSize()const;
	inline bool containsVex(key_transfered_type)const;
	key_type firstOutAdjVexOf(key_transfered_type)const;
	key_type nextOutAdjVexOf(key_transfered_type, key_transfered_type)const;
	key_type firstInAdjVexOf(key_transfered_type)const;
	key_type nextInAdjVexOf(key_transfered_type, key_transfered_type)const;
	size_type vexOutDegree(key_transfered_type)const;
	size_type vexInDegree(key_transfered_type)const;
	VertexType& locateVex(key_transfered_type);
	VertexType const& locateVex(key_transfered_type)const;
	inline void insertVex(key_transfered_type, VertexType const&);
	void deleteVex(key_transfered_type);
	std::vector<key_type> keys()const;
	//arc
	size_type arcSize()const;
	bool containsArc(key_transfered_type, key_transfered_type)const;
	EdgeType& locateArc(key_transfered_type, key_transfered_type);
	EdgeType const& locateArc(key_transfered_type, key_transfered_type)const;
	void insertArc(key_transfered_type, key_transfered_type, EdgeType const&);
	void deleteArc(key_transfered_type, key_transfered_type);

	//���ݱ�׼��
	iterator begin() { return m_vertexs.begin(); }
	const_iterator cbegin()const { return m_vertexs.cbegin(); }
	iterator end() { return m_vertexs.end(); }
	const_iterator cend()const { return m_vertexs.cend(); }
	//������ȱ���
	template<typename _Functor>
	std::shared_ptr<std::map<key_type, bool>> dfsTraverse(key_transfered_type, _Functor&&);
	//������ȱ���
	template<typename _Functor>
	std::shared_ptr<std::map<key_type, bool>> bfsTraverse(key_transfered_type, _Functor&&);
private:
	template<typename _Functor>
	void _dfsTraverse(key_transfered_type, _Functor&&, std::map<key_type, bool>&);
private:
	//��ʼ��
	void init() {

	}

	//����
	void destory() {
		while (m_vertexs.size() > 0) {
			this->deleteVex(this->begin()->first);
		}
	}

private:
	VertexContainter m_vertexs;
};


static SunnyTcsOrthogonalListOrientedGraph<int, int, int>* inttest;