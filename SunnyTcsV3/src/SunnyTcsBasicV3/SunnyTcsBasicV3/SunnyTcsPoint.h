#pragma once
#include "SunnyTcsMapActualData.hpp"
#include "SunnyTcsCoorSys.h"

namespace basic {

	//pt
	class SUNNYTCSBASICV3_EXPORT SunnyTcsPoint : public I_SunnyTcsVertex{
	public:
		//ctor
		SunnyTcsPoint(qint32 id ,const SunnyTcsCoorSys* cs) : I_SunnyTcsVertex(id),_cs(cs) {}
		//copy ctor
		SunnyTcsPoint(const SunnyTcsPoint&) = delete;
		//dtor
		virtual ~SunnyTcsPoint() {}
		//assignment
		SunnyTcsPoint& operator=(const SunnyTcsPoint&) = delete;

		// Í¨¹ý I_SunnyTcsVertex ¼Ì³Ð
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool isInRange(SunnyTcsAgvCoordinate coor) const override;

	protected:
		const SunnyTcsCoorSys* _cs;
	};
	

}
