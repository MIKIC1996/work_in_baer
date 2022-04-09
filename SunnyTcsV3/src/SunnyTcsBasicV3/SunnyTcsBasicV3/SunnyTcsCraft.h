#pragma once
#include "SunnyTcsVagueCondition.h"
#include "SunnyTcsUIDWorker.h"





#define ROUTE_RELATION_FINISH 1
#define ROUTE_RELATION_FAIL 2
#define ROUTE_RELATION_EVENT 3 


//json
//route
#define	JSON_ROUTE_INDEX "routeId"
#define JSON_ROUTE_STATUS "routeStatus"
#define JSON_ROUTE_CONDITION "routeCondition"
#define JSON_ROUTE_PTS "routePts"
#define JSON_ROUTE_SONINDEXS "routeSonIndexs"
#define JSON_ROUTE_DISPATCHER "routeDispatcherId"
#define JSON_ROUTE_ROUTER "routeRouterId"
#define JSON_ROUTE_AGVID "routeAgvId"


//craft
#define JSON_CRAFT_ID "craftId"
#define JSON_CRAFT_DESCRIPTION "craftDescription"
#define JSON_CRAFT_ORDERID "craftOrderId"
#define JSON_CRAFT_AGVID "craftAgvId"
#define JSON_CRAFT_ERRMSG "craftErrMsg"
#define JSON_CRAFT_ROUTES "craftRoutes"
#define JSON_CRAFT_CUR "craftCurrentRoute"
#define JSON_CRAFT_ROOT "craftRootRoute"



namespace basic {

	//分配器  路径规划器  逻辑分析器  复数执行器
	//我只允许 订单中心 和 一个执行器 同时执有一个订单指针，不允许有第三者
	//流程 状态
	enum E_SunnyTcsRouteStatus { 
											//状态中文	  |   处理者	        |           说明

		E_CRAFT_ORDERCENTER =0,				//未激活（工艺）   --订单中心				   -- 工艺模板，由订单中心托管
		
		E_ORDER_INIT_ORDERCENTER = 1,       //激活状态         -- 订单中心				   -- 订单最初状态，激活     
		
		E_ORDER_LOGIC_MODEL = 2,             //逻辑判断状态    -- 模型                       -- 逻辑判断中   

		E_ORDER_DISPATCHING_DISPATCHER = 3,   //分配中         -- 分配器                     -- 分配器进行处理   

		E_ORDER_DISPATCHED_MODEL = 4,         //分配完成       -- 模型                       -- 模型对已经分配，但是必须要模型确认，因为
																						//使用actualData接口，得到的小车状态不一定
																						//是实时的,   

		E_ORDER_ROUTING_ROUTER = 5,				//路径规划		 -- 规划器					   -- 路径规划器对路径进行规划

		E_ORDER_ROUTED_MODEL = 6,				//路径规划完成   -- 模型					   -- 模型对路径规划进行检查，没问题就创建指令，并转入工作

		E_ORDER_WORKING_MODEL = 7,				//工作中		 -- 模型					   -- 模型更新指令

		E_ORDER_FINISHED_ORDERCENTER = 8,		//完成			 -- 订单中心				   -- 订单完成

		E_ORDER_FAILED_ORDERCENTER = 9,			//失败			 -- 各个执行器				   -- 订单失败了，各个执行器都可以将订单转为该状态

		E_ORDER_CANCELING_ORDERCENTER = 10,		//订单撤销请求	 -- 订单中心				   -- 订单中心接收到外部的撤销请求，改为该状态，各执
						
		E_ORDER_CANCELED_ORDERCENTER = 11		//行器发现该状态，就放弃对该订单的引用
	};


	typedef std::tuple<qint32, qint32,bool> SunnyTcsPt; //点ID,工位ID,是否必经，没有工位就是0
	typedef QList<SunnyTcsPt> Pts;
	typedef Pts::iterator PtsIter;

	class SunnyTcsSonCraft;

	class SunnyTcsRoute : public Pts{
	public:
		//友元
		friend class SunnyTcsSonCraft;

