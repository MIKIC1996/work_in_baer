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

	class SunnyTcsRoute : public Pts{
	public:
		//��Ԫ
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

		//������ID��·���㷨��ID
		//1 ���������û��ָ��AGV����ô�ͱ���ָ��������ID
		//2 ���������ָ����agv,��ô������ID �ͱ���Ϊ
		qint32 _dispatcherId;  //����Ϊ��Ч����ID, 0 Ϊ Ĭ�ϰ�ָ��agvִ�У�-1��ʾ�̳и���������·���������0������·�����벻Ϊ 0.
		qint32 _agvId;   //������ID ��Ϊ��ǰ��ЧAGVID,  0 �������κ�AGV�� -1 ����̳��϶�����ִ�г��� �� ��·�� ����С��0
		qint32 _routerId;	//����Ϊ��Ч�㷨ID�� 0 Ϊ Ĭ�����·���㷨�� -1 ������ʵ�������м̳� ������  ��·�� �������0������·�����벻Ϊ 0��
	};





	//�ӹ���
	class SunnyTcsSonCraft :public SunnyTcsRoute/*�ؾ�������*/ {
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

		//������¹�ϵ
		void clearRelationShip() {
			for (SunnyTcsSonCraft* ter : _sonRoutes) {
				ter->_lastRoutes.keys().contains(_index) ? 1 : Q_ASSERT(0); //�������ǲ�������ֵĴ���˵�����ݽṹ�Ѿ����ƻ�
				ter->_lastRoutes.remove(_index);
			}
			for (SunnyTcsSonCraft* ter : _lastRoutes) {
				ter->_sonRoutes.keys().contains(_index) ? 1 : Q_ASSERT(0);
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

		//��ϸ������
		PtsIter _curPt; //����ֻ���������Ѿ���ɹ滮�ĵ�
		QQueue<SunnyTcsAction> _actionQueue;
		SunnyTcsSonCraft* _curOrder; // ��ǰִ�е��ĸ���
		E_SunnyTcsRouteStatus _status;
	};


	/*
	//�Ӷ���
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

	*/


	//����
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
		QString _craftId;//����ID
		QHash<qint32, SunnyTcsSonCraft*> _allSonCrafts;
		SunnyTcsSonCraft* _root;
	};


	typedef SunnyTcsCraft SunnyTcsOrder;

	/*
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
	*/

}
