// SunnyTcsBasicEasyTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <variant>
#include "..\SunnyTcsBasicV3\basic_graph_orthogonal_ini.h"

#include "..\SunnyTcsBasicV3\basic_object.h"

#include "..\SunnyTcsCoreV3\core_subtask.h"

#include "..\SunnyTcsBasicV3\basic_resource_manager_shared.h"

#include <concepts>
#include <type_traits>
#include <coroutine>

#include <sqlite/sqlite3.h>

int add(int a, int b) { return  a + b; }

#define PPP(arg)\
	C__##arg

#define UUUU(arg,...)\
	PPP(arg)...


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



void showAdjMatrix(SunnyTcsCraftModel& cm) {
	std::vector<int32_t> keys = cm.keys();
	std::cout << "  ";
	std::for_each(keys.begin(), keys.end(), [](int32_t k)->void {std::cout <<' ' << k; });
	std::cout << std::endl;
	std::cout<<"____________________" << std::endl;

	for (int i = 0; i < keys.size(); ++i) {
		std::cout << keys.at(i) << "|";
		for (int j = 0; j < keys.size(); ++j) {
			bool linked = cm.containsArc(keys.at(i), keys.at(j));
			if(linked){
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



struct FUN {

 	TCS_STATIC_REFLECT2(FUN,_iv,_cv)
	


	FUN(int v, char c) { _iv = v; _cv = c; 


	std::cout << typeid(&FUN::_cv).name() << std::endl;
	}

	

	int _iv;
	char _cv;
};






int main()
{

	FUN sam2(1, 33);
	const FUN sam{ 1,32 };
	TCS_SRCFN2(_iv, sam2) = 10;
	
	std::cout<< TCS_SRCFN2(_iv, sam2) <<std::endl;

	sam2._iv
	
	int arr[3][3] = { {1,2,3},{4,5,6},{7,8,9} };


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
