#pragma once
#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsLibGeneral.hpp"
#include "SunnyTcsGeneralArg.hpp"
#include "SunnyTcsFuncGeneral.hpp"


#define ORIENTATION_INACCURACY 100.0

namespace basic {

	//地图元素类型
	enum E_SunnyTcsMapObject_type {
		Enotype = 0,
		Ecoorsys = 1,
		Epoint = 2,
		Epath = 3,
		Elocation = 4,
		Evehicle = 5,
		Euls=6
	};


	//车辆状态
	enum E_SunnyTcsVehicleStatus {
		EOutLine = 1,//下线
		EUnconnected = 2,//断连
		EConnected =3,//已连接
		Eworking = 4//工作中
	};


	//每个元素独一无二的标识符，由类型和id组成
	struct SunnyTcsMapObject_tag {
		//ctor
		SunnyTcsMapObject_tag() :_eletype(Enotype), _id(0) {}
		SunnyTcsMapObject_tag(E_SunnyTcsMapObject_type type, qint32 id) :_eletype(type), _id(id) {}
		SunnyTcsMapObject_tag(const SunnyTcsMapObject_tag& rhs) = default;
		SunnyTcsMapObject_tag& operator=(const SunnyTcsMapObject_tag&) = default;
		virtual ~SunnyTcsMapObject_tag() {}

		//opetator
		bool operator==(const SunnyTcsMapObject_tag& rhs)const {
			return this->_eletype == rhs._eletype && this->_id == rhs._id;
		}

		bool operator!=(const SunnyTcsMapObject_tag& rhs)const {
			return !this->operator==(rhs);
		}

		bool isNull()const {
			return _eletype == Enotype;
		}

		QString toString()const {
			QString str;
			switch (_eletype)
			{
			case basic::Enotype:
				str += "noType_";
				break;
			case basic::Ecoorsys:
				str += "coorSys_";
				break;
			case basic::Epoint:
				str += "point_";
				break;
			case basic::Epath:
				str += "path_";
				break;
			case basic::Elocation:
				str += "location_";
				break;
			case basic::Evehicle:
				str += "vehicle_";
				break;
			}
			str += QString::number(_id);
			return str;
		}

		//json
		bool fromJson(QJsonObject& jobj) {
			if (!jobj.contains(JSON_OBJECT_TAG_TYPE) || !jobj.contains(JSON_OBJECT_TAG_ID))return false;
			_eletype = static_cast<E_SunnyTcsMapObject_type>(jobj[JSON_OBJECT_TAG_TYPE].toInt());
			_id = jobj[JSON_OBJECT_TAG_ID].toInt();
			return true;
		}

		QJsonObject toJson()const {
			QJsonObject jobj;
			jobj[JSON_OBJECT_TAG_TYPE] = static_cast<qint32>(_eletype);
			jobj[JSON_OBJECT_TAG_ID] = static_cast<qint32>(_id);
			return jobj;
		}

		E_SunnyTcsMapObject_type _eletype;
		qint32 _id;
	};


	//坐标维度，最高三维
	enum E_CoordinateDimension
	{
		E_ONE_DIMENSION = 1,
		E_TWO_DIMENSION = 2,
		E_THREE_DIMENSION = 3
	};
	

	//坐标方案2
	template<typename T>
	struct SunnyTcsCoordinate {

		//ctor
		SunnyTcsCoordinate(E_CoordinateDimension dim= E_ONE_DIMENSION
			, T x = T(), T y = T(), T z = T())
			:_dim(dim), _x(x), _y(y), _z(z)
		{}

		SunnyTcsCoordinate(const SunnyTcsCoordinate& rhs)
			:_dim(rhs._dim),_x(rhs._x),_y(rhs._y),_z(rhs._z)
		{}

		SunnyTcsCoordinate& operator=(const SunnyTcsCoordinate& rhs) {
			_dim = rhs._dim;
			_x = rhs._x;
			_y = rhs._y;
			_z = rhs._z;
			return *this;
		}
		
