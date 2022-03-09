#pragma once
#include "SunnyTcsMapActualData.hpp"

#include "SunnyTcsPath.h"
#include "SunnyTcsCraft.h"

namespace basic {


	class SunnyTcsVehicle : public I_SunnyTcsAgvStat
	{
	public:
		SunnyTcsVehicle(SunnyTcsAgvCode code, qint32 id, SunnyTcsCoorSys* cs);
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
		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData* data) = 0;
		virtual bool updateCommand(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData* data) = 0;//对route的订单列表进行处理

	protected:
		const SunnyTcsCoorSys* _cs;
		qint32 _groupId;
		QString _ip;//IP
		quint16 _port;//端口
		quint64 _connectId;//连接ID
	};



}
