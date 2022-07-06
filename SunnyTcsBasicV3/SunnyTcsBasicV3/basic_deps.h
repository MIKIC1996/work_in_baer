#pragma once


#include "pch.h"


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
