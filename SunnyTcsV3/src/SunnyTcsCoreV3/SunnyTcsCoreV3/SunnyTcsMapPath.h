#pragma once

#include "SunnyTcsMapPoint.h"


namespace core {


	class SUNNYTCSCOREV3_EXPORT  SunnyTcsMapPath : public A_SunnyTcsMapObject
	{
	public:
		SunnyTcsMapPath(qint32 id,
			const SunnyTcsMapPoint* start = nullptr,
			const SunnyTcsMapPoint* end = nullptr,
			const SunnyTcsMapPoint* ctrl = nullptr,
			qint32 positiveSpeed = 0,
			bool isDoubleDirection = true,
			qint32 negativeSpeed = 0

		);

		SunnyTcsMapPath(const SunnyTcsMapPath&) = default;

		virtual ~SunnyTcsMapPath();

		SunnyTcsMapPath& operator=(const SunnyTcsMapPath&) = default;

		//getter 
		inline qint32 getVirtualLinkFlag()const { return _virtualLinkFlag; }
		inline const SunnyTcsMapPoint* start()const { return _start; }
		inline const SunnyTcsMapPoint* end()const { return _end; }
		inline const SunnyTcsMapPoint* ctrl()const { return _ctrl; }
		inline bool isDirectLine()const { return !_ctrl; }
		inline qint32 getPositiveSpeed()const { return _positiveSpeed; }
		inline qint32 getNegativeSpeed()const { return _negativeSpeed; }

		//setter
		void setVirtualLinkFlag(qint32 flag) { _virtualLinkFlag = flag; }
		void setStart(const SunnyTcsMapPoint* pt) { _start = pt; }
		void setEnd(const SunnyTcsMapPoint* pt) { _end = pt; }
		void setCtrl(const SunnyTcsMapPoint* pt) { _ctrl = pt; }
		void setPositiveSpeed(qint32 posi) { _positiveSpeed = posi; }
		void setNegativeSpeed(qint32 nega) { _negativeSpeed = nega; }

		//换向
		void changDirection()
		{
			Q_ASSERT(_start && _end);
			const SunnyTcsMapPoint* temp = _start;
			_start = _end;
			_end = temp;
		}

		// 通过 A_SunnyTcsMapObject 继承
		virtual SunnyTcsMapObject_tag getTag() const override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool isInRange(SunnyTcsAgvCoordinate coor) const override;

		//json
		virtual QJsonObject toJson() const;
		virtual bool fromJson(QJsonObject& jobj, QString & reason);

	protected:
		const SunnyTcsMapPoint* _start;
		const SunnyTcsMapPoint* _end;
		const SunnyTcsMapPoint* _ctrl;


		qint32 _virtualLinkFlag; //虚拟链接标识，默认为0
	};



}



