#pragma once
#include "basic_deps.h"


//OS
#define TCS_OS_WIN32

//�⵼��
#define BASIC_EXPORT __declspec(dllexport)

//�ӿڼ��ǿ��
#define STRICT_INTERFACE_CHECK


#define TCS_TO_STR_2(expr) TCS_TO_STR_1(expr)  
#define TCS_TO_STR_1(expr) TCS_TO_STR(expr)
#define TCS_TO_STR(expr) #expr

//��ӿڹ淶��̬���

#define TCS_IS_HAS_INSERTED_TYPE(_Mark,_InsertType) \
template<typename _Ty>\
struct SunnyTcsHasInsertedType_##_Mark {\
	template<typename _T, typename _T:: _InsertType * = nullptr >\
	static constexpr bool check(_T*) { return true; }\
	static constexpr bool check(...) { return false; }\
	static constexpr bool value = check(static_cast<_Ty*>(0));\
};

#define TCS_CHECK_HAS_INSERTED_TYPE(_Mark,_Type)\
SunnyTcsHasInsertedType_##_Mark<_Type>::value


#define TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(_Type,_Mark,_InsertedType)\
TCS_IS_HAS_INSERTED_TYPE(_Mark,_InsertedType)\
static_assert( SunnyTcsHasInsertedType_##_Mark<_Type>::value \
, TCS_TO_STR_1( [__FILE__ __LINE__]_Type has no inserted type : _InsertedType ));



#define TCS_IS_HAS_MEMBER_FUNCTION(_Mark ,_Ret , _FuncName ,...) \
template<typename _Ty> \
struct SunnyTcsHasMemFunc_##_Mark{ \
template<typename _T, _Ret (_T::*)(##__VA_ARGS__) = &_T::_FuncName>\
static constexpr bool check(_T*) { return true; }\
static constexpr bool check(...) { return false; }\
static constexpr bool value = check(static_cast<_Ty*>(0)); \
};


#define TCS_IS_HAS_CONST_MEMBER_FUNCTION(_Mark ,_Ret , _FuncName ,...) \
template<typename _Ty> \
struct SunnyTcsHasMemFunc_##_Mark{ \
template<typename _T, _Ret (_T::*)(##__VA_ARGS__)const = & _T::_FuncName>\
static constexpr bool check(_T*) { return true; }\
static constexpr bool check(...) { return false; }\
static constexpr bool value = check(static_cast<_Ty*>(0)); \
};




#define TCS_CHECK_HAS_MEMBER_FUNCTION(_Type ,_Mark) \
 SunnyTcsHasMemFunc_##_Mark<_Type>::value


