#pragma once
#include "stdafx.h"



class chapter6
{
public:
	chapter6() {}
	~chapter6() {}


	template<typename T>
	void print(); //定义在内部的化，就是隐式内联了

};


#include "chapter6_1.h" //这样可以将模板声明与定义分离