		explicit SunnyTcsRoute(qint32 index):Pts(),_index(index),
		_dispatcherId(0),_agvId(0),_routerId(0)
		{}

		SunnyTcsRoute(const SunnyTcsRoute&) = default;

		virtual ~SunnyTcsRoute(){}

		SunnyTcsRoute& operator=(const SunnyTcsRoute&) = default;

		//getter
		inline qint32 getIndex()const { return _index; }
		inline qint32 getDispatcherId()const { return _dispatcherId; }
		inline qint32 getAgvId()const { return _agvId; }
		inline qint32 getRouterId()const { return _routerId; }

		//setter
		void setDispatcherId(qint32 id) { _dispatcherId = id; }
		void setAgvId(qint32 id) { _agvId = id; }
		void setRouterId(qint32 id) { _routerId = id; }

	protected:
		//indexer
		qint32 _index;

		//分配器ID与路径算法器ID
		//1 如果根订单没有指定AGV，那么就必须指定分配器ID
		//2 如果根订单指定了agv,那么分配器ID 就必须为
		qint32 _dispatcherId;  //正数为有效分配ID, 0 为 默认按指定agv执行，-1表示继承父订单，根路径必须大于0，其他路径必须不为 0.
		qint32 _agvId;   //正数的ID 均为当前有效AGVID,  0 不代表任何AGV， -1 代表继承上订单的执行车辆 ， 根路径 不可小于0
		qint32 _routerId;	//正数为有效算法ID， 0 为 默认最短路径算法， -1 代表再实际运行中继承 父订单  根路径 必须大于0，其他路径必须不为 0。
	};





	//子工艺
	class SunnyTcsSonCraft :public SunnyTcsRoute/*必经点容器*/ {
	public:
	
		SunnyTcsSonCraft():SunnyTcsRoute(0),_sonRoutes(),_lastRoutes() {
			
		}


		SunnyTcsSonCraft* getSonCraft(qint32 index)
		{
			return _sonRoutes.contains(index) ? _sonRoutes[index] : nullptr;
		}

		const SunnyTcsSonCraft* getSonCraft(qint32 index)const {
			return _sonRoutes.contains(index) ? _sonRoutes[index] : nullptr;
		}

		bool pushSon(SunnyTcsSonCraft* son) {
			
		}

		bool fromJson(QJsonObject& jobj) {
			return false;
		}

		QJsonObject toJson()const {
			return QJsonObject();
		}

		//清除上下关系
		void clearRelationShip() {
			for (SunnyTcsSonCraft* ter : _sonRoutes) {
				ter->_lastRoutes.keys().contains(_index) ? 1 : Q_ASSERT(0); //不包含是不容许出现的错误，说明数据结构已经被破坏
				ter->_lastRoutes.remove(_index);
			}
			for (SunnyTcsSonCraft* ter : _lastRoutes) {
				ter->_sonRoutes.keys().contains(_index) ? 1 : Q_ASSERT(0);
				ter->_sonRoutes.remove(_index);
			}
			_sonRoutes.clear(); 
			_lastRoutes.clear();
		}


		//基于递归的size计算
		qint32 size(QList<qint32>* s = nullptr)const {
			QList<qint32> recorder;
			s = s ? s : &recorder;
			s->append(_index);
			for (auto ter : _sonRoutes) {
				if (!s->contains(ter->getIndex())) {
					ter->size(s);
				}
			}
			return s->count();
		}

		//转字符串
		QString toString()const {
			QString str("----%1----\n");
			str = str.arg(QString::number(_index));
			for (auto ter : _lastRoutes) {
				str += QString::number(ter->getIndex());
				str += "\n";
			}
			str += "----------\n";
			for (auto ter : _sonRoutes) {
				str += QString::number(ter->getIndex());
				str += "\n";
			}
			str += "----------\n";
			return str;
		}

	
		void getAllSonCrafts(QHash<qint32, SunnyTcsSonCraft*>& record) {
			record.insert(_index, this);
			for (auto ter : _sonRoutes) {
				bool contained = record.contains(ter->getIndex());
				if (!contained) {
					ter->getAllSonCrafts(record);
				}
			}
		}