#define TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(_Type ,_Mark,_Ret ,_FuncName,...) \
TCS_IS_HAS_MEMBER_FUNCTION(_Mark,_Ret ,_FuncName,##__VA_ARGS__)\
static_assert( SunnyTcsHasMemFunc_##_Mark<_Type>::value \
, TCS_TO_STR_1( [__FILE__ __LINE__]_Type has no member function : _Ret _FuncName(##__VA_ARGS__) ));


#define TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(_Type ,_Mark,_Ret ,_FuncName,...) \
TCS_IS_HAS_CONST_MEMBER_FUNCTION(_Mark,_Ret ,_FuncName,##__VA_ARGS__)\
static_assert( SunnyTcsHasMemFunc_##_Mark<_Type>::value \
, TCS_TO_STR_1( [__FILE__ __LINE__]_Type has no member function : _Ret _FuncName(##__VA_ARGS__)const ));


//��־���
#ifdef TCS_OS_WIN32
#define TrimFilePath(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else//*nix
#define TrimFilePath(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif


#define LOG_DEBUG(fmt, ...)   \
printf("[DEBUG] [%s(%d)] : " fmt"\n",TrimFilePath(__FILE__),__LINE__,##__VA_ARGS__)
#define LOG_INFO(fmt, ...)    \
printf("[INFO ] [%s(%d)] : " fmt"\n",TrimFilePath(__FILE__),__LINE__,##__VA_ARGS__)
#define LOG_WARN(fmt, ...)    \
printf("[WARN ] [%s(%d)] : " fmt"\n",TrimFilePath(__FILE__),__LINE__,##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   \
printf("[ERROR] [%s(%d)] : " fmt"\n",TrimFilePath(__FILE__),__LINE__,##__VA_ARGS__)



//��̬����
#define TCS_STATIC_ASSERT(_Expr , _Decp) \
static_assert(_Expr , #_Decp);



//����Qt�������ݳ�Ա����
#define TCS_DECLARE_PRIVATE(Class)\
private: \
	inline std::shared_ptr<Class##Private> d_func() { return std::shared_ptr<Class##Private>( reinterpret_cast<Class##Private*>(&(*d_ptr))); }\
	inline std::shared_ptr<const Class##Private> d_func()const { return std::shared_ptr<const Class##Private>(reinterpret_cast<const Class##Private*>(&(*d_ptr))); } \
	friend class Class##Private;

#define TCS_D\
auto d = this->d_func();

#define TCS_DECLARE_PUBLIC(Class)\
public:\
	inline Class* q_func() { return reinterpret_cast<Class*>(q_ptr); }\
	inline const Class* q_func()const { return  reinterpret_cast<Class*>(q_ptr); } \
	friend class Class;

#define TCS_Q\
auto q = this->q_func();


//������ȡ
template<typename Ty>
class SunnyTcsTypeTraits {
public:
	typedef Ty value_type;
	typedef typename std::conditional< std::is_trivially_copyable<value_type>::value ,value_type , value_type const &>:: type TransferedType; 
	static value_type getDefaultValue() { return std::is_arithmetic<value_type>::value ? 0 : value_type(); }
	static value_type getMaxValue() { return 0; }
	static value_type getMinValue() { return 0; }
	static value_type getInvaildValue() { return -1; }
};




//��̬�������
//����ģ�壬���һ��tuple
template<typename T>
inline constexpr auto StructSchema() {
	return std::make_tuple();
}


//����һ��������������ֶ����ı�ʶ�࣬Ϊ��֧�־�̬���䣬������Ҫһ����̬��������ʶ��ÿ���������ÿ����Ա
//����ʹ�ö�̬���ݱ�ʶ����Ϊ��̬��������� �����ڣ���̬�����������ڲ���
#define TCS_CLASS_FIELD_MARK(ClassName, FieldName) \
class ClassName##_##FieldName{\
public:\
	static constexpr char const* className = #ClassName;\
	static constexpr char const* fieldName = #FieldName;\
};


#define TCS_DEFINE_CLASS_FIELD(ClassName , FieldName) \
	std::make_tuple(ClassName##_##FieldName(),&_Class::FieldName)


#define TCS_DEFINE_CLASS_SHCEMA(ClassName,...)\
template<>\
inline constexpr auto StructSchema<ClassName>() {\
	using _Class = ClassName;\
	return std::make_tuple(__VA_ARGS__);\
}



//Ԫ����ת������˫�� ת ����
template<typename CurType ,typename TarType>
struct StaticReflectFindFuncWarpper {
	template<typename T>
	struct apply { //�����ṩ�� FindTupleByTemplate ��Ԫ����
		static constexpr bool value = std::is_same< typename std::tuple_element<0, T>::type, TarType> ::value;
	};
};




 template<typename T , typename fn>
 auto& getClassFieldByName(T& var) {
	 auto schema = StructSchema<T>();
	 using TupleType = decltype(schema);
	 //StaticReflectFindFuncWarpper �������˫�Σ�ת��Ϊһ������Ԫ������ FindTupleByTemplate,��Ϊ����Ҫ��һ������Ԫ����
	 using Counter = typename FindTupleByTemplate<TupleType,  StaticReflectFindFuncWarpper<TupleType,fn>::apply >::type;
	 return var.*(
		 std::get<1>(std::get<Counter::value>(schema))
	 );
 }


 //����֧�־�̬����
#define TCS_SUPPORT_STATIC_REFLECT(ClassName)\
 friend inline constexpr auto StructSchema< ClassName >();


 //��̬���䣬����ȡ����
#define TCS_SRCFN(ClassName,FieldName,obj)\
	getClassFieldByName< ClassName ,ClassName##_##FieldName >( obj )






 //��̬�������2
//����ķ�����ƣ�����ʶ�ඨ����ȫ�֣�ͨ��ȫ�ֺ���ģ��� �ػ����õ� ��Է������ StructSchema<Class>ȫ�ֺ���
//ȱ�����ڣ���Ҫ���ⲿ�Է���ϸ�ڽ��ж��壬�����ʵ�ְ� ��ʶ�ඨ����������ڲ�������StructSchema��Ϊһ����ͨ��Ա����������������ڲ�

 //���ڱ�ʶ��Ϊ�ڲ��࣬����ֻ�� field��������
#define TCS_CLASS_FIELD_MARK2( FieldName) \
class C_##FieldName{\
public:\
	static constexpr char const* fieldName = #FieldName;\
};


 //_Class ::FieldName�� ȡ�������� const this ָ���Ӱ��
#define TCS_DEFINE_CLASS_FIELD2( FieldName) \
	std::make_tuple(C_##FieldName(),&_Class::FieldName)



 //StructSchema2 ����ֵ����const thisָ��Ӱ��
 //�ֱ���� const �Ͳ���const ��getClassFieldByName2 ��Ա���� ,��const�ķ��� ��Ա�Ĵ�const����
#define TCS_DEFINE_CLASS_SHCEMA2(ClassName,...)\
inline auto StructSchema2() const {\
	using _Class = ClassName;\
	return std::make_tuple(__VA_ARGS__);\
}\
 template<typename fn>\
 auto& getClassFieldByName2() const {\
	 auto schema = this->StructSchema2();\
	 using TupleType = decltype(schema);\
	 using Counter = typename FindTupleByTemplate<TupleType, StaticReflectFindFuncWarpper<TupleType, fn>::apply >::type;\
	 return (*this).*(\
		 std::get<1>(std::get<Counter::value>(schema))\
		 );\
 }\
 template<typename fn>\
 auto& getClassFieldByName2() {\
	 auto schema = this->StructSchema2();\
	 using TupleType = decltype(schema);\
	 using Counter = typename FindTupleByTemplate<TupleType, StaticReflectFindFuncWarpper<TupleType, fn>::apply >::type;\
	 return (*this).*(\
		 std::get<1>(std::get<Counter::value>(schema))\
		 );\
 }



 //��̬���䣬����ȡ����,ֱ����decltype��ȡ������ͣ����ô�ClassName��
#define TCS_SRCFN2(FieldName,obj)\
	obj.getClassFieldByName2< typename typename std::decay< decltype(obj)>::type::C_##FieldName >( )



#define TCS_STATIC_REFLECT_REGISTER_MARK2_1( arg1)  TCS_CLASS_FIELD_MARK2(arg1)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_2(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_1(arg2)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_3(arg1,arg2,...)TCS_CLASS_FIELD_MARK2(arg1)  TCS_STATIC_REFLECT_REGISTER_MARK2_2(arg2,##__VA_ARGS__) 
#define TCS_STATIC_REFLECT_REGISTER_MARK2_4(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_3(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_5(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_4(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_6(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_5(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_7(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_6(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_8(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_7(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_MARK2_9(arg1,arg2,...) TCS_CLASS_FIELD_MARK2(arg1) TCS_STATIC_REFLECT_REGISTER_MARK2_8(arg2,##__VA_ARGS__)



#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_1(arg1) TCS_DEFINE_CLASS_FIELD2(arg1)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_2(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_1(arg2)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_3(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_2(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_4(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_3(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_5(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_4(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_6(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_5(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_7(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_6(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_8(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_7(arg2,##__VA_ARGS__)
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2_9(arg1,arg2,...) TCS_DEFINE_CLASS_FIELD2(arg1),TCS_STATIC_REFLECT_REGISTER_SCHEMA2_8(arg2,##__VA_ARGS__)


 //��msvc�У�����������׼Ԥ�������ſ���ʹ��һ�¹��ܣ���Ϊmsvc��__VA_ARGS__��Ϊһ�����������ڶ����꺯��
#define TCS_STATIC_REFLECT_GET_PARM2(_1, _2 ,_3, _4, _5 , _6 ,_7 ,_8 ,_9 , func ,...) func 

 //��ʶ�ඨ���
#define TCS_STATIC_REFLECT_REGISTER_MARK2(arg1,...)\
 TCS_STATIC_REFLECT_GET_PARM2( arg1,##__VA_ARGS__ ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_9 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_8 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_7 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_6 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_5 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_4 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_3 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_2 ,\
 TCS_STATIC_REFLECT_REGISTER_MARK2_1 )\
(arg1 ,##__VA_ARGS__)


//����TCS_DEFINE_CLASS_SCHEMA�� ����չ��
#define TCS_STATIC_REFLECT_REGISTER_SCHEMA2(arg1,...)\
 TCS_STATIC_REFLECT_GET_PARM2( arg1,##__VA_ARGS__ ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_9 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_8 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_7 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_6 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_5 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_4 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_3 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_2 ,\
 TCS_STATIC_REFLECT_REGISTER_SCHEMA2_1 )\
(arg1 ,##__VA_ARGS__)


//��̬����ע��� ,TCS_STATIC_REFLECT_REGISTER_MARK2�����и����ı�ʶ�������ඨ�壬TCS_DEFINE_CLASS_SHCEMA2����StructSchema�ĵȳ�Ա����
//TCS_STATIC_REFLECT_REGISTER_SCHEMA2����չ�� һϵ��TCS_DEFINE_CLASS_FIELD2��������ʶ��ͳ�Աָ�룩
#define TCS_STATIC_REFLECT2(ClassName ,...)\
public:\
TCS_STATIC_REFLECT_REGISTER_MARK2(__VA_ARGS__)\
TCS_DEFINE_CLASS_SHCEMA2( ClassName ,\
	TCS_STATIC_REFLECT_REGISTER_SCHEMA2(__VA_ARGS__)\
)
