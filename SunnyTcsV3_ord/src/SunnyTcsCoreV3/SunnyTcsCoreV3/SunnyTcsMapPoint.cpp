#include "SunnyTcsMapPoint.h"

namespace core {



	SunnyTcsMapPoint::SunnyTcsMapPoint(const SunnyTcsMapCoorSys * cs, qint32 id, qint16 mode,
		qint32 rx, qint32 ry )
		:A_SunnyTcsMapObject(id),_cs(cs),
		_nagaMode(mode),_rxy(E_TWO_DIMENSION,0,0,0),_absPos(0),
		_lockOwner(0),_usedCount(0)
	{
		
	}


	SunnyTcsMapPoint::~SunnyTcsMapPoint()
	{
	}

	SunnyTcsMapObject_tag SunnyTcsMapPoint::getTag() const
	{
		return SunnyTcsMapObject_tag(Epoint, _id);
	}

	QVector<SunnyTcsMapBlock> SunnyTcsMapPoint::getBlocks(qint32 resolution) const
	{

		QVector<SunnyTcsMapBlock> bs;
		bs << SunnyTcsMapBlock(_rxy._x / resolution + 1, _rxy._y / resolution + 1);
		return bs;
	}


	bool SunnyTcsMapPoint::isInRange(SunnyTcsAgvCoordinate coor) const
	{
		if (E_ONE_DIMENSION == coor._dim) {
			return qAbs(coor._x - _absPos) < ORIENTATION_INACCURACY;
		}
		else {
			return qSqrt((coor._x - _rxy._x)*(coor._x - _rxy._x) + (coor._y - _rxy._y)*(coor._y - _rxy._y)) < ORIENTATION_INACCURACY;
		}
		return false;
	}



	QJsonObject SunnyTcsMapPoint::toJson() const
	{
		QJsonObject jobj;
		
		return jobj;
	}

	bool SunnyTcsMapPoint::fromJson(QJsonObject& jobj, QString & reason)
	{
		
		return false;
	}

	//I_SunnyTcsVertex
	qint32 SunnyTcsMapPoint::getPointId() const
	{
		return this->getId();
	}

	qint32 SunnyTcsMapPoint::getPointNaga() const
	{
		return _nagaMode;
	}

	qint32 SunnyTcsMapPoint::getPointAbsPos() const
	{
		return _absPos;
	}

	SunnyTcsAgvCoordinate SunnyTcsMapPoint::getPointCoor() const
	{
		return _rxy;
	}

	bool SunnyTcsMapPoint::isPointTrafficLocked(qint32 * ve = nullptr) const
	{
		if (ve) {
			*ve = _lockOwner;
		}
		return _lockOwner != 0;
	}

	bool SunnyTcsMapPoint::lockTraffic(qint32 ve) 
	{
		_lockOwner = (_lockOwner == 0 ? ve : _lockOwner);
		return (_lockOwner == ve ? true : false);
	}

	qint32 SunnyTcsMapPoint::getUsedCount() const
	{
		return _usedCount;
	}

	SunnyTcsArg SunnyTcsMapPoint::getAttribution(QString key, bool & ok) const
	{
		return SunnyTcsArg();
	}



	


}

