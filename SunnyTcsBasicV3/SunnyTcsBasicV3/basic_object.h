#pragma once

#include "basic_defs.h"



class SunnyTcsObjectData;
class SunnyTcsObjectPrivate;
class BASIC_EXPORT SunnyTcsObject {
	TCS_DECLARE_PRIVATE(SunnyTcsObject)
public:
	SunnyTcsObject();
protected:
	SunnyTcsObject(std::shared_ptr<SunnyTcsObjectData>);
private:
	std::shared_ptr<SunnyTcsObjectData> d_ptr;
};