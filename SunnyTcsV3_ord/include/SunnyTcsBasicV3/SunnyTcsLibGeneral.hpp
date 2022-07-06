#pragma once
#include "sunnytcsbasicv3_global.h"



//ʵ�����
namespace basic {

	//��������ֵתʮ����
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
	struct Tuple_for_each<_Function, _Tuple, 0> {	//��ֹ
		static void for_each(_Tuple& t) {
			_Function::template apply<_Tuple, 0>::application(t);
		}
	};


	//���ֻ���������㶨���Ա����ָ��
	class SunnyTcsUndefinedClass {};

	//�������������չʾ�洢 ���ֿɵ��ö��󣬰�������ָ�룬lambda���ʽ/���ʽָ�룬�º�������,��Ա����ָ�룬�ܵ���һ��ָ���С
	union  SunnyTcsCallableStorage {
		void* _M_callable_object; //�º�������ָ�����lambdaָ��
		const void* _M_const_callable_object; //const ���εķº�������ָ���lambdaָ��
		void(*_M_callable_function_ptr)();
		void (SunnyTcsUndefinedClass::* _M_callable_mem_function_ptr)();
	};


	//32λ��x86����4���ֽڣ�64λ�� 8���ֽڣ�����һ��ָ���С
	static constexpr size_t callable_storage_size = sizeof(SunnyTcsCallableStorage);


	//����һ��,������С���ڴ�Ϳ����ˣ��������������Ľṹ��ȥ�洢
	union SunnyTcsAnyData {

		void* access() { return &_M_pod_data[0]; }
		const void* access()const { return &_M_pod_data[0]; }

		template<typename _Ty> //���ڴ�����ת��Ϊ������Ҫ������
		_Ty& access() {
			return *static_cast<_Ty*>(access());
		}

		template<typename _Ty>
		const _Ty& access()const {
			return *static_cast<const _Ty*>(access());
		}

		char _M_pod_data[callable_storage_size];
	};


	//base���ṩ�����ĳ�ֿɵ��ö�����Ҫ�Ĵ洢��ȡ������������������
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
				_init_functor_aux(dst, std::forward<_Functor>(f), isStoredLocally());//�Ƿ�洢�ڱ���
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


