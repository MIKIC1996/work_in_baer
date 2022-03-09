#pragma once

#include "SunnyTcsPoint.h"

namespace basic {

	class SunnyTcsPath :public I_SunnyTcsEdge
	{
	public:
		SunnyTcsPath(qint32 id ,const SunnyTcsCoorSys* cs) :I_SunnyTcsEdge(id),_cs(cs) {}

		// 通过 I_SunnyTcsEdge 继承
		virtual qint32 getFromPointId() const override;

		virtual qint32 getCtrlPointId() const override;

		virtual qint32 getToPointId() const override;

		virtual qint32 getPathLen() const override;

		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;

		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

	protected:
		const SunnyTcsCoorSys* _cs;
		//为什么不放进接口里？因为接口并没有强制规定以指针的方式访问路径点
		const SunnyTcsPoint* _start;
		const SunnyTcsPoint* _end;
		const SunnyTcsPoint* _ctrl;

	};


}


