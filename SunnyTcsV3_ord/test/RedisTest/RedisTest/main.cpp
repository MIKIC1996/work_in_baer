#include <QtCore/QCoreApplication>

#include <iostream>
#include <hiredis.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

static redisContext* con = nullptr;

bool setString(string key, string value) {
	char buffer[200];
	sprintf(buffer, "set %s %s", key.c_str(), value.c_str());

	cout << buffer << endl;

	redisReply* rep = nullptr;
	rep = (redisReply*)redisCommand(con, buffer);

	if (!rep) {
		cout << "setString error" << endl;
		return false;
	}
	else {
		cout << rep->str << endl;
	}
	return true;
}






string getString(string key) {
	char buffer[200];
	sprintf(buffer,"get %s", key.c_str());
	redisReply* rep = nullptr;
	rep = (redisReply*)redisCommand(con, buffer);
	if (!rep) {
		cout << "get error" << endl;
	}
	return string(rep->str);
}






int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	 con = redisConnect("127.0.0.1", 6379);
	
	if (!con || con->err) {
		cout << "link error" << endl;
	}else{
		cout << "link success" << endl;
	}

	//setString("you", "aremine");
	cout << getString("you") << endl;

    return a.exec();
}










