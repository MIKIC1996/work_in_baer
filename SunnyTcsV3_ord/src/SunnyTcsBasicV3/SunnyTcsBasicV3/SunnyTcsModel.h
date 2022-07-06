#pragma once

#include "SunnyTcsPoint.h"
#include "SunnyTcsLocation.h"
#include "SunnyTcsPath.h"
#include "SunnyTcsVehicle.h"

namespace basic {

	class SUNNYTCSBASICV3_EXPORT SunnyTcsModel : public I_SunnyTcsActualData
	{
	public:
		explicit SunnyTcsModel(quint64 id);
		virtual ~SunnyTcsModel() {}

		// 通过 I_SunnyTcsActualData 继承
		virtual bool judgeSingleCondition(const SunnyTcsSingleCondition & conditon) override;
		virtual void agvStats(QHash<qint32, I_SunnyTcsAgvStat*>& ref) override;
		virtual void points(QHash<qint32, I_SunnyTcsVertex*>& ref) override;
		virtual void paths(QHash<qint32, I_SunnyTcsEdge*>& ref) override;
		virtual void uls(QHash<qint32, I_SunnyTcsUlsData*>& ref) override;

		// 虚函数
		virtual void init_distribution();
		virtual void update_distribution();

		//getter
		inline quint64 getModelId()const { return _modelId; }
		inline qint32 getHeight()const { return _hei; }
		inline qint32 getWidth()const { return _wid; }
		inline qint32 getResolution()const { return _resolution; }

		//setter
		void setHeight(qint32 hei) { _hei = hei; }
		void setWidth(qint32 wid) { _wid = wid; }
		void setResolution(qint32 res) { _resolution = res; }

		virtual bool fromJson(QJsonObject& jobj) { return false; }
		virtual QJsonObject toJson()const { return QJsonObject(); }

	protected:
		quint64 _modelId; //模型id,每个子类都有专属的id号，通常一个项目一个
		qint32 _wid;  //宽
		qint32 _hei;  //高
		qint32 _resolution; //分辨率

		//model member
		SunnyTcsCoorSys* _cs;
		QHash<qint32, SunnyTcsVehicle*> _ves;
		QHash<qint32, SunnyTcsPoint*> _pts;
		QHash<qint32, SunnyTcsPath*> _paths;

		QMap<SunnyTcsMapBlock, QList<I_SunnyTcsElementData*>> _distribution; //区块二维分布

	};

}


