#pragma once
#include "SunnyTcsPoint.h"

namespace basic {

	//工位
	class SUNNYTCSBASICV3_EXPORT SunnyTcsLocation:public I_SunnyTcsLocation
	{
	public:
		//ctor
		SunnyTcsLocation(qint32 id ,const SunnyTcsPoint* pt =nullptr);
		//copy ctor
		SunnyTcsLocation(const SunnyTcsLocation&) = delete;
		//detor
		virtual ~SunnyTcsLocation() {}
		//assignment
		SunnyTcsLocation& operator=(const SunnyTcsLocation&) = delete;

		const SunnyTcsPoint* getLinkPointPtr()const { return _linkedPt; }
		void bindLinkPt(const SunnyTcsPoint* pt) { _linkedPt = pt; }

		//继承虚函数
		virtual qint32 getLinkedPointId() const override;
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

		//自身虚函数
		virtual bool fromJson(QJsonObject& jobj ,const QHash<qint32,SunnyTcsPoint*>& pts) { return false; }
		virtual QJsonObject toJson()const { return QJsonObject(); }

	protected:
		const SunnyTcsPoint* _linkedPt;
	};


}



