#pragma once

#include "basic_db.h"


class SunnyTcsMysqlProxyPrivate;



class BASIC_EXPORT SunnyTcsMysqlProxy {
public:
	
	//ctor
	SunnyTcsMysqlProxy();
	//copy ctor
	SunnyTcsMysqlProxy(SunnyTcsMysqlProxy const&);
	//dector
	virtual ~SunnyTcsMysqlProxy();
	//assign
	SunnyTcsMysqlProxy& operator=(SunnyTcsMysqlProxy const&) = delete;

	//getter and setter
	inline IpType getIp()const;
	inline portType getPort()const;
	inline std::string getUserName()const;
	inline std::string getPassword()const;
	inline std::string getDbName()const;
	inline void setIp(IpType const&);
	inline void setPort(portType const&);
	inline void setUserName(std::string const&);
	inline void setPassword(std::string const&);
	inline void setDbName(std::string const&);

	//mysql
	inline bool linkCheck();
	bool startTransaction(std::string* err = nullptr);
	bool commit(std::string* err = nullptr);
	bool rollback(std::string* err = nullptr);
	bool query(std::string sqlStr, bool commmit = true ,std::string* err = nullptr, int32_t* fieldNum =nullptr , std::vector<std::string>* ret = nullptr);
	bool connect();
	inline void freeConnect();

private:
	std::unique_ptr< SunnyTcsMysqlProxyPrivate> d_ptr;
};

