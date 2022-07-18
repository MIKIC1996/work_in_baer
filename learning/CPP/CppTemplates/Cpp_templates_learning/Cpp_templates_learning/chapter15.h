#pragma once
class chapter15
{
public:
	chapter15();
	~chapter15();
};


//policy and traits -----------------------------------------------------------------------------------------

//������Ļ��� ����������һ��ȱ��
template<typename T>
T accum_easy(T const* start, T const * end) { // 1 ָ������������Ϊָ��
	T ret = T(); //2 ��������û�е������ǣ�Ҳ���ᷢ��Խ�� ��  3 ��ʼ��ȡ���� ���Ĭ�Ϲ��캯�������ɿ�
	for (start; start != end; ++start) { 
		ret += *start; //4 Ĭ����ͣ�û�ж���Ϊ���в�����
	}
	return ret;
}



//ȱ�ݽ��
//ȱ��2 �� 3 ��Ҫ���������⣬ͨ������trait, ���Ӷ�ģ�����T�� ��������

template<typename T>
class AccumTraits;

template<>
class AccumTraits<int> {
public:
	typedef long long Acct; //ָ���ۼӽ������
	
	//���úó�ʼֵ�����ַ������ã�ֻ�������������ĳ�ʼֵ���޷��Ը��������� ������趨��ʼֵ
	static constexpr int zero_value = 0;

	//����ʹ�����·���
	static int get_zero_value() {
		return 0;
	}
};


template<>
class AccumTraits<float> {
public:
	typedef double Acct;

	static float get_zero_value() {
		return 0.0;
	}
};


//�����͵õ������½������ 
template<typename T ,typename Trait = AccumTraits<T> > //��ʹ�õ�Trait �ṩ�������������ͻ������Լ�����trait,����ʹ���Ҹ��ĳ�ʼֵ
typename Trait::Acct accum_with_trait(T const * start, T const * end) {  //1 ָ������������Ϊָ��
	typedef typename Trait::Acct return_type; //�����ѡ����ʵķ������͵�����
	return_type ret = Trait::get_zero_value(); //����˺��ʵĳ�ʼ������
	for (start; start != end; ++start) {
		ret += *start; //4 Ĭ����ͣ�û�ж���Ϊ���в�����
	}
	return ret;
}


//ȱ��4������1 �ṩpolicy�࣬��������Ϊ��װ
class SumPolicy {
public:
	//ʹ�ó�Ա����ģ�����ʽ
	template <typename T1 ,typename T2>
	static void accum_ope(T1 & ret, T2 const & val) {
		ret += val;
	}
};

class MutiPolicy {
public:
	//ʹ�ó�Ա����ģ�����ʽ
	template <typename T1, typename T2>
	static void accum_ope(T1 & ret, T2 const & val) {
		ret *= val;
	}
};


template<typename T, typename Policy = MutiPolicy,typename Trait = AccumTraits<T> > //���� policy �� trait ���ṩ��ȷ�е���
typename Trait::Acct accum_with_trait_policy(T const * start, T const * end) {  //1 ָ������������Ϊָ��
	typedef typename Trait::Acct return_type; //�����ѡ����ʵķ������͵�����
	return_type ret = Trait::get_zero_value(); //����˺��ʵĳ�ʼ������
	for (start; start != end; ++start) {
		Policy::accum_ope(ret , *start); //�������Ϊ���� //������ȱ��5 �� ��ʼֵ�趨 ����policy�Ĳ�ͬӦ��Ҳ��ͬ����Ȼtrait��policyӦ�ô�����ϵ
	}
	return ret;
}

//ȱ��4 ����2 ��policy��Ϊ��ģ��
template<typename T1,typename T2>
class SumPolicy_template {
public:
	static void accum_ope(T1& ret, T2 const& val) {
		ret += val;
	}
};

template<typename T1,typename T2>
class MutiPolicy_template {
public:
	static void accum_ope(T1& ret, T2 const & val) {
		ret *= val;
	}
};


template<typename T, 
	template<typename ,typename> class Policy = MutiPolicy_template , //ʹ�� ģ���ģ�����
	template<typename> class Trait = AccumTraits > //traitҲʹ�� ģ���ģ����� ����ģ�������������ģ�壨����ģ������б���ʽ�����޶� ���ô������Զ����T �� Trait�İ�
												//��֮ǰ��ָ��Ϊһ����ȷ���࣬�������ڲ�ʹ��ȱʡֵ �� �ͻ�Ҳʹ��Trait<T>��ģ�� ������� ��Ҫ�ͻ��Լ����Trait �� T�İ� ��
													//�޶��Ƚ��٣�ֻҪ�ṩһ������Ҫ�������У�����������Ҫ��
typename Trait<T>::Acct accum_with_trait_policyTemplate(T const * start, T const * end) {  //1 ָ������������Ϊָ��
	typedef typename Trait<T>::Acct return_type; //�����ѡ����ʵķ������͵�����
	return_type ret = Trait<T>::get_zero_value(); //����˺��ʵĳ�ʼ������
	for (start; start != end; ++start) {
		Policy<return_type,T>/*trait��policy�����ｨ����ϵ return_type,Ҳ������Ҫ�����trait��Ϣ������ֱ�Ӱ�trait��policy*/
			::accum_ope(ret, *start); //�������Ϊ���� //������ȱ��5 �� ��ʼֵ�趨 ����policy�Ĳ�ͬӦ��Ҳ��ͬ����Ȼtrait��policyӦ�ô�����ϵ
	}
	return ret;
}



//ȱ��5 Ҫ������ȱ�ݣ���Ϊ��ʼֵ���� policy �� trait ��ͬ�����ģ�
class MutiPolicy_finish {

	template<typename Trait>
	typename Trait::Acct getZero() {
		
	}

};


//SFINAE Ӧ��
//�����Ƿ�Ϊһ����
template<typename T>
class isClassT {
public:
	typedef char one;
	typedef struct 
	{
		char arr[2];
	} two;
	//1
	template<typename C> static one testClass(int C::*) { std::cout << "one" << std::endl; return one(); } //ֻ��TΪ�࣬������Ա ָ��Ŵ���
	//2
	template<typename C> static two testClass(...) { std::cout << "two" << std::endl; return two(); }

	enum 
	{
		Yes = (sizeof(testClass<T>(0)) == 1) //sizeof�������ú��� ��T��һ��class�� testClass�Ͱ󶨵�1 ,�����2
	};

	enum 
	{
		No = !Yes
	};

};
