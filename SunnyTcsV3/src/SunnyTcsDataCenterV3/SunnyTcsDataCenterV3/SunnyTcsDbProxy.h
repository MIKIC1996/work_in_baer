#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"

//数据库代理 接口
class I_SunnyTcsDbProxy {
public:
	//连接状态
	enum E_ProxyStatus {
		UNCONNECTED = 1,
		CONNECTIING = 2,
		CONNECTED = 3,
		DISCONNECTING = 4, //发生断连
		DEACTIVING = 5,//人工请求挂起
		DEACTIVED = 6 //挂起状态
	};

	//getter
	E_ProxyStatus getCurrentStatus()const { return _status; }

	//重新激活
	virtual void active() {
		if (DEACTIVING == _status || DEACTIVED == _status) {
			_status = UNCONNECTED;
		}
	}

	//挂起
	virtual void deactive() {
		if (DEACTIVED != _status) {
			_status = DEACTIVING;
		}
	}

	virtual void reciveDbCommand(I_SunnyTcsDbMedia_impl* command) = 0;
	virtual I_SunnyTcsDbMedia_impl* getResultById(qint32 id) = 0;
	virtual I_SunnyTcsDbMedia_impl* popFirstResult() = 0;
	//开始工作
	virtual bool submitWork(int cirNum) = 0;

protected:
	quint64 _connId;//连接ID是唯一的，
	E_ProxyStatus _status = UNCONNECTED;
};