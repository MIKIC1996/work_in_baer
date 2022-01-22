// std_function.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <functional>
#include <mutex>


//std::function实现
/*

namespace jmq_std {

	//下列函数模版不是用来运行的，而是配合decltype,得到 _Functor 的 可调用类型的
	template<typename _Functor>
	inline _Functor& __callable_functor(_Functor& __f) 
	{
		return __f;
	}

	//如果是成员函数，
	template<typename _Member, typename _Class>
	inline _Mem_fn<_Member _Class::*> __callable_functor(_Member _Class::* &__p) 
		//成员函数指针无法直接调用，将类型解析为 std::men_fn的 包装类型，就使得成员函数指针包装成为可调用对象
	{
		return std::mem_fn(__p);
	}

	template<typename _Member, typename _Class>
	inline _Mem_fn<_Member _Class::*> __callable_functor(_Member _Class::* const &__p)
	{
		return std::mem_fn(__p);
	}

	template<typename _Member, typename _Class>
	inline _Mem_fn<_Member _Class::*> __callable_functor(_Member _Class::* volatile &__p)
	{
		return std::mem_fn(__p);
	}

	template<typename _Member, typename _Class>
	inline _Mem_fn<_Member _Class::*> __callable_functor(_Member _Class::* const volatile &__p)
	{
		return std::mem_fn(__p);
	}







	//这个只是用来方便定义函数指针
	class _Undefined_class{};

	//这个联合体用来展示存储 各种可调用对象，包括函数指针，lambda表达式，仿函数对象
	//成员函数指针
	union  _callable_storage {
		void* _M_callable_object; //仿函数对象指针或者lambda指针
		const void* _M_const_callable_object; //const 修饰的仿函数对象指针或lambda指针
		void(*_M_callable_function_ptr)();
		void (_Undefined_class::* _M_callable_mem_function_ptr)();
	};

	//看一下他的尺寸, 32位（x86）下4个字节，64位下 8个字节，就是一个指针大小
	static constexpr size_t _callable_storage_size = sizeof(_callable_storage);


	//上一个类只是展示用，我们真正需要的，是这种联合体的大小，然后创建一个
	//这样大小的内存就可以了，不必真的用上面的结构体去存储
	union _Any_callable_data {

		void* _M_access() { return &_M_pod_data[0]; }
		const void* _M_access()const { return &_M_pod_data[0]; }

		template<typename _Ty> //将内存数据转化为我们需要的类型
		_Ty& _M_access() {
			return *static_cast<_Ty*>(_M_access());
		}

		template<typename _Ty>
		const _Ty& _M_access() {
			return *static_cast<const _Ty*>(_M_access());
		}

		char _M_pod_data[_callable_storage_size];
	};







	class _Function_base {
	public:
		//这个_Function_base的存储数量只有一个_Any_callable_data；
		static const std::size_t _max_size = _callable_storage_size;
		
		//内嵌原函数，用来调用_Any_callable_data 的 _M_access，返回可调用对象指针
		template<typename _Functor>
		class _Base_manager {
			
			//是否直接存储在
			//_Any_callable_data中，
			static constexpr bool _store_locally =
				sizeof(_Functor) <= _max_size;
				
			typedef std::integral_constant<bool, _store_locally> _local_storage;
			
			static _Functor* _M_get_pointer(const _Any_callable_data& _src) {
				const _Functor* ptr = _store_locally ?
					std::addressof(_src._M_access<_Functor>()) : //存在本地，src上
					_src._M_access<const _Functor*>(); //存在堆上，src存的是指针
				return const_cast<_Functor* >
			}

		};





		_Any_callable_data _M_Functor;//实际存储可调用对象实体

	};


	template< typename... _Args>
	class function;



	template<typename _Res, typename... _ArgTypes>
	class function<_Res(_ArgTypes...)> : private _Function_base
	{
		typedef _Res _Signature_type(_ArgTypes...);

		template<typename _Functor>
		using _Invoke = decltype(__callable_functor(std::declval<_Functor&>())(std::declval<_ArgTypes>()...));

		template<typename _Functor>
		using _Callable = __check_func_return_type<_Invoke<_Functor>, _Res>;

		template<typename _Cond, typename _Tp>
		using _Requires = typename enable_if<_Cond::value, _Tp>::type;

	public:
		typedef _Res result_type;

		function() noexcept
			:_Function_base()
		{
		}

		function(nullptr_t) noexcept
			: _Function_base()
		{
		}

		template<typename _Res, typename... _ArgTypes>
		function(const function& __x)
			: _Function_base()
		{
			if (static_cast<bool>(__x))
			{
				_M_invoker = __x._M_invoker;
				_M_manager = __x._M_manager;
				__x._M_manager(_M_functor, __x._M_functor, __clone_functor);
			}
		}

		function(function&& __x)
			:_Function_base()
		{
			__x.swap(*this);
		}

		template<typename _Functor, typename = _Requires<_Callable<_Functor>, void>>
		function(_Functor __f)
		{
			typedef _Function_handler<_Signature_type, _Functor> _My_handler;

			if (_My_handler::_M_not_empty_function(__f))
			{
				_My_handler::_M_init_functor(_M_functor, std::move(__f));
				_M_invoker = &_My_handler::_M_invoke;
				_M_manager = &_My_handler::_M_manager;
			}
		}

		function& operator=(const function& __x)
		{
			function(__x).swap(*this);
			return *this;
		}

		function& operator=(function&& __x)
		{
			function(std::move(__x)).swap(*this);
			return *this;
		}

		function& operator=(nullptr_t)
		{
			if (_M_manager)
			{
				_M_manager(_M_functor, _M_functor, __destroy_functor);
				_M_manager = 0;
				_M_invoker = 0;
			}
			return *this;
		}

		template<typename _Functor>
		_Requires<_Callable<_Functor>, function&> operator=(_Functor&& __f)
		{
			function(std::forward<_Functor>(__f)).swap(*this);
			return *this;
		}

		template<typename _Functor>
		function& operator=(reference_wrapper<_Functor> __f) noexcept
		{
			function(__f).swap(*this);
			return *this;
		}

		void swap(function& __x)
		{
			std::swap(_M_functor, __x._M_functor);
			std::swap(_M_manager, __x._M_manager);
			std::swap(_M_invoker, __x._M_invoker);
		}

		explicit operator bool() const noexcept
		{
			return !_M_empty();
		}

		_Res operator()(_ArgTypes... __args) const;
		{
			if (_M_empty())
				__throw_bad_function_call();
			return _M_invoker(_M_functor, std::forward<_ArgTypes>(__args)...);
		}

	private:
		typedef _Res(*_Invoker_type)(const _Any_data&, _ArgTypes...);
		_Invoker_type _M_invoker;

	}














}




*/



