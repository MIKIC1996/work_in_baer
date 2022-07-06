#pragma once
#include "SunnyTcsGeneralArg.hpp"


//��sunnyTcsByteArg��̫���⣬��д�İ汾
namespace basic {

	
	template<typename _Ty>
	struct SunnyTcsTypeTraits {

		typedef _Ty tar_type;
		
		typedef typename std::_If< std::is_same<void, _Ty>::value, std::true_type, std::false_type >::type is_void;

		typedef typename std::is_trivially_destructible<_Ty>::type  is_trivial_detor;

		typedef std::integral_constant<std::size_t, sizeof(_Ty)> type_size;

		typedef typename std::_If< type_size::value <= callable_storage_size, std::true_type, std::false_type >::type  is_store_local;

		
		//�������ݳ�ʼ���ڴ�
		static void initDataStorage(SunnyTcsAnyData& data,const _Ty& val) {
			static_assert(!is_void::value, "use void type in typeArg");
			initDataStorage_store_local(data, val, is_store_local());
		}

		//�ͷ��ڴ�
		static void releaseStorage(SunnyTcsAnyData& data) {
			static_assert(!is_void::value, "use void type in typeArg");
			releaseStorage_is_store_local(data, is_store_local());
		}


		//�����ĺ���
		static void copyConstructInMen(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst) {
			static_assert(!is_void::value, "use void type in typeArg");
			copyConstructInMen_is_store_local(srcData,dst , is_store_local());
		}


		//��ָ��λ���ڴ���д���
		static bool constructInMem(const SunnyTcsAnyData& data, void* pos, std::size_t size) {
			if (is_void::value || size < type_size::value)return false; //ָ�����ڴ�ռ������������
			constructInMem_store_local(data, pos, is_store_local());
			return true;
		}

		
		//������תΪ�ֽ�����
		static void bytesFromMem(QByteArray& ret , const SunnyTcsAnyData& data) {
			ret.clear();
			bytesFromMem_store_local(ret, data, is_store_local());
		}

		//ת��Ϊ�ַ��ĺ���
		static QString toDataString(const SunnyTcsAnyData& data) {
			return toDataString_store_local(data, is_store_local());
		}

	protected:
		//��ʼ�����ڲ�����
		static void initDataStorage_store_local(SunnyTcsAnyData& data,const _Ty& val, std::true_type) {
			new (data.access())_Ty(val);
		}

		static void initDataStorage_store_local(SunnyTcsAnyData& data, const _Ty& val, std::false_type) {
			data.access<_Ty*>() = new _Ty(val);
		}


		//�ͷŵ��ڲ�����
		static void releaseStorage_is_store_local(SunnyTcsAnyData& data, std::true_type) {//���ڱ���
			releaseStorage_is_store_local_true_trivial_detor(data, is_trivial_detor());
		}
		
		static void releaseStorage_is_store_local_true_trivial_detor(SunnyTcsAnyData& data, std::true_type) {//���ڱ��ز��� ������������Ҫ
			std::memset(data.access(), 0, callable_storage_size);//ֱ�������ڴ����
		}


		static void releaseStorage_is_store_local_true_trivial_detor(SunnyTcsAnyData& data, std::false_type) {//���ڱ��ز��� ��������������Ҫ
			data.access<_Ty>().~Ty();//�ȵ�����������
			releaseStorage_is_store_local_true_trivial_detor(data, std::true_type());
		}


		static void releaseStorage_is_store_local(SunnyTcsAnyData& data, std::false_type) { //�����ڱ���
			delete data.access<_Ty*>(); //ֱ��delete����
		}

		//�������ڲ�����
		static void copyConstructInMen_is_store_local(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst, std::true_type) {
			std::memcpy(dst.access(), srcData.access(), callable_storage_size);
		}

		static void copyConstructInMen_is_store_local(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst, std::false_type) {
			dst.access<_Ty*>() = new _Ty(*(srcData.access<_Ty*>()));//���
		}

		//ָ��λ�ô������ڲ�����
		static void constructInMem_store_local(const SunnyTcsAnyData& data, void* pos,std::true_type ) {//���ڱ���
			new(pos) _Ty(data.access<_Ty>());
		}
		
		static void constructInMem_store_local(const SunnyTcsAnyData& data, void* pos, std::false_type) {//�����ڱ���
			new(pos) _Ty( *(data.access<_Ty*>()) );
		}

