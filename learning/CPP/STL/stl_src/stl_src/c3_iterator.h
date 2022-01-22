#pragma once

#include "stdafx.h"
#include "c2_allocator.h"

namespace jmq_std {

	//五种迭代器行为
	//InputIterator 只读 （++）
	//OutputIterator 只写 （++）
	//ForwardIterator	读写 （++）
	//BidirectionalIterator	双向 （++、--）
	//RandomAccessIterator	全指针算数能力（++、--、p+n、p-n、p[n],p1-p2,p1<p2等）

	struct InputIterator {};
	struct OutputIterator {};
	struct ForwardIterator :public InputIterator {};
	struct BidirectionalIterator :public ForwardIterator {};
	struct RandomAccessIterator :public BidirectionalIterator {};

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
