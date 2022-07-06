#pragma once


#include "pch.h"


//���ļ���Ż������������չ����


//tuple ��������������������
template<typename T, typename Y, typename C = std::integral_constant<int, 0>>
struct FindTupleType {
	typedef typename std::conditional <
		std::is_same< typename std::tuple_element<C::value, T >::type, Y >::value,
		C,
		typename FindTupleType<T, Y, std::integral_constant<int, C::value + 1>>::type > ::type type;

};


//�����ƫ�ػ����� ��һ���ػ�������C::value ���� tuple_element�ļ���
template<typename T, typename Y>
struct FindTupleType < T, Y, std::integral_constant<int, std::tuple_size<T>::value>> {
	typedef std::integral_constant<int, -1> type;
};



//tuple���������ݸ����� ģ��ԭ���������ҷ���������
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
