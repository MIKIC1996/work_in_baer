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

	template<typename _Ty1,typename _Ty2>
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
// 	template<class T1,class T2> //构造函数
// 	inline void construct(T1* p, const T2& value) {
// 		new(p) T1(value);
// 	}
// 
// 	
// 	template<class T>
// 	inline void destory(T* ptr) { //析构，版本1，就是简单调用析构函数
// 		ptr->~T();
// 	}
// 
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
		static void (*__malloc_alloc_oom_hander)(); //内存不足处理例程，设计该例程是 我们的责任
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
			result = realloc(p,n);
			if (result)return result;
		}
	}

	typedef __malloc_alloc_template<0> malloc_alloc;




	 







}







template<typename T>
struct add {
	typedef  T* pointer;
	typedef const pointer type;
};



int main()
{
	std::cout<< std::is_same<add<int>::type,  int* const>::value;

	getchar();
    return 0;
}

