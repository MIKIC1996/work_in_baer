#pragma once
#include "sunnytcsgraphicv3_global.h"


#define GRAPHICS_LOW_ZVALUE 0
#define GRAPHICS_COORSYS_ZVALUE  1
#define GRAPHICS_PATH_ZVALUE 2 
#define GRAPHICS_POINT_ZVALUE 3
#define GRAPHICS_LOCATION_ZVALUE 4
#define GRAPHICS_VEHICLE_ZVALUE 5
#define GRAPHICS_SELECT_ZVALUE 6


using namespace basic;

//mapItem �� ����
//�����������ڣ���֤���еĵ�ͼͼ�ζ���̳��ڴˣ��Ϳ��԰�ȫ�Ľ���dynamic_castת�����Ӷ��������е��麯����֪��ͼ����ʲô����
class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsMapGraphicItem :public QGraphicsItem
{
public:
	//ctor
	SunnyTcsMapGraphicItem(QString name)
		:QGraphicsItem(nullptr), _name(name)
	{
		setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable
			| QGraphicsItem::ItemSendsGeometryChanges
		);
	}
	//copy ctor
	SunnyTcsMapGraphicItem(const SunnyTcsMapGraphicItem&) = default;
	//dtor
	virtual ~SunnyTcsMapGraphicItem() {}
	//assignment
	SunnyTcsMapGraphicItem& operator=(const SunnyTcsMapGraphicItem&) = default;

	//getter 
	QString getName()const { return _name; }

	//setter
	void SetName(QString name) { _name = name; }

	// ͨ�� QGraphicsItem �̳�
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;//������scene����
	

	//����������������������ѡȡ����Ԫ������
	virtual SunnyTcsMapObject_tag getItemTag()const = 0;
	qint32 getItemId()const { return getItemTag()._id; }

protected:
	QString _name; //����

};



//ģ��״̬
enum E_SunnyTcsModelEditStatus {
	E_EDIT = 1, //�༭״̬
	E_RUNNING = 2 //����״̬
};



//��ͼgui��������Ҳ��ͼ��ģ�͵ĳ��࣬�����˸��ֳߴ磬�Լ�ģ��״̬
//�������壬ͨ���ó��࣬��ͼ��Ԫ�ض��󣬿��Ե�֪��ǰģ�͵�״̬���Լ�������Ƴߴ磬�Ӷ��������painter����
class SunnyTcsMapAdjuster
{
public:

	enum applyTargetType {
		POINT = 1,
		PATH =2,
		LOCATION =3,
		VEHICLE =4,
		GROUP =5
	};


	
	SunnyTcsMapAdjuster(qint32 wid, qint32 hei, qint32 resolution)
		:_sceneWid(wid), _sceneHei(hei), _resolution(resolution), _status(E_EDIT),_groupIdCounter(0),
		_ptIdCounter(0), _phIdCounter(0), _locIdCounter(0), _veIdCounter(0), _isAutoTrafficControlOpen(true),
		_ptIdQueue(),_phIdQueue(),_locIdQueue(),_veIdQueue(),_groupIdQueue()
	{
		if (resolution < 500) { //��С����0.5m
			_resolution = 500;
		}
		else if (resolution > 100000) { //��󾫶�100m
			_resolution = 100000;
		}
		//����һ��ֵ
		_ptIdQueue.push(1);
		_phIdQueue.push(1);
		_locIdQueue.push(1);
		_veIdQueue.push(1);
		_groupIdQueue.push(1);
	}

	//getter
	inline qint32 getWidth()const {
		return _sceneWid;
	}

	inline qint32 getHeight()const {
		return _sceneHei;
	}

	inline qint32 getResolution()const {
		return _resolution;
	}

	inline bool isTrackActived()const {
		return _isTrackActived;
	}


	//����ID
	void supplyGroupQueueId( )const {
		supplyQueueId(GROUP);
	}

	void supplyPtQueueId()const {
		supplyQueueId(POINT);
	}

	void supplyPathQueueId()const {
		supplyQueueId(PATH);
	}


	void supplyLocQueueId()const {
		supplyQueueId(LOCATION);
	}


	void supplyVeQueueId()const {
		supplyQueueId(VEHICLE);
	}


	void supplyQueueId(applyTargetType type)const {
		std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>>* que = &_ptIdQueue;
		switch (type)
		{
		case SunnyTcsMapAdjuster::POINT:
			que = &_ptIdQueue;
			break;
		case SunnyTcsMapAdjuster::PATH:
			que = &_phIdQueue;
			break;
		case SunnyTcsMapAdjuster::LOCATION:
			que = &_locIdQueue;
			break;
		case SunnyTcsMapAdjuster::VEHICLE:
			que = &_veIdQueue;
			break;
		case SunnyTcsMapAdjuster::GROUP:
			que = &_groupIdQueue;
			break;
		default:
			Q_ASSERT(0);
			break;
		}

		if (que->empty()) {
			que->push(1);
			que->push(2);
		}
		else if (que->size() == 1) {
			que->push(que->top() + 1);
		}
		
	}




