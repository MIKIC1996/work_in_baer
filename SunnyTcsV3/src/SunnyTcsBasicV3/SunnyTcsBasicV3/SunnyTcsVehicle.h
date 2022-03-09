#pragma once
#include "SunnyTcsMapActualData.hpp"

#include "SunnyTcsPath.h"
#include "SunnyTcsCraft.h"


#define VEHICLE_NORMAL_TYPE_ID 10001 //��������
#define VEHICLE_MITSUBISHI_BATTERY_TYPE_ID 11001  //�������� ���
#define VEHICLE_DAIMLER_ENGINE_TYPE_ID 12001 //daimler ������



namespace basic {


	//normal���͵������Ϣ
	static SunnyTcsAgvCode vehicle_normal(VEHICLE_NORMAL_TYPE_ID, VEHICLE_NAGA_RUBBON, 3, ARG_INT32, E_ONE_DIMENSION ,QSTRING_GBK("��ͨ����"));
	static SunnyTcsAgvCode vehicle_mitsubishi(VEHICLE_MITSUBISHI_BATTERY_TYPE_ID, VEHICLE_NAGA_INERTIA | VEHICLE_NAGA_INERTIA, 7, ARG_INT32, E_TWO_DIMENSION,QSTRING_GBK("�������⳵��"));
	static SunnyTcsAgvCode vehicle_daimler_engine(VEHICLE_DAIMLER_ENGINE_TYPE_ID, VEHICLE_NAGA_RUBBON, 3, ARG_UINT32, E_ONE_DIMENSION, QSTRING_GBK("��ķ�շ���������"));


	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle : public I_SunnyTcsAgvStat
	{
	public:
		static bool initVehicleSupportedList() {
			_vehicleSupported.append(vehicle_normal);
			_vehicleSupported.append(vehicle_mitsubishi);
			_vehicleSupported.append(vehicle_daimler_engine);
			return true;
		}

		static QList<SunnyTcsAgvCode> _vehicleSupported;
		static bool isInited;
		

	public:
		SunnyTcsVehicle(SunnyTcsAgvCode code, qint32 id);
		SunnyTcsVehicle(const SunnyTcsVehicle&) = delete;
		virtual ~SunnyTcsVehicle() {}
		SunnyTcsVehicle& operator=(const SunnyTcsVehicle&) = delete;

		//getter
		qint32 getGroupId()const { return _groupId; }
		QString getIp()const { return _ip; }
		quint16 getPort()const { return _port; }
		quint64 getConnectId()const { return _connectId; }

		//setter
		void setGroupId(qint32 groupId) { _groupId = groupId; }
		void setIp(QString ip) {
			_ip = ip;
			_connectId = connectionID(_ip, _port);
		}
		void setPort(quint16 port) {
			_port = port; 
			_connectId = connectionID(_ip, _port);
		}

		// ͨ�� I_SunnyTcsAgvStat �̳�
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool updateData(const QByteArray& data) = 0;
		virtual bool updateData(QByteArray&& data) { return false; }//��ֵ�汾����Ҫ������һ��ʵ��

		//�����麯��
		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData* data) = 0;
		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData* data) = 0;//��route�Ķ����б���д���

	protected:
		qint32 _groupId; //Ĭ����0����ʾȫ��
		QString _ip;//IP
		quint16 _port;//�˿�
		quint64 _connectId;//����ID
	};



}
