#include "SunnyTcsGraphicsVehicleLib.h"

SunnyTcsGraphicsVehicle_normal::SunnyTcsGraphicsVehicle_normal(const SunnyTcsGraphicsCoorSys * cs, const SunnyTcsMapAdjuster * ad, QPointF pt)
	:SunnyTcsVehicle_normal(ad->nextVeId()),SunnyTcsGraphicsVehicle(cs,ad,pt)
{
	
}
