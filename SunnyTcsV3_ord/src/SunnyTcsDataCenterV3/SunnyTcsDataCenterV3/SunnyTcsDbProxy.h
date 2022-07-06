#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"

//���ݿ���� �ӿ�
class I_SunnyTcsDbProxy {
public:
	//����״̬
	enum E_ProxyStatus {
		UNCONNECTED = 1,
		CONNECTIING = 2,
		CONNECTED = 3,
		DISCONNECTING = 4, //��������
		DEACTIVING = 5,//�˹��������
		DEACTIVED = 6 //����״̬
	};

	//getter
	E_ProxyStatus getCurrentStatus()const { return _status; }

	//���¼���
	virtual void active() {
		if (DEACTIVING == _status || DEACTIVED == _status) {
			_status = UNCONNECTED;
		}
	}

	//����
	virtual void deactive() {
		if (DEACTIVED != _status) {
			_status = DEACTIVING;
		}
	}

	virtual void reciveDbCommand(I_SunnyTcsDbMedia_impl* command) = 0;
	virtual I_SunnyTcsDbMedia_impl* getResultById(qint32 id) = 0;
	virtual I_SunnyTcsDbMedia_impl* popFirstResult() = 0;
	//��ʼ����
	virtual bool submitWork(int cirNum) = 0;

protected:
	quint64 _connId;//����ID��Ψһ�ģ�
	E_ProxyStatus _status = UNCONNECTED;
};