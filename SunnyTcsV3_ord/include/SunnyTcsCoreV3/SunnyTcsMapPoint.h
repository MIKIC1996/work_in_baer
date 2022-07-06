#pragma once

#include "SunnyTcsMapCoorSys.h"



//����ģʽ
#define MAP_VEHICLE_NAGAMODE_RUBBON 0x01
#define MAP_VEHICLE_NAGAMODE_INERTIA 0x02
#define MAP_VEHICLE_NAGAMODE_LASER 0x04


namespace core {

	//��
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

		// ͨ�� A_SunnyTcsMapObject �̳�
		virtual SunnyTcsMapObject_tag getTag() const override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool isInRange(SunnyTcsAgvCoordinate coor) const override;
		
		//json
		virtual QJsonObject toJson() const;
		virtual bool fromJson(QJsonObject& jobj, QString & reason);

	protected:
		qint32 _absPos;//��ľ���λ��
		SunnyTcsAgvCoordinate _rxy;//�ߵ����ö�ά,�����ö�ά��������Ϊ��
		qint32 _nagaMode; //һ����Ҳ������ ���ֵ�����ʽ ��0 ������ ��1 ɫ���㣬2 �ߵ��㣬4 �����
		const SunnyTcsMapCoorSys* _cs;//����ϵָ��
		
	};


}



