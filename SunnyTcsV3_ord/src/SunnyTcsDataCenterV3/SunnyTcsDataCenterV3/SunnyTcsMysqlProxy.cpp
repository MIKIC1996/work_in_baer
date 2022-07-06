#include "SunnyTcsMysqlProxy.h"


//  QQueue<I_SunnyTcsDbMedia_impl*> SunnyTcsMediaFactory::_generalMedia;
//  qint32 SunnyTcsMediaFactory::_MediaCounter = 0;
//  QMutex SunnyTcsMediaFactory::_lock;


void SunnyTcsMysqlProxy::reciveDbCommand(I_SunnyTcsDbMedia_impl * command)
{
	_waitQueueLock.lock(); //���߳�ͬʱ�ύ����������
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


//�����߳��ύ����
bool SunnyTcsMysqlProxy::submitWork(int cirNum) //��ʼ�ύ��ʱ��Ĭ�ϵ��� һ�δ���һ����ѯ���󣬺����Ե��õ�ʱ��������������Զ�����
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
			_status = CONNECTED; //ֱ������������
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
		//ʲô���������ȴ����¼���
		break;
	default:
		break;
	}

// 	int next = _waitQueue.count() * 0.75; //��������µ��δ����ķ�֮���ı���
// 
// 	num = next <= 0 ? 1 :		//���ջ�ѹ��������� �Զ��������������д����ѯ����Ĵ��� �����1�������20��
// 		next >= 20 ? 20 : next;

//	this->submitWork(1);
	return true;
}

bool SunnyTcsMysqlProxy::connectToDb()
{
	//��ʼ��mysql
	if (!_mysqlServer) {
		_mysqlServer = new MYSQL();
		mysql_init(_mysqlServer);
		char val = 1;
		mysql_options(_mysqlServer, MYSQL_OPT_RECONNECT, &val); //�����Զ�����
	}
	//����mysql
	if (mysql_real_connect(_mysqlServer,
		_ip.toStdString().c_str(), _userName.toStdString().c_str(),
		_password.toStdString().c_str(), _dbName.toStdString().c_str(),
		_port, NULL, 0))
		//�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
	{
		return true;
	}
	//����������ֶ��ύ
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
	SqlString err{ 0, std::string(mysql_error(_mysqlServer)) };//��ȡ������Ϣ
	media_ptr->setError(ERROR_DB_QUERY_FAILED);
	media_ptr->clear(); // ɾ������ԭ����Ϣ
	media_ptr->append(err);//�����ݿ��ṩ�Ĵ�����Ϣ��ӵ�β��
}


//��������涨һ��ֻ����һ��media,�����ⲿ���õ��ô����������ӵ��δ������
void SunnyTcsMysqlProxy::queryDb()
{
	//û������
	if (_waitQueue.count() <= 0) {
		return;
	}
	auto media_ptr = _waitQueue.first();
	qint32 sqlCount = media_ptr->count();
	bool failed = false;

	QList<SqlString> indexs; //{ sql��ѯ���� �ֶ��� ������� �� �ֶ��� ������� }
	qint32 searchCount = 0;//��ѯ��
	bool isTransactionOpened = false;
	//��������
	if (media_ptr->count()>1 ){ /* һ�����ϵ�sql��俪������*/
		//��������ʧ��
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
		while (0 != mysql_query(_mysqlServer, (*media_ptr)[i]._sqlCommand.c_str())) { //��ѯʧ�ܣ����ط�0
			//�����ز����
			media_ptr->addTryCount();
			//�����������
			if (media_ptr->getTryCount()> DB_MAX_TRY_COUNT ) {
				queryError(media_ptr);
				if (isTransactionOpened) {
					std::cout << "rollBack" << std::endl;
					if (mysql_query(_mysqlServer, SunnyTcsQueryStrFactory<MYSQL_ROLLBACK>::produceQueryStr()._sqlCommand.c_str()))//�ع�
					{
						std::cout << "roll back failed" << std::endl;
					}
				}
				_waitQueue.pop_front();
				_finishQueue.push_back(media_ptr);
				return;
			}
		}
		//�׶β�ѯ�ɹ�
		if (method != MYSQL_SELECT) { //�� ɾ �� �����ȡ���
			continue;
		}
		++searchCount;
		_mysqlRes = mysql_store_result(_mysqlServer);
		quint32 fields = mysql_num_fields(_mysqlRes);
		indexs << SqlString{ 0,QString::number(fields).toStdString() };//�����ֶ���
		indexs << SqlString{ 0, QString::number(mysql_num_rows(_mysqlRes)).toStdString() };//��������

		//��ȡ���
		while (_curRow = mysql_fetch_row(_mysqlRes)) {
			for (int j = 0; j < fields; ++j) {
				media_ptr->append(SqlString{ 0,std::string(_curRow[j]) });
			}
		}
	}
	//�ύ
	std::cout << "commit" << std::endl;
	if (mysql_query(_mysqlServer, SunnyTcsQueryStrFactory<MYSQL_COMMIT>::produceQueryStr()._sqlCommand.c_str()))
	{
		std::cout << "commit failed" << std::endl;
	}

	indexs.push_front ( SqlString{ 0, QString::number(searchCount).toStdString() });//���sql��ѯ��
	(typename I_SunnyTcsDbMedia_impl::_Mybase&)(*media_ptr) = std::move( indexs + std::move(*media_ptr));
	media_ptr->setError(ERROR_NO_ERROR);
	_waitQueue.pop_front();
	_finishQueue.push_back(media_ptr);
}




