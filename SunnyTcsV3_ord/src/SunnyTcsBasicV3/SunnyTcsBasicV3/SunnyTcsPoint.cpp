#include "SunnyTcsPoint.h"



namespace basic {




	SunnyTcsArg SunnyTcsPoint::getAttribution(QString key, bool & ok) const
	{
		return SunnyTcsArg();
	}

	bool SunnyTcsPoint::setAttribution(QString key, SunnyTcsArg arg)
	{
		return false;
	}


	QVector<SunnyTcsMapBlock> SunnyTcsPoint::getBlocks(qint32 resolution) const
	{
		QVector<SunnyTcsMapBlock> bs;
		bs << SunnyTcsMapBlock(_rxy._x / resolution + 1, _rxy._y / resolution + 1);
		return bs;
	}


	bool SunnyTcsPoint::isInRange(SunnyTcsAgvCoordinate coor) const
	{
		if (E_ONE_DIMENSION == coor._dim) {
			return qAbs(coor._x - _absPos) < ORIENTATION_INACCURACY;
		}
		else {
			return qSqrt((coor._x - _rxy._x)*(coor._x - _rxy._x) + (coor._y - _rxy._y)*(coor._y - _rxy._y)) < ORIENTATION_INACCURACY;
		}
		return false;
	}



}