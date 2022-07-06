#pragma once




#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsLibGeneral.hpp"

//数据库操作通用文件，提供了自动生成sql语句的方法。


//中文支持c风格字符串
static QTextCodec* pcode = QTextCodec::codecForName("GBK");
#define QSTRING_GBK(str) \
		pcode->toUnicode(str)
#define STD_STRING_GBK(str)\
		pcode->toUnicode(str).toStdString()
#define DB_STR_LIST_TMP QList<QString>()


//关系运算符
#define DB_EQUAL(val1,val2) \
 QString("%1=%2").arg(val1).arg(val2)

#define DB_UNEQUAL(val1,val2) \
 QString("%1!=%2").arg(val1).arg(val2)

#define DB_BIGGER(val1,val2) \
 QString("%1>%2").arg(val1).arg(val2)

#define DB_SMALLER(val1,val2) \
 QString("%1<%2").arg(val1).arg(val2)

#define DB_BIGGER_EQUAL(val1,val2) \
 QString("%1>=%2").arg(val1).arg(val2)

#define DB_SMALLER_EQUAL(val1,val2) \
 QString("%1<=%2").arg(val1).arg(val2)


namespace basic {

	//可能会用到 的 数据库标识类
	struct General_Tag {
		static constexpr quint8 value = 0;
		static constexpr char* value_str = "unknow";
	};
	struct MySql_tag :General_Tag {
		static constexpr quint8 value = 1;
		static constexpr char* value_str = "mysql";
	};
	struct Sqllite_tag :General_Tag {
		static constexpr quint8 value = 2;
		static constexpr char* value_str = "sqllite";
	};
	struct Redis_tag :General_Tag {
		static constexpr quint8 value = 3;
		static constexpr char* value_str = "redis";
	};
	struct Oracle_tag :General_Tag {
		static constexpr quint8 value = 4;
		static constexpr char* value_str = "oracle";
	};


	//sql语句
	struct SqlString {
		qint8 _sqlMethod;
		std::string _sqlCommand;
	};


	//字符串连接
	static QString combineStr(const QList<QString>& str_list, const QString& linkFlag) {
		QString ret;
		for (auto& ter : str_list) {
			ret += ter;
			ret += linkFlag;
		}
		return ret.count() > 0 ? ret.mid(0, ret.count() - linkFlag.count()) : ret;
	}


	//--------------------- mysql 通用工具库 -------------------------
	enum E_MysqlOperatoion {
		UNDEFINED_SQL_OPERATION =0,
		MYSQL_INSERT = 1,
		MYSQL_DELETE = 2,
		MYSQL_UPDATE = 3,
		MYSQL_SELECT = 4,
		MYSQL_START_TRANSACTION =5,
		MYSQL_COMMIT =6,
		MYSQL_ROLLBACK =7
	};


	/*mysql flag 定义
	位	 方式	   true		 false
	0	CONDITION	 AND	OR		条件连接关系	
	1	SELECT     DISTINCT  NOT DISTINCT   查询不重复
	2	
	3   
	4	
	5	
	6	
	7	
	8	
	9	
	10
	11
	12
	13
	14
	15
	16
	*/

#define MYSQL_FLAG_CONDITION	 SunnyTcsBinary<1>::value
#define MYSQL_FLAG_DISTINCT		 SunnyTcsBinary<10>::value


	template<int method>
	class SunnyTcsQueryStrFactory {
	public:
		SqlString produceQueryStr()const {
			static_assert(std::_Always_false<int>::value, "you can't export a sql str  with a unexisted method")
			return SqlString();
		}
	};


	//查
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_SELECT> {
	public:

		static SqlString produceQueryStr(QString fromTable,
			const QList<QString>& fids, const QList<QString>& cons, qint32 flag = 0) {

			if (fids.isEmpty() || fromTable.isEmpty()) {
				return SqlString();
			}

			QString str("SELECT %1 FROM %2 ");
			str = str.arg(combineStr(fids, QString(","))).arg(fromTable);

			if (cons.count() > 0) {
				str += "WHERE ";
				QString&& conditions = combineStr(cons, flag & 0x01 ? " OR " : " AND ");
				str += conditions;
			}
			str += ';';
			return SqlString{ MYSQL_SELECT, str.toStdString() };
		}

	};

	
	//增
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_INSERT> {
	public:

		static SqlString produceQueryStr(QString fromTable,
			const QList<QString>& fids, const QList<QString>& vals, qint32 flag = 0) {

			if (fids.isEmpty() || fromTable.isEmpty() || vals.isEmpty()) {
				return SqlString();
			}

			QString str("INSERT INTO %1 (%2) VALUES (%3);");
			str = str.arg(fromTable).arg(combineStr(fids, QString(","))).arg(combineStr(vals, QString(",")));
			return SqlString{ MYSQL_INSERT, str.toStdString() };
		}
	};


	//删除
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_DELETE> {
	public:

		static SqlString produceQueryStr(QString fromTable,
			const QList<QString>& vals = DB_STR_LIST_TMP, qint32 flag = 0) {

			if (vals.isEmpty()) {
				return fromTable.isEmpty() ? SqlString() : SqlString{ 0, QString("DELETE FROM %1;").arg(fromTable).toStdString() };
			}

			QString str("DELETE FROM %1 WHERE (%2);");
			str = str.arg(fromTable).arg(combineStr(vals, flag & 0x01 ? " OR " : " AND "));
			return SqlString{ MYSQL_DELETE, str.toStdString() };
		}

	};


	//改 update student set age=20,gender='female' where name='tom';
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_UPDATE> {
	public:

		static SqlString produceQueryStr(QString fromTable,
			const QList<QString>& fids, const QList<QString>& cons, qint32 flag = 0) {

			if (fids.isEmpty() || fromTable.isEmpty()) {
				return SqlString();
			}

			QString str("UPDATE %1 SET %2 ");
			str = str.arg(fromTable).arg(combineStr(fids, QString(",")));

			if (cons.count() > 0) {
				str += "WHERE ";
				QString&& conditions = combineStr(cons, flag & 0x01 ? " OR " : " AND ");
				str += conditions;
			}
			str += ';';
			return SqlString{ MYSQL_UPDATE, str.toStdString() };
		}
	};


	//事务
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_START_TRANSACTION> {
	public:

		static SqlString produceQueryStr(){
			return SqlString{ MYSQL_START_TRANSACTION, "start transaction;" };
		}
	};

	//提交
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_COMMIT> {
	public:

		static SqlString produceQueryStr(){
			return SqlString{ MYSQL_COMMIT, "commit;" };
	}
	};


	//回滚
	template<>
	class SunnyTcsQueryStrFactory<MYSQL_ROLLBACK> {
	public:

		static SqlString produceQueryStr(){
			return SqlString{ MYSQL_ROLLBACK, "rollback;" };
	}
	};


}

