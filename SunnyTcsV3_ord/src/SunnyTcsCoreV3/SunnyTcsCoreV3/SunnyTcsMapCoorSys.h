#pragma once

#include "SunnyTcsCoreV3.h"


using namespace basic;

namespace core {

	//Ԫ�ض���Ļ���
	class SUNNYTCSCOREV3_EXPORT A_SunnyTcsMapObject {
	public:
		//ctor
		A_SunnyTcsMapObject()  {}
		//operator
		bool operator==(const A_SunnyTcsMapObject& rhs)const { return this->getTag() == rhs.getTag(); }

		//�麯��
		virtual inline SunnyTcsMapObject_tag getTag()const = 0; 
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution)const{return QVector<SunnyTcsMapBlock>();}
		virtual bool isInRange(SunnyTcsAgvCoordinate coor)const { return false; }
	};


	//��ķ���
	enum E_SunnyTcsAxisDirection {
		Eright = 1,
		Eup = 2,
		Eleft = 3,
		Edown = 4
	};


	//��ͼ����ϵ
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

		
		//X�᾵��
		void mirrorX() { _xpos = _xpos == Eright || _xpos == Eleft ? (_xpos == Eright ? Eleft : Eright) : (_xpos == Eup) ? Edown : Eup; }
		
		//Y�᾵��
		void mirrorY() { _ypos = _ypos == Eright || _ypos == Eleft ? (_ypos == Eright ? Eleft : Eright) : (_ypos == Eup) ? Edown : Eup; }
		
		//����ϵ��ת
		void rotate() {
			qint32 xVal = static_cast<qint32>(_xpos);
			qint32 yVal = static_cast<qint32>(_ypos);
			xVal = xVal + 1 > 4 ? 1 : xVal + 1;
			yVal = yVal + 1 > 4 ? 1 : yVal + 1;
			_xpos = static_cast<E_SunnyTcsAxisDirection>(xVal);
			_ypos = static_cast<E_SunnyTcsAxisDirection>(yVal);
		}
		
		//�����麯��
		virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const {//����ʵ����ת��Ϊ��������
			return SunnyTcsAgvCoordinate();
		}

		virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene)const {
			return SunnyTcsAgvCoordinate();
		}

		// ͨ�� A_SunnyTcsMapObject �̳�
		virtual SunnyTcsMapObject_tag getTag() const override;
		

		//json
		virtual QJsonObject toJson() const ;
		virtual bool fromJson(QJsonObject& jobj, QString& reason) ;

	protected:
		const SunnyTcsAgvCoordinate _rxy;//��ʵ����
		E_SunnyTcsAxisDirection _xpos;
		E_SunnyTcsAxisDirection _ypos;
	};


}