	//�º����������lambda �����ߺ���ָ��
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
		static _Res _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::true_type) { //����Ϊ0
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			return (*func_ptr)();
		}

		static _Res _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::false_type) {
			return _handleInvoke_aux(args, waitFunc, std::integral_constant<int, 0>(), std::get<0>(*args));
		}

		template<typename _Int, typename _Ty, typename... _RestArgs>
		static _Res _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, _Int,
			_Ty&& curArg, _RestArgs&&... rest)  //���ÿɱ�ģ��������洦���������̣�չ��tuple����
		{
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "out of tuple range");
			return _handleInvoke_aux(args, waitFunc,
				std::integral_constant<int, _Int::value + 1>(),
				std::forward<_Ty>(curArg), std::get<_Int::value + 1>(*args), rest...);
		}

		template<  typename _Ty, typename... _RestArgs>
		static _Res _handleInvoke_aux(params_set* args,
			SunnyTcsAnyData* waitFunc, std::integral_constant<int, arg_count - 1>/*���׶���������*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple����չ�����
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			return (*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...); //placement new ������ֵ������resbuffer
		}

	};


	//void ����ֵ�ػ��汾
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
		static void _handleInvoke(params_set* args, SunnyTcsAnyData* waitFunc, std::true_type) {//����Ϊ0
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
			SunnyTcsAnyData* waitFunc, std::integral_constant<int, arg_count - 1>/*���׶���������*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple����չ�����
			_Functor* func_ptr = base_type::get_functor_ptr(*waitFunc);
			(*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...);
		}

	};


	//��Ա����ָ��
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
			SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::integral_constant<int, arg_count - 1>/*���׶���������*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple����չ�����
			callable_type_ptr func_ptr = (*base_type::get_functor_ptr(*waitFunc));
			_Class& obj_ref = obj->access<_Class>();
			return (obj_ref.*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...);
		}

	};


	//void �ػ�
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
			SunnyTcsAnyData* waitFunc, SunnyTcsAnyData* obj, std::integral_constant<int, arg_count - 1>/*���׶���������*/,
			_Ty&& curArg, _RestArgs&&... rest) { //tuple����չ�����
			callable_type_ptr func_ptr = (*base_type::get_functor_ptr(*waitFunc));
			_Class& obj_ref = obj->access<_Class>();
			(obj_ref.*func_ptr)(std::forward<_Ty>(curArg), std::forward<_RestArgs>(rest)...); //placement new ������ֵ������resbuffer
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
		
		//��Ƕ�ɵ��õ�Ԫ���ṩ�˵���һ���ɵ��ö��������������Ϣ
		struct CallableUnit {
			params_set _params; //������
			SunnyTcsAnyData _obj; //����ָ��
			SunnyTcsAnyData _func; //�ɵ��ö���ָ���ʵ��
			invoke_func_ptr _invoke; //������õĺ���ָ��
			manager_func_ptr _manager; //������
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
				free(_resultBuffer); //�������⣬��֪��Ϊʲô
			}

		}

		//��ѯ����
		inline std::size_t size()const { return _waitQueue.size(); }

		//��ȡ�������ָ��
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

		//submit ��Ա����
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
		void _work(std::true_type) { //�շ���ֵ
			if (_waitQueue.size() > 0) { //����δִ������
				CallableUnit& first = _waitQueue.front();
				first._invoke(&first._params, &first._func, &first._obj); //invokeִ��
				first._manager(first._func, first._func, SunnyTcsFunctionBase::destroy_func);//�Կɵ���ʵ����ͷ�
				_waitQueue.pop();
			}
		}

		void _work(std::false_type) { //�з���ֵ
			if (_waitQueue.size() > 0) { //����δִ������
				CallableUnit& first = _waitQueue.front();
				((_Res*)_resultBuffer) ->~_Res();
				memset(_resultBuffer, 0, sizeof(_Res));
				new(_resultBuffer) _Res( std::move( first._invoke(&first._params, &first._func, &first._obj)) ); //invokeִ��
				first._manager(first._func, first._func, SunnyTcsFunctionBase::destroy_func);//�Կɵ���ʵ����ͷ�
				_waitQueue.pop();
			}
		}

		//����ֵ�ݴ滺����ʼ��
		void init() {
			_init(isResultVoid());
		}

		void _init(std::false_type) {
			_resultBuffer = (void*)malloc(sizeof(result_type));
			new (_resultBuffer) result_type();//�ȹ���һ��Ĭ�ϵ�
		}

		void _init(std::true_type) {
			_resultBuffer = nullptr;
		}

		template< typename _Int, typename _Ty, typename... _RestArgs>
		void _submit_aux(CallableUnit& f, _Int, _Ty&& curArg, _RestArgs&&... rest) {
			static_assert(_Int::value >= 0 && _Int::value < arg_count, "submit out of Arg range");
			using CurArgType = typename std::tuple_element<_Int::value, params_set>::type;
			std::get<_Int::value>(f._params) = CurArgType(std::forward<_Ty>(curArg)); //һ���ṩ��curArg���Ͳ���,�޷���ʼ��CurArgType���������Զ�����
			_submit_aux(f, std::integral_constant<int, _Int::value + 1>(), std::forward<_RestArgs>(rest)...); //�ݹ���ô洢tuple�������� ����ת��
		}


		template<typename _Int>
		void _submit_aux(CallableUnit& f, _Int) { //�ύ��ֹ�׶Σ�����submit�Ĳ�������д���ʱ������������󣬱�֤�����������ڱ���׶Σ���������ʱ��ʧЧ��ȥ�ж�
			static_assert(_Int::value == arg_count, "submit error");
			_waitQueue.push(f);
		}

	protected:
		void* _resultBuffer;
		std::queue<CallableUnit> _waitQueue;
	};

}




