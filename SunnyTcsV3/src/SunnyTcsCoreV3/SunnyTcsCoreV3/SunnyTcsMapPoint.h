#pragma once

#include "SunnyTcsMapCoorSys.h"



//导航模式
#define MAP_VEHICLE_NAGAMODE_RUBBON 0x01
#define MAP_VEHICLE_NAGAMODE_INERTIA 0x02
#define MAP_VEHICLE_NAGAMODE_LASER 0x04

using namespace basic;

namespace core {

	//点
	class SUNNYTCSCOREV3_EXPORT SunnyTcsMapPoint : public A_SunnyTcsMapObject,public I_SunnyTcsVertex
	{
	public:
		SunnyTcsMapPoint(const SunnyTcsMapCoorSys* cs, qint32 id,
			qint16 mode, qint32 rx = 0, qint32 ry = 0);
		SunnyTcsMapPoint(const SunnyTcsMapPoint& rhs) = default;
		virtual ~SunnyTcsMapPoint();
		SunnyTcsMapPoint& operator=(const SunnyTcsMapPoint& rhs) {
			_cs = rhs._cs;
			_id = rhs._id;
			_nagaMode = rhs._nagaMode;
			_rxy = rhs._rxy;
			_absPos = rhs._absPos;
			_lockOwner = rhs._lockOwner;
			_usedCount = rhs._usedCount;
			return *this;
		}

		//getter
		inline const SunnyTcsMapCoorSys* getCoorSys()const { return _cs; }
		inline bool isHelpPoint()const { return _nagaMode == 0; }

		// 通过 I_SunnyTcsVertex 继承
		virtual qint32 getPointId() const override;

		virtual qint32 getPointNaga() const override;

		virtual qint32 getPointAbsPos() const override;

		virtual SunnyTcsAgvCoordinate getPointCoor() const override;

		virtual bool isPointTrafficLocked(qint32 * ve = nullptr) const override;

		virtual bool lockTraffic(qint32 ve) override;

		virtual qint32 getUsedCount() const override;

		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		
		//setter
		void setAbsPos(qint32 abs) { _absPos = abs; }
		void setRealityXy(qint32 x, qint32 y) { _rxy._x = x; _rxy._y = y; }
		void setNagativeMode(qint32 mode) { _nagaMode = mode; }
		void setCoorSys(const SunnyTcsMapCoorSys* cs) { _cs = cs; }

		// 通过 A_SunnyTcsMapObject 继承
		virtual SunnyTcsMapObject_tag getTag() const override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool isInRange(SunnyTcsAgvCoordinate coor) const override;

		//json
		virtual QJsonObject toJson() const;
		virtual bool fromJson(QJsonObject& jobj, QString & reason);

	protected:
		const SunnyTcsMapCoorSys* _cs;//坐标系指针

	};


}



