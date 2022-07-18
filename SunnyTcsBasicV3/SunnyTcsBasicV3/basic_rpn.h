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
//使用variant来存 参数集，就可以保证类型的统一
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

	//是不是左括号
	inline bool isLeftPa()const { return m_type == LeftPa; }

	//是不是右括号
	inline bool isRightPa()const { return m_type == RightPa; }

	//获取优先级
	inline int getPriority()const { return (int)(m_type); }

	//运算符计算
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

//元素
typedef std::variant<SunnyTcsRpnParamsSet, SunnyTcsRpnOperatorSignal> SunnyTcsRpnElement;

//运算错误
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
		bool isLastNum = false; //上一个是否是数字
		
		while(eles.size()>0) {
			auto iter = eles.begin();
			if (0 == (*iter).index()) //是参数
			{
				if (isLastNum)return SunnyTcsRpnParamsSet();//连续两次出现数字
				pstack.push(std::get<0>(*iter));
				iter = eles.erase(iter);
			}
			else { //是操作符
				SunnyTcsRpnOperatorSignal ope = std::get<1>(*iter);
				iter = eles.erase(iter);
				if (ope.isLeftPa())
				{
					pstack.push( reversePolishNotation(eles));//左括号递归调用自身
				}
				else if (ope.isRightPa()) { //右括号说明自身是递归调用，要结束自身
					break;
				}
				else {
					if (ostack.empty()) { //符号为空
						ostack.push(ope);
					}
					else {
						SunnyTcsRpnOperatorSignal topOpe = ostack.top();
						if (ope.getPriority() <= topOpe.getPriority()) { //新符号的优先级较低或者相等
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
		//计算
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



