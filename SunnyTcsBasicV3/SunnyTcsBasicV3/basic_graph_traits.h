#pragma once

#include "basic_graph_algorithm.h"



//����ͼ�У����ڶ�������͵� ��ȡ
template<typename Ty>
class SunnyTcsGraphKeyTrait {
public:
	typedef Ty value_type;
	typedef typename std::conditional< std::is_trivially_copyable<value_type>::value, value_type, value_type const&>::type TransferedType;
	static Ty getDefaultValue() { return 0; }
	static Ty getInvaildValue() { return -1; }
};



//����ͼ��ȡ������ͨ����ִ��ͼ��ͨ�ò�������ؼ�·�������·���ļ����
template<typename Ty>
class SunnyTcsOrientedGraphTrait {
public:
	typedef SunnyTcsOrientedGraphTrait<Ty>				Self;
	typedef typename Ty									GraphType;
	typedef typename GraphType::key_type				key_type;
	typedef typename GraphType::VertexType				VertexType;
	typedef typename GraphType::EdgeType				EdgeType;
	typedef typename GraphType::size_type				size_type;
	typedef typename GraphType::difference_type			difference_type;
	typedef typename GraphType::key_transfered_type		key_transfered_type;

	

	//����Ȩֵ����
	template<typename ValTy, typename Functor ,typename MatrixType>
	GraphErrorType toWeightMatrix(GraphType const& graph, Functor&& func ,
		std::map<key_type,size_type>& keyIndexMap, MatrixType& matrix ) {
		
	}



	//��ӡ�ڽӾ���
	static void showAdjMatrix(GraphType& cm) {
		std::vector<int32_t> keys = cm.keys();
		std::cout << "  ";
		std::for_each(keys.begin(), keys.end(), [](int32_t k)->void {std::cout << ' ' << k; });
		std::cout << std::endl;
		std::cout << "____________________" << std::endl;
		for (int i = 0; i < keys.size(); ++i) {
			std::cout << keys.at(i) << "|";
			for (int j = 0; j < keys.size(); ++j) {
				bool linked = cm.containsArc(keys.at(i), keys.at(j));
				if (linked) {
					std::cout << " " << 1;
				}
				else
				{
					std::cout << " " << 0;
				}
			}
			std::cout << std::endl;
		}
	}
	//������ȱ���
	static void bfsTraverse();
	//������ȱ���
	static void hfsTraverse();

	//�Ͻ�˹�������·��
	template< typename Valty , typename Functor>
	static bool dijkstraShortestPath(GraphType const& graph, key_transfered_type start,
		key_transfered_type end ,std::vector<key_type>& ret ,Valty& cost , Functor&& func) 
	{
		
		
	}



	
};


