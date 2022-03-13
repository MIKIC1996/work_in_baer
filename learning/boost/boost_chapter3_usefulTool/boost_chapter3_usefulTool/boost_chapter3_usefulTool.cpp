// boost_chapter3_usefulTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>

//不可拷贝的类
class ObjectNonCopyAble :public boost::noncopyable {
public:
	ObjectNonCopyAble(int v) {
		_val = v;
	}

	//ObjectNonCopyAble(const ObjectNonCopyAble& obj):noncopyable(obj) {
	//	_val = obj._val;   无法调用noncopyable的拷贝构造函数
	//}

	
protected:
	int _val = 0;
};


struct Person {
	bool _isMale;
	int _ord;
	char _name[100];
};

int main()
{
	ObjectNonCopyAble copy(100);
	//ObjectNonCopyAble copy2(copy);

	struct Person p1={true,10};
	if (p1._isMale) {
		std::cout << "fuck" << std::endl;
	}
	//std::cout << p1._name << std::endl;
	//Person p2(true, 11, "nima");

	//--------------ignored 忽略未使用变量和类型的警告-------------
	int noUsedValue = 1001;
	boost::ignore_unused(noUsedValue);

	typedef double Double_type;
	boost::ignore_unused<Double_type>();

	//-----------------boost::optional-------------------------
	boost::optional<int> int_option;
	std::cout << int_option.value_or(255) << std::endl;//返回有效值，否则返回默认值

	std::string str = "your are mine";
	boost::optional<std::string> per_op(str.length() > 3, str); //满足条件 初始化了
	boost::optional<std::string> per_op2(str.length() > 30, str);//不满足条件 算未初始化
	std::cout << per_op.value_or("not a value") << std::endl;
	std::cout << per_op2.value_or_eval([]() {return "not a val"; }) << std::endl;

	


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
