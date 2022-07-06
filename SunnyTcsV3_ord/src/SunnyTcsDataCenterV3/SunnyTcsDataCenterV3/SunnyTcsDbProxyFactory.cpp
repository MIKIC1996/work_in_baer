#include "SunnyTcsDbProxyFactory.h"






bool SunnyTcsDbParams::fromJson(QJsonObject & jobj, QString & err) throw(SunnyTcsException<ERROR_DB_JSON_ERROR_TYPE>())
{
	QString dbType = jobj[JSON_DB_TYPE].toString();
	_type = dbType == MySql_tag::value_str ? MySql_tag::value :
		dbType == Sqllite_tag::value_str ? Sqllite_tag::value :
		dbType == Redis_tag::value_str ? Redis_tag::value :
		dbType == Oracle_tag::value_str ? Oracle_tag::value : General_Tag::value;

	if (dbType == General_Tag::value) { //错误的数据库str
		throw SunnyTcsException<ERROR_DB_JSON_ERROR_TYPE>();
	}

	//其他配置项
	_ip = jobj[JSON_DB_IP].toString();
	_port = jobj[JSON_DB_PORT].toInt();
	_username = jobj[JSON_DB_USERNAME].toString();
	_psw = jobj[JSON_DB_PSW].toString();
	_dbName = jobj[JSON_DB_NAME].toString();
	return true;
}




QJsonObject SunnyTcsDbParams::toJson() const
{
	QJsonObject jobj;
	jobj[JSON_DB_TYPE] =
		_type == MySql_tag::value ? QString(MySql_tag::value_str) :
		_type == Sqllite_tag::value ? QString(Sqllite_tag::value_str) :
		_type == Redis_tag::value ? QString(Redis_tag::value_str) :
		_type == Oracle_tag::value ? QString(Oracle_tag::value_str) : QString(General_Tag::value_str);
	jobj[JSON_DB_TYPE] = _ip;
	jobj[JSON_DB_PORT] = _port;
	jobj[JSON_DB_USERNAME] = _username;
	jobj[JSON_DB_PSW] = _psw;
	jobj[JSON_DB_NAME] = _dbName;
	return jobj;
}



I_SunnyTcsDbProxy * SunnyTcsProxyFactory_general::createDbProxy(SunnyTcsDbParams params, SunnyTcsDbDriver* dr)
{
	switch (params._type) {
	case MySql_tag::value:
		return new SunnyTcsMysqlProxy(dr);//目前只支持mysql
	default:
		return nullptr;
	}
}
