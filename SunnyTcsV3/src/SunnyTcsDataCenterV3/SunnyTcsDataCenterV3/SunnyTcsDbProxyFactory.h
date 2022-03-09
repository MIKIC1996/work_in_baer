#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"
#include "SunnyTcsDbProxy.h"
#include "SunnyTcsMysqlProxy.h"


static bool readDbConfig(QString path) {
	


}


// ���ݿ����
struct SunnyTcsDbParams {

	quint8 _type; //��ʼ�����޷��ٸ���
	QString _ip;
	quint16 _port;
	QString _username;
	QString _psw;
	QString _dbName;

	//json
	bool fromJson(QJsonObject& jobj, QString& err = QString()) throw(SunnyTcsException<ERROR_DB_JSON_ERROR_TYPE>());
	QJsonObject toJson()const;
};


//proxy ���󹤳��ӿ�
class SunnyTcsDbDriver;
class I_SunnyTcsDbProxyFactory {
public:
	virtual I_SunnyTcsDbProxy* createDbProxy(SunnyTcsDbParams params, SunnyTcsDbDriver* dr) = 0;
};



class SunnyTcsProxyFactory_general :public I_SunnyTcsDbProxyFactory {
public:

	// ͨ�� I_SunnyTcsDbProxyFactory �̳�
	virtual I_SunnyTcsDbProxy * createDbProxy(SunnyTcsDbParams params, SunnyTcsDbDriver* dr) override;

};


