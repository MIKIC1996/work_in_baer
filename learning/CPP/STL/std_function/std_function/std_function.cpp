// std_function.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <functional>
#include <mutex>


//std::functionʵ��
/*

namespace jmq_std {

	//���к���ģ�治���������еģ��������decltype,�õ� _Functor �� �ɵ������͵�
	template<typename _Functor>
	inline _Functor& __callable_functor(_Functor& __f) 
	{
		return __f;
	}

	//����ǳ�Ա������
	template<typename _Member, typename _Class>
	inline _Mem_fn<_Member _Class::*> __callable_functor(_Member _Class::* &__p) 
		//��Ա����ָ���޷�ֱ�ӵ��ã������ͽ���Ϊ std::men_fn�� ��װ���ͣ���ʹ�ó�Ա����ָ���װ��Ϊ�ɵ��ö���
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







	//���ֻ���������㶨�庯��ָ��
	class _Undefined_class{};

	//�������������չʾ�洢 ���ֿɵ��ö��󣬰�������ָ�룬lambda���ʽ���º�������
	//��Ա����ָ��
	union  _callable_storage {
		void* _M_callable_object; //�º�������ָ�����lambdaָ��
		const void* _M_const_callable_object; //const ���εķº�������ָ���lambdaָ��
		void(*_M_callable_function_ptr)();
		void (_Undefined_class::* _M_callable_mem_function_ptr)();
	};

	//��һ�����ĳߴ�, 32λ��x86����4���ֽڣ�64λ�� 8���ֽڣ�����һ��ָ���С
	static constexpr size_t _callable_storage_size = sizeof(_callable_storage);


	//��һ����ֻ��չʾ�ã�����������Ҫ�ģ�������������Ĵ�С��Ȼ�󴴽�һ��
	//������С���ڴ�Ϳ����ˣ��������������Ľṹ��ȥ�洢
	union _Any_callable_data {

		void* _M_access() { return &_M_pod_data[0]; }
		const void* _M_access()const { return &_M_pod_data[0]; }

		template<typename _Ty> //���ڴ�����ת��Ϊ������Ҫ������
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
		//���_Function_base�Ĵ洢����ֻ��һ��_Any_callable_data��
		static const std::size_t _max_size = _callable_storage_size;
		
		//��Ƕԭ��������������_Any_callable_data �� _M_access�����ؿɵ��ö���ָ��
		template<typename _Functor>
		class _Base_manager {
			
			//�Ƿ�ֱ�Ӵ洢��
			//_Any_callable_data�У�
			static constexpr bool _store_locally =
				sizeof(_Functor) <= _max_size;
				
			typedef std::integral_constant<bool, _store_locally> _local_storage;
			
			static _Functor* _M_get_pointer(const _Any_callable_data& _src) {
				const _Functor* ptr = _store_locally ?
					std::addressof(_src._M_access<_Functor>()) : //���ڱ��أ�src��
					_src._M_access<const _Functor*>(); //���ڶ��ϣ�src�����ָ��
				return const_cast<_Functor* >
			}

		};





		_Any_callable_data _M_Functor;//ʵ�ʴ洢�ɵ��ö���ʵ��

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

