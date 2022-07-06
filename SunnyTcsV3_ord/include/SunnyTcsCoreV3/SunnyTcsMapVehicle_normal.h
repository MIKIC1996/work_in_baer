#pragma once


#include "SunnyTcsMapVehicle.h"

#define MAP_VEHICLE_NORMAL_CODE_ID 1001
#define MAP_VEHICLE_NORMAL_CODE_NAGE ( MAP_VEHICLE_NAGAMODE_RUBBON | MAP_VEHICLE_NAGAMODE_INERTIA)
#define MAP_VEHICLE_NORMAL_CODE_PARAM_COUNT 7
#define MAP_VEHICLE_NORMAL_CODE_ARG_TYPE ARG_INT32

namespace core {

	//简单的车辆实现
	class SUNNYTCSCOREV3_EXPORT  SunnyTcsMapVehicle_normal : public A_SunnyTcsMapVehicle
	{
	public:
		static const SunnyTcsAgvCode _code;

		SunnyTcsMapVehicle_normal(const SunnyTcsMapCoorSys * cs, qint32 id = 0, 
			QString ip = "127.0.0.1", quint16 port = 5003, qint32 groupId =0);

		SunnyTcsMapVehicle_normal(const SunnyTcsMapVehicle_normal&) = delete;

		virtual ~SunnyTcsMapVehicle_normal() {}

		SunnyTcsMapVehicle_normal& operator=(const SunnyTcsMapVehicle_normal&) = delete;
		

		// 通过 A_SunnyTcsMapVehicle 继承
		virtual SunnyTcsAgvStat getAgvStat() const override;

		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData * data, QString & err) override;

		virtual bool updateCommand(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData * data, QString & err) override;

		virtual bool updateData(const QByteArray & data, QString & err) override;

		virtual void lock()override{
			_lock.lock();
		}

		virtual void unlock()override {
			_lock.unlock();
		}

		virtual bool trylock()override {
			return _lock.tryLock();
		}

	protected:
		QMutex _lock;

		//agv的 DB 数据
		QMap<qint16, qint16> _commandFeedbackMap_normal; //40 指令反馈暂存区
		qint16 _liftHeight_normal; //2  50
		qint16 _degree_0_1_normal; //2
		qint16 _degree_normal; //2
		qint16 _rfid_normal; //2
		quint32 _speed_normal; //4  60
		quint64 _error_normal; //8  
		quint64 _warning_normal; //8  76
		quint32 _status_normal;  //4  80
		qint16 _battery_normal;  //2  82


	

	};





}



