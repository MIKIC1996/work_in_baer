#pragma once


#include "SunnyTcsDbProxyFactory.h"

//�����߽ӿ�
class I_SunnyTcsDbProxyManager {


};




// 
// //manager ��������������ݿ����� �������ڣ������̷߳��䡣
// class SunnyTcsDbProxyManager : public I_SunnyTcsDbMediaPool
// {
// public:
// 	SunnyTcsDbProxyManager() {
// 		_factory = new SunnyTcsProxyFactory_general();
// 	}
// 
// 	virtual ~SunnyTcsDbProxyManager() {
// 		if (_factory) {
// 			delete _factory;
// 		}
// 	}
// 
// 	
// 
// 	// ͨ�� I_SunnyTcsDbMediaPool �̳�
// 	virtual I_SunnyTcsDbMedia_impl * getResource() override;
// 	virtual void recircleResource(I_SunnyTcsDbMedia_impl *) override;
// 
// protected:
// 	QList<SunnyTcsDbParams> _params;//������
// 	QHash<quint64, I_SunnyTcsDbProxy*> _dbProxys;//DB����
// 	I_SunnyTcsDbProxyFactory* _factory;
// 
// 
// 
// };

