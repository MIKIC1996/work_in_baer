#pragma once

#include "SunnyTcsPoint.h"

namespace basic {

	class SUNNYTCSBASICV3_EXPORT SunnyTcsPath :public I_SunnyTcsEdge
	{
	public:
		SunnyTcsPath(qint32 id,const SunnyTcsPoint* start = nullptr , const SunnyTcsPoint* end =nullptr , const SunnyTcsPoint* ctrl =nullptr)
			:I_SunnyTcsEdge(id),_start(start),_end(end),_ctrl(ctrl) {}

		//getter
		const SunnyTcsPoint* getStart()const { return _start; }
		const SunnyTcsPoint* getEnd()const { return _end; }
		const SunnyTcsPoint* getCtrl()const { return _ctrl; }

		//setter
		void setStart(const SunnyTcsPoint* pt) { _start = pt; }
		void setEnd(const SunnyTcsPoint* pt) { _end = pt; }
		void setCtrl(const SunnyTcsPoint* pt) { _ctrl = pt; }

		// 通过 I_SunnyTcsEdge 继承
		virtual qint32 getFromPointId() const override;

		virtual qint32 getCtrlPointId() const override;

		virtual qint32 getToPointId() const override;

		virtual qint32 getPathLen() const override;

		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;

		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

	protected:
		//为什么不放进接口里？因为接口并没有强制规定以指针的方式访问路径点
		const SunnyTcsPoint* _start;
		const SunnyTcsPoint* _end;
		const SunnyTcsPoint* _ctrl;
	};


}


