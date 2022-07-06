#include "SunnyTcsMysqlProxy.h"


//  QQueue<I_SunnyTcsDbMedia_impl*> SunnyTcsMediaFactory::_generalMedia;
//  qint32 SunnyTcsMediaFactory::_MediaCounter = 0;
//  QMutex SunnyTcsMediaFactory::_lock;


void SunnyTcsMysqlProxy::reciveDbCommand(I_SunnyTcsDbMedia_impl * command)
{
	_waitQueueLock.lock(); //多线程同时提交可能有问题
	_waitQueue.push_back(command);
	_waitQueueLock.unlock();
}


I_SunnyTcsDbMedia_impl * SunnyTcsMysqlProxy::getResultById(qint32 id)
{
	return nullptr;
}


I_SunnyTcsDbMedia_impl * SunnyTcsMysqlProxy::popFirstResult()
{
	I_SunnyTcsDbMedia_impl* ret = _finishQueue.count() > 0 ? _finishQueue.first() : nullptr;
	ret ? _finishQueue.pop_front() : 0 ;
	return ret;
}


//向工作线程提交任务
bool SunnyTcsMysqlProxy::submitWork(int cirNum) //初始提交的时候默认的是 一次处理一条查询请求，后续自调用的时候根据请求数量自动决定
{
	_driver->submitToDriver(&SunnyTcsMysqlProxy::reallyWork ,this, cirNum);
	return true;
}


bool SunnyTcsMysqlProxy::reallyWork(int num)
{

	switch (_status)
	{
	case I_SunnyTcsDbProxy::UNCONNECTED:
		if(connectToDb())
		{
			std::cout << "link success" << std::endl;
			_status = CONNECTED; //直接跳到已连接
		}
		break;
	case I_SunnyTcsDbProxy::CONNECTIING:
		break;
	case I_SunnyTcsDbProxy::CONNECTED:
		if (!linkCheck()) {
			_status = DISCONNECTING;
			break;
		}
		for (int i = 0; i < num; ++i) {
			queryDb();
		}
		break;
	case I_SunnyTcsDbProxy::DISCONNECTING:
		std::cout << "freeConnection" << std::endl;
		freeConnection();
		_status = UNCONNECTED;
		break;
	case I_SunnyTcsDbProxy::DEACTIVING:
		std::cout << "deactiving" << std::endl;
		freeConnection();
		_status = DEACTIVED;
		break;
	case I_SunnyTcsDbProxy::DEACTIVED:
		//什么都不做，等待重新激活
		break;
	default:
		break;
	}

// 	int next = _waitQueue.count() * 0.75; //正常情况下单次处理四分之三的报文
// 
// 	num = next <= 0 ? 1 :		//按照积压任务的数量 自动调整单次运行中处理查询请求的次数 ，最低1条，最高20条
// 		next >= 20 ? 20 : next;

//	this->submitWork(1);
	return true;
}

bool SunnyTcsMysqlProxy::connectToDb()
{
	//初始化mysql
	if (!_mysqlServer) {
		_mysqlServer = new MYSQL();
		mysql_init(_mysqlServer);
		char val = 1;
		mysql_options(_mysqlServer, MYSQL_OPT_RECONNECT, &val); //设置自动重连
	}
	//连接mysql
	if (mysql_real_connect(_mysqlServer,
		_ip.toStdString().c_str(), _userName.toStdString().c_str(),
		_password.toStdString().c_str(), _dbName.toStdString().c_str(),
		_port, NULL, 0))
		//中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去  
	{
		return true;
	}
	//设置事务的手动提交
	mysql_autocommit(_mysqlServer, false);
	return false;
}

bool SunnyTcsMysqlProxy::linkCheck()
{
	return !_mysqlServer ? false : (0 == mysql_ping(_mysqlServer) ? true : false);
}


void SunnyTcsMysqlProxy::freeConnection()
{
	if (_mysqlRes) {
		mysql_free_result(_mysqlRes);
	}
	if (_mysqlServer) {
		mysql_close(_mysqlServer);
		delete _mysqlServer;
		_mysqlServer = nullptr;
	}
}


