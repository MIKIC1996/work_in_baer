#include "SunnyTcsLocation.h"



namespace basic {


	SunnyTcsLocation::SunnyTcsLocation(qint32 id, const SunnyTcsPoint * pt)
		:I_SunnyTcsLocation(id),_linkedPt(pt)
	{
	}

	SunnyTcsArg SunnyTcsLocation::getAttribution(QString key, bool & ok) const
	{
		return SunnyTcsArg();
	}

	bool SunnyTcsLocation::setAttribution(QString key, SunnyTcsArg arg)
	{
		return false;
	}

	qint32 SunnyTcsLocation::getLinkedPointId() const
	{
		return _linkedPt->getElementId();
	}



}