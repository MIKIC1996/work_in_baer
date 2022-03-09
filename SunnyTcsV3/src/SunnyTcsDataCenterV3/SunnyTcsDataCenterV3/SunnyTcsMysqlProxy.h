#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"
#include "SunnyTcsDbProxy.h"
#include "SunnyTcsDbDriver.h"



class SunnyTcsMysqlProxy :
	public I_SunnyTcsDbProxy 
{
public:
	typedef MySql_tag  db_tag;

	//ctor
	explicit SunnyTcsMysqlProxy(SunnyTcsDbDriver* driver)
		: _ip("localhost"), _port(3306), _userName(""),
		_password(""), _dbName(""), _driver(driver), 
		_mysqlServer(nullptr), _mysqlRes(nullptr), _curRow(),
		_circleCount(1), _waitQueueLock(),_waitQueue(),_finishQueue()
	{
		_connId = connectionID(_ip, _port);
	}
	SunnyTcsMysqlProxy(const SunnyTcsMysqlProxy&) = delete;
	SunnyTcsMysqlProxy& operator=(const SunnyTcsMysqlProxy&) = delete;
	//dtor
	virtual ~SunnyTcsMysqlProxy() {
		
	}

	//getter
	inline QString getIp()const { return _ip; }
	inline quint16 getPort()const { return _port; }
	inline QString getUserName()const { return _userName; }
	inline QString getPassword()const { return _password; }
	inline QString getDbName()const { return _dbName; }
	inline quint32 getCircleCount()const { return _circleCount; }
	inline quint64 getConnId()const { return _connId; }

	//setter
	void setIp(QString ip) { 
		_ip = ip; _connId = basic::connectionID(_ip, _port); 
	}
	void setPort(quint16 port) {
		_port = port; _connId = basic::connectionID(_ip, _port);
	}
	void setUserName(QString username) { _userName = username; }
	void setPassword(QString pw) { _password = pw; }
	void setDbName(QString db) { _dbName = db; }
	void setCircleCount(quint32 cir) { _circleCount = cir; }

	//继承 I_SunnyTcsDbProxy
	virtual void reciveDbCommand(I_SunnyTcsDbMedia_impl* command)override ;
	virtual I_SunnyTcsDbMedia_impl* getResultById(qint32 id) override ;
	virtual I_SunnyTcsDbMedia_impl* popFirstResult()override ;
	virtual bool submitWork(int cirNum =1) override;
	
protected:
	bool reallyWork(int num);
	bool connectToDb();
	bool linkCheck();//检查数据库连接
	void freeConnection(); 
	void queryError(I_SunnyTcsDbMedia_impl* media_ptr);
	void queryDb();

protected:
	
	//link info
	QString _ip;
	quint16 _port;
	QString _userName;
	QString _password;
	QString _dbName;

	//运行属性
	quint32 _circleCount;//获得driver执行权时的执行几条sql操作
	
	//工作线程
	SunnyTcsDbDriver* _driver; 

	//mysql
	MYSQL* _mysqlServer;
	MYSQL_RES* _mysqlRes;
	MYSQL_ROW _curRow;

	//等待队列
	QMutex _waitQueueLock;
	QQueue<I_SunnyTcsDbMedia_impl*> _waitQueue;
	QQueue<I_SunnyTcsDbMedia_impl*> _finishQueue;

};