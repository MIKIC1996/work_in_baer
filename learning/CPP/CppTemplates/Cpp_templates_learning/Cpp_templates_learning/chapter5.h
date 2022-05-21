#pragma once
#include "stdafx.h"



template<
	typename T,
	//第二个模板参数是类模板, 称为 “模板的模板参数” 
	template<typename elem, typename alloc = std::allocator<elem>> class Container = std::vector
>
class MyStack {
public:
	MyStack() :_elems() {}

	Container<T > _elems;

	void print();

	template<typename T_2,
		template<typename elem_2, typename alloc_2 >class Container_2 //这里不需要在设置缺省值了
	>
		void print_another_one(MyStack<T_2, Container_2>const & s);
};



template<typename T, template<typename /*elem*/, typename /*alloc*/ >class Container > //用不上的模板参数，可以不写
inline void MyStack<T, Container>::print() {


}

template<typename T, template<typename /*elem*/, typename /*alloc*/ >class Container >
template<typename T_2, template<typename /*elem*/, typename /*alloc*/ >class Container_2 >
inline void MyStack<T, Container>::print_another_one(MyStack<T_2, Container_2> const& s) {

}
