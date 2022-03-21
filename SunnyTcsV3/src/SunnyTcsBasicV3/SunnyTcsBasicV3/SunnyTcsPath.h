#pragma once

#include "SunnyTcsPoint.h"

namespace basic {

	class SUNNYTCSBASICV3_EXPORT SunnyTcsPath :public I_SunnyTcsEdge
	{
	public:
		SunnyTcsPath(qint32 id,const SunnyTcsPoint* start = nullptr , const SunnyTcsPoint* end =nullptr , const SunnyTcsPoint* ctrl =nullptr)
			:I_SunnyTcsEdge(id),_start(start),_end(end),_ctrl(ctrl) {}

		//getter
		inline const SunnyTcsPoint* getStart()const { return _start; }
		inline const SunnyTcsPoint* getEnd()const { return _end; }
		inline const SunnyTcsPoint* getCtrl()const { return _ctrl; }
		
		//setter
		void setStart(const SunnyTcsPoint* pt) { _start = pt; }
		void setEnd(const SunnyTcsPoint* pt) { _end = pt; }
		void setCtrl(const SunnyTcsPoint* pt) { _ctrl = pt; }
		

		// ͨ�� I_SunnyTcsEdge �̳�
		virtual qint32 getFromPointId() const override;

		virtual qint32 getCtrlPointId() const override;

		virtual qint32 getToPointId() const override;

		virtual qint32 getPathLen() const override;

		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;

		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;

		//�����麯��
		virtual bool fromJson(QJsonObject& jobj, const QHash<qint32, SunnyTcsPoint*>& pts) { return false; }
		virtual QJsonObject toJson()const { return QJsonObject(); }

	protected:
		
		//Ϊʲô���Ž��ӿ����Ϊ�ӿڲ�û��ǿ�ƹ涨��ָ��ķ�ʽ����·����
		const SunnyTcsPoint* _start;
		const SunnyTcsPoint* _end;
		const SunnyTcsPoint* _ctrl;
	};


}


