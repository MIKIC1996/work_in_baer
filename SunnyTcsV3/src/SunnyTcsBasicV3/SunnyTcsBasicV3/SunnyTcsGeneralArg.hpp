#pragma once
#include "sunnytcsbasicv3_global.h"


//枚举类型转换检查
#define E_ARG_TYPE_CHECK(p)  if(!((p>=0 && p<=0x0D )||(p>=0x71 && p<=0x78))){Q_ASSERT(0);}
//SunnyTcsArg 的 头大小
#define ARG_HEAD_LENGTH 5


#define _THROW_FROMBYTES_ERROR throw (SunnyTcsException<ERROR_BASIC_ARG_FROMBYTE_ERROR>)
#define _THROW_FROMBYTES_ERROR_T throw SunnyTcsException<ERROR_BASIC_ARG_FROMBYTE_ERROR>()
#define _THROW_TOBYTES_ERROR throw (SunnyTcsException<ERROR_BASIC_ARG_TOBYTE_ERROR>)
#define _THROW_TOBYTES_ERROR_T throw SunnyTcsException<ERROR_BASIC_ARG_TOBYTE_ERROR>()


namespace basic {

	//typedef 方便修改
	typedef char        char_tcs;
	typedef bool        bool_tcs;
	typedef qint8       int8_tcs;
	typedef qint16      int16_tcs;
	typedef qint32      int32_tcs;
	typedef qint64      int64_tcs;
	typedef quint8      uint8_tcs;
	typedef quint16     uint16_tcs;
	typedef quint32     uint32_tcs;
	typedef quint64     uint64_tcs;
	typedef QString     string_tcs;
	typedef QByteArray  byteArray_tcs;


	//arg type enum
	enum E_ARG_TYPE {
		//undef
		ARG_UNDEFINED = 0x00,
		//obt
		ARG_CHAR = 0x01,
		ARG_BOOL = 0x02,
		ARG_MIXED = 0x03,
		//signed
		ARG_INT8 = 0x04,
		ARG_INT16 = 0x05,
		ARG_INT32 = 0x06,
		ARG_INT64 = 0x07,
		//unsigned
		ARG_UINT8 = 0x08,
		ARG_UINT16 = 0x09,
		ARG_UINT32 = 0x0A,
		ARG_UINT64 = 0x0B,
		//oth
		ARG_QBYTEARRAY = 0x0C,
		ARG_QSTRING = 0x0D,
		//reserve
		ARG_RESERVE_01 = 0x71,
		ARG_RESERVE_02 = 0x72,
		ARG_RESERVE_03 = 0x73,
		ARG_RESERVE_04 = 0x74,
		ARG_RESERVE_05 = 0x75,
		ARG_RESERVE_06 = 0x76,
		ARG_RESERVE_07 = 0x77,
		ARG_RESERVE_08 = 0x78
	};


	//字节转换类
	class SunnyTcsBytesTransformer {
	public:
		template<class T>
		static QByteArray toBytes(const T& obj) {
			int size = sizeof(T);
			QByteArray bytes;
			for (int i = 1; i <= size; ++i) {
				uint8_t bye = (obj >> (size - i) * 8);
				bye = (bye &= 0xff);
				bytes.append(bye);
			}
			return bytes;
		}

		template<class T>
		static T fromByte(QByteArray bytes) {
			int size = sizeof(T);
			if (bytes.count() < size) {
				return 0;
			}
			T dst(0);
			T temp(0);
			int index{ 0 };
			T basc(0xff);
			for (int i = 0; i < size; ++i) {
				temp = (T)(bytes.at(i));
				index = size - i - 1;
				dst |= ((temp << (index * 8)) & (basc << (index * 8)));
			}
			return dst;
		}
	};


	//类型萃取类
	//未注册类
	template <typename Arg_type>
	class SunnyTcsArgTraits {
	public:
		static qint32 size(Arg_type arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_UNDEFINED; }
		static Arg_type fromBytes(const QByteArray& bytes) _THROW_FROMBYTES_ERROR
		{
			_THROW_FROMBYTES_ERROR_T;
			return Arg_type();
		}
		static QByteArray toBytes(Arg_type arg) _THROW_TOBYTES_ERROR
		{
			return QByteArray();
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size) _THROW_FROMBYTES_ERROR
		{
			//static_assert(std::_Always_false<int>::value, "you cant use a unregistered type in SunnyTcsArgTraits."); //不允许使用未经注册的类
			_THROW_FROMBYTES_ERROR_T;
		}
	};


