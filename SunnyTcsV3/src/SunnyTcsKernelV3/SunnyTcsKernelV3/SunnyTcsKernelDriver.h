#pragma once

#include "SunnyTcsKernelGeneral.h"







class SunnyTcsKernelDriver
{
public:
	SunnyTcsKernelDriver();
	virtual ~SunnyTcsKernelDriver();


	template<typename _Signature_type,typename _Functor,typename... _Args>
	void submit(_Signature_type* sig, _Functor&& f, _Args... rest) {}

};

