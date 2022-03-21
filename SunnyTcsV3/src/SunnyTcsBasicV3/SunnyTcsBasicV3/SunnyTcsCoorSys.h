#pragma once
#include "SunnyTcsMapActualData.hpp"






namespace basic {


	//��ͼ����ϵ
	class SUNNYTCSBASICV3_EXPORT SunnyTcsCoorSys : public I_SunnyTcsCoorSys
	{
	public:
		//ctor
		SunnyTcsCoorSys(qint32 id, E_SunnyTcsAxisDirection xpos = Eright, E_SunnyTcsAxisDirection ypos = Eup);
		//copy ctor
		SunnyTcsCoorSys(const SunnyTcsCoorSys& rhs) = delete;

		virtual ~SunnyTcsCoorSys() {}
		
		SunnyTcsCoorSys& operator=(const SunnyTcsCoorSys& rhs) = delete;

		// ͨ�� I_SunnyTcsCoorSys �̳�
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;

		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

		virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality) const override;

		virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene) const override;

		//�����麯��
		virtual bool fromJson(QJsonObject& jobj) { return false; }
		virtual QJsonObject toJson()const { return QJsonObject(); }

	};


}




