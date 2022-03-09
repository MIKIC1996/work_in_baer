#pragma once


#include <string>
#include <sql/mysql.h>
#include <SunnyTcsBasicV3/SunnyTcsBasicV3.h>
#include <SunnyTcsPromiseV3/SunnyTcsPromise.hpp>
#include <SunnyTcsBasicV3/SunnyTcsDbGeneral.hpp>

#define DB_MAX_TRY_COUNT 3//�����ز�3��


using namespace basic;


//�洢ý�� ���ͽӿڣ������洢 ���ݿ�ָ�� �� ���ؽ��
template<typename _Sql, typename Container = QList<_Sql>>
class I_SunnyTcsDbMedia : public Container {
public:
	typedef _Sql				value_type;
	typedef Container			_Mybase;
	typedef I_SunnyTcsDbMedia	_Myt;

	//ctor
	explicit I_SunnyTcsDbMedia(qint32 id) :_id(id), _errorCode(ERROR_NO_ERROR), _tryCount(0) {}
	I_SunnyTcsDbMedia(const I_SunnyTcsDbMedia&) = default;
	I_SunnyTcsDbMedia& operator=(const I_SunnyTcsDbMedia&) = default;
	//dtor
	virtual ~I_SunnyTcsDbMedia() {}

	//getter
	inline qint32 getId()const { return _id; }
	inline quint16 getTryCount()const { return _tryCount; }
	inline bool isNoError()const { return _errorCode == 0; }
	inline quint32 getErrorCode()const { return _errorCode; }

	//setter
	void setId(qint32 id) { _id = id; }
	void setError(quint32 errorCode ) {_errorCode = errorCode;}
	void addTryCount() { ++_tryCount; }

	//member function
	void print()const { //��ӡ
		for (auto& ter : *this) {
			std::cout << ter._sqlCommand << std::endl;
		}
	}

	void init() { //��ʼ��
		_errorCode = ERROR_NO_ERROR;
		_tryCount = 0;
		this->clear();
	}

protected:
	
	quint8 _DbType;		//Ŀ�����ݿ�����
	quint64 _ConnId;	//Ŀ�����ݿ�ip
	qint32 _id;			//��ˮ��
	quint16 _tryCount;	//�ز�������������ƾ�ʧ��
	quint32 _errorCode;	//������ 0��ʾ�޴���
	
};


//ý��ӿ�
typedef I_SunnyTcsDbMedia<SqlString> I_SunnyTcsDbMedia_impl;



//���ݿ�洢ý�� �� �Ľӿ�
class I_SunnyTcsDbMediaPool {
public:
	virtual I_SunnyTcsDbMedia_impl* getResource() = 0;
	virtual void recircleResource(I_SunnyTcsDbMedia_impl*) = 0;
};




//ý��Ļ�ȡ��ʽ������һ��ͳһ�� ��ȡ�ͻ��յ�ȽϺ�
class SunnyTcsMediaFactory {
public:

// 	template<typename _Ty>
// 	static I_SunnyTcsDbMedia_impl* getResource(const _Ty& who) {
// 		typedef typename _Ty::db_tag _DbTag;
// 		std::lock_guard<QMutex> guard(_lock);
// 		return getResource_aux(_DbTag());
// 	}
// 
// 	static void recircleResource(I_SunnyTcsDbMedia_impl* ptr, General_Tag) {
// 		std::lock_guard<QMutex> guard(_lock);
// 		_generalMedia.push_back(ptr);
// 	}
// 
// 	static void recircleResource(I_SunnyTcsDbMedia_impl* ptr, MySql_tag) {
// 		recircleResource(ptr,General_Tag());
// 	}
// 
// 	static void recircleResource(I_SunnyTcsDbMedia_impl* ptr, Sqllite_tag) {
// 		recircleResource(ptr,General_Tag());
// 	}
// 
// 	static void recircleResource(I_SunnyTcsDbMedia_impl* ptr, Redis_tag) {
// 		recircleResource(ptr,General_Tag());
// 	}
// 
// 	static void recircleResource(I_SunnyTcsDbMedia_impl* ptr, Oracle_tag) {
// 		recircleResource(ptr,General_Tag());
// 	}
// 
// private:
// 	SunnyTcsMediaFactory() {}
// 	SunnyTcsMediaFactory(const SunnyTcsMediaFactory&) = delete;
// 	SunnyTcsMediaFactory& operator=(const SunnyTcsMediaFactory&) = delete;
// 	~SunnyTcsMediaFactory() {}
// 
// protected:
// 	static I_SunnyTcsDbMedia_impl* getResource_aux(General_Tag) {
// 		if (_generalMedia.isEmpty()) {
// 			qint32 add = _generalMedia.count() * 2 + 20; //����������
// 			for (int i = 0; i < add; ++i) {
// 				_generalMedia.push_back(new I_SunnyTcsDbMedia_impl(
// 					nextId()));
// 			}
// 		}
// 		I_SunnyTcsDbMedia_impl* ret = _generalMedia.first();
// 		_generalMedia.pop_front();
// 		return ret;
// 	}
// 
// 	static qint32 nextId() {
// 		return _MediaCounter = _MediaCounter >= 9999999 ? 1 : 1 + _MediaCounter; //��Χ1 -- 10000000
// 	}
// 
// 	static void releaseResource() {
// 		std::lock_guard<QMutex> guard(_lock);
// 		for (auto ptr : _generalMedia) {
// 			delete ptr;
// 			ptr = nullptr;
// 		}
// 		_generalMedia.clear();
// 	}
// 
// protected:
// 	static QQueue< I_SunnyTcsDbMedia_impl* > _generalMedia; //ͨ��media
// 	static qint32 _MediaCounter;
// 	static QMutex _lock;
};








