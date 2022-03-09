#pragma once



#include "SunnyTcsMapPath.h"
#include "SunnyTcsMapVehicle.h"
#include "I_SunnyTcsLogger.h"
#include "I_SunnyTcsMsgSender.h"
#include "I_SunnyTcsRunner.h"
#include "SunnyTcsOrderCenter.h"
#include "SunnyTcsLineVariable.h"

#define JSON_MODEL_PTS "modelPts"
#define JSON_MODEL_PATHS "modelPaths"


//地图的json格式
/*
地图ID

地图长度

地图宽度

地图分辨率

*/

using namespace basic;

namespace core {

	//这个类是模型的超类，是内核模型 ，客户端模型等 的超类。
	//关于模型的多线程问题，对车辆、线边 和 外部设备的数据更新（高频率），是多线程的（锁），对点、线的数据更新（低频率） 是单线程的（无需锁）。
	// 线 和 点的数据是单线程的，也就是只有model线程能访问，其他线程只能通过接口获得非实时性信息，以及提交非实时性修改申请，不能向外界直接提供
	class SUNNYTCSCOREV3_EXPORT A_SunnyTcsModelData 
	{
	public:
		A_SunnyTcsModelData(SunnyTcsMapCoorSys* cs = nullptr,
			qint32 id = 0,
			qint32 wid = 1000,
			qint32 hei = 1000,
			qint32 resolution = 1000
		)
			:  _cs(cs), _modelId(id), _hei(hei), _wid(wid), _resolution(resolution),
			_ves(), _pts(), _paths()
		{}

		A_SunnyTcsModelData(const A_SunnyTcsModelData&) = delete;

		virtual ~A_SunnyTcsModelData() {}

		A_SunnyTcsModelData& operator=(const A_SunnyTcsModelData&) = delete;

		// 虚函数
		virtual void init_distribution() {//初始化分布
			for (auto ptr : _pts) {
				QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
				for (auto bl : bs) {
					if (!_distribution.keys().contains(bl)) {
						_distribution.insert(bl, QList<A_SunnyTcsMapObject*>());
					}
					_distribution[bl].append(ptr);
				}
			}
			for (auto ptr : _paths) {
				QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
				for (auto bl : bs) {
					if (!_distribution.keys().contains(bl)) {
						_distribution.insert(bl, QList<A_SunnyTcsMapObject*>());
					}
					_distribution[bl].append(ptr);
				}
			}
		}

		virtual void update_distribution() {//更新车辆分布
			for (auto ptr : _ves) {
				ptr->lock();
				QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
				if (bs.isEmpty()) { //不是二维车辆
					//调用一维车辆的匹配方法
					ptr->unlock();
					qDebug() << "isempty";
					continue;
				}else {
					if (!_distribution.keys().contains(bs.first())) {//无 匹配区块
						ptr->setcurrentPos(SunnyTcsMapObject_tag());
						ptr->unlock();
						qDebug() << "no pipei";
						continue;
					}
					else { //存在匹配区块
						SunnyTcsMapBlock bl = bs.first();
						QList<A_SunnyTcsMapObject*>& eles = _distribution[bl];
						//匹配点
						bool finded = false;
						for (auto eptr : eles) {
							if (eptr->getTag()._eletype == Epoint && eptr->isInRange(ptr->getCurrentCoor())) {
								ptr->setcurrentPos(eptr->getTag());
								finded = true;
								break;
							}
						}
						//匹配线
						if (!finded) {
							for (auto eptr : eles) {
								if (eptr->getTag()._eletype == Epath && eptr->isInRange(ptr->getCurrentCoor())) {
									ptr->setcurrentPos(eptr->getTag());
									finded = true;
									break;
								}
							}
						}
						qDebug() << "no pipei2";
						//没有找到匹配的 点线
						if(!finded)ptr->setcurrentPos(SunnyTcsMapObject_tag());
						ptr->unlock();
					}
				}
			}
		}

		virtual bool fromJson(QJsonObject& jobj, QString& err) { return false; }//json
		virtual QJsonObject toJson()const { return QJsonObject(); }//json

		//getter
		inline qint32 getModelId()const { return _modelId; }
		inline qint32 getHeight()const { return _hei; }
		inline qint32 getWidth()const { return _wid; }
		inline qint32 getResolution()const { return _resolution; }

		//setter
		void setHeight(qint32 hei) { _hei = hei; }
		void setWidth(qint32 wid) { _wid = wid; }
		void setResolution(qint32 res) { _resolution = res; }
		
	protected:
		qint32 _modelId; //模型id,每个子类都有专属的id号，通常一个项目一个
		qint32 _wid;
		qint32 _hei;
		qint32 _resolution;

		//model member
		SunnyTcsMapCoorSys* _cs;
		QHash<qint32, A_SunnyTcsMapVehicle*> _ves;
		QHash<qint32, SunnyTcsMapPoint*> _pts;
		QHash<qint32, SunnyTcsMapPath*> _paths;
		QMap<SunnyTcsMapBlock, QList<A_SunnyTcsMapObject*>> _distribution;
	};



	//内核模型类，数据抽象模型 不需要编辑功能，但必须实现 实际数据接口
	class SUNNYTCSCOREV3_EXPORT SunnyTcsMapModel 
		:public A_SunnyTcsModelData,
		public I_SunnyTcsActualData,
		public I_SunnyTcsExecutor,
		public I_SunnyTcsCraftRecivier,
		public I_SunnyTcsMsgMember,
		public I_SunnyTcsLoggerUser
	{
	public:
		SunnyTcsMapModel(
			std::shared_ptr<I_SunnyTcsRunner> runner,
			std::shared_ptr<I_SunnyTcsCraftAgency> agency,
			std::shared_ptr<I_SunnyTcsMsgSender> sender,
			std::shared_ptr<I_SunnyTcsLogger> loger);

		SunnyTcsMapModel(const SunnyTcsMapModel&) = delete;

		virtual ~SunnyTcsMapModel();

		SunnyTcsMapModel& operator=(const SunnyTcsMapModel&) = delete;

		// 通过 I_SunnyTcsActualData 继承,采用默认实现,这是因为
		virtual bool judgeSingleCondition(const SunnyTcsSingleCondition & conditon) const override;

		virtual void agvStats(QMap<qint32, SunnyTcsAgvStat>& ref) const override;

		virtual void points(QMap<qint32, SunnyTcsVertex>& ref) const override;

		virtual void paths(QMap<qint32, SunnyTcsEdge>& ref) const override;




		// 通过 I_SunnyTcsActualData 继承
		virtual void uls(QString ulsCode, QMap<qint32, SunnyTcsUlsData>& ref) const override;

	};

}



