#pragma once
#include "SunnyTcsMapActualData.hpp"

#include "SunnyTcsPath.h"
#include "SunnyTcsCraft.h"


#define VEHICLE_NORMAL_TYPE_ID 10001 //基本车型
#define VEHICLE_MITSUBISHI_BATTERY_TYPE_ID 11001  //广汽三菱 电池
#define VEHICLE_DAIMLER_ENGINE_TYPE_ID 12001 //daimler 发动机



namespace basic {


	//normal车型的相关信息
	static SunnyTcsAgvCode vehicle_normal(VEHICLE_NORMAL_TYPE_ID, VEHICLE_NAGA_RUBBON, 3, ARG_INT32, E_ONE_DIMENSION ,QSTRING_GBK("普通车辆"));
	static SunnyTcsAgvCode vehicle_mitsubishi(VEHICLE_MITSUBISHI_BATTERY_TYPE_ID, VEHICLE_NAGA_INERTIA | VEHICLE_NAGA_INERTIA, 7, ARG_INT32, E_TWO_DIMENSION,QSTRING_GBK("广汽三菱车辆"));
	static SunnyTcsAgvCode vehicle_daimler_engine(VEHICLE_DAIMLER_ENGINE_TYPE_ID, VEHICLE_NAGA_RUBBON, 3, ARG_UINT32, E_ONE_DIMENSION, QSTRING_GBK("戴姆勒发动机车辆"));


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

		// 通过 I_SunnyTcsAgvStat 继承
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool updateData(const QByteArray& data) = 0;
		virtual bool updateData(QByteArray&& data) { return false; }//右值版本，不要求子类一定实现

		//自身虚函数
		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData* data) = 0;
		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData* data) = 0;//对route的订单列表进行处理

	protected:
		qint32 _groupId; //默认组0，表示全部
		QString _ip;//IP
		quint16 _port;//端口
		quint64 _connectId;//连接ID
	};



}