		virtual ~SunnyTcsCoordinate() {}

		//operator
		bool operator==(const SunnyTcsCoordinate& rhs)const  {
			return _dim == rhs._dim && _x == rhs._x && _y == rhs._y && _z == rhs._z;
		}

		E_CoordinateDimension _dim;
		T _x;
		T _y;
		T _z;
	};



	//表示区间的类,
	template<typename T>
	class SunnyTcsGeneralRange {
	public:
		//默认为闭区间
		SunnyTcsGeneralRange() :_start(), _end(), _isStartContained(true), _isEndContained(true) {}

		SunnyTcsGeneralRange(T start, T end, bool leftContained = true, bool rightContained = true)
			:_start(start), _end(end), _isStartContained(leftContained), _isEndContained(rightContained) {
		}
		SunnyTcsGeneralRange(const SunnyTcsGeneralRange&) = default;
		SunnyTcsGeneralRange& operator=(const SunnyTcsGeneralRange&) = default;
		virtual ~SunnyTcsGeneralRange() = default;

		//是否在区间内,要考虑到前大后小的区间的情况，不能简单的认为start就一定是小的
		//如果要兼容 二维坐标系，就不得不考虑，二阶贝塞尔 曲线情况下的区间判断，这有点难度，至少需要提供辅助点的坐标
		bool isInRange(T val)const {
			//特殊情况
			if ((_isStartContained && val == _start) && (_isEndContained && val == _end))return true;
			//计算到两点的距离
			T distanceToStart = qAbs(val - _start);
			T distanceToEnd = qAbs(val - _end);
			return distanceToEnd + distanceToStart == qAbs(_end - _start) ? true : false;
		}

		inline T getStart()const {
			return _start;
		}

		inline T getEnd()const {
			return _end;
		}

		void setStart(T start) {
			_start = start;
		}

		void setEnd(T end) {
			_end = end;
		}

		inline bool isStartContained()const {
			return _isStartContained;
		}

		inline bool isEndContained()const {
			return _isEndContained;
		}

		void setStartContained(bool is) {
			_isStartContained = is;
		}

		void setEndContained(bool is) {
			_isEndContained = is;
		}

	protected:
		bool _isStartContained; //是否为左闭区间
		bool _isEndContained; //是否为右闭区间
		T _start;
		T _end;
	};



	//32位暂时够用了，不够就改成64
	typedef SunnyTcsCoordinate<qreal>  SunnyTcsAgvCoordinate_real;
	typedef SunnyTcsCoordinate<qint32> SunnyTcsAgvCoordinate;

	//懒得去特化了
	static QJsonObject toJson_coordinate_int32(const SunnyTcsAgvCoordinate& rhs){
		QJsonObject jobj;
		jobj[JSON_COOR_INT32_X] = rhs._x;
		jobj[JSON_COOR_INT32_Y] = rhs._y;
		jobj[JSON_COOR_INT32_Z] = rhs._z;
		jobj[JSON_COOR_INT32_DIM] = static_cast<qint32>(rhs._dim);
		return jobj;
	}

	static SunnyTcsAgvCoordinate fromJson_coordinate_int32(QJsonObject& jobj,bool& ok) {
		if (!jobj.contains(JSON_COOR_INT32_X) || !jobj.contains(JSON_COOR_INT32_Y) ||
			!jobj.contains(JSON_COOR_INT32_Z) || !jobj.contains(JSON_COOR_INT32_DIM)) {
			ok = false;
			return SunnyTcsAgvCoordinate();
		}
		SunnyTcsAgvCoordinate coor;
		coor._x = jobj[JSON_COOR_INT32_X].toInt();
		coor._y = jobj[JSON_COOR_INT32_Y].toInt();
		coor._z = jobj[JSON_COOR_INT32_Z].toInt();
		coor._dim = static_cast<E_CoordinateDimension>(jobj[JSON_COOR_INT32_DIM].toInt());
		return coor;
	}


