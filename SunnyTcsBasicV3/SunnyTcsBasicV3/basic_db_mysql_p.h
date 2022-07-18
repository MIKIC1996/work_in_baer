#pragma once

#include "basic_db_mysql.h"



class SunnyTcsMysqlProxyPrivate {
public:
	friend class SunnyTcsMysqlProxy;

	//ctor 
	SunnyTcsMysqlProxyPrivate()
		:m_ip(),m_port(0),m_userName(),m_password(),m_dbName(),m_mysqlServer(nullptr),m_mysqlRes(nullptr),m_curRow(nullptr)
	{
		init();
	}

	//copy ctor
	SunnyTcsMysqlProxyPrivate(SunnyTcsMysqlProxyPrivate const& var)
		:m_ip(var.m_ip),m_port(var.m_port),m_userName(var.m_userName),m_password(var.m_password),m_dbName(var.m_dbName),
		m_mysqlServer(nullptr), m_mysqlRes(nullptr), m_curRow(nullptr) 
	{
		init();
	}

	//detor
	virtual ~SunnyTcsMysqlProxyPrivate()
	{
		destory();
	}

	//assign
	SunnyTcsMysqlProxyPrivate& operator=(SunnyTcsMysqlProxyPrivate const&) = delete;


private:
	void init() {
		m_mysqlServer = new MYSQL();
		mysql_init(m_mysqlServer);
		char val = 1;
		mysql_options(m_mysqlServer, MYSQL_OPT_RECONNECT, &val); //设置自动重连
	}

	void destory() {
		delete m_mysqlServer;
		m_mysqlServer = nullptr;
	}

private:
	//attribution
	IpType m_ip;
	portType m_port;
	std::string m_userName;
	std::string m_password;
	std::string m_dbName;
	
	//mysql
	MYSQL* m_mysqlServer;
	MYSQL_RES* m_mysqlRes;
	MYSQL_ROW m_curRow;
};