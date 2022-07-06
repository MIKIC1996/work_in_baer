#pragma once

#include  "basic_general_lib.h"

/*

template<typename _Ty>
_Ty SunnyTcsNextResDefaultPolicy<_Ty>::getNextRes(const _Ty& val) {
	return val + 1;
}



@function: 左值是否可以通过getNextRes渐进获得
@param : 左值起始值
@param : 右值目标值
@return : 大于0表示可以渐进获得，等于0表示 left等于right，可以通过0步渐进获得, 小于0 表示不可渐进获得

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
		return false;//目标值与 起始值不具有渐进获得性质
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
			supplyId();//如果这时已经是遍历到最后一个资源了，必须先补充下
		}
		_que.pop();
	}
	_que = temp;
	if (!finded) {	//现存中没找到目标
		if (NextResPolicy::isLeftCanStepToRight(id, topVal)) { //该值在当前已有资源范围内，可是却没有找到，说明资源不可用
			return false; //该新ID 不可用
		}
		while (topVal != id) { //新ID可用
			topVal = NextResPolicy::getNextRes(topVal); //自增 1
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