	//坐标特化区间
	template<>
	class SunnyTcsGeneralRange<SunnyTcsAgvCoordinate> {
	public:
		//默认为闭区间
		explicit SunnyTcsGeneralRange(E_CoordinateDimension dim = E_ONE_DIMENSION) :_start(dim), _end(dim), _isStartContained(true), _isEndContained(true) {}

		SunnyTcsGeneralRange(E_CoordinateDimension dim, bool startContained, bool endContained, qint32 startx, qint32 endx,
			qint32 starty = 0, qint32 endy = 0, qint32 startz = 0, qint32 endz = 0)
			:_start(dim, startx, starty, startz), _end(dim, endx, endy, endz),
			_isStartContained(startContained), _isEndContained(endContained),
			_isArch(false), _ctrl()
		{}

		SunnyTcsGeneralRange(SunnyTcsAgvCoordinate start, SunnyTcsAgvCoordinate end)
			:_start(start),_end(end),
			_isStartContained(true),_isEndContained(true),
			_isArch(false),_ctrl()
		{
			Q_ASSERT(start._dim == end._dim);
		}

		SunnyTcsGeneralRange(const SunnyTcsGeneralRange& rhs) 
			:_start(rhs._start),_end(rhs._end),_isStartContained(rhs._isStartContained),
			_isEndContained(rhs._isEndContained),_isArch(rhs._isArch),_ctrl(rhs._ctrl)
		{}

		SunnyTcsGeneralRange& operator=(const SunnyTcsGeneralRange& rhs) {
			_start = (rhs._start);
			_end=(rhs._end);
			_isStartContained=(rhs._isStartContained);
			_isEndContained=(rhs._isEndContained);
			_isArch = rhs._isArch;
			_ctrl = rhs._ctrl;
			return *this;
		}

		virtual ~SunnyTcsGeneralRange(){

		}

		bool isArch()const {
			return _isArch;
		}

		void setArch(bool is) {
			_isArch = is;
		}

		void setArchPoint(SunnyTcsAgvCoordinate ctrl) {
			_ctrl = ctrl;
		}

