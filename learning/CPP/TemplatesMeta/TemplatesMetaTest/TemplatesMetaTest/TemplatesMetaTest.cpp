// TemplatesMetaTest.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"

using namespace std;


//使用模版元 进行数值计算，可以将那些 已知需要使用的 定（常量）值 ，在编译期就计算出来，从而无需浪费 运行期资源，比如 求某个数，比如10 的阶乘。 
//  basic 库中的logicInfo 就是可以典型的 应用模板元 的类，使用后可以大大提高效率！！！！！！！！！！！！！！！ 

template <int val>
struct factorial {
	static constexpr int value = val * factorial<val - 1>::value; //本质上也是递归，只是计算于 编译期
};


//中止条件
template<>
struct factorial<1>
{
	static constexpr int value = 1;
};


//类型外覆类---------------------------------------------------------------------------------
//将一个非类型元数据 包装成一个类型 ，一般来说，非类型 元数据 为constexpr 常量,即编译期 即可计算出值的 常量。

template<typename _Ty , _Ty val>
struct Constaint {
	typedef _Ty value_type;
	typedef Constaint<_Ty, val> type;
	static constexpr _Ty value =val;
};


template<int val> //int 版本的偏特化
struct  Constaint<int, val>
{
	typedef int value_type;
	typedef Constaint<int, val> type;
	static constexpr int value = val;
};


#define __INT( val ) \
	Constaint<int ,val>


// template<int val>
// typedef Constaint<int, val> Integar_Constaint<val>;  --非法


template<bool val>
struct  Constaint<bool,val>
{
	typedef bool value_type;
	typedef Constaint<bool, val> type;
	static constexpr bool value = val;

	//支持到bool 类型的隐式转换
	operator bool() {
		return this->value;
	}
};

//这就是 true 和 false 的类型 外覆器
typedef Constaint<bool, true> my_true_type;
typedef Constaint<bool, false> my_false_type;


//判断形 元函数--------------------------------------------------------------------------
template <typename _Ty>
struct my_is_pointer : public my_false_type //判断一个类型是否是指针
{

};


template <typename _Ty>
struct  my_is_pointer<_Ty*> :public my_true_type
{

};



//一个简单的 加法 元函数,这是针对 非类型元数据 的版本
template<typename _Ty, _Ty val1,_Ty val2>
struct adder {
	typedef _Ty value_type;
	static constexpr _Ty value = val1 + val2;
};



//这是针对 有类型外覆器 的类型元数据的 加法元函数 版本
template<typename _Ty1,typename _Ty2>
struct adder_t {
	typedef typename _Ty1::value_type value_type;
	static constexpr value_type value = _Ty1::value + _Ty2::value;
	//将value 包装成类外覆器
	typedef Constaint<value_type, value> value_box;
};


template<typename _Ty>
struct my_iterator_traits
{


};

//元数据集合
template<typename _Ty1, typename _Ty2 , typename _Ty3, typename _Ty4, typename _Ty5> 
struct meta_array_5 {
	//记录序列
	typedef _Ty1 _Ty1;
	typedef _Ty2 _Ty2;
	typedef _Ty3 _Ty3;
	typedef _Ty4 _Ty4;
	typedef _Ty5 _Ty5; //这是以类型 记录数据的版本
	

	//这么写是为了提供 这个序列 容器的类型 ，也就是meta_array_5，这种嵌入类模板的方法
	template<typename _Ty1, typename _Ty2, typename _Ty3, typename _Ty4, typename _Ty5>
	struct vector_type
		: meta_array_5< _Ty1,  _Ty2,  _Ty3,  _Ty4,  _Ty5>
	{};


	static void print() {
		cout << _Ty1::value << endl;
		cout << _Ty2::value << endl;
		cout << _Ty3::value << endl;
		cout << _Ty4::value << endl;
		cout << _Ty5::value << endl;
	}
};


//这是以静态数组 记录数据的版本
template<typename _Ty1, _Ty1 v1, _Ty1 v2, _Ty1 v3, _Ty1 v4, _Ty1 v5>
struct meta_array_5_c {
	 	typedef  _Ty1 element_type; //直接用静态成员记录数据的版本
	 	typedef element_type value_type[5]; //定义一个数组类型 ，作为奔类的value_type
	 	static const value_type value ;

};

template<typename _Ty1, _Ty1 v1, _Ty1 v2, _Ty1 v3, _Ty1 v4, _Ty1 v5>
 const typename meta_array_5_c<_Ty1, v1, v2, v3, v4, v5>::value_type
	 meta_array_5_c<_Ty1, v1, v2, v3, v4,v5>::value	 =	{v1,v2,v3,v4,v5 };




 //类模板外覆器 ，他使得一个类模板(元函数) 成为一个类，这样就能够成为元函数的 参数，
 struct add_alg_f {
	 template<typename _Class1, typename _Class2>
	 struct apply  : adder_t<_Class1,_Class2>
	 {
		
	 };
 };


 template <typename _Ty1,typename _Ty2>
 struct minus_t {
	 typedef typename _Ty1::value_type value_type;
	 static constexpr value_type value = _Ty1::value - _Ty2::value;
	 //将value 包装成类外覆器
	 typedef Constaint<value_type, value> value_box;
 };

 struct minus_alg_f {
	 template<typename _Class1, typename _Class2>
	 struct apply : minus_t<_Class1, _Class2>
	 {

	 };
 };


 //回想一下std::for_each ，他也将一个 函数 作为自生（函数） 的参数
template<typename _Vector1,typename _Vector2,typename _Func>
struct my_transform { //对两个序列 按照 func 进行处理
 
// 		typedef meta_array_5 <  //
// 		 typename _Func::template apply<typename _Vector1::_Ty1, typename _Vector2::_Ty1>::value_box,
// 		 typename _Func::template apply<typename _Vector1::_Ty2, typename _Vector2::_Ty2>::value_box,
// 		 typename _Func::template apply<typename _Vector1::_Ty3, typename _Vector2::_Ty3>::value_box,
// 		 typename _Func::template apply<typename _Vector1::_Ty4, typename _Vector2::_Ty4>::value_box,
// 		 typename _Func::template apply<typename _Vector1::_Ty5, typename _Vector2::_Ty5>::value_box
// 		 > res;

		typedef typename _Vector1::template vector_type< //假定 参数类，提供了序列容器类型模板
		 typename _Func::template apply<typename _Vector1::_Ty1, typename _Vector2::_Ty1>::value_box,
		 typename _Func::template apply<typename _Vector1::_Ty2, typename _Vector2::_Ty2>::value_box,
		 typename _Func::template apply<typename _Vector1::_Ty3, typename _Vector2::_Ty3>::value_box,
		 typename _Func::template apply<typename _Vector1::_Ty4, typename _Vector2::_Ty4>::value_box,
		 typename _Func::template apply<typename _Vector1::_Ty5, typename _Vector2::_Ty5>::value_box
		 > res;

		

 };







int main()
{
// 	cout << adder<int, 3, 5>::value << endl;
// 	cout << adder_t<Constaint<int, 5>, Constaint<int, 6>>::value << endl;
// 	cout << adder_t<__INT(4), __INT(3)>::value << endl;
// 	cout << factorial<3>::value << endl;
// 	cout << is_pointer<int*>::value << endl;

   typedef	typename my_transform<
		meta_array_5<__INT(1), __INT(2), __INT(3), __INT(4), __INT(5)>,
		meta_array_5<__INT(1), __INT(2), __INT(3), __INT(4), __INT(5)>,
	   minus_alg_f> ::res transform_type;
		
	transform_type::print();

	getchar();
    return 0;
}

