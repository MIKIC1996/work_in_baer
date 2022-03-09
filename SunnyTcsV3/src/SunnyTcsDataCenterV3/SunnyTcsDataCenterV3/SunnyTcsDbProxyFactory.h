#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"
#include "SunnyTcsDbProxy.h"
#include "SunnyTcsMysqlProxy.h"


static bool readDbConfig(QString path) {
	


}


// 数据库参数
struct SunnyTcsDbParams {

	quint8 _type; //初始化后无法再更改
	QString _ip;
	quint16 _port;
	QString _username;
	QString _psw;
	QString _dbName;

	//json
	bool fromJson(QJsonObject& jobj, QString& err = QString()) throw(SunnyTcsException<ERROR_DB_JSON_ERROR_TYPE>());
	QJsonObject toJson()const;
};


//proxy 抽象工厂接口
class SunnyTcsDbDriver;
class I_SunnyTcsDbProxyFactory {
public:
	virtual I_SunnyTcsDbProxy* createDbProxy(SunnyTcsDbParams params, SunnyTcsDbDriver* dr) = 0;
};



class SunnyTcsProxyFactory_general :public I_SunnyTcsDbProxyFactory {
public:

	// 通过 I_SunnyTcsDbProxyFactory 继承
	virtual I_SunnyTcsDbProxy * createDbProxy(SunnyTcsDbParams params, SunnyTcsDbDriver* dr) override;

};


