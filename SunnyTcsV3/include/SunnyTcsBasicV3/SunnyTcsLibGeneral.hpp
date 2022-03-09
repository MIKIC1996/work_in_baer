#pragma once
#include "sunnytcsbasicv3_global.h"



//实用类库
namespace basic {

	//二进制数值转十进制
	template<uint64_t N>
	struct SunnyTcsBinary {
		static unsigned const value
			= SunnyTcsBinary<N / 10>::value * 2 + N % 10;
	};

	template<>
	struct SunnyTcsBinary<0> {
		static constexpr unsigned long value = 0;
	};

	//define void tag
	struct SunnyTcsVoid {
	
	};


	//for_each for tuple
	template<typename _Function, typename _Tuple, int _index = std::tuple_size<_Tuple>::value - 1>
	struct Tuple_for_each {
		static void for_each(_Tuple& t) {
			static_assert(_index >= 0 && _index < std::tuple_size<_Tuple>::value, " out of tuple range.");
			Tuple_for_each<_Function, _Tuple, _index - 1>::for_each(t);
			_Function::template apply<_Tuple, _index >::application(t);
		}
	};

	template<typename _Function, typename _Tuple>
	struct Tuple_for_each<_Function, _Tuple, 0> {	//终止
		static void for_each(_Tuple& t) {
			_Function::template apply<_Tuple, 0>::application(t);
		}
	};


	//这个只是用来方便定义成员函数指针
	class SunnyTcsUndefinedClass {};

	//这个联合体用来展示存储 各种可调用对象，包括函数指针，lambda表达式/表达式指针，仿函数对象,成员函数指针，总的是一个指针大小
	union  SunnyTcsCallableStorage {
		void* _M_callable_object; //仿函数对象指针或者lambda指针
		const void* _M_const_callable_object; //const 修饰的仿函数对象指针或lambda指针
		void(*_M_callable_function_ptr)();
		void (SunnyTcsUndefinedClass::* _M_callable_mem_function_ptr)();
	};


	//32位（x86）下4个字节，64位下 8个字节，就是一个指针大小
	static constexpr size_t callable_storage_size = sizeof(SunnyTcsCallableStorage);


	//创建一个,这样大小的内存就可以了，不必真的用上面的结构体去存储
	union SunnyTcsAnyData {

		void* access() { return &_M_pod_data[0]; }
		const void* access()const { return &_M_pod_data[0]; }

		template<typename _Ty> //将内存数据转化为我们需要的类型
		_Ty& access() {
			return *static_cast<_Ty*>(access());
		}

		template<typename _Ty>
		const _Ty& access()const {
			return *static_cast<const _Ty*>(access());
		}

		char _M_pod_data[callable_storage_size];
	};


	//base中提供了针对某种可调用对象，需要的存储，取出，析构操作方法。
	class SunnyTcsFunctionBase {
	public:
		enum base_operation
		{
			get_func_ptr = 0x01,
			destroy_func = 0x02,
			clone_func = 0x03
		};

		template<typename _Functor>
		class BaseManager {
		public:
			static constexpr bool isLocalStored = sizeof(_Functor) <= callable_storage_size;
			typedef std::integral_constant<bool, isLocalStored > isStoredLocally;

			static void init_functor(SunnyTcsAnyData& dst, _Functor&& f) {
				_init_functor_aux(dst, std::forward<_Functor>(f), isStoredLocally());//是否存储于本地
			}

			static _Functor* get_functor_ptr(const SunnyTcsAnyData& data) {
				const _Functor* ptr = isLocalStored ? std::addressof(data.access<_Functor>()) : data.access<_Functor*>();
				return const_cast<_Functor*>(ptr);
			}

			static void delete_functor(SunnyTcsAnyData& dst) {
				_delete_functor_aux(dst, isStoredLocally());
			}

			static bool manager(SunnyTcsAnyData& dest, const SunnyTcsAnyData& source, base_operation op)
			{
				switch (op)
				{
				case get_func_ptr:
					dest.access<_Functor*>() = get_functor_ptr(source);
					break;

				case clone_func:
					break;

				case destroy_func:
					delete_functor(dest);
					break;
				}
				return true;
			}

		protected:
			static void _init_functor_aux(SunnyTcsAnyData& dst, _Functor&& f, std::true_type) {
				new (dst.access()) _Functor(f);
			}

			static void _init_functor_aux(SunnyTcsAnyData& dst, _Functor&& f, std::false_type) {
				dst.access<_Functor*>() = new _Functor(std::move(f));
			}

