#pragma once
#include "basic_deps.h"


//OS
#define TCS_OS_WIN32

//库导出
#define BASIC_EXPORT __declspec(dllexport)

//接口检测强度
#define STRICT_INTERFACE_CHECK


#define TCS_TO_STR_2(expr) TCS_TO_STR_1(expr)  
#define TCS_TO_STR_1(expr) TCS_TO_STR(expr)
#define TCS_TO_STR(expr) #expr

//类接口规范静态检测

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


//日志输出
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



//静态断言
#define TCS_STATIC_ASSERT(_Expr , _Decp) \
static_assert(_Expr , #_Decp);



//类似Qt的类数据成员隐藏
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


//类型萃取
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




//静态反射机制
//函数模板，获得一个tuple
template<typename T>
inline constexpr auto StructSchema() {
	return std::make_tuple();
}


//这是一个针对类名——字段名的标识类，为了支持静态反射，我们需要一个静态的类来标识，每个类里面的每个成员
//不能使用动态数据标识，因为静态反射完成于 编译期，动态数据在运行期产生
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



//元函数转换器，双参 转 单参
template<typename CurType ,typename TarType>
struct StaticReflectFindFuncWarpper {
	template<typename T>
	struct apply { //真正提供给 FindTupleByTemplate 的元函数
		static constexpr bool value = std::is_same< typename std::tuple_element<0, T>::type, TarType> ::value;
	};
};




 template<typename T , typename fn>
 auto& getClassFieldByName(T& var) {
	 auto schema = StructSchema<T>();
	 using TupleType = decltype(schema);
	 //StaticReflectFindFuncWarpper 用自身的双参，转换为一个单参元函数给 FindTupleByTemplate,因为后者要求一个单参元函数
	 using Counter = typename FindTupleByTemplate<TupleType,  StaticReflectFindFuncWarpper<TupleType,fn>::apply >::type;
	 return var.*(
		 std::get<1>(std::get<Counter::value>(schema))
	 );
 }


 //让类支持静态反射
#define TCS_SUPPORT_STATIC_REFLECT(ClassName)\
 friend inline constexpr auto StructSchema< ClassName >();


 //静态反射，按名取变量
#define TCS_SRCFN(ClassName,FieldName,obj)\
	getClassFieldByName< ClassName ,ClassName##_##FieldName >( obj )






 //静态反射机制2
//上面的反射机制，将标识类定义于全局，通过全局函数模板的 特化，得到 针对反射类的 StructSchema<Class>全局函数
//缺陷在于，需要在外部对反射细节进行定义，下面的实现把 标识类定义在了类的内部，并把StructSchema作为一个普通成员函数定义在了类的内部

 //由于标识类为内部类，所以只用 field命名即可
#define TCS_CLASS_FIELD_MARK2( FieldName) \
class C_##FieldName{\
public:\
	static constexpr char const* fieldName = #FieldName;\
};


 //_Class ::FieldName的 取法，不受 const this 指针的影响
#define TCS_DEFINE_CLASS_FIELD2( FieldName) \
	std::make_tuple(C_##FieldName(),&_Class::FieldName)



 //StructSchema2 返回值不受const this指针影响
 //分别定义带 const 和不带const 的getClassFieldByName2 成员函数 ,带const的返回 成员的带const引用
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



 //静态反射，按名取变量,直接用decltype获取类的类型，不用传ClassName了
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


 //在msvc中，必须启动标准预处理器才可以使用一下功能，因为msvc将__VA_ARGS__作为一个参数传给第二个宏函数
#define TCS_STATIC_REFLECT_GET_PARM2(_1, _2 ,_3, _4, _5 , _6 ,_7 ,_8 ,_9 , func ,...) func 

 //标识类定义宏
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


//用于TCS_DEFINE_CLASS_SCHEMA的 参数展开
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


//静态反射注册宏 ,TCS_STATIC_REFLECT_REGISTER_MARK2将所有给定的标识符进行类定义，TCS_DEFINE_CLASS_SHCEMA2创建StructSchema的等成员函数
//TCS_STATIC_REFLECT_REGISTER_SCHEMA2负责展开 一系列TCS_DEFINE_CLASS_FIELD2（关联标识类和成员指针）
#define TCS_STATIC_REFLECT2(ClassName ,...)\
public:\
TCS_STATIC_REFLECT_REGISTER_MARK2(__VA_ARGS__)\
TCS_DEFINE_CLASS_SHCEMA2( ClassName ,\
	TCS_STATIC_REFLECT_REGISTER_SCHEMA2(__VA_ARGS__)\
)
