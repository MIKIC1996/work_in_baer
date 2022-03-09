#pragma once
#include "SunnyTcsPoint.h"

namespace basic {

	//นคฮป
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
		
		void bindLinkPt(const SunnyTcsPoint* pt) { _linkedPt = pt; }

		virtual qint32 getLinkedPointId() const override;
		const SunnyTcsPoint* getLinkPointPtr()const { return _linkedPt; }
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

	protected:
		const SunnyTcsPoint* _linkedPt;
	};


}



