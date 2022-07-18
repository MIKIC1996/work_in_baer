#pragma once


#include "basic_stack.h"

#define RPN_BOOL_INDEX 0
#define RPN_INTEGER_INDEX 1
#define RPN_DOUBLE_INDEX 2


#define RPNP(obj) SunnyTcsRpnParamsSet(obj)
#define RPNO(obj) SunnyTcsRpnOperatorSignal(SunnyTcsRpnOperatorSignal::obj)

using Boolean_tcs = bool;
using Integer_tcs = int32_t;
using Double_tcs = double;
//ʹ��variant���� ���������Ϳ��Ա�֤���͵�ͳһ
typedef std::variant<Boolean_tcs, Integer_tcs, Double_tcs> SunnyTcsRpnParamsSet;


class SunnyTcsRpnOperatorSignal {
public:
	enum OperatorType {
		Add = 1,
		Minus =2 ,
		Multiply =3,
		Divede =4,
		And =6,
		Or =5,
		LeftPa = 7, 
		RightPa= 8
	};
	//ctor
	explicit SunnyTcsRpnOperatorSignal(OperatorType t):m_type(t){}

	//�ǲ���������
	inline bool isLeftPa()const { return m_type == LeftPa; }

	//�ǲ���������
	inline bool isRightPa()const { return m_type == RightPa; }

	//��ȡ���ȼ�
	inline int getPriority()const { return (int)(m_type); }

	//���������
	inline SunnyTcsRpnParamsSet caculate(SunnyTcsRpnParamsSet const& var1, SunnyTcsRpnParamsSet const& var2) {
		assert(var1.index() == var2.index());
		if (0 == var1.index()) {
			return caculate_boolean(var1, var2);
		}
		else if (1 == var1.index()) {
			return caculate_integer(var1, var2);
		}
		else {
			return caculate_double(var1, var2);
		}
	}

private:
	SunnyTcsRpnParamsSet caculate_boolean(SunnyTcsRpnParamsSet const& v1, SunnyTcsRpnParamsSet const& v2) {
		Boolean_tcs var1 = std::get<0>(v1);
		Boolean_tcs var2 = std::get<0>(v2);
		assert(m_type == And || m_type == Or);
		return SunnyTcsRpnParamsSet(m_type == And ? var1 & var2 : var1 | var2);
	}

	SunnyTcsRpnParamsSet caculate_integer(SunnyTcsRpnParamsSet const& v1, SunnyTcsRpnParamsSet const& v2) {
		Integer_tcs var1 = std::get<1>(v1);
		Integer_tcs var2 = std::get<1>(v2);
		switch (m_type)
		{
		case SunnyTcsRpnOperatorSignal::Add:
			return SunnyTcsRpnParamsSet( (Integer_tcs)( var1 + var2));
		case SunnyTcsRpnOperatorSignal::Minus:
			return SunnyTcsRpnParamsSet( (Integer_tcs)(var1 - var2));
		case SunnyTcsRpnOperatorSignal::Multiply:
			return SunnyTcsRpnParamsSet( (Integer_tcs)( var1 * var2));
		case SunnyTcsRpnOperatorSignal::Divede:
			return SunnyTcsRpnParamsSet( (Integer_tcs)(var1 / var2));
		default:
			assert(false);
		}
	}

	SunnyTcsRpnParamsSet caculate_double(SunnyTcsRpnParamsSet const& v1, SunnyTcsRpnParamsSet const& v2) {
		Double_tcs var1 = std::get<2>(v1);
		Double_tcs var2 = std::get<2>(v2);
		switch (m_type)
		{
		case SunnyTcsRpnOperatorSignal::Add:
			return SunnyTcsRpnParamsSet( (Double_tcs) (var1 + var2));
		case SunnyTcsRpnOperatorSignal::Minus:
			return SunnyTcsRpnParamsSet( (Double_tcs)(var1 - var2));
		case SunnyTcsRpnOperatorSignal::Multiply:
			return SunnyTcsRpnParamsSet( (Double_tcs)( var1 * var2));
		case SunnyTcsRpnOperatorSignal::Divede:
			return SunnyTcsRpnParamsSet( (Double_tcs)(var1 / var2));
		default:
			assert(false);
		}
	}

private:
	OperatorType m_type;
};

//Ԫ��
typedef std::variant<SunnyTcsRpnParamsSet, SunnyTcsRpnOperatorSignal> SunnyTcsRpnElement;

//�������
enum RpnErrorCode {
	RpnNoError = 0
};


class SunnyTcsRpn {
public:
	typedef SunnyTcsStack<SunnyTcsRpnParamsSet> ParamsStack;
	typedef SunnyTcsStack<SunnyTcsRpnOperatorSignal> OperatorStack;

	RpnErrorCode errorno()const { return RpnNoError; }

	SunnyTcsRpnParamsSet reversePolishNotation(std::vector<SunnyTcsRpnElement>& eles ) {
		ParamsStack pstack;
		OperatorStack ostack;
		bool isLastNum = false; //��һ���Ƿ�������
		
		while(eles.size()>0) {
			auto iter = eles.begin();
			if (0 == (*iter).index()) //�ǲ���
			{
				if (isLastNum)return SunnyTcsRpnParamsSet();//�������γ�������
				pstack.push(std::get<0>(*iter));
				iter = eles.erase(iter);
			}
			else { //�ǲ�����
				SunnyTcsRpnOperatorSignal ope = std::get<1>(*iter);
				iter = eles.erase(iter);
				if (ope.isLeftPa())
				{
					pstack.push( reversePolishNotation(eles));//�����ŵݹ��������
				}
				else if (ope.isRightPa()) { //������˵�������ǵݹ���ã�Ҫ��������
					break;
				}
				else {
					if (ostack.empty()) { //����Ϊ��
						ostack.push(ope);
					}
					else {
						SunnyTcsRpnOperatorSignal topOpe = ostack.top();
						if (ope.getPriority() <= topOpe.getPriority()) { //�·��ŵ����ȼ��ϵͻ������
							SunnyTcsRpnParamsSet value1 = pstack.top();
							pstack.pop();
							SunnyTcsRpnParamsSet value2 = pstack.top();
							pstack.pop();
							SunnyTcsRpnOperatorSignal ope = ostack.top();
							ostack.pop();
							pstack.push(ope.caculate(value2, value1));
						}
						else {
							ostack.push(ope);
						}
					}
				}
				
			}
		}
		//����
		assert(pstack.size() == ostack.size() + 1);
		while (ostack.size()) {
			SunnyTcsRpnParamsSet value1 = pstack.top();
			pstack.pop();
			SunnyTcsRpnParamsSet value2 = pstack.top();
			pstack.pop();
			SunnyTcsRpnOperatorSignal ope = ostack.top();
			ostack.pop();
			pstack.push(ope.caculate(value2, value1));
		}
		return pstack.top();
	}

};



