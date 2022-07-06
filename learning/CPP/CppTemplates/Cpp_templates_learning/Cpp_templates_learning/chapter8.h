#pragma once
#include <tuple>
#include <functional>
#define type_has_member_type_int(ty) (sizeof(test<ty>(0)) == 1)

//SFINAE‘≠‘Ú
typedef char RT1;
typedef struct 
{
	char twoSize[2];
} RT2;



template<typename T>
RT1 test( typename T::X const*) { return RT1(); }

template<typename T>
RT2 test(...) { return RT2(); }


class X {};

class MyClass
{
public:
	MyClass() {}
	~MyClass() {}

	int X;

};




template<int const & ref>
void refArgTest() {
	std::cout << ref << std::endl;
}


class chapter8
{
public:
	chapter8();
	~chapter8();

	void tests() {
		int a = 10;
		//refArgTest<global_val>();
		std::cout<< type_has_member_type_int(MyClass) <<std::endl;
	}

//	int _val;
};