void SunnyTcsMysqlProxy::queryError(I_SunnyTcsDbMedia_impl*  media_ptr)
{
	SqlString err{ 0, std::string(mysql_error(_mysqlServer)) };//获取错误信息
	media_ptr->setError(ERROR_DB_QUERY_FAILED);
	media_ptr->clear(); // 删除所有原有信息
	media_ptr->append(err);//将数据库提供的错误信息添加到尾部
}


//这个函数规定一次只处理一个media,可以外部设置调用次数，来增加单次处理次数
void SunnyTcsMysqlProxy::queryDb()
{
	//没有任务
	if (_waitQueue.count() <= 0) {
		return;
	}
	auto media_ptr = _waitQueue.first();
	qint32 sqlCount = media_ptr->count();
	bool failed = false;

	QList<SqlString> indexs; //{ sql查询数， 字段数 ，结果数 ， 字段数 ，结果数 }
	qint32 searchCount = 0;//查询数
	bool isTransactionOpened = false;
	//开启事务
	if (media_ptr->count()>1 ){ /* 一条以上的sql语句开启事务*/
		//开启事务失败
		if (0 != mysql_query(_mysqlServer, SunnyTcsQueryStrFactory<MYSQL_START_TRANSACTION>::produceQueryStr()._sqlCommand.c_str()) ){
			queryError(media_ptr);
			_waitQueue.pop_front();
			_finishQueue.push_back(media_ptr);
			return;
		}
		isTransactionOpened = true;
	}

	for (int i = 0; i < sqlCount; ++i) {
		qint8 method = (*media_ptr)[i]._sqlMethod;
		while (0 != mysql_query(_mysqlServer, (*media_ptr)[i]._sqlCommand.c_str())) { //查询失败，返回非0
			//增加重查次数
			media_ptr->addTryCount();
			//超过允许次数
			if (media_ptr->getTryCount()> DB_MAX_TRY_COUNT ) {
				queryError(media_ptr);
				if (isTransactionOpened) {
					std::cout << "rollBack" << std::endl;
					if (mysql_query(_mysqlServer, SunnyTcsQueryStrFactory<MYSQL_ROLLBACK>::produceQueryStr()._sqlCommand.c_str()))//回滚
					{
						std::cout << "roll back failed" << std::endl;
					}
				}
				_waitQueue.pop_front();
				_finishQueue.push_back(media_ptr);
				return;
			}
		}
		//阶段查询成功
		if (method != MYSQL_SELECT) { //增 删 改 无需存取结果
			continue;
		}
		++searchCount;
		_mysqlRes = mysql_store_result(_mysqlServer);
		quint32 fields = mysql_num_fields(_mysqlRes);
		indexs << SqlString{ 0,QString::number(fields).toStdString() };//保存字段数
		indexs << SqlString{ 0, QString::number(mysql_num_rows(_mysqlRes)).toStdString() };//保存结果数

		//存取结果
		while (_curRow = mysql_fetch_row(_mysqlRes)) {
			for (int j = 0; j < fields; ++j) {
				media_ptr->append(SqlString{ 0,std::string(_curRow[j]) });
			}
		}
	}
	//提交
	std::cout << "commit" << std::endl;
	if (mysql_query(_mysqlServer, SunnyTcsQueryStrFactory<MYSQL_COMMIT>::produceQueryStr()._sqlCommand.c_str()))
	{
		std::cout << "commit failed" << std::endl;
	}

	indexs.push_front ( SqlString{ 0, QString::number(searchCount).toStdString() });//添加sql查询数
	(typename I_SunnyTcsDbMedia_impl::_Mybase&)(*media_ptr) = std::move( indexs + std::move(*media_ptr));
	media_ptr->setError(ERROR_NO_ERROR);
	_waitQueue.pop_front();
	_finishQueue.push_back(media_ptr);
}




