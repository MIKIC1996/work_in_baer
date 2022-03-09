#include "SunnyTcsMapPath.h"

namespace core {


	SunnyTcsMapPath::SunnyTcsMapPath(qint32 id, const SunnyTcsMapPoint * start, const SunnyTcsMapPoint * end,
		const SunnyTcsMapPoint * ctrl, qint32 positiveSpeed, bool isDoubleDirection ,
		qint32 negativeSpeed)
		:A_SunnyTcsMapObject(id),_start(start),_end(end),_ctrl(ctrl),
		_isDoubleDirection(isDoubleDirection),
		_positiveSpeed(positiveSpeed),_negativeSpeed(0)
	{}

	SunnyTcsMapPath::~SunnyTcsMapPath()
	{}

	QVector<SunnyTcsMapBlock> SunnyTcsMapPath::getBlocks(qint32 resolution) const
	{
		SunnyTcsAgvCoordinate&& start = _start->getRealityXy();
		SunnyTcsAgvCoordinate&& end = _end->getRealityXy();
		SunnyTcsAgvCoordinate&& ctrl = _ctrl ? _ctrl->getRealityXy(): SunnyTcsAgvCoordinate();

		qint32 min_x = start._x < end._x ? start._x : end._x;
		qint32 min_y = start._y < end._y ? start._y : end._y;
		qint32 max_x = start._x > end._x ? start._x : end._x;
		qint32 max_y = start._y > end._y ? start._y : end._y;

		if (_ctrl) {
			min_x = min_x < ctrl._x ? min_x : ctrl._x;
			min_y = min_y < ctrl._y ? min_y : ctrl._y;
			max_x = max_x > ctrl._x ? max_x : ctrl._x;
			max_y = max_y > ctrl._y ? max_y : ctrl._y;
		}

		min_x = min_x / resolution +1;
		min_y = min_y / resolution +1;
		max_x = max_x / resolution +1;
		max_y = max_y / resolution +1;
		
		QVector<SunnyTcsMapBlock> bs;
		for (int i = min_y; i <= max_y; ++i) {
			for (int j = min_x; j <= max_x; ++j) {
				bs << SunnyTcsMapBlock(j, i);
			}
		}
		return bs;
	}


	//根据你给定的 坐标维度，选择合适的判断方式
	bool SunnyTcsMapPath::isInRange(SunnyTcsAgvCoordinate coor) const
	{	
		if (coor._dim == E_ONE_DIMENSION ) {
			SunnyTcsAgvRange range(_start->getAbsCoor(), _end->getAbsCoor());
			return range.isInRange(coor);
		}
		else if (coor._dim == E_TWO_DIMENSION) {
			SunnyTcsAgvRange range(_start->getRealityXy(), _end->getRealityXy());
			if (_ctrl) {//这是一条曲线
				range.setArch(true);
				range.setArchPoint(_ctrl->getRealityXy());
			}
			return range.isInRange(coor);
		}
	}


	QJsonObject SunnyTcsMapPath::toJson() const
	{
		QJsonObject jobj;
		return jobj;
	}


	bool SunnyTcsMapPath::fromJson(QJsonObject& jobj, QString & reason)
	{
		return false;
	}


	SunnyTcsMapObject_tag SunnyTcsMapPath::getTag() const
	{
		return SunnyTcsMapObject_tag(Epath, _id);
	}

}



