// std_bind.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>



//std::_if 一个简单的元函数，从输入的两个类型中，根据输入常量，选择一个为 结果（type)

template<bool _Dec,typename _Class1,typename _Class2>
struct my_if {
	typedef _Class2 type;
};


template<typename _Class1,typename _Class2>
struct my_if<true,_Class1,_Class2> {
	typedef _Class1 type;
};


//std::decay 应用了 if技术，是一个按照条件 返回不同结果的函数，
template <typename _Ty>
struct my_decay {
	typedef typename my_if < std::is_array<_Ty>::value,
							typename std::remove_extent<_Ty>::type,
							typename my_if< std::is_function<_Ty> ::value,
								typename std::add_pointer<_Ty>::type,
								typename std::remove_cv<_Ty>::type> ::type>
		::type type; 
	
	//如果是数组，去除extent, 如果是函数类型，添加指针，其他，去除const volatile
};



template<typename _Ty>
struct my_tuple_val {

	template<typename T>
	my_tuple_val(T val) :_val(val) {}


	_Ty _val;
};


template<typename... _Rests>
struct my_tuple {

	
};

template<>
struct my_tuple<> {


};

template<typename _This>
struct my_tuple <_This>
{
	template<typename _One>
	my_tuple(_One val) :_thisVal(val) {}

	void print() {
		std::cout << _thisVal._val << std::endl;
	}

	_This at(int ct) {
		
		return _thisVal._val;
	}

	my_tuple_val<_This> _thisVal;
};


//std::tuple 可变参数模板函数 对 ...Args的递归处理手法，这里也用上了。
template<typename _This,typename... _Rests>
struct my_tuple <_This,_Rests...>  //这样就相当于 一个随自己定义的结构体。 可以用于函数参数打包
	: my_tuple<_Rests...>
{
	typedef my_tuple<_Rests...> _MyBasic;

	template<typename _One,typename... _Args>
	my_tuple(_One val , _Args... rests):_MyBasic(rests...),_thisVal(val){}

	void print() {
		std::cout << ( _thisVal._val) << std::endl;
		_MyBasic& ba = (*this);
		ba.print();
	}

	virtual auto at(int ct)->decltype(ct == 0 ? _thisVal._val : ((_MyBasic&&)(*this)).at(ct - 1))
	{
		return ct == 0 ? _thisVal._val : ((_MyBasic&&)(*this)).at(ct - 1);
	}

	my_tuple_val<_This> _thisVal;

};



struct sonTup :  my_tuple<int, char, int>
{
	sonTup(int i1, char c1, int i2) :my_tuple(i1, c1, i2) ,_val(c1){}

	virtual char at(int ct)
	{
		std::cout << "sonson" << std::endl;
		return ct ==0 ? _val : _val;
	}

	char _val;

};




template<typename _Ty, _Ty val>
struct Constaint {
	typedef _Ty value_type;
	typedef Constaint<_Ty, val> type;
	static constexpr _Ty value = val;
};




//std::integar_sequence  //将一个数列 变成 一个类
template<typename _Ty,_Ty... _vals>
struct my_integar_sequence {
	typedef my_integar_sequence<_Ty,_vals...> type;
	typedef _Ty value_type;

};










//make_integar_sequence 从 输入数，形成一个 从 0 到输入数 的 integar_sequence
// template<typename _Ty,_Ty... _rests>
// struct my_make_seq;
// 
// 
// 
// template<typename _Ty, _Ty... _rests>
// struct my_make_seq<_Ty, Constaint<_Ty, 0>, my_integar_sequence<_Ty, _rests...> >
// 	: my_integar_sequence<_Ty, _rests...> ::type
// {};
// 
// 
// template<typename _Ty, _Ty _this, _Ty... _rests>
// struct my_make_seq<_Ty, Constaint<_Ty, _this>,my_integar_sequence<_Ty, _rests...> >
// 	:my_make_seq<
// 	_Ty,
// 	Constaint<_Ty, _this - 1>,
// 	my_integar_sequence<_Ty, _this - 1, _rests...>
// 	>
// {};



template<typename _Ty>
struct Traits {

};

class AA;
template<>
struct Traits<AA> {
	typedef int type;
};

class BB;
template<>
struct Traits<BB> {
	typedef char type;
};


struct AA {
	AA() {}

	typedef typename Traits<AA>::type type;
	static constexpr int _value = 1;
};


struct BB : AA {

	BB() :AA() {}

	typedef typename Traits<BB>::type type;
	static constexpr int _value = 2;
};

template<typename Ty>
void yun(Ty& obj) {
	typename Traits<Ty>::type c=86;
	std::cout << c;
}

template<int val>
void dao() {
	std::cout << 1;
}

template<>
void dao<2>() {
	std::cout << 2;
}


int main()
{
	
	//my_tuple<int, char, int> my(1, 'a', 1);
	//my.print();
	//std::cout << (my.at(1));
	
	AA* ptr = new BB();
	
	dao<2>();

	//print_seq<1, 2, 3>();

	getchar();
    return 0;
}

