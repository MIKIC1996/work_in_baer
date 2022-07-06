#include <QtCore/QCoreApplication>
#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <QDebug>

#include <QTextCodec>
#include <QJsonObject>
#include <stdarg.h>

#include "stafix.h"


using namespace std;

#define C_STRING_CHARACTER_GBK

//中文支持c风格字符串
QTextCodec* pcode = QTextCodec::codecForName("GBK");
#define QSTRING_GBK(str) \
		pcode->toUnicode(str)
#define STD_STRING_GBK(str)\
		pcode->toUnicode(str).toStdString()


#ifdef C_STRING_CHARACTER_GBK
	#define QSTRING_DFT QSTRING_GBK
#else
	#define QSTRING_DFT QString
#endif // C_STRING_CHARACTER_GBK



#define JSON_DB_IP "dbIp"
#define JSON_DB_PORT "dbPort"
#define JSON_DB_USER "dbUser"
#define JSON_DB_PSW "dbPsw"
#define JSON_DB_NAME "dbName"


static MYSQL* pSqlObject =nullptr;


struct SunnyTcsMySqlConfig {
	SunnyTcsMySqlConfig() = default;
	SunnyTcsMySqlConfig(std::string ip, quint16 port, std::string user, std::string psw, std::string dbName) :
		_ip(ip), _port(port), _user(user), _psw(psw), _dbName(dbName) {}
	SunnyTcsMySqlConfig(const SunnyTcsMySqlConfig&) = default;
	virtual ~SunnyTcsMySqlConfig(){}
	SunnyTcsMySqlConfig& operator=(const SunnyTcsMySqlConfig&) = default;

	std::string _ip;
	quint16 _port;
	std::string _user;
	std::string _psw;
	std::string _dbName;

	QJsonObject tojson()const{
		QJsonObject jobj;
		jobj[JSON_DB_IP] = QString::fromStdString(_ip);
		jobj[JSON_DB_PORT] = _port;
		jobj[JSON_DB_USER] = QString::fromStdString(_user);
		jobj[JSON_DB_PSW] = QString::fromStdString(_psw);
		jobj[JSON_DB_NAME] = QString::fromStdString(_dbName);
		return jobj;
	}

	bool fromJson(QJsonObject& jobj, QString& err) {
		_ip = jobj[JSON_DB_IP].toString().toStdString();
		_port = jobj[JSON_DB_PORT].toInt();
		_user = jobj[JSON_DB_USER].toString().toStdString();
		_psw = jobj[JSON_DB_PSW].toString().toStdString();
		_dbName = jobj[JSON_DB_NAME].toString().toStdString();
		return true;
	}
};


static bool initDataBase_mysql(const SunnyTcsMySqlConfig& config ) {
	if (!pSqlObject) {
		pSqlObject = new MYSQL();
	}
	mysql_init(pSqlObject);
	
	return mysql_real_connect(pSqlObject, config._ip.c_str(), config._user.c_str(), config._psw.c_str(), config._dbName.c_str(), config._port, nullptr, 0) 
	? true : false;
};


//数据库指令接口
class I_SunnyTcsDbCommand {
public:
	I_SunnyTcsDbCommand() = default;
	I_SunnyTcsDbCommand(const I_SunnyTcsDbCommand&) = default;
	virtual ~I_SunnyTcsDbCommand() {}
	I_SunnyTcsDbCommand& operator=(const I_SunnyTcsDbCommand&) = default;

	virtual std::string toComandStr()const  = 0;


	
};


class SunnyTcsMysqlCommand : public I_SunnyTcsDbCommand
{
public:
	SunnyTcsMysqlCommand(MYSQL* pSql = pSqlObject) :I_SunnyTcsDbCommand(){}

	virtual std::string toComandStr() const override = 0;

	virtual MYSQL_RES* exeCommand(bool& ok) 
	{
		if (0 != mysql_query(_pSql, this->toComandStr().c_str())) {
			ok = false;
			return nullptr;
		}
		return mysql_store_result(_pSql);
	}

protected:
	MYSQL* _pSql;
	std::string _tarTable; //目标表
	std::string _tarColumn;//目标列
};


class SunnyTcsMysqlCommand_select :public SunnyTcsMysqlCommand 
{
public:
	SunnyTcsMysqlCommand_select():SunnyTcsMysqlCommand(){}

	QString _tarTable; //目标表
	bool isDistinct = false; //是否过滤重复数据
	QString _tarColunm;//目标列
};


template<int size>
void targetStr(char* (&buf)[size]) {
	
}


QString targetStr(int size,char* start, ...) {
	va_list ap;
	va_start(ap, start);
	QString str = QSTRING_DFT(start);
	for (int i = 0; i < size - 1; ++i) {
		char* sub = va_arg(ap, char*);
		str += ",";
		str += QSTRING_DFT(sub);
	}
	va_end(ap);
	return str;
}




char field[40][40];


bool queryDataBase1(){
	
	//mysql_query(&sql, "set names gbk");

	if (0 != mysql_query(&sql, "select * from table1")) {
		cout << "query failed" << endl;
		return false;
	}

	res = mysql_store_result(&sql);

	if (!res) {
		cout << "get res error" << endl;
		return false;
	}
	else {
		cout << "get res rows :" << mysql_affected_rows(&sql)<<endl;
	}

	//获取字段名
	int fieldCount = mysql_num_fields(res);
	for (int i = 0; i < fieldCount; ++i) {
		strcpy(field[i], mysql_fetch_field(res)->name);
	}
	
	
	//获取数据
	while (column = mysql_fetch_row(res)) {
// 		printf("|");
// 		for (int i = 0; i < fieldCount; ++i) {
// 			printf("%s : %s |",field[i],column[i]);
// 		}
// 		printf(" \n");
		
		QString data(column[1]);
		qDebug() << data;
	}


	return true;

}


bool insertData(qint32 id, QString data) {
	QString str = QString("insert into table1 values ( %1 , '%2' ); ").arg(QString::number(id)).arg(data);
	
	qDebug() << str;
	if (0 == mysql_query(&sql, str.toStdString().data())) {
		cout << "insert success"<<endl;
		return true;
	}
	else {
		cout << "insert failed"<<endl;
		return false;
	}
}


bool updateData(qint32 id, QString data) {

	QString str = QString("update table1 set value = '%1' where id = %2").arg(data).arg(QString::number(id));
	qDebug() << str;
	if (0 == mysql_query(&sql, str.toStdString().data())) {
		cout << "update success" << endl;
		return true;
	}
	else {
		cout << "update failed" << endl;
		return false;
	}
}


bool deleteData(qint32 id) {

	QString str = QString("delete from table1 where id = %2").arg(id);
	qDebug() << str;
	if (0 == mysql_query(&sql, str.toStdString().data())) {
		cout << "delete success" << endl;
		return true;
	}
	else {
		cout << "delete failed" << endl;
		return false;
	}
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	

	mysql_init(&sql);

	const char* host = "localhost";
	const char* user = "root";
	const char* psw = "hongqihz";
	const int port = 3306;
	const char* table = "test";

	if (!mysql_real_connect(&sql, host, user, psw, table, port, nullptr, 0)) {
		cout << "real connect error!" << endl;
	} else {
		cout << "connect success" << endl;
	}
	

	deleteData(9);

	qDebug() << targetStr(2, "a", "b");

	cout << _num << endl;

    return a.exec();
}
