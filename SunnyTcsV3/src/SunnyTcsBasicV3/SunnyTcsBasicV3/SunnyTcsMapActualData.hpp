#pragma once

#include "SunnyTcsMapGeneral.hpp"
#include "SunnyTcsAction.h"



// vehicle nagative mode
#define VEHICLE_NAGA_RUBBON 0X01
#define VEHICLE_NAGA_INERTIA 0X02
#define VEHICLE_NAGA_LASER 0X04


//�����ں�ģ����ƵĽӿ��ļ�
namespace basic {

	//����ʶ��code
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

		qint32 _agvType;//����ʶ���
		qint32 _nagaMode; //֧�ֵĵ�����ʽ ,���32��
		qint32 _actionParamsCount;//ָ�����������
		E_ARG_TYPE _actionParamsType;//ָ�����������
		E_CoordinateDimension _dim;  //��ʼά�����Թ������⳵����Ч
		QString _description; //����
	};

	

	class I_SunnyTcsElementData;
	//ĳ����Ľӿ�
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
		//�����ǹ�I_SunnyTcsElementData�ڲ����õ�
		virtual void registerGroup(I_SunnyTcsElementData*) = 0;
		virtual void dropRegister(qint32 id) = 0;
		
	protected:
		qint32 _id;
		QString _name;
		QHash<qint32, I_SunnyTcsElementData*> _members;
	};




	//��ͼԪ�����ݽӿ�,�ӿ���ƾ������ �ӿڴ��麯�����У��������Զ��׼���ʵ�֣�
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

		//����������
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
		virtual SunnyTcsArg getAttribution(QString key,bool& ok)const = 0;//��Ƹýӿ���Ϊ������ �Ǳ���Ŀ�����ͻ��Ķ���������
		virtual bool setAttribution(QString key, SunnyTcsArg arg) = 0;
		//��λ�ӿڣ��ṩĬ��ʵ��
		virtual QVector<SunnyTcsMapBlock> getBlocks(qint32 resolution)const { return QVector<SunnyTcsMapBlock>(); }
		virtual bool isInRange(SunnyTcsAgvCoordinate coor)const { return false; }
	protected:
		qint32 _id;
		I_SunnyTcsGroup* _group;
	};



	//����ǳ������ػ��ӿ�,ʹ�ö�д�������̰߳�ȫ
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
		inline  SunnyTcsAgvCoordinate getAgvCurCoor()const { std::shared_lock<std::shared_mutex> lk(_lock); return _coor; }//����ӿ�
		inline  SunnyTcsMapObject_tag getAgvCurPos()const { std::shared_lock<std::shared_mutex> lk(_lock); return _pos; }//λ�ýӿ�
		inline  E_SunnyTcsVehicleStatus getAgvStatus()const { return _status; }//״̬�ӿ�


		inline  qint32 getLift()const { return _lift; }//�����ӿڣ���Ҫ��agv�Լ���д��Ҳ��Ҫ�����ʵ��
		inline  qint64 getError()const { std::shared_lock<std::shared_mutex> lk(_lock); return  _error; } //�����ӿڣ���Ҫ��agv�Լ���д��Ҳ��Ҫ�����ʵ��
		inline  qint64 getWarning()const { std::shared_lock<std::shared_mutex> lk(_lock); return _warning; } //�����ӿڣ���Ҫ��agv�Լ���д��Ҳ��Ҫ�����ʵ��
		
		//setter
		void setAgvCurCoor(SunnyTcsAgvCoordinate coor) { std::unique_lock<std::shared_mutex> lk(_lock); _coor = coor; }//��������
		void setAgvCurPos(SunnyTcsMapObject_tag curPos) { std::unique_lock<std::shared_mutex> lk(_lock); _pos = curPos; }//����λ��
		void setAgvStatue(E_SunnyTcsVehicleStatus status) { _status = status; }//����״̬

		void setLift(qint32 lift) { _lift = lift; }
		void setError(qint64 error) { std::unique_lock<std::shared_mutex> lk(_lock); _error = error; }
		void setWarning(qint64 warning) { std::unique_lock<std::shared_mutex> lk(_lock); _warning = warning; }
		
		//interface
		virtual bool isOrderLocked(quint64* orderId = nullptr) {//��������״̬
			std::shared_lock<std::shared_mutex> lock(_lock);
			if (orderId) {
				*orderId = _orderBinded;
			}
			return _orderBinded != 0 ? true : false;
		}

		virtual bool bindOrderToAgv(quint64 orderId) { //�������󶨵���
			std::unique_lock<std::shared_mutex> lk(_lock);
			_orderBinded = _orderBinded == 0 ? orderId : _orderBinded;
			return _orderBinded == orderId;
		}

		virtual SunnyTcsMapObject_tag getTag()const {
			std::shared_lock<std::shared_mutex> lock(_lock);
			return SunnyTcsMapObject_tag(Evehicle, _id);
		}

		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override= 0;//��ȡ���Խӿ�
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//�������Խӿ�

		virtual bool updateData(const QByteArray& data) = 0; //���ݸ���
		virtual bool updateData(QByteArray&& data) { return false; }//��ֵ�汾����Ҫ������һ��ʵ��

	protected:
		SunnyTcsAgvCode _code;
		SunnyTcsAgvCoordinate _coor;
		SunnyTcsMapObject_tag _pos;
		E_SunnyTcsVehicleStatus _status;
		quint64 _orderBinded;
		qint32 _lift;
		qint64 _error;
		qint64 _warning;

		//��д��
		mutable std::shared_mutex _lock;
	};


	//��ķ���
	enum E_SunnyTcsAxisDirection {
		Eright = 1,
		Eup = 2,
		Eleft = 3,
		Edown = 4
	};


	//����ϵ�ӿ�
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

		//X�᾵��
		void mirrorX() {
			std::unique_lock<std::shared_mutex> lk(_lock);
			_xpos = _xpos == Eright || _xpos == Eleft ? (_xpos == Eright ? Eleft : Eright) : (_xpos == Eup) ? Edown : Eup;
		}

		//Y�᾵��
		void mirrorY() {
			std::unique_lock<std::shared_mutex> lk(_lock);
			_ypos = _ypos == Eright || _ypos == Eleft ? (_ypos == Eright ? Eleft : Eright) : (_ypos == Eup) ? Edown : Eup; 
		}

		//����ϵ��ת
		void rotate() {
			std::unique_lock<std::shared_mutex> lk(_lock);
			qint32 xVal = static_cast<qint32>(_xpos);
			qint32 yVal = static_cast<qint32>(_ypos);
			xVal = xVal + 1 > 4 ? 1 : xVal + 1;
			yVal = yVal + 1 > 4 ? 1 : yVal + 1;
			_xpos = static_cast<E_SunnyTcsAxisDirection>(xVal);
			_ypos = static_cast<E_SunnyTcsAxisDirection>(yVal);
		}

		//�����麯��
		virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const = 0;
		virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene)const = 0;

		// ͨ�� I_SunnyTcsElementData �̳�
		virtual SunnyTcsMapObject_tag getTag() const override {
			std::shared_lock<std::shared_mutex> lk(_lock);
			return SunnyTcsMapObject_tag(Ecoorsys, _id); 
		}
		virtual SunnyTcsArg getAttribution(QString key, bool & ok) const override = 0;
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;


	protected:
		const SunnyTcsAgvCoordinate _rxy;//��ʵ����
		E_SunnyTcsAxisDirection _xpos;
		E_SunnyTcsAxisDirection _ypos;

		//��
		mutable std::shared_mutex _lock;
	};


	//���ʵʱ����,�̰߳�ȫ
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
		inline qint32 getPointNaga()const { return _nagaMode; }//���nagamode
		inline qint32 getPointAbsPos()const { return _absPos; }//��ľ���λ��
		inline SunnyTcsAgvCoordinate getPointCoor()const { std::shared_lock<std::shared_mutex> lk(_lock);  return _rxy; }//�������
		inline qint32 getUsedCount()const { return _usedCount; }//��ǰ�����ѹ滮·���Ըõ��ռ�����
		bool isPointTrafficLocked(qint32* ve = nullptr)const {//��ͨ�������
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
		bool lockTraffic(qint32 ve){//��ͨ��������
			std::unique_lock<std::shared_mutex> lk(_lock);
			_lockOwner = _lockOwner == 0 ? ve : _lockOwner;
			return _lockOwner == ve;
		}

		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
			std::shared_lock<std::shared_mutex> lk(_lock);
			return SunnyTcsMapObject_tag(Epoint, _id);
		}
		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override = 0;//��ȡ���Խӿ�
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//�������Խӿ�

	protected:
		qint32 _absPos;//��ľ���λ��
		SunnyTcsAgvCoordinate _rxy;//�ߵ����ö�ά,�����ö�ά��������Ϊ��
		qint32 _nagaMode; //һ����Ҳ������ ���ֵ�����ʽ ��0 ������ ��1 ɫ���㣬2 �ߵ��㣬4 �����
		qint32 _lockOwner; //��ӵ����
		qint32 _usedCount; //�����ѹ滮·���Ե��ռ����
		
		mutable std::shared_mutex _lock;
	};


	//�����ݣ��̰߳�ȫ
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
		inline qint32 getPositiveSpeed()const { return _positiveSpeed; }//�����ٶ�
		inline qint32 getNegativeSpeed()const { return _negativeSpeed; }//�����ٶȣ�����еĻ�
		inline bool isScanAeraActived()const { return _isScanAeraActived; }//�Ƿ񼤻�ɨ����
		inline qint32 getPositiveScanAera()const {return _positiveScanAera;}//����ɨ������
		inline qint32 getNegativeScanAera()const { return _negativeScanAera; }//����ɨ������
		bool isPathTrafficLocked(qint32* ve = nullptr) {//��ͨ�������
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
		bool lockTraffic(qint32 ve) {//��ͨ��������
			std::unique_lock<std::shared_mutex> lk(_lock);
			_lockOwner = _lockOwner == 0 ? ve : _lockOwner;
			return _lockOwner == ve;
		}

		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
			return SunnyTcsMapObject_tag(Epath, _id);
		}
		virtual qint32 getFromPointId()const = 0;//���id
		virtual qint32 getCtrlPointId()const = 0;//���Ƶ�id
		virtual qint32 getToPointId()const = 0;//Ŀ�ĵص�id
		virtual qint32 getPathLen()const = 0;//·����
		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override = 0;//��ȡ���Խӿ�
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//�������Խӿ�

	protected:
		bool _isSupportPositive;
		bool _isSupportNegative;
		bool _isScanAeraActived;
		qint32 _positiveSpeed;//���ε�Ĭ������
		qint32 _negativeSpeed; //֧�ַ���Ļ��������ٶ�
		qint32 _positiveScanAera;
		qint32 _negativeScanAera;
		qint32 _lockOwner; //��ӵ����

		mutable std::shared_mutex _lock;
	};



	//��λ�ӿ�,�̰߳�ȫ
	class I_SunnyTcsLocation :public I_SunnyTcsElementData ,public QList<SunnyTcsAction> { //ֱ�Ӷ�̳�Qlist,���ŷ���
	public:
		explicit I_SunnyTcsLocation(qint32 id) :I_SunnyTcsElementData(id),QList<SunnyTcsAction>(), _lock() {}

		I_SunnyTcsLocation(const I_SunnyTcsLocation&) = delete;

		virtual ~I_SunnyTcsLocation() {}

		I_SunnyTcsLocation& operator=(const I_SunnyTcsLocation&) = delete;

		virtual SunnyTcsMapObject_tag getTag()const {
			std::shared_lock<std::shared_mutex> lk(_lock);
			return SunnyTcsMapObject_tag(Elocation, _id);
		}

		virtual qint32 getLinkedPointId()const = 0;//�����ĵ�

	protected:
		mutable std::shared_mutex _lock;

	};



	//��Χϵͳ��ʵʱ����,ҲҪ�����̰߳�ȫ����
	class I_SunnyTcsUlsData : public I_SunnyTcsElementData {
	public:
		I_SunnyTcsUlsData(QString code, qint32 id) :I_SunnyTcsElementData(id) {}
		//�ⲿ�豸�ͺ�
		inline QString getUlsCode()const { return _ulsCode; }
		
		//interface
		virtual SunnyTcsMapObject_tag getTag()const {
			return SunnyTcsMapObject_tag(Euls, _id);
		}
		virtual SunnyTcsArg getAttribution(QString key, bool& ok)const override = 0;//��ȡ���Խӿ�
		virtual bool setAttribution(QString key, SunnyTcsArg arg) override = 0;//�������Խӿ�
	protected:
		QString _ulsCode;
	};



	class SunnyTcsSingleCondition;
	//ʵ�����ݵĳ����࣬�������������ݳ�Ա,
	//�̳������ͱ���ʵ�� �Ե������жϵĺ������߱��ж���������Ϊ�����жϵ�ʵ��ִ����
	//�ýӿڻ�����ʵ���ṩȫ��� �ڽӹ�ϵ ͼ �� �����ֲ�ͼ ����·���滮�� �� ���������� ʹ�ã��������ʮ�־�׼����ʵʱ��
	//�ýӿ���Ҫ�ṩ �Բ��ֵ�ͼԪ�� �����޸ĵ�����������Ϊ���ֲ�����API�ṩ�����ݲ���ʵʱ��ȱ�ݣ��б�����
	/*{
		������������������ɷ������Զ�����ɷ��䣬��Ҫʵʱ �޸�agv�Ķ�����״̬�����Զ�����״̬�޸ı�����ʵʱ�ģ�����������ʵʱ
		·���滮��������������ɷ�������Ҫ�� �㣬��·���� ������ʵʱ���� �� ����������·�������޸�Ҳ������ʵʱ������������ʵʱ
	}*/
	class I_SunnyTcsActualData { 
	public:
		//�������Ѿ������õı�׼�ӿ�
		//ģ���ǿ��Ա仯�ģ��и�����Ŀ������豸�ȣ��������ǽ�ִ���ж������Ķ��� ָ��Ϊģ�ͣ���������������
		virtual bool judgeSingleCondition(const SunnyTcsSingleCondition& conditon) = 0;
		//agv״̬��
		virtual void agvStats(QHash<qint32, I_SunnyTcsAgvStat*>& ref) = 0;
		//���
		virtual void points(QHash<qint32, I_SunnyTcsVertex*>& ref) = 0;
		//·����
		virtual void paths(QHash<qint32, I_SunnyTcsEdge*>& ref) = 0;
		//�����
		virtual void uls(QHash<qint32, I_SunnyTcsUlsData*>& ref) = 0;


		//һ���Եõ� froms��
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


		//һ���Եõ� tos��	
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

		//�õ�ĳagv��ǰ��״̬	
		virtual I_SunnyTcsAgvStat* getAgvStat(qint32 id, bool& ok) {
			QHash<qint32, I_SunnyTcsAgvStat*> agvs;
			this->agvStats(agvs);
			return agvs.keys().contains(id) ? agvs[id] : nullptr;
		}

		//����from �� to �ҳ����ʵ�·��
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

		//����id��ȡpath
		virtual I_SunnyTcsEdge* getEdgeById(qint32 id, bool& ok) {
			QHash<qint32, I_SunnyTcsEdge*> phs;
			this->paths(phs);
			return phs.keys().contains(id) ? phs[id] : nullptr;
		}

		//����id,�õ�vertex
		virtual I_SunnyTcsVertex* getVertexById(qint32 id, bool& ok){
			QHash<qint32, I_SunnyTcsVertex*> pts;
			this->points(pts);
			return pts.keys().contains(id) ? pts[id] : nullptr;
		}


		//����id,��ȡ����
		virtual I_SunnyTcsUlsData* getUlsById(qint32 id, bool& ok) {
			QHash<qint32, I_SunnyTcsUlsData*> ulss;
			this->uls(ulss);
			return ulss.keys().contains(id) ? ulss[id] : nullptr;
		}

	};



	//group�ӿڵ�ʵ��
	class SunnyTcsItemGroup :public I_SunnyTcsGroup {
	public:
		SunnyTcsItemGroup(qint32 id,QString name):I_SunnyTcsGroup(id,name){}
		virtual ~SunnyTcsItemGroup(){}

		// ͨ�� I_SunnyTcsGroup �̳�
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
	