		//是否在区间内,要考虑到前大后小的区间的情况，不能简单的认为start就一定是小的
		//如果要兼容 二维坐标系，就不得不考虑，二阶贝塞尔 曲线情况下的区间判断，这有点难度，至少需要提供辅助点的坐标
		bool isInRange(SunnyTcsAgvCoordinate val)const {
			if (val._dim != _start._dim)return false;

			if (_start._dim == E_ONE_DIMENSION) {//一维坐标
				qint32 start = _start._x;
				qint32 end = _end._x;
				qint32 curr = val._x;
				if ((_isStartContained && curr==start)||(_isEndContained && curr==end))return true;
				if ((curr > start && curr < end) || (curr > end && curr < start))return true;
				return false;
			}
			else if (_start._dim == E_TWO_DIMENSION) {//二维坐标
				if (_isArch) {//曲线
					qreal p1_rx = static_cast<qreal>(_start._x);
					qreal p1_ry = static_cast<qreal>(_start._y);
					qreal p3_rx = static_cast<qreal>(_end._x);
					qreal p3_ry = static_cast<qreal>(_end._y);
 					qreal p2_rx = static_cast<qreal>(_ctrl._x);
					qreal p2_ry = static_cast<qreal>(_ctrl._y);
 					qreal rx = static_cast<qreal>(val._x);
 					qreal ry = static_cast<qreal>(val._y);

 					qreal ax = p1_rx - 2.0 * p2_rx + p3_rx;
 					qreal bx = -2.0 * p1_rx + 2.0 * p2_rx;
 					qreal cx = p1_rx - rx;

 					qreal ay = p1_ry - 2.0 * p2_ry + p3_ry;
 					qreal by = -2.0 * p1_ry + 2.0 * p2_ry;
 					qreal cy = p1_ry - ry;
 
					if (ax == 0 || ay==0) {
						return false;
					}

 					QList<qreal> _ratios;
 					QList<SunnyTcsAgvCoordinate_real> _coors;
 
 					//从x中解析出两个坐标
 					_ratios << ((-bx + qSqrt(qPow(bx, 2.0) - 4.0 * ax*cx)) / (2.0 * ax));
 					_ratios << ((-bx - qSqrt(qPow(bx, 2.0) - 4.0 * ax*cx)) / (2.0 * ax));
 
 					//从y中解析出两个坐标
 					_ratios << ((-by + qSqrt(qPow(by, 2.0) - 4.0 * ay*cy)) / (2.0 * ay));
 					_ratios << ((-by - qSqrt(qPow(by, 2.0) - 4.0 * ay*cy)) / (2.0 * ay));
 
					for (int i = 0; i < 4; ++i) {
						qreal t = _ratios[i];
						qreal tx = 0.0, ty = 0.0;
						if (t >= 0.0 && t <= 1.0 ) {
							tx = (1.0 - t)*(1.0 - t)*p1_rx + 2.0*t*(1.0 - t)*p2_rx + t*t*p3_rx;
							ty = (1.0 - t)*(1.0 - t)*p1_ry + 2.0*t*(1.0 - t)*p2_ry + t*t*p3_ry;
							_coors.append(SunnyTcsAgvCoordinate_real(E_TWO_DIMENSION,tx, ty));
						}
					}
					auto iter = _coors.begin();
					
					while (iter != _coors.end()) {	
						
						if (directLineLength(rx, ry, iter->_x, iter->_y) <= ORIENTATION_INACCURACY) {
							return true;
						}

						++iter;
					}
					return false;
				}else {//直线
					qreal startx = static_cast<qreal>(_start._x);
					qreal starty = static_cast<qreal>(_start._y);
					qreal endx = static_cast<qreal>(_end._x);
					qreal endy = static_cast<qreal>(_end._y);
					qreal currx = static_cast<qreal>(val._x);
					qreal curry = static_cast<qreal>(val._y);
					return (pointToLineDistance(currx, curry, startx, starty, endx, endy) < ORIENTATION_INACCURACY) ? true : false;
				}
			}
			else if (_start._dim == E_THREE_DIMENSION) {//三维坐标，不处理
				return false;
			}
			return false;
		}

		inline E_CoordinateDimension getDimension() { return _start._dim; }

		SunnyTcsAgvCoordinate getStart()const {
			return _start;
		}

		SunnyTcsAgvCoordinate getEnd()const {
			return _end;
		}

		void setStart(qint32 x,qint32 y=0) {
			_start._x = x;
			_start._y = y;
		}

		void sedEnd(qint32 x, qint32 y=0) {
			_end._x = x;
			_end._y = y;
		}

		void setCtrl(qint32 x, qint32 y = 0) {
			_ctrl._x = x;
			_ctrl._y = y;
		}

		bool isStartContained()const {
			return _isStartContained;
		}

		bool isEndContained()const {
			return _isEndContained;
		}

		void setStartContained(bool is) {
			_isStartContained = is;
		}

		void setEndContained(bool is) {
			_isEndContained = is;
		}

		inline SunnyTcsMapObject_tag getObjectBinded()const { return _tag; }

		void bindToMapObject(SunnyTcsMapObject_tag tag) {
			_tag = tag;
		}

		QString toString()const {
			QString str( "%1 %2 -%3-> %4 %5 : %6" );

			QString start;
			if (_start._dim != E_ONE_DIMENSION) {
				start = QString("( %1 , %2 )").arg(QString::number(_start._x)).arg(QString::number(_start._y));
			}
			else {
				start = QString("( %1 )").arg(QString::number(_start._x));
			}

			QString ctrl;
			if (_ctrl._dim != E_ONE_DIMENSION && _isArch) {
				ctrl = QString("( %1 , %2 )").arg(QString::number(_ctrl._x)).arg(QString::number(_ctrl._y));
			}
			else if(_isArch) {
				ctrl = QString("( %1 )").arg(QString::number(_ctrl._x));
			}


			QString end;
			if (_end._dim != E_ONE_DIMENSION) {
				end = QString("( %1 , %2 )").arg(QString::number(_end._x)).arg(QString::number(_end._y));
			}
			else {
				end = QString("( %1 )").arg(QString::number(_end._x));
			}

			return str.arg(_isStartContained ? QString("[") : QString("("))
				.arg(start).arg(ctrl).arg(end).arg(_isEndContained ? QString("]") : QString(")")).arg(_tag.toString());
		}


