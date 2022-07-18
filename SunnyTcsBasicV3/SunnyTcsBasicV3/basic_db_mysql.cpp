
#include "pch.h"
#include "basic_db_mysql_p.h"







SunnyTcsMysqlProxy::SunnyTcsMysqlProxy()
	:d_ptr(nullptr)
{
	d_ptr = std::make_unique<SunnyTcsMysqlProxyPrivate>();
}

SunnyTcsMysqlProxy::SunnyTcsMysqlProxy(SunnyTcsMysqlProxy const& var)
	:d_ptr(nullptr)
{
	d_ptr = std::make_unique<SunnyTcsMysqlProxyPrivate>(*var.d_ptr);
}

SunnyTcsMysqlProxy::~SunnyTcsMysqlProxy()
{
	freeConnect();
}

IpType SunnyTcsMysqlProxy::getIp()const { return d_ptr->m_ip; }
portType SunnyTcsMysqlProxy::getPort()const { return d_ptr->m_port; }
std::string SunnyTcsMysqlProxy::getUserName()const { return d_ptr->m_userName; }
std::string SunnyTcsMysqlProxy::getPassword()const { return d_ptr->m_password; }
std::string SunnyTcsMysqlProxy::getDbName()const { return d_ptr->m_dbName; }
void SunnyTcsMysqlProxy::setIp(IpType const& var) { d_ptr->m_ip = var; }
void SunnyTcsMysqlProxy::setPort(portType const& var) { d_ptr->m_port = var; }
void SunnyTcsMysqlProxy::setUserName(std::string const& var) { d_ptr->m_userName = var; }
void SunnyTcsMysqlProxy::setPassword(std::string const& var) { d_ptr->m_password = var; }
void SunnyTcsMysqlProxy::setDbName(std::string const& var) { d_ptr->m_dbName = var; }



bool SunnyTcsMysqlProxy::connect() {
	//中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去 
	bool ret = mysql_real_connect(d_ptr->m_mysqlServer, d_ptr->m_ip.c_str(), d_ptr->m_userName.c_str(),
		d_ptr->m_password.c_str(), d_ptr->m_dbName.c_str(), d_ptr->m_port, NULL, 0);
	mysql_autocommit(d_ptr->m_mysqlServer, false);
	return ret;
}



bool SunnyTcsMysqlProxy::linkCheck()
{
	return 0 == mysql_ping( d_ptr->m_mysqlServer ) ? true : false;
}


bool SunnyTcsMysqlProxy::startTransaction(std::string* err )
{
	if (0 != mysql_query(d_ptr->m_mysqlServer, "start transaction;")) {
		if (err) *err = mysql_error(d_ptr->m_mysqlServer);
		return false;
	}
	return true;
}


bool SunnyTcsMysqlProxy::commit(std::string* err )
{
	if (0 != mysql_query(d_ptr->m_mysqlServer, "commit;")) {
		if (err) *err = mysql_error(d_ptr->m_mysqlServer);
		return false;
	}
	return true;
}


bool SunnyTcsMysqlProxy::rollback(std::string* err )
{
	if (0 != mysql_query(d_ptr->m_mysqlServer, "rollback;")) {
		if (err) *err = mysql_error(d_ptr->m_mysqlServer);
		return false;
	}
	return true;
}


bool SunnyTcsMysqlProxy::query(std::string sqlStr, bool commmit , std::string* err, int32_t* fieldNum, std::vector<std::string>* ret)
{
	if ( !linkCheck() || 0 != mysql_query(d_ptr->m_mysqlServer, sqlStr.c_str())) {
		if (err) *err = mysql_error(d_ptr->m_mysqlServer);
		return false;
	}

	//提交
	if (commmit && !this->commit(err)) return false;

	//存储结果
	int32_t fields = 0;
	if (!ret || !fieldNum || !(d_ptr->m_mysqlRes = mysql_store_result(d_ptr->m_mysqlServer)) || (0>=(fields = mysql_num_fields(d_ptr->m_mysqlRes))) )return true;

	*fieldNum = fields;
	while (d_ptr->m_curRow = mysql_fetch_row(d_ptr->m_mysqlRes)) {
		for (int j = 0; j < fields; ++j) {
			char* data = d_ptr->m_curRow[j];
			//std::cout << data << std::endl;
			ret->push_back( data ? data : std::string());
		}
	}
	mysql_free_result(d_ptr->m_mysqlRes);
	d_ptr->m_mysqlRes = nullptr;
	return true;
}


void SunnyTcsMysqlProxy::freeConnect()
{
	mysql_close(d_ptr-> m_mysqlServer);
}







