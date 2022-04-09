#pragma once

#include "SunnyTcsVehicle.h"


namespace basic {



	//normal���͵������Ϣ
	static SunnyTcsAgvCode vehicle_normal(VEHICLE_NORMAL_TYPE_ID, VEHICLE_NAGA_RUBBON, 3, ARG_INT32, E_ONE_DIMENSION, QSTRING_GBK("��ͨ����"));
	static SunnyTcsAgvCode vehicle_mitsubishi(VEHICLE_MITSUBISHI_BATTERY_TYPE_ID, VEHICLE_NAGA_INERTIA | VEHICLE_NAGA_INERTIA, 7, ARG_INT32, E_TWO_DIMENSION, QSTRING_GBK("�������⳵��"));
	static SunnyTcsAgvCode vehicle_daimler_engine(VEHICLE_DAIMLER_ENGINE_TYPE_ID, VEHICLE_NAGA_RUBBON, 3, ARG_UINT32, E_ONE_DIMENSION, QSTRING_GBK("��ķ�շ���������"));



	//���͹����ӿ�
	class SUNNYTCSBASICV3_EXPORT I_SunnyTcsVehicleFactory{
	public:
		static QMap<qint32, SunnyTcsAgvCode> _vehicleSupported;
		static bool isInited;

		static bool initVehicleSupportedMap() {
			_vehicleSupported.insert(vehicle_normal._agvType, vehicle_normal);
			_vehicleSupported.insert(vehicle_mitsubishi._agvType, vehicle_mitsubishi);
			_vehicleSupported.insert(vehicle_daimler_engine._agvType, vehicle_daimler_engine);
			return true;
		}

		virtual SunnyTcsVehicle* createVehicleByCode(SunnyTcsAgvCode code) {
			return createVehicleByCodeId(code._agvType);
		}
		virtual SunnyTcsVehicle* createVehicleByCodeId(qint32 id)=0;
	};





	//��ʼ���ͣ������ָ���ͳ���
	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle_normal : public SunnyTcsVehicle
	{
	public:
		//ctor
		SunnyTcsVehicle_normal(qint32 id) : SunnyTcsVehicle(vehicle_normal, id) {}
		//copy ctor
		SunnyTcsVehicle_normal(const SunnyTcsVehicle_normal&) = delete;
		//detor
		virtual ~SunnyTcsVehicle_normal() {}
		//assignment
		SunnyTcsVehicle_normal& operator=(const SunnyTcsVehicle_normal&) = delete;



		// ͨ�� SunnyTcsVehicle �̳�
		virtual bool updateData(const QByteArray & data) override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

	};


	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle_mitsubishi_battery :public SunnyTcsVehicle 
	{
	public:
		//ctor
		SunnyTcsVehicle_mitsubishi_battery(qint32 id) : SunnyTcsVehicle(vehicle_mitsubishi, id) {}
		//copy ctor
		SunnyTcsVehicle_mitsubishi_battery(const SunnyTcsVehicle_mitsubishi_battery&) = delete;
		//detor
		virtual ~SunnyTcsVehicle_mitsubishi_battery() {}
		//assignment
		SunnyTcsVehicle_mitsubishi_battery& operator=(const SunnyTcsVehicle_mitsubishi_battery&) = delete;


		// ͨ�� SunnyTcsVehicle �̳�
		virtual bool updateData(const QByteArray & data) override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

	};




	class SUNNYTCSBASICV3_EXPORT SunnyTcsVehicle_daimer_engine :public SunnyTcsVehicle
	{
	public:
		//ctor
		SunnyTcsVehicle_daimer_engine(qint32 id) : SunnyTcsVehicle(vehicle_daimler_engine, id) {}
		//copy ctor
		SunnyTcsVehicle_daimer_engine(const SunnyTcsVehicle_daimer_engine&) = delete;
		//detor
		virtual ~SunnyTcsVehicle_daimer_engine() {}
		//assignment
		SunnyTcsVehicle_daimer_engine& operator=(const SunnyTcsVehicle_daimer_engine&) = delete;

		// ͨ�� SunnyTcsVehicle �̳�
		virtual bool updateData(const QByteArray & data) override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsOrder> craft, I_SunnyTcsActualData * data) override;
	};
	

	class SUNNYTCSBASICV3_EXPORT SunnyTcsBasicVehicleFactory : public I_SunnyTcsVehicleFactory {
	public:
		// ͨ�� I_SunnyTcsVehicleFactory �̳�
		virtual SunnyTcsVehicle* createVehicleByCodeId(qint32 id) override;

	};


}

