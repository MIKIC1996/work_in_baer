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

//mapItem 的 超类
//存在意义在于，保证所有的地图图形对象继承于此，就可以安全的进行dynamic_cast转换，从而调用特有的虚函数，知道图形是什么类型
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

	// 通过 QGraphicsItem 继承
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;//限制在scene以内
	

	//下述两个函数，用以区分选取到的元素类型
	virtual SunnyTcsMapObject_tag getItemTag()const = 0;
	qint32 getItemId()const { return getItemTag()._id; }

protected:
	QString _name; //名字

};



//模型状态
enum E_SunnyTcsModelEditStatus {
	E_EDIT = 1, //编辑状态
	E_RUNNING = 2 //运行状态
};



//地图gui调整器，也是图形模型的超类，定义了各种尺寸，以及模型状态
//存在意义，通过该超类，子图形元素对象，可以得知当前模型的状态，以及各项绘制尺寸，从而合理调用painter函数
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
		if (resolution < 500) { //最小精度0.5m
			_resolution = 500;
		}
		else if (resolution > 100000) { //最大精度100m
			_resolution = 100000;
		}
		//插入一个值
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


	//补充ID
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




	//申请ID
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
					//已经是最后一个了，必须先补充下
					supplyQueueId(type);
				}
			}
			que->pop();
		}
		*que = temp;

		if (!finded) {	//现存中没找到目标
			if (topVal >= id) {
				return false;
			}

			while (topVal <= id) {
				++topVal; //自增 1
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


	//获取ID
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

	//归还ID
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

	
	
	//地图宽高 区块分辨率
	qint32 _sceneWid;		//scene 宽
	qint32 _sceneHei;		//scene 高		
	qint32 _resolution;		//区块分辨率
	//背景色
	QColor _backColor = QColor(60, 60, 60); 
	//select 选中的颜色必须统一
	QColor _item_select_color = QColor(247, 198, 54);
	//报警色也必须统一
	QColor _item_warning_color = Qt::red; 
	//报错颜色
	QColor _item_error_color = Qt::red;

protected:

	//是否启动自动交通管制
	bool _isAutoTrafficControlOpen;
	//状态
	E_SunnyTcsModelEditStatus _status = E_EDIT;

	bool _isTrackActived = false;

	mutable qint32 _groupIdCounter;
	mutable qint32 _ptIdCounter;
	mutable qint32 _phIdCounter;
	mutable qint32 _locIdCounter;
	mutable qint32 _veIdCounter;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _groupIdQueue;//组ID
	mutable std::priority_queue<qint32 ,std::vector<qint32>,std::greater<qint32>> _ptIdQueue;//当对象被删除，会归还ID,以供后续使用
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _phIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _locIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _veIdQueue;

};


