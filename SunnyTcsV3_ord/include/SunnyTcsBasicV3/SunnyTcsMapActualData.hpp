#pragma once

#include "SunnyTcsMapGeneral.hpp"
#include "SunnyTcsAction.h"



//这是内核模型设计的接口文件
namespace basic {

	//车型识别code
	struct SunnyTcsAgvCode {

		SunnyTcsAgvCode(qint32 agvType =0, qint32 nagaMode=0, qint32 paramsCount=0, E_ARG_TYPE argType=ARG_UNDEFINED , E_CoordinateDimension dim = E_ONE_DIMENSION)
			:_agvType(agvType), _nagaMode(nagaMode), _actionParamsCount(paramsCount), _actionParamsType(argType),_dim(dim)
		{}
		SunnyTcsAgvCode(const SunnyTcsAgvCode&) = default;
		virtual ~SunnyTcsAgvCode() {}
		SunnyTcsAgvCode& operator=(const SunnyTcsAgvCode&) = default;

		bool operator==(const SunnyTcsAgvCode& rhs)const  {
			return _agvType == rhs._agvType && _nagaMode == rhs._nagaMode && _actionParamsCount == rhs._actionParamsCount &&
				_actionParamsType == rhs._actionParamsType && _dim == rhs._dim;
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
		E_CoordinateDimension _dim;
	};

	
	//地图元素数据接口,接口设计尽量设计 接口纯虚函数就行，除非是显而易见的实现！
	class I_SunnyTcsElementData {
	public:
		//ctor
		explicit I_SunnyTcsElementData(qint32 id) :_id(id) {}
		//dtor
		virtual ~I_SunnyTcsElementData() {}
		//getter 
		inline qint32 getElementId() const { return _id; }
		//setter
		void setElementId(qint32 id) { _id = id; }

		//interface
		//锁
		virtual void lock() {} //设计这三个锁接口，是为了应付不可避免的多线程访问问题，多线程的实现交由开发者自己完成
		virtual void unlock() {}
		virtual bool tryLock() { return false; }
		virtual std::shared_mutex* getSharedLock() { return nullptr; }//获取读写锁

		
		virtual SunnyTcsMapObject_tag getTag()const = 0;
		virtual SunnyTcsArg getAttribution(QString key,bool& ok)const = 0;//设计该接口是为了满足 非标项目垃圾客户的多样性需求
		virtual bool setAttribution(QString key, SunnyTcsArg arg) = 0;
		//定位接口，提供默认实现
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution)const { return QVector<SunnyTcsMapBlock>(); }
		virtual bool isInRange(SunnyTcsAgvCoordinate coor)const { return false; }
	protected:
		qint32 _id;
	};



	//这个是车辆的特化接口
	class I_SunnyTcsAgvStat : public I_SunnyTcsElementData {
	public:
		I_SunnyTcsAgvStat(SunnyTcsAgvCode code, qint32 id)
			: I_SunnyTcsElementData(id), _code(code),
			_coor(code._dim, 0, 0, 0), _pos(),
			_status(EUnconnected),_orderBinded(0)
		{}

		I_SunnyTcsAgvStat(const I_SunnyTcsAgvStat&) = delete;

		virtual ~I_SunnyTcsAgvStat(){}

		I_SunnyTcsAgvStat& operator=(const I_SunnyTcsAgvStat&) = delete;

		//getter
		inline SunnyTcsAgvCode getAgvCode()const { return _code; }
		inline SunnyTcsAgvCoordinate getAgvCurCoor()const { return _coor; }//坐标接口
		inline SunnyTcsMapObject_tag getAgvCurPos()const { return _pos; }//位置接口
		inline E_SunnyTcsVehicleStatus getAgvStatus()const { return _status; }//状态接口
		
		//setter
		void setAgvCurCoor(SunnyTcsAgvCoordinate coor) { _coor = coor; }//设置坐标
		void setAgvCurPos(SunnyTcsMapObject_tag curPos) { _pos = curPos; }//设置位置
		void setAgvStatue(E_SunnyTcsVehicleStatus status) { _status = status; }//设置状态
		
		//interface
		virtual bool isOrderLocked(quint64* orderId = nullptr) {//订单锁定状态
			if (orderId) {
				*orderId = _orderBinded;
			}
			return _orderBinded != 0 ? true : false;
		}

		virtual bool bindOrderToAgv(quint64 orderId) { //将订单绑定到车
			_orderBinded = _orderBinded == 0 ? orderId : _orderBinded;
			return _orderBinded == orderId;
		}

