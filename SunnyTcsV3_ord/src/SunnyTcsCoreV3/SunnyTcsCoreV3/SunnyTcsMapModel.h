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


//��ͼ��json��ʽ
/*
��ͼID

��ͼ����

��ͼ���

��ͼ�ֱ���

*/

using namespace basic;

namespace core {

	//�������ģ�͵ĳ��࣬���ں�ģ�� ���ͻ���ģ�͵� �ĳ��ࡣ
	//����ģ�͵Ķ��߳����⣬�Գ������߱� �� �ⲿ�豸�����ݸ��£���Ƶ�ʣ����Ƕ��̵߳ģ��������Ե㡢�ߵ����ݸ��£���Ƶ�ʣ� �ǵ��̵߳ģ�����������
	// �� �� ��������ǵ��̵߳ģ�Ҳ����ֻ��model�߳��ܷ��ʣ������߳�ֻ��ͨ���ӿڻ�÷�ʵʱ����Ϣ���Լ��ύ��ʵʱ���޸����룬���������ֱ���ṩ
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

		// �麯��
		virtual void init_distribution() {//��ʼ���ֲ�
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

		virtual void update_distribution() {//���³����ֲ�
			for (auto ptr : _ves) {
				ptr->lock();
				QVector<SunnyTcsMapBlock>&& bs = ptr->getBlocks(_resolution);
				if (bs.isEmpty()) { //���Ƕ�ά����
					//����һά������ƥ�䷽��
					ptr->unlock();
					qDebug() << "isempty";
					continue;
				}else {
					if (!_distribution.keys().contains(bs.first())) {//�� ƥ������
						ptr->setcurrentPos(SunnyTcsMapObject_tag());
						ptr->unlock();
						qDebug() << "no pipei";
						continue;
					}
					else { //����ƥ������
						SunnyTcsMapBlock bl = bs.first();
						QList<A_SunnyTcsMapObject*>& eles = _distribution[bl];
						//ƥ���
						bool finded = false;
						for (auto eptr : eles) {
							if (eptr->getTag()._eletype == Epoint && eptr->isInRange(ptr->getCurrentCoor())) {
								ptr->setcurrentPos(eptr->getTag());
								finded = true;
								break;
							}
						}
						//ƥ����
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
						//û���ҵ�ƥ��� ����
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
		qint32 _modelId; //ģ��id,ÿ�����඼��ר����id�ţ�ͨ��һ����Ŀһ��
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



	//�ں�ģ���࣬���ݳ���ģ�� ����Ҫ�༭���ܣ�������ʵ�� ʵ�����ݽӿ�
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

		// ͨ�� I_SunnyTcsActualData �̳�,����Ĭ��ʵ��,������Ϊ
		virtual bool judgeSingleCondition(const SunnyTcsSingleCondition & conditon) const override;

		virtual void agvStats(QMap<qint32, SunnyTcsAgvStat>& ref) const override;

		virtual void points(QMap<qint32, SunnyTcsVertex>& ref) const override;

		virtual void paths(QMap<qint32, SunnyTcsEdge>& ref) const override;




		// ͨ�� I_SunnyTcsActualData �̳�
		virtual void uls(QString ulsCode, QMap<qint32, SunnyTcsUlsData>& ref) const override;

	};

}