	//用来去除引用属性
	template<typename Arg_type>
	class SunnyTcsArgTraits<Arg_type&>
	{
	public:
		static qint32 size(Arg_type& arg) { return SunnyTcsArgTraits<Arg_type>::size(arg); }
		static E_ARG_TYPE argType() { return SunnyTcsArgTraits<Arg_type>::argType(); }
		static auto fromBytes(const QByteArray& bytes)->decltype(SunnyTcsArgTraits<Arg_type>::fromBytes(bytes)) 
		{
			return SunnyTcsArgTraits<Arg_type>::fromBytes(bytes);
		}
		static QByteArray toBytes(Arg_type& arg) 
		{
			return SunnyTcsArgTraits<Arg_type>::toBytes(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size) 
		{
			SunnyTcsArgTraits<Arg_type>::constructInMemoryPointed(bytes, target, size);
		}
	};


	//用来去除const属性
	template<typename Arg_type>
	class SunnyTcsArgTraits<const Arg_type>
	{
	public:
		static qint32 size(const Arg_type arg) { return SunnyTcsArgTraits<Arg_type>::size(arg); }
		static E_ARG_TYPE argType() { return SunnyTcsArgTraits<Arg_type>::argType(); }
		static auto fromBytes(const QByteArray& bytes)->decltype(SunnyTcsArgTraits<Arg_type>::fromBytes(bytes, ok)) 
		{
			return SunnyTcsArgTraits<Arg_type>::fromBytes(bytes, ok);
		}
		static QByteArray toBytes(const Arg_type arg) 
		{
			return SunnyTcsArgTraits<Arg_type>::toBytes(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)
		{
			SunnyTcsArgTraits<Arg_type>::constructInMemoryPointed(bytes, target, size);
		}
	};


	//char 类
	template<>
	class SunnyTcsArgTraits<char_tcs> {
	public:
		typedef char_tcs type;