	protected:
		QHash<qint32, SunnyTcsSonCraft*> _sonRoutes; 
		QHash<qint32, SunnyTcsSonCraft*> _lastRoutes;

		//详细的属性
		PtsIter _curPt; //用来只是容器中已经完成规划的点
		QQueue<SunnyTcsAction> _actionQueue;
		SunnyTcsSonCraft* _curOrder; // 当前执行到哪个了
		E_SunnyTcsRouteStatus _status;
	};


	/*
	//子订单
	class SunnyTcsSonOrder :public SunnyTcsRoute{
	public:
		friend class SunnyTcsOrder;

		explicit SunnyTcsSonOrder(qint32 index)
			:SunnyTcsRoute(index), _status(E_ORDER_INIT_ORDERCENTER),
			_curOrder(nullptr), _actionQueue(), _curPt(), _sonRoutes(), _lastRoutes()
		{
			_curOrder = this;
		}

		SunnyTcsSonOrder(const SunnyTcsSonCraft& craft , QHash<qint32, SunnyTcsSonOrder*>* indexListPtr = nullptr)
			:SunnyTcsRoute(craft._index), _status(E_ORDER_INIT_ORDERCENTER),
			_curOrder(nullptr), _actionQueue(), _curPt(), _sonRoutes(), _lastRoutes()
		{
			_curOrder = this;
			dynamic_cast<SunnyTcsRoute&>(*this) = dynamic_cast<const SunnyTcsRoute&>(craft);
			QHash<qint32, SunnyTcsSonOrder*> sonOrderHash;
			indexListPtr = indexListPtr ? indexListPtr : &sonOrderHash;//这个是用来累计已存在index的，防止来回指
			indexListPtr->insert(_index,this); //将自己加进去

			auto iter = craft._sonRoutes.begin();
			while (iter != craft._sonRoutes.end()) {
				bool contained = indexListPtr->contains((**iter).getIndex());
				SunnyTcsSonOrder* sonPtr = contained ?
					(*indexListPtr)[(**iter).getIndex()] : new SunnyTcsSonOrder(**iter , indexListPtr); //之前已经创建过了,无需创建
				if (!_sonRoutes.keys().contains((**iter).getIndex())){
					_sonRoutes.insert(sonPtr->getIndex(), sonPtr);
					sonPtr->_lastRoutes.insert(_index, this);
				}
				++iter;
			}
		}

		//copy ctor
		SunnyTcsSonOrder(const SunnyTcsSonOrder&) = delete;

		//dtor
		virtual ~SunnyTcsSonOrder() {}

		//assignment
		SunnyTcsSonOrder& operator=(const SunnyTcsSonOrder&) = delete;

		//基于递归的size计算
		qint32 size(QList<qint32>* s = nullptr)const {
			QList<qint32> recorder;
			s = s ? s : &recorder;
			s->append(_index);
			for (auto ter : _sonRoutes) {
				if (!s->contains(ter->getIndex()) ){
					ter->size(s);
				}
			}
			return s->count();
		}

		//得到状态
		inline E_SunnyTcsRouteStatus getStatus()const { return _curOrder->_status; }

		//设置状态
		void setStatus(E_SunnyTcsRouteStatus status) { _curOrder->_status = status; }


		//清除上下关系
		void clearRelationShip() {
			for (SunnyTcsSonOrder* ter : _sonRoutes) {
				ter->_lastRoutes.keys().contains(_index) ? 1 : throw SunnyTcsException<ERROR_BASIC_CONFUSED_RELATIONSHIP>();
				ter->_lastRoutes.remove(_index);
			}
			for (SunnyTcsSonOrder* ter : _lastRoutes) {
				ter->_sonRoutes.keys().contains(_index) ? 1 : throw SunnyTcsException<ERROR_BASIC_CONFUSED_RELATIONSHIP>();
				ter->_sonRoutes.remove(_index);
			}
			_sonRoutes.clear();
			_lastRoutes.clear();
		}

		//转字符串
		QString toString()const {
			QString str("----%1----\n");
			str = str.arg(QString::number(_index));
			for (auto ter : _lastRoutes) {
				str += QString::number(ter->getIndex());
				str += "\n";
			}
			str += "----------\n";
			for (auto ter : _sonRoutes) {
				str += QString::number(ter->getIndex());
				str += "\n";
			}
			str += "----------\n";
			return str;
		}

	protected:
		void getAllSonOrders(QHash<qint32, SunnyTcsSonOrder*>& record) {
			record.insert(_index, this);
			for (auto ter : _sonRoutes) {
				bool contained = record.contains(ter->getIndex());
				if (!contained) {
					ter->getAllSonOrders(record);
				}
			}
		}


	protected:
		PtsIter _curPt; //用来只是容器中已经完成规划的点
		QQueue<SunnyTcsAction> _actionQueue;
		SunnyTcsSonOrder* _curOrder; // 当前执行到哪个了
		E_SunnyTcsRouteStatus _status;
		//子路径
		QHash<qint32, SunnyTcsSonOrder*> _sonRoutes; //普通子订单，默认为完成后执行									  
		//父路径
		QHash<qint32, SunnyTcsSonOrder*> _lastRoutes;
	};

	*/


