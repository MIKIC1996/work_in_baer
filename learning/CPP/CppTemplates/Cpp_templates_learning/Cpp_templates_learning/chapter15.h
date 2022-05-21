#pragma once
class chapter15
{
public:
	chapter15();
	~chapter15();
};


//policy and traits -----------------------------------------------------------------------------------------

//最基本的积累 函数，存在一下缺陷
template<typename T>
T accum_easy(T const* start, T const * end) { // 1 指定迭代器类型为指针
	T ret = T(); //2 返回类型没有单独考虑，也许会发生越界 ；  3 初始化取决于 类的默认构造函数，不可靠
	for (start; start != end; ++start) { 
		ret += *start; //4 默认求和，没有对行为进行参数化
	}
	return ret;
}



//缺陷解决
//缺陷2 和 3 ，要解决这个问题，通过引入trait, 增加对模板参数T的 属性描述

template<typename T>
class AccumTraits;

template<>
class AccumTraits<int> {
public:
	typedef long long Acct; //指定累加结果类型
	
	//设置好初始值，这种方法不好，只能设置整性数的初始值，无法对浮点数或者 类对象设定初始值
	static constexpr int zero_value = 0;

	//所以使用以下方法
	static int get_zero_value() {
		return 0;
	}
};


template<>
class AccumTraits<float> {
public:
	typedef double Acct;

	static float get_zero_value() {
		return 0.0;
	}
};


//这样就得到了以下解决方案 
template<typename T ,typename Trait = AccumTraits<T> > //对使用的Trait 提供可配置能力，客户可以自己定义trait,或者使用我给的初始值
typename Trait::Acct accum_with_trait(T const * start, T const * end) {  //1 指定迭代器类型为指针
	typedef typename Trait::Acct return_type; //解决了选择合适的返回类型的问题
	return_type ret = Trait::get_zero_value(); //解决了合适的初始化问题
	for (start; start != end; ++start) {
		ret += *start; //4 默认求和，没有对行为进行参数化
	}
	return ret;
}


//缺陷4，方案1 提供policy类，将处理行为封装
class SumPolicy {
public:
	//使用成员函数模板的形式
	template <typename T1 ,typename T2>
	static void accum_ope(T1 & ret, T2 const & val) {
		ret += val;
	}
};

class MutiPolicy {
public:
	//使用成员函数模板的形式
	template <typename T1, typename T2>
	static void accum_ope(T1 & ret, T2 const & val) {
		ret *= val;
	}
};


template<typename T, typename Policy = MutiPolicy,typename Trait = AccumTraits<T> > //这里 policy 和 trait 都提供了确切的类
typename Trait::Acct accum_with_trait_policy(T const * start, T const * end) {  //1 指定迭代器类型为指针
	typedef typename Trait::Acct return_type; //解决了选择合适的返回类型的问题
	return_type ret = Trait::get_zero_value(); //解决了合适的初始化问题
	for (start; start != end; ++start) {
		Policy::accum_ope(ret , *start); //解决了行为问题 //引发了缺陷5 ： 初始值设定 随着policy的不同应该也不同，显然trait和policy应该存在联系
	}
	return ret;
}

//缺陷4 方案2 ，policy作为类模板
template<typename T1,typename T2>
class SumPolicy_template {
public:
	static void accum_ope(T1& ret, T2 const& val) {
		ret += val;
	}
};

template<typename T1,typename T2>
class MutiPolicy_template {
public:
	static void accum_ope(T1& ret, T2 const & val) {
		ret *= val;
	}
};


template<typename T, 
	template<typename ,typename> class Policy = MutiPolicy_template , //使用 模板的模板参数
	template<typename> class Trait = AccumTraits > //trait也使用 模板的模板参数 ，对模板参数进行了类模板（包括模板参数列表格式）的限定 ，好处在于自动完成T 与 Trait的绑定
												//，之前是指定为一个明确的类，很明显在不使用缺省值 且 客户也使用Trait<T>类模板 的情况下 需要客户自己完成Trait 与 T的绑定 ，
													//限定比较少，只要提供一个满足要求的类就行，并不做其他要求
typename Trait<T>::Acct accum_with_trait_policyTemplate(T const * start, T const * end) {  //1 指定迭代器类型为指针
	typedef typename Trait<T>::Acct return_type; //解决了选择合适的返回类型的问题
	return_type ret = Trait<T>::get_zero_value(); //解决了合适的初始化问题
	for (start; start != end; ++start) {
		Policy<return_type,T>/*trait和policy在这里建立联系 return_type,也许还需要更多的trait信息，不如直接把trait给policy*/
			::accum_ope(ret, *start); //解决了行为问题 //引发了缺陷5 ： 初始值设定 随着policy的不同应该也不同，显然trait和policy应该存在联系
	}
	return ret;
}



//缺陷5 要解决这个缺陷，认为初始值是由 policy 和 trait 共同决定的，
class MutiPolicy_finish {

	template<typename Trait>
	typename Trait::Acct getZero() {
		
	}

};


//SFINAE 应用
//测试是否为一个类
template<typename T>
class isClassT {
public:
	typedef char one;
	typedef struct 
	{
		char arr[2];
	} two;
	//1
	template<typename C> static one testClass(int C::*) { std::cout << "one" << std::endl; return one(); } //只有T为类，函数成员 指针才存在
	//2
	template<typename C> static two testClass(...) { std::cout << "two" << std::endl; return two(); }

	enum 
	{
		Yes = (sizeof(testClass<T>(0)) == 1) //sizeof并不调用函数 ，T是一个class， testClass就绑定到1 ,否则就2
	};

	enum 
	{
		No = !Yes
	};

};

