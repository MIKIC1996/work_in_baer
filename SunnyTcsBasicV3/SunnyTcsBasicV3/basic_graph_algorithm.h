#pragma once


#include "basic_graph.h"
#include "basic_math_matrix_variant.h"



class SunnyTcsGraphAlgorithm {
public:
	static char const* strerror(GraphErrorType err);

	inline GraphErrorType errorno()const { return m_error; }


	//ͨ����ͼ�㷨_�Ͻ�˹����_����Ȩֵ����_���·���㷨��Ч��O(n^2)
	template<typename Ty>
	bool dijkstraShortestPath(
		SunnyTcsDynamicVariantMatrix<Ty>& matrix,
		typename SunnyTcsDynamicVariantMatrix<Ty>::size_type start, //���
		SunnyTcsDynamicVariantArray< typename SunnyTcsDynamicVariantMatrix<Ty>::size_type>& spath, //���·������
		SunnyTcsDynamicVariantArray< typename SunnyTcsDynamicVariantMatrix<Ty>::value_type>& cost //ÿ��Ŀ�����С����
	) { 
		if (!matrix.isRowVaild(start))return false; //��㲢����Ȩֵ��������Ч
		using size_type = typename SunnyTcsDynamicVariantMatrix<Ty>::size_type;
		using value_type = typename SunnyTcsDynamicVariantMatrix<Ty>::value_type;
		SunnyTcsDynamicVariantArray<bool> isFinished(matrix.rows());//��ɱ���¼��ص�����·���Ƿ��Ѿ������
		std::vector<size_type> vexs; //���еĶ����ھ����е�����
		for (size_type i = 0; i < matrix.rows(); ++i) { //����Ȩֵ���������е��У���Ч�м�����һ������
			if (matrix.isRowVaild(i)) { //�ҵ�һ����
				vexs.push_back(i);
				isFinished.insert(i, false);//��ʼ���������
				if (i != start && matrix.isPosVaild(start, i)) { //start���õ���ͨ
					cost.insert(i, matrix[start][i]); //��¼���������
					spath.insert(i ,start);
				}
			}
		}
		cost.insert(start, SunnyTcsTypeTraits<value_type>::getDefaultValue()); //�������Ļ���Ϊ0
		isFinished[start] = true; //��㵽��㱾��������·��
		spath.insert(start, start); //Ҫ����㣬��������Լ���

		for (int i = 0; i < vexs.size(); ++i) {
			long long  k = -1;
			value_type min = SunnyTcsTypeTraits<value_type>::getMaxValue();//��ȡ��󻨷�
			for (int j = 0; j < vexs.size(); ++j) {
				if (!isFinished[vexs[j]] && cost.isPosVaild(vexs[j]) && cost[vexs[j]] < min) { //����֪�������ҵ���С��
					k = vexs[j];
					min = cost[vexs[j]];
				}
			}
			//��������֪�����У��ҵ���С���Ǹ����ѣ�������Ѿ��ǵ����������·��
			if (-1 == k)continue;
			isFinished[k] = true;
			//����Ѱ��k��������
			for (int j = 0; j < vexs.size(); ++j) {
				//���δ�ҵ����·���ĵ㣬���뱾���ҵ����·���ĵ�k �������� ����������㻹û�м�¼���ѣ������Ѽ�¼���ѱ� ��ǰ��start��k�ٵ��õ�Ļ��Ѵ�
				//��ô�͸���һ�»��ѱ����Ұ��������µ�spath·������
				if (!isFinished[vexs[j]] && matrix.isPosVaild(k, vexs[j]) &&
					(!cost.isPosVaild(vexs[j]) || min + matrix[k][vexs[j]] < cost[vexs[j]]))
				{
					cost.insert(vexs[j], min + matrix[k][vexs[j]]);
					spath.insert(vexs[j], k);
				}
			}
		}
	}

private:
	GraphErrorType m_error = NoError;

};