		//json
		bool fromJson(QJsonObject& jobj) {
			bool ok = true;
			_start = fromJson_coordinate_int32(jobj[JSON_RANGE_COOR_INT32_START].toObject(),ok);
			_end = fromJson_coordinate_int32(jobj[JSON_RANGE_COOR_INT32_END].toObject(), ok);
			_ctrl = fromJson_coordinate_int32(jobj[JSON_RANGE_COOR_INT32_CTRL].toObject(), ok);
			_isArch = jobj[JSON_RANGE_COOR_INT32_ISARCH].toBool();
			_isStartContained = jobj[JSON_RANGE_COOR_INT32_START_CONTAINED].toBool();
			_isEndContained = jobj[JSON_RANGE_COOR_INT32_END_CONTAINED].toBool();
			if (!ok)return false;
		}

		QJsonObject toJson()const{
			QJsonObject jobj;
			jobj[JSON_RANGE_COOR_INT32_START] = toJson_coordinate_int32(_start);
			jobj[JSON_RANGE_COOR_INT32_END] = toJson_coordinate_int32(_end);
			jobj[JSON_RANGE_COOR_INT32_CTRL] = toJson_coordinate_int32(_ctrl);
			jobj[JSON_RANGE_COOR_INT32_ISARCH] = _isArch;
			jobj[JSON_RANGE_COOR_INT32_START_CONTAINED] = _isStartContained;
			jobj[JSON_RANGE_COOR_INT32_END_CONTAINED] = _isEndContained;
			return jobj;
		}

	protected:
		bool _isStartContained; //是否为左闭区间
		bool _isEndContained; //是否为右闭区间
		SunnyTcsAgvCoordinate _start;
		SunnyTcsAgvCoordinate _end;
		SunnyTcsMapObject_tag _tag;

		//二维弯道辅助点
		bool _isArch;
		SunnyTcsAgvCoordinate _ctrl;
};

	using SunnyTcsAgvRange = SunnyTcsGeneralRange<SunnyTcsAgvCoordinate> ;


	//地图像素点,两种定位方法之一
	struct SunnyTcsMapBlock {
		SunnyTcsMapBlock() :_xblock(-1), _yblock(-1) {}
		SunnyTcsMapBlock(qint32 xb, qint32 yb) :_xblock(xb), _yblock(yb) {}
		SunnyTcsMapBlock(const SunnyTcsMapBlock&) = default;
		SunnyTcsMapBlock& operator=(const SunnyTcsMapBlock&) = default;
		virtual ~SunnyTcsMapBlock() {}

		bool operator==(const SunnyTcsMapBlock& rhs)const { return _xblock == rhs._xblock && _yblock == rhs._yblock; }

		bool operator!=(const SunnyTcsMapBlock& rhs)const { return !this->operator==(rhs); }

		bool operator<(const SunnyTcsMapBlock& rhs)const {
			if ((rhs._yblock == _yblock && rhs._xblock > _xblock) || (rhs._yblock > _yblock)) {
				return true;
			}
			return false;
		}

		bool operator>(const SunnyTcsMapBlock& rhs)const {
			return !this->operator ==(rhs) && !this->operator <(rhs);
		}

		bool operator<=(const SunnyTcsMapBlock& rhs)const {
			return !this->operator>(rhs);
		}

		bool operator>=(const SunnyTcsMapBlock& rhs)const {
			return !this->operator<(rhs);
		}

		qint32 _xblock;
		qint32 _yblock;
	};
	

}