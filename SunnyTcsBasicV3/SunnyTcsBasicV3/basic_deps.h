#pragma once


#include "pch.h"

//本库基于C++ 17开发， 未来有可能使用C++ 20的协程
//本文件存放基于依赖库的扩展功能


//tuple 函数，查找子类型索引
template<typename T, typename Y, typename C = std::integral_constant<int, 0>>
struct FindTupleType {
	typedef typename std::conditional <
		std::is_same< typename std::tuple_element<C::value, T >::type, Y >::value,
		C,
		typename FindTupleType<T, Y, std::integral_constant<int, C::value + 1>>::type > ::type type;

};


//下面的偏特化限制 进一步特化，导致C::value 超过 tuple_element的极限
template<typename T, typename Y>
struct FindTupleType < T, Y, std::integral_constant<int, std::tuple_size<T>::value>> {
	typedef std::integral_constant<int, -1> type;
};



//tuple函数，根据给定的 模板原函数，查找符合条件的
template<typename TupleType, template<typename> class FindMetaFunc, typename Ct = std::integral_constant<int, 0>>
struct FindTupleByTemplate {
	typedef typename std::conditional<
		FindMetaFunc< typename std::tuple_element<Ct::value, TupleType>::type>::value,
		Ct,
		typename FindTupleByTemplate<TupleType, FindMetaFunc, std::integral_constant<int, Ct::value + 1>>::type
	> ::type type;
};


template<typename TupleType, template<typename> class FindMetaFunc>
struct FindTupleByTemplate < TupleType, FindMetaFunc, std::integral_constant<int, std::tuple_size<TupleType>::value>> {
	typedef std::integral_constant<int, -1> type;
};


//tuple for each
template<typename TupleType , typename Functor , typename Ct = std::integral_constant<int , 0>>
static void TupleForEach(TupleType& tup, Functor&& func ,Ct = Ct()) {
	func(std::get<Ct::value>(tup));
	TupleForEach(tup, std::forward<Functor>(func),std::integral_constant<int,Ct::value+1>());
}


template<typename TupleType , typename Functor >
static void TupleForEach (TupleType& tup, Functor&& func , std::integral_constant<int, std::tuple_size< typename std::decay<TupleType>::type >::value >)
{}


//字符串拼接
static void _combineStrWithLinkFlag(std::string const& linkFlag, std::string& str) {
	str.erase(str.size()  - linkFlag.size(), linkFlag.size());
}


template<typename T, typename... Args >
static void _combineStrWithLinkFlag(std::string const& linkFlag, std::string& str, T&& arg1, Args&&... args) {
	str += arg1;
	str += linkFlag;
	_combineStrWithLinkFlag(linkFlag,str, std::forward<Args>(args)...);
}



template<typename T, typename... Args>
static std::string combineStrWithLinkFlag(std::string linkFlag , T&& arg1, Args&&... args) {
	std::string str;
	_combineStrWithLinkFlag(linkFlag , str , std::forward<T>(arg1),std::forward<Args>(args)...);
	return str;
}



//不可拷贝的类
class UnCopyable {
private:
	UnCopyable(UnCopyable const&) {}
	UnCopyable& operator=(UnCopyable const&) { return *this; }
};
