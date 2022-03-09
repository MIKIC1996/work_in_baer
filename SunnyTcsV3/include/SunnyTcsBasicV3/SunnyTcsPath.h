#pragma once

#include "SunnyTcsPoint.h"

namespace basic {

	class SunnyTcsPath :public I_SunnyTcsEdge
	{
	public:
		SunnyTcsPath(qint32 id ,const SunnyTcsCoorSys* cs) :I_SunnyTcsEdge(id),_cs(cs) {}

		// ͨ�� I_SunnyTcsEdge �̳�
		virtual qint32 getFromPointId() const override;

		virtual qint32 getCtrlPointId() const override;

		virtual qint32 getToPointId() const override;

		virtual qint32 getPathLen() const override;

		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;

		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

	protected:
		const SunnyTcsCoorSys* _cs;
		//Ϊʲô���Ž��ӿ����Ϊ�ӿڲ�û��ǿ�ƹ涨��ָ��ķ�ʽ����·����
		const SunnyTcsPoint* _start;
		const SunnyTcsPoint* _end;
		const SunnyTcsPoint* _ctrl;

	};


}


