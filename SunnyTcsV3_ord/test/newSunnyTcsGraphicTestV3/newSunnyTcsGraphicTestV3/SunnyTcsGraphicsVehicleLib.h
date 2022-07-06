#pragma once


#include "SunnyTcsGraphicsVehicle.h"




class SunnyTcsGraphicsVehicle_normal :public SunnyTcsVehicle_normal, public SunnyTcsGraphicsVehicle {
public:
	//ctor
	SunnyTcsGraphicsVehicle_normal(const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad, QPointF pt = QPointF(0, 0));
	//copy ctor
	SunnyTcsGraphicsVehicle_normal(const SunnyTcsGraphicsVehicle_normal&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsVehicle_normal() {}
	//assignment
	SunnyTcsGraphicsVehicle_normal& operator=(const SunnyTcsGraphicsVehicle_normal&) = delete;



protected:


};