		//ת�ֽ�������ڲ�����
		static void bytesFromMem_store_local(QByteArray& ret, const SunnyTcsAnyData& data,std::true_type) {//���ڱ���
			ret = SunnyTcsBytesTransformer::toBytes(data.access<_Ty>());
		}

		static void bytesFromMem_store_local(QByteArray& ret, const SunnyTcsAnyData& data, std::false_type) {//�����ڱ���
			ret = SunnyTcsBytesTransformer::toBytes( *(data.access<_Ty*>()) );
		}

		//ת��Ϊ�ַ��ĺ������ڲ�����
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


		//�������ݳ�ʼ���ڴ�
		static void initDataStorage(SunnyTcsAnyData& data,const string_tcs& val) {
			data.access<string_tcs*>() = new string_tcs(val);
		}

		//�ͷ��ڴ�
		static void releaseStorage(SunnyTcsAnyData& data) {
			delete data.access<string_tcs*>();
			std::memset(data.access(), 0, callable_storage_size);
		}

		//�����ĺ���
		static void copyConstructInMen(const SunnyTcsAnyData& srcData, SunnyTcsAnyData& dst) {
			dst.access<string_tcs*>() = new string_tcs( *(srcData.access<string_tcs*>()) );
		}

		//��ָ��λ���ڴ���д���
		static bool constructInMem(const SunnyTcsAnyData& data, void* pos, std::size_t size) {
			if (size < callable_storage_size)return false; //ָ�����ڴ�ռ������������
			new(pos) string_tcs( *(data.access<string_tcs*>()) );
			return true;
		}

		//������תΪ�ֽ�����
		static void bytesFromMem(QByteArray& ret, const SunnyTcsAnyData& data) {
			ret.clear();
			ret += data.access<string_tcs*>()->toLocal8Bit();
		}

		//ת��Ϊ�ַ��ĺ���
		static QString toDataString(const SunnyTcsAnyData& data) {
			return *(data.access<string_tcs*>());
		}

	};


	//arg�����л���������
	class  SunnyTcsTypeArgBuilder;


	//���Ͳ��� ��������SunnyTcsArg���Ծ������ͽ����˴�С������ѡ����ʵĴ洢���ԣ�������ȫ����QByteArray�洢
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
		//��ô洢����ָ��
		void* access() { return _data.access(); }
		const void* access()const { return _data.access(); }
		template<typename _Ty> //���ڴ�����ת��Ϊ������Ҫ������
		_Ty& access() {return *static_cast<_Ty*>(access());}
		template<typename _Ty>
		const _Ty& access()const {return *static_cast<const _Ty*>(access());}

		//��ָ��λ�ý��й���
		bool constructInMem(void* pos, std::size_t size);
		//ת�ֽ�����
		QByteArray bytesFromMem()const;
		//תjson
		QJsonObject toJson()const;
		//ת�����ַ���
		QString toDataString()const;

		//��ȡ����
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
		if (_releaseStorageFunc)_releaseStorageFunc(_data);//���ͷ�һ������
		using type_traits = SunnyTcsTypeTraits<_Ty>;
		type_traits::initDataStorage(_data, rhs);
		_copyConstructInMenFunc = &type_traits::copyConstructInMen;
		_releaseStorageFunc = &type_traits::releaseStorage;
		_constructInMemFunc = &type_traits::constructInMem;
		_bytesFromMemFunc = &type_traits::bytesFromMem;
		_toDataStringFunc = &type_traits::toDataString;
		return *this;
	}

	//��������
	typedef SunnyTcsTypeArg SunnyTcsArg;

	//�����л������з���arg
	class SUNNYTCSBASICV3_EXPORT SunnyTcsTypeArgBuilder {
	public:
		//��arg��json�з���
		static bool buildTypeArgFromJson(SunnyTcsTypeArg& arg, const QJsonObject& jobj ,QString& err);
		//ֱ�Ӵ�����arg�����������з���
		static bool buildTypeArgByBytes(SunnyTcsTypeArg& arg, const QByteArray& bytes);
		//�������ͺ�����������з���
		static bool buildTypeArgByTypeAndDataBytes(SunnyTcsTypeArg& arg, E_ARG_TYPE argType, const QByteArray& bytes, QString& err);	
		//�������У����ַ���ת��Ϊarg
		static bool buildTypeArgByString(SunnyTcsTypeArg& arg, E_ARG_TYPE argType, QString& str);
	};


}


