// boost_chapter2_memoryManage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <boost/smart_ptr.hpp>
#include <boost/make_unique.hpp>//内含支持std::unique_ptr的工厂函数
//#include <boost/smart_ptr/scoped_ptr.hpp>
//#include <boost/smart_ptr/shared_ptr.hpp>
//#include <boost/smart_ptr/weak_ptr.hpp>
//#include <boost/smart_ptr/intrusive_ptr.hpp>


//函数对象
class Sumer {
public:
	int operator()(int a,int b) {
		return a + b;
	}

};


class Self_Weak {//返回指向自身的指针的类
public:

	Self_Weak(int nn){
		n = nn;
	}

	void print() {
		std::cout << n << std::endl;
	}

	boost::shared_ptr<Self_Weak> getShared() {
		return boost::make_shared<Self_Weak>(*this);
	}
	
private:
	int n;

};




class Printer{
public:
	void operator() (std::string str) {
		std::cout << str << std::endl;
	}
};
template<class T>//函数对象与调用函数对象的函数
void exeFuncObj(std::string str, T a) {
	a(str);
};

//-----------------------------------可变参数模板 递归函数方式展开
void print() {
	std::cout << "empty" << std::endl;
}
//展开函数
template <class T, class... Args>//class... 不能有空格
void print(T head, Args... rest) {//Args... 不能有空格
	std::cout << "parameter " << head << std::endl;
	print(rest...);
};




//-------------------------------可变参数模板 逗号表达式展开
template <class T>
void Cprint(T t) {
	std::cout << t << std::endl;
};

template <class ...Args>//模板函数
void expand(Args... args) {
	int arr[] = { (Cprint(args), 0)... };
};

//用到数组的初始化列表，这个数组的目的纯粹是为了在数组构造的过程展开参数包。
//{(printarg(args), 0)...}将会展开成((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0),  etc... )，
//最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]。printarg便会处理参数包中每一个参数。

template<class... Args>//模板类
class ArgsTester {
public:
	static void argsPrint(Args... rest) {
		int arr[] = { (zprint(rest),0)... };
	}

	template <class T>
	static void zprint(T t) {
		std::cout << t << std::endl;
	};
};


int sum(int a, int b,int(*func)(int v1,int v2)) {
	return func(a, b);
}

//定制 删除器
void deleter(std::string *strP) {
	std::cout << *strP << std::endl;
	delete strP;
}





int main()
{
	//------------------------------scoped_ptr--------------------------
	std::string* std_ptr=NULL;
	{
		//将指针设为私有的scoped_ptr,不可拷贝，不可复制，私有的拷贝构造函数和 =运算符重载函数
		boost::scoped_ptr<std::string> scp_ptr(new std::string("you"));//无需delete ,在ptr析构时自动delete
		//如果一个类持有该种指针，这个类也是不可拷贝和=赋值的
		//该指针不可++ --
		std::cout << *scp_ptr << std::endl;
		*scp_ptr = "your fuck";
		std::cout << scp_ptr->length() << std::endl;
		std_ptr = scp_ptr.get();//由get 得到原始指针，不可delete
		assert(scp_ptr != nullptr);
		scp_ptr.reset();
		if (!scp_ptr) {
			std::cout << " are mine" << std::endl;
		}
	}//delete std_ptr;//会奔溃，因为scoped_ptr已经delete 资源了

	//---------------------std::unique_ptr-----------------------------
	{
		std::unique_ptr<int> u_ptr(new int(100));//与scoped_ptr差不多
		auto u_ptr2= boost::make_unique<int>(101);
		std::cout << *u_ptr2  << std::endl;
	}
	//-----------------------shared_ptr--------------------------------
	{
		boost::shared_ptr<int> s_ptr(new int(250));
		assert(s_ptr.use_count() == 1);
		assert(s_ptr.unique());
		boost::shared_ptr<int> s_ptr_c = s_ptr;
		assert(!s_ptr.unique());
		assert(s_ptr == s_ptr_c && s_ptr_c.use_count() == 2);

		boost::shared_ptr<std::string> str_s_ptr = boost::make_shared<std::string>("funny mud pee");
		s_ptr.reset();
	}

	//print(1, 3, "y");
	print(1, 1, "t");
	expand(2, 34, "zzz");
	ArgsTester<int, double, std::string>::argsPrint(1, 1.1, "sasd");
	
	{//删除器---------------------
		boost::shared_ptr<std::string> sstrp(new std::string("bx"), &deleter);
	}
	//指针转换函数---------------返回shared_ptr
	boost::shared_ptr<std::string> sstrp(new std::string("nk"));
	boost::static_pointer_cast<std::string>(sstrp);
	boost::dynamic_pointer_cast<std::string>(sstrp);
	//boost::const_pointer_cast<>

	//别名构造函数------------------------
	boost::shared_ptr<int> int_p = boost::make_shared<int>(10);
	int n = 100;
	boost::shared_ptr<int> int_p2(int_p, &n);//共享计数，却指向他人
	std::cout << int_p.use_count() << std::endl;
	std::cout << *int_p2 << std::endl;



	//---------------------lambda表达式----------------------------
	int val = 100;
	auto res = [val](int a, int b)->int {return (a > val && b==val) ? 1000 : 10000; };//res代表一个函数类型
	std::cout << res(101,120) << std::endl;

	auto fuc = [](int a, int b)->int {return a + b; };
	std::cout<<sum(17, 20, fuc)<<std::endl;//lambda表达式 和 函数指针 


	Sumer a;//函数对象
	std::cout << a(10, 20) << std::endl;
	Printer p;
	exeFuncObj("tkz",p);
	
	//----------------------void* 指针---------------------------
	void* voidptr = new std::string("why im a guy");
	std::cout << *(static_cast<std::string*>(voidptr)) << std::endl;


	//----------------------weak_ptr-----------------------------

	{
		boost::shared_ptr<double> dou_ptr = boost::make_shared<double>(0.5);
		boost::weak_ptr<double> weak_ptr(dou_ptr);
		boost::shared_ptr<double> dou2 = weak_ptr.lock();
		assert(weak_ptr.use_count() == 2);
		dou_ptr.reset();
		dou2.reset();
		assert(weak_ptr.expired());
	}

	Self_Weak ptr3(250);
	ptr3.getShared()->print();
	



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
