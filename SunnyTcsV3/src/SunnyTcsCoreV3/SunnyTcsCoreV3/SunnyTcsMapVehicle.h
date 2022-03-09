#pragma once

#include "SunnyTcsCoreV3.h"
#include "SunnyTcsMapCoorSys.h"
#include "SunnyTcsMapPoint.h"

using namespace basic;

namespace core {


	//车辆类，1.能从数据中更新状态; 2.能根据给定的生产任务，生成符合自身类型的 指令列表; 3能按照自身状态更新指令
	//车辆子类，每个子类的区别在于， 车的导航方式可能不同，车的DB块可能不同，
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

		//将订单绑定到该agv
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

		// 通过 A_SunnyTcsMapObject 继承
		virtual SunnyTcsMapObject_tag getTag() const override;

		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override{//getblock 是专门用于计算二维区域的函数，一维车辆没有用，反馈空容器即可
			SunnyTcsAgvCoordinate&& coor = this->getCurrentCoor();
			QVector<SunnyTcsMapBlock> bs;
			if (coor._dim == E_TWO_DIMENSION) {
				SunnyTcsMapBlock bl(coor._x / resolution +1, coor._y / resolution+ 1);
				bs << bl;
			}
			return bs;
		}
		
		// ——自身虚函数——
		//提供状态表
		virtual SunnyTcsAgvStat getAgvStat()const = 0;

		//创建更新指令
		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsCraft> craft,I_SunnyTcsActualData* data, QString& err) = 0;
		virtual bool updateCommand(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData* data, QString& err) = 0;//对route的订单列表进行处理

		//从字节中解析出数据的部分
		virtual bool updateData(const QByteArray& data, QString& err) = 0;
		virtual bool updateData(QByteArray&& data, QString& err) { return false; }//右值版本，不要求子类一定实现

		//获取当前的坐标  和 位置 
		virtual SunnyTcsAgvCoordinate getCurrentCoor()const { return _coor; }
		virtual SunnyTcsMapObject_tag getCurrentPos()const { return _curPos; }

		virtual void setCurrentCoor(SunnyTcsAgvCoordinate coor) {
			_coor = coor;
		}

		virtual void setcurrentPos(SunnyTcsMapObject_tag pos) {
			_curPos = pos;
		}

		//车辆是可以多线程访问的，所以必须上锁，线和点 是由model 完全管制的,这里只提供接口，具体由子类去实现
		virtual void lock() {}
		virtual void unlock() {}
		virtual bool trylock() { return false; }

		//json
		virtual QJsonObject toJson() const { return QJsonObject(); }
		virtual bool fromJson(QJsonObject& jobj, QString & reason) { return false; }

	protected:
		const SunnyTcsAgvCode _code;
		const SunnyTcsMapCoorSys* _cs;		//坐标系指针

		qint32 _groupId;
		QString _ip;//IP
		quint16 _port;//端口
		quint64 _connectId;//连接ID
		E_SunnyTcsVehicleStatus _status;	//车辆状态

		SunnyTcsAgvCoordinate _coor;		//当前坐标
		SunnyTcsMapObject_tag _curPos;		//当前位置

		quint64 _orderId_binded;			//绑定的 订单ID,没有为0
	};




}


