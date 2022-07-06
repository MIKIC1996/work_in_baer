#include <QtCore/QCoreApplication>

#include "SunnyTcsDataCenterGeneral.hpp"
#include "SunnyTcsMysqlProxy.h"

class AA {

public:
	int add(int a, int b) {
		return a + b + c;
	}

	int c = 100;

};



bool funkSb(int a) {
	
	
	return false;
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);


	

	

// 	const char* host = "localhost";
// 	const char* user = "root";
// 	const char* psw = "hongqihz";
// 	const int port = 3306;
// 	const char* table = "test";
// 
// 	SunnyTcsDbDriver dr;
// 	SunnyTcsMysqlProxy proxy(&dr);
// 	proxy.setIp(host);
// 	proxy.setPort(3306);
// 	proxy.setUserName(user);
// 	proxy.setPassword(psw);
// 	proxy.setDbName(table);
// 
// 
// 	SunnyTcsErrorInfo<11>::err_info;
// 
// 	proxy.submitWork();
// 	dr.start();

// 	bool thRun = true;
// 	std::thread th([&proxy,&thRun]()->void {
// 		while (thRun) {
// 			I_SunnyTcsDbMedia_impl* ret = proxy.popFirstResult();
// 			if (ret) {
// 				ret->print();
// 				delete ret;
// 			}
// 		}
// 	});


// 	char c = 0;
// 	while ('q' != (c = getchar())) {
// 		if ('s' == c) {
// 			proxy.deactive();
// 		}
// 		else if ('a' == c) {
// 			proxy.active();
// 		}
// 		else if ('t' == c) {
// 			dr.requestInterruption();//ÔÝÍ£Ïß³Ì
// 		}
// 		else if ('y' == c) {
// 			dr.start();
// 		
// 			
// 		}else if ('1' == c) {
// 
// 			I_SunnyTcsDbMedia_impl* command = new I_SunnyTcsDbMedia_impl(1);
// 			*command << SunnyTcsQueryStrFactory<MYSQL_SELECT>::produceQueryStr("class", DB_STR_LIST_TMP << "id" << "name" << "score", DB_STR_LIST_TMP << DB_EQUAL("id", "17"));
// 			*command << SunnyTcsQueryStrFactory<MYSQL_DELETE>::produceQueryStr("class");
// 			*command << SunnyTcsQueryStrFactory<MYSQL_INSERT>::produceQueryStr("class", DB_STR_LIST_TMP << "id" << "name", DB_STR_LIST_TMP << "14" << "'twelve'");
// 			*command << SunnyTcsQueryStrFactory<MYSQL_INSERT>::produceQueryStr("class", DB_STR_LIST_TMP << "id" << "name", DB_STR_LIST_TMP << "15" << "'twelve'");
// 			*command << SunnyTcsQueryStrFactory<MYSQL_INSERT>::produceQueryStr("class", DB_STR_LIST_TMP << "id" << "name", DB_STR_LIST_TMP << "16" << "'twelve'");
// 			proxy.reciveDbCommand(command);
// 		}
// 		else if ('n'==c) {
// 			
// 		}
// 
// 	}
// 	thRun = false;
// 	dr.requestInterruption();
// 	while (dr.isRunning());
// 	th.join();
// 	

	getchar();
	return a.exec();
}
