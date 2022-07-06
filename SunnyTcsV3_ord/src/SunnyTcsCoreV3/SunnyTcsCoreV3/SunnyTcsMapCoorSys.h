#pragma once

#include "SunnyTcsCoreV3.h"


using namespace basic;

namespace core {

	//元素对象的基类
	class SUNNYTCSCOREV3_EXPORT A_SunnyTcsMapObject {
	public:
		//ctor
		A_SunnyTcsMapObject()  {}
		//operator
		bool operator==(const A_SunnyTcsMapObject& rhs)const { return this->getTag() == rhs.getTag(); }

		//虚函数
		virtual inline SunnyTcsMapObject_tag getTag()const = 0; 
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution)const{return QVector<SunnyTcsMapBlock>();}
		virtual bool isInRange(SunnyTcsAgvCoordinate coor)const { return false; }
	};


	//轴的方向
	enum E_SunnyTcsAxisDirection {
		Eright = 1,
		Eup = 2,
		Eleft = 3,
		Edown = 4
	};


	//地图坐标系
	class  SUNNYTCSCOREV3_EXPORT SunnyTcsMapCoorSys :
		public A_SunnyTcsMapObject
	{
	public:
		//tor
		SunnyTcsMapCoorSys(qint32 id, E_SunnyTcsAxisDirection xpos = Eright, E_SunnyTcsAxisDirection ypos = Eup);
		SunnyTcsMapCoorSys(const SunnyTcsMapCoorSys& rhs);
		virtual ~SunnyTcsMapCoorSys();
		SunnyTcsMapCoorSys& operator=(const SunnyTcsMapCoorSys& rhs);

		//getter
		inline SunnyTcsAgvCoordinate getRealityXy()const { return _rxy; }
		inline E_SunnyTcsAxisDirection getAxisDirectionX()const { return _xpos; }
		inline E_SunnyTcsAxisDirection getAxisDirectionY()const { return _ypos; }

		
		//X轴镜像
		void mirrorX() { _xpos = _xpos == Eright || _xpos == Eleft ? (_xpos == Eright ? Eleft : Eright) : (_xpos == Eup) ? Edown : Eup; }
		
		//Y轴镜像
		void mirrorY() { _ypos = _ypos == Eright || _ypos == Eleft ? (_ypos == Eright ? Eleft : Eright) : (_ypos == Eup) ? Edown : Eup; }
		
		//坐标系旋转
		void rotate() {
			qint32 xVal = static_cast<qint32>(_xpos);
			qint32 yVal = static_cast<qint32>(_ypos);
			xVal = xVal + 1 > 4 ? 1 : xVal + 1;
			yVal = yVal + 1 > 4 ? 1 : yVal + 1;
			_xpos = static_cast<E_SunnyTcsAxisDirection>(xVal);
			_ypos = static_cast<E_SunnyTcsAxisDirection>(yVal);
		}
		
		//自身虚函数
		virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const {//将现实坐标转换为场景坐标
			return SunnyTcsAgvCoordinate();
		}

		virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene)const {
			return SunnyTcsAgvCoordinate();
		}

		// 通过 A_SunnyTcsMapObject 继承
		virtual SunnyTcsMapObject_tag getTag() const override;
		

		//json
		virtual QJsonObject toJson() const ;
		virtual bool fromJson(QJsonObject& jobj, QString& reason) ;

	protected:
		const SunnyTcsAgvCoordinate _rxy;//现实坐标
		E_SunnyTcsAxisDirection _xpos;
		E_SunnyTcsAxisDirection _ypos;
	};


}





