#include "SunnyTcsMapCoorSys.h"


namespace core {

	qint32 A_SunnyTcsMapObject::park_inaccuracy = 10;
	qint32 A_SunnyTcsMapObject::running_inaccuracy = 50;



	SunnyTcsMapCoorSys::SunnyTcsMapCoorSys(qint32 id,  E_SunnyTcsAxisDirection xpos, E_SunnyTcsAxisDirection ypos)
		: A_SunnyTcsMapObject(id), _rxy(E_TWO_DIMENSION,0,0,0), _xpos(xpos), _ypos(ypos)
	{
		
	}


	SunnyTcsMapCoorSys::SunnyTcsMapCoorSys(const SunnyTcsMapCoorSys & rhs)
		: A_SunnyTcsMapObject(rhs), _rxy(rhs._rxy), _xpos(rhs._xpos), _ypos(rhs._ypos)
	{

	}


	SunnyTcsMapCoorSys::~SunnyTcsMapCoorSys()
	{

	}

	SunnyTcsMapCoorSys& SunnyTcsMapCoorSys::operator=(const SunnyTcsMapCoorSys& rhs) {
		_id = rhs._id;
		_xpos = rhs._xpos;
		_ypos = rhs._ypos;
		return *this;
	}



	QJsonObject SunnyTcsMapCoorSys::toJson() const
	{
		QJsonObject jobj;
		return jobj;
	}


	bool SunnyTcsMapCoorSys::fromJson(QJsonObject& jobj, QString& reason)
	{
		return false;
	}


	SunnyTcsMapObject_tag SunnyTcsMapCoorSys::getTag() const
	{
		return SunnyTcsMapObject_tag(Ecoorsys, _id);
	}


}

	