		virtual SunnyTcsMapObject_tag getTag()const {
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
			_rxy(E_TWO_DIMENSION, 0, 0, 0), _xpos(Eright), _ypos(Eup)
		{}
		//copy ctor
		I_SunnyTcsCoorSys(const I_SunnyTcsCoorSys& rhs) = delete;
		//dtor
		virtual ~I_SunnyTcsCoorSys() {}
		//assignment
		I_SunnyTcsCoorSys& operator=(const I_SunnyTcsCoorSys&) = delete;

		//getter
		inline SunnyTcsAgvCoordinate getRealityXy()const { return _rxy; }
		inline E_SunnyTcsAxisDirection getAxisDirectionX()const { return _xpos; }
		inline E_SunnyTcsAxisDirection getAxisDirectionY()const { return _ypos; }

		//X轴镜像
		void mirrorX() { _xpos = _xpos == Eright || _xpos == Eleft ? (_xpos == Eright ? Eleft : Eright) : (_xpos == Eup) ? Edown : Eup; }

		//Y轴镜像
		void mirrorY() { _ypos = _ypos == Eright || _ypos == Eleft ? (_ypos == Eright ? Eleft : Eright) : (_ypos == Eup) ? Edown : Eup; }

		//坐标系旋转
		void rotate() {
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
		virtual SunnyTcsMapObject_tag getTag() const override { return SunnyTcsMapObject_tag(Ecoorsys, _id); }
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override = 0;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;


	protected:
		const SunnyTcsAgvCoordinate _rxy;//现实坐标
		E_SunnyTcsAxisDirection _xpos;
		E_SunnyTcsAxisDirection _ypos;
	};


	//点的实时数据
	class I_SunnyTcsVertex : public I_SunnyTcsElementData {
	public:
		explicit I_SunnyTcsVertex(qint32 id =0)
			:I_SunnyTcsElementData(id), _absPos(0),
			_rxy(E_TWO_DIMENSION, 0, 0, 0), _nagaMode(0),
			_lockOwner(0), _usedCount(0) {}

		I_SunnyTcsVertex(const I_SunnyTcsVertex&) = delete;

		virtual ~I_SunnyTcsVertex() {}

		I_SunnyTcsVertex& operator=(const I_SunnyTcsVertex&) = delete;

		//getter
		inline qint32 getPointNaga()const { return _nagaMode; }//点的nagamode
		inline qint32 getPointAbsPos()const { return _absPos; }//点的绝对位置
		inline SunnyTcsAgvCoordinate getPointCoor()const { return _rxy; }//点的坐标
		inline qint32 getUsedCount()const { return _usedCount; }//当前所有已规划路径对该点的占用情况
		bool isPointTrafficLocked(qint32* ve = nullptr)const {//交通管制情况
			if (ve) {
				*ve = _lockOwner;
			}
			return _lockOwner != 0 ? true : false;
		}

		//setter
		void setPointNaga(qint32 naga) { _nagaMode = naga; }
		void setPointAbsPos(qint32 abs) { _absPos = abs; }
		void setPointCoor(SunnyTcsAgvCoordinate rxy) { _rxy = rxy; }
		void setUsedCount(qint32 used) { _usedCount = used; }
		bool lockTraffic(qint32 ve){//交通管制上锁
			_lockOwner = _lockOwner == 0 ? ve : _lockOwner;
			return _lockOwner == ve;
		}

		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
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
		
	};


	//边数据
	class I_SunnyTcsEdge : public I_SunnyTcsElementData {
	public:
		explicit I_SunnyTcsEdge(qint32 id=0)
			:I_SunnyTcsElementData(id),_isDoubleDirection(true), _isScanAeraActived(false),
			_positiveSpeed(300),_negativeSpeed(300),
			_positiveScanAera(0),_negativeScanAera(0),_lockOwner(0){}

		I_SunnyTcsEdge(const I_SunnyTcsEdge&) = delete;

		virtual ~I_SunnyTcsEdge() {}

		I_SunnyTcsEdge& operator=(const I_SunnyTcsEdge&) = delete;

		//getter
		inline bool isDoubleDirection()const { return _isDoubleDirection; }//是否双向支持
		inline qint32 getPositiveSpeed()const { return _positiveSpeed; }//正向速度
		inline qint32 getNegativeSpeed()const { return _negativeSpeed; }//反向速度，如果有的话
		inline bool isScanAeraActived()const { return _isScanAeraActived; }//是否激活扫描区
		inline qint32 getPositiveScanAera()const {return _positiveScanAera;}//正向扫描区域
		inline qint32 getNegativeScanAera()const { return _negativeScanAera; }//反向扫描区域
		bool isPathTrafficLocked(qint32* ve = nullptr) {//交通管制情况
			if (ve) {
				*ve = _lockOwner;
			}
			return _lockOwner != 0 ? true : false;
		}
		
		//setter
		void setIfDoubleDirection(bool is) { _isDoubleDirection = is; }
		void setPositiveSpeed(qint32 sp) { _positiveSpeed = sp; }
		void setNegativeSpeed(qint32 sp) { _negativeSpeed = sp; }
		void setIfScanAeraActived(bool is) { _isScanAeraActived = is; }
		void setPositiveScanAera(qint32 aera) { _positiveScanAera = aera; }
		void setNegativeScanAera(qint32 aera) { _negativeScanAera = aera; }
		bool lockTraffic(qint32 ve) {//交通管制上锁
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
		bool _isDoubleDirection;
		bool _isScanAeraActived;
		qint32 _positiveSpeed;//本段的默认限速
		qint32 _negativeSpeed; //支持反向的化，反向速度
		qint32 _positiveScanAera;
		qint32 _negativeScanAera;
		qint32 _lockOwner; //锁拥有者
	};



	//工位接口
	class I_SunnyTcsLocation :public I_SunnyTcsElementData {
	public:
		explicit I_SunnyTcsLocation(qint32 id) :I_SunnyTcsElementData(id) {}

		virtual SunnyTcsMapObject_tag getTag()const {
			return SunnyTcsMapObject_tag(Elocation, _id);
		}

		virtual qint32 getLinkedPointId()const = 0;//相连的点

	protected:
		QList<SunnyTcsAction> _actions;//工位用来存储指令
	};



	//外围系统的实时数据
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

}
	



