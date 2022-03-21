#pragma once

#include "SunnyTcsMapGeneral.hpp"
#include "SunnyTcsAction.h"



// vehicle nagative mode
#define VEHICLE_NAGA_RUBBON 0X01
#define VEHICLE_NAGA_INERTIA 0X02
#define VEHICLE_NAGA_LASER 0X04


//这是内核模型设计的接口文件
namespace basic {

	//车型识别code
	struct SunnyTcsAgvCode {
		//ctor
		SunnyTcsAgvCode(qint32 agvType =0, qint32 nagaMode=0, qint32 paramsCount=0,
			E_ARG_TYPE argType=ARG_UNDEFINED , E_CoordinateDimension dim = E_ONE_DIMENSION ,QString description = "")
			:_agvType(agvType), _nagaMode(nagaMode), _actionParamsCount(paramsCount), _actionParamsType(argType),_dim(dim),_description(description)
		{}
		//copy ctor
		SunnyTcsAgvCode(const SunnyTcsAgvCode&) = default;
		//dector
		virtual ~SunnyTcsAgvCode() {}
		//assignment
		SunnyTcsAgvCode& operator=(const SunnyTcsAgvCode&) = default;

		bool operator==(const SunnyTcsAgvCode& rhs)const  {
			return _agvType == rhs._agvType && _nagaMode == rhs._nagaMode && _actionParamsCount == rhs._actionParamsCount &&
				_actionParamsType == rhs._actionParamsType && _dim == rhs._dim && _description == rhs._description;
		}

		bool fromJson(QJsonObject& jobj) {
			_agvType = jobj[JSON_MAP_MODEL_VECODES_VALUE].toInt();
			_nagaMode = jobj[JSON_MAP_MODEL_VECODES_SPT_NAGA].toInt();
			_actionParamsCount = jobj[JSON_MAP_MODEL_VECODES_PARAMS_COUNT].toInt();
			_actionParamsType = static_cast<E_ARG_TYPE>(jobj[JSON_MAP_MODEL_VECODES_PARAMS_TYPE].toInt());
			return true;
		}

		QJsonObject toJson()const {
			QJsonObject jobj;
			jobj[JSON_MAP_MODEL_VECODES_VALUE] = _agvType;
			jobj[JSON_MAP_MODEL_VECODES_SPT_NAGA] = _nagaMode;
			jobj[JSON_MAP_MODEL_VECODES_PARAMS_COUNT] = _actionParamsCount;
			jobj[JSON_MAP_MODEL_VECODES_PARAMS_TYPE] = (qint32) _actionParamsType;
			return jobj;
		}

		qint32 _agvType;//车型识别号
		qint32 _nagaMode; //支持的导航方式 ,最多32种
		qint32 _actionParamsCount;//指令参数的数量
		E_ARG_TYPE _actionParamsType;//指令参数的类型
		E_CoordinateDimension _dim;  //初始维数，对广汽三菱车辆无效
		QString _description; //描述
	};

	

	class I_SunnyTcsElementData;
	//某个组的接口
	class I_SunnyTcsGroup {
	public:
		friend class I_SunnyTcsElementData;
	public:
		I_SunnyTcsGroup(qint32 id, QString name) :_id(id), _name(name) ,_members(){}
		virtual ~I_SunnyTcsGroup() {}

		qint32 getId()const { return _id; }
		QString getName()const { return _name; }
		const QHash<qint32, I_SunnyTcsElementData*>& getMembers()const { return _members; }

	protected:
		//以下是供I_SunnyTcsElementData内部调用的
		virtual void registerGroup(I_SunnyTcsElementData*) = 0;
		virtual void dropRegister(qint32 id) = 0;
		
	protected:
		qint32 _id;
		QString _name;
		QHash<qint32, I_SunnyTcsElementData*> _members;
	};




	//地图元素数据接口,接口设计尽量设计 接口纯虚函数就行，除非是显而易见的实现！
	class I_SunnyTcsElementData {
	public:
		friend class I_SunnyTcsGroup;
	public:
		//ctor
		explicit I_SunnyTcsElementData(qint32 id , I_SunnyTcsGroup* group = nullptr) :_id(id),_group(group) {
			if (_group) {
				_group->registerGroup(this);
			}
		}

