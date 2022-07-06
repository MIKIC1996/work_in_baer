#pragma once
#include <SunnyTcsCraft.h>



using namespace basic;
using namespace std;

template<typename _Ty, _Ty val>
struct Constaint {
	typedef _Ty value_type;
	typedef Constaint<_Ty, val> type;
	static constexpr _Ty value = val;
};


template<int val>
using int_constaint = Constaint<int, val>;



using jmq_type = std::tuple<int, int, int>;
jmq_type jmq = std::make_tuple(6, 7, 6);

std::function<void(int, int, int)> func = [](int a, int b, int c)->void {cout << a << b << c << endl; };

void work(int a, int b, int c) {
	cout << a << b << c << endl;
}

template< typename J, typename... Args>
void funn(J arg,Args... rest) {
	work(arg, rest...);
}


template<int seq =0,typename J ,typename... Args>
void printe(J arg1, Args... rest) {
	cout << seq << " : " << arg1 << endl;
	printe<seq + 1>(rest...);
}

template<int seq = 0, typename J>
void printe(J arg1) {
	cout << seq << " : " << arg1 << endl;
}

void work() {

}

template<typename T>
void _work(T) {

}

template<>
void _work(int_constaint<2>) {

}


template <typename _Int,typename J , typename... Args>
void working(_Int ,J arg,Args... rest) {
	if (_Int::value < 2) {
//		static_assert(index == 1, "2222");
		cout <<"b"<< _Int::value << endl;
		working( int_constaint<_Int::value +1>(), arg,  rest...,std::get<_Int::value + 1>(jmq)); 
	}
	else {
		//static_assert(index == 2, "3333");
		//work(arg, rest...);
		cout<<"c"<< _Int::value << endl;

	}
}

template < typename J, typename... Args>
void working(int_constaint<2>, J arg, Args... rest) {
	
	cout << sizeof...(Args) << endl;
		//static_assert(index == 2, "3333");
		//work(arg, rest...);
		cout << "c" <<2 << endl;
		funn(arg, rest...);
	
}


void AAA() {

}


void BBB() {
	return AAA();
}

// template <int index =0 ,typename J >
// void working(J arg) {
// 	static_assert(index == 0, "1111");
// 	
// 	cout << "hahah" << endl;
// 	working<index +1>(arg, std::get<index + 1>(jmq));
// 	
// }

template<int index =0>
void working() {
	
}

class KKK {};



void actionTest() {
// 	SunnyTcsAction action;
// 	action.setParams_meta<1>(SunnyTcsArg(1));
// 	SunnyTcsArg arg1 = action.getParam_meta<1>();
// 	SunnyTcsArg arg2 = action.getParam_meta<1>();
// 	cout << arg1.toString().toStdString()<<endl;
// 	cout << arg2.toString().toStdString() << endl;

	//printe(3, 5, 3, 3, 3);

	//funn(4, 5, 6);

}


void craftTest() {

	try {
		{
			SunnyTcsCraft c1(2022128);
			qint32 i1 = c1.addSonCraft();
			qint32 i2 = c1.addSonCraft();
			qint32 i3 = c1.addSonCraft();
			qint32 i4 = c1.addSonCraft();
			qint32 i5 = c1.addSonCraft();

			c1[i1] << c1[i2];
			c1[i1] << c1[i3];
			c1[i3] << c1[i4];
			c1[i3] << c1[i5];

			c1[i5] << c1[i1];
			
			SunnyTcsOrder o1(SunnyTcsUIDWorker::getUIDWorker()->nextId(),c1);

			std::cout << o1[i1].toString().toStdString() << std::endl;
			std::cout << o1[i2].toString().toStdString() << std::endl;
			std::cout << o1[i3].toString().toStdString() << std::endl;
			std::cout << o1[i4].toString().toStdString() << std::endl;
			std::cout << o1[i5].toString().toStdString() << std::endl;
			std::cout << o1.size() << std::endl;

			
		}
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	

}

