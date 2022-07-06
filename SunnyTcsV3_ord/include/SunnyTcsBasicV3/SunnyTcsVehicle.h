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

		// ͨ�� I_SunnyTcsAgvStat �̳�
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override;
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution) const override;
		virtual bool updateData(const QByteArray& data) = 0;
		virtual bool updateData(QByteArray&& data) { return false; }//��ֵ�汾����Ҫ������һ��ʵ��

		//�����麯��
		virtual bool CreateOrderAction(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData* data) = 0;
		virtual bool updateCommand(std::shared_ptr<SunnyTcsCraft> craft, I_SunnyTcsActualData* data) = 0;//��route�Ķ����б���д���

	protected:
		const SunnyTcsCoorSys* _cs;
		qint32 _groupId;
		QString _ip;//IP
		quint16 _port;//�˿�
		quint64 _connectId;//����ID
	};



}