			static void _delete_functor_aux(SunnyTcsAnyData& dst, std::true_type) {
				dst.access<_Functor>().~_Functor();
			}

			static void _delete_functor_aux(SunnyTcsAnyData& dst, std::false_type) {
				delete dst.access<_Functor*>();
			}
		};

	};


	template<typename... _Args>
	class SunnyTcsFunctionHandler;


	//仿函数对象或者lambda ，或者函数指针
	template< typename _Functor, typename _Res, typename... _Args >
	class SunnyTcsFunctionHandler<_Res(_Args...), _Functor > :public SunnyTcsFunctionBase::BaseManager<_Functor> {
	private:
		static constexpr std::size_t arg_count = sizeof...(_Args);
		typedef typename std::_If< arg_count == 0, SunnyTcsVoid, std::tuple<_Args...>>::type params_set;
		typedef std::integral_constant<bool, arg_count == 0> isParamsVoid;
		typedef SunnyTcsFunctionBase::BaseManager<_Functor> base_type;

	public:
		static _Res handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj) {
			return _handleInvoke(args, waitFunc, isParamsVoid());
		}

	private:
		static _Res _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::true_type) { //参数为0
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			return (*func_ptr)();
		}

		static _Res _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::false_type) {
			return _handleInvoke_aux(args, waitFunc, std::integral_constant<int, 0>(), std::get<0>(*args));
		}

		template<typename _Int, typename _Ty, typename... _RestArgs>
		static _Res _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, _Int,
			_Ty&& curArg, _RestArgs&&... rest)  //利用可变模版参数常规处理的逆向过程，展开tuple参数
		{
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "out of tuple range");
			return _handleInvoke_aux(args, waitFunc,
				std::integral_constant<int, _Int::value + 1>(),
				std::forward<_Ty>(curArg), std::get<_Int::value + 1>(*args), rest...);
		}

		template<  typename _Ty, typename... _RestArgs>
		static _Res _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, std::integral_constant<int, arg_count - 1>/*最后阶段限制条件*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple参数展开完毕
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			return (*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...); //placement new 将返回值储存在resbuffer
		}

	};


	//void 返回值特化版本
	template< typename _Functor, typename... _Args >
	class SunnyTcsFunctionHandler<void(_Args...), _Functor > :public SunnyTcsFunctionBase::BaseManager<_Functor> {
	private:
		static constexpr std::size_t arg_count = sizeof...(_Args);
		typedef typename std::_If< arg_count == 0, SunnyTcsVoid, std::tuple<_Args...>>::type params_set;
		typedef std::integral_constant<bool, arg_count == 0> isParamsVoid;
		typedef SunnyTcsFunctionBase::BaseManager<_Functor> base_type;

	public:
		static void handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj) {
			_handleInvoke(args, waitFunc, isParamsVoid());
		}

	private:
		static void _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::true_type) {//参数为0
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			(*func_ptr)();
		}

		static void _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::false_type) {
			_handleInvoke_aux(args, waitFunc, std::integral_constant<int, 0>(), std::get<0>(*args));
		}

		template<typename _Int, typename _Ty, typename... _RestArgs>
		static void _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, _Int,
			_Ty&& curArg, _RestArgs&&... rest)
		{
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "out of tuple range");
			_handleInvoke_aux(args, waitFunc,
				std::integral_constant<int, _Int::value + 1>(),
				std::forward<_Ty>(curArg), std::get<_Int::value + 1>(*args), rest...);
		}

		template<  typename _Ty, typename... _RestArgs>
		static void _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, std::integral_constant<int, arg_count - 1>/*最后阶段限制条件*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple参数展开完毕
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			(*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...);
		}

	};


	//成员函数指针
	template< typename _Functor, typename _Class, typename _Res, typename... _Args >
	class SunnyTcsFunctionHandler<_Res(_Args...), _Functor _Class::* > :public SunnyTcsFunctionBase::BaseManager< _Functor _Class::*> {
	private:
		typedef _Functor _Class::* callable_type_ptr;

		static constexpr std::size_t arg_count = sizeof...(_Args);
		typedef typename std::_If< arg_count == 0, SunnyTcsVoid, std::tuple<_Args...>>::type params_set;
		typedef std::integral_constant<bool, arg_count == 0> isParamsVoid;
		typedef SunnyTcsFunctionBase::BaseManager<callable_type_ptr> base_type;

	public:
		static _Res handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj) {
			return _handleInvoke(args, waitFunc, obj, isParamsVoid());
		}


	private:
		static _Res _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::true_type) {
			_Functor _Class::* func_ptr = (*base_type::get_functor_ptr(*waitFunc));
			_Class& obj_ref = obj->access<_Class>();
			return (obj_ref.*func_ptr)();
		}

		static _Res _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::false_type) {
			return _handleInvoke_aux(args, waitFunc, obj, std::integral_constant<int, 0>(), std::get<0>(*args));
		}

		template<typename _Int, typename _Ty, typename... _RestArgs>
		static _Res _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, _Int,
			_Ty&& curArg, _RestArgs&&... rest)
		{
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "out of tuple range");
			return _handleInvoke_aux(args, waitFunc, obj,
				std::integral_constant<int, _Int::value + 1>(),
				std::forward<_Ty>(curArg), std::get<_Int::value + 1>(*args), rest...);
		}


		template<  typename _Ty, typename... _RestArgs>
		static _Res _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::integral_constant<int, arg_count - 1>/*最后阶段限制条件*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple参数展开完毕
			callable_type_ptr func_ptr = (*base_type::get_functor_ptr(*waitFunc));
			_Class& obj_ref = obj->access<_Class>();
			return (obj_ref.*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...);
		}

	};


	//void 特化
	template< typename _Functor, typename _Class, typename... _Args >
	class SunnyTcsFunctionHandler<void(_Args...), _Functor _Class::* > :public SunnyTcsFunctionBase::BaseManager< _Functor _Class::*> {
	private:
		typedef _Functor _Class::* callable_type_ptr;

		static constexpr std::size_t arg_count = sizeof...(_Args);
		typedef typename std::_If< arg_count == 0, SunnyTcsVoid, std::tuple<_Args...>>::type params_set;
		typedef std::integral_constant<bool, arg_count == 0> isParamsVoid;
		typedef SunnyTcsFunctionBase::BaseManager<_Functor _Class::*> base_type;

	public:
		static void handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj) {
			_handleInvoke(args, waitFunc, obj, isParamsVoid());
		}

	private:
		static void _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::true_type) {
			_Functor _Class::* func_ptr = *(base_type::get_functor_ptr(*waitFunc));
			_Class& obj_ref = obj->access<_Class>();
			(obj_ref.*func_ptr)();
		}

		static void _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::false_type) {
			_handleInvoke_aux(args, waitFunc, obj, std::integral_constant<int, 0>(), std::get<0>(*args));
		}

		template<typename _Int, typename _Ty, typename... _RestArgs>
		static void _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, _Int,
			_Ty&& curArg, _RestArgs&&... rest)
		{
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "out of tuple range");
			_handleInvoke_aux(args, waitFunc, obj,
				std::integral_constant<int, _Int::value + 1>(),
				std::forward<_Ty>(curArg), std::get<_Int::value + 1>(*args), rest...);
		}

		template<  typename _Ty, typename... _RestArgs>
		static void _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::integral_constant<int, arg_count - 1>/*最后阶段限制条件*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple参数展开完毕
			callable_type_ptr func_ptr = (*base_type::get_functor_ptr(*waitFunc));
			_Class& obj_ref = obj->access<_Class>();
			(obj_ref.*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...); //placement new 将返回值储存在resbuffer
		}

	};


	template<typename _Res, typename... _Args>
	class SunnyTcsThreadSeed_basic;


	template<typename _Res, typename... _Args>
	class SunnyTcsThreadSeed_basic<_Res(_Args...)>
	{
	public:
		static constexpr std::size_t arg_count = sizeof...(_Args);
		typedef typename std::_If< arg_count == 0, SunnyTcsVoid, std::tuple<_Args...>>::type params_set;
		typedef std::integral_constant<bool, arg_count == 0> isParamsVoid;
		typedef _Res result_type;
		typedef typename std::_If<std::is_same<void, result_type>::value, std::true_type, std::false_type>::type isResultVoid;
		typedef _Res signature_type(_Args...);
		typedef result_type(*invoke_func_ptr) (params_set* args, SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj);
		typedef bool(*manager_func_ptr)(SunnyTcsAnyData& dest, const SunnyTcsAnyData& source, SunnyTcsFunctionBase::base_operation op);
		
		//内嵌可调用单元，提供了调用一个可调用对象所需的所有信息
		struct CallableUnit {
			params_set _params; //参数集
			SunnyTcsAnyData _obj; //对象指针
			SunnyTcsAnyData _func; //可调用对象指针或实例
			invoke_func_ptr _invoke; //负责调用的函数指针
			manager_func_ptr _manager; //管理者
		};

		//ctor
		SunnyTcsThreadSeed_basic() {
			init();
		}

		//dtor
		virtual ~SunnyTcsThreadSeed_basic() {
			while (!_waitQueue.empty()) {
				_waitQueue.pop();
			}
			if (_resultBuffer) {
				((result_type*)_resultBuffer) ->~result_type();
				free(_resultBuffer); //这有问题，不知道为什么
			}

		}

		//查询负载
		inline std::size_t size()const { return _waitQueue.size(); }

		//获取结果缓存指针
		inline void* getResultPtr() { return _resultBuffer; }


		//submit
		template<typename _Function, typename... _RestArgs>
		void submit(_Function&& f, _RestArgs&&... rest) {
			using Handler = SunnyTcsFunctionHandler<signature_type, _Function>;
			CallableUnit unit;
			memset(unit._obj.access(), 0, callable_storage_size); // obj
			Handler::init_functor(unit._func, std::forward<_Function>(f)); //func
			unit._invoke = &(Handler::handleInvoke); //invoke
			unit._manager = &(Handler::manager);//_manager
			_submit_aux(unit, std::integral_constant<int, 0>(), std::forward<_RestArgs>(rest) ...);//params
		}

		//submit 成员函数
		template<typename _Class, typename... _RestArgs>
		void submit(signature_type _Class::* f, _Class* obj_ptr, _RestArgs... rest) {
			using Tmp_functor = signature_type _Class::*;
			using Handler = SunnyTcsFunctionHandler<signature_type, Tmp_functor>;
			CallableUnit unit;
			unit._obj.access<_Class*>() = obj_ptr;// obj
			Handler::init_functor(unit._func, std::forward<Tmp_functor>(f)); //func
			unit._invoke = &(Handler::handleInvoke); //invoke
			unit._manager = &(Handler::manager);//_manager
			_submit_aux(unit, std::integral_constant<int, 0>(), std::forward<_RestArgs>(rest) ...);//params
		}

		void work() {
			_work(isResultVoid());
		}

	protected:
		void _work(std::true_type) { //空返回值
			if (_waitQueue.size() > 0) { //存在未执行任务
				CallableUnit& first = _waitQueue.front();
				first._invoke(&first._params, &first._func, &first._obj); //invoke执行
				first._manager(first._func, first._func, SunnyTcsFunctionBase::destroy_func);//对可调用实体的释放
				_waitQueue.pop();
			}
		}

		void _work(std::false_type) { //有返回值
			if (_waitQueue.size() > 0) { //存在未执行任务
				CallableUnit& first = _waitQueue.front();
				((_Res*)_resultBuffer) ->~_Res();
				memset(_resultBuffer, 0, sizeof(_Res));
				new(_resultBuffer) _Res( std::move( first._invoke(&first._params, &first._func, &first._obj)) ); //invoke执行
				first._manager(first._func, first._func, SunnyTcsFunctionBase::destroy_func);//对可调用实体的释放
				_waitQueue.pop();
			}
		}

		//返回值暂存缓区初始化
		void init() {
			_init(isResultVoid());
		}

		void _init(std::false_type) {
			_resultBuffer = (void*)malloc(sizeof(result_type));
			new (_resultBuffer) result_type();//先构造一个默认的
		}

		void _init(std::true_type) {
			_resultBuffer = nullptr;
		}

		template< typename _Int, typename _Ty, typename... _RestArgs>
		void _submit_aux(CallableUnit& f, _Int, _Ty&& curArg, _RestArgs&&... rest) {
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "submit out of Arg range");
			using CurArgType = typename std::tuple_element<_Int::value, params_set>::type;
			std::get<_Int::value>(f._params) = CurArgType(std::forward<_Ty>(curArg)); //一旦提供的curArg类型不对,无法初始化CurArgType，编译器自动报错
			_submit_aux(f, std::integral_constant<int, _Int::value + 1>(), std::forward<_RestArgs>(rest)...); //递归调用存储tuple，将参数 完美转发
		}


		template<typename _Int>
		void _submit_aux(CallableUnit& f, _Int) { //提交中止阶段，在你submit的参数数量写错的时候会产生编译错误，保证将错误消灭于编译阶段，无需运行时损失效率去判断
			static_assert(_Int::value == arg_count, "submit error");
			_waitQueue.push(f);
		}

	protected:
		void* _resultBuffer;
		std::queue<CallableUnit> _waitQueue;
	};

}