	//工艺
	class SunnyTcsCraft {
	public:
		explicit SunnyTcsCraft(QString id) :
			_craftId(id), _allSonCrafts(), _root(nullptr) {
		}

		virtual ~SunnyTcsCraft() {
			for (auto ter : _allSonCrafts) {
				ter->clearRelationShip();
				delete ter;
			}
		}

		bool isEmpty()const {
			return !_root;
		}

		SunnyTcsSonCraft* getRoot() {
			return _root;
		}

		const SunnyTcsSonCraft* getRoot()const {
			return _root;
		}



		bool fromJson(QJsonObject& jobj) {
			return false;
		}
			
		QJsonObject toJson()const {
			return QJsonObject();
		}


	protected:
		QString _craftId;//工艺ID
		QHash<qint32, SunnyTcsSonCraft*> _allSonCrafts;
		SunnyTcsSonCraft* _root;
	};


	typedef SunnyTcsCraft SunnyTcsOrder;

	/*
	//订单类
	class SunnyTcsOrder {
	public:
		SunnyTcsOrder(quint64 orderId ,const SunnyTcsCraft& craft)
			:_root(nullptr),_ordId(orderId)
		{
			Q_ASSERT(!craft.isEmpty());//不可使用空工艺初始化
			_root = new SunnyTcsSonOrder(*(craft.getRoot()));
			init();
		}

		SunnyTcsOrder(quint64 orderId, const SunnyTcsSonCraft& sonCraft)
			:_root(nullptr), _ordId(orderId)
		{
			_root = new SunnyTcsSonOrder(sonCraft);
			init();
		}

		SunnyTcsOrder(const SunnyTcsOrder&) = delete;

		virtual ~SunnyTcsOrder() {
			for (auto ter : _allSonOrders) {
				ter->clearRelationShip();
				delete ter;
			}
		}

		SunnyTcsOrder& operator=(const SunnyTcsOrder&) = delete;


		SunnyTcsSonOrder& operator[](qint32 index) {
			_allSonOrders.keys().contains(index) ? 1 : throw SunnyTcsException<ERROR_BASIC_UNEXISTED_ORDER_INDEX>();
			return *(_allSonOrders[index]);
		}

		const SunnyTcsSonOrder& operator[](qint32 index)const {
			_allSonOrders.keys().contains(index) ? 1 : throw SunnyTcsException<ERROR_BASIC_UNEXISTED_ORDER_INDEX>();
			return *(_allSonOrders[index]);
		}

		qint32 size()const {
			return _allSonOrders.count();
		}
		
	protected:
		void init() {
			_allSonOrders.clear();
			_root->getAllSonOrders(_allSonOrders);
		}

	protected:
		quint64 _ordId;//订单ID;
		SunnyTcsSonOrder* _root;
		QHash<qint32, SunnyTcsSonOrder*> _allSonOrders;
	};
	*/

}
