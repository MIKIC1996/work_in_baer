#pragma once


#include "stdafx.h"
#include <type_traits>

namespace jmq_std {


	struct __true_type {};
	struct __false_type {};
	
	template<typename T>
	struct __type_traits {
		typedef __true_type this_dummy_member_must_be_first;
		
		typedef __false_type has_trivial_default_constructor;
		typedef __false_type has_trivial_copy_constructor;
		typedef __false_type has_trivial_assignment_operator;
		typedef __false_type has_trivial_destructor;
		typedef __false_type is_POD_type;
	};


	template<typename T>
	struct __iterator_traits {
		typedef typename T::iterator_categoty	iterator_categoty;
		typedef typename T::value_type value_type;
		typedef typename T::difference_type difference_type;
		typedef typename T::pointer pointer;
		typedef typename T::reference reference;
	};


	//--------------------------------------------------SGI STL 空间配置器，非泛型---------------------------------------------------
	template<class T1, class T2> //构造函数
	inline void construct(T1* p, const T2& value) {
		new(p) T1(value);
	}


	template<class T>
	inline void destory(T* ptr) { //析构，版本1，就是简单调用析构函数
		ptr->~T();
	}

	 
	template<class ForwardIter>
	inline void destory(ForwardIter first, ForwardIter last) { //第二版本
		typedef typename iterator_traits<ForwardIterator>::value_type value_type;
		value_type* ptr;
		__destory(first, last, ptr);
	}

	
	template<class ForwardIter,class T>
	inline void __destory(ForwardIter first, ForwardIter last, T*) {
		typedef typename __type_traits<T>::has_trivial_destructor has_trivial_destructor;
		__destory_aux(first, last, has_trivial_destructor());
	}

	template<typename ForwardIter>
	inline void __destory_aux(ForwardIter first, ForwardIter last, __false_type) {
		for (; first < last; ++first) {
			destory(first);
		}
	}

	template<typename ForwardIter>
	inline void __destory_aux(ForwardIter first, ForwardIter last, __false_type) {
		//无需调用析构函数
	}



	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator _First, Size _Count, const T& _Val) {
		__uninitialized_fill_n(_First, _Count, _Val, value_type(_Val));
	}

	template<class ForwardIterator, class Size, class T, class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator _First, Size _Count, const T& _Val, T1) {

	}

	template<class ForwardIterator, class Size, class T, class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator _First, Size _Count, const T& _Val, T1*) {

	}



	//第一级配置器 __malloc_alloc_template / malloc_alloc --------------------
#define __THROW_BAD_ALLOC_JMQ throw bad_alloc;

	template<int inst>
	class __malloc_alloc_template {

	public:
		static void* allocate(size_t n) {
			void* result = malloc(n);
			if (nullptr == result) {
				result = oom_malloc(n);
			}
			return result;
		}

		static void deallocate(void* p, size_t) {
			free(p);
		}

		static void* reallocate(void* p, size_t, size_t new_sz) {
			void* result = realloc(p, new_sz);
			if (nullptr == result) {
				result = oom_realloc(p, new_sz);
			}
			return result;
		}

		static void(*set_malloc_hander(void(*f)()))() {
			void(*old)() = __malloc_alloc_oom_hander;
			__malloc_alloc_oom_hander = f;
			return old;
		}



	private:
		//用来处理oom 的情况 的函数指针 
		static void* oom_malloc(size_t);
		static void* oom_realloc(void*, size_t);
		static void(*__malloc_alloc_oom_hander)(); //内存不足处理例程，设计该例程是 我们的责任
	};




	typedef __malloc_alloc_template<0> malloc_alloc;






	//第二级配置器，主要用于管理 小内存 的自由链表----------------------
	enum { __ALIGN = 8 };
	enum { __MAX_BYTES = 128 };
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN }; //自由链表个数

	union obj //自由链表节点的构造
	{
		union obj* free_list_link;
		char client_data[1];
	};

	template<int inst>
	class __default_alloc_template {
	public:



		static void* allocate(size_t n);
		static void deallocate(void* p, size_t n);
		static void* reallocate(void* p, size_t old_sz, size_t new_sz);
		static void* refill(size_t n);

		//从内存池中取出 size*nobjs 字节的内存，如果内存池空间不足，实际nobjs会变少
		static char* chunk_alloc(size_t size, int& nobjs);


	private:
		static size_t round_up(size_t bytes) //将bytes上调到8的倍数
		{
			return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);        //    (x + 00000111 )   &  11111000
		}


		static size_t freeList_index(size_t bytes) {//根据bytes 数 得到 自由链表index
			return ((bytes + __ALIGN - 1) / __ALIGN) - 1;
		}


		static obj* volatile free_list[__NFREELISTS]; //16 个自由链表

		static char* start_free;
		static char* end_free;
		static size_t heap_size;
	};


	
	//上述两种空间配置器，并不符合stl标准，所以使用下面的配接器分装
	template<class T ,class Alloc>
	class simple_alloc {
	public:
		static T* allocate(size_t n) {
			return 0 == n ? nullptr : (T*) Alloc::allocate(n * sizeof(T));
		}

		static T* allocate(void) {
			return (T*)Alloc::allocate(sizeof(T));
		}

		static void deallocate(T* p, size_t n) {
			if (0 != n) {
				Alloc::deallocate(p, n * sizeof(T));
			}
		}

		static void deallocate(T* p){
			Alloc::deallocate(p, sizeof(T));
		}

	};



}