		static qint32 size(char_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_CHAR; }
		static char_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(char_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return bytes.at(bytes.count() - 1); //为了支持不同类型间比较，应该从最后一个字节开始转化
		}
		static QByteArray toBytes(char arg) _THROW_TOBYTES_ERROR
		{
			return QByteArray().append(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<bool_tcs> {
	public:
		typedef bool_tcs type;

		static qint32 size(bool_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_BOOL; }
		static bool_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(bool_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return bytes.at(bytes.count() - 1) == 0x00 ? false : true;
		}
		static QByteArray toBytes(bool_tcs arg) _THROW_TOBYTES_ERROR
		{
			return QByteArray().append((char)arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<int8_tcs> {
	public:
		typedef int8_tcs type;

		static qint32 size(int8_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_INT8; }
		static int8_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(int8_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return static_cast<int8_tcs>(bytes.at(bytes.count() - 1));
		}
		static QByteArray toBytes(int8_tcs arg)_THROW_TOBYTES_ERROR
		{
			return QByteArray().append(static_cast<char>(arg));
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<int16_tcs> {
	public:
		typedef int16_tcs type;

		static qint32 size(int16_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_INT16; }
		static int16_tcs fromBytes(const QByteArray& bytes) _THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(int16_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return SunnyTcsBytesTransformer::fromByte<int16_tcs>(bytes.mid(bytes.count() - 2, 2));
		}
		static QByteArray toBytes(int16_tcs arg) _THROW_TOBYTES_ERROR
		{
			return SunnyTcsBytesTransformer::toBytes<int16_tcs>(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};



	template<>
	class SunnyTcsArgTraits<int32_tcs> {
	public:
		typedef int32_tcs type;

		static qint32 size(int32_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_INT32; }
		static int32_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(int32_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return SunnyTcsBytesTransformer::fromByte<int32_tcs>(bytes.mid(bytes.count() - 4, 4));
		}
		static QByteArray toBytes(int32_tcs arg)_THROW_TOBYTES_ERROR
		{
			return SunnyTcsBytesTransformer::toBytes<int32_tcs>(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<int64_tcs> {
	public:
		typedef int64_t type;

		static qint32 size(int64_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_INT64; }
		static int64_tcs fromBytes(const QByteArray& bytes) _THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(int64_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return SunnyTcsBytesTransformer::fromByte<int64_tcs>(bytes.mid(bytes.count() - 8, 8));
		}
		static QByteArray toBytes(int64_tcs arg) _THROW_TOBYTES_ERROR
		{
			return SunnyTcsBytesTransformer::toBytes<int64_tcs>(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<uint8_tcs> {
	public:
		typedef uint8_tcs type;

		static qint32 size(uint8_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_UINT8; }
		static uint8_tcs fromBytes(const QByteArray& bytes) _THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(uint8_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return static_cast<uint8_tcs>(bytes.at(0));
		}
		static QByteArray toBytes(uint8_tcs arg) _THROW_TOBYTES_ERROR
		{
			return QByteArray().append((char)arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<uint16_tcs> {
	public:
		typedef uint16_tcs type;

		static qint32 size(uint16_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_UINT16; }
		static uint16_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(uint16_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return SunnyTcsBytesTransformer::fromByte<uint16_tcs>(bytes.mid(bytes.count() - 2, 2));
		}
		static QByteArray toBytes(uint16_tcs arg) _THROW_TOBYTES_ERROR
		{
			return SunnyTcsBytesTransformer::toBytes<uint16_tcs>(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<uint32_tcs> {
	public:
		typedef uint32_tcs type;

		static qint32 size(uint32_tcs arg) { return sizeof(uint32_tcs); }
		static E_ARG_TYPE argType() { return ARG_UINT32; }
		static uint32_tcs fromBytes(const QByteArray& bytes) _THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(uint32_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return SunnyTcsBytesTransformer::fromByte<uint32_tcs>(bytes.mid(bytes.count() - 4, 4));
		}
		static QByteArray toBytes(uint32_tcs arg) _THROW_TOBYTES_ERROR
		{
			return SunnyTcsBytesTransformer::toBytes<uint32_tcs>(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<uint64_tcs> {
	public:
		typedef uint64_tcs type;

		static qint32 size(uint64_tcs arg) { return sizeof(arg); }
		static E_ARG_TYPE argType() { return ARG_UINT64; }
		static uint64_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			if (bytes.count() < sizeof(uint64_tcs))
			{
				_THROW_FROMBYTES_ERROR_T;
			}
			return SunnyTcsBytesTransformer::fromByte<uint64_tcs>(bytes.mid(bytes.count() - 8, 8));
		}
		static QByteArray toBytes(uint64_tcs arg)_THROW_TOBYTES_ERROR
		{
			return SunnyTcsBytesTransformer::toBytes<uint64_tcs>(arg);
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			type* ptr = (type*)target;
			type  ret = fromBytes(bytes);
			*ptr = ret;
		}
	};


	template<>
	class SunnyTcsArgTraits<byteArray_tcs> {
	public:
		typedef byteArray_tcs type;

		static qint32 size(byteArray_tcs arg) { return arg.count(); }
		static E_ARG_TYPE argType() { return ARG_QBYTEARRAY; }
		static byteArray_tcs fromBytes(const QByteArray& bytes)_THROW_FROMBYTES_ERROR
		{
			return bytes;
		}
		static QByteArray toBytes(byteArray_tcs arg)_THROW_TOBYTES_ERROR
		{
			return arg;
		}

		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			new (target)type(bytes);
		}
	};


	template<>
	class SunnyTcsArgTraits<string_tcs> {
	public:
		typedef string_tcs type;

		static qint32 size(string_tcs arg) { return arg.count(); }
		static E_ARG_TYPE argType() { return ARG_QSTRING; }
		static string_tcs fromBytes(const QByteArray& bytes) _THROW_FROMBYTES_ERROR
		{
			return QString::fromLocal8Bit(bytes);
		}
		static QByteArray toBytes(string_tcs arg)_THROW_TOBYTES_ERROR
		{
			return arg.toLocal8Bit();
		}
		//在指定内存上构造一个对象
		static void constructInMemoryPointed(const QByteArray& bytes, void* target, std::size_t size)_THROW_FROMBYTES_ERROR
		{
			if (size < sizeof(type)) {
				_THROW_FROMBYTES_ERROR_T;
			}
			new (target)type(QString::fromLocal8Bit(bytes));
		}
	};



	

	//construct in memory pointed 在指定内存上构造对象的 函数指针
	typedef void(*cimp)(const QByteArray&, void*, std::size_t);

	

	//万用类型的容器，通过将类型按照一定的规则转为字节存储，规则由SunnyTcsArgTraits 规定
	class SunnyTcsArg 
	{
	public:

		//从字节解析时无法通过类型指令cimp函数指针，所以不得已要有这个_cimpHash
// 		static bool _inited;
// 		static QHash<E_ARG_TYPE, cimp> _cimpHash;
// 		static bool initFuncion() { //初始化函数
// 			//_cimpHash.insert()
// 			return true;
// 		}

		//获取值元函数
		template<typename Arg_type>
		struct meta_getValue {
			static Arg_type meta_getValue_f(const QByteArray& bytes, bool& ok)
			{
				return SunnyTcsArgTraits<Arg_type>::fromBytes(bytes);
			}
		};

		//左值版本，允许传入比需要数更多的bytes，不会对bytes自动删除已分析部分
		static SunnyTcsArg fromBytes(const QByteArray& bytes, bool& ok) {
			SunnyTcsArg arg;
			qint32 count = 0;
			ok = arg.fromBytes(bytes, count);
			if (!ok) {
				arg.defaultSet();
				return arg;
			}
			return arg;
		}

		//传入右值的版本，每次分析成功，都会从右值中删除 已经分析的部分
		static SunnyTcsArg fromBytes(QByteArray&& bytes, bool& ok) {
			SunnyTcsArg arg;
			qint32 count = 0;
			ok = arg.fromBytes(bytes, count);
			if (!ok) {
				arg.defaultSet();
				return arg;
			}
			bytes.remove(0, count);
			return arg;
		}

		//get value
		template<typename Arg_type>
		static auto getValue(Arg_type&& exp, const QByteArray& bytes, bool& ok) ->decltype(SunnyTcsArgTraits<Arg_type>::fromBytes(_value, ok))
		{
			return SunnyTcsArgTraits<Arg_type>::fromBytes(bytes, ok);
		}


		//ctor
		SunnyTcsArg() :_value(), _size(ARG_HEAD_LENGTH), _type(ARG_UNDEFINED),_cf(nullptr)
		{}

		template<typename Arg_type>
		SunnyTcsArg(Arg_type&& val) //并没有对隐式转换添加限制
			:_value(SunnyTcsArgTraits<Arg_type>::toBytes(std::forward<Arg_type>(val))),//完美转发
			_size(SunnyTcsArgTraits<Arg_type>::size(val) + ARG_HEAD_LENGTH),
			_type(SunnyTcsArgTraits<Arg_type>::argType()),_cf(&SunnyTcsArgTraits<Arg_type>::constructInMemoryPointed)
		{}

		//copy ctor
		SunnyTcsArg(const SunnyTcsArg& arg) :_type(arg._type), _size(arg._size), _value(arg._value),_cf(arg._cf) {}

		//move ctor
		SunnyTcsArg(SunnyTcsArg&& arg) noexcept
			: _type(arg._type), _size(arg._size), _value(),_cf(arg._cf)
		{
			_value.swap(arg._value);
		}

		//dtor
		virtual ~SunnyTcsArg() {}

		//assignment
		template<typename T>
		SunnyTcsArg& operator=(T&& rhs) {
			_type = SunnyTcsArgTraits<T>::argType();
			_size = SunnyTcsArgTraits<T>::size(rhs) + ARG_HEAD_LENGTH;
			_value = SunnyTcsArgTraits<T>::toBytes(std::forward<T>(rhs));
			_cf = &SunnyTcsArgTraits<T>::constructInMemoryPointed;
			return *this;
		}

		//assignment
		SunnyTcsArg& operator=(const SunnyTcsArg& rhs) {
			_type = rhs._type;
			_size = rhs._size;
			_value = rhs._value;
			_cf = rhs._cf;
			return *this;
		}

		//move assignment
		SunnyTcsArg& operator=(SunnyTcsArg&& rhs) noexcept {
			_type = rhs._type;
			_size = rhs._size;
			_cf = rhs._cf;
			_value.swap(rhs._value);
			return *this;
		}

		//operator
		template<typename T>
		bool operator==(const T& rhs)const {
			bool ok1 = true;
			bool ret = true;
			switch (_type) {
			case ARG_CHAR:
				ret = getValue(char(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_BOOL:
				ret = getValue(bool(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT8:
				ret = getValue(qint8(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT16:
				ret = getValue(qint16(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT32:
				ret = getValue(qint32(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT64:
				ret = getValue(qint64(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT8:
				ret = getValue(quint8(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT16:
				ret = getValue(quint16(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT32:
				ret = getValue(quint32(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT64:
				ret = getValue(quint64(0), ok1) == rhs;
				Q_ASSERT(ok1);
				return ret;
			}
			return false;
		}


		bool operator==(const SunnyTcsArg& arg) const {
			return (arg._type == this->_type && arg._value == this->_value&&_cf == arg._cf);
		}


		bool operator==(const string_tcs& arg)const {//字符串需要特殊处理
			bool ok = true;
			ok &= (this->_type == ARG_QSTRING&& arg == meta_getValue<string_tcs>::meta_getValue_f(_value, ok)) ;
			return ok;
		}


		bool operator==(const byteArray_tcs& arg)const {//字符数组需要特殊处理
			if (this->_type == ARG_QBYTEARRAY&& arg == this->_value) {
				return true;
			}
			return false;
		}


		template<typename T>
		bool operator!=(T&& rhs) const {
			return !this->operator==(std::forward<T>(rhs));
		}


		template<typename T>
		bool operator>(const T& rhs) const {
			bool        ok1 = true;
			bool        ret = true;
			switch (_type) {
			case ARG_CHAR:
				ret = (meta_getValue<char_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_BOOL:
				ret = (meta_getValue<bool_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT8:
				ret = (meta_getValue<int8_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT16:
				ret = (meta_getValue<int16_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT32:
				ret = (meta_getValue<int32_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_INT64:
				ret = (meta_getValue<int64_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT8:
				ret = (meta_getValue<uint8_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT16:
				ret = (meta_getValue<uint16_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT32:
				ret = (meta_getValue<uint32_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			case ARG_UINT64:
				ret = (meta_getValue<uint64_tcs>::meta_getValue_f(_value, ok1) > rhs);
				Q_ASSERT(ok1);
				return ret;
			}
			return false;
		}


		template<>
		bool operator>(const SunnyTcsArg& arg)const {
			bool ok2 = false;
			bool ret = false;
			switch (arg._type){
			case ARG_CHAR:
				ret = this->operator>(meta_getValue<char_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_BOOL:
				ret = this->operator>(meta_getValue<bool_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_INT8:
				ret = this->operator>(meta_getValue<int8_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_INT16:
				ret = this->operator>(meta_getValue<int16_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_INT32:
				ret = this->operator>(meta_getValue<int32_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_INT64:
				ret = this->operator>(meta_getValue<int64_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_UINT8:
				ret = this->operator>(meta_getValue<uint8_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_UINT16:
				ret = this->operator>(meta_getValue<uint16_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_UINT32:
				ret = this->operator>(meta_getValue<uint32_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_UINT64:
				ret = this->operator>(meta_getValue<uint64_tcs>::meta_getValue_f(_value, ok2));
				Q_ASSERT(ok2);
				return ret;
			case ARG_QBYTEARRAY:
				return false;
			case ARG_QSTRING:
				return false;
			}
			return false;
		}

		template<typename T>
		bool operator>=(T&& arg)const {
			return !this->operator<(std::forward<T>(arg));
		}

		template<typename T>
		bool operator<(T&& arg)const {
			return !this->operator==(std::forward<T>(arg)) && !this->operator>(std::forward<T>(arg));
		}

		template<typename T>
		bool operator<=(T&& arg) const {
			return !this->operator>(std::forward<T>(arg));
		}

		//bytes
		bool fromBytes(const QByteArray& bytes, qint32 &parsedCount) {
			do {
				if (bytes.count() < ARG_HEAD_LENGTH) {
					break;
				}
				int typeVal = SunnyTcsBytesTransformer::fromByte<qint8>(bytes.mid(0, 1));
				E_ARG_TYPE_CHECK(typeVal);
				_type = static_cast<E_ARG_TYPE>(typeVal);
				_size = SunnyTcsBytesTransformer::fromByte<qint32>(bytes.mid(1, 4));
				if (_size > bytes.count()) {//_size是指整个arg的大小
					break;
				}
				_value = bytes.mid(ARG_HEAD_LENGTH, _size - ARG_HEAD_LENGTH);
				parsedCount = _size;
				return true;
			} while (0);
			parsedCount = 0;
			defaultSet();
			return false;
		}


		QByteArray toBytes()const
		{
			QByteArray ret;
			ret.append(SunnyTcsBytesTransformer::toBytes<qint8>(static_cast<qint8>(_type)));
			ret.append(SunnyTcsBytesTransformer::toBytes<qint32>(_size));
			ret.append(_value);
			return std::move(ret);
		}

		//json
		QJsonObject toJson()const {
			QJsonObject jobj;
			jobj[JSON_ARG_TYPE] = static_cast<qint32>(_type);
			jobj[JSON_ARG_SIZE] = static_cast<qint32>(_size);
			QJsonArray jarr;
			for (int i = 0; i < _value.count(); ++i) {
				jarr.append((qint32)(_value.at(i)));
			}
			jobj[JSON_ARG_PARAM] = jarr;
			return jobj;
		}


		bool fromJson(QJsonObject& jobj, QString& err) {
			_type = static_cast<E_ARG_TYPE>(jobj[JSON_ARG_TYPE].toInt());
			_size = jobj[JSON_ARG_SIZE].toInt();
			QJsonArray arr = jobj[JSON_ARG_PARAM].toArray();
			_value.clear();
			auto iter = arr.begin();
			while (iter != arr.end()) {
				_value.append(static_cast<char>(iter->toInt()));
				++iter;
			}
			if (_value.count() + ARG_HEAD_LENGTH != _size) {
				err = "size error";
				return false;
			}
			return true;
		}

		//getter
		inline qint32 getSize() const { return _size; }

		inline qint32 getArgSize()const { return _value.count(); }

		inline E_ARG_TYPE getType() const { return _type; }

		inline QByteArray getByteArray()const { return _value; }

		template<typename Arg_type>
		auto getValue(Arg_type&& exp, bool& ok) const  ->decltype(SunnyTcsArgTraits<Arg_type>::fromBytes(_value, ok))
		{
			return SunnyTcsArgTraits<Arg_type>::fromBytes(_value, ok);
		}

		QString toString() const {
			QString str("");
			bool ok = true;
			switch (_type)
			{
			case ARG_UNDEFINED:
				str += "undefined : none\n";
				return str;
			case ARG_CHAR:
				str += "char : ";
				str += _value.at(0);
				str += '\n';
				return str;
			case ARG_BOOL:
				str += "bool : ";
				str += meta_getValue<char_tcs>::meta_getValue_f(_value,ok) ? "true" : "false";
				return ok ? str : "ERROR BOOL";
			case ARG_MIXED:
				str += "mixed : mixed\n";
				return str;
			case ARG_INT8:
				str += "int8 : ";
				str += QString::number(meta_getValue<int8_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR int8";
			case ARG_INT16:
				str += "int16 : ";
				str += QString::number(meta_getValue<int16_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR int16";
			case ARG_INT32:
				str += "int32 : ";
				str += QString::number(meta_getValue<int32_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR int32";
			case ARG_INT64:
				str += "int64 : ";
				str += QString::number(meta_getValue<int64_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR int64";
			case ARG_UINT8:
				str += "uint8 : ";
				str += QString::number(meta_getValue<uint8_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR uint8";
			case ARG_UINT16:
				str += "uint16 : ";
				str += QString::number(meta_getValue<uint16_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR uint16";
			case ARG_UINT32:
				str += "uint32 : ";
				str += QString::number(meta_getValue<uint32_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR uint32";
			case ARG_UINT64:
				str += "uint64 : ";
				str += QString::number(meta_getValue<uint64_tcs>::meta_getValue_f(_value, ok));
				str += '\n';
				return  ok ? str : "ERROR uint64";
			case ARG_QBYTEARRAY:
				str += "bytearray : ";
				str += QString(_value);
				str += '\n';
				return str;
			case ARG_QSTRING:
				str += "string : ";
				str += meta_getValue<string_tcs>::meta_getValue_f(_value, ok);
				str += '\n';
				return ok ? str : "ERROR string";
			default:
				return "other | other\n";
			}
			return str;
		}

		//指定创建
		void constructInMem(void* target, std::size_t size) {
			Q_ASSERT(_cf);
			_cf(_value, target, size);
		}

	 private:
		void defaultSet() {
			_type = ARG_UNDEFINED;
			_size = 5;//这个size指的是 整个arg转化为bytes后 的大小
			_value.clear();
			_cf = nullptr;
		}

	protected:
		E_ARG_TYPE _type;
		qint32 _size;
		QByteArray _value;
		cimp _cf;
	};



}