	//����ID
	bool applyForQueueId(applyTargetType type, qint32 id) const{
		Q_ASSERT(id > 0);
		supplyQueueId(type);
		std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>>* que = &_ptIdQueue;
		switch (type)
		{
		case SunnyTcsMapAdjuster::POINT:
			que = &_ptIdQueue;
			break;
		case SunnyTcsMapAdjuster::PATH:
			que = &_phIdQueue;
			break;
		case SunnyTcsMapAdjuster::LOCATION:
			que = &_locIdQueue;
			break;
		case SunnyTcsMapAdjuster::VEHICLE:
			que = &_veIdQueue;
			break;
		case SunnyTcsMapAdjuster::GROUP:
			que = &_groupIdQueue;
			break;
		default:
			Q_ASSERT(0);
			break;
		}
		std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> temp;
		bool finded = false;
		qint32 topVal = 0;
		while (que->size() > 0) {
			topVal = que->top();
			if (topVal != id) {
				temp.push(topVal);
			}
			else {
				finded = true;
				if (que->size() == 1) {
					//�Ѿ������һ���ˣ������Ȳ�����
					supplyQueueId(type);
				}
			}
			que->pop();
		}
		*que = temp;

		if (!finded) {	//�ִ���û�ҵ�Ŀ��
			if (topVal >= id) {
				return false;
			}

			while (topVal <= id) {
				++topVal; //���� 1
				if (topVal != id) {
					que->push(topVal);
				}
			}
		}
		return true;
	}

	bool applyForGroupId(qint32 id) const {
		return applyForQueueId(GROUP, id);
	}

	bool applyForPtId(qint32 id) const {
		return applyForQueueId(POINT, id);
	}

	bool applyForPathId(qint32 id) const {
		return applyForQueueId(PATH,id);
	}


	bool applyForLocId(qint32 id) const {
		return applyForQueueId(LOCATION, id);
	}

	bool applyForVeId(qint32 id) const {
		return applyForQueueId(VEHICLE, id);
	}


	//��ȡID
	qint32 nextGroupId() const{
		supplyGroupQueueId();
		qint32 ret = _groupIdQueue.top();
		_groupIdQueue.pop();
		return ret;
	}


	qint32 nextPtId()const {
		supplyPtQueueId();
		qint32 ret = _ptIdQueue.top();
		_ptIdQueue.pop();
		qDebug() << "next pt id is " << ret;
		return ret;
	}

	qint32 nextPhId()const {
		supplyPathQueueId();
		qint32 ret = _phIdQueue.top();
		_phIdQueue.pop();
		return ret;
	}

	qint32 nextLocId()const {
		supplyLocQueueId();
		qint32 ret = _locIdQueue.top();
		_locIdQueue.pop();
		return ret;
	}

	qint32 nextVeId() const {
		supplyVeQueueId();
		qint32 ret = _veIdQueue.top();
		_veIdQueue.pop();
		return ret;
	}

	//�黹ID
	void returnGroupId(qint32 id)const {
		_groupIdQueue.push(id);
	}

	void returnPtId(qint32 id)const {
		_ptIdQueue.push(id);
	}

	void returnPhId(qint32 id)const {
		_phIdQueue.push(id);
	}

	void returnLocId(qint32 id)const {
		_locIdQueue.push(id);
	}

	void returnVeId(qint32 id)const {
		_veIdQueue.push(id);
	}


	bool isAutoTrafficControlOpen()const { return _isAutoTrafficControlOpen; }
	E_SunnyTcsModelEditStatus getEditStatus()const { return _status; }

	//setter
	void setIsTrackActived(bool is) { _isTrackActived = is; }
	void setEditStatus(E_SunnyTcsModelEditStatus status) { _status = status; }
	void setAutoTrafficControlOpen(bool is) { _isAutoTrafficControlOpen = is; }

	
	
	//��ͼ��� ����ֱ���
	qint32 _sceneWid;		//scene ��
	qint32 _sceneHei;		//scene ��		
	qint32 _resolution;		//����ֱ���
	//����ɫ
	QColor _backColor = QColor(60, 60, 60); 
	//select ѡ�е���ɫ����ͳһ
	QColor _item_select_color = QColor(247, 198, 54);
	//����ɫҲ����ͳһ
	QColor _item_warning_color = Qt::red; 
	//������ɫ
	QColor _item_error_color = Qt::red;

protected:

	//�Ƿ������Զ���ͨ����
	bool _isAutoTrafficControlOpen;
	//״̬
	E_SunnyTcsModelEditStatus _status = E_EDIT;

	bool _isTrackActived = false;

	mutable qint32 _groupIdCounter;
	mutable qint32 _ptIdCounter;
	mutable qint32 _phIdCounter;
	mutable qint32 _locIdCounter;
	mutable qint32 _veIdCounter;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _groupIdQueue;//��ID
	mutable std::priority_queue<qint32 ,std::vector<qint32>,std::greater<qint32>> _ptIdQueue;//������ɾ������黹ID,�Թ�����ʹ��
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _phIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _locIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _veIdQueue;

};


