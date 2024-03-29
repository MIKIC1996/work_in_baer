// std_men_fn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <functional>
using namespace std;


class AAA {
public:

	int add(int a, int b) const{
		cout << "const"<<(a + b) << endl;
		return a + b;
	}

	int add(int a, int b){
		cout << (a + b) << endl;
		return a + b;
	}

	int _value = 199;

};


//如何定义类的成员函数指针
typedef int (AAA::*mem_func)(int a,int b);
//如何定义类的常成员函数指针
typedef int (AAA::*mem_func_const)(int a, int b)const;
//如何定义类成员对象指针
typedef int AAA::*mem_val;
//如何使用类成员函数指针
void _use_class_mem_function(){
	//定义一个类成员函数指针
	mem_func_const func1;
	//指针赋值，注意语法
	func1 = &AAA::add;
	//类成员函数指针必须配合 类实例一起使用
	const AAA a1;
	(a1.*func1)(1, 2);

	mem_val val;
	val = &AAA::_value;
	cout << a1.*val << endl;
};


//使用模板定义一个简单的 类成员函数包装器
template <typename _Res, typename _Class ,typename... _ArgTypes>
class My_Men_fn  {
public:
	typedef _Res(_Class::*_Functor)(_ArgTypes...);

	explicit My_Men_fn(_Functor __pmf) {
		_pmf = __pmf;
	}

	_Res operator()(_Class& __object, _ArgTypes&&... __args) {   //该形式 要求 __object必须引用一左值
		return (__object.*_pmf)(std::forward<_ArgTypes>(__args)...);
	}

	_Res operator()(_Class&& __object, _ArgTypes&&... __args) { //该可以传入右值
		return (std::move(__object).*_pmf)(std::forward<_ArgTypes>(__args)...);
	}

	_Res operator()(_Class* __object, _ArgTypes&&... __args) {   //该形式 要求 __object必须引用一左值
		return (*__object.*_pmf)(std::forward<_ArgTypes>(__args)...);
	}

	template<typename _Tp> //针对派生类 或者 智能指针
	_Res operator()(_Tp&&  __object, _ArgTypes&&... __args) {
		return _M_call(std::forward<_Tp>(__object), &__object, std::forward<_ArgTypes>(__args)...);
	}

	template<typename _Tp, typename... _Args>
	_Res _M_call(_Tp&& __object, const volatile _Class *, _Args&&... __args) const
	{
		return (std::forward<_Tp>(__object).*__pmf)(std::forward<_Args>(__args)...);
	}

	template<typename _Tp, typename... _Args>
	_Res _M_call(_Tp&& __ptr, const volatile void *, _Args&&... __args) const
	{
		return ((*__ptr).*__pmf)(std::forward<_Args>(__args)...);
	}

protected:
	_Functor _pmf;
};


//使用这个包装器
void _use_my_mem_fn() {

	My_Men_fn<int,AAA,int,int> pmf(&AAA::add); //使用这个类必须事先指定好类模板参数，我们可以用 函数模板推导。
	AAA a1;
	pmf(a1, 1, 3);
	
}

//利用函数模板的自动参数推导，自动获取所需要的_my_men_fn对象
template<typename _Res, typename _Class, typename... _ArgTypes>
My_Men_fn<_Res, _Class, _ArgTypes...> _My_Men_fn(_Res (_Class::* pmf)(_ArgTypes... __args)) {
	return My_Men_fn< _Res, _Class,_ArgTypes...>(pmf);
}

void _use_my_mem_fn_func() {
	AAA a1;
	(_My_Men_fn(&AAA::add))(a1,1,3);
}



class CA {
public:
	CA() :_val(0) { std::cout << "1111"; }
	CA(int val) :_val(val) { std::cout << "2222"; }

	int _val;
};


class CB :public virtual CA {
public:
	CB() :CA() {
		std::cout << 33333;
	}
};

class CC :public virtual CA {
public:
	CC() :CA(8) {
		std::cout << 44444;
	}

};


class CD :public CB, public CC {
public:
	CD():CB(),CC(){}

};


int main()
{
	CD cd;
	std::cout << cd._val;
	//_use_class_mem_function();

	//std::mem_fn()

	getchar();
    return 0;
}

