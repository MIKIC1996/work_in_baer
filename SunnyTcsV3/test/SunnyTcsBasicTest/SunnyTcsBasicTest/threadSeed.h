#pragma once

#include <iostream>
#include <SunnyTcsLibGeneral.hpp>
#include <functional>

using namespace std;
using namespace basic;




int add2(int a, int b) {
	cout << a + b << endl;
	return a + b;
	
}

int add3(int a, int b,int c) {
	cout << a + b +c<< endl;
	return a + b+c;

}


bool funkSB(int a) {
	cout << a << endl;
	return false;
}


void threadSeedTest() {
	SunnyTcsThreadSeed_basic<bool(int)> ba;
	ba.submit([](int a) {
		cout << a << endl;
		return false;
	},10);
	ba.work();
	cout << "end" << endl;
}

