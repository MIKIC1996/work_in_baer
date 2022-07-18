#pragma once


#include "basic_graph.h"
#include "basic_math_matrix_variant.h"



class SunnyTcsGraphAlgorithm {
public:
	static char const* strerror(GraphErrorType err);

	inline GraphErrorType errorno()const { return m_error; }


	//通用型图算法_迪杰斯特拉_基于权值矩阵_最短路径算法，效率O(n^2)
	template<typename Ty>
	bool dijkstraShortestPath(
		SunnyTcsDynamicVariantMatrix<Ty>& matrix,
		typename SunnyTcsDynamicVariantMatrix<Ty>::size_type start, //起点
		SunnyTcsDynamicVariantArray< typename SunnyTcsDynamicVariantMatrix<Ty>::size_type>& spath, //最短路径数组
		SunnyTcsDynamicVariantArray< typename SunnyTcsDynamicVariantMatrix<Ty>::value_type>& cost //每个目标的最小花费
	) { 
		if (!matrix.isRowVaild(start))return false; //起点并不在权值矩阵中有效
		using size_type = typename SunnyTcsDynamicVariantMatrix<Ty>::size_type;
		using value_type = typename SunnyTcsDynamicVariantMatrix<Ty>::value_type;
		SunnyTcsDynamicVariantArray<bool> isFinished(matrix.rows());//完成表，记录相关点的最短路径是否已经计算出
		std::vector<size_type> vexs; //所有的顶点在矩阵中的索引
		for (size_type i = 0; i < matrix.rows(); ++i) { //遍历权值矩阵中所有的行，有效行即代表一个顶点
			if (matrix.isRowVaild(i)) { //找到一个点
				vexs.push_back(i);
				isFinished.insert(i, false);//初始化完成数组
				if (i != start && matrix.isPosVaild(start, i)) { //start到该点相通
					cost.insert(i, matrix[start][i]); //记录下这个花费
					spath.insert(i ,start);
				}
			}
		}
		cost.insert(start, SunnyTcsTypeTraits<value_type>::getDefaultValue()); //设置起点的花费为0
		isFinished[start] = true; //起点到起点本身就是最短路径
		spath.insert(start, start); //要到起点，就是起点自己啊

		for (int i = 0; i < vexs.size(); ++i) {
			long long  k = -1;
			value_type min = SunnyTcsTypeTraits<value_type>::getMaxValue();//获取最大花费
			for (int j = 0; j < vexs.size(); ++j) {
				if (!isFinished[vexs[j]] && cost.isPosVaild(vexs[j]) && cost[vexs[j]] < min) { //从已知花费中找到最小的
					k = vexs[j];
					min = cost[vexs[j]];
				}
			}
			//从所有已知花费中，找到最小的那个花费，这个花费就是到这个点的最短路径
			if (-1 == k)continue;
			isFinished[k] = true;
			//遍历寻找k的衍生点
			for (int j = 0; j < vexs.size(); ++j) {
				//如果未找到最短路径的点，他与本次找到最短路径的点k 是相连的 ，并且这个点还没有记录花费，或者已记录花费比 当前从start到k再到该点的花费大
				//那么就更新一下花费表，并且把这个点更新到spath路径表中
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