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

	//������  ·���滮��  �߼�������  ����ִ����
	//��ֻ���� �������� �� һ��ִ���� ͬʱִ��һ������ָ�룬�������е�����
	//���� ״̬
	enum E_SunnyTcsRouteStatus { 
											//״̬����	  |   ������	        |           ˵��

		E_CRAFT_ORDERCENTER =0,				//δ������գ�   --��������				   -- ����ģ�壬�ɶ��������й�
		
		E_ORDER_INIT_ORDERCENTER = 1,       //����״̬         -- ��������				   -- �������״̬������     
		
		E_ORDER_LOGIC_MODEL = 2,             //�߼��ж�״̬    -- ģ��                       -- �߼��ж���   

		E_ORDER_DISPATCHING_DISPATCHER = 3,   //������         -- ������                     -- ���������д���   

		E_ORDER_DISPATCHED_MODEL = 4,         //�������       -- ģ��                       -- ģ�Ͷ��Ѿ����䣬���Ǳ���Ҫģ��ȷ�ϣ���Ϊ
																						//ʹ��actualData�ӿڣ��õ���С��״̬��һ��
																						//��ʵʱ��,   

		E_ORDER_ROUTING_ROUTER = 5,				//·���滮		 -- �滮��					   -- ·���滮����·�����й滮

		E_ORDER_ROUTED_MODEL = 6,				//·���滮���   -- ģ��					   -- ģ�Ͷ�·���滮���м�飬û����ʹ���ָ���ת�빤��

		E_ORDER_WORKING_MODEL = 7,				//������		 -- ģ��					   -- ģ�͸���ָ��

		E_ORDER_FINISHED_ORDERCENTER = 8,		//���			 -- ��������				   -- �������

		E_ORDER_FAILED_ORDERCENTER = 9,			//ʧ��			 -- ����ִ����				   -- ����ʧ���ˣ�����ִ���������Խ�����תΪ��״̬

		E_ORDER_CANCELING_ORDERCENTER = 10,		//������������	 -- ��������				   -- �������Ľ��յ��ⲿ�ĳ������󣬸�Ϊ��״̬����ִ
						
		E_ORDER_CANCELED_ORDERCENTER = 11		//�������ָ�״̬���ͷ����Ըö���������
	};


	typedef std::tuple<qint32, qint32,bool> SunnyTcsPt; //��ID,��λID,�Ƿ�ؾ���û�й�λ����0
	typedef QList<SunnyTcsPt> Pts;
	typedef Pts::iterator PtsIter;

	class SunnyTcsSonCraft;
	class SunnyTcsSonOrder;

	class SunnyTcsRoute : public Pts{
	public:
		//��Ԫ
		friend class SunnyTcsSonCraft;
		friend class SunnyTcsSonOrder;

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

		//������ID��·���㷨��ID
		//1 ���������û��ָ��AGV����ô�ͱ���ָ��������ID
		//2 ���������ָ����agv,��ô������ID �ͱ���Ϊ
		qint32 _dispatcherId;  //����Ϊ��Ч����ID, 0 Ϊ Ĭ�ϰ�ָ��agvִ�У�-1��ʾ�̳и���������·���������0������·�����벻Ϊ 0.
		qint32 _agvId;   //������ID ��Ϊ��ǰ��ЧAGVID,  0 �������κ�AGV�� -1 ����̳��϶�����ִ�г��� �� ��·�� ����С��0
		qint32 _routerId;	//����Ϊ��Ч�㷨ID�� 0 Ϊ Ĭ�����·���㷨�� -1 ������ʵ�������м̳� ������  ��·�� �������0������·�����벻Ϊ 0��

		
	};


	class SunnyTcsSonCraft;
	//���������
	class SunnyTcsRouteIndexer {
	public:
		static constexpr qint32 max_index = 100000000;//������ֵ�ǰ�ȫ�ģ����ն������ֶ���ģ�����100���������
		
		SunnyTcsRouteIndexer() :_indexCounter(0) {}
		SunnyTcsRouteIndexer(const SunnyTcsRouteIndexer&) = default;
		virtual ~SunnyTcsRouteIndexer() {}
		SunnyTcsRouteIndexer& operator=(const SunnyTcsRouteIndexer&) = default;

		virtual qint32 getNextIndex() {
			_indexCounter = (_indexCounter >= max_index ? 1 : (_indexCounter + 1));  // 1 - 99999999 
			return _indexCounter;
		}

		virtual void appendRoute(qint32 index, SunnyTcsSonCraft* route) = 0;

	protected:
		qint32 _indexCounter;
	};

	//�Ӷ���
	class SunnyTcsSonOrder;

	//�ӹ���
	class SunnyTcsSonCraft :public SunnyTcsRoute/*�ؾ�������*/ {
	public:
		friend class SunnyTcsSonOrder;

		SunnyTcsSonCraft(SunnyTcsRouteIndexer* indexer):SunnyTcsRoute(0),_sonRoutes(),_lastRoutes() {
			Q_ASSERT(indexer);
			_indexer = indexer;
			_index = _indexer->getNextIndex();//�趨�Լ��ڸù����е�index,
			_indexer->appendRoute(_index, this);
		}

		SunnyTcsSonCraft& operator[](qint32 index) {//��ȡ�Ӷ���
			Q_ASSERT(_sonRoutes.keys().contains(index));
			return  *( _sonRoutes[index]);
		}

		SunnyTcsSonCraft& operator<<(SunnyTcsSonCraft& son) {//�Ѷ�����ӵ��Ӷ����У������Լ����Լ�
			Q_ASSERT(son._indexer == _indexer);//������ͬһ�������ڵ�
			_sonRoutes.insert(son._index, &son);
			son._lastRoutes.insert(this->getIndex(), this);
			return *this;
		}

		SunnyTcsSonCraft& operator>> (SunnyTcsSonCraft& son) {
			Q_ASSERT(_indexer == son._indexer);
			return this->operator>> (son._index);
		}

		SunnyTcsSonCraft& operator>> (qint32 index) {//��index��Ӧ���Ӷ�������
			Q_ASSERT(_sonRoutes.keys().contains(index)&&_sonRoutes[index]->_lastRoutes.contains(_index));
			_sonRoutes[index]->_lastRoutes.remove(_index);
			_sonRoutes.remove(index);
			return *this;
		}

		//������¹�ϵ
		void clearRelationShip() {
			for (SunnyTcsSonCraft* ter : _sonRoutes) {
				ter->_lastRoutes.keys().contains(_index) ? 1 : throw SunnyTcsException<ERROR_BASIC_CONFUSED_RELATIONSHIP>();
				ter->_lastRoutes.remove(_index);
			}
			for (SunnyTcsSonCraft* ter : _lastRoutes) {
				ter->_sonRoutes.keys().contains(_index) ? 1 : throw SunnyTcsException<ERROR_BASIC_CONFUSED_RELATIONSHIP>();
				ter->_sonRoutes.remove(_index);
			}
			_sonRoutes.clear();
			_lastRoutes.clear();
		}


		//���ڵݹ��size����
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


		//ת�ַ���
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
		SunnyTcsRouteIndexer* _indexer;
		QHash<qint32, SunnyTcsSonCraft*> _sonRoutes; 
		QHash<qint32, SunnyTcsSonCraft*> _lastRoutes;
	};



	//�Ӷ���
	class SunnyTcsSonOrder :public SunnyTcsRoute/*��ϸ������*/ {
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
			indexListPtr = indexListPtr ? indexListPtr : &sonOrderHash;//����������ۼ��Ѵ���index�ģ���ֹ����ָ
			indexListPtr->insert(_index,this); //���Լ��ӽ�ȥ

			auto iter = craft._sonRoutes.begin();
			while (iter != craft._sonRoutes.end()) {
				bool contained = indexListPtr->contains((**iter).getIndex());
				SunnyTcsSonOrder* sonPtr = contained ?
					(*indexListPtr)[(**iter).getIndex()] : new SunnyTcsSonOrder(**iter , indexListPtr); //֮ǰ�Ѿ���������,���贴��
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

		//���ڵݹ��size����
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

		//�õ�״̬
		inline E_SunnyTcsRouteStatus getStatus()const { return _curOrder->_status; }

		//����״̬
		void setStatus(E_SunnyTcsRouteStatus status) { _curOrder->_status = status; }


		//������¹�ϵ
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

		//ת�ַ���
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
		PtsIter _curPt; //����ֻ���������Ѿ���ɹ滮�ĵ�
		QQueue<SunnyTcsAction> _actionQueue;
		SunnyTcsSonOrder* _curOrder; // ��ǰִ�е��ĸ���
		E_SunnyTcsRouteStatus _status;
		//��·��
		QHash<qint32, SunnyTcsSonOrder*> _sonRoutes; //��ͨ�Ӷ�����Ĭ��Ϊ��ɺ�ִ��									  
		//��·��
		QHash<qint32, SunnyTcsSonOrder*> _lastRoutes;
	};



	//����
	class SunnyTcsCraft : public SunnyTcsRouteIndexer {
	public:
		explicit SunnyTcsCraft(quint64 id) :SunnyTcsRouteIndexer(),
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

		qint32 addSonCraft() {
			SunnyTcsSonCraft* newOne = new SunnyTcsSonCraft(this);
			if (isEmpty()) {
				_root = newOne;
			}
			_allSonCrafts.insert(newOne->getIndex(), newOne);
			return newOne->getIndex();
		}

		bool removeSonCraft(qint32 index) {
			if (_root && _root->getIndex() == index) {
				return false; // ����ɾ����
			}
			if (_allSonCrafts.keys().contains(index)) {
				_allSonCrafts[index]->clearRelationShip();
				_allSonCrafts.remove(index);
				return true;
			}
			return false;
		}

		SunnyTcsSonCraft& operator[](qint32 index) {
			_allSonCrafts.keys().contains(index) ? 1 : throw SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>();
			return *(_allSonCrafts[index]);
		}

		const SunnyTcsSonCraft& operator[](qint32 index)const {
			_allSonCrafts.keys().contains(index) ? 1 : throw SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>();
			return *(_allSonCrafts[index]);
		}

		// ͨ�� SunnyTcsRouteIndexer �̳�
		virtual void appendRoute(qint32 index, SunnyTcsSonCraft * route) override {
			if (_allSonCrafts.keys().contains(index)) {
				throw SunnyTcsException<ERROR_BASIC_REPEAT_INDEX_IN_CRAFT>();
			}
			if (_allSonCrafts.isEmpty()) {
				_root = route;
			}
			_allSonCrafts.insert(index, route);
		}

	protected:
		quint64 _craftId;//����ID
		QHash<qint32, SunnyTcsSonCraft*> _allSonCrafts;
		SunnyTcsSonCraft* _root;
	};


	
	//������
	class SunnyTcsOrder {
	public:
		SunnyTcsOrder(quint64 orderId ,const SunnyTcsCraft& craft)
			:_root(nullptr),_ordId(orderId)
		{
			Q_ASSERT(!craft.isEmpty());//����ʹ�ÿչ��ճ�ʼ��
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
		quint64 _ordId;//����ID;
		SunnyTcsSonOrder* _root;
		QHash<qint32, SunnyTcsSonOrder*> _allSonOrders;
	};



	/*
	//indexer
	class SunnyTcsCraftIndexer {
	public:
		explicit SunnyTcsCraftIndexer(qint32 max = 9999) :_max(max), _indexCounter(0) ,_curRoute(nullptr),_rootRoute(nullptr){}

		SunnyTcsCraftIndexer(const SunnyTcsCraftIndexer& rhs)
			:_max(rhs._max), _indexCounter(rhs._indexCounter), _curRoute(nullptr), _rootRoute(nullptr), _routes()
		{}

		virtual ~SunnyTcsCraftIndexer() {}

		SunnyTcsCraftIndexer& operator=(const SunnyTcsCraftIndexer&) = delete;

		inline qint32 getNextIndex(){
			_indexCounter = (_indexCounter >= _max ? 0 : (_indexCounter + 1) );  // 0 - 9999  
			return _indexCounter;
		}

		virtual void appendRoute(qint32 index , SunnyTcsRoute* route) {
			if (_routes.isEmpty()) {
				_rootRoute = route;
				_curRoute = route;
			}
			_routes.insert(index, route);
		}

		inline qint32 getRouteCount()const { return _routes.count(); }

	protected:
		const qint32 _max;
		qint32 _indexCounter;
		QHash<qint32, SunnyTcsRoute*> _routes;
		SunnyTcsRoute* _rootRoute;
		SunnyTcsRoute* _curRoute;
	};


	//�����ӹ���
	class SUNNYTCSBASICV3_EXPORT SunnyTcsRoute {
	public:
		friend class SunnyTcsCraft;
		typedef QList<SunnyTcsVertex> Pts;
		typedef typename QList<SunnyTcsVertex>::iterator PtsIter;
		typedef typename QList<SunnyTcsVertex>::const_iterator PtsCiter;

		explicit SunnyTcsRoute(SunnyTcsCraftIndexer* indexer)
			:_indexer(indexer), _index(0), _status(E_CRAFT_ORDERCENTER),
			_sonRoutes(), _lastRoutes(), _pts(), _dispatcherId(0), _routerId(0),
			_conditionStr(), _isUpdated(false), _curRouted(_pts.begin()), _actionQueue(),
			_condition(nullptr), _routeResult() , _agvId(0)
		{
			Q_ASSERT(indexer);
			_index = _indexer->getNextIndex();//�趨�Լ��ڸù����е�index,
			_indexer->appendRoute(_index, this);
			std::cout << "create route : " << _index << std::endl;
		}


		SunnyTcsRoute(const SunnyTcsRoute& rhs, SunnyTcsCraftIndexer* indexer)
			:_indexer(indexer), _index(rhs._index),  _status(rhs._status),
			_sonRoutes(), _lastRoutes(), _pts(rhs._pts), _dispatcherId(rhs._dispatcherId), _routerId(rhs._routerId),
			_conditionStr(rhs._conditionStr), _isUpdated(rhs._isUpdated), _curRouted(_pts.begin()), _actionQueue(rhs._actionQueue),
			_condition(nullptr), _routeResult(rhs._routeResult), _agvId(rhs._agvId)
		{
			// _sonRoutes  _lastRoutes  _curRouted, ��Щ���ܼ򵥿���  _condition������
			indexer->appendRoute(_index, this);
			std::cout << "copy create route : " << _index << std::endl;
		}

		//ctor
		SunnyTcsRoute(const SunnyTcsRoute& rhs) = delete;

		SunnyTcsRoute& operator=(const SunnyTcsRoute& rhs) = delete;

		virtual ~SunnyTcsRoute() {
			std::cout << "release route: " << _index << std::endl;
		}


		SunnyTcsCraftIndexer* getCraftIndexPtr() { return _indexer; }


		//���������ز���
		SunnyTcsRoute& operator[](qint32 index) {//��ȡ�Ӷ���
			Q_ASSERT(_sonRoutes.keys().contains(index));
			return *(_sonRoutes[index]);
		}
		

		SunnyTcsRoute& operator<<(SunnyTcsRoute& son) {//�Ѷ�����ӵ��Ӷ����У������Լ����Լ�
			Q_ASSERT(son._indexer == _indexer);//������ͬһ�������ڵ�
			_sonRoutes.insert(son.getIndex(), &son);
			
			son._lastRoutes.insert(this->getIndex(), this);
			return *this;
		}


		SunnyTcsRoute& insertSonRoute(SunnyTcsRoute& son ,qint32 relation) {
			Q_ASSERT(son._indexer == _indexer);//������ͬһ�������ڵ�
			Q_ASSERT(relation == ROUTE_RELATION_FINISH || relation == ROUTE_RELATION_FAIL || relation == ROUTE_RELATION_EVENT);
			_sonRoutes.insert(son.getIndex(), &son);
			_sonRouteRelation.insert(son.getIndex(), relation);
			son._lastRoutes.insert(this->getIndex(), this);
			return *this;
		}
		

		SunnyTcsRoute& operator >> (SunnyTcsRoute& son) {
			Q_ASSERT(_indexer == son._indexer);
			return this->operator >> (son._index);
		}


		SunnyTcsRoute& operator>>(qint32 index) {//��index��Ӧ���Ӷ�������
			Q_ASSERT(_sonRoutes.keys().contains(index));
			Q_ASSERT(_sonRouteRelation.keys().contains(index));
			Q_ASSERT(_sonRoutes[index]->_lastRoutes.contains(_index));
			_sonRoutes[index]->_lastRoutes.remove(_index);
			_sonRouteRelation.remove(index);
			_sonRoutes.remove(index);
			return *this;
		}


		bool operator==(const SunnyTcsRoute& route)const {
			return _index == route._index  && _sonRoutes == route._sonRoutes &&_indexer == route._indexer &&
				_status == route._status && _routerId == route._routerId && _dispatcherId == route._dispatcherId &&
				 _conditionStr == route._conditionStr && _pts == route._pts;
		}


		//index
		inline qint32 getIndex()const { return _index; }
		void setIndex(qint32 index) { _index = index; }

	
		//statue
		bool isStatusUpdated() {
			bool ret = _isUpdated;
			_isUpdated = false;
			return ret;
		}

		inline E_SunnyTcsRouteStatus getStatus()const { return _status; }
		void setStatus(E_SunnyTcsRouteStatus status) {
			if (_status == E_ORDER_FINISHED_ORDERCENTER || 
				_status == E_ORDER_FAILED_ORDERCENTER ||
				_status == E_ORDER_CANCELING_ORDERCENTER ||
				_status == E_ORDER_CANCELED_ORDERCENTER) {//������״̬�²����������
				return;
			}
			_status = status;
			_isUpdated = true;
		}

		

		//condition
		inline std::shared_ptr<I_SunnyTcsCondition> getCondition() { return _condition; }
		void setCondition(std::shared_ptr<I_SunnyTcsCondition> con) { _condition = con; }
		inline QString getConditionStr()const { return _conditionStr; }
		void setConditionStr(QString con) {
			_conditionStr = con;
		}

		//dispatch
		inline qint32 getDispatchId() const {
			return _dispatcherId;
		}

		void setDispatchId(qint32 id) {
			_dispatcherId = id;
		}

		//router
		inline qint32 getRouterId()const {
			return _routerId;
		}

		void setRouterId(qint32 id) {
			_routerId = id;
		}

		//·�������
		void appendPt(const SunnyTcsVertex& ver) {
			_pts.append(ver);
		}

		void removePt(const SunnyTcsVertex& ver) {
			_pts.removeOne(ver);
		}

		void removeFirstPt() {
			_pts.removeFirst();
		}

		void removeLastPt() {
			_pts.removeLast();
		}

		void clearPt() {
			_pts.clear();
		}


		


		//processing
		//�Ƿ�����·�����ѹ滮
		QList<qint32> getSonRouteIndexs()const {
			return _sonRoutes.keys();
		}


		bool isAllRouteRouted()const {
			return _curRouted == _pts.end();
		}


		//�õ���һ����Ҫ�滮��·��
		Pts getNextRouteNeedRouting() {
			Pts route;
			getNextRouteNeedRouting(route);
			return route;
		}


		//�õ���һ����Ҫ�滮��·��
		void getNextRouteNeedRouting(Pts &route) {
			route.clear();
			auto iter = _curRouted;
			while (iter != _pts.end()) {
				route.append(*iter);
				//ֻҪ��·���滮������ط�����ֹͣ����
				++iter;
				
			}
		}

		PtsCiter getCurRouteEndPoint() const {
			return _curRouted;
		}


		qint32 getCurRoutedIndex()const {
			return _pts.indexOf(*_curRouted);
		}


		//�õ���һ����Ҫ�滮��·��������
		PtsCiter getNextRouteEndPoint() const {
			return _curRouted;
		}


		//routeReslut
		//������һ��Ҫִ�е�·��
		bool setNextRoute(Pts& route) {
			_routeResult.clear();
			_routeResult = route;
			while (_curRouted != _pts.end()) {
				if ( (*_curRouted).first == route.last().first) {
					return true;
				}
				++_curRouted;
			}
			return false;
		}

		Pts getNextRoute() {
			return _routeResult;
		}

		Pts& getNextRouteRef() {
			return _routeResult;
		}

		const Pts& getNextRouteRef()const {
			return _routeResult;
		}


		//actionQueue
		void clearActionQueue() {
			_actionQueue.clear();
		}

		void setActionQueue(const QQueue<SunnyTcsAction>& actions) {
			_actionQueue.clear();
			_actionQueue = actions;
		}

		void appendAction(SunnyTcsAction ac) {
			_actionQueue.push_back(ac);
		}

		QQueue<SunnyTcsAction> getActionQueue()const{
			return _actionQueue;
		}

		QQueue<SunnyTcsAction>& getActionQueueRef() {
			return _actionQueue;
		}

		const QQueue<SunnyTcsAction>& getActionQueueRef()const {
			return _actionQueue;
		}

		//string
		QString toString(QString& str, int spaceCount = 0,bool easy =true)const {

			if (!easy) {
				
			}
			for (int i = 0; i < spaceCount; ++i) {
				if (i % 8 == 0) {
					str += "|";
				}
				else {
					str += " ";
				}
			}
			str += "---------------\n";
			
			for (int i = 0; i < spaceCount; ++i) {
				if (i % 8 == 0) {
					str += "|";
				}else{
					str += " ";
				}
			}
			str += "|routeIndex : ";
			str += QString::number(_index);
			str += "\n";

			for (int i = 0; i < spaceCount; ++i) {
				if (i % 8 == 0) {
					str += "|";
				}
				else {
					str += " ";
				}
			}
			str += "|sonRoutes : \n";
			for (auto& ter : _sonRoutes.values()) {
				ter->toString(str, spaceCount + 8);
			}
			for (int i = 0; i < spaceCount; ++i) {
				if (i % 8 == 0) {
					str += "|";
				}
				else {
					str += " ";
				}
			}
			str += "---------------\n";
			return str;
		}

	protected:
		//indexer -------------------------------------------
		SunnyTcsCraftIndexer* _indexer;//indexer
		
		qint32 _index;
		QHash<qint32, SunnyTcsRoute*> _sonRoutes; //��ͨ�Ӷ�����Ĭ��Ϊ��ɺ�ִ��
		QHash<qint32, SunnyTcsRoute*> _lastRoutes;

		//������ID��·���㷨��ID
		//1 ���������û��ָ��AGV����ô�ͱ���ָ��������ID
		//2 ���������ָ����agv,��ô������ID �ͱ���Ϊ
		qint32 _dispatcherId;  //����Ϊ��Ч����ID, 0 Ϊ Ĭ�ϰ�ָ��agvִ�У�-1��ʾ�̳и���������·���������0������·�����벻Ϊ 0.
		qint32 _agvId;   //������ID ��Ϊ��ǰ��ЧAGVID,  0 �������κ�AGV�� -1 ����̳��϶�����ִ�г��� �� ��·�� ����С��0
		qint32 _routerId;	//����Ϊ��Ч�㷨ID�� 0 Ϊ Ĭ�����·���㷨�� -1 ������ʵ�������м̳� ������  ��·�� �������0������·�����벻Ϊ 0��
		
		//ִ������
		QString _conditionStr;

		//���й���������-------------------------------------------
		//�ؾ���
		Pts _pts;
		E_SunnyTcsRouteStatus _status;//����״̬

		bool _isUpdated;
		std::shared_ptr<I_SunnyTcsCondition> _condition;
		PtsIter _curRouted;//���й����У�ָ�����һ���Ѿ��滮��SunnyTcsVertex
		//׼ȷ·��
		Pts _routeResult;//�������浱ǰִ�е�·��
		//ָ���б�
		QQueue<SunnyTcsAction> _actionQueue;
	};



	//��������
	class SUNNYTCSBASICV3_EXPORT SunnyTcsCraft : public SunnyTcsCraftIndexer {
	public:
		SunnyTcsCraft()
			:SunnyTcsCraftIndexer(), _craftId(0), _orderId(0), _orderLock(), _errMsg()
		{

		}

		//ctor
		SunnyTcsCraft(const SunnyTcsCraft& rhs)
			:SunnyTcsCraftIndexer(rhs),_errMsg(rhs._errMsg),
			_orderId(rhs._orderId),_orderLock(),
			_craftId(rhs._craftId)
		{
			for (auto& ter : rhs._routes) {
				new SunnyTcsRoute(*ter, this);
			}

			for (auto& ter : rhs._routes) {
				const QList<qint32>& sonIndexs = ter->getSonRouteIndexs();
				for (qint32 sonIndex : sonIndexs) {
					*_routes[ter->getIndex()] << *_routes[sonIndex];
				}
			}
		}

		virtual ~SunnyTcsCraft() {
			_rootRoute = nullptr;
			_curRoute = nullptr;
			std::for_each(_routes.begin(), _routes.end(), [](SunnyTcsRoute* ptr)->void {delete ptr; });
		}

		//������
		SunnyTcsCraft& operator=(const SunnyTcsCraft& rhs) = delete;


		bool operator==(const SunnyTcsCraft& rhs)const {
			return _craftId == rhs._craftId &&
				_orderId == rhs._orderId &&
				_routes == rhs._routes &&
				((_rootRoute == nullptr && rhs._rootRoute == nullptr) || (_rootRoute->getIndex() == rhs._rootRoute->getIndex())) &&
				((_curRoute == nullptr && rhs._curRoute == nullptr) || (_curRoute->getIndex() == rhs._curRoute->getIndex())) &&
				_max == rhs._max &&
				_indexCounter == rhs._indexCounter
				;
		}


		SunnyTcsRoute& operator[](qint32 index) {
			if (!_routes.keys().contains(index) && _routes[index])Q_ASSERT(0);
			return *(_routes[index]);
		}


		//�ӹ���
		//���һ���ӹ���
		virtual qint32 addRoute() {
			SunnyTcsRoute* rt = new SunnyTcsRoute(this);//���������ӹ��� ����
			return rt->getIndex();
		}

		QList<qint32> sonIndexsOfCurrentRoute() {
			if (!_curRoute)return QList<qint32>();
			return _curRoute->_sonRoutes.keys();
		}

		QHash<qint32, std::shared_ptr<I_SunnyTcsCondition>> sonConditionsOfCurrentRoute() {
			QHash < qint32, std::shared_ptr<I_SunnyTcsCondition>> ret;
			if (!_curRoute)return ret;
			for (auto& ter : _curRoute->_sonRoutes) {
				ret.insert(ter->getIndex(), ter->getCondition());
			}
			return ret;
		}

		//ȡ���ӹ���
		virtual bool removeRoute(qint32 index) {
			if (_routes.keys().contains(index)) {
				if (_rootRoute == _routes[index]) {
					return false;
				}
				else if (_curRoute == _routes[index])
				{
					_curRoute == _rootRoute;
				}

				for (auto& ter : _routes[index]->_sonRoutes) {//�������ӹ��� �� �ӹ�����
					Q_ASSERT(ter->_lastRoutes.keys().contains(index));//ȥ���ӹ��� �� ������
					ter->_lastRoutes.remove(index);
				}
				for (auto& ter : _routes[index]->_lastRoutes) {
					Q_ASSERT(ter->_sonRoutes.keys().contains(index));//ȥ�������յ� ������
					ter->_sonRoutes.remove(index);
				}
				_routes[index]->_indexer = nullptr;

				delete _routes[index];
				_routes.remove(index);
			}
			return true;
		}


		//��һ����ǰ·��
		bool setNextCurrentRoute(qint32 index) {
			if (!_curRoute || !_curRoute->_sonRoutes.keys().contains(index)) {
				return false;
			}
			_curRoute = _curRoute->_sonRoutes[index];
			return true;
		}

		//������ת���ɳ�ʼ���Ķ���
		SunnyTcsCraft* toInitOrder(qint32 agvId = 0) const {
			SunnyTcsCraft* ptr = new SunnyTcsCraft(*this);
			ptr->_orderId = SunnyTcsUIDWorker::getUIDWorker()->nextId();
			return ptr;
		}

		inline qint32 getCraftId()const { return _craftId; }
		inline quint64 getOrderId()const { return _orderId; }
		
		inline qint32 getAgvId()const { return 0; }
		void setAgvId(qint32 id) { }

		E_SunnyTcsRouteStatus getCurrentStatus()const {
			if (!_curRoute) {
				Q_ASSERT(0);
			}
			return _curRoute->getStatus();
		}

		void setCurrentStatus(E_SunnyTcsRouteStatus status) {
			if (!_curRoute) {
				Q_ASSERT(0);
			}
			_curRoute->setStatus(status);
		}


		

		//��
		void lock() {
			_orderLock.lock();
		}

		void unlock() {
			_orderLock.unlock();
		}

		bool trylock() {
			return _orderLock.tryLock();
		}


		SunnyTcsRoute* getCurrentRoute() {
			return _curRoute;
		}

		bool setCurrentRoute(qint32 index) {
			if (!_routes.keys().contains(index)) {
				return false;
			}
			_curRoute = _routes[index];
			return true;
		}

		SunnyTcsRoute* getRootRoute() {
			return _rootRoute;
		}

		void getnextRouteNeedRouting(SunnyTcsRoute::Pts& pts) {
			_curRoute->getNextRouteNeedRouting(pts);
		}

		inline QString getErrorMsg()const {
			return _errMsg;
		}

		void setErrorMsg(QString msg) {
			_errMsg = msg;
		}

		QString toString(bool tree = true, qint32 startIndex = 0)const {
			QString str;
			Q_ASSERT(startIndex == 0 || _routes.keys().contains(startIndex));
			SunnyTcsRoute* startRoot = startIndex == 0 ? _rootRoute : _routes[startIndex];
			if (!startRoot)return str;
			if (tree) {
				startRoot->toString(str);
			}
			else {
				for (auto& ter : _routes) {	
					
				}
			}
			return str;
		}

	protected:
		qint32 _craftId;//����ID 
		quint64 _orderId;//����ID
		QString _errMsg;
		QMutex _orderLock;
		
	};


	*/

}
