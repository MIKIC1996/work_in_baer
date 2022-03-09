#pragma once


#include "SunnyTcsDbProxyFactory.h"

//管理者接口
class I_SunnyTcsDbProxyManager {


};




// 
// //manager 负责管理所有数据库代理的 生命周期，负责线程分配。
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
// 	// 通过 I_SunnyTcsDbMediaPool 继承
// 	virtual I_SunnyTcsDbMedia_impl * getResource() override;
// 	virtual void recircleResource(I_SunnyTcsDbMedia_impl *) override;
// 
// protected:
// 	QList<SunnyTcsDbParams> _params;//参数集
// 	QHash<quint64, I_SunnyTcsDbProxy*> _dbProxys;//DB代理
// 	I_SunnyTcsDbProxyFactory* _factory;
// 
// 
// 
// };