int add(int a, int b) {
	std::cout << a + b << std::endl;
	return a + b;
}


void print(int a, int b) {
	std::cout << a + b << std::endl;
}

void printc() {
	std::cout << "hello meta" << std::endl;
}

int getvalue() {
	return 2;
}

class AA {

public:
	int add(int a, int b) {

		std::cout << a + b << std::endl;
		return a + b;
	}

	void print(int a, int b) {
		std::cout << a + b << std::endl;
	}


	void printc() {
		std::cout << "hello meta" << std::endl;
	}

	int getvalue() {
		return 2;
	}
};



// struct Tuple_iterator_end {
// 	static constexpr int index = 10000;
// 	typedef void type;
// 	typedef void next;
// 	typedef void prior;
// };
// 
// template<typename _Tuple, int _index>
// struct Tuple_iterator {
// 
// 	static constexpr int index = _index;
// 	typedef typename std::tuple_element<_index, _Tuple>::type type;
// 
// 
// 	typedef typename  std::_If< index == std::tuple_size<_Tuple>::value , Tuple_iterator<_Tuple, _index >, Tuple_iterator<_Tuple, _index + 1> >::type  next;
// 	typedef typename  Tuple_iterator<_Tuple, _index - 1> prior;
// };
// 
// 
// template<typename _Tuple>
// struct Tuple_iterator<_Tuple,0> {
// 	static constexpr int index = 0;
// 	typedef typename std::tuple_element<0, _Tuple>::type type;
// 
// 	typedef typename Tuple_iterator<_Tuple, 1> next;
// };
// 
// 
// 
// 
// template<typename Iter_first , typename Iter_last ,typename _TargetType>
// struct Tuple_find {
// 
// 	typedef typename
// 		std::_If<  std::is_same < typename Iter_first::type, _TargetType >::value,
// 		Iter_first,
// 		typename Tuple_find< typename Iter_first::next, Iter_last , _TargetType>::type
// 		>::type type;
// 	
// 
// 		
// };
// 
// 
// typedef std::tuple<int, char, double> sample;
// 


int main()
{
	

	std::mutex lock1;
	std::mutex lock2;

	std::thread t1([&lock1, &lock2]()->void { 
		std::lock(lock1, lock2); 
		std::lock_guard<std::mutex> g1(lock1,std::adopt_lock );
		std::lock_guard<std::mutex> g2(lock2, std::adopt_lock);
		std::cout << "t1" << std::endl; });
	
	std::thread t2([&lock1, &lock2]()->void { 
		std::lock(lock1, lock2);
		std::lock_guard<std::mutex> g1(lock1, std::adopt_lock);
		std::lock_guard<std::mutex> g2(lock2, std::adopt_lock);
		std::cout << "t2" << std::endl; });

 	getchar();
    return 0;
}

