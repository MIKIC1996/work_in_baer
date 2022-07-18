// SunnyTcsBasicEasyTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <variant>
#include "..\SunnyTcsBasicV3\basic_graph_orthogonal_ini.h"

#include "..\SunnyTcsBasicV3\basic_object.h"

#include "..\SunnyTcsCoreV3\core_subtask.h"

#include "..\SunnyTcsBasicV3\basic_resource_manager_shared.h"

#include "..\SunnyTcsBasicV3\basic_math_matrix.h"

#include "..\SunnyTcsBasicV3\basic_db_mysql.h"

#include "..\SunnyTcsBasicV3\basic_graph_adjmatrix.h"

#include "..\SunnyTcsBasicV3\basic_rpn.h"

#include <concepts>
#include <type_traits>
#include <coroutine>





/*
struct HelloCo {
	struct  HelloPromise
	{
		HelloCo get_return_object() {
			//return std::coroutine_handle<HelloPromise>::from_promise(*this);
		}
		auto initial_suspend() { }
		auto  final_suspend() { }
		void unhandled_exception(){}
		void return_void() {}
	};
	using promise_type = HelloPromise;

	HelloCo(std::coroutine_handle<HelloPromise> h):_h(h){}

	std::coroutine_handle<HelloPromise> _h;

};



HelloCo hello() {
	std::cout << "hello" << std::endl;
	co_await std::suspend_always{};
	std::cout << "world" << std::endl;
}

*/





struct FUN {

 	TCS_STATIC_REFLECT3(FUN,_iv,_cv)
	
	

	FUN(int v, char c) { _iv = v; _cv = c; 

	}

	

	int _iv;
	char _cv;
};



void arrayTest() {
	SunnyTcsDynamicVariantArray<int> arr;
	arr.insert(3, 3);
	arr.insert(4, 4);
	arr.insert(5, 5);
	arr.remove(5);
	arr.push_front( 5);
	arr.push_front( 0);

	auto iter = arr.begin();
	while (iter!=arr.end()) {
		//assert(iter);
		std::cout << *iter << std::endl;
		++iter;
	}

}


void MatrixTest() {
	SunnyTcsDynamicVariantMatrix<int> ma(0, 0);
	ma.insert(1, 1, 11);
	ma.resetSize(20, 20);
	ma.insert(1, 1, 11);
	ma.insert(2, 2, 22);
	ma.insert(19, 19, 1919);
	ma.swapRows(1, 19);
	ma.swapColumns(1, 19);
	SunnyTcsDynamicVariantMatrix<int> mma2(std::move(ma));
	SunnyTcsDynamicVariantMatrix<int> mma3(mma2);
	mma3.insert(3, 3, 33);
	mma3.removeRow(3);
	std::cout << "__" << mma3.firstInVaildRow() << std::endl;
	assert(mma2 == mma3);
	mma2 = std::move(ma);
	ma.resetColumns(19);
	ma.resetRows(2);
	auto one = mma3.toOtherMatrix<long>([](auto& obj)->long {return (long)(2 * obj); });
	SunnyTcsDynamicVariantMatrix<long>& mma = one;
	
	auto iter = mma.begin();
	while (iter != mma.end()) {
		std::cout << *iter << std::endl;
		++iter;
	}
	
}



void AdjMatrixTest() {
	struct Point {
		int _id;
		std::string name;

		bool operator==(Point const& var)const {
			return _id == var._id && name == var.name;
		}
	};

	struct Edge {
		int _id;
		std::string name;

		bool operator==(Edge const& var)const {
			return _id == var._id && name == var.name;
		}
	};

	SunnyTcsAdjMatrixOrientedGraph<int, Point, Edge> amg(300);
	amg.insertVex(0, Point{ 0,"pt0" });
	amg.insertVex(1, Point{ 1,"pt1" });
	amg.insertVex(2, Point{ 2,"pt2" });
	amg.insertVex(3, Point{ 3,"pt3" });
	amg.insertVex(4, Point{ 4,"pt4" });
	amg.insertVex(5, Point{ 5,"pt5" });
	amg.insertVex(6, Point{ 6,"pt6" });

	amg.insertArc(1, 2, Edge{ 12,"path12" });
	amg.insertArc(1, 3, Edge{ 13,"path13" });
	amg.insertArc(1, 5, Edge{ 15,"path15" });
	amg.insertArc(3, 4, Edge{ 34,"path34" });
	amg.insertArc(5, 6, Edge{ 56,"path56" });
	amg.insertArc(4, 6, Edge{ 46,"path46" });
	SunnyTcsOrientedGraphTrait<SunnyTcsAdjMatrixOrientedGraph<int, Point, Edge>>::showAdjMatrix(amg);

	SunnyTcsDynamicVariantMatrix<int> wm = amg.toWeightMatrix<int>([](Edge const& e)->int {return e._id*2 ; });
	
	
	SunnyTcsGraphAlgorithm alg;
	SunnyTcsDynamicVariantArray<typename SunnyTcsDynamicVariantMatrix<int>::difference_type > spath;
	SunnyTcsDynamicVariantArray<int> cost;
	alg.dijkstraShortestPath<int>(wm, 1, spath, cost);

	for (int i = 0; i < spath.size(); ++i) {
		if(spath.isPosVaild(i))
		std::cout << i << " : " << spath[i] << std::endl;
	}

	for (int i = 0; i < cost.size(); ++i) {
		if (cost.isPosVaild(i))
			std::cout << i << " : " << cost[i] << std::endl;
	}
	
}




int main()
{
	
	do{
		AdjMatrixTest();
	} while (0);

	SunnyTcsStack<int> si;

	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
