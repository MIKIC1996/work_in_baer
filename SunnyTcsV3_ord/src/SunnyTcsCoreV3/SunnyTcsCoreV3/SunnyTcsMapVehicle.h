#pragma once

#include "SunnyTcsCoreV3.h"
#include "SunnyTcsMapCoorSys.h"
#include "SunnyTcsMapPoint.h"

using namespace basic;

namespace core {


	//�����࣬1.�ܴ������и���״̬; 2.�ܸ��ݸ����������������ɷ����������͵� ָ���б�; 3�ܰ�������״̬����ָ��
	//�������࣬ÿ��������������ڣ� ���ĵ�����ʽ���ܲ�ͬ������DB����ܲ�ͬ��
	class SUNNYTCSCOREV3_EXPORT A_SunnyTcsMapVehicle :public A_SunnyTcsMapObject
	{
	public:
		A_SunnyTcsMapVehicle(const SunnyTcsMapCoorSys* cs, SunnyTcsAgvCode code,
			qint32 id = 0, QString ip = "127.0.0.1", quint16 port = 5003, qint32 groupId = 0
		);

		A_SunnyTcsMapVehicle(const A_SunnyTcsMapVehicle&) = delete;

		virtual ~A_SunnyTcsMapVehicle();
		
		A_SunnyTcsMapVehicle& operator=(const A_SunnyTcsMapVehicle& rhs) = delete;
		
		inline QString getIp()const { return _ip; }
		inline quint16 getPort()const { return _port; }
		inline quint64 getConnectId()const { return _connectId; }
		inline SunnyTcsAgvCode getAgvCode()const { return _code; }
		
		void setIp(QString ip) {
			_ip = ip;
			_connectId = connectionID(_ip, _port);
		}

		void setPort(quint16 port) {
			_port = port;
			_connectId = connectionID(_ip, _port);
		}

		bool isOrderBinded() {
			return _orderId_binded != 0;
		}

		//�������󶨵���agv
		bool bindOrder(quint64 orderId) {
			if (_orderId_binded != 0) {
				return false;
			}
			else {
				_orderId_binded = orderId;
				return true;
			}
		}

		void unbindOrder() {
			_orderId_binded = 0;
		}

		// ͨ�� A_SunnyTcsMapObject �̳�
		virtual SunnyTcsMapObject_tag getTag() const override;

		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override{//getblock ��ר�����ڼ����ά����ĺ�����һά����û���ã���������������
			SunnyTcsAgvCoordinate&& coor = this->getCurrentCoor();
			QVector<SunnyTcsMapBlock> bs;
			if (coor._dim == E_TWO_DIMENSION) {
				SunnyTcsMapBlock bl(coor._x / resolution +1, coor._y / resolution+ 1);
				bs << bl;
			}
			return bs;
		}
		
		// ���������麯������
		//�ṩ״̬��
		virtual SunnyTcsAgvStat getAgvStat()const = 0;

		//��������ָ��
		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsCraft> craft,I_SunnyTcsActualData* data, QString& err) = 0;
		virtual bool updateCommand(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData* data, QString& err) = 0;//��route�Ķ����б���д���

		//���ֽ��н��������ݵĲ���
		virtual bool updateData(const QByteArray& data, QString& err) = 0;
		virtual bool updateData(QByteArray&& data, QString& err) { return false; }//��ֵ�汾����Ҫ������һ��ʵ��

		//��ȡ��ǰ������  �� λ�� 
		virtual SunnyTcsAgvCoordinate getCurrentCoor()const { return _coor; }
		virtual SunnyTcsMapObject_tag getCurrentPos()const { return _curPos; }

		virtual void setCurrentCoor(SunnyTcsAgvCoordinate coor) {
			_coor = coor;
		}

		virtual void setcurrentPos(SunnyTcsMapObject_tag pos) {
			_curPos = pos;
		}

		//�����ǿ��Զ��̷߳��ʵģ����Ա����������ߺ͵� ����model ��ȫ���Ƶ�,����ֻ�ṩ�ӿڣ�����������ȥʵ��
		virtual void lock() {}
		virtual void unlock() {}
		virtual bool trylock() { return false; }

		//json
		virtual QJsonObject toJson() const { return QJsonObject(); }
		virtual bool fromJson(QJsonObject& jobj, QString & reason) { return false; }

	protected:
		const SunnyTcsAgvCode _code;
		const SunnyTcsMapCoorSys* _cs;		//����ϵָ��

		qint32 _groupId;
		QString _ip;//IP
		quint16 _port;//�˿�
		quint64 _connectId;//����ID
		E_SunnyTcsVehicleStatus _status;	//����״̬

		SunnyTcsAgvCoordinate _coor;		//��ǰ����
		SunnyTcsMapObject_tag _curPos;		//��ǰλ��

		quint64 _orderId_binded;			//�󶨵� ����ID,û��Ϊ0
	};




}


