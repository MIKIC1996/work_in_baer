#include "pch.h"
#include "basic_object_p.h"





SunnyTcsObjectData::~SunnyTcsObjectData(){}



SunnyTcsObject::SunnyTcsObject():d_ptr(std::make_shared<SunnyTcsObjectPrivate>()){}



SunnyTcsObject::SunnyTcsObject(std::shared_ptr<SunnyTcsObjectData> d):d_ptr(d){}










