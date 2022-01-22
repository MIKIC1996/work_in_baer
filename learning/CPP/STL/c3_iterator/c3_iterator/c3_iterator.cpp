// c3_iterator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>
#include <functional>


#include <iostream>



namespace jmq_std {

	//五种迭代器行为
	//InputIterator 只读 （++）
	//OutputIterator 只写 （++）
	//ForwardIterator	读写 （++）
	//BidirectionalIterator	双向 （++、--）
	//RandomAccessIterator	全指针算数能力（++、--、p+n、p-n、p[n],p1-p2,p1<p2等）

	struct InputIterator {};
	struct OutputIterator {};
	struct ForwardIterator :public InputIterator{};
	struct BidirectionalIterator:public ForwardIterator{};
	struct RandomAccessIterator :public BidirectionalIterator{};

	//stl的iterator接口
	template <class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T&>
	struct iterator {
		//stl 迭代器规范
		typedef Category	iterator_categoty;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};
}


class A {
public:
	A(int& val) :ref(val) {
		a = 10;
		ptr = &a;
	}

	int a;
	int *ptr;
	int& ref;
};



int main()
{
	int val = 100;
	char* me = (char*)malloc(20);
	memset(me, 0, 20);

	new (me) A(val); //在me那边构造一个A

	std::cout << sizeof(int&) << std::endl;
	int * _a =(int*) me;
	std::cout << *_a << std::endl;
	_a++;
	std::cout << **(int **)_a << std::endl;
	_a++;
	std::cout << **(int **)_a << std::endl;
	_a++;
	std::cout << *_a << std::endl;
	getchar();
    return 0;
}

