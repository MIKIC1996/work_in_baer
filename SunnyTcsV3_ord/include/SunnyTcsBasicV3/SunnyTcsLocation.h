#pragma once
#include "SunnyTcsPoint.h"

namespace basic {

	//นคฮป
	class SunnyTcsLocation:public I_SunnyTcsLocation
	{
	public:
		SunnyTcsLocation(qint32 id,const SunnyTcsCoorSys* cs);

		SunnyTcsLocation(const SunnyTcsLocation&) = delete;

		virtual ~SunnyTcsLocation() {}

		SunnyTcsLocation& operator=(const SunnyTcsLocation&) = delete;

		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

		virtual qint32 getLinkedPointId() const override;

	protected:
		const SunnyTcsCoorSys* _cs;
		const SunnyTcsPoint* _linkedPt;
	};


}



