#pragma once
#include "stdafx.h"



template<
	typename T,
	//�ڶ���ģ���������ģ��, ��Ϊ ��ģ���ģ������� 
	template<typename elem, typename alloc = std::allocator<elem>> class Container = std::vector
>
class MyStack {
public:
	MyStack() :_elems() {}

	Container<T > _elems;

	void print();

	template<typename T_2,
		template<typename elem_2, typename alloc_2 >class Container_2 //���ﲻ��Ҫ������ȱʡֵ��
	>
		void print_another_one(MyStack<T_2, Container_2>const & s);
};



template<typename T, template<typename /*elem*/, typename /*alloc*/ >class Container > //�ò��ϵ�ģ����������Բ�д
inline void MyStack<T, Container>::print() {


}

template<typename T, template<typename /*elem*/, typename /*alloc*/ >class Container >
template<typename T_2, template<typename /*elem*/, typename /*alloc*/ >class Container_2 >
inline void MyStack<T, Container>::print_another_one(MyStack<T_2, Container_2> const& s) {

}