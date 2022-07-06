#pragma once
#include "SunnyTcsGeneralArg.hpp"


//对sunnyTcsByteArg不太满意，重写的版本
namespace basic {

	
	template<typename _Ty>
	struct SunnyTcsTypeTraits {

		typedef _Ty tar_type;
		
		typedef typename std::_If< std::is_same<void, _Ty>::value, std::true_type, std::false_type >::type is_void;

		typedef typename std::is_trivially_destructible<_Ty>::type  is_trivial_detor;

		typedef std::integral_constant<std::size_t, sizeof(_Ty)> type_size;

		typedef typename std::_If< type_size::value <= callable_storage_size, std::true_type, std::false_type >::type  is_store_local;

		
		//按照数据初始化内存
		static void initDataStorage(SunnyTcsAnyData& data,const _Ty& val) {
			static_assert(!is_void::value, "use void type in typeArg");
			initDataStorage_store_local(data, val, is_store_local());
		}

		//释放内存
		static void releaseStorage(SunnyTcsAnyData& data) {
			static_assert(!is_void::value, "use void type in typeArg");
			releaseStorage_is_store_local(data, is_store_local());
		}


		//拷贝的函数
		static void copyConstructInMen(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst) {
			static_assert(!is_void::value, "use void type in typeArg");
			copyConstructInMen_is_store_local(srcData,dst , is_store_local());
		}


		//在指定位置内存进行创建
		static bool constructInMem(const SunnyTcsAnyData& data, void* pos, std::size_t size) {
			if (is_void::value || size < type_size::value)return false; //指定的内存空间允许大于类型
			constructInMem_store_local(data, pos, is_store_local());
			return true;
		}

		
		//将数据转为字节数组
		static void bytesFromMem(QByteArray& ret , const SunnyTcsAnyData& data) {
			ret.clear();
			bytesFromMem_store_local(ret, data, is_store_local());
		}

		//转换为字符的函数
		static QString toDataString(const SunnyTcsAnyData& data) {
			return toDataString_store_local(data, is_store_local());
		}

	protected:
		//初始化的内部函数
		static void initDataStorage_store_local(SunnyTcsAnyData& data,const _Ty& val, std::true_type) {
			new (data.access())_Ty(val);
		}

		static void initDataStorage_store_local(SunnyTcsAnyData& data, const _Ty& val, std::false_type) {
			data.access<_Ty*>() = new _Ty(val);
		}


		//释放的内部函数
		static void releaseStorage_is_store_local(SunnyTcsAnyData& data, std::true_type) {//存于本地
			releaseStorage_is_store_local_true_trivial_detor(data, is_trivial_detor());
		}
		
		static void releaseStorage_is_store_local_true_trivial_detor(SunnyTcsAnyData& data, std::true_type) {//存于本地并且 析构函数不重要
			std::memset(data.access(), 0, callable_storage_size);//直接清理内存就行
		}


		static void releaseStorage_is_store_local_true_trivial_detor(SunnyTcsAnyData& data, std::false_type) {//存于本地并且 但是析构函数重要
			data.access<_Ty>().~Ty();//先调用析构函数
			releaseStorage_is_store_local_true_trivial_detor(data, std::true_type());
		}


		static void releaseStorage_is_store_local(SunnyTcsAnyData& data, std::false_type) { //不存于本地
			delete data.access<_Ty*>(); //直接delete就行
		}

		//拷贝的内部函数
		static void copyConstructInMen_is_store_local(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst, std::true_type) {
			std::memcpy(dst.access(), srcData.access(), callable_storage_size);
		}

		static void copyConstructInMen_is_store_local(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst, std::false_type) {
			dst.access<_Ty*>() = new _Ty(*(srcData.access<_Ty*>()));//深拷贝
		}

		//指定位置创建的内部函数
		static void constructInMem_store_local(const SunnyTcsAnyData& data, void* pos,std::true_type ) {//存在本地
			new(pos) _Ty(data.access<_Ty>());
		}
		
