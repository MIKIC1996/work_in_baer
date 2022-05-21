// c4_sequenceContainers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <tuple>

template<int inst>
void print() {
	std::cout << "kong" << std::endl;
}

template<>
void print<1>() {
	std::cout << "kon2g" << std::endl;
}


class AA {
public:
	AA() {}

	AA(const AA&) {
		std::cout << "AA copy" << std::endl;
	}

	AA(AA&&) noexcept {
		std::cout << "AA move" << std::endl;
	}

	~AA(){}

	int val = 10;


};


AA getAA(AA& ref) {
	return ref;
}


int main()
{
	
	AA aa;
	
	AA bb(AA());
	


	getchar();
    return 0;
}