		//dtor
		virtual ~I_SunnyTcsElementData() {
			if (_group) {
				_group->dropRegister(this->getElementId());
			}
		}

		//getter 
		inline qint32 getElementId() const { return _id; }

		I_SunnyTcsGroup* getGroup()const { return _group; }

		//setter
		void setElementId(qint32 id) { _id = id; }

		//重新设置组
		void registerNewGroup(I_SunnyTcsGroup* newGroup) {
			if (_group) {
				_group->dropRegister(this->getElementId());
			}
			if (newGroup) {
				newGroup->registerGroup(this);
			}
			_group = newGroup;
		}

		//interface		
		virtual SunnyTcsMapObject_tag getTag()const = 0;
		virtual SunnyTcsArg getAttribution(QString key,bool& ok)const = 0;//设计该接口是为了满足 非标项目垃圾客户的多样性需求
		virtual bool setAttribution(QString key, SunnyTcsArg arg) = 0;
		//定位接口，提供默认实现
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution)const { return QVector<SunnyTcsMapBlock>(); }
		virtual bool isInRange(SunnyTcsAgvCoordinate coor)const { return false; }
	protected:
		qint32 _id;
		I_SunnyTcsGroup* _group;
	};



	//这个是车辆的特化接口,使用读写锁保障线程安全
	class I_SunnyTcsAgvStat : public I_SunnyTcsElementData {
	public:
		//ctor
		I_SunnyTcsAgvStat(SunnyTcsAgvCode code, qint32 id)
			: I_SunnyTcsElementData(id), _code(code),
			_coor(code._dim, 0, 0, 0), _pos(),
			_status(EOutLine),_orderBinded(0),_lift(0),_error(0),_warning(0),_lock()
		{}
		//copy ctor
		I_SunnyTcsAgvStat(const I_SunnyTcsAgvStat&) = delete;
		//detor
		virtual ~I_SunnyTcsAgvStat(){}
		//operator=
		I_SunnyTcsAgvStat& operator=(const I_SunnyTcsAgvStat&) = delete;

		//getter
		inline  SunnyTcsAgvCode getAgvCode()const { std::shared_lock<std::shared_mutex> lk(_lock); return _code; }
		inline  SunnyTcsAgvCoordinate getAgvCurCoor()const { std::shared_lock<std::shared_mutex> lk(_lock); return _coor; }//坐标接口
		inline  SunnyTcsMapObject_tag getAgvCurPos()const { std::shared_lock<std::shared_mutex> lk(_lock); return _pos; }//位置接口
		inline  E_SunnyTcsVehicleStatus getAgvStatus()const { return _status; }//状态接口


		inline  qint32 getLift()const { return _lift; }//保留接口，需要的agv自己重写，也不要求必须实现
		inline  qint64 getError()const { std::shared_lock<std::shared_mutex> lk(_lock); return  _error; } //保留接口，需要的agv自己重写，也不要求必须实现
		inline  qint64 getWarning()const { std::shared_lock<std::shared_mutex> lk(_lock); return _warning; } //保留接口，需要的agv自己重写，也不要求必须实现
		
		//setter
		void setAgvCurCoor(SunnyTcsAgvCoordinate coor) { std::unique_lock<std::shared_mutex> lk(_lock); _coor = coor; }//设置坐标
		void setAgvCurPos(SunnyTcsMapObject_tag curPos) { std::unique_lock<std::shared_mutex> lk(_lock); _pos = curPos; }//设置位置
		void setAgvStatue(E_SunnyTcsVehicleStatus status) { _status = status; }//设置状态

		void setLift(qint32 lift) { _lift = lift; }
		void setError(qint64 error) { std::unique_lock<std::shared_mutex> lk(_lock); _error = error; }
		void setWarning(qint64 warning) { std::unique_lock<std::shared_mutex> lk(_lock); _warning = warning; }
		
		//interface
		virtual bool isOrderLocked(quint64* orderId = nullptr) {//订单锁定状态
			std::shared_lock<std::shared_mutex> lock(_lock);
			if (orderId) {
				*orderId = _orderBinded;
			}
			return _orderBinded != 0 ? true : false;
		}

		virtual bool bindOrderToAgv(quint64 orderId) { //将订单绑定到车
			std::unique_lock<std::shared_mutex> lk(_lock);
			_orderBinded = _orderBinded == 0 ? orderId : _orderBinded;
			return _orderBinded == orderId;
		}

		virtual SunnyTcsMapObject_tag getTag()const {
			std::shared_lock<std::shared_mutex> lock(_lock);
			return SunnyTcsMapObject_tag(Evehicle, _id);
		}

		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override= 0;//获取属性接口
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//设置属性接口

		virtual bool updateData(const QByteArray& data) = 0; //数据更新
		virtual bool updateData(QByteArray&& data) { return false; }//右值版本，不要求子类一定实现

	protected:
		SunnyTcsAgvCode _code;
		SunnyTcsAgvCoordinate _coor;
		SunnyTcsMapObject_tag _pos;
		E_SunnyTcsVehicleStatus _status;
		quint64 _orderBinded;
		qint32 _lift;
		qint64 _error;
		qint64 _warning;

		//读写锁
		mutable std::shared_mutex _lock;
	};


	//轴的方向
	enum E_SunnyTcsAxisDirection {
		Eright = 1,
		Eup = 2,
		Eleft = 3,
		Edown = 4
	};


	//坐标系接口
	class I_SunnyTcsCoorSys :public I_SunnyTcsElementData {
	public:
		//ctor
		explicit I_SunnyTcsCoorSys(qint32 id = 0) :I_SunnyTcsElementData(id),
			_rxy(E_TWO_DIMENSION, 0, 0, 0), _xpos(Eright), _ypos(Eup), _lock(){}
		//copy ctor
		I_SunnyTcsCoorSys(const I_SunnyTcsCoorSys& rhs) = delete;
		//dtor
		virtual ~I_SunnyTcsCoorSys() {}
		//operator=
		I_SunnyTcsCoorSys& operator=(const I_SunnyTcsCoorSys&) = delete;

		//getter
		inline SunnyTcsAgvCoordinate getRealityXy()const { std::shared_lock<std::shared_mutex> lk(_lock); return _rxy; }
		inline E_SunnyTcsAxisDirection getAxisDirectionX()const { return _xpos; }
		inline E_SunnyTcsAxisDirection getAxisDirectionY()const { return _ypos; }

		//X轴镜像
		void mirrorX() {
			std::unique_lock<std::shared_mutex> lk(_lock);
			_xpos = _xpos == Eright || _xpos == Eleft ? (_xpos == Eright ? Eleft : Eright) : (_xpos == Eup) ? Edown : Eup;
		}

		//Y轴镜像
		void mirrorY() {
			std::unique_lock<std::shared_mutex> lk(_lock);
			_ypos = _ypos == Eright || _ypos == Eleft ? (_ypos == Eright ? Eleft : Eright) : (_ypos == Eup) ? Edown : Eup; 
		}

		//坐标系旋转
		void rotate() {
			std::unique_lock<std::shared_mutex> lk(_lock);
			qint32 xVal = static_cast<qint32>(_xpos);
			qint32 yVal = static_cast<qint32>(_ypos);
			xVal = xVal + 1 > 4 ? 1 : xVal + 1;
			yVal = yVal + 1 > 4 ? 1 : yVal + 1;
			_xpos = static_cast<E_SunnyTcsAxisDirection>(xVal);
			_ypos = static_cast<E_SunnyTcsAxisDirection>(yVal);
		}

		//自身虚函数
		virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const = 0;
		virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene)const = 0;

		// 通过 I_SunnyTcsElementData 继承
		virtual SunnyTcsMapObject_tag getTag() const override {
			std::shared_lock<std::shared_mutex> lk(_lock);
			return SunnyTcsMapObject_tag(Ecoorsys, _id); 
		}
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override = 0;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;


	protected:
		const SunnyTcsAgvCoordinate _rxy;//现实坐标
		E_SunnyTcsAxisDirection _xpos;
		E_SunnyTcsAxisDirection _ypos;

		//锁
		mutable std::shared_mutex _lock;
	};


	//点的实时数据,线程安全
	class I_SunnyTcsVertex : public I_SunnyTcsElementData {
	public:
		//ctor
		explicit I_SunnyTcsVertex(qint32 id =0)
			:I_SunnyTcsElementData(id), _absPos(0),
			_rxy(E_TWO_DIMENSION, 0, 0, 0), _nagaMode(0),
			_lockOwner(0), _usedCount(0), _lock() {}
		//copy ctor
		I_SunnyTcsVertex(const I_SunnyTcsVertex&) = delete;
		//detor
		virtual ~I_SunnyTcsVertex() {}
		//operator=
		I_SunnyTcsVertex& operator=(const I_SunnyTcsVertex&) = delete;

		//getter
		inline qint32 getPointNaga()const { return _nagaMode; }//点的nagamode
		inline qint32 getPointAbsPos()const { return _absPos; }//点的绝对位置
		inline SunnyTcsAgvCoordinate getPointCoor()const { std::shared_lock<std::shared_mutex> lk(_lock);  return _rxy; }//点的坐标
		inline qint32 getUsedCount()const { return _usedCount; }//当前所有已规划路径对该点的占用情况
		bool isPointTrafficLocked(qint32* ve = nullptr)const {//交通管制情况
			std::shared_lock<std::shared_mutex> lk(_lock);
			if (ve) {
				*ve = _lockOwner;
			}
			return _lockOwner != 0 ? true : false;
		}

		//setter
		void setPointNaga(qint32 naga) { _nagaMode = naga; }
		void setPointAbsPos(qint32 abs) { _absPos = abs; }
		void setPointCoor(SunnyTcsAgvCoordinate rxy) { std::unique_lock<std::shared_mutex> lk(_lock); _rxy = rxy; }
		void setUsedCount(qint32 used) { _usedCount = used; }
		bool lockTraffic(qint32 ve){//交通管制上锁
			std::unique_lock<std::shared_mutex> lk(_lock);
			_lockOwner = _lockOwner == 0 ? ve : _lockOwner;
			return _lockOwner == ve;
		}

		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
			std::shared_lock<std::shared_mutex> lk(_lock);
			return SunnyTcsMapObject_tag(Epoint, _id);
		}
		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override = 0;//获取属性接口
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//设置属性接口

	protected:
		qint32 _absPos;//点的绝对位置
		SunnyTcsAgvCoordinate _rxy;//惯导点用二维,激光用二维，辅助点为空
		qint32 _nagaMode; //一个点也可以是 多种导航方式 ，0 辅助点 ，1 色带点，2 惯导点，4 激光点
		qint32 _lockOwner; //锁拥有者
		qint32 _usedCount; //现在已规划路径对点的占用数
		
		mutable std::shared_mutex _lock;
	};


	//边数据，线程安全
	class I_SunnyTcsEdge : public I_SunnyTcsElementData {
	public:
		//ctor
		explicit I_SunnyTcsEdge(qint32 id=0)
			:I_SunnyTcsElementData(id),_isSupportPositive(true),_isSupportNegative(false), _isScanAeraActived(false),
			_positiveSpeed(300),_negativeSpeed(300),
			_positiveScanAera(0),_negativeScanAera(0),_lockOwner(0),_lock(){}
		//copy ctor
		I_SunnyTcsEdge(const I_SunnyTcsEdge&) = delete;
		//detor
		virtual ~I_SunnyTcsEdge() {}
		//operator=
		I_SunnyTcsEdge& operator=(const I_SunnyTcsEdge&) = delete;

		//getter
		inline bool isSupportPositive() const { return _isSupportPositive; }
		inline bool isSupportNegative() const { return _isSupportNegative; }
		inline qint32 getPositiveSpeed()const { return _positiveSpeed; }//正向速度
		inline qint32 getNegativeSpeed()const { return _negativeSpeed; }//反向速度，如果有的话
		inline bool isScanAeraActived()const { return _isScanAeraActived; }//是否激活扫描区
		inline qint32 getPositiveScanAera()const {return _positiveScanAera;}//正向扫描区域
		inline qint32 getNegativeScanAera()const { return _negativeScanAera; }//反向扫描区域
		bool isPathTrafficLocked(qint32* ve = nullptr) {//交通管制情况
			std::shared_lock<std::shared_mutex> lk(_lock);
			if (ve) {
				*ve = _lockOwner;
			}
			return _lockOwner != 0 ? true : false;
		}
		
		//setter
		void setIsSupportPositive(bool is) { _isSupportPositive = is; }
		void setIsSupportNegative(bool is) { _isSupportNegative = is; }
		void setPositiveSpeed(qint32 sp) { _positiveSpeed = sp; }
		void setNegativeSpeed(qint32 sp) { _negativeSpeed = sp; }
		void setIfScanAeraActived(bool is) { _isScanAeraActived = is; }
		void setPositiveScanAera(qint32 aera) { _positiveScanAera = aera; }
		void setNegativeScanAera(qint32 aera) { _negativeScanAera = aera; }
		bool lockTraffic(qint32 ve) {//交通管制上锁
			std::unique_lock<std::shared_mutex> lk(_lock);
			_lockOwner = _lockOwner == 0 ? ve : _lockOwner;
			return _lockOwner == ve;
		}

		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
			return SunnyTcsMapObject_tag(Epath, _id);
		}
		virtual qint32 getFromPointId()const = 0;//起点id
		virtual qint32 getCtrlPointId()const = 0;//控制点id
		virtual qint32 getToPointId()const = 0;//目的地点id
		virtual qint32 getPathLen()const = 0;//路径长
		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override = 0;//获取属性接口
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//设置属性接口

	protected:
		bool _isSupportPositive;
		bool _isSupportNegative;
		bool _isScanAeraActived;
		qint32 _positiveSpeed;//本段的默认限速
		qint32 _negativeSpeed; //支持反向的化，反向速度
		qint32 _positiveScanAera;
		qint32 _negativeScanAera;
		qint32 _lockOwner; //锁拥有者

		mutable std::shared_mutex _lock;
	};



	//工位接口,线程安全
	class I_SunnyTcsLocation :public I_SunnyTcsElementData ,public QList<SunnyTcsAction> { //直接多继承Qlist,用着方便
	public:
		explicit I_SunnyTcsLocation(qint32 id) :I_SunnyTcsElementData(id),QList<SunnyTcsAction>(), _lock() {}

		I_SunnyTcsLocation(const I_SunnyTcsLocation&) = delete;

		virtual ~I_SunnyTcsLocation() {}

		I_SunnyTcsLocation& operator=(const I_SunnyTcsLocation&) = delete;

		virtual SunnyTcsMapObject_tag getTag()const {
			std::shared_lock<std::shared_mutex> lk(_lock);
			return SunnyTcsMapObject_tag(Elocation, _id);
		}

		virtual qint32 getLinkedPointId()const = 0;//相连的点

	protected:
		mutable std::shared_mutex _lock;

	};



	//外围系统的实时数据,也要进行线程安全处理
	class I_SunnyTcsUlsData : public I_SunnyTcsElementData {
	public:
		I_SunnyTcsUlsData(QString code, qint32 id) :I_SunnyTcsElementData(id) {}
		//外部设备型号
		inline QString getUlsCode()const { return _ulsCode; }
		
		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
			return SunnyTcsMapObject_tag(Euls, _id);
		}
		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override = 0;//获取属性接口
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//设置属性接口
	protected:
		QString _ulsCode;
	};



	class SunnyTcsSingleCondition;
	//实际数据的抽象类，包含基本的数据成员,
	//继承他，就必须实现 对单条件判断的函数，具备判断能力，作为条件判断的实际执行者
	//该接口还必须实现提供全面的 邻接关系 图 和 车辆分布图 ，供路径规划器 和 订单分配器 使用，这两项不必十分精准（非实时）
	//该接口需要提供 对部分地图元素 属性修改的能力，这是为了弥补上述API提供的数据并非实时的缺陷，列表如下
	/*{
		分配器，从数据中完成分析，对订单完成分配，需要实时 修改agv的订单绑定状态。所以订单绑定状态修改必须是实时的，访问允许不是实时
		路径规划器，从数据中完成分析，需要对 点，和路径的 锁进行实时锁定 与 解锁，所以路径锁的修改也必须是实时，访问允许不是实时
	}*/
	class I_SunnyTcsActualData { 
	public:
		//以下是已经决定好的标准接口
		//模型是可以变化的，有各个项目的外接设备等，所有我们将执行判断条件的对象 指定为模型，而不是条件本身
		virtual bool judgeSingleCondition(const SunnyTcsSingleCondition& conditon) = 0;
		//agv状态表
		virtual void agvStats(QHash<qint32, I_SunnyTcsAgvStat*>& ref) = 0;
		//点表
		virtual void points(QHash<qint32, I_SunnyTcsVertex*>& ref) = 0;
		//路径表
		virtual void paths(QHash<qint32, I_SunnyTcsEdge*>& ref) = 0;
		//外设表
		virtual void uls(QHash<qint32, I_SunnyTcsUlsData*>& ref) = 0;


		//一次性得到 froms表
		virtual void froms(QHash<qint32, QList<qint32>>& ref) {
			QHash<qint32, I_SunnyTcsEdge*> phs;
			ref.clear();
			this->paths(phs);
			for (auto ptr : phs) {
				if (!ref.keys().contains(ptr->getElementId())) {
					ref.insert(ptr->getElementId(), QList<qint32>());
				}
				ref[ptr->getElementId()].append(ptr->getFromPointId());
			}
		}


		//一次性得到 tos表	
		virtual void tos(QHash<qint32, QList<qint32>>& ref) {
			QHash<qint32, I_SunnyTcsEdge*> phs;
			ref.clear();
			this->paths(phs);
			for (auto ptr : phs) {
				if (!ref.keys().contains(ptr->getElementId())) {
					ref.insert(ptr->getElementId(), QList<qint32>());
				}
				ref[ptr->getElementId()].append(ptr->getToPointId());
			}
		}

		virtual I_SunnyTcsElementData* getElement(E_SunnyTcsMapObject_type type, qint32 id) {
			return nullptr;
		}

		//得到某agv当前的状态	
		virtual I_SunnyTcsAgvStat* getAgvStat(qint32 id, bool& ok) {
			QHash<qint32, I_SunnyTcsAgvStat*> agvs;
			this->agvStats(agvs);
			return agvs.keys().contains(id) ? agvs[id] : nullptr;
		}

		//根据from 和 to 找出合适的路径
		virtual I_SunnyTcsEdge* getEdgeByFromAndTo(qint32 from, qint32 to, bool& ok) {
			QHash<qint32, I_SunnyTcsEdge*> phs;
			this->paths(phs);
			for (auto ptr : phs) {
				if (ptr->getFromPointId() == from && ptr->getToPointId() == to) {
					return ptr;
				}
			}
			return nullptr;
		}

		//根据id获取path
		virtual I_SunnyTcsEdge* getEdgeById(qint32 id, bool& ok) {
			QHash<qint32, I_SunnyTcsEdge*> phs;
			this->paths(phs);
			return phs.keys().contains(id) ? phs[id] : nullptr;
		}

		//根据id,得到vertex
		virtual I_SunnyTcsVertex* getVertexById(qint32 id, bool& ok){
			QHash<qint32, I_SunnyTcsVertex*> pts;
			this->points(pts);
			return pts.keys().contains(id) ? pts[id] : nullptr;
		}


		//根据id,获取外设
		virtual I_SunnyTcsUlsData* getUlsById(qint32 id, bool& ok) {
			QHash<qint32, I_SunnyTcsUlsData*> ulss;
			this->uls(ulss);
			return ulss.keys().contains(id) ? ulss[id] : nullptr;
		}

	};



	//group接口的实现
	class SunnyTcsItemGroup :public I_SunnyTcsGroup {
	public:
		SunnyTcsItemGroup(qint32 id,QString name):I_SunnyTcsGroup(id,name){}
		virtual ~SunnyTcsItemGroup(){}

		// 通过 I_SunnyTcsGroup 继承
		virtual void registerGroup(I_SunnyTcsElementData * mem) override {
			_members.insert(mem->getElementId(), mem);
		}

		virtual void dropRegister(qint32 id) override {
			if (_members.contains(id)) {
				_members.remove(id);
			}
		}

	};



}
	



