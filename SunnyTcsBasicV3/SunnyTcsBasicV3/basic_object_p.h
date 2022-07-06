#pragma once
#include "basic_object.h"


class SunnyTcsObjectData {
public:
	virtual ~SunnyTcsObjectData() = 0;
};




class SunnyTcsObjectPrivate
	:public SunnyTcsObjectData {
public:
	virtual ~SunnyTcsObjectPrivate(){}

};

