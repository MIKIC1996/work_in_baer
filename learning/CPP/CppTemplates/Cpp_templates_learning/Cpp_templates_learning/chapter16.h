#pragma once




class chapter16
{
public:
	chapter16();
	~chapter16();
};



//������ṩ������ģ������� ȱʡʵ��
template< typename T1 = char ,typename T2 = int ,typename T3 = double>
class templateTest {


};


//ȱ��1: �����Ҫ�޸�T2,����T1�� Ĭ��ģ��ʵ��ҲҪд����
static templateTest<char, long> t; //char ҲҪд����




//���ȱ��1
struct DefaultArgs { //������ṩ�� Ĭ�ϵ� ��������
	typedef char P1;
	typedef int P2;
	typedef double P3;
};


//�̳������Ĭ�ϲ�������û���κ��޸�
struct PolicyDefaultArgs :virtual public DefaultArgs {}; //�����̳У�û�ж�P1 P2 P3 ���и���


//��Ĭ�ϲ���1�������޸�
template<typename T>
struct PolicyOneIs :virtual public DefaultArgs { //��P1�޸�
	typedef T P1; //����͸�����P1

};

template<typename T>
struct PolicyTwoIs :virtual public DefaultArgs { //��P1�޸�
	typedef T P2; //����͸�����P1

};

template<typename T>
struct PolicyThreeIs :virtual public DefaultArgs { //��P1�޸�
	typedef T P3; //����͸�����P1

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
		virtual public DisCriminator<Setter2, 2>,  //����DisCriminator�Ļ����ͻ��μ̳�ͬһ�������ˣ�PolicyDefaultArgs�����������
		virtual public DisCriminator< Setter3, 3>
	{

	};
	typedef ArgsSelector<PolicySetter1, PolicySetter2, PolicySetter3> Policys; //ArgsSelectorͬʱ�̳��������������ϣ�Ҳ�ͼ̳�����ص�P1,P2,P3 

};

// void test16() {
// 	std::cout << std::is_same<templateTest_better<PolicyOneIs<bool>>::Policys::P1, bool>::value << std::endl;
// }








