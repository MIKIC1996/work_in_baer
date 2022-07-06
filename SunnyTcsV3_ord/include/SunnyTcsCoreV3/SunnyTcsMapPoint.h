#pragma once

#include "SunnyTcsMapCoorSys.h"



//导航模式
#define MAP_VEHICLE_NAGAMODE_RUBBON 0x01
#define MAP_VEHICLE_NAGAMODE_INERTIA 0x02
#define MAP_VEHICLE_NAGAMODE_LASER 0x04


namespace core {

	//点
	class SUNNYTCSCOREV3_EXPORT SunnyTcsMapPoint : public A_SunnyTcsMapObject
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
			return *this;
		}

		//getter
		inline SunnyTcsAgvCoordinate getAbsCoor()const { return SunnyTcsAgvCoordinate(E_ONE_DIMENSION,_absPos); }
		inline qint32 getAbsPos()const { return _absPos; }
		inline SunnyTcsAgvCoordinate getRealityXy()const { return _rxy; }
		inline qint32 getNagetiveMode()const { return _nagaMode; }
		inline const SunnyTcsMapCoorSys* getCoorSys()const { return _cs; }
		inline bool isHelpPoint()const { return _nagaMode == 0; }
		
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
		qint32 _absPos;//点的绝对位置
		SunnyTcsAgvCoordinate _rxy;//惯导点用二维,激光用二维，辅助点为空
		qint32 _nagaMode; //一个点也可以是 多种导航方式 ，0 辅助点 ，1 色带点，2 惯导点，4 激光点
		const SunnyTcsMapCoorSys* _cs;//坐标系指针
		
	};


}



