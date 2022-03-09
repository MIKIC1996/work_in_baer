#include "SunnyTcsCoorSys.h"


namespace basic {


	SunnyTcsCoorSys::SunnyTcsCoorSys(qint32 id, E_SunnyTcsAxisDirection xpos, E_SunnyTcsAxisDirection ypos)
		:I_SunnyTcsCoorSys(id)
	{
		_xpos = xpos;
		_ypos = ypos;
	}

	SunnyTcsArg SunnyTcsCoorSys::getAttribution(QString key, bool & ok) const
	{
		return SunnyTcsArg();
	}

	bool SunnyTcsCoorSys::setAttribution(QString key, SunnyTcsArg arg)
	{
		return false;
	}

	SunnyTcsAgvCoordinate SunnyTcsCoorSys::transformToScene(SunnyTcsAgvCoordinate reality) const
	{
		return SunnyTcsAgvCoordinate();
	}

	SunnyTcsAgvCoordinate SunnyTcsCoorSys::transformToReality(SunnyTcsAgvCoordinate scene) const
	{
		return SunnyTcsAgvCoordinate();
	}

	

}

