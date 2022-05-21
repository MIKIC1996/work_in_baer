#pragma once




class chapter16
{
public:
	chapter16();
	~chapter16();
};



//这个类提供了所有模板参数的 缺省实参
template< typename T1 = char ,typename T2 = int ,typename T3 = double>
class templateTest {


};


//缺陷1: 如果你要修改T2,就连T1的 默认模板实参也要写出来
static templateTest<char, long> t; //char 也要写出来




//解决缺陷1
struct DefaultArgs { //这个类提供了 默认的 参数集合
	typedef char P1;
	typedef int P2;
	typedef double P3;
};


//继承上面的默认参数集，没有任何修改
struct PolicyDefaultArgs :virtual public DefaultArgs {}; //单纯继承，没有对P1 P2 P3 进行覆盖


//对默认参数1进行了修改
template<typename T>
struct PolicyOneIs :virtual public DefaultArgs { //对P1修改
	typedef T P1; //这里就覆盖了P1

};

template<typename T>
struct PolicyTwoIs :virtual public DefaultArgs { //对P1修改
	typedef T P2; //这里就覆盖了P1

};

template<typename T>
struct PolicyThreeIs :virtual public DefaultArgs { //对P1修改
	typedef T P3; //这里就覆盖了P1

};



template<typename Base,int num>
struct DisCriminator :public Base { 


};


template< typename PolicySetter1 = PolicyDefaultArgs, 
	typename PolicySetter2 = PolicyDefaultArgs,
	typename PolicySetter3 = PolicyDefaultArgs>
struct templateTest_better {

	template<typename Setter1 ,typename Setter2 ,typename Setter3>
	struct ArgsSelector :
		virtual public DisCriminator<Setter1, 1>,
		virtual public DisCriminator<Setter2, 2>,  //不用DisCriminator的话，就会多次继承同一个基类了（PolicyDefaultArgs），编译错误
		virtual public DisCriminator< Setter3, 3>
	{

	};
	typedef ArgsSelector<PolicySetter1, PolicySetter2, PolicySetter3> Policys; //ArgsSelector同时继承与三个参数集合，也就继承了相关的P1,P2,P3 

};

// void test16() {
// 	std::cout << std::is_same<templateTest_better<PolicyOneIs<bool>>::Policys::P1, bool>::value << std::endl;
// }









