// Cpp_templates_learning.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "chapter5.h"
#include "chapter6.h"

#include "chapter8.h"
#include "chapter15.h"

#include "chapter16.h"

int main()
{
	
	long long ret =0;
	while (1) {
		for (int i = 0; i < 10000000; ++i) {
			ret += i;
		}
		ret = 0;
	}

	getchar();
}

