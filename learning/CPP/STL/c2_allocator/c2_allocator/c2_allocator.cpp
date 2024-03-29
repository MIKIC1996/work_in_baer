// c2_allocator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace jmq_std {

	//-----------------------------------------------一个基本的空间配置器-----------------------------------------------------------
	template <typename _Ty>
	inline _Ty* _allocate(ptrdiff_t size, _Ty*) { //分配内存
		set_new_handler(nullptr); //参数类型 void (*f)() ,在operator new 失败的时候，调用，如果传空指针，就直接抛出bad_alloc
		_Ty* tmp = (_Ty*)(::operator new((size_t)(size * sizeof(_Ty))));
		if (nullptr == tmp) {
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}

	/*
	一.new
		new operator就是new操作符，不能被重载，假如A是一个类，那么A * a = new A; 实际上执行如下3个过程。
		（1）调用operator new分配内存，operator new (sizeof(A))
		（2）调用构造函数生成类对象，A::A()
		（3）返回相应指针
		事实上，分配内存这一操作就是由operator new(size_t)来完成的，如果类A重载了operator new，那么将调用A::operator new(size_t)，否则调用全局::operator new(size_t)，后者由C++默认提供。

	二.operator new
		operator new是函数，分为三种形式（前2种不调用构造函数，这点区别于new operator）：
		void* operator new (std::size_t size) throw (std::bad_alloc);
		void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
		void* operator new (std::size_t size, void* ptr) throw();
		第一种分配size个字节的存储空间，并将对象类型进行内存对齐。如果成功，返回一个非空的指针指向首地址。失败抛出bad_alloc异常。
		第二种在分配失败时不抛出异常，它返回一个NULL指针。
		第三种是placement new版本，它本质上是对operator new的重载，定义于#include <new>中。它不分配内存，调用合适的构造函数在ptr所指的地方构造一个对象，之后返回实参指针ptr。
		第一、第二个版本可以被用户重载，定义自己的版本，第三种placement new不可重载。
		A* a = new A; //调用第一种
		A* a = new(std::nothrow) A; //调用第二种
		new (p)A(); //调用第三种
		new (p)A()调用placement new之后，还会在p上调用A::A()，这里的p可以是堆中动态分配的内存，也可以是栈中缓冲。
	*/


	template <typename _Ty>
	inline void _deallocate(_Ty* buffer) { //释放内存
		::operator delete (buffer);
	}

	template<typename _Ty1, typename _Ty2>
	inline void _construct(_Ty1* p, const _Ty2& value) { //对象构建
		new(p) _Ty1(value);
	}

	template <typename _Ty>
	inline void _destory(_Ty* ptr) { //对象析构
		ptr->~_Ty();
	}


	template<typename _Ty>
	class allocator {
	public:
		//stl规范
		typedef _Ty value_type;
		typedef _Ty* pointer;
		typedef const _Ty* const_pointer;

	};




	//--------------------------------------------------SGI STL 空间配置器，非泛型---------------------------------------------------
	template<class T1,class T2> //构造函数
	inline void construct(T1* p, const T2& value) {
		new(p) T1(value);
	}

	
	template<class T>
	inline void destory(T* ptr) { //析构，版本1，就是简单调用析构函数
		ptr->~T();
	}

// 
// 
// 	template<class ForwardIter>
// 	inline void destory(ForwardIter first, ForwardIter last) { //第二版本
// 		__destory
// 	}
// 
// 	template<class T>
// 	auto value_type(T& obj) ->decltype(type_trait<T>::value_type())
// 	{
// 		return type_trait<T>::value_type();
// 	}
// 
// 
// 	template<class ForwardIter,class T>
// 	inline void __destory(ForwardIter first, ForwardIter last, T) {}
// 



	template<typename T>
	auto value_type(const T& obj)->decltype(typename T::value_type())
	{
		return typename T::value_type();
	}

	template<typename T>//指针特化
	T value_type(T* obj)
	{
		return T();
	}

	
	template<class ForwardIterator , class Size , class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator _First, Size _Count, const T& _Val) {
		__uninitialized_fill_n(_First, _Count, _Val, value_type(_Val));
	}
	
	template<class ForwardIterator, class Size, class T,class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator _First, Size _Count, const T& _Val,T1 ) {

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


	template<int inst>
	void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_hander)() = nullptr;

	template<int inst>
	void* __malloc_alloc_template<inst>::oom_malloc(size_t n) {
		void(*my_malloc_hander)();
		void * result;

		for (;;) { //不断的重新配置
			my_malloc_hander = __malloc_alloc_oom_hander;
			if (nullptr = my_malloc_hander) {
				__THROW_BAD_ALLOC_JMQ;
			}
			(*my_malloc_hander)(); //调用处理例程，企图释放内存
			result = malloc(n);
			if (result)return result;
		}

	}

	template<int inst>
	void* __malloc_alloc_template<inst>::oom_realloc(void* p, size_t n) {
		void(*my_malloc_hander)();
		void * result;

		for (;;) { //不断的重新配置
			my_malloc_hander = __malloc_alloc_oom_hander;
			if (nullptr = my_malloc_hander) {
				__THROW_BAD_ALLOC_JMQ;
			}
			(*my_malloc_hander)(); //调用处理例程，企图释放内存
			result = realloc(p, n);
			if (result)return result;
		}
	}

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


	template<int inst>
	char* __default_alloc_template<inst>::start_free = nullptr;

	template<int inst>
	char* __default_alloc_template<inst>::end_free = nullptr;

	template<int inst>
	size_t __default_alloc_template<inst>::heap_size = 0;

	template<int inst>
	 obj* volatile  __default_alloc_template<inst>::free_list[__NFREELISTS] ={
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


	 template<int inst>
	 void* __default_alloc_template<inst>::allocate(size_t n) {
		 obj* volatile * my_free_list;
		 obj* result;

		 if (n > (size_t)(__MAX_BYTES)) {
			 return malloc_alloc::allocate(n);
		 }

		 my_free_list = free_list + freeList_index(n);
		 result = *my_free_list;
		 if (nullptr == result) {
			 //没有可用的free list ,重新填充free_list
			 void* r = refill(round_up(n));
			 return r;
		 }
		 *my_free_list = result->free_list_link;
		 return result;
	 }

	 template<int inst>
	 void __default_alloc_template<inst> ::deallocate(void* p, size_t n)
	 {
		 Q_ASSERT(p);
		 obj* q = (obj*)p;
		 obj* volatile *my_free_list;

		 //寻找合适的
		 if (n > (size_t)__MAX_BYTES) {
			 malloc_alloc::deallocate(p, n);
			 return;
		 }
		 //回收区块
		 my_free_list = free_list + freeList_index(n);
		 q->free_list_link = *my_free_list;
		 *my_free_list = q;
	 }


	 template<int inst>
	 void* __default_alloc_template<inst>::refill(size_t n) {
		 int nobjs = 20;
		 char* chunk = chunk_alloc(n, nobjs);
		 obj* volatile * my_free_list = nullptr;
		 obj* result=nullptr;
		 obj* current_obj = nullptr, *next_obj = nullptr;
		 int i=0;
		 
		 if (1 == nobjs) { //只获得了一个，直接返回给客端，不填充free_list
			 return (obj*)chunk;
		 }

		 my_free_list = free_list + freeList_index(n);
		 result = (obj*)(chunk);
		 *my_free_list = next_obj = (obj*)(chunk + n);
		 for (i = 1;; i++) {
			 current_obj = next_obj;
			 next_obj = (obj*)((char*)next_obj + n);
			 if (nobjs - 1 == i) {
				 current_obj->free_list_link = nullptr; //对尾最后一个obj的free_list_link总是设为0
				 break;
			 }
			 else {
				 current_obj->free_list_link = next_obj;
			 }
		 }
		 return result;
	 }
	 


	 template<int inst>
	 char* __default_alloc_template<inst>::chunk_alloc(size_t size, int& nobjs)
	 {
		 char* result = nullptr;
		 size_t total_bytes = size * nobjs;
		 size_t bytes_left = end_free - start_free;
		 if (bytes_left > total_bytes) {
			//内存足够
			 result = start_free;
			 start_free += total_bytes;
			 return result;
		 }
		 else if (bytes_left > size) {
			//足够供应一个以上 ，nobjs个以下
			 nobjs = bytes_left / size; 
			 total_bytes = nobjs * size;
			 result = start_free;
			 //同上
			 result = start_free;
			 start_free += total_bytes;
			 return result;
		 }
		 else {
			 //一个都不够
			 //先处理残余空间，编入free_list
			 if (bytes_left > 0) {
				 obj * volatile * my_free_list = free_list + freeList_index(bytes_left);
				 ((obj*)start_free)->free_list_link = *my_free_list;
				 *my_free_list = (obj*)start_free;
			 }
			 
			 //扩充内存池
			 size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
			 start_free = (char*)malloc(bytes_to_get);

			 obj* volatile * my_free_list = nullptr;
			 obj* p = nullptr;

			 if (nullptr == start_free) {//malloc失败，那么从自己的自由链表中看看有没有合适的
				 int i = 0;
				 
				 for (i = size; i < __MAX_BYTES; i += __ALIGN) {
					 my_free_list = free_list + freeList_index(i);
					 p = *my_free_list;
					 if (nullptr != p) {
						 *my_free_list = p->free_list_link; //把p取出
						 start_free = (char*) p;
						 end_free = start_free += i;
						 return  chunk_alloc(size, nobjs);
					 }
				}

			}
			 end_free = 0;//山穷水尽
			 start_free = (char*) (malloc_alloc::allocate(bytes_to_get));//要么成功，要么异常
			 heap_size += bytes_to_get;
			 end_free = start_free + bytes_to_get;
			 return (chunk_alloc(size, nobjs));
		 }
	 }






}








int main()
{


	getchar();
    return 0;
}