		static void constructInMem_store_local(const SunnyTcsAnyData& data, void* pos, std::false_type) {//不存在本地
			new(pos) _Ty( *(data.access<_Ty*>()) );
		}

		//转字节数组的内部函数
		static void bytesFromMem_store_local(QByteArray& ret, const SunnyTcsAnyData& data,std::true_type) {//存在本地
			ret = SunnyTcsBytesTransformer::toBytes(data.access<_Ty>());
		}

		static void bytesFromMem_store_local(QByteArray& ret, const SunnyTcsAnyData& data, std::false_type) {//不存在本地
			ret = SunnyTcsBytesTransformer::toBytes( *(data.access<_Ty*>()) );
		}

		//转换为字符的函数的内部函数
		static QString toDataString_store_local(const SunnyTcsAnyData& data,std::true_type ) {
			return QString::number(data.access<_Ty>());
		}

		static QString toDataString_store_local(const SunnyTcsAnyData& data,std::false_type) {
			return QString::number( *(data.access<_Ty*>()) );
		}

	};




	template<>
	struct SunnyTcsTypeTraits<string_tcs> {

		typedef string_tcs tar_type;

		typedef std::false_type  is_void;

		typedef std::false_type  is_trivial_detor;

		typedef std::integral_constant<std::size_t, sizeof(string_tcs)> type_size;

		typedef std::false_type  is_store_local;


		//按照数据初始化内存
		static void initDataStorage(SunnyTcsAnyData& data,const string_tcs& val) {
			data.access<string_tcs*>() = new string_tcs(val);
		}

		//释放内存
		static void releaseStorage(SunnyTcsAnyData& data) {
			delete data.access<string_tcs*>();
			std::memset(data.access(), 0, callable_storage_size);
		}

		//拷贝的函数
		static void copyConstructInMen(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst) {
			dst.access<string_tcs*>() = new string_tcs( *(srcData.access<string_tcs*>()) );
		}

		//在指定位置内存进行创建
		static bool constructInMem(const SunnyTcsAnyData& data, void* pos, std::size_t size) {
			if (size < callable_storage_size)return false; //指定的内存空间允许大于类型
			new(pos) string_tcs( *(data.access<string_tcs*>()) );
			return true;
		}

		//将数据转为字节数组
		static void bytesFromMem(QByteArray& ret, const SunnyTcsAnyData& data) {
			ret.clear();
			ret += data.access<string_tcs*>()->toLocal8Bit();
		}

		//转换为字符的函数
		static QString toDataString(const SunnyTcsAnyData& data) {
			return *(data.access<string_tcs*>());
		}

	};


	//arg反序列化工具声明
	class  SunnyTcsTypeArgBuilder;


	//类型参数 用来代替SunnyTcsArg，对具体类型进行了大小分析，选择合适的存储策略，而不是全部用QByteArray存储
	class SUNNYTCSBASICV3_EXPORT SunnyTcsTypeArg
	{
	public:
		static QMap<E_ARG_TYPE, QString> supportArgTyps;
		static bool mapInitFunc();
		static bool mapInit;
		

		static constexpr qint32 argHeadSize = 8;
		friend class SunnyTcsTypeArgBuilder;
		 

		//default ctor
		SunnyTcsTypeArg();
		//ctor
		template<typename _Ty>
		explicit SunnyTcsTypeArg(const _Ty& val);
		//copy ctor
		SunnyTcsTypeArg(const SunnyTcsTypeArg& rhs);
		//move ctor
		SunnyTcsTypeArg(SunnyTcsTypeArg&& rhs);
		//detor
		virtual ~SunnyTcsTypeArg(){if (_releaseStorageFunc)_releaseStorageFunc(_data);}

