#pragma once

#include  "basic_general_lib.h"

/*

template<typename _Ty>
_Ty SunnyTcsNextResDefaultPolicy<_Ty>::getNextRes(const _Ty& val) {
	return val + 1;
}



@function: ��ֵ�Ƿ����ͨ��getNextRes�������
@param : ��ֵ��ʼֵ
@param : ��ֵĿ��ֵ
@return : ����0��ʾ���Խ�����ã�����0��ʾ left����right������ͨ��0���������, С��0 ��ʾ���ɽ������

template<typename _Ty>
bool SunnyTcsNextResDefaultPolicy<_Ty> ::isLeftCanStepToRight(_Ty const& left, _Ty const& right)
{
	return  (right - left) * (getNextRes(left) - left) >= 0;
}



template<typename _Ty>
bool SunnyTcsNextResDefaultPolicy<_Ty> :: operator()(_Ty const& left, _Ty const& right) {
	return left > right;
}


template<
	typename _Ty,
	template<typename> class _NextResPolicy,
	template<typename, typename, typename > class _Container
>
SunnyTcsUniqueIdManager<_Ty, _NextResPolicy, _Container> ::SunnyTcsUniqueIdManager(_Ty const& val)
	:_que(), _start(val)
{
	_que.push(val);
	supplyId();
}





template<
	typename _Ty,
	template<typename> class _NextResPolicy,
	template<typename, typename, typename > class _Container
>
_Ty SunnyTcsUniqueIdManager<_Ty, _NextResPolicy, _Container> ::getNextId()
{
	supplyId();
	_Ty ret = _que.top();
	_que.pop();
	return ret;
}



template<
	typename _Ty,
	template<typename> class _NextResPolicy,
	template<typename, typename, typename > class _Container
>
bool SunnyTcsUniqueIdManager<_Ty, _NextResPolicy, _Container> ::applyForId(_Ty id)
{
	if (!NextResPolicy::isLeftCanStepToRight(_start, id)) {
		return false;//Ŀ��ֵ�� ��ʼֵ�����н����������
	}
	supplyId();
	_Ty topVal;
	_Container temp;
	bool finded = false;
	while (_que.size() > 0) {
		topVal = _que.top();
		if (topVal != id) {
			temp.push(topVal);
		}
		else {
			finded = true;
			supplyId();//�����ʱ�Ѿ��Ǳ��������һ����Դ�ˣ������Ȳ�����
		}
		_que.pop();
	}
	_que = temp;
	if (!finded) {	//�ִ���û�ҵ�Ŀ��
		if (NextResPolicy::isLeftCanStepToRight(id, topVal)) { //��ֵ�ڵ�ǰ������Դ��Χ�ڣ�����ȴû���ҵ���˵����Դ������
			return false; //����ID ������
		}
		while (topVal != id) { //��ID����
			topVal = NextResPolicy::getNextRes(topVal); //���� 1
			if (topVal != id) {
				_que.push(topVal);
			}
		}
	}
	return true;
}



template<
	typename _Ty,
	template<typename> class _NextResPolicy,
	template<typename, typename, typename > class _Container
>
void SunnyTcsUniqueIdManager<_Ty, _NextResPolicy, _Container> ::supplyId() {
	if (_que.size() == 1) {
		_que.push(_NextResPolicy<_Ty>::getNextRes(_que.top()));
	}
}



template<
	typename _Ty,
	template<typename> class _NextResPolicy,
	template<typename, typename, typename > class _Container
>
void SunnyTcsUniqueIdManager<_Ty, _NextResPolicy, _Container> ::returnId(_Ty id) {
	_que.push(id);
}




template<typename _Ty>
SunnyTcsUniqueIdKeeper<_Ty>::SunnyTcsUniqueIdKeeper(IdManager * idm)
	: _idm(idm)
{
	assert(idm);
	_res = _idm->getNextId();
}
*/

namespace basic {

	/*
	
	

	*/


}