		//operator=
		template<typename _Ty>
		SunnyTcsTypeArg& operator=(const _Ty& rhs);
		SunnyTcsTypeArg& operator=(const SunnyTcsTypeArg& rhs);
		//operator= move
		SunnyTcsTypeArg& operator=(SunnyTcsTypeArg&& rhs);
		//operator==
		bool operator==(const SunnyTcsTypeArg& arg)const;

		//getterr
		E_ARG_TYPE getType()const { return _type; }
		//获得存储数据指针
		void* access() { return _data.access(); }
		const void* access()const { return _data.access(); }
		template<typename _Ty> //将内存数据转化为我们需要的类型
		_Ty& access() {return *static_cast<_Ty*>(access());}
		template<typename _Ty>
		const _Ty& access()const {return *static_cast<const _Ty*>(access());}

		//在指定位置进行构建
		bool constructInMem(void* pos, std::size_t size);
		//转字节数组
		QByteArray bytesFromMem()const;
		//转json
		QJsonObject toJson()const;
		//转数据字符串
		QString toDataString()const;

		//获取描述
		QString toString()const;
		
	protected:
		E_ARG_TYPE _type;
		SunnyTcsAnyData _data;
		void (*_copyConstructInMenFunc)(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst);
		void (*_releaseStorageFunc)(SunnyTcsAnyData& data);
		bool (*_constructInMemFunc)(const SunnyTcsAnyData& data, void* pos, std::size_t size);
		void (*_bytesFromMemFunc)(QByteArray& ret, const SunnyTcsAnyData& data);
		QString(*_toDataStringFunc)(const SunnyTcsAnyData& data);
	};


	template<typename _Ty>
	inline SunnyTcsTypeArg::SunnyTcsTypeArg(const _Ty & val)
	{
		_type = SunnyTcsArgTraits<_Ty>::argType();
		using type_traits = SunnyTcsTypeTraits<_Ty>;
		type_traits::initDataStorage(_data, val);
		_copyConstructInMenFunc = &type_traits::copyConstructInMen;
		_releaseStorageFunc = &type_traits::releaseStorage;
		_constructInMemFunc = &type_traits::constructInMem;
		_bytesFromMemFunc = &type_traits::bytesFromMem;
		_toDataStringFunc = &type_traits::toDataString;
	}

	template<typename _Ty>
	inline SunnyTcsTypeArg & SunnyTcsTypeArg::operator=(const _Ty & rhs)
	{
		_type = SunnyTcsArgTraits<_Ty>::argType();
		if (_releaseStorageFunc)_releaseStorageFunc(_data);//先释放一下数据
		using type_traits = SunnyTcsTypeTraits<_Ty>;
		type_traits::initDataStorage(_data, rhs);
		_copyConstructInMenFunc = &type_traits::copyConstructInMen;
		_releaseStorageFunc = &type_traits::releaseStorage;
		_constructInMemFunc = &type_traits::constructInMem;
		_bytesFromMemFunc = &type_traits::bytesFromMem;
		_toDataStringFunc = &type_traits::toDataString;
		return *this;
	}

	//另外命名
	typedef SunnyTcsTypeArg SunnyTcsArg;

	//从序列化数据中分析arg
	class SUNNYTCSBASICV3_EXPORT SunnyTcsTypeArgBuilder {
	public:
		//从arg的json中分析
		static bool buildTypeArgFromJson(SunnyTcsTypeArg& arg, const QJsonObject& jobj ,QString& err);
		//直接从整个arg的数据数据中分析
		static bool buildTypeArgByBytes(SunnyTcsTypeArg& arg, const QByteArray& bytes);
		//根据类型和数据数组进行分析
		static bool buildTypeArgByTypeAndDataBytes(SunnyTcsTypeArg& arg, E_ARG_TYPE argType, const QByteArray& bytes, QString& err);	
		//从类型中，将字符串转化为arg
		static bool buildTypeArgByString(SunnyTcsTypeArg& arg, E_ARG_TYPE argType, QString& str);
	};


}


